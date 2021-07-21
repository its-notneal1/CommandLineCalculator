// Stack data structure implementation using linked list
// Created by Neal A
#ifndef LSTACK_H
#define LSTACK_H
#include <iostream> // print error
#include <cstdlib> // exit()
#include "Node.h"
// used to convert infix to postfix

template<class T>
class LStack {
private:
    ListNode<T> *top;
    int LStackSize;
public:
    LStack();
    ~LStack();
    T pop();
    void push(const T &item);
    int getLStackSize() const;
    bool isEmpty();
    bool isEmpty() const; // const version
    void displayAll();
    T getTop() const;
    class stackUnderflow{};
};

// Methods
/************************************
Default constructor points top
to nullptr
************************************/
template<class T>
LStack<T>::LStack() {
    top = nullptr;
    LStackSize = 0;
}
/**********************`**************
Destructor iterates through stack and
deletes all nodes not using pop
************************************/
template<class T>
LStack<T>::~LStack() {
    if(isEmpty()) return;
    ListNode<T> *tempNode = top->next;
    while(tempNode != nullptr) {
        delete top;
        top = tempNode;
        tempNode = tempNode->next;
    }
}

/************************************
Returns the current size of the stack
(number of elements)
************************************/
template<typename T>
int LStack<T>::getLStackSize() const {
    return LStackSize;
}

/************************************
Check if stack is empty
************************************/
template<class T>
bool LStack<T>::isEmpty() {
    if(LStackSize <= 0) return true; 
    return false;
}

template<class T>
bool LStack<T>::isEmpty() const {
    if(LStackSize <= 0) return true;
    return false;
}

/************************************
Push new item into stack
************************************/
template<class T>
void LStack<T>::push(const T &item) {
    ListNode<T> *nNode = new ListNode<T>;
    nNode->data = item;
    if(isEmpty()) {
        nNode->next = nullptr;
    } else {
        nNode->next = top;
    }
    top = nNode;
    nNode = nullptr;
    LStackSize++; // increment the size of the stack
}

/************************************
Pop the top element of the stack
************************************/
template<class T>
T LStack<T>::pop() {
    if(isEmpty()) {
        std::cout << "Stack Underflow" << std::endl;
        throw stackUnderflow();
        exit(1);
    }
    T item = top->data;
    LStackSize--;
    if(isEmpty()) {
        delete top;
        top = nullptr;
    } else {
        ListNode<T> *tempNode = top->next;
        delete top;
        top = tempNode;
        tempNode = nullptr;
    }
    return item;
}

template<class T>
void LStack<T>::displayAll() {
    if(isEmpty()) std::cout << "Stack Is Empty" << std::endl;
    ListNode<T> *tempNode = top;
    while(tempNode != nullptr) {
        std::cout << tempNode->data << "->";
        tempNode = tempNode->next;
    }
    std::cout << std::endl;
}

template<class T>
T LStack<T>::getTop() const {
    if(isEmpty()) {
        std::cout << "Stack is empty" << std::endl;
    }
    return top->data;
}

#endif
