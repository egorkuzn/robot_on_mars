#include "robot.h"

namespace planet{
    void Robot::move(Direction way, UI& console){
        switch(way){
            case Direction::UP:
                moveUp(console);
                break;
            case Direction::DOWN:
                moveDown(console);
                break;
            case Direction::LEFT:
                moveLeft(console);
                break;
            case Direction::RIGHT:
                moveRight(console);
                break;            
        }
    }

    void 
}