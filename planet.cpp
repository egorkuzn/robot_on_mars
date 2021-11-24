#include "planet.h"
#define KEY_Esc 27


namespace planet{
    bool Planet::get_command(void){
        char Key = getch();
        switch (Key)
        {
        case 'u':
            return robots[manual].moveUp();
        case 's':
            return robots[manual].moveDown();
        case 'a':
            return robots[manual].moveLeft();
        case 'd':
            return robots[manual].moveRight();
        case 'f':
            return robots[manual].scan();
        case 'e':
            return robots[manual].grab();
        case 'q':
            return menu();
        case KEY_Esc:
            return false;
        default:
            break;
        }
    }
}