#include "cmode.h"

namespace planet{
    CMode::CMode(size_t& x,
                size_t& y,
                size_t& id,
                size_t& idxInCollectors,
                data& server) : x(x),
                                y(y),
                                id(id),
                                idxInCollectors(idxInCollectors),
                                server(server) {}
    bool CMode::isUnknownArea(){
        return server.isUnknownPoint(x + 1, y) &&
        server.isUnknownPoint(x - 1, y) &&
        server.isUnknownPoint(x, y + 1) &&
        server.isUnknownPoint(x, y - 1);
    }

    CMode::~CMode(){}

    void CMode::goInRandWay(){
        if(server.availibleToGo(x + 1, y))
            server.addInAccumulator(id, toDoType::MOVE, Direction::RIGHT);
        else if(server.availibleToGo(x, y + 1))
            server.addInAccumulator(id, toDoType::MOVE, Direction::UP);
        else if(server.availibleToGo(x - 1, y))
            server.addInAccumulator(id, toDoType::MOVE, Direction::LEFT);
        else if(server.availibleToGo(x, y - 1))
            server.addInAccumulator(id, toDoType::MOVE, Direction::DOWN);
    }

    void CMode::scan(){
        server.addInAccumulator(idxInCollectors, toDoType::SCAN);
    }

    ManualMode::ManualMode(size_t& x,
                            size_t& y,
                            size_t& id,
                            size_t& idxInCollectors,
                            data& server) 
                                : CMode(x, y, id, idxInCollectors ,server){
        server.send(x, y, id);
        server.setFocus(id);
    }

    ManualMode::~ManualMode(){}

    void ManualMode::func(){
        return;
    }

    ScanMode::ScanMode(size_t& x,
                      size_t& y,
                      size_t& id,
                      size_t& idxInCollectors,
                      data& server)
                                : CMode(x, y, id, idxInCollectors, server){
        server.send(x, y, id);
    }

    ScanMode::~ScanMode(){}

    void ScanMode::func(){
        if(isUnknownArea())
            scan();        
        else
            goInRandWay();        
    }

    AutoMode::AutoMode(size_t& x,
                      size_t& y,
                      size_t& id,
                      size_t& idxInCollectors,
                      data& server)
                                : CMode(x, y, id, idxInCollectors, server){
        server.send(x, y, id);
    }

    AutoMode::~AutoMode(){}

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