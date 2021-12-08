#include "cmode.h"

namespace planet{
    ManualMode::ManualMode(data& server){
        server.setFocus(id);
        func(server);
    }

    void ManualMode::func(data& server){
        return;
    }

}