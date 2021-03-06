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

#include "applications/dioxide/Dioxide_m.h"

#include "applications/dioxide/Dioxide.h"

#include "overlay/monoxideoverlay/MonoxideOverlay.h"

#include "common/InitStages.h"

#include <execinfo.h>

using namespace dioxide;

Define_Module(Dioxide);

int Dioxide::global_index = 0;
uint64_t Dioxide::global_tx_id = 0;
uint64_t Dioxide::global_header_id = 0;
MainBlock Dioxide::global_main_block;
simtime_t Dioxide::init_time;

#ifdef DEBUG_DIOXIDE
std::list<ChainBlock> Dioxide::debug_all_headers;
std::list<Blockchain*> Dioxide::debug_all_blockchains;
#endif

uint64_t Dioxide::next_hash(uint64_t &h){
    return static_cast<uint64_t>(intuniform(0,10000))*1000000ULL + h++;
}

static inline int get_zone_id(const int& pub_key, const int& sharding_scale){
    return pub_key & ((1<<sharding_scale)-1);
}

void Dioxide::init_dioxide_message(DioxideMessage *msg, int type, int byte_length){
    msg->setType(type);
    msg->setSenderAddress(thisNode);
    msg->setSenderKey(pub_key);
    msg->setByteLength(byte_length);
}

// initializeApp() is called when the module is being created.
// Use this function instead of the constructor for initializing variables.
void Dioxide::initializeApp(int stage)
{
    // initializeApp will be called twice, each with a different stage.
    // stage can be either MIN_STAGE_APP (this module is being created),
    // or MAX_STAGE_APP (all modules were created).

    if (stage == MAX_STAGE_APP){
        // let's wait until all nodes joined the network, dynamic join/leave is not implemented yet
        scheduleAt(simTime() + 30.0, initMsg);
        init_time = simTime() + 30.0;
    }
    if (stage != MIN_STAGE_APP) return;

    // copy the module parameter values to our own variables
    sharding_scale = par("sharding_scale");
    n_full_nodes = par("n_full_nodes");
    n_validators = par("n_validators"); // number of validators

    time_slot = par("time_slot");
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

    // int total_nodes = n_full_nodes * n_validators * n_zones;
    /* each zone: n_full_nodes*n_validators full nodes
     * pub_key:
     *   0 ~ n_zones-1 : validator 0
     *   n_zones ~ 2*n_zones-1 : validator 1
     *   ...
     */

    // full node
    zone_id = get_zone_id(pub_key, sharding_scale);
    validator_id = pub_key / n_zones;
    full_node_id_base = validator_id * n_zones;

    // init the PRG
    global_main_block.init(intuniform(0,10000));
    vs.init(n_zones, zone_id, n_validators, global_main_block.rand);

    // initialize our statistics variables
    numSent = 0;
    numReceived = 0;

    // tell the GUI to display our variables
    WATCH(numSent);
    WATCH(numReceived);

    EV << "Dioxide: Node Key:" << pub_key << std::endl;

    // *. FULL_NODEs init with initial Transaction, no inbound RelayTransaction at bootstrap
    // create transaction pool and init blockchain structure
    tx_pool = new TransactionPool();
    blockchain = new Blockchain[n_zones];
    // init genesis blocks
    FullBlock genesis_block;
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

    tx_block = new TransactionBlock();

    // wait for initial phase done
    initMsg = new cMessage("Init Timer");
    timerMsg = new cMessage("Node Timer");

    bindToPort(10000+pub_key);
}


