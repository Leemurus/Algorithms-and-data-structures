#pragma once
#include <bits/unique_ptr.h>

template <class Struct, class ValueType>
class StackIterator: public std::iterator <std::input_iterator_tag, Struct> {
private:
    Struct *p;

    explicit StackIterator (Struct *p);
public:
    StackIterator (const StackIterator &it);

    StackIterator& operator++();

    StackIterator& operator++(int);

    bool operator!=(StackIterator &other) const;

    bool operator==(StackIterator &other) const;

    ValueType operator*() const;

    template <class T>
    friend class Stack;
};

template <class ValueType>
class Stack {
private:
    struct Node {
        Node *prev;
        ValueType value;
        explicit Node (Node *link) : prev(link) {}
    };

    Node *head, *tail;

public:
    Stack();

    ~Stack();

    typedef StackIterator <Node, ValueType> iterator;

    iterator begin();

    iterator end();

    void push(ValueType value);

    void pop();
};

template<class ValueType>
Stack<ValueType>::Stack() {
    this -> tail = new Node(nullptr);
    head = new Node(tail);
}

template<class ValueType>
Stack<ValueType>::~Stack() {
    while (head != tail) {
        this -> pop();
    }
    this -> pop();
}

template<class ValueType>
typename Stack<ValueType>::iterator Stack<ValueType>::begin() {
    return iterator(head -> prev);
}

template<class ValueType>
typename Stack<ValueType>::iterator Stack<ValueType>::end() {
    return iterator(tail);
}

template<class ValueType>
void Stack<ValueType>::push(ValueType value) {
    head -> value = value;
    Node *newHead = new Node(head);
    head = newHead;
}

template<class ValueType>
void Stack<ValueType>::pop() {
    Node *newHead = head -> prev;
    delete head;
    tail = newHead;
}

template <class Struct, class ValueType>
StackIterator<Struct, ValueType>::StackIterator(Struct *p) : p(p) {}

template <class Struct, class ValueType>
StackIterator<Struct, ValueType>::StackIterator(const StackIterator &it) : p(it.p) {}

template <class Struct, class ValueType>
StackIterator<Struct, ValueType>& StackIterator<Struct, ValueType>::operator++() {
    p = p -> prev;
    return *this;
}

template<class Struct, class ValueType>
StackIterator<Struct, ValueType>& StackIterator<Struct, ValueType>::operator++(int) {
    p = p -> prev;
    return *this;
}

template<class Struct, class ValueType>
bool StackIterator<Struct, ValueType>::operator!=(StackIterator &other) const {
    return p != other.p;
}

template<class Struct, class ValueType>
bool StackIterator<Struct, ValueType>::operator==(StackIterator &other) const {
    return p == other.p;
}

template<class Struct, class ValueType>
ValueType StackIterator<Struct, ValueType>::operator*() const {
    return p->value;
}