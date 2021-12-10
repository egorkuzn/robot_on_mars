#include "planet.h"

namespace planet{
    Planet::Planet(){}

    void Planet::menu(void){
        if(server.Key() == graphics::Keys::U){
            server.readCmd();
            if(server.cmd() == "collector")
                collectors.cmd();
            else if(console.cmd() == "sapper")
                suppers.cmd();
            else
                server.outBadCmd();            
        }
    }

    void Planet::takeRobotsStep(void){
        collectors.refresh();
        suppers.refresh();
    }    

    bool Planet::getCommand(void){
        server.getKey();
        if(server.Key() == graphics::Keys::Esc)
            return false;
        collectors.man();
        menu();
        takeRobotsStep();
        return true;
    }
}