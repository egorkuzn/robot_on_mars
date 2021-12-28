#pragma once

#include "ui.h"
#include "item.h"
#include "data.h"
#include <vector>

namespace planet{
    class Robot{
        public: 
            Robot(std::vector<vectorItems>& ground, data& server);
            void move(Direction way);
            // void changeServer(data& new_server); // future feature
            ~Robot(){}
            void scan();            
            size_t xGround;
            size_t yGround;
            size_t xServer;
            size_t yServer;
            size_t id;
            std::vector<vectorItems>& ground;
            data& server;
        private:
            size_t X(size_t x);
            size_t Y(size_t y);
            void moveUp();
            void moveDown();
            void moveLeft();
            void moveRight();
            void confirmServerStep();
    };
}