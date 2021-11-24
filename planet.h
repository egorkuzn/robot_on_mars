#pragma once
#include <vector>
#include "surface.h"
#include "data.h"
#include "robot.h"
#include "planet.cpp"

namespace planet{
    class Planet{
        public:
            std::vector<robot> robots;
            Surface ground;
            Data server; 
        private:
            bool get_command(void);
    };
}