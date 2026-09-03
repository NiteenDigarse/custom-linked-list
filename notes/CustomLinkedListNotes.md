CustomLinkedList — Engineering Notes

1. Project Overview

CustomLinkedList is a singly linked list implemented from scratch in C++.

The goal is not only to make a linked list work, but to understand:

Dynamic memory allocation

Pointer ownership

Node linking

Object lifetime

Rule of Five

Copy vs move semantics

Const-correctness

Iterators

Exception safety

Complexity

Testing and memory safety

2. Internal Structure

The list contains three important members:

Node* head_;
Node* tail_;
std::size_t size_;

A node contains:

struct Node
{
    int data;
    Node* next;

    Node(int value);
};

Conceptually:

head_
  |
  v
[10 | *] -> [20 | *] -> [30 | nullptr]
                         ^
                         |
                       tail_

Important

tail_ points to the last node, not to nullptr.

The last node's next pointer is nullptr.

tail_ --------------------+
                          |
                          v
[30 | nullptr]
      ^
      |
      next

3. Node Creation

A new node is dynamically allocated:

Node* newNode = new Node(value);

The Node constructor initializes:

Node::Node(int value)
    : data(value), next(nullptr)
{
}

So a newly created node starts with:

data = value
next = nullptr

4. push_front()

Purpose:

Add a node at the beginning.

Empty list

Before:

head_ = nullptr
tail_ = nullptr

push_front(10)

After:

head_
  |
  v
[10 | nullptr]
  ^
  |
tail_

Non-empty list

Before:

head_
  |
  v
[20] -> [30] -> nullptr

Create:

[10 | ?]

Then:

newNode->next = head_;
head_ = newNode;

Result:

head_
  |
  v
[10] -> [20] -> [30] -> nullptr

Complexity

O(1)

5. push_back()

Purpose:

Add a node at the end.

Because we maintain tail_, we don't need to traverse the whole list.

tail_->next = newNode;
tail_ = newNode;

Before:

head_
  |
  v
[10] -> [20] -> nullptr
                 ^
                 |
               tail_

After:

head_
  |
  v
[10] -> [20] -> [30] -> nullptr
                         ^
                         |
                       tail_

Complexity

O(1)

6. pop_front()

Remove the first node.

Node* oldHead = head_;
head_ = head_->next;
delete oldHead;

Example:

Before:

head_
  |
  v
[10] -> [20] -> [30] -> nullptr

After:

head_
  |
  v
[20] -> [30] -> nullptr

The old [10] node is deleted.

Important

If the list becomes empty:

tail_ = nullptr;

must also be done.

Complexity

O(1)

7. pop_back()

A singly linked list does not have a previous pointer.

Therefore, to remove the last node, we must find the node immediately before tail_.

Node* current = head_;

while (current->next != tail_)
{
    current = current->next;
}

Then:

delete tail_;

tail_ = current;
tail_->next = nullptr;

Complexity

O(n)

8. clear()

clear() deletes every node.

Important pattern:

Node* current = head_;

while (current != nullptr)
{
    Node* next = current->next;
    delete current;
    current = next;
}

Why save next first?

This is dangerous:

delete current;
current = current->next;   // WRONG

After delete current, accessing current->next is a use-after-free.

Correct:

current
  |
  v
[10] -> [20]

save next
  |
  v
[20]

delete current

move current to saved next

Then:

head_ = nullptr;
tail_ = nullptr;
size_ = 0;

Complexity

O(n)

9. Destructor

The destructor:

CustomLinkedList::~CustomLinkedList()
{
    clear();
}

This follows the RAII principle.

When the list object dies, it releases all nodes that it owns.

CustomLinkedList destroyed
        |
        v
      clear()
        |
        v
delete node 1
delete node 2
delete node 3
...

10. Copy Constructor

Copying a linked list requires a deep copy.

Example:

CustomLinkedList a;
a.push_back(10);
a.push_back(20);
a.push_back(30);

