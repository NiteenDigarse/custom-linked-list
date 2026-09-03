#include "CustomLinkedList.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <utility>

void test_push_operations()
{
    CustomLinkedList list;

    list.push_front(20);
    list.push_front(10);
    list.push_back(30);
    list.push_back(40);

    assert(list.size() == 4);
    assert(list.front() == 10);
    assert(list.back() == 40);

    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);
    assert(list[3] == 40);
}

void test_pop_operations()
{
    CustomLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.pop_front();

    assert(list.size() == 2);
    assert(list.front() == 20);

    list.pop_back();

    assert(list.size() == 1);
    assert(list.front() == 20);
    assert(list.back() == 20);

    list.pop_back();

    assert(list.empty());
}

void test_insert()
{
    CustomLinkedList list;

    list.push_back(10);
    list.push_back(30);

    list.insert(1, 20);

    assert(list.size() == 3);
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);

    list.insert(0, 5);

    assert(list.front() == 5);

    list.insert(list.size(), 40);

    assert(list.back() == 40);
    assert(list.size() == 5);
}

void test_erase()
{
    CustomLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    list.erase(1);

    assert(list.size() == 3);
    assert(list[0] == 10);
    assert(list[1] == 30);
    assert(list[2] == 40);

    list.erase(0);

    assert(list.front() == 30);
    assert(list.size() == 2);

    list.erase(list.size() - 1);

    assert(list.back() == 30);
    assert(list.size() == 1);
}

void test_find()
{
    CustomLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    assert(list.find(10));
    assert(list.find(20));
    assert(list.find(30));

    assert(!list.find(100));
}

void test_clear()
{
    CustomLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.clear();

    assert(list.empty());
    assert(list.size() == 0);
}

void test_copy_constructor()
{
    CustomLinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    CustomLinkedList copy(original);

    assert(copy.size() == 3);
    assert(copy[0] == 10);
    assert(copy[1] == 20);
    assert(copy[2] == 30);

    copy[0] = 100;

    assert(original[0] == 10);
    assert(copy[0] == 100);
}

void test_copy_assignment()
{
    CustomLinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    CustomLinkedList copy;

    copy.push_back(100);
    copy.push_back(200);

    copy = original;

    assert(copy.size() == 3);
    assert(copy[0] == 10);
    assert(copy[1] == 20);
    assert(copy[2] == 30);

    copy[1] = 200;

    assert(original[1] == 20);
}

void test_move_constructor()
{
    CustomLinkedList source;

    source.push_back(10);
    source.push_back(20);
    source.push_back(30);

    CustomLinkedList destination(std::move(source));

    assert(destination.size() == 3);
    assert(destination[0] == 10);
    assert(destination[1] == 20);
    assert(destination[2] == 30);

    assert(source.empty());
    assert(source.size() == 0);
}

void test_move_assignment()
{
    CustomLinkedList source;

    source.push_back(10);
    source.push_back(20);
    source.push_back(30);

    CustomLinkedList destination;

    destination.push_back(100);
    destination.push_back(200);

    destination = std::move(source);

    assert(destination.size() == 3);
    assert(destination[0] == 10);
    assert(destination[1] == 20);
    assert(destination[2] == 30);

    assert(source.empty());
    assert(source.size() == 0);
}

void test_iterators()
{
    CustomLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    auto it = list.begin();

    assert(*it == 10);

    ++it;
    assert(*it == 20);

    ++it;
    assert(*it == 30);

    ++it;
    assert(!(it != list.end()));
}

void test_range_based_for()
{
    CustomLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    int expected = 10;

    for (int value : list)
    {
        assert(value == expected);
        expected += 10;
    }
}

void test_const_iterator()
{
    CustomLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    const CustomLinkedList& constList = list;

    auto it = constList.begin();

    assert(*it == 10);

    ++it;
    assert(*it == 20);

    ++it;
    assert(*it == 30);

    ++it;
   assert(!(it != constList.end()));
}

void test_empty_operations()
{
    CustomLinkedList list;

    assert(list.empty());
    assert(list.size() == 0);

    list.pop_front();
    list.pop_back();

    assert(list.empty());
}

void test_exceptions()
{
    CustomLinkedList list;

    bool frontException = false;

    try
    {
        list.front();
    }
    catch (const std::out_of_range&)
    {
        frontException = true;
    }

    assert(frontException);

    bool backException = false;

    try
    {
        list.back();
    }
    catch (const std::out_of_range&)
    {
        backException = true;
    }

    assert(backException);

  bool atException = false;

try
{
    list.at(0);
}
catch (const std::out_of_range&)
{
    atException = true;
}

assert(atException);

    bool insertException = false;

    try
    {
        list.insert(1, 100);
    }
    catch (const std::out_of_range&)
    {
        insertException = true;
    }

    assert(insertException);

    bool eraseException = false;

    try
    {
        list.erase(0);
    }
    catch (const std::out_of_range&)
    {
        eraseException = true;
    }

    assert(eraseException);
    //valid at() test
    CustomLinkedList validList;

validList.push_back(10);
validList.push_back(20);

assert(validList.at(0) == 10);
assert(validList.at(1) == 20);
}

void test_self_assignment()
{
    CustomLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list = list;

    assert(list.size() == 3);
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);
}

void test_stress_operations()
{
    CustomLinkedList list;

    for (int i = 0; i < 10000; ++i)
    {
        list.push_back(i);
    }

    assert(list.size() == 10000);
    assert(list.front() == 0);
    assert(list.back() == 9999);

    for (int i = 0; i < 5000; ++i)
    {
        list.pop_front();
    }

    assert(list.size() == 5000);
    assert(list.front() == 5000);

    list.clear();

    assert(list.empty());
    assert(list.size() == 0);
}

int main()
{
    test_stress_operations();
    test_push_operations();
    test_pop_operations();
    test_insert();
    test_erase();
    test_find();
    test_clear();

    test_copy_constructor();
    test_copy_assignment();

    test_move_constructor();
    test_move_assignment();

    test_iterators();
    test_range_based_for();
    test_const_iterator();

    test_empty_operations();
    test_exceptions();
    test_self_assignment();

    std::cout << "All CustomLinkedList tests passed!\n";

    return 0;
}