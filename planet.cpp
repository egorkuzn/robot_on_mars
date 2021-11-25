#include "planet.h"

namespace planet{
    bool Planet::menu(Keys Key){
        if(Key == Key::U){
            consol.clear();
            consol.readCmd()
            if(consol.cmd == "collector"){
                consol.readCmd();
                collectors.cmd(consol.cmd(), consol);
            } else if(consol.cmd == "supper"){
                consol.readCmd();
                suppers.cmd(consol.cmd(), consol);
            } else{
                consol.outBadCmd();
                while(Key != Keys::Enter)
                    Key = consol.getKey();
            }
        }
    }

    bool Planet::getCommand(UI& consol = 0){
        Keys Key = consol.getKey();
        takeRobotsStep();
        if(Key == Keys::Esc)
            return false;
        collectors.man(Key);
        menu(Key);
        return true;
    }
}