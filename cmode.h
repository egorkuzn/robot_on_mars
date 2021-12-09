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
            virtual void func();
        protected:
            size_t& x;
            size_t& y;
            size_t& id;
            data& server;
    };

    class ManualMode: public CMode{
        public:
            ManualMode(size_t& x,
                    size_t& y,
                    size_t& id,
                    data& server);
            void func() override;
    };

    class AutoMode: public CMode{
        public:
            AutoMode(size_t& x,
                    size_t& y,
                    size_t& id,
                    data& server);
            void func() override;
    };

    class ScanMode: public CMode{
        public:
            ScanMode(size_t& x,
                    size_t& y,
                    size_t& id,
                    data& server);
            void func() override;
    };
}