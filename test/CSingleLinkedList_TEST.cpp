#include "../list.h"
#include <iostream>

using namespace utility;


int main()
{
    const static int MAXSIZE = 2;

    /* TEST 1
     *
     * Push Pop
     *
     */
    std::cout << "Test 1 ";
    {
        CSingleLinkedList<int> list;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            list.pushFront(i);
            list.pushBack(i);
        }
        if (list.getSize() != 2 * MAXSIZE)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        for (size_t i = 1 ; i < 2 * MAXSIZE + 1; ++i)
        {
            int m_test = list.popFront();
            if (i <= MAXSIZE && m_test  != MAXSIZE - i)
            {
                std::cout << "WRONG" << std::endl;
                exit(1);
            }
            else if (i > MAXSIZE && m_test  != i - MAXSIZE - 1)
            {
                std::cout << "WRONG" << std::endl;
                exit(1);
            }
        }
        std::cout << "OK" << std::endl;
    }

    /* ------ */

    /* TEST 2
     *
     * Iterate Clear
     *
     */
    std::cout << "Test 2  ";
    {
        CSingleLinkedList<int> list;
        for (int i = 0; i < MAXSIZE; ++i) {
            list.pushBack(i);
        }
        CSingleLinkedList<int>::CIterator it = list.begin();
        size_t i = 0;
        while (it != list.end()) {
            int src = it.getData();
            if (src != i) {
                std::cout << "WRONG" << std::endl;
                exit(1);
            }
            ++i;
            ++it;
        }
        list.clear();
        if (list.getSize() != 0) {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        std::cout << "OK" << std::endl;
    }

    /* ------ */

    /* TEST 3
     *
     * Erase
     *
     */
    std::cout << "Test 3  ";
    {
        CSingleLinkedList<int> list;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            list.pushFront(i);
        }
        CSingleLinkedList<int>::CIterator it = list.begin();
        list.erase(it);
        ++it;
        if (it != list.begin())
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        while (it != list.end())
        {
            list.erase(it);
            ++it;
        }
        list.erase(it);
        if (list.getSize() != 0)
        {
            std::cout << "WRONG" << std::endl;
            exit(1);
        }
        std::cout << "OK" << std::endl;
    }
    /* ------ */

    return 0;
}

