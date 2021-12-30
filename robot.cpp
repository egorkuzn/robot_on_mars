#include "robot.h"

namespace planet{
    size_t Robot::X(size_t x){
        return (x + ground[0].capacity()) % ground[0].capacity();
    }

    size_t Robot::Y(size_t y){
        return (y + ground.size()) % ground.size();
    }

    void Robot::confirmServerStep(){
        if(ground[yGround][xGround] == BOMB)
            ground[yGround][xGround] = EMPTY;
        if(ground[yGround][xGround] == ROCK)
            server.send(xServer, yServer, id, robotStatus::DIE);   
        else
            server.send(xServer, yServer, id);
    }

    void Robot::moveRight(){
        xGround = X(xGround + 1);
        xServer = xServer + 1;
        confirmServerStep();
    }

    void Robot::moveLeft(){
        xGround = X(xGround - 1);
        xServer = xServer - 1;
        confirmServerStep();
    }

    void Robot::moveDown(){
        yGround = Y(yGround + 1);
        yServer = yServer + 1;
        confirmServerStep();
    }

    void Robot::moveUp(){
        yGround = Y(yGround - 1);
        yServer = yServer - 1;
        confirmServerStep();
    }

    Robot::Robot(std::vector<vectorItems>& ground, data& server) : ground(ground), server(server){
        srand(time(NULL));
        xGround = size_t(rand()) % ground.size();
        yGround = size_t(rand()) % ground[0].capacity();
        while (ground[yGround][xGround] == ROCK)
        {
            xGround = size_t(rand()) % ground.size();
            yGround = size_t(rand()) % ground[0].capacity();
        }        
        xServer = server.xFromFirstLanding(xGround);
        yServer = server.yFromFirstLanding(yGround);
        id = server.getId();
        server.send(xServer, yServer, ground[yGround][xGround]);
        confirmServerStep();
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

}