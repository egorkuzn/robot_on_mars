#pragma once

#include "robot.h"



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
        cmd
        private:

    };

    class vectorC: public std::vector{

    }
}