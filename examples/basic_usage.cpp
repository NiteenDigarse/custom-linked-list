#include <iostream>
#include<utility>
#include "CustomLinkedList.h"

int main()
{
    CustomLinkedList list;

    std::cout << "Initial size: " << list.size() << '\n';

    list.push_front(10);
    std::cout << "After push_front(10): " << list.size() << '\n';

    list.push_front(20);
    std::cout << "After push_front(20): " << list.size() << '\n';

    list.push_back(30);
    std::cout << "After push_back(30): " << list.size() << '\n';

    list.pop_front();
    std::cout << "After pop_front(): " << list.size() << '\n';

    list.pop_back();
    std::cout << "After pop_back(): " << list.size() << '\n';

    //clear() testing 
    list.push_back(40);
list.push_back(50);

std::cout << "Before clear(): " << list.size() << '\n';

list.clear();

std::cout << "After clear(): " << list.size() << '\n';


// cheking the copy constructor 
CustomLinkedList original;

original.push_back(10);
original.push_back(20);
original.push_back(30);

CustomLinkedList copy = original;

std::cout << "Original size: " << original.size() << '\n';
std::cout << "Copy size: " << copy.size() << '\n';


// chekin the assignment operator 
CustomLinkedList a;

a.push_back(10);
a.push_back(20);
a.push_back(30);

CustomLinkedList b;

b.push_back(100);
b.push_back(200);

b = a;

std::cout << "A size: " << a.size() << '\n';
std::cout << "B size: " << b.size() << '\n';

// move cosntructor 
// CustomLinkedList source;

// source.push_back(10);
// source.push_back(20);
// source.push_back(30);

// CustomLinkedList destination(std::move(source));

// std::cout << "Source size after move: "
//           << source.size() << '\n';

// std::cout << "Destination size: "
//           << destination.size() << '\n';


          //cheaking move constructor
         

CustomLinkedList source;

source.push_back(10);
source.push_back(20);
source.push_back(30);

CustomLinkedList destination;

destination.push_back(100);
destination.push_back(200);

destination = std::move(source);

std::cout << "Source size after move assignment: "
          << source.size() << '\n';

std::cout << "Destination size: "
          << destination.size() << '\n';


          CustomLinkedList list2;

list2.push_back(10);
list2.push_back(20);
list2.push_back(30);

std::cout << "Front: " << list2.front() << '\n';
std::cout << "Back: " << list2.back() << '\n';
std::cout << "Empty: " << list2.empty() << '\n';

list2.front() = 100;
list2.back() = 300;

std::cout << "Modified front: " << list2.front() << '\n';
std::cout << "Modified back: " << list2.back() << '\n';

list2.clear();

std::cout << "Empty after clear: " << list2.empty() << '\n';


// find()
CustomLinkedList searchList;

searchList.push_back(10);
searchList.push_back(20);
searchList.push_back(30);
searchList.push_back(40);

std::cout << "Find 30: " << searchList.find(30) << '\n';
std::cout << "Find 99: " << searchList.find(99) << '\n';

// inser();

CustomLinkedList insertList;

insertList.push_back(10);
insertList.push_back(20);
insertList.push_back(40);

insertList.insert(2, 30);

std::cout << "After insert, size: "
          << insertList.size() << '\n';

std::cout << "Front: "
          << insertList.front() << '\n';

std::cout << "Back: "
          << insertList.back() << '\n';

std::cout << "Find 30: "
          << insertList.find(30) << '\n';


// erase() test
CustomLinkedList eraseList;

eraseList.push_back(10);
eraseList.push_back(20);
eraseList.push_back(30);
eraseList.push_back(40);

eraseList.erase(2);

std::cout << "After erase, size: "
          << eraseList.size() << '\n';

std::cout << "Find 30: "
          << eraseList.find(30) << '\n';

std::cout << "Find 40: "
          << eraseList.find(40) << '\n';


//operator[]
CustomLinkedList indexList;

indexList.push_back(10);
indexList.push_back(20);
indexList.push_back(30);
indexList.push_back(40);

std::cout << "Index 0: " << indexList[0] << '\n';
std::cout << "Index 1: " << indexList[1] << '\n';
std::cout << "Index 2: " << indexList[2] << '\n';
std::cout << "Index 3: " << indexList[3] << '\n';

indexList[1] = 200;

std::cout << "After modification: "
          << indexList[1] << '\n';

const CustomLinkedList constIndexList = indexList;

std::cout << "Const index 1: "
          << constIndexList[1] << '\n';

          //iterator
          CustomLinkedList iteratorList;

iteratorList.push_back(10);
iteratorList.push_back(20);
iteratorList.push_back(30);

std::cout << "Iterator traversal:\n";

for (auto it = iteratorList.begin();
     it != iteratorList.end();
     ++it)
{
    std::cout << *it << '\n';
}

// rangr based for loop
std::cout << "Range-based for:\n";

for (int value : iteratorList)
{
    std::cout << value << '\n';
}

// const iterator testing 
const CustomLinkedList constIteratorList = iteratorList;

std::cout << "Const Iterator traversal:\n";

for (auto it = constIteratorList.begin();
     it != constIteratorList.end();
     ++it)
{
    std::cout << *it << '\n';
}

//===================
std::cout << "\n=== Empty List Exception Test ===\n";

CustomLinkedList emptyList;

try
{
    emptyList.front();
}
catch (const std::out_of_range& e)
{
    std::cout << "front(): " << e.what() << '\n';
}

try
{
    emptyList.back();
}
catch (const std::out_of_range& e)
{
    std::cout << "back(): " << e.what() << '\n';
}
    



    // =============/=================== 
    std::cout << "\n=== Invalid operator[] Test ===\n";

try
{
    emptyList[0];
}
catch (const std::out_of_range& e)
{
    std::cout << "operator[]: " << e.what() << '\n';
}




// =====================/========================== 
std::cout << "\n=== Invalid insert() Test ===\n";

try
{
    emptyList.insert(1, 100);
}
catch (const std::out_of_range& e)
{
    std::cout << "insert(): " << e.what() << '\n';
}
//======================//=========================
std::cout << "\n=== Invalid erase() Test ===\n";

try
{
    emptyList.erase(0);
}
catch (const std::out_of_range& e)
{
    std::cout << "erase(): " << e.what() << '\n';
}
return 0;
}