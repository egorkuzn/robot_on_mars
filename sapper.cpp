#include "sapper.h"

namespace planet{
    Sapper::Sapper(std::vector<vectorItems>& ground,
                                planet::data& server): Robot(ground, server){}

    void Sapper::work(){
        if(!way.capacity()){ 
            server.isAnyFound(id, BOMB);           
            way = server.takeNearestWay(id, BOMB);
        }

        if(way.capacity()){
            move(way.back());
            way.pop_back();
            if(ground[yGround][xGround] == BOMB)
                ground[yGround][xGround] = EMPTY;
        }
    }

    void Sapper::on(){
        isOn = true;
    }

    void Sapper::off(){
        isOn = false;
    }

    void Sapper::func(){
        if(server.isRobotLive[id] && isOn)
            work();
    }

    void Sapper::changeMode(){
        isOn = !isOn; 
    }

    void vectorS::cmd(char* context){
        server.readCmd(context);
        if(server.cmd() == "add"){
            this->push_back(Sapper(ground, server));
        }
        else if(server.cmd() == "change mode")
            (*this)[server.getNum()].changeMode();
    }

    void vectorS::refresh(){
        for(Sapper & elem : *this)
            elem.func();
    }
}