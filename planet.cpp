#include "planet.h"

namespace planet{
    void Planet::menu(UI& console){
        if(console.Key == Keys::U){
            console.readCmd()
            if(console.cmd == "collector")
                collectors.cmd(console);
            else if(console.cmd == "supper")
                suppers.cmd(console);
            else
                console.outBadCmd();            
        }
    }

    void takeRobotsStep(void){
        collectors.refresh(consol);
        suppers.refresh(consol);
    }    

    bool Planet::getCommand(UI& console = 0){
        console.getKey();
        if(console.Key == Keys::Esc)
            return false;
        collectors.man(console);
        menu(console);
        takeRobotsStep(surface, console);
        return true;
    }
}