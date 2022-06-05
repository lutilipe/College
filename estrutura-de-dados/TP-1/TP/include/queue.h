#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "msgassert.h"

using namespace std;


template <class T>
class Queue;

template <class T>
class QueueNode {
    public:
        QueueNode<T>() { val = (T) 0; next = NULL; };
    private:
        QueueNode<T> *next;
        T val;
        friend class Queue<T>;
};

template <class T>
class Queue {
    private:
        QueueNode<T> *head;
        QueueNode<T> *tail;
        int length;
    public:
        Queue();
        ~Queue();

        void enqueue(T el);
        bool empty();
        T front();
        T dequeue();
        int size();
};

template <class T> Queue<T>::Queue() {
    head = new QueueNode<T>();
    tail = head;
    length = 0;
}

template <class T> Queue<T>::~Queue() {
    while(!empty()) {
        dequeue();
    }
    delete head;
}

template <class T> bool Queue<T>::empty() {
    return length == 0;
}

template <class T> void Queue<T>::enqueue(T el) {
    QueueNode<T> *n = new QueueNode<T>();
    n->val = el;
    tail->next = n;
    tail = n;
    length++;
}

template <class T> T Queue<T>::front() {
    erroAssert(!empty(), "Queue is empty!");

    return tail->val;
}

template <class T> T Queue<T>::dequeue() {
    erroAssert(!empty(), "Queue is empty!");

    T aux = head->next->val;
    QueueNode<T> *p = head;
    head = head->next;
    delete p;
    length--;
    return aux;
}

template <class T> int Queue<T>::size() {
    return length;
}

#endif
