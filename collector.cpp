#include "collector.h"

namespace palnet{
    void vectorC::man(Keys Key){
        (*this)[manId].cmd(Key);        
    }

    void vectorC::cmd(UI& console){
        console.readCmd();
        if(consol.cmd == "auto")
            (*this)[manId].auto(consol);
        else if(consol.cmd == "scan")
            (*this)[manId].scanOn(consol.getNum());
        else if(consol.cmd == "switch")
            manId = consol.getNum();
        else if(consol.cmd == "add")
            this->push_back();
        else 
            consol.outBadCmd();
    }
}