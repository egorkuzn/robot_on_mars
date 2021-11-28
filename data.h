#pragma once

#include <vector>

namespace planet{
    class data{
        public:
        data();
        send();
        get();
        mapMask;  
        void error(char* msg);  
        private:   
        UI* consol = nullptr; 
    }
}