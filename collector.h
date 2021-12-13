#pragma once

#include <vector>
#include "item.h"
#include "robot.h"
#include "cmode.h"
#include "data.h"

namespace planet{
    class Collector: public Robot{
        public:
            Collector(std::vector<vectorItems>& ground, data& server): Robot(ground, server){}
            void cmd();
            void grab();
            void refresh();            
            void genCMode(CModeT type);  
            CMode* mode = nullptr;                  
    };

    class vectorC: public std::vector<Collector>{
        public:
            vectorC(std::vector<vectorItems>& ground, planet::data& server) :
                ground(ground), server(server){}
            void man();
            void cmd();
            void refresh();
        private:
            void doAction(size_t id, toDoType toDo, Direction where);
            std::vector<vectorItems>& ground;
            planet::data& server;
            size_t manId = 0;
    };
}