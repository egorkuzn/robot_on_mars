#include "collector.h"

namespace planet{
    Collector::Collector(std::vector<vectorItems>& ground, data& server, size_t idx):
                            Robot(ground, server), idxInCollectors(idx){
    }

    Collector::~Collector(){
        // some times deletes, when it's already deleted
        delete mode;
    }

    void Collector::genCMode(CModeT type){
        if(!mode)
            delete mode;
        switch(type){
            case CModeT::AUTO:  
                modeStatus = CModeT::AUTO;         
                mode = new AutoMode(id, idxInCollectors, server);
                break;
            case CModeT::MAN:
                modeStatus = CModeT::MAN;
                mode = new ManualMode(id, idxInCollectors, server);
                break;
            case CModeT::SCAN:
                modeStatus = CModeT::SCAN;
                mode = new ScanMode(id, idxInCollectors, server);        
                break;                
        }
    }

    void Collector::grab(){
        if(ground[yGround][xGround] == Item::APPLE){
            server.incAppleCount();
            server.send(xServer, yServer, Item::EMPTY);
        }
    }

    void Collector::cmd(char* context){
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

    void vectorC::man(char* context){
        if(serverId.size())
            if(server.isRobotLive[serverId[manId]])
                (*this)[manId].cmd(context);  
            else
                serverId.erase(manId);
            
    }

    void vectorC::add(){
        manId = this -> size();
        this->push_back(Collector(ground, server, this -> size()));                
        this->back().genCMode(CModeT::MAN);
        serverId.insert({manId, this->back().id});        
    }

    bool vectorC::vectorCheck(){
        if(!serverId.contains(manId)){
            if(!serverId.size()){
               if(server.cmd() == "add")
                    add();
            } else
                manId = serverId.begin()->first;
            return false;
        }
        
        return true;
    }

    void vectorC::cmd(char* context){
        server.readCmd(context);

        if(!vectorCheck())
            return;

        if(server.cmd() == "auto")
            (*this)[manId].genCMode(CModeT::AUTO);
        else if(server.cmd() == "scan")
            (*this)[manId].genCMode(CModeT::SCAN);
        else if(server.cmd() == "switch"){
            (*this)[manId].genCMode(CModeT::AUTO);
            manId = server.getNum();
            (*this)[manId].genCMode(CModeT::MAN);
        }
        else if(server.cmd() == "add")
            add();
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
        for(size_t i = 0; i < this -> size(); ++i)
            if(serverId.contains(i))
                (*this)[i].refresh();
    }
}