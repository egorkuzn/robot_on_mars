#pragma once

#include <cstdlib>
#include <ctime>

namespace planet{
    enum Item: unsigned char{
        APPLE,
        BOMB,
        ROCK,
        EMPTY
    };

    class vectorItems{
        public:
        vectorItems(size_t length);
        ~vectorItems();
        size_t capacity() const;
        size_t cardinality() const;
        void push_back(const Item elem);
        class ItemRef{
            public:
            ItemRef(const size_t index, vectorItems& obj);
            ~ItemRef();
            ItemRef& operator= (Item elem);
            operator Item();
            private:
            size_t itemIndex;
            vectorItems* vectorItemsObj;
        };
        Item getItemByIndex(const size_t index) const;
        void changeItemByIndex(const size_t index, Item elem);
        vectorItems& operator=(const vectorItems& other);
        vectorItems(const vectorItems& other);
        ItemRef operator[](size_t index);
        private:
        void randItem();
        void randEmpty();
        void genItems();
        void genTerrain();
        unsigned char* baseArr = nullptr;
        size_t length;
        size_t sizeBaseArr = 0;
        size_t sizeVector = 0;
        void Push();
        void Pop();         
    };
}