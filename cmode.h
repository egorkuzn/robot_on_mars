#pragma once 

#include "data.h"

namespace planet{
    enum class CModeT{
        AUTO,
        MAN,
        SCAN
    };

    class CMode{
        public:
            virtual void func(size_t x,
                             size_t y,
                             size_t id,
                             data& server);
        protected:
            size_t x = 0;
            size_t y = 0;
            size_t id = 0;
            data& server;
    };

    class ManualMode: public CMode{
        public:
            ManualMode(data& server);
            void func(size_t x,
                      size_t y,
                      size_t id,
                      data& server) override;
    };

    class AutoMode: public CMode{
        public:
            AutoMode(data& server);
            void func(size_t x,
                      size_t y,
                      size_t id,
                      data& server) override;
    };

    class ScanMode: public CMode{
        public:
            ScanMode(data& server);
            void func(size_t x,
                      size_t y,
                      size_t id,
                      data& server) override;
    };
}