#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "msgassert.h"
#include "memlog.h"

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
        int id = -1;
        StackNode<T> *head;
        int length;
    public:
        Stack(int i);
        ~Stack();

        void push(T el);
        bool empty();
        void clean();
        T pop();
        int size();
        T top();
};

template <class T> Stack<T>::Stack(int i) {
    id = i;
    head = new StackNode<T>();
    length = 0;
}

template <class T> void Stack<T>::clean() {
    while(!empty()) {
        pop();
    }
}

template <class T> Stack<T>::~Stack() {
    Stack::clean();
    delete head;
}

template <class T> bool Stack<T>::empty() {
    LEMEMLOG((long int)(&(length)),sizeof(int),Stack::id);
    return length == 0;
}

template <class T>void Stack<T>::push(T el) {
    StackNode<T> *n = new StackNode<T>();
    LEMEMLOG((long int)(&(head->next)),sizeof(StackNode<T>),Stack::id);
    StackNode<T> *tmp = head->next;
    n->val = el;
    ESCREVEMEMLOG((long int)(&(head->next)),sizeof(StackNode<T>),Stack::id);
    head->next = n;
    n->next = tmp;
    length++;
}

template <class T>T Stack<T>::pop() {
    erroAssert(!empty(), "Stack is empty!");

    LEMEMLOG((long int)(&(head->next)),sizeof(StackNode<T>),Stack::id);
    StackNode<T> *tmp = head->next;
    T v = tmp->val;
    ESCREVEMEMLOG((long int)(&(head->next)),sizeof(StackNode<T>),Stack::id);
    head->next = tmp->next;
    delete tmp;
    length--;
    return v;
}

template <class T>T Stack<T>::top() {
    erroAssert(!empty(), "Stack is empty!");
    LEMEMLOG((long int)(&(head->next->val)),sizeof(T),Stack::id);
    return this->head->next->val;
}

template <class T> int Stack<T>::size() {
    LEMEMLOG((long int)(&(length)),sizeof(int),Stack::id);
    return length;
}

#endif
