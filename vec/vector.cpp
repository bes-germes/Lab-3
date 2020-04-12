#include <cassert>
#include "Vector.h"

MyVector::MyVector(size_t size, ResizeStrategy strategy,float coef){
    this->_size = size;
    this->_capacity = 1;
    this->_data = nullptr;
    this->_coef = coef;
    this->_strategy = strategy;
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strategy, float coef){
    this->_coef = coef;
    this->_size = 0;
    this->_capacity = 1;
    for(int i = 0; i < size; i++)
        this->pushBack(value);
    this->_strategy = strategy;
}

MyVector::MyVector(const MyVector& copy){
    this->_coef = copy._coef;
    delete [] _data;
    this->_size = 0;
    this->_capacity = 1;
    for (int i = 0; i < copy._size; i++)
        this->pushBack(copy[i]);
}

MyVector& MyVector::operator=(const MyVector& copy){
    this->_size = copy._size;
    this->_capacity = copy._capacity;
    this->_data = copy._data;
    this->_strategy = copy._strategy;
    return *this;
}

MyVector::~MyVector(){
    delete [] _data;
    this->_data = nullptr;
    this->_size = 0;
    this->_capacity = 0;
}

size_t MyVector::capacity() const{
    return this->_capacity;
}

size_t MyVector::size() const{
    return  this->_size;
}

float MyVector::loadFactor(){
    if(this->_size/this->_capacity > 1){
        this->_capacity * this->_coef;
        float k = this->_capacity * this->_coef;
        return k;
    }
    else if(this->_size/this->_capacity < 1/(this->_coef * this->_coef)){
        this->_capacity / this->_coef;
        float k = this->_capacity / this->_coef;
        return k;
    }
}

ValueType& MyVector::operator[] (const size_t i) const{
    return _data[i];
}

void MyVector::pushBack(const ValueType& value){
    if(this->_capacity == 1)
        reserve(2);
    else if(this->_size + 2 > this->_capacity)
        reserve(this->_capacity * this->_coef);
    this->_data[_size] = value;
    this->_size++;
}

void MyVector::pushFront(const ValueType& value){
    if(this->_capacity == 1)
        reserve(2);
    else if(this->_size + 2 > this->_capacity)
        reserve(this->_capacity * this->_coef);
    int a = this->_data[0], b;
    for(int i = 1; i < this->_size + 1; i++) {
        b = this->_data[i];
        this->_data[i] = a;
        a = b;
    }
    this->_data[0] = value;
    this->_size++;
}

void MyVector::insert(const size_t index, const ValueType& value){
    if(index < 0 || index >= this->_size)
        assert(index<0 || index >= this->_size);
    else if(index == 0){
        pushFront(value);
    }
    else if(index == this->_size - 1){
        pushBack(value);
    }
    else if (index < this->_size) {
        if (loadFactor())
            reserve(loadFactor());
        ValueType a1, a2;
        a1 = this->_data[index];
        this->_data[index] = value;
        for (int i = index; i < this->_size - 1; i++) {
            a2 = this->_data[i + 1];
            this->_data[i + 1] = a1;
            a1 = a2;
        }
        this->_data[this->_size] = a1;
        this->_size++;
    }
    else {
        pushBack(value);
    }
}

void MyVector::insert(const size_t index, const MyVector& vector){
    for(int i = 0; i < vector._size; i++){
        this->insert(index + i, vector[i]);
    }
}

void MyVector::popBack(){
    this->_data[_size - 1] = NULL;
    this->_size--;
}

void MyVector::erase( const size_t index){
    if(index < 0)
        assert(index < 0);
    if (index < this->_size) {
        for (int i = index; i < _size; i++)
            this->_data[i] = this->_data[i + 1];
        this->_size--;
    }
}

void MyVector::erase( const size_t index, const size_t len){
    if(index < 0)
        assert(index < 0);
    else if (index < this->_size) {
        for(int i = 0; i < len; i++){
            erase(index);
        }
    }
}

