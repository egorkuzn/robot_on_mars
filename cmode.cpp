#include "cmode.h"

namespace planet{
    CMode::CMode(size_t& x,
                size_t& y,
                size_t& id,
                data& server) : x(x),
                                y(y),
                                id(id),
                                server(server) {}
    bool CMode::isUnknownArea(){
        return server.isUnknownPoint(x + 1, y) &&
        server.isUnknownPoint(x - 1, y) &&
        server.isUnknownPoint(x, y + 1) &&
        server.isUnknownPoint(x, y - 1);
    }

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
        server.addInAccumulator(id, toDoType::SCAN);
    }

    ManualMode::ManualMode(size_t& x,
                            size_t& y,
                            size_t& id,
                            data& server) 
                                : CMode(x, y, id, server){
        server.send(x, y, id);
        server.setFocus(id);
    }

    void ManualMode::func(){
        return;
    }

    ScanMode::ScanMode(size_t& x,
                      size_t& y,
                      size_t& id,
                      data& server)
                                : CMode(x, y, id, server){
        server.send(x, y, id);
    }

    void ScanMode::func(){
        if(isUnknownArea())
            scan();        
        else
            goInRandWay();        
    }

    AutoMode::AutoMode(size_t& x,
                      size_t& y,
                      size_t& id,
                      data& server)
                                : CMode(x, y, id, server){
        server.send(x, y, id);
    }

    void AutoMode::collectNearestApple(){
        if(!way.capacity())
            way = server.takeNearestWay(id, APPLE);
        server.addInAccumulator(id, toDoType::MOVE, *way.end());
        way.pop_back();
    }

    void AutoMode::func(){
        if(server.isAnyAppleFound(id))
            collectNearestApple();
        else if(isUnknownArea())
            scan();
        else
            goInRandWay();
    }
}