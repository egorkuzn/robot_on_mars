#include "planet.h"

namespace planet{
    bool Planet::menu(Keys Key){
        if(Key == Key::U){
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
        Keys Key = console.getKey();
        if(Key == Keys::Esc)
            return false;
        collectors.man(Key);
        menu(Key);
        takeRobotsStep(surface, console);
        return true;
    }
}