#pragma once

#include "robot.h"
#include "item.h"
#include <vector>
#include <string>
#include "ui.h"

namespace planet{
    enum class toDoType{

    }
    class data{
        public:
        data();
        send(Robot* machine, toDoType action);
        get();
        void readCmd();
        char* cmd();
        void getKey();
        int getNum();
        Keys Key();
        void outBadCmd;
        std::vector<vectorItems> updatedMap;
        std::vector<std::vector<bool>> updatedMapMask;
        void error(char* msg);  
        private:   
        UI* console = nullptr;
        Keys savedKey = Keys::EMPTY;
    }
}