#ifndef TOOLS
#define TOOLS

#include <stdio.h>
#include <stdlib.h>

class Tools{
public:
    static void Cry(int condition, char* error = ""){
        if (condition){
            fprintf (stderr, "ERROR: %s", error);
            exit(-1);
        }
    }
};


#endif
