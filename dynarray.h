#ifndef DYNARRAY
#define DYNARRAY

#define INITIAL_CAPACITY 1

#include "tools.h"

#include <stdlib.h>

#define Access(type, v, i) ((type)((char*)((v).data) + ((v).cellsize * (i))))

class Vector{
public:
    void * data;
    int length;
    int capacity;
    int cellsize;

    void Initialize(int h){
        capacity = INITIAL_CAPACITY;
        cellsize = h;
        length = 0;
        data = NULL;
        AllocateData();
    }

    int Extend (int count = 1){
        if ((capacity - length) < count){
            while (capacity < length + count){
                capacity *= 2;
            }
            AllocateData();
        }

        length += count;

        return length;
    }




private:
    void AllocateData(){
        data = realloc (data, cellsize * capacity);
        #ifdef DEBUG
        Tools.Cry(data == NULL, "Realloc Error in vector");
        #endif
    }
};


#endif
