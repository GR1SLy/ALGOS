#ifndef LIST_H
#define LIST_H
#include <iostream>
using namespace std;

#pragma once

template<typename T>
class List
{
    template<typename T1>
    struct Node 
    {
        T1 value;
        Node* next;
        Node() { value = T(); next = nullptr; }
        Node(T1 val) : Node() { value = val; }
        Node(T1 val, Node* n) : Node(val) { next = n; }
    };

    Node<T>* head;
    Node<T>* tail;
    int count;

public:

    struct iterator
    {
        iterator() { node = nullptr; }
        iterator(Node<T>* n) { node = n; }
        T operator*() { return node->value; }
        iterator& operator++() { node = node->next; return *this; }
        bool operator!=(const iterator& other) { return node != other.node; }
        bool operator==(const iterator& other) { return node == other.node; }
    private:
        Node<T> *node;
    };

    List();
    List(const List<T>& other);
    ~List();
    int size();
    void clear();
    bool empty();
    bool contains(T value);
    T at(int index);
    void swap_to(T value, int index);
    iterator find(T value);
    void push_front(T value);
    void insert_after(int index, T value);
    void pop_front();
    void erase_after(int index);
    iterator begin();
    iterator end();

    void print();
};

#endif

template <typename T>
inline List<T>::List()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <typename T>
inline List<T>::List(const List &other) : List<T>::List()
{
    if (other.head == nullptr) return;
    this->count = other.count;
    this->head = new Node<T>(other.head->value);
    Node<T>* other_current = other.head;
    Node<T>* this_current = this->head;
    while (other_current->next != other.head) {
        this_current->next = new Node<T>(other_current->next->value);
        this_current = this_current->next;
        other_current = other_current->next;
    }
    this_current->next = this->head;
    this->tail = this_current;
}

template <typename T>
inline List<T>::~List()
{
    this->clear();
}

template <typename T>
inline int List<T>::size()
{
    return count;
}

template <typename T>
inline void List<T>::clear()
{
    if (this->empty()) return;
    Node<T>* current = head;
    Node<T>* prev = head;
    while (current->next != head) {
        prev = current;
        current = current->next;
        delete prev;
    }
    delete current;
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template <typename T>
inline bool List<T>::empty()
{
    return head == nullptr;
}

template <typename T>
inline bool List<T>::contains(T value)
{
    Node<T>* current = head;
    while (current->next != head) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }
    if (current->value == value) {
        return true;
    }
    return false;
}

template <typename T>
inline T List<T>::at(int index)
{
    if (index < 0 || index >= count) {
        throw std::out_of_range("At index out of range");
    }
    Node<T>* current = head;
    for (int i = 0; i < count; ++i, current = current->next) {
        if (i == index) {
            return current->value;
        }
    }
    return T();
}

template <typename T>
inline void List<T>::swap_to(T value, int index)
{
    if (index < 0 || index >= count) {
        throw std::out_of_range("Swap index out of range");
    }
    Node<T>* current = head;
    for (int i = 0; i < count; ++i, current = current->next) {
        if (i == index) {
            current->value = value;
            return;
        }
    }
}

template <typename T>
inline typename List<T>::iterator List<T>::find(T value)
{
    Node<T>* current = head;
    while (current->next != head) {
        if (current->value == value) {
            return iterator(current);
        }
        current = current->next;
    }
    if (current->value == value) return iterator(current);
    return this->end();
}

template <typename T>
inline void List<T>::push_front(T value)
{
    if (this->empty()) {
        head = new Node<T>(value);
        tail = head;
        tail->next = head;
    }
    else {
        Node<T>* old_head = head;
        head = new Node<T>(value, old_head);
        tail->next = head;
    }
    count++;
}

template <typename T>
inline void List<T>::insert_after(int index, T value)
{
    if (index < 0 || index >= count) {
        throw std::out_of_range("Insert index out of range");
    }
    Node<T>* current = head;
    for (int i = 0; i < count; ++i, current = current->next) {
        if (i == index) {
            Node<T>* new_node = new Node<T>(value, current->next);
            current->next = new_node;
            if (current == tail) tail = new_node;
            count++;
            return;
        }
    }
}

template <typename T>
inline void List<T>::pop_front()
{
    if (this->empty()) return;
    if (head == tail) this->clear();
    else {
        Node<T>* old_head = head;
        head = head->next;
        delete old_head;
        tail->next = head;
    }
    count--;
}

template <typename T>
inline void List<T>::erase_after(int index)
{
    if (index < 0 || index >= count - 1) {
        throw std::out_of_range("Erase index out of range");
    }
    Node<T>* current = head;
    for (int i = 0; i < count; ++i, current = current->next) {
        if (i == index) {
            Node<T>* erasing_node = current->next;
            current->next = current->next->next;
            if (erasing_node == tail) tail = current;
            delete erasing_node;
            count--;
            return;
        }
    }
}

template <typename T>
inline typename List<T>::iterator List<T>::begin()
{
    return iterator(head);
}

template <typename T>
inline typename List<T>::iterator List<T>::end()
{
    return iterator(tail);
}

template <typename T>
inline void List<T>::print()
{
    if (this->empty()) return;
    Node<T>* current = head;
    while (current->next != head) {
        cout << current->value << endl;
        current = current->next;
    }
    cout << current->value << endl;
    cout << "Head: " << head->value << "\tTail: " << tail->value << endl;
}
