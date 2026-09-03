#pragma once

#include <cstddef>

class CustomLinkedList
{
private:
    struct Node
    {
        int data;
        Node* next;

        Node(int value);
    };

//Iterator
class Iterator{
    private:
        Node *current_;
        public:
            explicit Iterator(Node *node);
            int& operator*();
            Iterator& operator++();
            bool operator!=(const Iterator& other) const;
};

// cosnt Iterator calss 
class ConstIterator
{
private:
    const Node* current_;

public:
    explicit ConstIterator(const Node* node);
    const int& operator*() const;
    ConstIterator& operator++();
    bool operator!=(const ConstIterator& other) const;
};

    Node* head_;
    Node* tail_;
    std::size_t size_;

public:

std::size_t size() const;
    CustomLinkedList();
    //pushfront()
    void push_front(int value);
    //push_back()
    void push_back(int value);
    // pop_front()
    void pop_front();
    // pop_back()
    void pop_back();
    //clear()
    void clear();
    // destructor
    ~CustomLinkedList();
    // copy constructor
    CustomLinkedList(const CustomLinkedList &other);
    //copy Assignment operator
    CustomLinkedList &operator=(const CustomLinkedList &other);
    // Move constructor
    CustomLinkedList(CustomLinkedList &&other);
    //Move Assignment Operator
    CustomLinkedList &operator=(CustomLinkedList &&other);

    //=============================//====================

    //Starting the Basic read/access API

    int&front();
    int &back();
     // const-correct front()/back()
    const int& front() const;
    const int& back() const;
    bool empty() const;
    
    bool find(int value) const;

    // insert()
    void insert(std::size_t index, int value);
    //erase()
    void erase(std::size_t index);
    //operator[]
    int& operator[](std::size_t index);
const int& operator[](std::size_t index) const;
//begin()
Iterator begin();
// end()
Iterator end();
// const begin() and cosnt end()
ConstIterator begin() const;
ConstIterator end() const;
// at() 
int& at(std::size_t index);
const int& at(std::size_t index) const;

};




