#include "collector.h"

namespace planet{
    void Collector::cmd(UI& console){
        switch(console.Key){
            case Keys::Q:
                break;
            case Keys::W:
                this->move(Direction::UP, console);
                break;
            case Keys::S:
                this->move(Direction::DOWN, console);
                break;
            case Keys::A:
                this->move(Direction::LEFT, console);
                break;
            case Keys::D:
                this->move(Direction::RIGHT, console);
                break;
            case Keys::F:
                this->scan();
                break;
            case Keys::E:
                this->grab();
                break;
            default
        }
    }
    void vectorC::man(UI& console){
        (*this)[manId].cmd(console.Key);        
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