CustomLinkedList b = a;

We want:

a:
[10] -> [20] -> [30]

b:
[10] -> [20] -> [30]

But these must be different nodes in different memory locations.

Wrong idea

Copying pointers:

a.head_ --------+
                |
                v
              [10] -> [20] -> [30]
                ^
                |
b.head_ --------+

Now both objects own the same nodes.

When both destructors run, the same memory may be deleted twice.

Correct idea

Create new nodes:

a:
[10] -> [20] -> [30]

b:
[10] -> [20] -> [30]

with completely separate memory.

11. Copy Assignment

Copy assignment:

a = b;

must first protect against self-assignment:

if (this == &other)
{
    return *this;
}

Then:

clear();

and copy all nodes from other.

Self-assignment

list = list;

Without the self-assignment check, clear() would destroy the list before attempting to copy from it.

12. Move Constructor

Move semantics transfer ownership instead of allocating new nodes.

CustomLinkedList::CustomLinkedList(CustomLinkedList&& other)
    : head_(other.head_),
      tail_(other.tail_),
      size_(other.size_)
{
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
}

Before:

other
  |
  v
[10] -> [20] -> [30]

After move:

destination
     |
     v
[10] -> [20] -> [30]

other
  |
 nullptr

The nodes themselves were not copied.

Only ownership was transferred.

Complexity

O(1)

13. Move Assignment

Move assignment:

destination = std::move(source);

First release the destination's old nodes:

clear();

Then steal source's resources:

head_ = other.head_;
tail_ = other.tail_;
size_ = other.size_;

Finally reset the source:

other.head_ = nullptr;
other.tail_ = nullptr;
other.size_ = 0;

Complexity

O(n) because the old destination nodes must be deleted.

The actual ownership transfer is O(1).

14. Rule of Five

Because the class manually owns dynamically allocated memory, it needs the five special member functions:

1. Destructor
2. Copy constructor
3. Copy assignment operator
4. Move constructor
5. Move assignment operator

This is the Rule of Five.

Our class implements all five.

15. front() and back()

front() returns the first element.

return head_->data;

back() returns the last element.

return tail_->data;

Both have:

O(1)

complexity.

Empty list safety

Accessing either on an empty list is invalid.

Therefore:

if (empty())
{
    throw std::out_of_range("front() called on empty list");
}

and similarly for back().

16. const-correctness

Two versions exist:

int& front();
const int& front() const;

The first allows modification:

list.front() = 100;

The const version prevents modification:

const CustomLinkedList& list = ...;

list.front() = 100;   // compile error

The same idea applies to:

back()

operator[]

begin()

end()

17. empty() and size()

bool empty() const
{
    return size_ == 0;
}

std::size_t size() const
{
    return size_;
}

Because size_ is maintained during every insertion/removal, both are:

O(1)

18. find()

find() walks through nodes:

Node* current = head_;

while (current != nullptr)
{
    if (current->data == value)
    {
        return true;
    }

    current = current->next;
}

Because a linked list has no random access, it may need to inspect every node.

Complexity

Best case:  O(1)
Worst case: O(n)

19. insert()

Valid insertion positions are:

0 ... size_

Notice that size_ itself is valid.

Example:

size = 3

insert(0) -> beginning
insert(1) -> middle
insert(2) -> middle
insert(3) -> end

Therefore validation is:

if (index > size_)
{
    throw std::out_of_range("insert() index out of range");
}

Special cases

if (index == 0)
{
    push_front(value);
    return;
}

if (index == size_)
{
    push_back(value);
    return;
}

For the middle, find the previous node and reconnect pointers:

Before:

[10] -> [30]

New node:

[20]

Reconnect:

[10] -> [20] -> [30]

Complexity

Because finding the position requires traversal:

O(n)

20. erase()

Valid indexes are:

0 ... size_ - 1

Validation:

if (index >= size_)
{
    throw std::out_of_range("erase() index out of range");
}

