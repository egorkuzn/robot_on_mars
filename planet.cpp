#include "planet.h"
#define N 30

namespace planet{
    std::vector<vectorItems> Planet::genGround(size_t high, size_t width){
        vectorItems tmp = vectorItems(high * width);
        std::vector<vectorItems> result;
        for(size_t i = 0; i < high; ++i){
            result.push_back(vectorItems(size_t(0)));
            for(size_t j = 0; j < width; ++j)
                result[i].push_back(tmp[i * width + j]);
        }

        return result;
    }

    Planet::Planet() : ground(genGround(N, N)),
                       server(N, N),
                       collectors(ground, server),
                       sappers(ground, server){}

    Planet::operator bool(){
        return server && status;
    }

    void Planet::menu(void){
        if(server.Key() == graphics::Keys::U){
            server.readCmd("Input \'collector\' or \'sapper\'");            
            if(server.cmd() == "collector")
                collectors.cmd("\'auto\'|\'scan\'|\'switch\'|\'add\'");
            else if(server.cmd() == "sapper")
                sappers.cmd("\'add\'|\'change mode\'");
            else{
                server.outBadCmd();  
                status = false;
            }          
        }
    }

    void Planet::takeRobotsStep(void){
        collectors.refresh();
        sappers.refresh();
    }    

    void Planet::getCommand(void){
        server.getKey();
        if(server.Key() == graphics::Keys::Esc){
            status = false;
            return;
        }
        collectors.man("");
        menu();
        takeRobotsStep();
        // we needed to set some time balance
        server.mapViewUpdate();
    }
}