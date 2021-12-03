#pragma once

#include <locale.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include "item.h"
#include "getch.h"

namespace graphics{
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
            ~UI();
            operator bool() const;
            void display(); 
            void refreshW();
            void clearLiveStr();
            bool isChanged();
            Keys getKey();
            std::string readCmd(char* constex);
            int getNum(char* context);
            void error(char* context);
            void moveMapUp();
            void moveMapDown();
            void moveMapLeft();
            void moveMapRight();
        private:
            void backDel(std::string str);
            void frontDel(std::string str);
            void genDisplayedMatrix();
            Keys reactionOnKeyboard(int ch);
            void sleepcp(int milliseconds);
            bool status = true;
            size_t high = 7;
            size_t width = 25;
            int x = 12;
            int y = 3;
            std::vector<std::string> displayedMatrix;
            std::vector<bool> matrixMask;
            std::string liveStr;
    };
}
/*
🟥 - unvisited point
🟫 - visited point
🤖 - robot
*/