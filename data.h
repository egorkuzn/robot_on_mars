#pragma once

#include "item.h"
#include <vector>
#include <string>
#include <map>
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
        std::vector <action> collectorsTasks;
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