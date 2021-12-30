#include "collector.h"

namespace planet{
    Collector::Collector(std::vector<vectorItems>& ground, data& server, size_t idx):
                            Robot(ground, server), idxInCollectors(idx){
    }

    Collector::~Collector() = default;

    void vectorC::updateServerId(){
        for(size_t i = 0; i < serverId.size(); ++i)
            if(!server.isRobotLive[serverId[i].serverId])
                serverId[i].isLive = false;
    }

    void Collector::dieIfBomb(){
        if(ground[yGround][xGround] == BOMB)
            server.send(xServer, yServer, id, robotStatus::DIE);
    }

    void Collector::scan(){   
        server.send(xServer + 1, yServer, ground[Y(yGround)][X(xGround + 1)]);
        server.send(xServer - 1, yServer, ground[Y(yGround)][X(xGround - 1)]);
        server.send(xServer, yServer + 1, ground[Y(yGround + 1)][X(xGround)]);
        server.send(xServer, yServer - 1, ground[Y(yGround - 1)][X(xGround)]);
    }

    void Collector::genCMode(CModeT type){
        if(mode){
            delete mode;
            mode = nullptr;
        }
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
            ground[yGround][xGround] = Item::EMPTY;
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
        dieIfBomb();
    }

    void Collector::refresh(){
        mode -> func();
        dieIfBomb();
    }

    void vectorC::man(char* context){
        if(serverId.size() && serverId[manId].isLive){
            (*this)[manId].cmd(context); 
            (*this)[manId].dieIfBomb();
        } 
    }

    void vectorC::add(){
        if(this -> size())
            (*this)[manId].genCMode(CModeT::AUTO);
        manId = this -> size();
        this->push_back(Collector(ground, server, this -> size()));                
        this->back().genCMode(CModeT::MAN);
        serverId.push_back({this->back().id, true}); 
        this->back().dieIfBomb();
    }

    size_t vectorC::firstLive(){
        for(size_t i = 0; i < serverId.size(); ++i)
            if(serverId[i].isLive)
                return i;
        return 0;
    }

    bool vectorC::vectorCheck(){
        if(serverId.size() == 0){
            if(server.cmd() == "add")
                add();
            return false;
        }
        
        if(!serverId[manId].isLive){
            if(server.cmd() == "add")
                add();
            else 
                manId = firstLive();
            return false;
        }

        return true;
    }

    void vectorC::cmd(char* context){
        updateServerId();

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
    }

    void vectorC::takeIndexFromId(size_t& id){
        for(size_t i = 0; i < serverId.size(); ++i)
            if(serverId[i].serverId == id){
                id = i;        
                break;
            }
    }

    void vectorC::doAction(size_t id, toDoType toDo, Direction where){
        takeIndexFromId(id);
        switch (toDo)
        {
        case toDoType::MOVE :
            (*this)[id].move(where);
            break;
        case toDoType::GRAB :
            (*this)[id].grab();
            break;
        case toDoType::SCAN :
            (*this)[id].scan();
            break;
        }
        (*this)[id].dieIfBomb();
    }

    void vectorC::refresh(){
        for(auto elem : server.collectorsTasks)
            doAction(elem.id, elem.toDo, elem.where);
        server.collectorsTasks.clear();  
        updateServerId();    
        for(size_t i = 0; i < this -> size(); ++i)
            if(serverId[i].isLive)
                (*this)[i].refresh();
    }
}