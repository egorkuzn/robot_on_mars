#pragma once

#include <vector>
#include <string>
#include "ui.h"

namespace planet{
    class data{
        public:
        data();
        send();
        get();
        void readCmd();
        char* cmd();
        void getKey();
        Keys Key();
        void outBadCmd;
        mapMask;  
        void error(char* msg);  
        private:   
        UI* consol = nullptr; 
    }
}