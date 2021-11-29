#pragma once

#include <vector>
#include "surface.h"
#include "robot.h"
#include "cmode.h"
#include "data.h"

namespace planet{
    class Collector: public Robot{
        public:
            CMode mode;
            void cmd();
            void refresh();
            void genCMode();            
    };

    class vectorC: public std::vector<Collector>{
        public:
            vectorC(surface& ground, data& server) : ground(ground), server(server);
            void man();
            void cmd();
            void refresh();
        private:
            surface& ground; 
            data& server;
            size_t manId = 0;
    };
}