#pragma once

#include "item.h"
#include <vector>
#include <queue>
#include <string>
#include <list>
#include <unordered_map>
#include "ui.h"

namespace planet
{
    enum class Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };

    enum class toDoType
    {
        MOVE,
        GRAB,
        SCAN,
    };

    enum class robotStatus
    {
        LIVE,
        DIE
    };

    struct action{
        size_t id;
        toDoType toDo;
        Direction where;
    };

    class data
    {
    public:
        data(size_t x, size_t y);
        ~data();
        operator bool();
        void send(size_t x, size_t y, Item item);
        void send(size_t x, size_t y, size_t id, robotStatus status = robotStatus::LIVE);
        uint8_t isNotFirst(size_t value, char ort);
        size_t yFromFirstLanding(size_t y);
        size_t xFromFirstLanding(size_t x);
        void setFocus(size_t id);
        void incAppleCount();
        void cmdToScanArea(size_t id);
        void addInAccumulator(size_t id, toDoType toDo, Direction where = Direction::NONE);
        std::list <action> collectorsTasks;
        std::vector<Direction> takeNearestWay(size_t id, Item thing);
        bool availibleToGo(size_t id, Direction where);
        bool isUnknownPoint(size_t id, Direction where);
        bool isAnyFound(size_t id, Item item);
        void getKey();
        int getNum();
        size_t getId();
        void readCmd(char* context);
        std::string cmd();
        void outBadCmd();
        std::vector<vectorItems> updatedMap;
        std::vector<std::vector<bool>> updatedMapMask;
        std::vector<bool> isRobotLive;
        std::vector<std::pair<size_t, size_t>> xyRobots; // first is y, second is x. The rizon why: matrix view
        void error(char *msg);
        size_t Num();
        graphics::Keys Key();  
    private:
        Item takeItem(size_t coordinate);
        std::list<size_t> genPointsQueue(size_t x, size_t y);
        std::vector<std::vector<std::vector<Direction>>> ways;
        std::vector<Direction> matrixBFS(size_t id, Item item);
        Direction toDirectionType(size_t coordinate0, size_t coordinate);
        bool isAppleForGrab(size_t coordinate, Item item);
        bool foundInDistribution(size_t coordinte, Item item);
        size_t point(size_t x, size_t y);
        size_t point(std::pair<size_t, size_t> coordinate);
        size_t extractX(size_t cootdinate);
        size_t extractY(size_t coordinate);
        size_t Y(size_t y);
        size_t X(size_t x);
        void resizeMaps(size_t x, size_t y);
        std::vector<size_t[2]> bombWay;
        std::vector<size_t[2]> appleWay;
        std::vector<std::list<size_t>> distribution; // 0 - apple distribution for collectors, 1 - bomb distribution for sappers
        size_t baseX = 0;
        size_t baseY = 0;
        size_t xLimit = 0;
        size_t yLimit = 0;
        size_t appleCount = 0;
        size_t liveCount = 0;
        size_t dieCount = 0;
        bool isFirst = true;
        bool status = true;
        graphics::Keys savedKey = graphics::Keys::EMPTY;
        std::string commandLine;
        graphics::UI *console = nullptr;
    };
}