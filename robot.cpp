#include "robot.h"

namespace planet{
    void Robot::moveRight(){
        x = (x + 1) % ground[0].capacity();
        if(ground[y][x] == (ROCK || BOMB))
            server.send(x, y, id, robotStatus::DIE);   
        else
            server.send(x, y, id);
    }

    void Robot::moveLeft(){
        x = (x + ground[0].capacity() - 1) % ground[0].capacity();
        if(ground[y][x] == (ROCK || BOMB))
            server.send(x, y, id, robotStatus::DIE);   
        else
            server.send(x, y, id);
    }

    void Robot::moveDown(){
        y = (y + ground.size() - 1) % ground.size();
        if(ground[y][x] == (ROCK || BOMB))
            server.send(x, y, id, robotStatus::DIE);   
        else
            server.send(x, y, id);
    }

    void Robot::moveUp(){
        y = (y + ground.size() + 1) % ground.size();
        if(ground[y][x] == (ROCK || BOMB))
            server.send(x, y, id, robotStatus::DIE);   
        else
            server.send(x, y, id);
    }

    Robot::Robot(std::vector<vectorItems>& ground, data& server) : ground(ground), server(server){
        xGround = rand() % ground.size();
        yGround = rand() % ground[0].capacity();
        xServer = server.xFromFirstLanding(xGround);
        yServer = server.yFromFirstLanding(yGround);
        id = server.getId();
        server.send(xServer, yServer, ground[yGround][xGround]);
        if(ground[yGround][xGround] == (ROCK || BOMB))
            server.send(xServer, yServer, id, robotStatus::DIE);       
    } 
    
    void Robot::move(Direction way){
        switch(way){
            case Direction::UP:
                moveUp();
                break;
            case Direction::DOWN:
                moveDown();
                break;
            case Direction::LEFT:
                moveLeft();
                break;
            case Direction::RIGHT:
                moveRight();
                break;            
        }
    }

    void Robot::scan(){   
        server.send(x + 1, y, ground[y][x + 1]);
        server.send(x - 1, y, ground[y][x - 1]);
        server.send(x, y + 1, ground[y + 1][x]);
        server.send(x, y - 1, ground[y - 1][x]);
    }
}