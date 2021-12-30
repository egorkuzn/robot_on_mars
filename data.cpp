#include "data.h"

namespace planet{    
    void data::resizeMaps(size_t y, size_t x){
        while (!(updatedMap.size() > y)){
            vectorItems itemsTmp(updatedMap[0].capacity());
            updatedMap.push_back(itemsTmp);
            std::vector<bool> boolTmp(updatedMap[0].capacity(), false);
            updatedMapMask.push_back(boolTmp);
        }

        while(!(updatedMapMask[0].size() > x)){
            for(auto& elem : updatedMap)
                elem[x];            

            for(auto& elem: updatedMapMask)             
                elem.push_back(false);
            
        }
    }


    data::data(size_t x, size_t y) : updatedMap(2, vectorItems(2)),
                updatedMapMask(2, std::vector<bool> (2, false)),
                console (graphics::UI(xyRobots, updatedMapMask, updatedMap, x, y)) 
    {
        isFirst = true;
        xLimit = x;
        yLimit = y;
        resizeMaps(yLimit, xLimit);
    }

    data::~data(){
    }

    void data::mapViewUpdate(){
        if(necessary){
            console.mapUpdate(xyRobots, updatedMapMask, updatedMap);
            necessary = false;
        }

    }

    size_t data::Y(size_t y){
        return (y + yLimit) % yLimit;
    }

    size_t data::X(size_t x){
        return (x + xLimit) % xLimit;
    }

    data::operator bool(){
        return console && status;
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
        console.displayAppleCount(appleCount);
    }

    size_t data::xFromFirstLanding(size_t x){
        if(!isFirst)
            return X(x - baseX);
        baseX = x;
        return 0;
    }

    size_t data::yFromFirstLanding(size_t y){
        if(!isFirst)
            return Y(y -baseY);
        baseY = y;
        isFirst = false;
        return 0;
    }

    size_t data::getId(){
        ++liveCount;
        console.displayRobotCount(liveCount);
        isRobotLive.push_back(true);
        return xyRobots.size();
    }

    int data::getNum(){
        return console.getNum();
    }

    void data::readCmd(char* context){
        commandLine = console.readCmd(context);
    }

    std::string data::cmd(){
        return commandLine;
    }

    void data::send(size_t x, size_t y, size_t id, robotStatus status){
        x = X(x);
        y = Y(y);
        while(!(xyRobots.size() > id))
            xyRobots.resize(id + 1);
        xyRobots[id].first = y;
        xyRobots[id].second = x;  

        if(status == robotStatus::DIE){
            isRobotLive[id] = false;
            ++dieCount;
            --liveCount;
            console.displayDieCount(dieCount);
            return;
        }

        resizeMaps(xyRobots[id].second, xyRobots[id].first);
        
        if(!updatedMapMask[xyRobots[id].first][xyRobots[id].second])
                    send(x, y, EMPTY);

        necessary = true;
    }

    void data::send(size_t x, size_t y, Item item){
        x = X(x);
        y = Y(y);

        resizeMaps(y, x);

        updatedMap[y][x] = item;

        if(!updatedMapMask[y][x])
            updatedMapMask[y][x] = true; 
        
        necessary = true;
    }

    void data::getKey(){
        savedKey = console.getKey();
    }

    graphics::Keys data::Key(){        
        return savedKey;
    }

    void data::error(char* msg){
        console.error(msg);        
    }

    void data::addInAccumulator(size_t id, toDoType toDo, Direction where){
        action* newAction = new action;
        newAction->toDo = toDo;
        newAction->id = id;
        newAction->where = where;
        collectorsTasks.push_back(*newAction);
        delete newAction;
    }

    void data::setFocus(size_t id){
        console.changeCentre(xyRobots[id].second, xyRobots[id].first);
    }

    bool data::isSafePoint(size_t y, size_t x, bool bombIgnore){
        if(updatedMap[Y(y)][X(x)] == ROCK ||
           (updatedMap[Y(y)][X(x)] == BOMB && !bombIgnore))
            return false;
        else 
            return true;
    }

    bool data::availibleToGo(size_t id, Direction where, bool bombIgnore){
        size_t x = xyRobots[id].second;
        size_t y = xyRobots[id].first;

        switch (where)
        {
        case Direction::UP:
            --y;
            break;
        case Direction::DOWN:
            ++y;
            break;
        case Direction::LEFT:
            --x;
            break;
        case Direction::RIGHT:
            ++x;
            break;
        default:
            break;
        }        

        return isSafePoint(y, x, bombIgnore);
    }

