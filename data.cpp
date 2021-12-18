#include "data.h"

namespace planet{
    data::data() : updatedMap(1, vectorItems(1)),
                updatedMapMask(1, std::vector<bool> (1, false)){
        console = new graphics::UI(xyRobots, updatedMapMask, updatedMap); 
    }

    data::~data(){
        delete console;
    }

    data::operator bool(){
        return // ошибки чекать тыры-пыры
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
            xyRobots[0].first = baseY;
            xyRobots[0].second = baseX;
        }
        ++liveCount;
        console -> displayRobotCount(liveCount);
        xyRobots.push_back({0, 0});
        isRobotLive.push_back(true);
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

    void data::send(size_t x, size_t y, size_t id, robotStatus status){
        xyRobots[id].first = y + yOfFirstLanding();
        xyRobots[id].second = x + xOfFirstLanding();
        if(status == robotStatus::DIE){
            isRobotLive[id] = false;
            ++dieCount;
            --liveCount;
            console -> displayDieCount(dieCount);
            return;
        }

        if(!updatedMapMask[xyRobots[id].first][xyRobots[id].second])
                    send(x, y, EMPTY);
        
    }

    void data::send(size_t x, size_t y, Item item){
        if(y > updatedMap.capacity()){
            vectorItems itemsTmp(updatedMap[0].capacity());
            updatedMap.push_back(itemsTmp);
            updatedMap[y][updatedMap[0].capacity() - 1];
            std::vector<bool> boolTmp(updatedMap[0].capacity(), false);
            updatedMapMask.push_back(boolTmp);
        }

        if(x > updatedMapMask[0].capacity()){
            for(auto& elem : updatedMap)
                elem[x];
            for(auto& elem: updatedMapMask)
                elem.resize(x + 1, false);
        }

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

    void data::addInAccumulator(size_t id, toDoType toDo, Direction where){
        action* newAction = new action;
        newAction -> toDo = toDo;
        newAction -> id = id;
        newAction -> where = where;
        collectorsTasks.push_back(*newAction);
        delete newAction;
    }

    void data::setFocus(size_t id){
        console->changeCentre(xyRobots[id].second, xyRobots[id].first);
    }

    bool data::availibleToGo(size_t x, size_t y){
        bool result = updatedMap[y][x] != (ROCK || BOMB);
        result &= updatedMapMask[y][x];
        return result;
    }

    bool data::isUnknownPoint(size_t x, size_t y){
        return !updatedMapMask[y][x];
    }

    size_t data::point(std::pair<size_t, size_t> coordinate){
        return coordinate.first * updatedMap[0].capacity() + coordinate.second;
    }

    size_t data::point(size_t x, size_t y){
        return y * updatedMap[0].capacity() + x;
    }

    std::list<size_t> data::genPointsQueue(size_t x, size_t y){
        std::list<size_t> q;
        if(updatedMapMask[y + 1][x] && (updatedMap[y + 1][x] != (BOMB||ROCK)))
            q.push_back(point(y + 1, x));        

        if(updatedMapMask[y - 1][x] && (updatedMap[y - 1][x] != (BOMB||ROCK)))
            q.push_back(point(y - 1, x));        

        if(updatedMapMask[y][x + 1] && (updatedMap[y][x + 1] != (BOMB||ROCK)))
            q.push_back(point(y, x + 1));        

        if(updatedMapMask[y][x - 1] && (updatedMap[y][x - 1] != (BOMB||ROCK)))
            q.push_back(point(y, x - 1));        

        return q;
    }

    Item data::takeItem(size_t coordinate){
        size_t k = updatedMap[0].capacity();
        return updatedMap[coordinate / k][coordinate % k];
    }

    bool data::foundInDistribution(size_t coordinate, Item item){
        if(!distribution.size())
            distribution.resize(4);
        for(size_t elem : distribution[item])
            if(coordinate == elem)
                return true;
        distribution[item].push_back(coordinate);
        return false;
    }

    bool data::isAppleForGrab(size_t coordinate, Item item){
        if(takeItem(coordinate) == item)
            if(!foundInDistribution(coordinate, item))
                return true;
        return false;
    }

    size_t data::extractX(size_t coordinate){
        return coordinate % updatedMap[0].capacity();
    }

    size_t data::extractY(size_t coordinate){
        return coordinate / updatedMap[0].capacity();
    }

    Direction data::toDirectionType(size_t coordinate0, size_t coordinate){
        if(coordinate > coordinate0){
            if(coordinate - coordinate0 == 1)
                return Direction::RIGHT;
            else
                return Direction::UP;
        } else if (coordinate < coordinate0){
            if(coordinate0 - coordinate == 1)
                return Direction::LEFT;
            else
                return Direction::DOWN;
        } else
            return Direction::NONE;
    }

    std::vector<Direction> data::matrixBFS(size_t id, Item item){
        std::queue<size_t> q;
        size_t __capacity = updatedMap.capacity() * updatedMap[0].capacity();
        std::vector<bool> used(__capacity);
        std::vector<size_t> destination(__capacity), parents(__capacity);
        size_t itemPoint;
        bool found = false;
        used[point(xyRobots[id])] = true;
        q.push(point(xyRobots[id]));
        //        
        while (!found && !q.empty()){
            size_t vertice = q.front();
            q.pop();
            std::list<size_t> pointsQueue = genPointsQueue(extractX(vertice), extractY(vertice));

            for(size_t pointIterator : pointsQueue){
                size_t to = pointIterator;

                if(!used[to]){
                    used[to] = true;
                    q.push(to);
                    destination[to] = destination[vertice] + 1;
                    parents[to] = vertice;
                }  

                found = isAppleForGrab(to, APPLE);

                if(found)
                    itemPoint = to;
            }
        }   

        std::vector<Direction> path; // output path to item

        if (!used[itemPoint])
            return path;// nothing
        else {
            //cycling while no come back to the start
            for (size_t vertice = itemPoint; vertice != point(xyRobots[id]); vertice = parents[vertice])
                path.push_back (toDirectionType(parents[vertice], vertice));
            return path;
        }
    }

    bool data::isAnyFound(size_t id, Item item){
        if(!ways[id][item].capacity())
            ways[id][item] = matrixBFS(id, item);             
        
        if(!ways[id][item].capacity())
            return true;
        else 
            return false;
    }

    std::vector<Direction> data::takeNearestWay(size_t id, Item item){
        return ways[id][item];
    }

    void data::outBadCmd(){
        console->error("Bad command was inputed");
    }
}