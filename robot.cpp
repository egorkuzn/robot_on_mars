#include "robot.h"

namespace planet{
    void Robot::move(Direction way){
        switch(way){
            case Direction::UP:
                moveUp(ground, server);
                break;
            case Direction::DOWN:
                moveDown(ground, server);
                break;
            case Direction::LEFT:
                moveLeft(ground, server);
                break;
            case Direction::RIGHT:
                moveRight(ground, server);
                break;            
        }
    }

    void Robot::scan(){   
        server.send(x, y);
    }
}