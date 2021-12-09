#include "cmode.h"

namespace planet{
    ManualMode::ManualMode(data& server){
        server.setFocus(id);
        func(server);
    }

    void ManualMode::func(data& server){
        return;
    }

    ScanMode::ScanMode(data& server){
        server.send(x, y, id);
        func(server);
    }

    void ScanMode::func(data& server){
        if(isUnknownArea())
            scan();        
        else
            goInRandWay();        
    }

    AutoMode::AutoMode(data& server){
        if(isAnyAppleFound())
            collectClosedApple();
        else if(isUnknownArea())
            scan();
        else
            goInRandWay();
    }
}