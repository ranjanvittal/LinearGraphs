#ifndef DYNARRAY
#define DYNARRAY

#define INITIAL_CAPACITY 1


#include <stdlib.h>

#define Access(type, v, i) ((type)((char*)((v).data) + ((v).cellsize * (i))))

class Vector{
public:
    // Data stored at this location
    void * data;

    // Number of elements stored so far
    int length;

    // Number of cells allocated so far
    int capacity;

    // Size of a cell
    int cellsize;

    /*
    Initialize
        Parameters :
            cellsize = How much cellsize you need.
    Initializing vector based on how much cellsize is required.
    */
    void Initialize(int cellsize);

    /*
    Extend
        Parameters :
            count = How many more elements you want to add.
    */
    int Extend (int count = 1);

private:
    /* AllocateData :
            private function used to allocate more space if and when required.
    */
    void AllocateData();
};

#endif
