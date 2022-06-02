#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "msgassert.h"

using namespace std;

template <class T>
class Stack;

template <class T>
class Node {
    public:
        Node() { val = (T) 0; next = NULL; };
    private:
        T val;
        Node<T> *next;
        friend class Stack<T>;
};

template <class T>
class Stack {
    private:
        Node<T> *head;
        int length;
    public:
        Stack();
        ~Stack();

        void push(T el);
        bool empty();
        T pop();
        int size();
};

template <class T> Stack<T>::Stack() {
    head = new Node<T>();
    length = 0;
}

template <class T> Stack<T>::~Stack() {
    while(!empty()) {
        pop();
    }
    delete head;
}

template <class T> bool Stack<T>::empty() {
    return length == 0;
}

template <class T>void Stack<T>::push(T el) {
    Node<T> *n = new Node<T>();
    Node<T> *tmp = head->next;
    n->val = el;
    head->next = n;
    n->next = tmp;
    length++;
}

template <class T>T Stack<T>::pop() {
    erroAssert(!empty(), "Trying to remove from an empty stack!");

    Node<T> *tmp = head->next;
    T v = tmp->val;
    head->next = tmp->next;
    delete tmp;
    length--;
    return v;
}

template <class T> int Stack<T>::size() {
    return length;
}

#endif
