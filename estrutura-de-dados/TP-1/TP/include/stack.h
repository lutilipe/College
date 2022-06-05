#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "msgassert.h"

using namespace std;

template <class T>
class Stack;

template <class T>
class StackNode {
    public:
        StackNode() { val = (T) 0; next = NULL; };
    private:
        T val;
        StackNode<T> *next;
        friend class Stack<T>;
};

template <class T>
class Stack {
    private:
        StackNode<T> *head;
        int length;
    public:
        Stack();
        ~Stack();

        void push(T el);
        bool empty();
        T pop();
        int size();
        T top();
};

template <class T> Stack<T>::Stack() {
    head = new StackNode<T>();
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
    StackNode<T> *n = new StackNode<T>();
    StackNode<T> *tmp = head->next;
    n->val = el;
    head->next = n;
    n->next = tmp;
    length++;
}

template <class T>T Stack<T>::pop() {
    erroAssert(!empty(), "Stack is empty!");

    StackNode<T> *tmp = head->next;
    T v = tmp->val;
    head->next = tmp->next;
    delete tmp;
    length--;
    return v;
}

template <class T>T Stack<T>::top() {
    erroAssert(!empty(), "Stack is empty!");

    return this->head->next->val;
}

template <class T> int Stack<T>::size() {
    return length;
}

#endif
