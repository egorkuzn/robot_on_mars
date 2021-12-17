#include "collector.h"

namespace planet{
    void Collector::genCMode(CModeT type){
        switch(type){
            case CModeT::AUTO:
                mode = new ManualMode(x, y, id, idxInCollectors, server);
            case CModeT::MAN:
                mode = new AutoMode(x, y, id, idxInCollectors, server);
            case CModeT::SCAN:
                mode = new ScanMode(x, y, id, idxInCollectors, server);                        
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
        mode -> func();
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
            Collector tmp(ground, server, this->capacity());
            this->push_back(tmp);
        }
        else 
            server.outBadCmd();
    }

    void vectorC::doAction(size_t id, toDoType toDo, Direction where){
        switch (toDo)
        {
        case toDoType::MOVE :
            (*this)[id].move(where);
        case toDoType::GRAB :
            (*this)[id].grab();
        case toDoType::SCAN :
            (*this)[id].scan();
        }
    }

    void vectorC::refresh(){
        for(auto elem : server.collectorsTasks)
            doAction(elem.id, elem.toDo, elem.where);
        server.collectorsTasks.clear();      
        for(Collector & elem : *this)
            elem.refresh();
    }
}