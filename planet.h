#pragma once
#include <iostream>
#include <string>
#include <curses.h>
#include <cstdlib>
#include "ui.h"
#include "surface.h"
#include "data.h"
#include "collector.h"
#include "sapper.h"
#include "planet.cpp"

namespace planet{
    class Planet{
        public:
            Planet();
            surface ground;
            vectorC collectors(ground);
            vectorS suppers(ground);
            data server; 
            bool getCommand(void);
        private:
            size_t manual = 0;
            void menu(void);   
            void takeRobotsStep(void);         
    };
}