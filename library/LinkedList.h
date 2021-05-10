#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
template<class T>
class LinkedList {
private:
    ListNode<T> *front;
    ListNode<T> *rear;
    int ListSize;
public:
    LinkedList();
    LinkedList(const LinkedList &sourceObj);
    ~LinkedList();
    
    bool isEmpty();
    void addRear(const T &item); // using const pass by reference in case object passing is large
    void addFront(const T &item);
    void insert(const T &item, int afterNumNodes);
    void insertAscending(const T &item);
    void insertDescending(const T &item);
    int searchNode(T key);
    bool removeNode(T key);
    bool removeNodes(T key);
    class LLUnderflow{};
};

template<class T>
LinkedList<T>::LinkedList() {
    front = rear = nullptr;
    count = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &sourceObj) {
    this->front = this->rear = nullptr;
    count = 0;
    Node *tempPtr = sourceObj->front;
    while(tempPtr != nullptr) {
        this->addRear(tempPtr->elem);
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    if(isEmpty()) return;
    ListNode<T> *tempNode = front->next;
    while(front != nullptr) {
        delete front;
        front = tempNode;
        tempNode = tempNode->next;
        count--;
    }
}

template<class T>
bool LinkedList<T>::isEmpty() {
    if(count <= 0) return true;
    return false;
}

template<class T>
void LinkedList<T>::addRear(const T &item) {
    ListNode<T> *nListNode = new ListNode<T>;
    nListNode->data = item;
    if(isEmpty()) {
        front = rear = nListNode;
        nListNode->next = nullptr;
    } else {
        rear->next = nListNode;
        rear = nListNode;
    }
    count++;
}

template<class T>
void LinkedList<T>::addFront(const T &item) {
    ListNode<T> *nListNode = new ListNode<T>;
    nListNode->data = item;
    if(isEmpty()) {
        front = rear = nListNode;
        nListNode->next = nullptr;
    } else {
        nListNode->next = front;
        front = nListNode;
    }
    count++;
}

template<class T>
void LinkedList<T>::insertAscending(const T &item) {
    if(isEmpty()) {
        addRear(item);
        return;
    }
    for(ListNode<T> *prevNode = front, ListNode<T> *currNode = front->next; 
        currNode != nullptr && item > currNode->data; 
        curr = curr->next, prev = prev->next); // traverse the linked list
    
}

#endif