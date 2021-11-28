#pragma once

#include "item.h"

namespace planet{
    class Surface{
        public:
        Surface(data* server,
                size_t high = 1000,
                size_t width = 1000) : server(server), high(high), width(width);
        ~Surface(){}
        void genItems(void);
        void genTerrain(void);
        vectorItems matrix;
        private:
            data* server;
            size_t high;
            size_t width;
    };
}