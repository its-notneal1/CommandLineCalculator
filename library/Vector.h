// self implemented vector
#ifndef VECTOR_H
#define VECTOR_H

template<class T>
class Vector {
private:
    T *array;
    unsigned int arraySize; // the size of the vector
    unsigned int count; // number of elements inside dynamic array
    
    int getArraySize() const;
    void allocateArraySize();
    void copyArray();
public:
    Vector();
    ~Vector();
    Vector(const Vector &sourceObject);
    int size() const; // the number of elements
    void push_back(T item);
    void clear();
};

template<class T>
Vector<T>::Vector() { // initialize as empty variable
    array = nullptr;
    count = 0; 
    arraySize = 1;
}

template<class T>
Vector<T>::~Vector() {
    if(array == NULL) {
        return;
    }
}

template<class T>
void Vector<T>::allocateArraySize() {
    if(count < arraySize - 1) return;
    arraySize *= 2; // double the array size
    T tempArray[arraySize] = new T;
}

template<class T>
void Vector<T>::push_back(T item) {
    if(size == arraySize) { // allocate more memory
        allocateArraySize();
    }
}




#endif