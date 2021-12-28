#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "ui.h"
#include "item.h"
#include "data.h"
#include "collector.h"
#include "sapper.h"

namespace planet{
    class Planet{
        public:
            Planet();
            void getCommand(void);
            operator bool();
        private:
            std::vector<vectorItems> ground;
            std::vector<vectorItems> genGround(size_t high, size_t width);
            data server; 
            vectorC collectors;
            vectorS sappers;
            bool status = true;
            size_t manual = 0;
            void menu(void);   
            void takeRobotsStep(void);         
    };
}