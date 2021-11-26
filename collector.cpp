#include "collector.h"

namespace planet{
    void Collector::cmd(UI& console, data& server){
        switch(console.Key){
            case Keys::Q:
                break;
            case Keys::W:
                this->move(Direction::UP, console, server);
                break;
            case Keys::S:
                this->move(Direction::DOWN, console, server);
                break;
            case Keys::A:
                this->move(Direction::LEFT, console, server);
                break;
            case Keys::D:
                this->move(Direction::RIGHT, console, server);
                break;
            case Keys::F:
                this->scan(console, server);
                break;
            case Keys::E:
                this->grab(console, server);
                break;
            default:
            break;
        }
    }

    void Collector::refresh(UI& console, data& server){
        server.send(id, mode.action);
    }

    void vectorC::man(UI& console, data& server){
        (*this)[manId].cmd(console.Key);        
    }

    void vectorC::cmd(UI& console, data& server){
        console.readCmd();
        if(consol.cmd == ("auto"))
            (*this)[manId].mode.fill(AUTO, consol, server);
        if(consol.cmd == ("scan"))
            (*this)[manId].mode.fill(SCAN, consol, server);
        else if(consol.cmd == "switch"){
            (*this)[manId].mode.fill(AUTO, consol, server);
            manId = consol.getNum();
            (*this)[manId].mode.fill(MAN, consol, server);
        }
        else if(consol.cmd == "add")
            this->push_back();
        else 
            consol.outBadCmd();
    }

    void vectorC::refresh(UI& console, data& server){
        for(Collector & elem : *this)
            elem.refresh(console, server);
    }
}