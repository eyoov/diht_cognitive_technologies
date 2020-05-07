#include "../list.h"
#include <iostream>

using namespace utility;

int main(){

    static const int MAXSIZE = 1000;

    /* TEST 1
     *
     * size InQueue
     *
     */
    std::cout << "Test 1" << std::endl;
    {
        CQueue<int> queue;
        for (int i = 0; i < MAXSIZE; ++i)
        {
            queue.InQueue(i);
        }
        if (queue.getSize() != MAXSIZE)
        {
            std::cout << "SIZE WRONG" << std::endl;
            exit(1);
        }
        for (int i = 0; i < MAXSIZE; ++i)
        {
            if (queue.DeQueue() != i)
            {
                std::cout << "INQUEUE WRONG" << std::endl;
                exit(1);
            }
        }
        std::cout << "OK" << std::endl;
    }
    /* -------- */

    /* TEST 2
     *
     * clear IsQueueEmpty
     *
     */
    std::cout << "Test 2" << std::endl;
    {
        CQueue<int> queue;
        if (!queue.isQueueEmpty())
        {
            std::cout << "ISQUEUEEMPTY WRONG" << std::endl;
            exit(1);
        }
        for (int i = 0; i < MAXSIZE; ++i)
        {
            queue.InQueue(i);
        }
        queue.clear();
        if (queue.getSize() != 0)
        {
            std::cout << "CLEAR WRONG" << std::endl;
            exit(1);
        }
        std::cout << "OK" << std::endl;
    }
    /* -------- */

    return 0;
}

