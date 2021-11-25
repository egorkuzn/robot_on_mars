#pragma once

#include "robot.h"
#include "ui.h"

namespace planet{
    class CollectorMode{
        scan
        grab
        moveUp
        moveDown
        moveLeft
        moveRigth
        manualOff
        manualOn
        autoOn
    };

    class Collector: public Robot, public CollectorMode{
        public:
        cmd(const std::string)
        private:

    };

    class vectorC: public std::vector<Collector>{
        public:
            void man(Keys Key);
            void cmd(UI& console);
        private:
            size_t manId = 0;
    };
}