#include "planet.h"

namespace planet{
    bool Planet::menu(void){
        consol.clear();
        consol.readCmd()
        if(consol.cmd == "manual"){
            consol.readNum("robot");
            if(consol.isInRange(robots.size())){
                robots[manual].manualOff;
                manual = consol.num;      
                robots[manual].manualOn; 
            }
            else 
                consol.outNoRobot();     
        } else if (consol.cmd == "scan"){
            consol.readNum("steps");
            robots[manual].scanOn(consol.Num);
        } else if (consol.cmd == "auto"){
            robots[manual].autoOn();
        }
    }

    bool Planet::getCommand(void){
        int Key = consol.getKey();
        takeRobotsStep();
        switch (Key)
        {
        case 'u':
            return robots[manual].moveUp(consol);
        case 's':
            return robots[manual].moveDown(consol);
        case 'a':
            return robots[manual].moveLeft(consol);
        case 'd':
            return robots[manual].moveRight(consol);
        case 'f':
            return robots[manual].scan(consol);
        case 'e':
            return robots[manual].grab(consol);
        case 'q':
            return menu();
        case -1:
            return false;
        default:
            break;
        }
    }
}