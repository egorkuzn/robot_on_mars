#pragma once

#include "ui.h"
#include "item.h"
#include "data.h"
#include <vector>

namespace planet{
    enum class Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class Robot{
        public: 
            Robot(std::vector<vectorItems>& ground, data& server);
            void move(Direction way);
            // void changeServer(data& new_server); // future feature
            ~Robot(){}
            Robot(const Robot& other);
            void scan();
            size_t x;
            size_t y;
            size_t id;
            robotStatus status = robotStatus::LIVE;
            std::vector<vectorItems>& ground;
            data& server;
        private:
            void moveUp();
            void moveDown();
            void moveLeft();
            void moveRight();
    };
}