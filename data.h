#pragma once

#include "item.h"
#include <vector>
#include <string>
#include "ui.h"

namespace planet
{
    enum class toDoType
    {

    };

    enum class robotStatus
    {
        LIVE,
        DIE
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