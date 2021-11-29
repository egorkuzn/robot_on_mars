#pragma once

#include "item.h"

namespace planet{
    class surface{
        public:
        surface(){}
        surface(data* server,
                size_t high = 1000,
                size_t width = 1000) : server(server), high(high), width(width);
        ~surface(){}
        void genItems(void);
        void genTerrain(void);
        vectorItems matrix;
        private:
            data* server;
            size_t high;
            size_t width;
    };
}