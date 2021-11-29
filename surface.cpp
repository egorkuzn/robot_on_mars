#include "surface.h"

namespace planet{
    surface::surface(data* server,
                     size_t high = 1000,
                     size_t width = 1000) : server(server), high(high), width(width){
        vectorItems tmp(server);
        matrix = tmp;
        matrix[high * width - 1];
        genTerrain();
        genItems();
    }

    void surface::genItems(void){
        size_t chances = high * width / 20;
        for(chances; chances > 0; --chances)
            matrix.randItem(high, width);
    }

    void surface::genTerrain(void){
        size_t chances = high * width / 5;
        for(chances; chances > 0; --chances)
            matrix.randRock(high, width);
    }    
}