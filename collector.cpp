#include "collector.h"

namespace planet{
    void Collector::genCMode(CModeT type){
        switch(type){
            case CModeT::AUTO:
                mode = ManualMode(x, y, id, server);
            case CModeT::MAN:
                mode = AutoMode(x, y, id, server);
            case CModeT::SCAN:
                mode = ScanMode(x, y, id, server);                        
        }
    }

    void Collector::grab(){
        if(ground[y][x] == Item::APPLE){
            server.incAppleCount();
            server.send(x, y, Item::EMPTY);
        }
    }

    void Collector::cmd(){
        switch(server.Key()){
            case graphics::Keys::Q:
                break;
            case graphics::Keys::W:
                this->move(Direction::UP);
                break;
            case graphics::Keys::S:
                this->move(Direction::DOWN);
                break;
            case graphics::Keys::A:
                this->move(Direction::LEFT);
                break;
            case graphics::Keys::D:
                this->move(Direction::RIGHT);
                break;
            case graphics::Keys::F:
                this->scan();
                break;
            case graphics::Keys::E:
                this->grab();
                break;
            default:
                break;
        }
    }

    void Collector::refresh(){
        mode.func();
    }

    void vectorC::man(){
        (*this)[manId].cmd();        
    }

    void vectorC::cmd(){
        server.readCmd();
        if(server.cmd() == "auto")
            (*this)[manId].genCMode(CModeT::AUTO);
        else if(server.cmd() == "scan")
            (*this)[manId].genCMode(CModeT::SCAN);
        else if(server.cmd() == "switch"){
            (*this)[manId].genCMode(CModeT::AUTO);
            manId = server.getNum();
            (*this)[manId].genCMode(CModeT::MAN);
        }
        else if(server.cmd() == "add"){            
            Collector tmp(ground, server);
            this->push_back(tmp);
        }
        else 
            server.outBadCmd();
    }

    void vectorC::refresh(){
        for(Collector & elem : *this)
            elem.refresh();
    }
}