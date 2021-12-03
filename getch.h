#pragma once

#include <termios.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/time.h>
#include <unistd.h>

namespace safety_input{
    static struct termios old, fresh;

    /* Initialize fresh terminal i/o settings */
    void initTermios(int echo);

    /* Restore old terminal i/o settings */
    void resetTermios(void);

    /* Read 1 character - echo defines echo mode */
    char getch_(int echo);

    /* Read 1 character without echo */
    char getch(void);

    /* Read 1 character with echo */
    char getche(void);
}