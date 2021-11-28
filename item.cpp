#include "surface.h"

namespace planet{
    Item vectorItems::getItemByIndex(const size_t index) const{
        if(!(index < sizeVector))
            exit(EXIT_FAILURE);
        return Item((baseArr[index/4] >> (3 - index % 4) * 2) & 3);
    } 

    void vectorItems::changeItemByIndex(size_t index, Item elem){
        if (!(index < sizeVector)) 
            exit(EXIT_FAILURE);        
        baseArr[index / 4] -= ((baseArr[index / 4] >> (3 - index % 4) * 2) & 3) << ((3 - index % 4) * 2);
        baseArr[index / 4] += elem << (3 - index % 4) * 2;
    }

    size_t capacity() const{
        return sizeVector;
    }

    size_t cardinality() const{
        return sizeBaseArr;
    }

    vectorItems::ItemRef::ItemRef(size_t index, vectorItems& obj){
        itemIndex = index;
        vectorItemsObj = &obj;
    }

    vectorItems::ItemRef& vectorItems::ItemRef::operator=(Item elem){
        vectorItemsObj->changeItemByIndex(itemIndex, elem);
        return *this;
    }

    vectorItems::ItemRef::operator Item(){
        return vectorItemsObj->getItemByIndex(itemIndex);
    }

    vectorItems::ItemRef vectorItems::operator[](const size_t index){
        while (index >= this->sizeVector)
            this->push_back(Item::EMPTY);
        return ItemRef(index, *this);
    }

    void vectorItems::push_back(const Item elem){
        ++sizeVector;
        if(sizeVector > sizeBaseArr * 4)
            Push();
        baseArr[(sizeVector - 1) / 4] += (unsigned char)elem << (3 - (sizeVector - 1) % 4) *2;
    }

    vectorItems::vectorItems(const vectorItems& other){
        if(sizeVector > 0){
            delete baseArr;
            sizeVector = 0;
            sizeBaseArr = 0;
        }
        if(other.capacity() > 0)
            for(size_t i = 0; i < other.capacity(); ++i)
                this -> push_back(other.getItemByIndex(i));
        sizeVector = other.capacity();
        sizeBaseArr = other.cardinality();
    }

    vectorItems& vectorItems::operator=(const vectorItems& other){
        if(this == &other)
            return *this;
        if(sizeVector != 0){
            sizeVector = 0;
            sizeBaseArr = 0;
            delete[] baseArr;
        }
        for(size_t i = 0; i < other.capacity(); ++i)
            this -> push_back(other.getItemByIndex(i));
        return *this;
    }

    void randItem(size_t high, size_t width){
        size_t randh = rand() % high;
        size_t randw = rand() % width;
        (*this)[randh * width + randw] = Item(rand() % 3);
    }

    void randRock(size_t high, size_t width){
        size_t randh = rand() % high;
        size_t randw = rand() % width;
        (*this)[randh * width + randw] = Item(3);
    }
}