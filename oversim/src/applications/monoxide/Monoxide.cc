/*
 * Monoxide.cc
 *
 *  Created on: Oct 30, 2020
 *      Author: qucheng
 */


#include <string>
#include <climits>

#include "common/UnderlayConfigurator.h"
#include "common/GlobalStatistics.h"

#include "applications/monoxide/Monoxide_m.h"

#include "applications/monoxide/Monoxide.h"

#include "overlay/monoxideoverlay/MonoxideOverlay.h"

#include "common/InitStages.h"

#include <execinfo.h>

Define_Module(Monoxide);

int Monoxide::global_index = 0;
uint64_t Monoxide::global_tx_id = 0;
uint64_t Monoxide::global_header_id = 0;
uint64_t Monoxide::global_block_id = 0;
uint64_t Monoxide::global_pow_nonce = 0;

#ifdef DEBUG_MONOXIDE
std::list<ChainBlock> Monoxide::debug_all_headers;
std::list<PoWPuzzle> Monoxide::debug_all_puzzles;
std::list<PoWNonce> Monoxide::debug_all_nonces;
std::list<BatchChainBlock> Monoxide::debug_all_blocks;
std::list<BatchChainBlock> Monoxide::debug_all_stores;
std::list<Blockchain*> Monoxide::debug_all_blockchains;
#endif

uint64_t Monoxide::next_hash(uint64_t &h){
    return static_cast<uint64_t>(intuniform(0,10000))*1000000ULL + h++;
}

static inline int get_zone_id(const int& pub_key, const int& sharding_scale){
    return pub_key & ((1<<sharding_scale)-1);
}

void Monoxide::init_monoxide_message(MonoxideMessage *msg, int type, int byte_length){
    msg->setType(type);
    msg->setSenderAddress(thisNode);
    msg->setSenderKey(pub_key);
    msg->setByteLength(byte_length);
}

