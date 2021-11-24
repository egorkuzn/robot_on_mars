#include <iostream>
#include "planet.h"

int main(){
    planet::Planet Mars;
    while(true){
        if(!Mars.get_command())
            break;
    }
    return 0;
}