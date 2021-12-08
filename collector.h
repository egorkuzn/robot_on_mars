#pragma once

#include <vector>
#include "item.h"
#include "robot.h"
#include "cmode.h"
#include "data.h"

namespace planet{
    class Collector: private Robot{
        public:
            Collector(std::vector<vectorItems>& ground, data& server): Robot(ground, server){}
            CMode mode;
            void cmd();
            void grab();
            void refresh();
            void genCMode(CModeT type);                    
    };

    class vectorC: public std::vector<Collector>{
        public:
            vectorC(std::vector<vectorItems>& ground, data& server) :
                ground(ground), server(server){}
            void man();
            void cmd();
            void refresh();
        private:
            std::vector<vectorItems>& ground;
            data& server;
            size_t manId = 0;
    };
}