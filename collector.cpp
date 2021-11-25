#include "collector.h"

namespace palnet{
    void Collector::cmd(Keys Key){
        switch(Key){
            case Keys::W
            // сделать для остальных клавиш
        }
    }
    void vectorC::man(Keys Key){
        (*this)[manId].cmd(Key);        
    }

    void vectorC::cmd(UI& console){
        console.readCmd();
        if(consol.cmd == ("auto"))
            (*this)[manId].mode.fill(AUTO, consol);
        if(consol.cmd == ("scan"))
            (*this)[manId].mode.fill(SCAN, consol);
        else if(consol.cmd == "switch"){
            (*this)[manId].mode.fill(AUTO, consol);
            manId = consol.getNum();
            (*this)[manId].mode.fill(MAN, consol);
        }
        else if(consol.cmd == "add")
            this->push_back();
        else 
            consol.outBadCmd();
    }
}