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

    enum class Matrix{
        MAP,
        MASK
    };

    class UI{
        public:
            UI( std::vector<std::pair<size_t, size_t>>& xyRobots,
                std::vector<std::vector<bool>>& matrixMask,
                std::vector<planet::vectorItems>& externMatrix );
            ~UI();
            operator bool() const;
            void display(); 
            bool isChanged();
            Keys getKey();
            std::string readCmd(char* constex = nullptr);
            int getNum(char* context = nullptr);
            void error(char* context);
            void changeCentre(size_t x0, size_t y0);
            void displayAppleCount(size_t value);
            void displayRobotCount(size_t value);
            void displayDieCount(size_t count);  
        private:
            int _kbhit();
            void window();
            void sleepcp(int milliseconds);
            void refreshStatusBar();
            int safetyIndexTake(Matrix mType, size_t x0, size_t y0);
            bool isRobotHere(size_t x0, size_t y0);
            std::string emojiTranslator(planet::Item item);
            std::string genMatrixString(size_t stringNumb);
            Keys reactionOnKeyboard(int ch);
            bool status = true;
            size_t high = 7;
            size_t width = 25;
            size_t appleCount = 0;
            size_t liveCount = 0;
            size_t dieCount = 0;
            int x = 12;
            int y = 3;
            std::vector<std::string> displayedMatrix;
            std::vector<std::pair<size_t, size_t>>& xyRobots;
            std::vector<std::vector<bool>>& matrixMask;
            std::vector<planet::vectorItems>& externMatrix;
            std::string liveStr;
            std::string statusBar;
    };
}
