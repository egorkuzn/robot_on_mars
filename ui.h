#pragma once

#include "ncurses.h"
#include "string"

namespace planet{
    enum class Keys{
        U,
        S,
        D,
        A,
        Q,
        E,
        F,
        Esc,
    };

    class UI{
        public:
            UI();
            UI& operator=(u_char type);
            void readCmd(void);
            Key getKey(void);
            std::string cmd;
            uint getNum(void);
            void outBadCmd(void);
    };
}