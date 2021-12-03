#pragma once

#include "item.h"

namespace planet {
    class surface : public vectorItems{
        public:
        surface(size_t high = 1000,
                size_t width = 1000);
        ~surface(){}
        void genItems(void);
        void genTerrain(void);
        private:
            size_t high;
            size_t width;
    };
}