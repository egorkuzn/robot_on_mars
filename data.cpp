#include "data.h"

namespace planet{
    data::data(){
        console = new UI;        
    }

    uint8_t data:: isNotFirst(size_t value, char ort){
        if(xyRobots.size())
            return 1;
        if(ort == 'y')
            baseY = xyRobots[0][0];        
        if(ort == 'x')
            baseX = xyRobots[0][1];        
        return 0;
    }

    size_t data::xOfFirstLanding(){
        return baseX;
    }

    size_t data::yOfFirstLanding(){
        return baseY;
    }

    size_t data::getId(){
        if(!xyRobots.size()){
            xyRobots[0][0] = baseY;
            xyRobots[0][1] = baseX;
        }
        xyRobots.resize(xyRobots.size() + 1);
        isRobotLive.resize(isRobotLive.size() + 1);
        return xyRobots.size() - 1;
    }

    int data::getNum(){
        return console.getNum();
    }

    void data::readCmd(){
        commandLine = console.readCmd();
    }

    std::string data::cmd(){
        return commandLine;
    }

    void data::send(size_t x, size_t y, size_t id, robotStatus status = robotStatus::LIVE){
        xyRobots[id][0] = y + yOfFirstLanding();
        xyRobots[id][1] = x + xOfFirstLanding();
        if(status == robotStatus::DIE){
            isRobotLive[id] = false;
            return;
        }
        if(!updatedMapMask[xyRobots[id][0]][xyRobots[id][1]]){
            updatedMap[xyRobots[id][0]][xyRobots[id][1]] = EMPTY;
            updatedMapMask[xyRobots[id][0]][xyRobots[id][1]] = true;
        }
    }

    void data::send(size_t x, size_t y, Item item){
        updatedMap[xyRobots[id][0]][xyRobots[id][1]] = item;
        updatedMapMask[xyRobots[id][0]][xyRobots[id][1]] = true;
    }

    void data::getKey(){
        savedKey = consol.getKey();
    }

    Keys data::Key(){
        return savedKey;
    }

    void data::error(char* msg){
        consol.error(msg);        
    }
}