// initializeApp() is called when the module is being created.
// Use this function instead of the constructor for initializing variables.
void Monoxide::initializeApp(int stage)
{
    // initializeApp will be called twice, each with a different stage.
    // stage can be either MIN_STAGE_APP (this module is being created),
    // or MAX_STAGE_APP (all modules were created).

    if (stage == MAX_STAGE_APP){
        if (role == ROLE_FULL_NODE){
            // let's wait until all nodes joined the network, dynamic join/leave is not implemented yet
            scheduleAt(simTime() + 30.0, initMsg);
        }
    }
    if (stage != MIN_STAGE_APP) return;

    // copy the module parameter values to our own variables
    sharding_scale = par("sharding_scale");
    n_full_nodes = par("n_full_nodes");
    n_miners = par("n_miners");
    n_coordinators = par("n_coordinators"); // number of mining facilities

    block_interval = par("block_interval");
    block_size = par("block_size");
    transaction_size = par("transaction_size");
    tx_per_block = block_size * 1024 / transaction_size;

    // set node parameters
    srt_key = global_index++; // set srt_key be a incremental value
    pub_key = srt_key; // only for simulation, set pub_key = srt_key

    thisNode.setKey(pub_key);
    // only for simulation, set overlay key directly. static setting without bootstrap.
    MonoxideOverlay *monoxideoverlay = dynamic_cast<MonoxideOverlay*>(overlay);
    monoxideoverlay->myKey = pub_key;

    n_zones = (1<<sharding_scale);

    int total_full_nodes = n_full_nodes * n_coordinators * n_zones;
    int total_work_nodes = n_coordinators * n_miners + total_full_nodes;
    // int total_nodes = total_work_nodes + n_coordinators;
    /* each zone: n_full_nodes*n_coordinators full nodes, n_miners*n_coordinators/n_zones miners
     * pub_key:
     * 0 ~ total_full_nodes-1 : ROLE_FULL_NODE
     *   + 0 ~ n_zones-1 : facility 0
     *   + n_zones ~ 2*n_zones-1 : facility 1
     *     ...
     * total_full_nodes ~ total_work_nodes-1 : ROLE_MINER
     *   + 0 ~ n_miners-1 : facility 0
     *   + n_miners ~ 2*n_miners-1 : facility 1
     *     ...
     * total_work_nodes ~ total_nodes : ROLE_COORDINATOR
     *   + 0 : coordinator 0
     *   + 1 : coordinator 1
     *     ...
     */

    if (pub_key < total_full_nodes){ // full node
        zone_id = get_zone_id(pub_key, sharding_scale);
        coordinator_id = pub_key / n_zones;
        role = ROLE_FULL_NODE;
    } else if (pub_key < total_work_nodes) { // miner
        role = ROLE_MINER;
        coordinator_id = (pub_key-total_full_nodes) / n_miners;
    } else {
        role = ROLE_COORDINATOR;
        coordinator_id = pub_key - total_work_nodes;
        full_node_id_base = coordinator_id*n_zones;
        miner_id_base = total_full_nodes + coordinator_id*n_miners;
    }
    coordinator_id = coordinator_id + total_work_nodes;

    // initialize our statistics variables
    numSent = 0;
    numReceived = 0;

    // tell the GUI to display our variables
    WATCH(numSent);
    WATCH(numReceived);

    EV << "Monoxide: Node Key:" << pub_key << " Role:" << role << std::endl;

    if (role == ROLE_FULL_NODE){
        // *. FULL_NODEs init with initial Transaction, no inbound RelayTransaction at bootstrap
        // create transaction pool and init blockchain structure
        tx_pool = new TransactionPool();
        blockchain = new Blockchain[n_zones];
        // init genesis blocks
        BatchChainBlock genesis_block;
        genesis_block.version = 0;
        genesis_block.hashvalue = 0;
        genesis_block.prev_hash = 0;
        genesis_block.scale = sharding_scale;
        genesis_block.timestamp = simTime().dbl();
        genesis_block.confirmed_root = 0;
        genesis_block.outbound_root = 0;
        for (int id = 0; id < n_zones; ++id){
            genesis_block.index = id;
            blockchain[id].init(genesis_block);

#ifdef DEBUG_MONOXIDE
            debug_all_blockchains.emplace_back(blockchain+id);
#endif
        }

        // 1. FULL_NODEs generate new TransactionBlock and ChainBlock with Transaction and confirmed inbound RelayTransaction.
        // generate a chain block, filled with initial transactions
        tx_block = new TransactionBlock();
        fill_transaction_block();
        // create merkle tree
        tx_block->buildBlock(coordinator_id);

        // wait for initial phase done
        initMsg = new cMessage("Init Timer");
        timerMsg = new cMessage("Node Timer");

    } else if (role == ROLE_MINER){
        timerMsg = new cMessage("Miner Timer");
        puzzleMsg = nullptr;
    } else if (role == ROLE_COORDINATOR){
        timerMsg = new cMessage("Coordinator Timer");
        // coordinator init the block list
        block_list = new ChainBlockList(n_zones);

        powPuzzleMsg = new PoWPuzzleMessage();
        init_monoxide_message(powPuzzleMsg, MMSG_POW_PUZZLE, 16);
        PoWPuzzle &powPuzzle = powPuzzleMsg->getPowPuzzle();
        powPuzzle.base_index = 0;
        powPuzzle.batch_size = n_zones;
        powPuzzle.batch_scale = sharding_scale;

        batchChainBlockMsg = new BatchChainBlockMessage();
        init_monoxide_message(batchChainBlockMsg, MMSG_BATCH_BLOCK, 120);
    }

    bindToPort(2000);
}


void Monoxide::send_chain_block(){
    // send block header to coordinator
    ChainBlockMessage *chainBlockMsg = new ChainBlockMessage();
    init_monoxide_message(chainBlockMsg, MMSG_BLOCK, 100);
    ChainBlock &chainBlock = chainBlockMsg->getChainBlock();
    chainBlock.version = blockchain[zone_id].last_block->version + 1; // we use version to store the block height
    chainBlock.scale = sharding_scale;
    chainBlock.index = zone_id;
    chainBlock.prev_hash = blockchain[zone_id].last_block->hash(); // previous block hash
    chainBlock.timestamp = simTime().dbl();
    chainBlock.pow_target = block_interval; // only for simulation, we use this to indicate average block time
    chainBlock.confirmed_root = tx_block->confirmedRoot();
    chainBlock.outbound_root = tx_block->outboundRoot();
    chainBlock.hashvalue = next_hash(global_header_id);

#ifdef DEBUG_BLOCKCHAIN
    chainBlock.debug_full_node_key = pub_key;
#endif

#ifdef DEBUG_MONOXIDE
    debug_all_headers.emplace_back(chainBlock);
#endif

    numSent++; // update statistics

    //EV << pub_key << ": Sending ChainBlock to " << coordinator_id << "!" << std::endl;

    callRoute(coordinator_id, chainBlockMsg); // send it to the coordinator through overlay
}

