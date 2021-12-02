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
        W,
        Esc,
        EMPTY
    };

    class UI{
        public:
            UI();
            UI& operator=(u_char type);
            void readCmd(void);
            Keys getKey(void);
            Keys Key;
            std::string cmd;
            uint getNum(void);
            void outBadCmd(void);
    };
}