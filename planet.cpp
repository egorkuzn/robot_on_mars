#include "planet.h"

namespace planet{
    Planet::Planet():{
    }

    void Planet::menu(data& server){
        if(server.console.Key == Keys::U){
            server.console.readCmd()
            if(console.cmd == "collector")
                collectors.cmd(server);
            else if(console.cmd == "supper")
                suppers.cmd(server);
            else
                server.console.outBadCmd();            
        }
    }

    void takeRobotsStep(void){
        collectors.refresh(server);
        suppers.refresh(server);
        server.refresh();
    }    

    bool Planet::getCommand(void){
        server.console.getKey();
        if(server.console.Key == Keys::Esc)
            return false;
        collectors.man(server);
        menu(server);
        takeRobotsStep(server);
        return true;
    }
}