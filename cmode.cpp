#include "cmode.h"

namespace planet{
    CMode::CMode(size_t id,
                size_t idxInCollectors,
                data& server) : id(id),
                                idxInCollectors(idxInCollectors),
                                server(server) {}
    
    bool CMode::isUnknownArea(){
        return server.isUnknownPoint(id, Direction::UP) &&
        server.isUnknownPoint(id, Direction::DOWN) &&
        server.isUnknownPoint(id, Direction::LEFT) &&
        server.isUnknownPoint(id, Direction::RIGHT);
    }

    CMode::~CMode() = default;

    void CMode::goInRandWay(){
        if(server.availibleToGo(id, Direction::RIGHT))
            server.addInAccumulator(id, toDoType::MOVE, Direction::RIGHT);
        else if(server.availibleToGo(id, Direction::UP))
            server.addInAccumulator(id, toDoType::MOVE, Direction::UP);
        else if(server.availibleToGo(id, Direction::LEFT))
            server.addInAccumulator(id, toDoType::MOVE, Direction::LEFT);
        else if(server.availibleToGo(id, Direction::DOWN))
            server.addInAccumulator(id, toDoType::MOVE, Direction::DOWN);
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
                                : CMode(id, idxInCollectors, server){}

    AutoMode::~AutoMode() = default;

    void AutoMode::collectNearestApple(){
        if(!way.capacity())
            way = server.takeNearestWay(id, APPLE);
        server.addInAccumulator(idxInCollectors, toDoType::MOVE, *way.end());
        way.pop_back();
    }

    void AutoMode::func(){
        if(server.isAnyFound(id, APPLE))
            collectNearestApple();
        else if(isUnknownArea())
            scan();
        else
            goInRandWay();
    }
}