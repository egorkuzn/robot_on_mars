#pragma once

#include "item.h"
#include <vector>
#include <string>
#include "ui.h"

namespace planet{
    enum class toDoType{

    };

    enum class robotStatus{
        LIVE,
        DIE
    };    

    class data{
        public:
            data();
            void send(size_t x, size_t y, Item item);
            void send(size_t x, size_t y, size_t id, robotStatus status = robotStatus::LIVE);
            uint8_t isFirst();
            size_t dyFromFirstLanding(size_t y);
            size_t dxFromFirstLanding(size_t x);
            void incAppleCount();
            void setFocus(size_t id);
            void getKey();
            int getNum();
            size_t getId();
            void readCmd();
            char* cmd();
            void outBadCmd();
            std::vector<vectorItems> updatedMap;
            std::vector<std::vector<bool>> updatedMapMask;
            std::vector<size_t [2]> xyRobots;
            void error(char* msg);  
            size_t Num();
            graphics::Keys Key();
        private:   
            graphics::UI* console = nullptr;

    };
}