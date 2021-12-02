#include "data.h"

namespace planet{
    data::data(){
        console = new UI;        
    }

    void send(Collector* machine, toDoType action){
        
    }

    void getKey(){
        savedKey = consol.getKey();
    }

    Keys Key(){
        return savedKey;
    }

    void error(char* msg){
        consol.error(msg);        
    }
}