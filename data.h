#pragma once

#include "item.h"
#include <vector>
#include <queue>
#include <string>
#include <list>
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
        data();
        data& operator=(data& other); // необходимо 
        void send(size_t x, size_t y, Item item);
        void send(size_t x, size_t y, size_t id, robotStatus status = robotStatus::LIVE);
        uint8_t isNotFirst(size_t value, char ort);
        size_t yOfFirstLanding();
        size_t xOfFirstLanding();
        void setFocus(size_t id);
        void incAppleCount();
        void setFocus(size_t id);
        void cmdToScanArea(size_t id);
        void addInAccumulator(size_t id, toDoType toDo, Direction where = Direction::NONE);
        std::list <action> collectorsTasks;
        std::vector<Direction> takeNearestWay(size_t id, Item thing);
        bool availibleToGo(size_t x, size_t y);
        bool isUnknownPoint(size_t x, size_t y);
        bool isAnyAppleFound(size_t id);
        void getKey();
        int getNum();
        size_t getId();
        void readCmd();
        std::string cmd();
        void outBadCmd();
        std::vector<vectorItems> updatedMap;
        std::vector<std::vector<bool>> updatedMapMask;
        std::vector<bool> isRobotLive;
        std::vector<size_t[2]> xyRobots;
        void error(char *msg);
        size_t Num();
        graphics::Keys Key();        
    private:
        Item takeItem(size_t coordinate);
        std::list<size_t> genPointsQueue(size_t x, size_t y);
        std::vector<size_t[2]> matrixBFS(size_t id, Item item);
        bool isAppleForGrab(size_t coordinate, Item item);
        bool foundInDistribution(size_t coordinte, Item item);
        size_t point(size_t coordinate [2]);
        std::vector<size_t[2]> bombWay;
        std::vector<size_t[2]> appleWay;
        std::vector<std::list<size_t>> distribution; // 0 - apple distribution for collectors, 1 - bomb distribution for sappers
        size_t baseX;
        size_t baseY;
        size_t appleCount = 0;
        size_t liveCount = 0;
        size_t dieCount = 0;
        graphics::Keys savedKey;
        std::string commandLine;
        graphics::UI *console = nullptr;
    };
}