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
            CMode(size_t& id,
                size_t& idxInCollectors,
                data& server);
            virtual void func() = 0;
            virtual ~CMode();
        protected:
            void goInRandWay();
            bool isUnknownArea();
            void scan();
            size_t& id;
            size_t& idxInCollectors;
            data& server;
    };

    class ManualMode: public CMode{
        public:
            ManualMode(size_t& id,
                    size_t& idxInCollectors,
                    data& server);
            void func() override;
            ~ManualMode() override;
    };

    class AutoMode: public CMode{
        public:
            AutoMode(size_t& id,
                    size_t& idxInCollectors,
                    data& server);
            void func() override;
            ~AutoMode() override;
        private:
            bool isAnyAppleFound();
            void collectNearestApple();
            std::vector<Direction> way;
    };

    class ScanMode: public CMode{
        public:
            ScanMode(size_t& id,
                    size_t& idxInCollectors,
                    data& server);
            void func() override;
            ~ScanMode() override;
    };
}