First node

Reuse:

pop_front();

Last node

Reuse:

pop_back();

Middle node

Find the node before the target:

[10] -> [20] -> [30]

erase(1)

previous = [10]
target   = [20]
next     = [30]

Reconnect:

[10] --------> [30]

Then:

delete nodeToDelete;

Complexity

O(n)

21. operator[]

Linked lists do not provide true random access.

For:

list[3]

we must start from head_ and move three times.

Node* current = head_;

for (std::size_t i = 0; i < index; ++i)
{
    current = current->next;
}

Validation:

if (index >= size_)
{
    throw std::out_of_range("operator[] index out of range");
}

Complexity

O(n)

This is fundamentally different from a vector's operator[], which is O(1).

22. Iterator

The iterator stores a node pointer:

Node* current_;

It behaves like a movable pointer into the linked list.

begin()

return Iterator(head_);

So:

begin()
  |
  v
[10] -> [20] -> [30] -> nullptr

end()

return Iterator(nullptr);

Important:

end() does not point to the last node.

It represents the position after the last element.

[10] -> [20] -> [30] -> nullptr
                         ^
                         |
                        end()

23. Iterator operator*

int& Iterator::operator*()
{
    return current_->data;
}

This allows:

*it

to access the current node's data.

Because it returns int&, modification is possible:

*it = 100;

24. Iterator operator++

Iterator& Iterator::operator++()
{
    current_ = current_->next;
    return *this;
}

It moves the iterator to the next node.

it
 |
 v
[10] -> [20] -> [30]

++it

it
      |
      v
[10] -> [20] -> [30]

25. Iterator operator!=

bool Iterator::operator!=(const Iterator& other) const
{
    return current_ != other.current_;
}

Range-based loops use this to know when traversal ends.

26. Range-based for loop

This:

for (int value : list)
{
    std::cout << value;
}

conceptually becomes:

auto it = list.begin();
auto end = list.end();

while (it != end)
{
    int value = *it;
    ++it;
}

Therefore the iterator needs:

begin()
end()
operator!=
operator*
operator++

27. ConstIterator

A const iterator stores:

const Node* current_;

and dereferences to:

const int&

Therefore:

const CustomLinkedList& list = ...;

for (int value : list)
{
    // read allowed
}

but modification through the iterator is prevented.

28. Exception Safety

Invalid operations should not silently access invalid memory.

Examples:

list.front();       // invalid if empty
list.back();        // invalid if empty
list[100];          // invalid if index >= size
list.insert(100, 5);// invalid if index > size
list.erase(100);    // invalid if index >= size

We throw:

std::out_of_range

This is much safer than allowing undefined behavior.

29. size_t and Underflow

std::size_t is unsigned.

Therefore:

std::size_t size = 0;

size - 1

does not produce -1.

It wraps around to a very large unsigned value.

This is why validation should happen before expressions such as:

size_ - 1

For erase():

if (index >= size_)
{
    throw std::out_of_range(...);
}

must come before checking:

index == size_ - 1

30. Memory Ownership Model

The list owns every node it creates.

CustomLinkedList
      |
      +---- owns Node 1
      |
      +---- owns Node 2
      |
      +---- owns Node 3

The list is responsible for deleting them.

Ownership transfer during move

Source owns nodes

       ↓ std::move

Destination owns nodes

Source owns nothing

This is the central idea behind move semantics in this project.

31. Complexity Summary

Operation

Complexity

push_front

O(1)

push_back

O(1)

pop_front

O(1)

pop_back

O(n)

front

O(1)

back

O(1)

empty

O(1)

size

O(1)

clear

O(n)

find

O(n)

insert

O(n)

erase

O(n)

operator[]

O(n)

iterator increment

O(1)

copy constructor

O(n)

copy assignment

O(n)

move constructor

O(1)

move assignment

O(n)

32. Testing Strategy

The project uses dedicated tests in:

