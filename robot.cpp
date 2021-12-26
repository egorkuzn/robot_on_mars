#include "robot.h"

namespace planet{
    size_t Robot::X(size_t x){
        return (x + ground[0].capacity()) % ground[0].capacity();
    }

    size_t Robot::Y(size_t y){
        return (y + ground.size()) % ground.size();
    }

    void Robot::moveRight(){
        xGround = X(xGround + 1);
        xServer = xServer + 1;
        if(ground[yGround][xGround] == (ROCK || BOMB))
            server.send(xServer, yServer, id, robotStatus::DIE);   
        else
            server.send(xServer, yServer, id);
    }

    void Robot::moveLeft(){
        xGround = X(xGround - 1);
        xServer = xServer - 1;
        if(ground[yGround][xGround] == (ROCK || BOMB))
            server.send(xServer, yServer, id, robotStatus::DIE);   
        else
            server.send(xServer, yServer, id);
    }

    void Robot::moveDown(){
        yGround = Y(yGround - 1);
        yServer = yServer - 1;
        if(ground[yGround][xGround] == (ROCK || BOMB))
            server.send(xServer, yServer, id, robotStatus::DIE);   
        else
            server.send(xServer, yServer, id);
    }

    void Robot::moveUp(){
        yGround = Y(yGround + 1);
        yServer = yServer + 1;
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
        else
            server.send(xServer, yServer, id);
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
        server.send(xServer + 1, yServer, ground[Y(yGround)][X(xGround + 1)]);
        server.send(xServer - 1, yServer, ground[Y(yGround)][X(xGround - 1)]);
        server.send(xServer, yServer + 1, ground[Y(yGround + 1)][X(xGround)]);
        server.send(xServer, yServer - 1, ground[Y(yGround - 1)][X(xGround)]);
    }
}