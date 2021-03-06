/*
 * Blockchain.c
 *
 *  Created on: Nov 3, 2020
 *      Author: qucheng
 */

#include "Blockchain.h"

#include <algorithm>

MerkleTreePath::~MerkleTreePath(){
    MerkleTreePathNode *leaf = this->leaf, *next_leaf = nullptr;
    while (leaf->parent != nullptr){
        next_leaf = leaf->parent;
        delete leaf;
        leaf = next_leaf;
    }
}

TransactionBlock::TransactionBlock(){
    tx_tree = nullptr;
    outbound_tx_tree = nullptr;
}

TransactionBlock::~TransactionBlock(){
    delete tx_tree;
    delete outbound_tx_tree;
}

void TransactionBlock::buildBlock(int miner){
    txs.emplace_back(CoinbaseTransaction(miner));

    all_txs.clear();
    for (auto it = txs.begin(); it != txs.end(); ++it){
        all_txs.emplace_back(&(*it));
    }
    for (auto it = relay_txs.begin(); it != relay_txs.end(); ++it){
        all_txs.emplace_back(&(*it));
    }
    tx_tree = new MerkleTree<BaseTransaction*>(all_txs);

    // outbound transactions
    outbound_tx_tree = new MerkleTree<Transaction*>(outbound_txs);
}

uint64_t TransactionBlock::confirmedRoot() const{
    return tx_tree->root->hashvalue;
}

uint64_t TransactionBlock::outboundRoot() const{
    // outbound tx may be not exists
    if (outbound_tx_tree->root == nullptr){
        return 0;
    }
    return outbound_tx_tree->root->hashvalue;
}

void TransactionBlock::clear(){
    delete tx_tree;
    delete outbound_tx_tree;
    tx_tree = nullptr;
    outbound_tx_tree = nullptr;
    outbound_txs.clear();
    all_txs.clear();

    txs.clear();
    relay_txs.clear();
}

void TransactionBlock::add_transaction(const Transaction &tx){
    txs.emplace_back(tx);
}

void TransactionBlock::add_relay_transaction(const RelayTransaction &tx){
    relay_txs.emplace_back(tx);
}

void TransactionBlock::remove_duplicate(const TransactionBlock& tx_block){
    if (outbound_tx_tree != nullptr){ // clear outbound txs if exists
        delete outbound_tx_tree;
        outbound_tx_tree = nullptr;
        outbound_txs.clear();
    }
    if (tx_tree != nullptr){ // clear tx tree and all txs
        delete tx_tree;
        tx_tree = nullptr;
        all_txs.clear();
    }
    txs.clear(); // only for simulation, remove all transactions
    // remove duplicate transactions
//    for (auto itb = tx_block.txs.begin(); itb != tx_block.txs.end(); ++itb){
//        for (auto ita = txs.begin(); ita != txs.end();){
//            if (ita->hash() == itb->hash()){
//                // remove ita
//                ita = txs.erase(ita);
//            } else {
//                ++ita;
//            }
//        }
//    }
    // remove duplicate relay transactions
    for (auto itb = tx_block.relay_txs.begin(); itb != tx_block.relay_txs.end(); ++itb){
        for (auto ita = relay_txs.begin(); ita != relay_txs.end();){
            if (ita->hash() == itb->hash()){
                // remove ita
                ita = relay_txs.erase(ita);
            } else {
                ++ita;
            }
        }
    }
}

void Blockchain::init(const BatchChainBlock &genesis_block){
    block_tree.emplace_back(genesis_block);
    last_block = &block_tree.back();
    append_block_info(genesis_block);
    latest_block = last_block;
}

void Blockchain::append_block_info(const BatchChainBlock &block){
    int size = outbound_root_history.size();
    outbound_root_history.push_back(block.outbound_root);
    block_height_history.push_back(block.version);
    prev_hash_history.push_back(block.prev_hash);
    timestamp_history.push_back(block.timestamp);
    block_hash_index[block.hash()] = size;
}

