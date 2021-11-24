#include <iostream>
#include "planet.h"

int main(){
    planet::Planet Mars;
    while(true){
        if(!Mars.getCommand())
            break;
    }
    return 0;
}