void Dioxide::send_chain_block(){
    // 0. FULL_NODEs gather Transaction from clients and inbound RelayTransaction from other FULL_NODEs.
    // 1. FULL_NODEs generate new TransactionBlock with Transaction and confirmed inbound RelayTransaction
    fill_transaction_block();
    // 2. FULL_NODEs select validator randomly, current validators create and sign FullBlock and broadcast in zone.
    //    Then send ChainBlock to other zones. (jump 5)
    globalStatistics->addStdDev("Dioxide: Transactions/block", tx_block->all_txs.size());
    globalStatistics->addStdDev("Dioxide: Inbound Transactions/block", tx_block->relay_txs.size());
    globalStatistics->addStdDev("Dioxide: Outbound Transactions/block", tx_block->outbound_txs.size());

    // send block header to all other zones
    DChainBlockMessage *chainBlockMsg = new DChainBlockMessage();
    init_dioxide_message(chainBlockMsg, DMSG_BLOCK, 100);
    ChainBlock &chainBlock = chainBlockMsg->getChainBlock();
    chainBlock.version = blockchain[zone_id].last_block->version + 1; // we use version to store the block height
    chainBlock.scale = sharding_scale;
    chainBlock.index = zone_id;
    chainBlock.prev_hash = blockchain[zone_id].last_block->hash(); // previous block hash
    chainBlock.timestamp = simTime().dbl();
    chainBlock.confirmed_root = tx_block->confirmedRoot();
    chainBlock.outbound_root = tx_block->outboundRoot();
    chainBlock.hashvalue = next_hash(global_header_id);
    chainBlock.signature = srt_key;

#ifdef DEBUG_BLOCKCHAIN
    chainBlock.debug_full_node_key = pub_key;
#endif

#ifdef DEBUG_MONOXIDE
    debug_all_headers.emplace_back(chainBlock);
#endif

    // send full block in zone
    DFullBlockMessage *fullBlockMsg = new DFullBlockMessage();
    init_dioxide_message(fullBlockMsg, DMSG_FULL_BLOCK, block_size*1024);
    FullBlock &fullBlock = fullBlockMsg->getFullBlock();
    fullBlock = FullBlock(chainBlock);
    fullBlock.tx_block.reset(tx_block);

    int status = blockchain[fullBlock.index].new_block(fullBlock);
    assert(status == Blockchain::BLOCK_STATE_NEW);

    numSent++; // update statistics

    // send fullBlock in zone
    for (int id = 0; id < n_validators; ++id){
        int dest_id = id * n_zones + zone_id;
        if (pub_key != dest_id){
            assert(dest_id != fullBlockMsg->getSenderKey());
            fullBlockMsg->setDestKey(dest_id);
            callRoute(dest_id, fullBlockMsg->dup());
        }
    }
    // send chainBlock to all other zones
    for (int i=0; i<n_zones; ++i){
        int dest_id = full_node_id_base + i;
        if (pub_key != dest_id){
            assert(dest_id != chainBlockMsg->getSenderKey());
            chainBlockMsg->setDestKey(dest_id);
            callRoute(dest_id, chainBlockMsg->dup());
        }
    }

    // 5. FULL_NODEs(validators) get outbound Transactions from TransactionBlock.
    if (tx_block->outbound_txs.size()>0){
        // 10. FULL_NODEs generate forwarded RelayTransaction from outbound Transactions.
        for (size_t out_id = 0; out_id < tx_block->outbound_txs.size(); ++out_id){
            Transaction *outbound_tx = tx_block->outbound_txs.at(out_id);
            DRelayTransactionMessage *relayTxMsg = new DRelayTransactionMessage();
            init_dioxide_message(relayTxMsg, DMSG_FORWARDED_TX, 128);
            RelayTransaction &relayTx = relayTxMsg->getRelayTransaction();
            relayTx.hashvalue = outbound_tx->hashvalue;
            relayTx.scale = sharding_scale;
            relayTx.index = zone_id;
            relayTx.orig_block_height = chainBlock.version;
            relayTx.position = out_id;
            relayTx.relay_tx = *outbound_tx;

            relayTx.relay_tx_path.reset(tx_block->outbound_tx_tree->generatePath(out_id));
            // 11. FULL_NODEs send forwarded RelayTransaction to target zone.
            int dest_id = pub_key-zone_id+get_zone_id(outbound_tx->to, sharding_scale);
            relayTxMsg->setDestKey(dest_id);
            callRoute(dest_id, relayTxMsg);
        }
    }
    delete chainBlockMsg;
    delete fullBlockMsg;

    tx_block = new TransactionBlock();
}