void Blockchain::prune(){
#ifdef LEDGER_PRUNE
    // only for simulation, clean block with too low block height here
    for (auto it = block_tree.begin(); it != block_tree.end();){
        if (it->version + N_CONFIRM < last_block->version){
            auto leaf = leaf_blocks.find(it->hash());
            if (leaf != leaf_blocks.end()){
                // here we deleted a branch
                leaf_blocks.erase(leaf);
                ++orphan_count;
            }
            it = block_tree.erase(it);
        } else {
            ++it;
        }
    }
#endif
}

int Blockchain::store_fork_block(const BatchChainBlock &fork_block){
#ifdef LEDGER_PRUNE
    // with ledger prune, blocks with block height less than current height - N_CONFIRM are pruned
    if (fork_block.version + N_CONFIRM <= last_block->version){
        // ignore block height less than current height - N_CONFIRM
        return BLOCK_STATE_INVALID;
    }
#endif
    // can we find previous block in block_tree?
    for (auto it = block_tree.begin(); it != block_tree.end(); ++it){
        if (fork_block.prev_hash == it->hash() && fork_block.version == it->version + 1){
            assert(last_block != &(*it)); // this should not happen in a fork
            // found previous block, append fork block
            leaf_blocks.erase(it->hash());
            block_tree.emplace_back(fork_block);
            append_block_info(fork_block);
            latest_block = &block_tree.back();
            leaf_blocks[latest_block->hash()] = latest_block;
            if (fork_block.version > last_block->version){
                // we need to replace the block chain with this fork
                // this case is rare, since orphan rate is low when block interval is large
                last_block = &block_tree.back();
                ++switch_count;
                prune();
            }
            return BLOCK_STATE_FORK;
        }
    }
    // may be it is a future block
    if (fork_block.version + N_CONFIRM > last_block->version + 1){
        return BLOCK_STATE_FUTURE;
    }
    // we can not found previous block
    // this case should be very rare in simulation environment when network delay is small
    // without block buffer and block synchronize mechanism, we treat this as an error now
    assert(false);
    return BLOCK_STATE_INVALID;
    // only for simulation, here we skip validation of transaction block and some field of batch chain block
}

bool Blockchain::store_new_block(const BatchChainBlock &new_block){
    if (new_block.version != last_block->version+1){
        // block height not match
        return false;
    }
    if (last_block->hash() != new_block.prev_hash){
        // block hash not match
        return false;
    }
    // only for simulation, here we skip validation of transaction block and some field of batch chain block
    leaf_blocks.erase(last_block->hash());
    block_tree.emplace_back(new_block);
    last_block = &block_tree.back();
    append_block_info(new_block);
    latest_block = &block_tree.back();
    leaf_blocks[latest_block->hash()] = latest_block;
    prune();
    return true;
}

int Blockchain::new_block(const BatchChainBlock &block){
    // ensure index is right
    assert(block.index == last_block->index);
    // return true if the block is stored
    if (store_new_block(block)){ // this is a valid new block in block chain
        ++block_count;
        return BLOCK_STATE_NEW;
    }
    int status = store_fork_block(block);
    if (status == BLOCK_STATE_FORK){
        ++block_count;
        ++fork_count;
        return BLOCK_STATE_FORK;
    }
    return status;
}

int Blockchain::check_relay_transaction(const RelayTransaction &relay_tx){
    uint64_t cur_hash = last_block->hash();
    int cur_index = block_hash_index[cur_hash];
    int cur_height = last_block->version;
    if (relay_tx.orig_block_height + N_CONFIRM > cur_height){
        return RELAY_TX_AVAILABLE;
    }
    for (;cur_height > relay_tx.orig_block_height;){
        cur_hash = prev_hash_history[cur_index];
        cur_index = block_hash_index[cur_hash];
        cur_height = block_height_history[cur_index];
    }
    assert(cur_height == relay_tx.orig_block_height);
    if (relay_tx.relay_tx_path->root->hashvalue == outbound_root_history[cur_index]){
        original_timestamp = timestamp_history[cur_index];
        return RELAY_TX_CONFIRMED;
    }
    return RELAY_TX_INVALID;
}

