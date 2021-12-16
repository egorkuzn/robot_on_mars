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
            size_t x;
            size_t y;
            size_t id;
            std::vector<vectorItems>& ground;
            data& server;
        private:
            void moveUp();
            void moveDown();
            void moveLeft();
            void moveRight();
    };
}