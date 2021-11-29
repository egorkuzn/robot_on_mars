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

    void Collector::cmd(surface& ground, data& server){
        switch(console.Key){
            case Keys::Q:
                break;
            case Keys::W:
                this->move(Direction::UP, ground, server);
                break;
            case Keys::S:
                this->move(Direction::DOWN, ground, server);
                break;
            case Keys::A:
                this->move(Direction::LEFT, ground, server);
                break;
            case Keys::D:
                this->move(Direction::RIGHT, ground, server);
                break;
            case Keys::F:
                this->scan(ground, server);
                break;
            case Keys::E:
                this->grab(ground, server);
                break;
            default:
                break;
        }
    }

    void Collector::refresh(data& server){
        server.send(id, mode.action);
    }

    void vectorC::man(){
        (*this)[manId].cmd(ground, console.Key);        
    }

    void vectorC::cmd(){
        server.readCmd();
        if(server.cmd == ("auto"))
            (*this)[manId].genCMode(CModeT::AUTO, server);
        if(server.cmd == ("scan"))
            (*this)[manId].genCMode(CModeT::SCAN, server);
        else if(server.cmd == "switch"){
            (*this)[manId].genCMode(CModeT::AUTO, server);
            manId = server.getNum();
            (*this)[manId].genCMode(CModeT::MAN, server);
        }
        else if(server.cmd == "add")
            this->push_back();
        else 
            server.outBadCmd();
    }

    void vectorC::refresh(){
        for(Collector & elem : *this)
            elem.func(ground, server);
    }
}