    bool data::isUnknownPoint(size_t id, Direction where){ 
        size_t x = xyRobots[id].second;
        size_t y = xyRobots[id].first;

        switch (where){
            case Direction::UP:
                --y;
                break;
            case Direction::DOWN:
                ++y;
                break;
            case Direction::LEFT:
                --x;
                break;
            case Direction::RIGHT:
                ++x;
                break;
            default:
                break;
        }   

        return !updatedMapMask[Y(y)][X(x)];
    }

    size_t data::point(std::pair<size_t, size_t> coordinate){
        return Y(coordinate.first) * xLimit + X(coordinate.second);
    }

    size_t data::point(size_t y, size_t x){
        return Y(y) * xLimit + X(x);
    }

    std::list<size_t> data::genPointsQueue(size_t x, size_t y, bool bombIgnore){
        std::list<size_t> q;
        if(updatedMapMask[Y(y + 1)][X(x)] && (isSafePoint(Y(y + 1), x, bombIgnore)))
            q.push_back(point(Y(y + 1), x));        

        if(updatedMapMask[Y(y - 1)][X(x)] && (isSafePoint(Y(y - 1), x, bombIgnore)))
            q.push_back(point(Y(y - 1), x));        

        if(updatedMapMask[Y(y)][X(x + 1)] && (isSafePoint(y, X(x + 1), bombIgnore)))
            q.push_back(point(y, X(x + 1)));        

        if(updatedMapMask[Y(y)][X(x - 1)] && (isSafePoint(y, X(x - 1), bombIgnore)))
            q.push_back(point(Y(y), X(x - 1)));        

        return q;
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

    bool data::isForGrab(size_t coordinate, Item item){
        Item res = takeItem(coordinate);
        if(res == item || (item == EMPTY && res == APPLE))
            //if(!foundInDistribution(coordinate, item))
                return true;
        return false;
    }

    size_t data::extractX(size_t coordinate){
        return coordinate % xLimit;
    }

    size_t data::extractY(size_t coordinate){
        return coordinate / xLimit;
    }
    
    Item data::takeItem(size_t coordinate){
        return updatedMap[extractY(coordinate)][extractX(coordinate)];
    }


    Direction data::toDirectionType(size_t coordinate0, size_t coordinate){
        size_t x0 = extractX(coordinate0);
        size_t y0 = extractY(coordinate0);
        size_t x = extractX(coordinate);
        size_t y = extractY(coordinate);
        if(y > y0)
            return Direction::DOWN;
        
        if(y < y0)
            return Direction::UP;

        if(x > x0)
            return Direction::RIGHT;

        if(x < x0)
            return Direction::LEFT;

        return Direction::NONE;
    }

    void data::matrixBFS(size_t id, Item item){
        bool bombIgnore = false;
        if(item == BOMB)
            bombIgnore = true;
        std::queue<size_t> q;
        size_t __capacity = xLimit * yLimit;
        std::vector<bool> used(__capacity);
        std::vector<size_t> destination(__capacity), parents(__capacity);
        size_t itemPoint = -1;
        bool found = false;
        bool found_finally = false;
        used[point(xyRobots[id])] = true;
        q.push(point(xyRobots[id]));
        //        
        while (!found && !q.empty()){
            size_t vertice = q.front();
            q.pop();
            std::list<size_t> pointsQueue = genPointsQueue(extractX(vertice), extractY(vertice), bombIgnore);

            for(size_t pointIterator : pointsQueue){
                size_t to = pointIterator;

                if(!used[to]){
                    used[to] = true;
                    q.push(to);
                    destination[to] = destination[vertice] + 1;
                    parents[to] = vertice;
                    found = isForGrab(to, item);
                    if(found){
                        itemPoint = to;
                        break;
                    }
                }  
            }
            if(found)
                break;
        }   

        if (itemPoint == -1 || !used[itemPoint])
            return;// nothing
        else {
            //cycling while no come back to the start
            for (size_t vertice = itemPoint; vertice != point(xyRobots[id]); vertice = parents[vertice]){
                (ways[id][item]).push_back(toDirectionType(parents[vertice], vertice));
            }
            return;
        }
    }

    bool data::isAnyFound(size_t id, Item item){
        // init ways
        while(!(ways.size() > id)){
            ways.resize(ways.size() + 1);
            while (!(ways.back().size() > item))
                ways.back().resize(ways.back().size() + 1);
        }

        matrixBFS(id, item);             
        
        if(ways[id][item].capacity())
            return true;
        else 
            return false;
    }

    std::vector<Direction> data::takeNearestWay(size_t id, Item item){
        return ways[id][item];
    }

    void data::outBadCmd(){
        console.error("Bad command was inputed");
    }
}