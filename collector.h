#pragma once

#include <vector>
#include "item.h"
#include "robot.h"
#include "cmode.h"
#include "data.h"

namespace planet{
    typedef struct idStruct{
        size_t serverId;
        bool isLive;
    } idStruct;

    class Collector: public Robot{
        public:
            Collector(std::vector<vectorItems>& ground, data& server, size_t idx);
            ~Collector();
            void cmd(char* context);
            void grab();
            void scan();
            void refresh();            
            void genCMode(CModeT type);  
            void dieIfBomb();
        private:
            CModeT modeStatus = CModeT::SCAN;
            CMode* mode = nullptr; 
            size_t idxInCollectors;                 
    };

    class vectorC: public std::vector<Collector>{
        public:
            vectorC(std::vector<vectorItems>& ground, planet::data& server) :
                ground(ground), server(server){}
            void man(char* context);
            void cmd(char* context);
            void refresh();
        private:
            void add();
            bool vectorCheck();
            void updateServerId();
            size_t firstLive();
            void takeIndexFromId(size_t& id);
            void doAction(size_t id, toDoType toDo, Direction where);
            std::vector<vectorItems>& ground;
            std::vector<idStruct> serverId;
            planet::data& server;
            size_t manId = 0;
    };
}