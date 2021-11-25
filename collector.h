#pragma once

#include <vector>
#include "robot.h"
#include "ui.h"

namespace planet{
    class CMode: public ManualMode, public ScanMode, public AutoMode{
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

    class Collector: public Robot, public CMode{
        public:
        void changeMode(UI& consol);
        CMode mode;

        private:

    };

    class vectorC: public std::vector<Collector>{
        public:
            void man(Keys Key);
            void cmd(UI& console);
            void refresh(UI& consol);
        private:
            size_t manId = 0;
    };
}