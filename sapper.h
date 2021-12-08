#pragma once

#include <vector>
#include "robot.h"
#include "data.h"
#include "item.h"

namespace planet{
    class Sapper: public Robot{
        Sapper(std::vector<vectorItems>& ground, planet::data& server): Robot(ground, server){}
        void refresh();
        void on();
        void off();
    };
     
    class vectorS: public std::vector<Sapper>{
        public:
            vectorS(std::vector<vectorItems>& ground, planet::data& server) : 
                ground(ground), server(server){}
            void cmd();
            void refresh();
        private:
            std::vector<vectorItems>& ground;
            planet::data& server;
    };
}