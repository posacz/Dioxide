/*
 * Dioxide.h
 *
 * This application simulated workflow of Dioxide without epoch.
 * *. FULL_NODEs init with initial Transaction, no inbound RelayTransaction at bootstrap (jump 1)
 * 0. FULL_NODEs gather Transaction from clients and inbound RelayTransaction from other FULL_NODEs. (running as a daemon)
 * 1. FULL_NODEs generate new TransactionBlock with Transaction and confirmed inbound RelayTransaction.
 *     To avoid to invalidate transactions when originate block becomes orphan.
 *     We slightly changed Fork Resolution strategy by only allow RelayTransaction to be packed when its originate block is considered confirmed, i.e. with 6 blocks followed.
 *     This is reasonable because it is rare for a confirmed block becomes orphan later and it is useless and confusing to invalidate a confirmed transaction.
 *     But it is possible for a available/unsolved block becomes orphan as 0.83% orphan rate shown in experiment.
 *     The outbound transactions are generated from Transactions.
 * 2. FULL_NODEs select validator randomly, current validators create and sign FullBlock and broadcast in zone.
 *    Then send ChainBlock to other zones. (jump 5)
 * FULL_NODE(validator) ===FullBlock===> FULL_NODE(not validator) (jump 3)
 * FULL_NODE(validator) ===ChainBlock===> FULL_NODE(other zone) (jump 4)
 * 3. FULL_NODEs(not validator) receive and store FullBlock, update tx pool. (done)
 * 4. FULL_NODEs(other zone) receive ChainBlock and store ChainBlock into Blockchain, then broadcast in zone. (done)
 * 5. FULL_NODEs(validators) get outbound Transactions from TransactionBlock.
 * 6. FULL_NODEs(validators) generate forwarded RelayTransaction from outbound Transactions.
 * 7. FULL_NODEs(validators) send forwarded RelayTransaction to target zone.
 * FULL_NODE(validator) ===RelayTransaction===> FULL_NODE
 * 8. FULL_NODEs in target zone receive forwarded RelayTransaction and broadcast in zone.
 * FULL_NODE ===RelayTransaction(broadcast)===> FULL_NODE
 * 9. FULL_NODEs store forwarded RelayTransaction into TransactionPool. (done)
 *
 *  Created on: Oct 30, 2020
 *      Author: qucheng
 */

#ifndef APPLICATIONS_DIOXIDE_DIOXIDE_H_
#define APPLICATIONS_DIOXIDE_DIOXIDE_H_

#include "common/OverSimDefs.h"

#include "common/BaseApp.h"

#include "Dioxide_m.h"
#include "Blockchain.h"

#include <random>

#define DEBUG_BREAK {int a=0;a=a+1;if(a==1){a=1;}}
#define DEBUG_DIOXIDE
//#define CROSS_ZONE_TRANSACTIONS

class ValidatorSelector
{
public:
    int n_zones, n_validators;
    int zone_id;
    unsigned seed;
    uint64_t last_time_slot;
    int last_validator;
    std::minstd_rand0 prg;
    std::uniform_int_distribution<int> val_dist;

    inline int get_validator(uint64_t time_slot){
        assert(last_time_slot <= time_slot);
        if (last_time_slot == time_slot){
            return last_validator;
        }
        for (;last_time_slot<time_slot;++last_time_slot){
            last_validator = val_dist(prg);
        }
        return last_validator;
    }

    inline void init(int n_zones, int zone_id, int n_validators, unsigned rand){
        this->n_zones = n_zones;
        this->n_validators = n_validators;
        this->zone_id = zone_id;
        this->seed = rand + zone_id;
        this->last_time_slot = 0;
        this->prg = std::minstd_rand0(this->seed);
        this->val_dist = std::uniform_int_distribution<int>(0, n_validators-1);
    }
};

class Dioxide : public BaseApp
{
    // shared global parameters
    static int global_index; // for fast assign node id
    static uint64_t global_tx_id; // for fast assign tx hash
    static uint64_t global_header_id; // for fast assign chain block hash
    static MainBlock global_main_block; // store all shared info
    static simtime_t init_time; // when this protocol is ready

    uint64_t next_hash(uint64_t &h);

#ifdef DEBUG_DIOXIDE
    // only for debug,
    static std::list<ChainBlock> debug_all_headers;
    static std::list<Blockchain*> debug_all_blockchains;
#endif

    // module parameters
    int sharding_scale; // how many zones, numbers of zones is (1<<sharding_scale)
    int n_validators; // how many validators total
    int n_full_nodes; // how many full nodes in each zone of one coordinator, must be 1

    // the time slot
    int time_slot; //ms
    // only for simulation, the full block size
    int block_size; //kB
    int transaction_size; //B
    unsigned int tx_per_block;

    // derived parameters
    int n_zones;

    // node parameters
    int pub_key, srt_key; // the global id of this node
    int validator_id; // the validator id
    int full_node_id_base; // base index of full node
    int zone_id; // the zone id

    // the block chain structure (for simulation, while not store all block)
    Blockchain *blockchain = nullptr;

    TransactionBlock *tx_block; // for storing transactions
    TransactionPool *tx_pool; // for storing inbound relay transactions

    uint64_t time_slot_id;
    ValidatorSelector vs; // for select validator in each time slot

    void send_chain_block();
    void fill_transaction_block();
    void init_dioxide_message(DioxideMessage *msg, int type, int byte_length);

    // statistics
    int numSent;              //number of packets sent
    int numReceived;          //number of packets received

    // our timer
    cMessage *timerMsg = nullptr, *initMsg = nullptr;

    // message handlers
    void handle_chain_block_message(DChainBlockMessage *msg);
    void handle_full_block_message(DFullBlockMessage *msg);

    // application routines
    void initializeApp(int stage);                 // called when the module is being created
    void finishApp();                              // called when the module is about to be destroyed
    void handleTimerEvent(cMessage* msg);          // called when we received a timer message
    void deliver(OverlayKey& key, cMessage* msg);  // called when we receive a message from the overlay
    void handleUDPMessage(cMessage* msg);          // called when we receive a UDP message

public:
    Dioxide() { timerMsg = nullptr; };
    ~Dioxide() { cancelAndDelete(timerMsg); delete[] blockchain;};
};

#endif /* APPLICATIONS_DIOXIDE_DIOXIDE_H_ */
