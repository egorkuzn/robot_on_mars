#pragma once

#include "ui.h"
#include "surface.h"

namespace planet{
    enum class Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class Movement{
        public:
            void moveUp(surface& ground, data& server);
            void moveDown(surface& ground, data& server);
            void moveLeft(surface& ground, data& server);
            void moveRight(surface& ground, data& server);
    };

    class Robot: public Movement{
        public: 
            void move(Direction way);
            void changeServer(data& server) : server(server){}
            void scan();
            size_t x;
            size_t y;
        protected:
            surface& ground;
            data& server;
    };
}