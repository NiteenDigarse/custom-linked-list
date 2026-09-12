# CustomLinkedList

A custom singly linked list implementation in modern C++ built from scratch to understand dynamic memory management, ownership, copy/move semantics, iterators, const-correctness, exception handling, and data-structure internals.

## Overview

`CustomLinkedList` is a manually implemented singly linked list that manages its own dynamically allocated nodes.

The project was developed as part of a C++ engineering learning journey, with a focus on understanding how standard-library-style containers work internally rather than simply using them.

## Features

* `push_front()` — Insert an element at the beginning
* `push_back()` — Insert an element at the end
* `pop_front()` — Remove the first element
* `pop_back()` — Remove the last element
* `front()` / `back()` — Access first and last elements
* `insert()` — Insert an element at a specific index
* `erase()` — Remove an element at a specific index
* `find()` — Search for an element
* `clear()` — Remove all elements
* `size()` — Get the number of elements
* `empty()` — Check whether the list is empty
* `operator[]` — Unchecked element access
* `at()` — Bounds-checked element access
* Forward iterator support
* Const iterator support
* Range-based `for` loop support
* Copy constructor
* Copy assignment operator
* Move constructor
* Move assignment operator
* Self-assignment handling
* Exception handling for invalid operations
* Dedicated test suite
* Stress testing with large numbers of nodes

## Internal Structure

The list uses three main pieces of state:

```text
head_
   |
   v
[10] -> [20] -> [30] -> nullptr
                         ^
                       tail_

size_ = 3
```

Each node contains:

```cpp
struct Node
{
    int data;
    Node* next;
};
```

* `head_` points to the first node.
* `tail_` points to the last node.
* The last node's `next` pointer is `nullptr`.
* `size_` stores the number of nodes currently in the list.

## Memory Management

Nodes are dynamically allocated and released manually.

Example:

```text
push_back(10)

head_
  |
  v
[10 | nullptr]
  ^
  |
tail_
```

When nodes are removed, their allocated memory is released to avoid memory leaks.

The destructor calls `clear()` to release all nodes owned by the list.

## Copy Semantics

The class implements deep copying.

Copying a list creates completely independent nodes:

```text
List A:

[10] -> [20] -> [30]

        copy
         |
         v

List B:

[10] -> [20] -> [30]
```

The nodes are different allocations, so modifying one list does not modify the other.

Implemented:

```cpp
CustomLinkedList(const CustomLinkedList& other);
CustomLinkedList& operator=(const CustomLinkedList& other);
```

Self-assignment is also handled safely.

## Move Semantics

Move operations transfer ownership of the dynamically allocated nodes instead of creating new copies.

Implemented:

```cpp
CustomLinkedList(CustomLinkedList&& other);
CustomLinkedList& operator=(CustomLinkedList&& other);
```

Conceptually:

```text
Before move:

A -> [10] -> [20] -> [30]
B -> empty

After move:

A -> empty
B -> [10] -> [20] -> [30]
```

This avoids unnecessary allocations and copies.

## Rule of Five

Because the class manages a dynamically allocated resource, it implements all five special member functions:

```cpp
~CustomLinkedList();

CustomLinkedList(const CustomLinkedList& other);
CustomLinkedList& operator=(const CustomLinkedList& other);

CustomLinkedList(CustomLinkedList&& other);
CustomLinkedList& operator=(CustomLinkedList&& other);
```

This provides explicit control over resource ownership during construction, copying, moving, and destruction.

## Iterator Support

The container provides forward iterators:

```cpp
begin()
end()
```

This allows normal iterator-based traversal:

```cpp
for (auto it = list.begin(); it != list.end(); ++it)
{
    std::cout << *it << '\n';
}
```

It also supports range-based `for` loops:

```cpp
for (int value : list)
{
    std::cout << value << '\n';
}
```

A separate `ConstIterator` provides read-only traversal for const lists.

## Const-Correctness

