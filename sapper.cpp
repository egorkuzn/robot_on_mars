#include "sapper.h"

namespace planet{
    void Sapper::on(){

    }

    void Sapper::off(){

    }

    void vectorS::cmd(){
        server.readCmd();
        if(server.cmd() == "add"){
            \\добавить робота
        }
        else if(server.cmd() == "canche mode")
            (*this)[server.getNum()].changeMode();
    }

    void vectorS::refresh(){
        for(Sapper & elem : *this)
            elem.refresh();
    }
}