/*
 * Blockchain.h
 *
 *  Created on: Nov 2, 2020
 *      Author: qucheng
 */

#ifndef APPLICATIONS_DIOXIDE_BLOCKCHAIN_H_
#define APPLICATIONS_DIOXIDE_BLOCKCHAIN_H_

#include <cstdint>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <cmath>
#include <cassert>

namespace dioxide{
#define DEBUG_BLOCKCHAIN
//#define LEDGER_PRUNE

class MerkleTreeData
{
public:
    uint64_t hashvalue = 0;
    inline uint64_t hash() const{
        return hashvalue;
    }
    virtual ~MerkleTreeData(){}
};

class BaseTransaction: public MerkleTreeData
{
public:
};

class Transaction: public BaseTransaction
{
public:
    int from, to, value;
};

class MerkleTreePathNode
{
public:
    MerkleTreePathNode *left = nullptr, *right = nullptr, *parent = nullptr;
    uint64_t hashvalue = 0, hash_proof = 0;
};

class MerkleTreePath
{
public:
    MerkleTreePathNode *root = nullptr, *leaf = nullptr;
    virtual ~MerkleTreePath();
};

class MerkleTreeNode
{
public:
    MerkleTreeNode *left = nullptr, *right = nullptr, *parent = nullptr;
    uint64_t hashvalue = 0;
};

template <typename T>
class MerkleTree
{
public:
    MerkleTreeNode *root = nullptr;
    int size = 0, depth = 0;
    const std::vector<T> *data = nullptr;

    template <typename D>
    const MerkleTreeData *cast_data(D &d){
        return dynamic_cast<const MerkleTreeData*>(&d);
    }
    template <typename D>
    const MerkleTreeData *cast_data(D *pd){
        return dynamic_cast<const MerkleTreeData*>(pd);
    }

    // only for simulation, root hash is left hash + right hash
    MerkleTreeNode *createMerkleTree(int& index, int depth){
        if (index>=this->size){
            return nullptr;
        }
        MerkleTreeNode *node = new MerkleTreeNode();
        //leaf node
        if (depth==this->depth){
            const MerkleTreeData *pd = cast_data(data->at(index));
            node->hashvalue = pd->hash();
            index += 1;
            return node;
        }
        //left child
        node->left = this->createMerkleTree(index, depth+1);
        node->left->parent = node;
        //right child
        node->right = this->createMerkleTree(index, depth+1);
        if (node->right != nullptr){
            node->right->parent = node;
        }
        //hashvalue
        node->hashvalue = node->left->hashvalue;
        if (node->right != nullptr){
            node->hashvalue += node->right->hashvalue;
        }
        return node;
    }
    void deleteMerkleTree(MerkleTreeNode *root){
        if (root == nullptr){
            return;
        }
        this->deleteMerkleTree(root->left);
        this->deleteMerkleTree(root->right);
        delete root;
    }

    explicit MerkleTree(const std::vector<T> &data){
        this->data = &data;
        this->size = data.size();
        if (size == 0){ // empty tree
            this->depth = 0;
            return;
        }
        if (size == 1){
            this->depth = 1;
        }else{
            this->depth = floor(log2(size-1))+2;
        }
        int index = 0;
        this->root = this->createMerkleTree(index, 1);
    }
    virtual ~MerkleTree(){
        this->deleteMerkleTree(this->root);
    }

    MerkleTreePath *generatePath(int index){
        if (index >= this->size){
            return nullptr;
        }
        MerkleTreePath *path = new MerkleTreePath();
        MerkleTreePathNode *path_root = new MerkleTreePathNode();
        path->root = path_root;
        MerkleTreeNode *cur_node = this->root;
        MerkleTreePathNode *path_node = path_root;
        for (int d=1; d<this->depth; ++d){
            path_node->hashvalue = cur_node->hashvalue;
            if (index & (1<<(this->depth-d-1))){
                path_node->right = new MerkleTreePathNode();
                path_node->hash_proof = cur_node->left->hashvalue;
                path_node->right->parent = path_node;
                path_node = path_node->right;
                cur_node = cur_node->right;
            } else {
                path_node->left = new MerkleTreePathNode();
                if (cur_node->right != nullptr){
                    path_node->hash_proof = cur_node->right->hashvalue;
                }
                path_node->left->parent = path_node;
                path_node = path_node->left;
                cur_node = cur_node->left;
            }
        }
        path_node->hashvalue = cur_node->hashvalue;
        path->leaf = path_node;
        return path;
    }
};

class RelayTransaction: public BaseTransaction
{
public:
    int scale;
    int index;
    int orig_block_height;
    int position;
    Transaction relay_tx; // the outbound transaction from another zone
    std::shared_ptr<MerkleTreePath> relay_tx_path = nullptr;
};

class TransactionPool
{
public:
    std::list<RelayTransaction> tx_list;

