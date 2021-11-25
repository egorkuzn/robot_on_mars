#include "collector.h"

namespace palnet{


    void vectorC::man(Keys Key){
        (*this)[manId].cmd(Key);        
    }

    void vectorC::cmd(UI& console){
        console.readCmd();
        if(consol.cmd == ("auto" || "scan"))
            (*this)[manId].changeMode(consol);
        else if(consol.cmd == "switch")
            manId = consol.getNum();
        else if(consol.cmd == "add")
            this->push_back();
        else 
            consol.outBadCmd();
    }
}