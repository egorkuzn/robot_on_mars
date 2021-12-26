#include "robot.h"

namespace planet{
    void Robot::moveRight(){
        xGround = (xGround + ground[0].capacity() + 1) % ground[0].capacity();
        xServer = (xServer + ground[0].capacity() + 1) % ground[0].capacity();
        if(ground[yGround][xGround] == (ROCK || BOMB))
            server.send(xServer, yServer, id, robotStatus::DIE);   
        else
            server.send(xServer, yServer, id);
    }

    void Robot::moveLeft(){
        xGround = (xGround + ground[0].capacity() - 1) % ground[0].capacity();
        xServer = (xServer + ground[0].capacity() - 1) % ground[0].capacity();
        if(ground[yGround][xGround] == (ROCK || BOMB))
            server.send(xServer, yServer, id, robotStatus::DIE);   
        else
            server.send(xServer, yServer, id);
    }

    void Robot::moveDown(){
        yGround = (yGround + ground.size() - 1) % ground.size();
        yServer = (yServer + ground.size() - 1) % ground.size();
        if(ground[yGround][xGround] == (ROCK || BOMB))
            server.send(xServer, yServer, id, robotStatus::DIE);   
        else
            server.send(xServer, yServer, id);
    }

    void Robot::moveUp(){
        yGround = (yGround + ground.size() + 1) % ground.size();
        yServer = (yServer + ground.size() + 1) % ground.size();
        if(ground[yGround][xGround] == (ROCK || BOMB))
            server.send(xServer, yServer, id, robotStatus::DIE);   
        else
            server.send(xServer, yServer, id);
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
        server.send(xServer + 1, yServer, ground[yGround][xGround + 1]);
        server.send(xServer - 1, yServer, ground[yGround][xGround - 1]);
        server.send(xServer, yServer + 1, ground[yGround + 1][xGround]);
        server.send(xServer, yServer - 1, ground[yGround - 1][xGround]);
    }
}