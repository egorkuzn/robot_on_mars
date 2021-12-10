#include "cmode.h"

namespace planet{
    bool CMode::isUnknownArea(){

    }

    void CMode::goInRandWay(){

    }

    void CMode::scan(){

    }

    void CMode::cmdToScanArea(){
        
    }

    ManualMode::ManualMode(size_t& x,
                            size_t& y,
                            size_t& id,
                            data& server){
        server.setFocus(id);
        func();
    }

    void ManualMode::func(){
        return;
    }

    ScanMode::ScanMode(size_t& x,
                      size_t& y,
                      size_t& id,
                      data& server){
        server.send(x, y, id);
        func();
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
                      data& server){


    }

    void AutoMode::collectNearestApple(){
        if(!way.capacity())
            way = server.takeNearestWay(id, BOMB);
        server.addInAccumulator(id, move, *way.end());
        way.pop_back();
    }

    void AutoMode::func(){
        if(isAnyAppleFound())
            collectNearestApple();
        else if(isUnknownArea())
            cmdToScanArea();
        else
            goInRandWay();
    }


}