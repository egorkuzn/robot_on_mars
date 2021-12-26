#include "planet.h"
#define N 1000

namespace planet{
    Planet::Planet() : ground(N, vectorItems(N)),
                       server(N, N),
                       collectors(ground, server),
                       sappers(ground, server){}

    Planet::operator bool(){
        return server && status;
    }

    void Planet::menu(void){
        if(server.Key() == graphics::Keys::U){
            server.readCmd("Input \'collector\' or \'sapper\'");            
            if(server.cmd() == "collector")
                collectors.cmd("\'auto\'|\'scan\'|\'switch\'|\'add\'");
            else if(server.cmd() == "sapper")
                sappers.cmd("\'add\'|\'change mode\'");
            else{
                server.outBadCmd();  
                status = false;
            }          
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