The class provides both mutable and const overloads.

For example:

```cpp
int& front();
const int& front() const;
```

This means:

```cpp
CustomLinkedList list;
list.front() = 100;        // allowed
```

while:

```cpp
const CustomLinkedList list;
list.front();              // read-only
```

cannot be used to modify the stored value.

## Element Access

Two different access styles are provided.

### `operator[]`

Unchecked access:

```cpp
list[2];
```

It does not perform bounds checking.

### `at()`

Bounds-checked access:

```cpp
list.at(2);
```

Invalid indexes throw:

```cpp
std::out_of_range
```

This provides a safer alternative when index validation is required.

## Exception Handling

The implementation validates invalid operations and throws `std::out_of_range` where appropriate.

Examples include:

* Calling `front()` on an empty list
* Calling `back()` on an empty list
* Invalid `at()` index
* Invalid `insert()` index
* Invalid `erase()` index

## Project Structure

```text
custom-linked-list/
│
├── CMakeLists.txt
├── .gitignore
│
├── include/
│   └── CustomLinkedList.h
│
├── src/
│   └── CustomLinkedList.cpp
│
├── examples/
│   └── basic_usage.cpp
│
├── tests/
│   └── test_custom_linked_list.cpp
│
└── notes/
    └── CustomLinkedListNotes.md
```

The `build/` directory is intentionally excluded from Git through `.gitignore`.

## Building the Project

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

## Running the Example

After building:

```bash
build\Debug\CustomLinkedListExample.exe
```

Depending on the CMake generator/configuration, the executable location may differ.

## Running Tests

Build the project first:

```bash
cmake -S . -B build
cmake --build build
```

Then run:

```bash
build\Debug\CustomLinkedListTests.exe
```

The test suite covers normal operations, copy/move semantics, iterators, exceptions, boundary cases, and stress operations.

## Complexity

For a singly linked list:

| Operation       | Complexity |
| --------------- | ---------: |
| `push_front()`  |       O(1) |
| `push_back()`   |       O(1) |
| `pop_front()`   |       O(1) |
| `pop_back()`    |       O(n) |
| `front()`       |       O(1) |
| `back()`        |       O(1) |
| `find()`        |       O(n) |
| `insert(index)` |       O(n) |
| `erase(index)`  |       O(n) |
| `operator[]`    |       O(n) |
| `at()`          |       O(n) |
| `begin()`       |       O(1) |
| `end()`         |       O(1) |

Unlike a contiguous container such as `std::vector`, linked-list elements are stored in separate dynamically allocated nodes.

## Testing

The project includes a dedicated assert-based test suite covering:

* Basic insertion and removal
* Front/back operations
* Indexed insertion and deletion
* Searching
* Clearing
* Copy construction
* Copy assignment
* Move construction
* Move assignment
* Self-assignment
* Iterator traversal
* Const iterator traversal
* Range-based loops
* Exception cases
* Boundary conditions
* Large-scale stress operations

The implementation was tested with thousands of nodes to verify basic correctness under larger workloads.

## Key C++ Concepts Practiced

This project focuses on practical understanding of:

* Classes and encapsulation
* Nested classes
* Pointers
* Dynamic memory allocation
* Ownership
* RAII
* Destructors
* Copy constructor
* Copy assignment
* Move constructor
* Move assignment
* Rule of Five
* Deep copy
* Move semantics
* References
* `const` correctness
* Operator overloading
* Iterators
* Exception handling
* CMake
* Unit testing
* Git and GitHub

## Future Improvements

Possible future extensions include:

* Bidirectional linked list
* Reverse iterator
* Custom allocator support
* Generic/template-based linked list
* More STL-compatible iterator functionality
* Additional performance benchmarks
* Automated testing through CI/CD

## Author

**Niteen Digarse**

This project is part of my ongoing C++ engineering journey focused on strengthening C++, data structures, memory management, systems-level thinking, and software engineering practices.
