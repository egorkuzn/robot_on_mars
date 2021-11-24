#pragma once
#include <vector>
#include <curses.h>
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
            size_t manual;
            bool get_command(void);
        private:
            void menu();            
    };
}