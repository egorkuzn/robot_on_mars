#include "data.h"

namespace planet{
    data::data(){
        consol = new UI;        
    }

    void send(size_t x, size_t y){
        
    }

    void error(char* msg){
        consol.error(msg);        
    }
}