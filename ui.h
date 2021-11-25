#pragma once
#include "ncurses.h"

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
    }

    class UI{
        public:
            UI();
            UI& operator=(u_char type);
        private:
    };
}