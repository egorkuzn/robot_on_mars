#include "collector.h"

namespace palnet{
    void vectorC::man(Keys Key){
        (*this)[manId].cmd(Key);        
    }

    void vectorC::cmd(UI& console){
        console
    }
}