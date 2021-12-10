#include "sapper.h"

namespace planet{
    void Sapper::work(){
        if(!way.capacity())
            way = server.takeNearestWay(id, BOMB);
        move(*way.end());
        way.pop_back();
    }
    void Sapper::on(){
        isOn = true;
    }

    void Sapper::off(){
        isOn = false;
    }

    void Sapper::func(){
        if(isOn)
            work();
    }

    void Sapper::changeMode(){
        isOn = !isOn; 
    }

    void vectorS::cmd(){
        server.readCmd();
        if(server.cmd() == "add"){
            Sapper tmp;
            (*this).push_back(tmp); 
        }
        else if(server.cmd() == "change mode")
            (*this)[server.getNum()].changeMode();
    }

    void vectorS::refresh(){
        for(Sapper & elem : *this)
            elem.refresh();
    }
}