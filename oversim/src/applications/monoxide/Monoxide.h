/*
 * Monoxide.h
 *
 * This application simulated the mining facilities of Monoxide.
 * Mining facility workflow:
 * *. FULL_NODEs init with initial Transaction, no inbound RelayTransaction at bootstrap (jump 1)
 * 0. FULL_NODEs gather Transaction from clients and inbound RelayTransaction from other FULL_NODEs. (running as a daemon)
 * 1. FULL_NODEs generate new TransactionBlock with Transaction and confirmed inbound RelayTransaction.
 *     To avoid to invalidate transactions when originate block becomes orphan.
 *     We slightly changed Fork Resolution strategy by only allow RelayTransaction to be packed when its originate block is considered confirmed, i.e. with 6 blocks followed.
 *     This is reasonable because it is rare for a confirmed block becomes orphan later and it is useless and confusing to invalidate a confirmed transaction.
 *     But it is possible for a available/unsolved block becomes orphan as 0.83% orphan rate shown in experiment.
 *     The outbound transactions are generated from Transactions.
 * 2. FULL_NODEs update and send ChainBlock to COORDINATOR. (whenever a new BatchChainBlock is updated in blockchain in this zone)
 * FULL_NODE ===ChainBlock===> COORDINATOR
 * 3. COORDINATOR gather ChainBlocks and update ChainBlockList.
 * 4. COORDINATOR generate PoWPuzzle and send to MINERs.
 * COORDINATOR ===PoWPuzzle(broadcast)===> MINER
 * 5. MINERs calculate PoWPuzzle and get PoWNonce.
 * 6. MINERs send PoWNonce to COORDINATOR.
 * MINER ===PoWNonce===> COORDINATOR
 * 7. COORDINATOR generate BatchChainBlock for each zone if PoWNonce is valid.
 * 8. COORDINATOR send BatchChainBlock to FULL_NODEs in all zones.
 * COORDINATOR ===BatchChainBlock===> FULL_NODE (jump 9, 14)
 * 9. FULL_NODEs get outbound Transactions from TransactionBlock.
 * 10. FULL_NODEs generate forwarded RelayTransaction from outbound Transactions.
 * 11. FULL_NODEs send forwarded RelayTransaction to target zone.
 * FULL_NODE ===RelayTransaction===> FULL_NODE
 * 12. FULL_NODEs in target zone receive forwarded RelayTransaction and broadcast in zone.
 * FULL_NODE ===RelayTransaction(broadcast)===> FULL_NODE
 * 13. FULL_NODEs store forwarded RelayTransaction into TransactionPool. (done)
 * 14. Origin FULL_NODE broadcast full BatchChainBlock in zone if the BatchChainBlock is valid.
 * FULL_NODE ===BatchChainBlock(broadcast, FULL_BLOCK)===> FULL_NODE
 * 15. FULL_NODEs receive full BatchChainBlock, store into Blockchain if the BatchChainBlock is valid. (jump 1)
 *
 *  Created on: Oct 30, 2020
 *      Author: qucheng
 */

#ifndef APPLICATIONS_MONOXIDE_MONOXIDE_H_
#define APPLICATIONS_MONOXIDE_MONOXIDE_H_

#include "common/OverSimDefs.h"

#include "common/BaseApp.h"

#include "Monoxide_m.h"
#include "Blockchain.h"

#define DEBUG_BREAK {int a=0;a=a+1;if(a==1){a=1;}}
//#define DEBUG_MONOXIDE
//#define CROSS_ZONE_TRANSACTIONS

class Monoxide : public BaseApp
{
    // shared global parameters
    static int global_index; // for fast assign node id
    static uint64_t global_tx_id; // for fast assign tx hash
    static uint64_t global_header_id; // for fast assign chain block hash
    static uint64_t global_block_id; // for fast assign batch chain block hash
    static uint64_t global_pow_nonce; // for fast assign the pow nonce

    uint64_t next_hash(uint64_t &h);

#ifdef DEBUG_MONOXIDE
    // only for debug,
    static std::list<ChainBlock> debug_all_headers;
    static std::list<PoWPuzzle> debug_all_puzzles;
    static std::list<PoWNonce> debug_all_nonces;
    static std::list<BatchChainBlock> debug_all_blocks;
    static std::list<BatchChainBlock> debug_all_stores;
    static std::list<Blockchain*> debug_all_blockchains;
#endif

    // module parameters
    int sharding_scale; // how many zones, numbers of zones is (1<<sharding_scale)
    int n_coordinators; // how many mining facilities total
    int n_full_nodes; // how many full nodes in each zone of one mining facility, must be 1
    int n_miners; // how many miners in one mining facility

    // only for simulation, the average block interval
    int block_interval; //ms
    // only for simulation, the full batch chain block size
    int block_size; //kB
    int transaction_size; //B
    unsigned int tx_per_block;

    // derived parameters
    int n_zones;

    enum{
        ROLE_FULL_NODE=0,
        ROLE_MINER=1,
        ROLE_COORDINATOR=2
    };

    // node parameters
    int pub_key, srt_key; // the global id of this node
    int coordinator_id; // the mining facility id
    int full_node_id_base; // base index of full node, just for coordinator
    int miner_id_base; // base index of miner, just for coordinator
    int zone_id; // the zone id (if it is not miner)
    int role; // full node, miner, or mining coordinator

    // the block chain structure (for simulation, while not store all block)
    Blockchain *blockchain = nullptr;

    TransactionBlock *tx_block; // for storing transactions
    TransactionPool *tx_pool; // for storing inbound relay transactions

    void send_chain_block();
    void fill_transaction_block();

    ChainBlockList *block_list; // for coordinator storing ChainBlockList

    PoWPuzzleMessage *powPuzzleMsg = nullptr; // the coordinator's puzzle message
    BatchChainBlockMessage *batchChainBlockMsg = nullptr; // the coordinator's batch chain block message

    PoWPuzzleMessage *puzzleMsg = nullptr; // for miner store the puzzle message

    void init_monoxide_message(MonoxideMessage *msg, int type, int byte_length);

    // statistics
    int numSent;              //number of packets sent
    int numReceived;          //number of packets received

    // our timer
    cMessage *timerMsg = nullptr, *initMsg = nullptr;

    // message handlers
    void handle_batch_block_message(BatchChainBlockMessage *msg);
    void handle_full_block_message(BatchChainBlockMessage *msg);

    // application routines
    void initializeApp(int stage);                 // called when the module is being created
    void finishApp();                              // called when the module is about to be destroyed
    void handleTimerEvent(cMessage* msg);          // called when we received a timer message
    void deliver(OverlayKey& key, cMessage* msg);  // called when we receive a message from the overlay
    void handleUDPMessage(cMessage* msg);          // called when we receive a UDP message

public:
    Monoxide() { timerMsg = nullptr; };
    ~Monoxide() { cancelAndDelete(timerMsg); delete[] blockchain;};
};

#endif /* APPLICATIONS_MONOXIDE_MONOXIDE_H_ */
