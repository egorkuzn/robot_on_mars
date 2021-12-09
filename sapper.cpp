#include "sapper.h"

namespace planet{
    void Sapper::work(){
        
    }
    void Sapper::on(){

    }

    void Sapper::off(){

    }

    void Sapper::func(){
        if(isOn)
            work();
    }

    void vectorS::cmd(){
        server.readCmd();
        if(server.cmd() == "add"){
            Sapper tmp;
            (*this).push_back(tmp); 
        }
        else if(server.cmd() == "canche mode")
            (*this)[server.getNum()].changeMode();
    }

    void vectorS::refresh(){
        for(Sapper & elem : *this)
            elem.refresh();
    }
}