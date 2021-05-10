// ListNode Class for Linked List implementation
#ifndef NODE_H
#define NODE_H
template<class T>
class ListNode {
template<typename S> friend class LQueue;
template<typename U> friend class LStack;
private:
    T data;
    ListNode *next;
};
#endif
