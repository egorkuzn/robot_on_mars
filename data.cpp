#include "data.h"

namespace planet{
    data::data(){
        console = new graphics::UI; 
        //инициализация матрицы
        //инициализация маски      
        console -> importUpdatedMatrix(updatedMap);
        console -> importUpdatedMaskMatrix(updatedMapMask); 
    }

    uint8_t data:: isNotFirst(size_t value, char ort){
        if(xyRobots.size())
            return 1;
        if(ort == 'y')
            baseY = rand() % value;        
        if(ort == 'x')
            baseX = rand() % value;        
        return 0;
    }

    void data::incAppleCount(){
        ++appleCount;
        console -> displayAppleCount(appleCount);
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
        ++liveCount;
        console -> displayRobotCount(liveCount);
        xyRobots.resize(xyRobots.size() + 1);
        isRobotLive.resize(isRobotLive.size() + 1);
        return xyRobots.size() - 1;
    }

    int data::getNum(){
        return console -> getNum();
    }

    void data::readCmd(){
        commandLine = console -> readCmd();
    }

    std::string data::cmd(){
        return commandLine;
    }

    void data::send(size_t x, size_t y, size_t id, robotStatus status = robotStatus::LIVE){
        xyRobots[id][0] = y + yOfFirstLanding();
        xyRobots[id][1] = x + xOfFirstLanding();
        if(status == robotStatus::DIE){
            isRobotLive[id] = false;
            ++dieCount;
            --liveCount;
            console -> displayDieCount(dieCount);
            return;
        }
        if(!updatedMapMask[xyRobots[id][0]][xyRobots[id][1]]){
            updatedMap[xyRobots[id][0]][xyRobots[id][1]] = EMPTY;
            updatedMapMask[xyRobots[id][0]][xyRobots[id][1]] = true;
        }
    }

    void data::send(size_t x, size_t y, Item item){
        updatedMap[y][x] = item;
        updatedMapMask[y][x] = true;
        
    }

    void data::getKey(){
        savedKey = console -> getKey();
    }

    graphics::Keys data::Key(){
        return savedKey;
    }

    void data::error(char* msg){
        console -> error(msg);        
    }

    void data::addInAccumulator(size_t id, toDoType toDo, Direction where = Direction::NONE){
        action* newAction = new action;
        newAction -> toDo = toDo;
        newAction -> id = id;
        newAction -> where = where;
        collectorsTasks.push_back(*newAction);
        delete newAction;
    }

    void data::setFocus(size_t id){
        console->changeCentre(xyRobots[id][1], xyRobots[id][0]);
    }

    bool data::availibleToGo(size_t x, size_t y){
        bool result = updatedMap[y][x] != (ROCK || BOMB);
        result &= updatedMapMask[y][x];
        return result;
    }

    bool data::isUnknownPoint(size_t x, size_t y){
        return !updatedMapMask[y][x];
    }

    bool data::isAnyAppleFound(size_t id){
        //проходимся бфс 
    }
}