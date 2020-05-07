#include "../list.h"
#include <iostream>

using namespace utility;

int main(){

    static const int MAXSIZE = 1000;

    /*
     * Test 1
     * Push Iterator
     */
    {
        std::cout << "Test 1" << std::endl;

        CDoublyLinkedListFictive<int> list;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            list.pushFront(i);
        }
        for (int i = 0; i < MAXSIZE; ++i)
        {
            list.pushBack(i);
        }
        if (list.getSize() != 2 * MAXSIZE)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        CDoublyLinkedListFictive<int>::CIterator it = list.begin();
        for (int i = 0; i < 2 * MAXSIZE; ++i, ++it)
        {
            if (i < MAXSIZE && (*it) != MAXSIZE - 1 - i)
            {
                std::cout << "WRONG" << std::endl;
                exit(1);
            }
            if (i >= MAXSIZE && (*it) != i - MAXSIZE)
            {
                std::cout << "WRONG" << std::endl;
                exit(1);
            }
        }
        std::cout << "Ok" << std::endl;
    }

    /*
     * Test 2
     * Pop
     */
    {
        std::cout << "Test 2" << std::endl;

        CDoublyLinkedListFictive<int> list;
        for (int i = 0; i < 2 * MAXSIZE; ++i)
        {
            list.pushBack(i);
        }
        for (int i = 0; i < MAXSIZE; ++i)
        {
            if (list.popFront() != i)
            {
                std::cout << "WRONG" << std::endl;
                exit(1);
            }
        }
        if (list.getSize() != MAXSIZE)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        for (int i = 0; i < MAXSIZE; ++i)
        {
            if (list.popFront()!= i + MAXSIZE)
            {
                std::cout << "WRONG" << std::endl;
                exit(1);
            }
        }
        if (list.getSize() != 0)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        std::cout << "Ok" << std::endl;
    }

    /*
     * Test 3
     * Clear
     */
    {
        std::cout << "Test 3" << std::endl;

        CDoublyLinkedListFictive<int> list;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            list.pushBack(i);
        }
        if (list.getSize() != MAXSIZE)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        list.clear();
        if (list.getSize() != 0)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        std::cout << "Ok" << std::endl;
    }

    /*
     * Test 4
     * Erase PreBegin
     */
    {
        std::cout << "Test 4" << std::endl;

        CDoublyLinkedListFictive<int> list;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            list.pushFront(i);
        }
        CDoublyLinkedListFictive<int>::CIterator it = list.begin();
        list.erase(it);
        ++it;
        if (it != list.begin())
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        std::cout << "OK" << std::endl;
    }

    /*
     * Test 5
     * EraseNext PostEnd
     */
    {
        std::cout << "Test 5" << std::endl;

        CDoublyLinkedListFictive<int> list;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            list.pushFront(i);
        }
        CDoublyLinkedListFictive<int>::CIterator it = list.end();
        --it;
        list.eraseAndNext(it);
        if (it != list.end())
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        it = list.begin();
        list.eraseAndNext(it);
        if (it != list.begin())
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        if (list.getSize() != MAXSIZE - 2)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        std::cout << "Ok" << std::endl;

    }

    /*
     * Test 6
     * Iterator
     */
    {
        std::cout << "Test 6" << std::endl;

        CDoublyLinkedListFictive<int> list;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            list.pushFront(i);
        }
        CDoublyLinkedListFictive<int>::CIterator it = list.begin();
        for (int i = 0; it != list.end(); ++it, ++i)
        {
            if (it.getData()!= MAXSIZE - i - 1)
            {
                std::cout << "WRONG" << std::endl;
                exit(1);
            }
        }
        std::cout << "Ok" << std::endl;

    }

    /*
     * Test 7
     * Erase Insert
     */
    {
        std::cout << "Test 7" << std::endl;

        CDoublyLinkedListFictive<int> list;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            list.pushFront(i);
        }
        CDoublyLinkedListFictive<int>::CIterator it = list.begin();
        for (int i = 0; i < 100; ++i)
        {
            ++it;
        }
        int new_str = -1;
        list.erase(it);
        list.insert(it, new_str);
        ++it;
        if (it.getData() != new_str)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }

        it = list.begin();
        --it;
        new_str = -1;
        list.insert(it, new_str);
        if (list.begin().getData() != -1)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }

        it = list.end();
        --it;
        new_str = MAXSIZE;
        list.insert(it, new_str);
        ++it;
        if (it.getData() != MAXSIZE)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        ++it;
        if (it != list.end())
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        std::cout << "Ok" << std::endl;
    }



    return 0;
}