// finish is called when the module is being destroyed
void Monoxide::finishApp()
{
    // finish() is usually used to save the module's statistics.
    // We'll use globalStatistics->addStdDev(), which will calculate min, max, mean and deviation values.
    // The first parameter is a name for the value, you can use any name you like (use a name you can find quickly!).
    // In the end, the simulator will mix together all values, from all nodes, with the same name.

    globalStatistics->addStdDev("Monoxide: Sent packets", numSent);
    globalStatistics->addStdDev("Monoxide: Received packets", numReceived);
    if (role == ROLE_FULL_NODE){
        for (int i = 0; i < n_zones; ++i){
            globalStatistics->addStdDev("Monoxide: Block height", blockchain[i].last_block->version);
            globalStatistics->addStdDev("Monoxide: Block count", blockchain[i].block_count);
            globalStatistics->addStdDev("Monoxide: Fork count", blockchain[i].fork_count);
            globalStatistics->addStdDev("Monoxide: Switch count", blockchain[i].switch_count);
            globalStatistics->addStdDev("Monoxide: Orphan count", blockchain[i].orphan_count);
        }
    }
}


// handleTimerEvent is called when a timer event triggers
void Monoxide::handleTimerEvent(cMessage* msg)
{
    // if the simulator is still busy creating the network,
    // let's wait a bit longer
    if (underlayConfigurator->isInInitPhase()){
        scheduleAt(simTime() + 1.0, msg);
        return;
    }

    if (role == ROLE_FULL_NODE){
        if (msg == initMsg){
            // Booststrap, initial ChainBlockMessage
            // 2. FULL_NODEs send ChainBlock to COORDINATOR.
            send_chain_block();
            delete msg;
            // start timer for broadcast new BatchChainBlock and send new ChainBlock
            // scheduleAt(simTime() + 1.0, msg);
        } else if (msg == timerMsg){
            // broadcast new BatchChainBlock
        } else {
            MonoxideMessage *monoxideMsg = dynamic_cast<MonoxideMessage*>(msg);
            int msgType = monoxideMsg->getType();
            if (msgType == MMSG_BATCH_BLOCK){
                handle_batch_block_message(dynamic_cast<BatchChainBlockMessage*>(msg));
            } else if (msgType == MMSG_FULL_BLOCK){
                handle_full_block_message(dynamic_cast<BatchChainBlockMessage*>(msg));
            } else {
                error("Error msg type");
            }
        }
    } else if (role == ROLE_COORDINATOR){
        assert(msg == timerMsg);
        // create and send new PoWPuzzle to miners
    } else if (role == ROLE_MINER){
        assert(msg == timerMsg);
        // PoW finished
        // 6. MINERs send PoWNonce to COORDINATOR.
        PoWNonceMessage *powNonceMsg = new PoWNonceMessage();
        init_monoxide_message(powNonceMsg, MMSG_POW_NONCE, 20);
        PoWNonce& powNonce = powNonceMsg->getPowNonce();
        PoWPuzzle& powPuzzle = puzzleMsg->getPowPuzzle();
        PoWPuzzle *pPuzzle = static_cast<PoWPuzzle*>(&powNonce);
        *pPuzzle = powPuzzle;
        powNonce.block_list_root = powPuzzle.block_list_root;
        powNonce.pow_nonce = next_hash(global_pow_nonce);

#ifdef DEBUG_BLOCKCHAIN
        powNonce.debug_puzzle_timestamp = powPuzzle.debug_puzzle_timestamp;
        powNonce.debug_pow_timestamp = simTime().dbl();
        powNonce.debug_miner_key = pub_key;
#endif

#ifdef DEBUG_MONOXIDE
        debug_all_nonces.emplace_back(powNonce);
#endif

        delete puzzleMsg;
        puzzleMsg = nullptr;
        callRoute(coordinator_id, powNonceMsg);
    } else {
        error("Timer");
    }
}

