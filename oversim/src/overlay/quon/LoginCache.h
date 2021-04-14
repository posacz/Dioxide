
#ifndef LOGINCACHE_H
#define LOGINCACHE_H

#include "common/OverSimDefs.h"
#include "common/NodeHandle.h"
#include "common/Vector2D.h"
#include "common/GlobalStatisticsAccess.h"

class lcEntry {
    public:
        lcEntry() {}
        lcEntry(Vector2D p, simtime_t t) : pos(p), time(t) {}
        Vector2D pos;
        simtime_t time;
};

class LoginCache : public cSimpleModule
{
    public:
        void initialize() override;
        void finish() override;
        NodeHandle getLoginNode( Vector2D pos );
        void registerPos( NodeHandle node, Vector2D pos );

    private:
        std::map<NodeHandle,lcEntry> nodelist;
        double movementSpeed;
        int bytessend;
        int bytesrecv;
        GlobalStatistics* globalStatistics;

};

#endif
