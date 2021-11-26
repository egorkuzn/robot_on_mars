#pragma once

#include "ui.h"

namespace planet{
    enum class Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    class Movement{
        public:
            void moveUp(UI& console);
            void moveDown(UI& console);
            void moveLeft(UI& console);
            void moveRight(UI& console);
    };

    class Robot: public Movement{
        public: 
            void move(Direction way, UI& console);
            void scan();
    };
}