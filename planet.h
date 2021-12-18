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
            operator bool();
        private:
            std::vector<vectorItems> ground;
            data server; 
            vectorC collectors;
            vectorS sappers;
            bool getCommand(void);
            size_t manual = 0;
            void menu(void);   
            void takeRobotsStep(void);         
    };
}