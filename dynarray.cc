
#define INITIAL_CAPACITY 1

#define DEBUG

#include <stdio.h>
#include <stdlib.h>

#include "dynarray.h"

void Cry(int condition,const char* error = ""){
        if (condition){
            fprintf (stderr, "ERROR: %s", error);
            exit(-1);
        }
}

void Vector::Initialize(int h){
    capacity = INITIAL_CAPACITY;
    cellsize = h;
    length = 0;
    data = NULL;
    AllocateData();
}

//default count = 1
int Vector::Extend (int count){
    if ((capacity - length) < count){
        while (capacity < length + count){
            capacity *= 2;
        }
        AllocateData();
    }

    length += count;

    return length;
}

void Vector::AllocateData(){
    data = realloc (data, cellsize * capacity);
    //#ifdef DEBUG
    Cry(data == NULL, "Realloc Error in vector");
    //#endif
}
