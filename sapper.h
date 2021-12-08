#pragma once

#include <vector>
#include "robot.h"
#include "data.h"
#include "item.h"

namespace planet{
    class Supper: public Robot{
        Supper(std::vector<vectorItems>& ground, data& server): Robot(ground, server){}
        void refresh();
        void on();
        void off();
    };
     
    class vectorS: public std::vector<Supper>{
        public:
            vectorS(std::vector<vectorItems>& ground, data& server) : 
                ground(ground), server(server){}
            void cmd();
            void refresh();
        private:
            std::vector<vectorItems>& ground;
            data& server;
    };
}