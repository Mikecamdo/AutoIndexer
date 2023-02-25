//
// Created by mikec_g1kgiu8 on 9/14/2021.
//

#ifndef INC_21F_PA02_DSVECTOR_H
#define INC_21F_PA02_DSVECTOR_H

#include <iostream>

template <typename T>
class DSVector {
    private:
        int capacity; //how large the array inside the vector is
        int size; //how many elements are in the vector
        T* data;

        void resize(); //private function that resizes the array
        int getCapacity() const; //private function that returns the capacity of the array


public:
        //Constructors/Destructor
        DSVector(int initial = 10); //constructor, default size is set to 10
        DSVector(const DSVector&); //copy constructor
        ~DSVector(); //destructor

        //Functions
        void push_back(const T&); //adds to the end of the vector
        int length() const; //returns the size of the vector
        void erase(int); //erases an element from the vector
        const T& at(int) const; //returns the element at a specified location
        int find(T) const; //returns the first location of the specified element

        //Overloaded Operators
        DSVector& operator = (const DSVector&);
        const T& operator[] (int) const;
};

template <typename T>
DSVector<T>::DSVector (int initial) {
    capacity = initial; //initial capacity is value passed to constructor (or 10 if no value is passed)
    size = 0; //initially 0 elements in the vector
    data = new T[initial]; //creates an array with size capacity
}

template <typename T>
DSVector<T>::DSVector (const DSVector<T>& arg) { //copies the passed along DSVector's values into the new DSVector
    capacity = arg.getCapacity();
    size = arg.length();
    data = new T[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = arg[i];
    }
}

template <typename T>
DSVector<T>::~DSVector() { //destructor
    delete[] data;
}

template <typename T>
void DSVector<T>::push_back(const T& val) { //adds a passed along value to the end of the vector
    if (size == capacity) { //resizes the internal array when it runs out of space
        resize();
    }
    data[size++] = val;
}

template <typename T>
void DSVector<T>::resize() { //creates a new internal array with 10 more locations and copies everything to the new array
    capacity += 10;
    T* temp = new T[capacity];
    for (int i = 0; i < size; i++) {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
}

template <typename T>
int DSVector<T>::length() const { //returns the size of the vector
    return size;
}

template <typename T>
void DSVector<T>::erase(int index) { //removes an element from the vector
    size -= 1; //decrease size by 1
    T* temp = new T[capacity]; //create a new array
    for (int i = 0; i < index; i++) { //copies all values before the deleted value to the new array
        temp[i] = data[i];
    }
    for (int i = index; i < size; i++) { //copies all values after the deleted value to the new array
        temp[i] = data[i + 1];
    }
    delete[] data; //deletes the old array
    data = temp;
}

template <typename T>
const T & DSVector<T>::at(int index) const {
    if (index < 0 || index > size - 1) { //throws an out_of_range error if data[index] does not exist
        throw std::out_of_range("Attempting to access an out of bounds element");
    }
    return data[index]; //returns the element at index
}

template <typename T>
int DSVector<T>::find(T element) const{
    for (int i = 0; i < size; i++) {
        if (data[i] == element) {
            return i; //returns the first location of the passed along element
        }
    }
    return -1; //returns -1 if not found (permissible because an index location cannot be negative)
}

template <typename T>
int DSVector<T>::getCapacity() const{
    return capacity; //returns the capacity of the array
}

template <typename T>
DSVector<T>& DSVector<T>::operator=(const DSVector& arg) { //copies the passed vector's values to the current vector
    delete[] data; //deletes the old array
    data = new T[arg.getCapacity()]; //creates a new array with arg's capacity
    capacity = arg.getCapacity();
    size = arg.length();
    for (int i = 0; i < size; i++) { //copies all values from arg to the current array
        data[i] = arg[i];
    }
    return *this;
}

template <typename T>
const T& DSVector<T>::operator[] (int index) const {
    if (index < 0 || index > size - 1) { //throws an out_of_range error if data[index] does not exist
        throw std::out_of_range("Attempting to access an out of bounds element");
    }
    return data[index];  //returns the element at index
}


#endif //INC_21F_PA02_DSVECTOR_H
