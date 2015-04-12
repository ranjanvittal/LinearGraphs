#include "tree.h"

#include <iostream>


int main() {
    Tree t(true, 1);

    printf ("Vector = %d x %d\n", t.graph.cellsize, t.graph.capacity);

    register int a, b, c;
    a = t.AddNode();
    b = t.AddNode();
    c = t.AddNode();
    printf ("\n------------\n");
    t.Print();
    t.AddEdge(a, b);
    t.Print();
    t.AddEdge(c, b);
    t.Print();
    t.AddEdge(a, c);

    t.Print();


    return 555;
}
