#include "planet.h"

namespace planet{
    bool Planet::menu(Keys Key){
        if(Key == Key::U){
            console.clear();
            console.readCmd()
            if(console.cmd == "collector")
                collectors.cmd(console);
            else if(console.cmd == "supper")
                suppers.cmd(console);
            else
                console.outBadCmd();            
        }
    }

    bool Planet::getCommand(UI& console = 0){
        Keys Key = console.getKey();
        takeRobotsStep(surface, console);
        if(Key == Keys::Esc)
            return false;
        collectors.man(Key);
        menu(Key);
        return true;
    }
}