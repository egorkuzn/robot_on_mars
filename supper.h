#pragma once

#include <vector>
#include "robot.h"

namespace planet{
    class Supper: public Robot{

    };
     
    class vectorS: public std::vector<Supper>{
        public:
            void refresh(UI& consol);
        private:

    };
}