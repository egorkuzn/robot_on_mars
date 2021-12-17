#include "planet.h"
#define N 1000

namespace planet{
    Planet::Planet() : ground(N, vectorItems(N)),
                       collectors(ground, server),
                       sappers(ground, server){}

    void Planet::menu(void){
        if(server.Key() == graphics::Keys::U){
            server.readCmd();
            if(server.cmd() == "collector")
                collectors.cmd();
            else if(server.cmd() == "sapper")
                sappers.cmd();
            else
                server.outBadCmd();            
        }
    }

    void Planet::takeRobotsStep(void){
        collectors.refresh();
        sappers.refresh();
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