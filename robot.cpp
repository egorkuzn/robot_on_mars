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

    void Robot::moveDown(){
        y = (y + ground.size() + 1) % ground.size();
        if(ground[y][x] == (ROCK || BOMB))
            server.send(x, y, id, robotStatus::DIE);   
        else
            server.send(x, y, id);
    }

    Robot::Robot(std::vector<vectorItems>& ground, data& server) : ground(ground), server(server){
        x = (rand() % ground[0].capacity()) * (size_t)server.isFirst(); // x from landing of first robot
        y = rand() % ground.size() * (size_t)server.isFirst();  // y from landing of first robot 
        id = server.getId();
        server.send(x, y, ground[y + server.dyFromFirstLanding(y)][x + server.dxFromFirstLanding(x)]);
        if(ground[y][x] == (ROCK || BOMB)){
            server.send(x, y, id, robotStatus::DIE);  

        }    
    } 

    Robot::Robot(const Robot& other){
        this->x = other.x;
        this->y = other.y;
        this->id = other.id;
        this->status = other.status;
        this->server = other.server;
        this->ground = other.ground;
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