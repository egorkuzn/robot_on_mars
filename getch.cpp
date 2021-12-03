#include "getch.h"

namespace safety_input{
    void initTermios(int echo) 
    {   
        tcgetattr(0, &old); /* grab old terminal i/o settings */
        fresh = old; /* make fresh settings same as old settings */
        fresh.c_lflag &= ~ICANON; /* disable buffered i/o */
        fresh.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
        tcsetattr(0, TCSANOW, &fresh); /* use these fresh terminal i/o settings now */
    }

    void resetTermios(void) 
    {
        tcsetattr(0, TCSANOW, &old);
    }

    char getch_(int echo) 
    {
        char ch;
        initTermios(echo);
        ch = getchar();
        resetTermios();
        return ch;
    }

    char getch(void) 
    {
        return getch_(0);
    }

    char getche(void) 
    {
        return getch_(1);
    }

}