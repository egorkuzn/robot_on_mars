#pragma once

#include "robot.h"
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
        mapMask;  
        void error(char* msg);  
        private:   
        UI* console = nullptr;
        Keys savedKey = Keys::EMPTY;
    }
}