void Monoxide::fill_transaction_block(){
    // first, get all confirmed inbound relay transactions from tx_pool
    for (auto it = tx_pool->tx_list.begin(); it != tx_pool->tx_list.end();){
        Transaction &tx = it->relay_tx;
        assert(get_zone_id(tx.to, sharding_scale) == zone_id);
        int status = blockchain[get_zone_id(tx.from, sharding_scale)].check_relay_transaction(*it);
        if (status == Blockchain::RELAY_TX_CONFIRMED){
            // pack transaction
            tx_block->add_relay_transaction(*it);
            it = tx_pool->tx_list.erase(it);
            if (tx_block->txs.size()+tx_block->relay_txs.size() >= tx_per_block){
                break;
            }
        } else if (status == Blockchain::RELAY_TX_INVALID){
            // remove invalid relay transaction
            it = tx_pool->tx_list.erase(it);
        } else { //Blockchain::RELAY_TX_AVAILABLE
            ++it;
        }
    }
    // second, load transactions from disk
    while (tx_block->txs.size()+tx_block->relay_txs.size() < tx_per_block){
        Transaction tx;
        tx.hashvalue = next_hash(global_tx_id);
        //TODO: fill the transaction with real transaction values
        tx.from = n_zones*intuniform(0, n_full_nodes*n_coordinators-1) + zone_id;
#ifdef CROSS_ZONE_TRANSACTIONS
        tx.to = intuniform(0, n_full_nodes*n_coordinators*n_zones-1);
#else
        tx.to = n_zones*intuniform(0, n_full_nodes*n_coordinators-1) + zone_id;
#endif
        tx_block->add_transaction(tx);
    }
    // generate outbound transactions
    for (auto it = tx_block->txs.begin(); it != tx_block->txs.end(); ++it){
        if (get_zone_id(it->to, sharding_scale) != zone_id){ // it is a outbound transaction
            tx_block->outbound_txs.push_back(&(*it));
        }
    }
    // build merkle tree
    tx_block->buildBlock(coordinator_id);
}

