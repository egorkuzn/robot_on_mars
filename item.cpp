#include "item.h"

namespace planet{
    Item vectorItems::getItemByIndex(const size_t index) const{
        if(!(index < sizeVector))
            exit(EXIT_FAILURE);
        return Item((baseArr[index/4] >> (3 - index % 4) * 2) & 3);
    } 

    vectorItems::~vectorItems(){
        delete[] baseArr;
    }

    vectorItems::ItemRef::~ItemRef(){}

    void vectorItems::Push(void) {
        if (sizeBaseArr == 0) {
            baseArr = new unsigned char[1];	
            baseArr[0] = 0;
            ++sizeBaseArr;
        } else {
            unsigned char* newArr = new unsigned char[sizeBaseArr * 2];

            for (size_t i = 0; i < sizeBaseArr; ++i) 
                newArr[i] = baseArr[i];
            
            for (size_t i = sizeBaseArr; i < sizeBaseArr * 2; ++i) 
                newArr[i] = 0;
            
            sizeBaseArr *= 2;
            delete[] baseArr;
            baseArr = newArr;
        }
    }

    void vectorItems::Pop(void) {
		if (sizeBaseArr > 1) {
			unsigned char* newArr = new unsigned char[--sizeBaseArr];
			
            for (size_t i = 0; i < sizeBaseArr; ++i)
				newArr[i] = baseArr[i];
						
			delete[] baseArr;
			baseArr = newArr;
		} else {
			delete[] baseArr;
			--sizeBaseArr;
		}
	}

    void vectorItems::changeItemByIndex(size_t index, Item elem){
        if (!(index < sizeVector)) 
            exit(EXIT_FAILURE);        
        baseArr[index / 4] -= ((baseArr[index / 4] >> (3 - index % 4) * 2) & 3) << ((3 - index % 4) * 2);
        baseArr[index / 4] += elem << (3 - index % 4) * 2;
    }

    size_t vectorItems::capacity() const{
        return sizeVector;
    }

    size_t vectorItems::cardinality() const{
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
            this->push_back(Item::ROCK);
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

    void vectorItems::randItem(){        
        (*this)[rand() % length] = Item(rand() % 2 + 1);
    }

    void vectorItems::randEmpty(){
        (*this)[rand() % length] = EMPTY;
    }

    void vectorItems::genItems(void){
        size_t chances = length / 20;
        for(chances; chances > 0; --chances)
            (*this).randItem();
    }

    void vectorItems::genTerrain(void){
        size_t chances = length / 1.5;
        for(chances; chances > 0; --chances)
            (*this).randEmpty();
    }    

    vectorItems::vectorItems(size_t length) : length(length){
        if(length > 0){
            (*this)[length - 1]; // firstly: filling vector by rocks
            srand(time(NULL));
            genTerrain(); // then gen empty places
            genItems(); // add bombs and apples
        }
    }
}