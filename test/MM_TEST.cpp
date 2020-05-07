#include "../mm.h"
#include <iostream>

using namespace std;
using namespace utility;

struct example_data_structure
{
    int _example_field;

    example_data_structure(int _val) :_example_field(_val) {}

    example_data_structure(): _example_field() {}

    bool operator== (const example_data_structure other) const
    {
        return (_example_field == other._example_field);
    }
};

int main()
{
    const int MAXSIZE = 10000;
    const int BLOCKSIZE = 1000;

    /*
     * Test 1
     */

    {
        std::cout << "Test 1" << std::endl;

        CMemoryManager<example_data_structure> M(BLOCKSIZE, false);
        example_data_structure* array[2 * MAXSIZE];
        for (int i = 0; i < MAXSIZE; ++i)
        {
            array[i] = M.newObject();
            array[i]->_example_field = i;
        }

        for (int i = 0; i < MAXSIZE; i = i + 2)
        {
            M.deleteObject(array[i]);
        }

        for (int i = MAXSIZE; i < 2 * MAXSIZE; ++i)
        {
            array[i] = M.newObject();
            array[i]->_example_field = i;
        }
        for (int i = 1; i < 2 * MAXSIZE; i = i + 2)
        {
            M.deleteObject(array[i]);
        }

        try
        {
            M.clear();
        }
        catch (CException)
        {
            std::cout << "catched" << std::endl;
        }

        for (int i = (MAXSIZE % 2 == 0) ? MAXSIZE : (MAXSIZE - 1); i < 2 * MAXSIZE; i = i + 2)
        {
            M.deleteObject(array[i]);
        }
        M.clear();
    }



    /*
     * Test 2
     */

    {
        std::cout << "Test 2" << std::endl;

        CMemoryManager<example_data_structure> M(BLOCKSIZE, true);
        example_data_structure* array[2 * MAXSIZE];
        for (int i = 0; i < MAXSIZE; ++i)
        {
            array[i] = M.newObject();
            array[i]->_example_field = i;
        }

        for (int i = 0; i < MAXSIZE; i = i + 2)
        {
            M.deleteObject(array[i]);
        }

        for (int i = MAXSIZE; i < 2 * MAXSIZE; ++i)
        {
            array[i] = M.newObject();
            array[i]->_example_field= i;
        }
        for (int i = 1; i < 2 * MAXSIZE; i = i + 2)
        {
            M.deleteObject(array[i]);
        }

        M.clear();
    }

    return 0;
}

