#pragma once
#include <iostream>
#include <string>
#include <curses.h>
#include <cstdlib>
#include "ui.h"
#include "item.h"
#include "data.h"
#include "collector.h"
#include "sapper.h"
#include "planet.cpp"

namespace planet{
    class Planet{
        public:
            Planet();
            vectorItems ground;
            data server; 
            vectorC collectors(ground, server);
            vectorS suppers(ground, server);
            bool getCommand(void);
        private:
            size_t manual = 0;
            void menu(void);   
            void takeRobotsStep(void);         
    };
}