#pragma once

#include "data.h"
#include "cstdlib"

namespace planet{
    enum Item: unsigned char{
        EMPTY,
        APPLE,
        BOMB,
        ROCK
    };

    class vectorItems{
        public:
        vectorItems(){}
        ~vectorItems();
        size_t capacity() const;
        size_t cardinality() const;
        void push_back(const Item elem);
        class ItemRef{
            public:
            ItemRef(const size_t index, vectorItems& obj);
            ~ItemRef(){}
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
        void randItem(size_t high, size_t width);
        void randRock(size_t high, size_t width);
        private:
        unsigned char* baseArr = nullptr;
        size_t sizeBaseArr = 0;
        size_t sizeVector = 0;
        void Push();
        void Pop();         
    };
}