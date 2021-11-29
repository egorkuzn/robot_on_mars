#include "planet.h"

namespace planet{
    Planet::Planet(){}

    void Planet::menu(void){
        if(server.Key == Keys::U){
            server.readCmd()
            if(server.cmd == "collector")
                collectors.cmd(ground, server);
            else if(console.cmd == "supper")
                suppers.cmd(ground, server);
            else
                server.outBadCmd();            
        }
    }

    void takeRobotsStep(void){
        collectors.refresh(server);
        suppers.refresh(server);
    }    

    bool Planet::getCommand(void){
        server.getKey();
        if(server.Key() == Keys::Esc)
            return false;
        collectors.man(server);
        menu();
        takeRobotsStep();
        return true;
    }
}