void MyVector::reserve(const size_t capacity){
    this->_capacity = (this->_capacity == 0) ? 1 : this->_capacity;
    while (this->_capacity < capacity)
        this->_capacity ++;
    if (this->_data == 0)
        this->_data = new ValueType[this->_capacity];
    else {
        ValueType* newData = new ValueType[this->_capacity];
        memcpy(newData, _data, this->_size * sizeof(ValueType));
        delete [] _data;
        this->_data = newData;
    }
}

long long int MyVector::find(const ValueType& value, bool isBegin) const {
    if (isBegin == true) {
        for (int i = 0; i < this->_capacity; i++) {
            if (this->_data[i] == value) {
                return i;
            }
        }
    }
    else {
        for (int i = this->_capacity; i > 0; i--) {
            if (this->_data[i] == value) {
                return i;
            }
        }
    }
    return -1;
}

void MyVector::resize(const size_t size, const ValueType){
    if(size > this->_size) {
        reserve(size);
        ValueType * new_data = new ValueType[size];
        memcpy(new_data, this->_data, size * sizeof(ValueType));
        delete[] this->_data;
        this->_data = new_data;
        for(int i = this->_size; i < size; i++){
            this->_data[i] = 0;
        }
        this->_size = size;
    }
    else{
        ValueType * new_data = new ValueType[size];
        memcpy(new_data, this->_data, size * sizeof(ValueType));
        delete[] this->_data;
        this->_data = new_data;
        this->_size = size;
    }
}

void MyVector::clear(){
    erase(0, this->_size);
}

void MyVector::print(){
    std::cout << "size: " << this->_size << "\n";
    std::cout << "capacity: " << this->_capacity << "\n";
    for(int i = 0 ; i < this->_size; i++)
        std::cout << "[" << i << "] - " << this->_data[i] << "\n";
    std::cout << "\n";
}

MyVector sortedSquares(const MyVector& vec, bool strategy){
    MyVector vector;
    if (strategy){
        int i = 0;
        MyVector vc;
        while(vec[i] < 0) {
            vc.pushFront(abs(vec[i]));
            i++;
        }
        int vcSize = vc.size();
        int vecSize = vec.size();
        int j = 0;
        for(; i < vecSize && j < vcSize; i++) {
            int a = 0;
            if (vec[i] < vc[j]) {
                a = vec[i] * vec[i];
                vector.pushBack(a);
            }
            else if(vec[i] > vc[j]){
                a = vc[j] * vc[j];
                vector.pushBack(a);
                j++;
            }
            else {
                a = vc[j] * vc[j];
                vector.pushBack(a);
                vector.pushBack(a);
                j++;
            }
        }
        for(; i < vecSize; i++) {
            int a = vec[i] * vec[i];
            vector.pushBack(a);
        }
        for(; j < vcSize; j++) {
            int a = vc[j] * vc[j];
            vector.pushBack(a);
        }
    }
    else{
        int i = 0;
        MyVector vc;
        while(vec[i] < 0) {
            vc.pushFront(abs(vec[i]));
            i++;
        }
        int vcSize = vc.size();
        int vecSize = vec.size();
        int j = 0;
        for(; i < vecSize && j < vcSize; i++) {
            int a = 0;
            if (vec[i] < vc[j]) {
                a = vec[i] * vec[i];
                vector.pushFront(a);
            }
            else if(vec[i] > vc[j]){
                a = vc[j] * vc[j];
                vector.pushFront(a);
                j++;
            }
            else{
                a = vc[j] * vc[j];
                vector.pushFront(a);
                vector.pushFront(a);
                j++;
            }
        }
        for(; i < vecSize; i++) {
            int a = vec[i] * vec[i];
            vector.pushFront(a);
        }
        for(; j < vcSize; j++) {
            int a = vc[j] * vc[j];
            vector.pushFront(a);
        }
    }
    return vector;
}

ValueType* Vector::begin(){
    return _data;
}

ValueType* Vector::end(){
    return _data + _size;
}
