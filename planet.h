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
            vectorC collectors;
            vectorS suppers;
            surface ground;
            data server; 
            bool getCommand(UI& console = 0);
        private:
            UI console;
            size_t manual = 0;
            void menu(UI& console);   
            void takeRobotsStep(void);         
    };
}