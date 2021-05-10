// Queue data structure implemented with linked list
// Created by Neal A.
#ifndef LQueue_h
#define LQueue_h
#include <iostream> // print error message
#include <cstdlib> // exit()
#include "Node.h"
template<class T>
class LQueue {
private:
    ListNode<T> *front;
    ListNode<T> *rear;
    int LQueueSize;
    void underflowError();
public:
    LQueue();
    ~LQueue();
    LQueue(const LQueue &sourceObject);
    int getLQueueSize() const;
    bool isEmpty();
    bool isEmpty() const;
    void addRear(const T &item);
    T popFront();
    void displayAll() const;
    class queueUnderflow{};
};

// Methods 

// Default Constructor
template<class T>
LQueue<T>::LQueue() {
    front = rear = nullptr;
    LQueueSize = 0;
}

// Copy Constructor
template<class T>
LQueue<T>::LQueue(const LQueue<T> &sourceObject) {
    front = nullptr;
    rear = nullptr;
    LQueueSize = 0;
    for(ListNode<T> *tempNode = sourceObject.front; tempNode != nullptr; tempNode = tempNode->next) {
        addRear(tempNode->data);
    }
}

//Destructor
template<class T>
LQueue<T>::~LQueue() {
    ListNode<T> *tempNode = front;
    while(tempNode != nullptr) {
	front = front->next;
	delete tempNode;
	tempNode = front;
    }
}

template<class T>
int LQueue<T>::getLQueueSize() const {
    return LQueueSize;
}

template<class T> 
bool LQueue<T>::isEmpty() {
    if(LQueueSize == 0) return true;
    return false;
}

template<class T> 
bool LQueue<T>::isEmpty() const {
    if(LQueueSize == 0) return true;
    return false;
}

template<class T>
void LQueue<T>::addRear(const T &item) {
    ListNode<T> *nNode = new ListNode<T>;
    nNode->data = item;
    nNode->next = nullptr;
    if(isEmpty()) {
        front = nNode;
    } else {
        rear->next = nNode;
    }
    rear = nNode;
    nNode = nullptr;
    LQueueSize++; 
}

template<class T>
T LQueue<T>::popFront() {
    if(isEmpty()) {
        throw queueUnderflow();
    }
    T item = front->data;
    LQueueSize--;
    if(isEmpty()) {
        delete front;
        front = nullptr;
        rear = nullptr;
    } else {
        ListNode<T> *tempNode = front->next;
        delete front;
        front = tempNode;
        tempNode = nullptr;
    }
    return item;
}

template<class T> 
void LQueue<T>::underflowError() {
    std::cout << "Queue Underflow" << std::endl;
    exit(1); // exit with error code 1
}

template<class T>
void LQueue<T>::displayAll() const {
    if(isEmpty()) {
        std::cout << "Queue is empty" << std::endl;
        return;
    }
    ListNode<T> *tempNode = front;
    while(tempNode != nullptr) {
        std::cout << tempNode->data << "->";
        tempNode = tempNode->next;
    }
    tempNode = nullptr;
    std::cout << std::endl;
}
#endif
