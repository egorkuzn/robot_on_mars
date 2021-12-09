#include "cmode.h"

namespace planet{
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

    void AutoMode::func(){
        if(isAnyAppleFound())
            collectClosedApple();
        else if(isUnknownArea())
            server.cmdToScanArea(id);
        else
            server.goInRandWay(id);
    }


}