void Monoxide::handle_batch_block_message(BatchChainBlockMessage *msg){
    BatchChainBlock &batchChainBlock = msg->getBatchChainBlock();
    if (zone_id == batchChainBlock.index){
        assert(tx_block->txs.size() > 0);
        assert(tx_block->tx_tree != nullptr);
        if (tx_block->confirmedRoot() != batchChainBlock.confirmed_root){
            // inconsistency of coordinator and full node, abort
            delete msg;
            return;
        }
    }
    // 15. FULL_NODEs receive BatchChainBlock, store into Blockchain. (jump 0)
    int status = blockchain[batchChainBlock.index].new_block(batchChainBlock);
    if (status == Blockchain::BLOCK_STATE_FUTURE){
        // let us delay this message
        scheduleAt(simTime() + 1.0, msg->dup());
        delete msg;
        return;
    } else if (status != Blockchain::BLOCK_STATE_INVALID){
#ifdef DEBUG_MONOXIDE
        batchChainBlock.debug_store_timestamp = simTime().dbl();
        batchChainBlock.debug_store_node_key = pub_key;
        debug_all_stores.emplace_back(batchChainBlock);
#endif
        // 14. FULL_NODEs broadcast BatchChainBlock in zone.
        msg->setType(MMSG_FULL_BLOCK);
        if (batchChainBlock.index == zone_id){ // also replicate transaction block
            batchChainBlock.tx_block.reset(tx_block);
            msg->setByteLength(block_size * 1024);
        } else { // only replicate batch chain block
            batchChainBlock.tx_block = nullptr;
            msg->setByteLength(100);
        }
        for (int id = 0; id < n_coordinators; ++id){
            int dest_id = id * n_zones + zone_id;
            if (dest_id != pub_key){ // not me
                callRoute(dest_id, msg->dup());
            }
        }
        if (batchChainBlock.index == zone_id){

            globalStatistics->addStdDev("Monoxide: Transactions/block", tx_block->all_txs.size());
            globalStatistics->addStdDev("Monoxide: Inbound Transactions/block", tx_block->relay_txs.size());
            globalStatistics->addStdDev("Monoxide: Outbound Transactions/block", tx_block->outbound_txs.size());

            // 9. FULL_NODEs get outbound Transactions from TransactionBlock.
            if (tx_block->outbound_txs.size()>0){
                // 10. FULL_NODEs generate forwarded RelayTransaction from outbound Transactions.
                for (size_t out_id = 0; out_id < tx_block->outbound_txs.size(); ++out_id){
                    Transaction *outbound_tx = tx_block->outbound_txs.at(out_id);
                    RelayTransactionMessage *relayTxMsg = new RelayTransactionMessage();
                    init_monoxide_message(relayTxMsg, MMSG_FORWARDED_TX, 128);
                    RelayTransaction &relayTx = relayTxMsg->getRelayTransaction();
                    relayTx.hashvalue = outbound_tx->hashvalue;
                    relayTx.scale = sharding_scale;
                    relayTx.index = zone_id;
                    relayTx.orig_block_height = batchChainBlock.version;
                    relayTx.position = out_id;
                    relayTx.relay_tx = *outbound_tx;

                    relayTx.relay_tx_path.reset(tx_block->outbound_tx_tree->generatePath(out_id));
                    // 11. FULL_NODEs send forwarded RelayTransaction to target zone.
                    callRoute(pub_key-zone_id+get_zone_id(outbound_tx->to, sharding_scale), relayTxMsg);
                }
            }
            tx_block = new TransactionBlock(); // prepare next tx_block
            // (jump 0)
            // 0. FULL_NODEs gather Transaction from clients and inbound RelayTransaction from other FULL_NODEs.
            // 1. FULL_NODEs generate new TransactionBlock with Transaction and confirmed inbound RelayTransaction
            fill_transaction_block();
            // 2. FULL_NODEs update and send ChainBlock to COORDINATOR. (whenever a new BatchChainBlock is updated in blockchain in this zone)
            send_chain_block();
        }
    } else {
        error("Invalid block");
    }
    // delete this origin message
    delete msg;
}

void Monoxide::handle_full_block_message(BatchChainBlockMessage *msg){
    BatchChainBlock &batchChainBlock = msg->getBatchChainBlock();
    // 15. FULL_NODEs receive BatchChainBlock, store into Blockchain.
    int status = blockchain[batchChainBlock.index].new_block(batchChainBlock);
    if (status == Blockchain::BLOCK_STATE_FUTURE){
        // let us delay this message
        scheduleAt(simTime() + 1.0, msg->dup());
        //error("future");
        delete msg;
        return;
    } else if (status != Blockchain::BLOCK_STATE_INVALID){
#ifdef DEBUG_MONOXIDE
        batchChainBlock.debug_store_timestamp = simTime().dbl();
        batchChainBlock.debug_store_node_key = pub_key;
        debug_all_stores.emplace_back(batchChainBlock);
#endif
        //  (jump 0)
        if (batchChainBlock.index == zone_id){
            Blockchain& bc = blockchain[zone_id];
            if (bc.latest_block == bc.last_block){ // not a fork
                // received block is on the main fork, remove same transactions in tx_block and received TransactionBlock, and fill new Transactions
                tx_block->remove_duplicate(*batchChainBlock.tx_block);
                // 0. FULL_NODEs gather Transaction from clients and inbound RelayTransaction from other FULL_NODEs.
                // 1. FULL_NODEs generate new TransactionBlock with Transaction and confirmed inbound RelayTransaction.
                fill_transaction_block();
                // 2. FULL_NODEs update and send ChainBlock to COORDINATOR. (whenever a new BatchChainBlock is updated in blockchain in this zone)
                send_chain_block();
            }
        }
    } else {
        error("Invalid block");
    }
    delete msg;
}

