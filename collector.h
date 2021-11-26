#pragma once

#include <vector>
#include "robot.h"
#include "cmode.h"
#include "data.h"

namespace planet{
    class Collector: public Robot{
        public:
            CMode mode;
            void cmd(data& server);
            void refresh();
            void genCMode();
    };

    class vectorC: public std::vector<Collector>{
        public:
            void man(data& server);
            void cmd(data& server);
            void refresh(data& server);
        private:
            size_t manId = 0;
    };
}