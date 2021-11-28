#include "robot.h"

namespace planet{
    void Robot::move(Direction way, surface& ground, data& server){
        switch(way){
            case Direction::UP:
                moveUp(server);
                break;
            case Direction::DOWN:
                moveDown(server);
                break;
            case Direction::LEFT:
                moveLeft(server);
                break;
            case Direction::RIGHT:
                moveRight(server);
                break;            
        }
    }

    void Robot::scan(surface& ground, data& server){   
        server.send(x, y);
    }
}