// deliver() is called when we receive a message from the overlay.
// Unknown packets can be safely deleted here.
void Monoxide::deliver(OverlayKey& key, cMessage* msg)
{
    if (overlay->getThisNode().getKey().isUnspecified()){
        error("key");
    }
    // we are only expecting messages of type MonoxideMessage, throw away any other
    MonoxideMessage *monoxideMsg = dynamic_cast<MonoxideMessage*>(msg);
    if (monoxideMsg == nullptr) {
        delete msg; // type unknown!
        return;
    }
    //EV << thisNode.getIp() << ": Got packet from " << monoxideMsg->getSenderAddress() << std::endl;
    int msgType = monoxideMsg->getType();
    if (role == ROLE_COORDINATOR){
        if (msgType == MMSG_BLOCK){
            ChainBlockMessage *chainBlockMsg = dynamic_cast<ChainBlockMessage*>(monoxideMsg);
            // 3. COORDINATOR gather ChainBlocks and form ChainBlockList.
            ChainBlock &chainBlock = chainBlockMsg->getChainBlock();
            if (block_list->headers[chainBlock.index].version < chainBlock.version){
                block_list->add(chainBlock);
                if (block_list->size == n_zones){
                    // 4. COORDINATOR generate PoWPuzzle and send to MINERs.
                    block_list->buildTree();
                    PoWPuzzle &powPuzzle = powPuzzleMsg->getPowPuzzle();
                    powPuzzle.block_list_root = block_list->root_hash();
    #ifdef DEBUG_BLOCKCHAIN
                    powPuzzle.debug_puzzle_timestamp = simTime().dbl();
                    powPuzzle.debug_cooridnator_key = pub_key;
                    powPuzzle.debug_block_list = block_list->headers;
    #endif
    #ifdef DEBUG_MONOXIDE
                    debug_all_puzzles.emplace_back(powPuzzle);
                    // check block_list
                    int min_version = INT_MAX, max_version = 0;
                    for (auto it=block_list->headers.begin(); it!=block_list->headers.end(); ++it){
                        if (it->version < min_version){
                            min_version = it->version;
                        }
                        if (it->version > max_version){
                            max_version = it->version;
                        }
                    }
                    if (max_version - min_version > 1){
                        error("puzzle");
                    }
    #endif
                    for (int i=0; i<n_miners; ++i){
                        // send to miners
                        callRoute(miner_id_base+i, powPuzzleMsg->dup());
                    }
                }
            }
            delete chainBlockMsg;
        } else if (msgType == MMSG_POW_NONCE){
            PoWNonceMessage *powNonceMsg = dynamic_cast<PoWNonceMessage*>(monoxideMsg);
            PoWNonce& powNonce = powNonceMsg->getPowNonce();
            if (block_list->size == n_zones && powNonce.block_list_root == block_list->root_hash()){
                double latest_timestamp = 0;
                // 7. COORDINATOR generate BatchChainBlock for each zone.
                for (int id=0; id<block_list->size; ++id){
                    // 8. COORDINATOR send BatchChainBlock to FULL_NODEs in all zones.
                    ChainBlock& chainBlock = block_list->headers[id];
                    bool is_sent = block_list->is_sent[id];
                    if (is_sent){ // already sent this chain block
                        continue;
                    }
                    if (latest_timestamp < chainBlock.timestamp){
                        latest_timestamp = chainBlock.timestamp;
                    }
                    assert(id==chainBlock.index);
                    BatchChainBlock& batchChainBlock = this->batchChainBlockMsg->getBatchChainBlock();
                    batchChainBlock.version = chainBlock.version;
                    batchChainBlock.scale = chainBlock.scale;
                    batchChainBlock.index = chainBlock.index;
                    batchChainBlock.prev_hash = chainBlock.prev_hash;
                    batchChainBlock.timestamp = chainBlock.timestamp;
                    batchChainBlock.pow_target = chainBlock.pow_target;
                    batchChainBlock.confirmed_root = chainBlock.confirmed_root;
                    batchChainBlock.outbound_root = chainBlock.outbound_root;

                    batchChainBlock.base_index = powNonce.base_index;
                    batchChainBlock.batch_size = powNonce.batch_size;
                    batchChainBlock.batch_scale = powNonce.batch_scale;
                    batchChainBlock.batch_pow_nonce = powNonce.pow_nonce;

                    // only for simulation, reduce sim time by skip path generation
                    // batchChainBlock.header_path.reset(block_list->header_tree->generatePath(id));

                    // only for simulation, get block hashvalue from global variable
                    batchChainBlock.hashvalue = next_hash(global_block_id);

#ifdef DEBUG_BLOCKCHAIN
                    batchChainBlock.debug_puzzle_timestamp = powNonce.debug_puzzle_timestamp;
                    batchChainBlock.debug_pow_timestamp = powNonce.debug_pow_timestamp;
                    batchChainBlock.debug_block_timestamp = simTime().dbl();
                    batchChainBlock.debug_coordinator_key = pub_key;
                    batchChainBlock.debug_miner_key = powNonce.debug_miner_key;
                    batchChainBlock.debug_full_node_key = chainBlock.debug_full_node_key;
#endif

#ifdef DEBUG_MONOXIDE
                    debug_all_blocks.emplace_back(batchChainBlock);
#endif

                    // send to all zones
                    for (int dest_id=0; dest_id<n_zones; ++dest_id){
                        callRoute(full_node_id_base+dest_id, batchChainBlockMsg->dup());
                    }
                }
                block_list->sent(); // set is_sent
                globalStatistics->addStdDev("Monoxide: Mining time", simTime().dbl()-latest_timestamp);
            }
            delete powNonceMsg;
        } else {
            delete monoxideMsg;
        }
    } else if (role == ROLE_MINER) {
        if (msgType == MMSG_POW_PUZZLE){
            if (puzzleMsg != nullptr){
                delete puzzleMsg;
                puzzleMsg = nullptr;
            }
            puzzleMsg = dynamic_cast<PoWPuzzleMessage*>(monoxideMsg);
            // 5. MINERs calculate PoWPuzzle and get PoWNonce.
            int total_miners = n_miners * n_coordinators;

            double block_time = block_interval / (double)1000.0 * (double)total_miners;
            block_time = exponential(block_time);

            // cancel previous puzzle
            if (timerMsg->isScheduled()){
                cancelEvent(timerMsg);
            }
            // wait for block time to get the PoWNonce
            scheduleAt(simTime() + block_time, timerMsg);
        } else {
            delete monoxideMsg;
        }
    } else if (role == ROLE_FULL_NODE) {
        if (msgType == MMSG_BATCH_BLOCK){
            // this is a batch chain block header send by our coordinator
            handle_batch_block_message(dynamic_cast<BatchChainBlockMessage*>(monoxideMsg));
        } else if (msgType == MMSG_FULL_BLOCK){
            // this is a full batch chain block send by other full nodes
            handle_full_block_message(dynamic_cast<BatchChainBlockMessage*>(monoxideMsg));
        } else if (msgType == MMSG_FORWARDED_TX){
            RelayTransactionMessage *relayTxMsg = dynamic_cast<RelayTransactionMessage*>(monoxideMsg);
            relayTxMsg->setType(MMSG_RELAY_TX);
            RelayTransaction &relayTx = relayTxMsg->getRelayTransaction();
            assert(relayTx.index != zone_id); // this is a forwarded message
            // 12. FULL_NODEs in target zone receive forwarded RelayTransaction and broadcast in zone.
            for (int id = 0; id < n_coordinators; ++id){
                int dest_id = id * n_zones + zone_id;
                if (dest_id != pub_key){ // not me
                    callRoute(dest_id, relayTxMsg->dup());
                }
            }
            // 13. FULL_NODEs store forwarded RelayTransaction into TransactionPool. (done)
            tx_pool->tx_list.push_back(relayTx);
            delete relayTxMsg;
        } else if (msgType == MMSG_RELAY_TX){
            RelayTransactionMessage *relayTxMsg = dynamic_cast<RelayTransactionMessage*>(monoxideMsg);
            RelayTransaction &relayTx = relayTxMsg->getRelayTransaction();
            // 13. FULL_NODEs store forwarded RelayTransaction into TransactionPool. (done)
            tx_pool->tx_list.push_back(relayTx);
            delete relayTxMsg;
        } else {
            delete monoxideMsg;
        }
    } else {
        delete monoxideMsg;
    }
    // send it back to its owner
    //sendMessageToUDP(monoxideMsg->getSenderAddress(), monoxideMsg);
}


// handleUDPMessage() is called when we receive a message from UDP.
// Unknown packets can be safely deleted here.
void Monoxide::handleUDPMessage(cMessage* msg)
{
    // Message isn't needed any more -> delete it
    delete msg;
}
