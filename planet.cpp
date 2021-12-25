#include "planet.h"
#define N 1000

namespace planet{
    Planet::Planet() : ground(N, vectorItems(N)),
                       collectors(ground, server),
                       sappers(ground, server){}

    Planet::operator bool(){
        return server && status;
    }

    void Planet::menu(void){
        if(server.Key() == graphics::Keys::U){
            server.readCmd("Input \'collector\' or \'sapper\':");            
            if(server.cmd() == "collector")
                collectors.cmd("");
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

    void Planet::getCommand(void){
        server.getKey();
        if(server.Key() == graphics::Keys::Esc){
            status = false;
            return;
        }
        collectors.man("");
        menu();
        takeRobotsStep();
    }
}