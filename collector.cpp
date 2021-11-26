#include "collector.h"

namespace planet{
    void Collector::genCMode(CModeT type, data& server){
        switch(type){
            case CModeT::AUTO:
                mode = ManualMode(server);
            case CModeT::MAN:
                mode = AutoMode(server);
            case CModeT::SCAN:
                mode = ScanMode(server);                        
        }
    }

    void Collector::cmd(data& server){
        switch(console.Key){
            case Keys::Q:
                break;
            case Keys::W:
                this->move(Direction::UP, server);
                break;
            case Keys::S:
                this->move(Direction::DOWN, server);
                break;
            case Keys::A:
                this->move(Direction::LEFT, server);
                break;
            case Keys::D:
                this->move(Direction::RIGHT, server);
                break;
            case Keys::F:
                this->scan(server);
                break;
            case Keys::E:
                this->grab(server);
                break;
            default:
                break;
        }
    }

    void Collector::refresh(data& server){
        server.send(id, mode.action);
    }

    void vectorC::man(data& server){
        (*this)[manId].cmd(console.Key);        
    }

    void vectorC::cmd(data& server){
        console.readCmd();
        if(consol.cmd == ("auto"))
            (*this)[manId].genCMode(CModeT::AUTO, server);
        if(consol.cmd == ("scan"))
            (*this)[manId].genCMode(CModeT::SCAN, server);
        else if(consol.cmd == "switch"){
            (*this)[manId].genCMode(CModeT::AUTO, server);
            manId = consol.getNum();
            (*this)[manId].genCMode(CModeT::MAN, server);
        }
        else if(consol.cmd == "add")
            this->push_back();
        else 
            consol.outBadCmd();
    }

    void vectorC::refresh(data& server){
        for(Collector & elem : *this)
            elem.func(server);
    }
}