#pragma once

#include <vector>
#include "robot.h"
#include "ui.h"

namespace planet{
    enum CModeT{
        AUTO,
        MAN,
        SCAN
    }

    class CMode: public ManualMode, public ScanMode, public AutoMode{
        fill
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

    class Collector: public Robot{
        public:
        CMode mode;
        void cmd(UI& console);
    };

    class vectorC: public std::vector<Collector>{
        public:
            void man(UI& console);
            void cmd(UI& console);
            void refresh(UI& console);
        private:
            size_t manId = 0;
    };
}