// finish is called when the module is being destroyed
void Dioxide::finishApp()
{
    // finish() is usually used to save the module's statistics.
    // We'll use globalStatistics->addStdDev(), which will calculate min, max, mean and deviation values.
    // The first parameter is a name for the value, you can use any name you like (use a name you can find quickly!).
    // In the end, the simulator will mix together all values, from all nodes, with the same name.

    globalStatistics->addStdDev("Dioxide: Sent packets", numSent);
    globalStatistics->addStdDev("Dioxide: Received packets", numReceived);
    for (int i = 0; i < n_zones; ++i){
        globalStatistics->addStdDev("Dioxide: Block height", blockchain[i].last_block->version);
        globalStatistics->addStdDev("Dioxide: Block count", blockchain[i].block_count);
        globalStatistics->addStdDev("Dioxide: Fork count", blockchain[i].fork_count);
        globalStatistics->addStdDev("Dioxide: Switch count", blockchain[i].switch_count);
        globalStatistics->addStdDev("Dioxide: Orphan count", blockchain[i].orphan_count);
    }
}


// handleTimerEvent is called when a timer event triggers
void Dioxide::handleTimerEvent(cMessage* msg)
{
    // if the simulator is still busy creating the network,
    // let's wait a bit longer
    if (underlayConfigurator->isInInitPhase()){
        scheduleAt(simTime() + 1.0, msg);
        return;
    }

    if (msg == initMsg){
        // wait until init time
        if (simTime() < init_time){
            scheduleAt(init_time, initMsg);
            return;
        }
    }

    if (msg == initMsg){
        assert(simTime() >= init_time);
        // Booststrap, initial ChainBlockMessage
        time_slot_id = 1;
        // 2. FULL_NODEs send FullBlock&ChainBlock
        if (vs.get_validator(time_slot_id) == validator_id){
            send_chain_block();
        }
        delete msg;
        assert(simTime().dbl() < init_time.dbl() + time_slot/1000.0*(time_slot_id-1) + 5.0);
        scheduleAt(init_time + time_slot/1000.0*time_slot_id, timerMsg);
    } else if (msg == timerMsg){
        // broadcast FullBlock&ChainBlock
        ++time_slot_id;
        int cur_validator = vs.get_validator(time_slot_id);
        if (cur_validator == validator_id){
            send_chain_block();
        }
        assert(simTime().dbl() < init_time.dbl() + time_slot/1000.0*(time_slot_id-1) + 5.0);
        scheduleAt(init_time + time_slot/1000.0*time_slot_id, timerMsg);
    } else {
        DioxideMessage *dioxideMsg = dynamic_cast<DioxideMessage*>(msg);
        int msgType = dioxideMsg->getType();
        if (msgType == DMSG_BLOCK){
            handle_chain_block_message(dynamic_cast<DChainBlockMessage*>(msg));
        } else if (msgType == DMSG_FULL_BLOCK){
            handle_full_block_message(dynamic_cast<DFullBlockMessage*>(msg));
        } else {
            error("Error msg type");
        }
    }
}

void Dioxide::fill_transaction_block(){
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
        tx.from = n_zones*intuniform(0, n_full_nodes*n_validators - 1) + zone_id;
#ifdef CROSS_ZONE_TRANSACTIONS
        tx.to = intuniform(0, n_full_nodes*n_validators*n_zones-1);
#else
        tx.to = n_zones*intuniform(0, n_full_nodes*n_validators - 1) + zone_id;
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
    tx_block->buildBlock();
}

void Dioxide::handle_chain_block_message(DChainBlockMessage *msg){
    ChainBlock &chainBlock = msg->getChainBlock();
    assert(zone_id != chainBlock.index);
    int status = blockchain[chainBlock.index].new_block(FullBlock(chainBlock));
    if (status == Blockchain::BLOCK_STATE_FUTURE){
        // let us delay this message
        scheduleAt(simTime() + 1.0, msg->dup());
        delete msg;
        return;
    } else if (status != Blockchain::BLOCK_STATE_INVALID){
        // 4. FULL_NODEs(other zone) receive ChainBlock and store ChainBlock into Blockchain, then broadcast in zone. (done)
        if (validator_id == msg->getSenderKey()/n_zones){
            // broadcast in zone
            for (int id = 0; id < n_validators; ++id){
                int dest_id = id * n_zones + zone_id;
                if (dest_id != pub_key){ // not me
                    msg->setDestKey(dest_id);
                    callRoute(dest_id, msg->dup());
                }
            }
        }
    } else {
        error("Invalid block");
    }
    // delete this origin message
    delete msg;
}

