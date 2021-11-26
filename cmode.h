#pragma once 

#include "ui.h"
#include "data.h"

namespace planet{
    enum class CModeT{
        AUTO,
        MAN,
        SCAN
    };

    class CMode{
        public:
            virtual void func(data& server);
    };

    class ManualMode: public CMode{
        public:
            ManualMode(data& server);
            void func(data& server) override;
    };

    class AutoMode: public CMode{
        public:
            AutoMode(data& server);
            void func(data& server) override;
    };

    class ScanMode: public CMode{
        public:
            ScanMode(data& server);
            void func(data& server) override;
    };
}