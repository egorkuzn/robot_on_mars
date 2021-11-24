#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <curses.h>
#include <cstdlib>
#include "surface.h"
#include "data.h"
#include "robot.h"
#include "planet.cpp"

namespace planet{
    class Planet{
        public:
            std::vector<robot> robots;
            Surface ground;
            Data server; 
            bool getCommand(void);
        private:
            UI consol;
            size_t manual = 0;
            bool menu(void);   
            void takeRobotsStep(void);         
    };
}