void Dioxide::handle_full_block_message(DFullBlockMessage *msg){
    FullBlock &fullBlock = msg->getFullBlock();
    assert(fullBlock.index == zone_id);
    // 3. FULL_NODEs(not validator) receive and store FullBlock, update tx pool. (done)
    int status = blockchain[fullBlock.index].new_block(fullBlock);
    if (status == Blockchain::BLOCK_STATE_FUTURE){
        // let us delay this message
        scheduleAt(simTime() + 1.0, msg->dup());
        delete msg;
        return;
    } else if (status != Blockchain::BLOCK_STATE_INVALID){
        Blockchain& bc = blockchain[zone_id];
        if (bc.latest_block == bc.last_block){ // not a fork
            // received block is on the main fork, remove same transactions in tx_block and received TransactionBlock, and fill new Transactions
            tx_block->remove_duplicate(*fullBlock.tx_block);
        }
    } else {
        error("Invalid block");
    }
    delete msg;
}

// deliver() is called when we receive a message from the overlay.
// Unknown packets can be safely deleted here.
void Dioxide::deliver(OverlayKey& key, cMessage* msg)
{
    if (overlay->getThisNode().getKey().isUnspecified()){
        error("key");
    }
    // we are only expecting messages of type MonoxideMessage, throw away any other
    DioxideMessage *dioxideMsg = dynamic_cast<DioxideMessage*>(msg);
    if (dioxideMsg == nullptr) {
        error("type");
    }
    if (dioxideMsg->getDestKey() != pub_key){
        error("dest key");
        // wrong destination, try again
        callRoute(dioxideMsg->getDestKey(), dioxideMsg);
        return;
    }
    assert(dioxideMsg->getSenderKey() != pub_key);
    int msgType = dioxideMsg->getType();
    if (msgType == DMSG_BLOCK){
        // this is a chain block header send by other zone
        handle_chain_block_message(dynamic_cast<DChainBlockMessage*>(dioxideMsg));
    } else if (msgType == DMSG_FULL_BLOCK){
        // this is a full chain block send by other full nodes
        handle_full_block_message(dynamic_cast<DFullBlockMessage*>(dioxideMsg));
    } else if (msgType == DMSG_FORWARDED_TX){
        DRelayTransactionMessage *relayTxMsg = dynamic_cast<DRelayTransactionMessage*>(dioxideMsg);
        relayTxMsg->setType(DMSG_RELAY_TX);
        RelayTransaction &relayTx = relayTxMsg->getRelayTransaction();
        assert(relayTx.index != zone_id); // this is a forwarded message
        // 8. FULL_NODEs in target zone receive forwarded RelayTransaction and broadcast in zone.
        for (int id = 0; id < n_validators; ++id){
            int dest_id = id * n_zones + zone_id;
            if (dest_id != pub_key){ // not me
                relayTxMsg->setDestKey(dest_id);
                callRoute(dest_id, relayTxMsg->dup());
            }
        }
        // 9. FULL_NODEs store forwarded RelayTransaction into TransactionPool. (done)
        tx_pool->tx_list.push_back(relayTx);
        delete relayTxMsg;
    } else if (msgType == DMSG_RELAY_TX){
        DRelayTransactionMessage *relayTxMsg = dynamic_cast<DRelayTransactionMessage*>(dioxideMsg);
        RelayTransaction &relayTx = relayTxMsg->getRelayTransaction();
        // 9. FULL_NODEs store forwarded RelayTransaction into TransactionPool. (done)
        tx_pool->tx_list.push_back(relayTx);
        delete relayTxMsg;
    } else {
        delete dioxideMsg;
    }
}


// handleUDPMessage() is called when we receive a message from UDP.
// Unknown packets can be safely deleted here.
void Dioxide::handleUDPMessage(cMessage* msg)
{
    // Message isn't needed any more -> delete it
    delete msg;
}