tests/
    test_custom_linked_list.cpp

The tests cover:

Push operations

Pop operations

Insert

Erase

Find

Clear

Copy constructor

Copy assignment

Move constructor

Move assignment

Iterators

Range-based for

Const iterator

Empty operations

Exception handling

Self-assignment

Stress operations

The test executable reports:

All CustomLinkedList tests passed!

33. Stress Testing

Stress testing creates many nodes:

for (int i = 0; i < 10000; ++i)
{
    list.push_back(i);
}

Then performs many removals and clears the list.

The purpose is to exercise:

Pointer manipulation

Node allocation

Node deletion

size_ tracking

head_

tail_

clear()

This increases confidence beyond a tiny three-node example.

34. AddressSanitizer

AddressSanitizer (ASan) is a development/testing tool used to detect memory errors.

It can help detect problems such as:

Use-after-free

Double-free

Heap buffer overflow

Memory leaks in supported configurations

It is especially useful for this project because the list manually uses:

new
delete

ASan is a testing tool, not a feature of CustomLinkedList.

35. Important Linked List Mental Model

Always think in terms of:

Node
 |
 +-- data
 |
 +-- next

and:

head_ -> first node
tail_ -> last node
last->next -> nullptr

For every operation ask:

Which node is being created/deleted?

Who owns that node?

Which pointer changes?

Could a pointer become dangling?

Does head_ remain correct?

Does tail_ remain correct?

Is size_ correct?

Does every allocated node eventually get deleted?

These questions are more important than memorizing code.

36. Engineering Lessons

This project demonstrates several important C++ engineering concepts:

Resource ownership

The container owns dynamically allocated nodes.

RAII

The destructor releases resources automatically when the object dies.

Rule of Five

Manual ownership requires correct copy/move behavior.

Deep copy

Copying an owning data structure requires independent resources.

Move semantics

Resources can be transferred instead of copied.

Const-correctness

Const objects must not be accidentally modified.

Exception safety

Invalid input should be handled explicitly.

Iterator abstraction

Users can traverse the container without knowing its internal node structure.

Testing

Correctness should be verified systematically rather than only through manual output.

37. Key Difference: Vector vs Linked List

CustomVector

[10][20][30][40]

Elements are contiguous.

Random access:

O(1)

Insertion/removal in the middle:

O(n)

CustomLinkedList

[10] -> [20] -> [30] -> [40]

Nodes may be scattered in memory.

Random access:

O(n)

Insertion/removal after finding the position:

O(n)

Push front:

O(1)

Push back with tail_:

O(1)

38. Final Project Checklist

[✓] Node structure
[✓] head_
[✓] tail_
[✓] size_
[✓] push_front()
[✓] push_back()
[✓] pop_front()
[✓] pop_back()
[✓] front()
[✓] back()
[✓] empty()
[✓] size()
[✓] clear()
[✓] destructor
[✓] copy constructor
[✓] copy assignment
[✓] move constructor
[✓] move assignment
[✓] find()
[✓] insert()
[✓] erase()
[✓] operator[]
[✓] const operator[]
[✓] Iterator
[✓] ConstIterator
[✓] begin()
[✓] end()
[✓] range-based for
[✓] bounds checking
[✓] exception handling
[✓] dedicated tests
[✓] stress testing
[ ] final memory-sanitizer verification
[ ] complexity/API review
[ ] cleanup/refactoring
[ ] README
[ ] Git commit
[ ] GitHub push

39. Final Mental Picture

The complete container can be visualized as:

              CustomLinkedList
             /       |        \
            /        |         \
        head_      tail_      size_
          |           |          |
          v           v          v
       [10 | *] -> [20 | *] -> [30 | nullptr]
          |
        first                  last

Ownership:

CustomLinkedList
      |
      +--> Node
             |
             +--> Node
                    |
                    +--> Node
                           |
                           +--> nullptr

The list is responsible for the lifetime of this entire chain.