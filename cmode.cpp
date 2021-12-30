#include "cmode.h"

namespace planet{
    CMode::CMode(size_t id,
                size_t idxInCollectors,
                data& server) : id(id),
                                idxInCollectors(idxInCollectors),
                                server(server) {}
    
    bool CMode::isUnknownArea(){
        return server.isUnknownPoint(id, Direction::UP) ||
        server.isUnknownPoint(id, Direction::DOWN) ||
        server.isUnknownPoint(id, Direction::LEFT) ||
        server.isUnknownPoint(id, Direction::RIGHT);
    }

    CMode::~CMode() = default;

    Direction CMode::randWay(){
        Direction where;
        u_char randCount = rand() % 4;
        switch (randCount)
        {
        case 0:
            return Direction::UP;   
        case 1:
            return Direction::DOWN;
        case 2:
            return Direction::LEFT;
        case 3:
            return Direction::RIGHT;
        default:
            return Direction::NONE;     
        }
    }

    void CMode::goInRandWay(){
        Direction where = randWay();
        for(u_char i = 0; i < 4; ++i)
            if(server.availibleToGo(id, where)){
                server.addInAccumulator(id, toDoType::MOVE, where);
                break;
            }
            else
                where = randWay();        
    }

    void CMode::scan(){
        server.addInAccumulator(idxInCollectors, toDoType::SCAN);
    }

    ManualMode::ManualMode(size_t id,
                            size_t idxInCollectors,
                            data& server) 
                                : CMode(id, idxInCollectors ,server){
        server.setFocus(id);
    }

    ManualMode::~ManualMode() = default;

    void ManualMode::func(){
        server.setFocus(id);
    }

    ScanMode::ScanMode(size_t id,
                      size_t idxInCollectors,
                      data& server)
                                : CMode(id, idxInCollectors, server){}

    ScanMode::~ScanMode() = default;

    void ScanMode::func(){
        if(isUnknownArea())
            scan();        
        else
            goInRandWay();    
    }

    AutoMode::AutoMode(size_t id,
                      size_t idxInCollectors,
                      data& server)
                                : CMode(id, idxInCollectors, server){
        way.resize(4);
    }

    AutoMode::~AutoMode() = default;

    void AutoMode::collectNearest(Item item){
        if(!way[item].size())
            way[item] = server.takeNearestWay(id, APPLE);
        if(way[item].size()){  
            server.addInAccumulator(idxInCollectors, toDoType::MOVE, way[item].back());
            way[item].pop_back();
        }
    }

    bool AutoMode::stadingOnApple(){
        return server.updatedMap[server.xyRobots[id].first]
                                [server.xyRobots[id].second] == APPLE;
    }

    void AutoMode::func(){
        if(stadingOnApple())
            server.addInAccumulator(id, toDoType::GRAB);
        if(server.isAnyFound(id, APPLE))
            collectNearest(APPLE);
        else if(server.isAnyFound(id, EMPTY))
            collectNearest(EMPTY);
        else if(isUnknownArea())
            scan();       

        server.mapViewUpdate();     
    }
}