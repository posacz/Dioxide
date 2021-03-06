/*
 * Blockchain.h
 *
 *  Created on: Nov 2, 2020
 *      Author: qucheng
 */

#ifndef APPLICATIONS_MONOXIDE_BLOCKCHAIN_H_
#define APPLICATIONS_MONOXIDE_BLOCKCHAIN_H_

#include <cstdint>
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <cmath>
#include <cassert>
#include <algorithm>

//#define DEBUG_BLOCKCHAIN
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

class CoinbaseTransaction: public Transaction
{
public:
    explicit inline CoinbaseTransaction(int who){
        from = -1;
        to = who;
    }
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

    void buildBlock(int miner);

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
    int pow_target;
    uint64_t confirmed_root; // transaction block tx_tree root
    uint64_t outbound_root;

#ifdef DEBUG_BLOCKCHAIN
    int debug_full_node_key;
#endif
};

class ChainBlockList
{
public:
    std::unique_ptr<MerkleTree<ChainBlock>> header_tree = nullptr;
    std::vector<ChainBlock> headers;
    std::vector<bool> is_sent;
    int size;
    const int capacity;

    explicit ChainBlockList(int capacity):
            headers(capacity),
            is_sent(capacity),
            size(0),
            capacity(capacity)
    {
        std::fill(is_sent.begin(), is_sent.end(), false);
    }
    virtual ~ChainBlockList() = default;
    inline void add(const ChainBlock &chainBlock){
        int zone_id = chainBlock.index;
        if (headers[zone_id].version == 0){
            ++size;
        }
        assert(headers[zone_id].version < chainBlock.version);
        headers[zone_id] = chainBlock;
        is_sent[zone_id] = false;
    }
    inline void buildTree(){
        assert(size==capacity);
        header_tree.reset(new MerkleTree<ChainBlock>(headers));
    }
    inline uint64_t root_hash() const{
        return header_tree->root->hashvalue;
    }
    inline void sent(){
        std::fill(is_sent.begin(), is_sent.end(), true);
    }
};

class PoWPuzzle
{
public:
    // batch config
    int base_index;
    int batch_size;
    int batch_scale;
    // block list root
    uint64_t block_list_root;

#ifdef DEBUG_BLOCKCHAIN
    // additional debug info
    double debug_puzzle_timestamp;
    int debug_cooridnator_key;
    std::vector<ChainBlock> debug_block_list;
#endif
};

class PoWNonce: public PoWPuzzle
{
public:
    uint64_t pow_nonce;

#ifdef DEBUG_BLOCKCHAIN
    // additional debug info
    double debug_puzzle_timestamp;
    double debug_pow_timestamp;
    int debug_miner_key;
#endif
};

class BatchChainBlock: public MerkleTreeData
{
public:
    // chain block
    int version;
    int scale;
    int index;
    uint64_t prev_hash;
    double timestamp;
    int pow_target;
    uint64_t confirmed_root;
    uint64_t outbound_root;

    // batch chain block
    std::shared_ptr<MerkleTreePath> header_path = nullptr;
    int base_index;
    int batch_size;
    int batch_scale;
    uint64_t batch_pow_nonce;

    // only for simulation, simplify block chain and transaction storage
    // only for full block, the transaction block
    std::shared_ptr<TransactionBlock> tx_block;

#ifdef DEBUG_BLOCKCHAIN
    // additional debug info
    double debug_puzzle_timestamp;
    double debug_pow_timestamp;
    double debug_block_timestamp;
    double debug_store_timestamp;
    int debug_miner_key;
    int debug_coordinator_key;
    int debug_full_node_key;
    int debug_store_node_key;
#endif

    BatchChainBlock()=default;
    BatchChainBlock(const BatchChainBlock& batchChainBlock)=default;
    virtual ~BatchChainBlock()=default;
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
    const BatchChainBlock *last_block = nullptr; // store last valid block, the block chain
    const BatchChainBlock *latest_block = nullptr; // store latest block
    // if fork exists, store all blocks of all forks here
    std::list<BatchChainBlock> block_tree; // refer to all nodes of block tree, pruned by N_CONFIRM
    std::map<uint64_t, const BatchChainBlock*> leaf_blocks; // store all leaf blocks of all forks in block_tree
    // only for simulation, store only outbound root of all blocks for validation of relay transactions
    std::vector<uint64_t> outbound_root_history; // outbound_root_history
    std::vector<int> block_height_history; // block height history
    std::vector<uint64_t> prev_hash_history; // previous block hash history
    std::map<uint64_t, int> block_hash_index; // map from block hash to index in history

    void append_block_info(const BatchChainBlock &block);

    explicit Blockchain() = default;
    virtual ~Blockchain() = default;

    void init(const BatchChainBlock &genesis_block);

    void prune();
    int store_fork_block(const BatchChainBlock &fork_block);
    bool store_new_block(const BatchChainBlock &new_block);

    int new_block(const BatchChainBlock &block);

    std::vector<double> timestamp_history; // timestamp history
    double original_timestamp;
    int check_relay_transaction(const RelayTransaction &relay_tx);
};

#endif /* APPLICATIONS_MONOXIDE_BLOCKCHAIN_H_ */
