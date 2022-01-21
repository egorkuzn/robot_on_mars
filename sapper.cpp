#include "sapper.h"

namespace planet{
    Sapper::Sapper(std::vector<vectorItems>& ground,
                                planet::data& server): Robot(ground, server){}
    
    Direction Sapper::randWay(){
        Direction where;
        u_char randCount = rand() % 4;
        switch (randCount)
        {
        case 0:
            return Direction::UP;   
        case 1:
            return Direction::DOWN;
        case 2:
            return Direction::LEFT;
        case 3:
            return Direction::RIGHT;
        default:
            return Direction::NONE;     
        }
    }

    void Sapper::goInRandWay(){
        Direction where = randWay();
        for(u_char i = 0; i < 4; ++i)
            if(server.availibleToGo(id, where, true)){
                move(where);
                break;
            }
            else
                where = randWay();        
    }

    void Sapper::work(){            
        goInRandWay();
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