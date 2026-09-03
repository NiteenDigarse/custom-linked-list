#include "CustomLinkedList.h"
#include <stdexcept>

CustomLinkedList::Node::Node(int value)
    : data(value), next(nullptr)
{
}

CustomLinkedList::CustomLinkedList()
    : head_(nullptr),
      tail_(nullptr),
      size_(0)
{
}

std::size_t CustomLinkedList::size() const
{
    return size_;
}

// PushFront()
void CustomLinkedList::push_front(int value)
{
    Node *newNode = new Node(value);

    // handling the empty list case
    if (head_ == nullptr)
    {
        head_ = newNode;
        tail_ = newNode;
    }
    else
    {
        newNode->next = head_;
        head_ = newNode;
    }
    ++size_;
}

// push_back()

void CustomLinkedList::push_back(int value)
{
    Node *newNode = new Node(value);

    if (head_ == nullptr)
    {
        head_ = newNode;
        tail_ = newNode;
    }
    else
    {
        tail_->next = newNode;
        tail_ = newNode;
    }
    ++size_;
}

// pop-front()
void CustomLinkedList::pop_front()
{

    if (head_ == nullptr)
    {
        return;
    }
    Node *oldHead = head_;
    head_ = head_->next;

    delete oldHead;
    --size_;

    if (head_ == nullptr)
    {
        tail_ = nullptr;
    }
}

// pop-back()

void CustomLinkedList::pop_back()
{
    if (head_ == nullptr)
    {
        return;
    }

    // Only one node
    if (head_ == tail_)
    {
        delete head_;

        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;

        return;
    }

    // Find the node before tail

    Node *current = head_;

    while (current->next != tail_)
    {
        current = current->next;
    }
    delete tail_;

    tail_ = current;
    tail_->next = nullptr;
    --size_;
}

// clear()
void CustomLinkedList::clear()
{
    Node *current = head_;

    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;

        current = next;
    }

    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

// destructor
CustomLinkedList::~CustomLinkedList()
{
    clear();
};

// copy cosntructor
CustomLinkedList::CustomLinkedList(const CustomLinkedList &other) : head_(nullptr), tail_(nullptr), size_(0)
{
    Node *current = other.head_;
    while (current != nullptr)
    {
        push_back(current->data);
        current = current->next;
    }
}

// copy Assignment operator

CustomLinkedList &CustomLinkedList::operator=(const CustomLinkedList &other)
{
    if (this == &other)
    {
        return *this;
    }
    clear();
    Node *Current = other.head_;
    while (Current != nullptr)
    {
        push_back(Current->data);
        Current = Current->next;
    }
    return *this;
}

//  Move constructor

CustomLinkedList::CustomLinkedList(CustomLinkedList &&other) : head_(other.head_), tail_(other.tail_), size_(other.size_)
{
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

// Move Constructor

CustomLinkedList &CustomLinkedList::operator=(CustomLinkedList &&other)
{
    if (this == &other)
    {
        return *this;
    }
    clear();

    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;

    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;

    return *this;
}

// Starting the Basic read/acceess API

int& CustomLinkedList::front()
{
    if (empty())
    {
        throw std::out_of_range("front() called on empty list");
    }

    return head_->data;
}

int& CustomLinkedList::back()
{
    if (empty())
    {
        throw std::out_of_range("back() called on empty list");
    }

    return tail_->data;
}

bool CustomLinkedList::empty() const
{
    return size_ == 0;
}


// const-correct front()/back()

const int& CustomLinkedList::front() const
{
    if (empty())
    {
        throw std::out_of_range("front() called on empty list");
    }

    return head_->data;
}

const int& CustomLinkedList::back() const
{
    if (empty())
    {
        throw std::out_of_range("back() called on empty list");
    }

    return tail_->data;
}



//find()
bool CustomLinkedList::find(int value)const
{
    Node *current = head_;

    while(current!=nullptr)
    {
        if(current->data==value){
            return true;
        }
        current = current->next;
    }
    return  false;
}

//insert()
void CustomLinkedList::insert(std::size_t index,int value)
{ if (index > size_)
    {
        throw std::out_of_range("insert() index out of range");
    }

    if(index==0)
    {
        push_front(value);
        return ;
    }

    if(index==size_)
    {
        push_back(value);
                  return;
    }

    Node *current = head_;

      for (std::size_t i = 0; i < index - 1; ++i)
    {
        current = current->next;
    }

    Node* newNode = new Node(value);

    newNode->next = current->next;
    current->next = newNode;

    ++size_;
}

// erase()
void CustomLinkedList::erase(std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("erase() index out of range");
    }
    if(index==0)
    {
        pop_front();
        return;
    }
    
    if(index==size_-1)
    {
        pop_back();
        return;
    }
    Node *current = head_;

    for (std::size_t i = 0; i < index - 1;i++)
    {
        current = current->next;
    }

    Node *nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    delete nodeToDelete;
    --size_;
}

//operator[]
int& CustomLinkedList::operator[](std::size_t index)
{
    //!bound cheking 
    // if (index >= size_)
    // {
    //     throw std::out_of_range("operator[] index out of range");
    // }

    Node* current = head_;

    for (std::size_t i = 0; i < index; ++i)
    {
        current = current->next;
    }

    return current->data;
}

// const operator[] 
const int& CustomLinkedList::operator[](std::size_t index) const
{
    //! bound cheking
    // if (index >= size_)
    // {
    //     throw std::out_of_range("operator[] index out of range");
    // }

    Node* current = head_;

    for (std::size_t i = 0; i < index; ++i)
    {
        current = current->next;
    }

    return current->data;
}
// at() 
int& CustomLinkedList::at(std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("at() index out of range");
    }

    Node* current = head_;

    for (std::size_t i = 0; i < index; ++i)
    {
        current = current->next;
    }

    return current->data;
}

//non const at
const int& CustomLinkedList::at(std::size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("at() index out of range");
    }

    Node* current = head_;

    for (std::size_t i = 0; i < index; ++i)
    {
        current = current->next;
    }

    return current->data;
}

//Iterator Constructor 
CustomLinkedList::Iterator::Iterator(Node* node)
    : current_(node)
{
}

int&CustomLinkedList::Iterator::operator*()
{
    return current_->data;
}

// operator++()
CustomLinkedList::Iterator&
CustomLinkedList::Iterator::operator++()
{
    current_ = current_->next;
    return *this;
}
//operator!=()
bool CustomLinkedList::Iterator::operator!=(
    const Iterator& other) const
{
    return current_ != other.current_;
}

//begin()
CustomLinkedList::Iterator CustomLinkedList::begin()
{
    return Iterator(head_);
}
//end()
CustomLinkedList::Iterator CustomLinkedList::end()
{
    return Iterator(nullptr);
}

// const Iterator Constructor 
CustomLinkedList::ConstIterator::ConstIterator(const Node* node)
    : current_(node)
{
}

// cosnt operator*()
const int& CustomLinkedList::ConstIterator::operator*() const
{
    return current_->data;
}
// cosnt operator++
CustomLinkedList::ConstIterator&
CustomLinkedList::ConstIterator::operator++()
{
    current_ = current_->next;
    return *this;
}
// cosnt operator!=()
bool CustomLinkedList::ConstIterator::operator!=(
    const ConstIterator& other) const
{
    return current_ != other.current_;
}

// const begin and end 
CustomLinkedList::ConstIterator
CustomLinkedList::begin() const
{
    return ConstIterator(head_);
}

CustomLinkedList::ConstIterator
CustomLinkedList::end() const
{
    return ConstIterator(nullptr);
}