    TransactionPool()=default;
    virtual ~TransactionPool()=default;
};

class TransactionBlock
{
public:
    std::list<Transaction> txs;
    std::list<RelayTransaction> relay_txs;

    MerkleTree<BaseTransaction*> *tx_tree;
    std::vector<BaseTransaction*> all_txs;

    MerkleTree<Transaction*> *outbound_tx_tree;
    std::vector<Transaction*> outbound_txs;

    TransactionBlock();
    virtual ~TransactionBlock();

    void add_transaction(const Transaction &tx);
    void add_relay_transaction(const RelayTransaction &tx);

    void buildBlock();

    uint64_t confirmedRoot() const;
    uint64_t outboundRoot() const;

    void clear();

    void remove_duplicate(const TransactionBlock &tx_block);
};

class ChainBlock: public MerkleTreeData
{
public:
    // block header
    int version = 0;
    int scale;
    int index;
    uint64_t prev_hash;
    double timestamp;
    uint64_t confirmed_root; // transaction block tx_tree root
    uint64_t outbound_root;
    int signature; // validator sign this block

#ifdef DEBUG_BLOCKCHAIN
    int debug_full_node_key;
#endif

    ChainBlock()=default;
    ChainBlock(const ChainBlock& chainBlock)=default;
};

class FullBlock: public ChainBlock
{
public:
    // only for simulation, simplify block chain and transaction storage
    // only for full block, the transaction block
    std::shared_ptr<TransactionBlock> tx_block = nullptr;

    FullBlock()=default;
    FullBlock(const FullBlock& fullBlock)=default;
    FullBlock(const ChainBlock& chainBlock):ChainBlock(chainBlock)
    {
    }
    virtual ~FullBlock()=default;
};

class Blockchain
{
    // only for simulation, blocks are not actually stored.
    // only latest block headers and histroy of outbound roots are stored.
public:
    // orphaned block is block on a fork with height lower than current block height - N_CONFIRM
    // relay transaction becomes invalid when origin block becomes orphaned.
    enum{
        BLOCK_STATE_INVALID = 0,
        BLOCK_STATE_NEW = 1,
        BLOCK_STATE_FORK = 2,
        BLOCK_STATE_FUTURE = 3 // a future block is a block come earlier than its previous block
    };
    enum{
        RELAY_TX_AVAILABLE = 0,
        RELAY_TX_CONFIRMED = 1,
        RELAY_TX_INVALID =  2
    };
    static constexpr int N_CONFIRM = 6; // 6 block confirmation
    int block_count = 0; // +1 when new block success
    int fork_count = 0; // +1 when a block append on a fork branch
    int switch_count = 0; // +1 when main branch switched
    int orphan_count = 0; // +1 when a branch dropped
    const FullBlock *last_block = nullptr; // store last valid block, the block chain
    const FullBlock *latest_block = nullptr; // store latest block
    // if fork exists, store all blocks of all forks here
    std::list<FullBlock> block_tree; // refer to all nodes of block tree, pruned by N_CONFIRM
    std::map<uint64_t, const FullBlock*> leaf_blocks; // store all leaf blocks of all forks in block_tree
    // only for simulation, store only outbound root of all blocks for validation of relay transactions
    std::vector<uint64_t> outbound_root_history; // outbound_root_history
    std::vector<int> block_height_history; // block height history
    std::vector<uint64_t> prev_hash_history; // previous block hash history
    std::map<uint64_t, int> block_hash_index; // map from block hash to index in history

    void append_block_info(const FullBlock &block);

    explicit Blockchain() = default;
    virtual ~Blockchain() = default;

    void init(const FullBlock &genesis_block);

    void prune();
    int store_fork_block(const FullBlock &fork_block);
    bool store_new_block(const FullBlock &new_block);

    int new_block(const FullBlock &block);

    std::vector<double> timestamp_history; // timestamp history
    double original_timestamp;
    int check_relay_transaction(const RelayTransaction &relay_tx);
};

// block of main chain
// Since we do not simulate main chain, we use this block stores all necessary info shared with all nodes
class MainBlock
{
public:
    // global randomness
    unsigned rand;

    bool is_inited = false;

    explicit MainBlock() = default;
    void init(unsigned rand);
};

}

#endif /* APPLICATIONS_MONOXIDE_BLOCKCHAIN_H_ */
