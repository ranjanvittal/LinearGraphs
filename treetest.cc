#include "tree.h"

#include <iostream>

using namespace std;

class A{
public:
    int a;

    virtual int aaa(){
        return 0;
    }
    /*
    virtual int aba(){
        return 0;
    }
    */

};

class B : public A{
public:
    int b;
//    int c;
};

class C : public B{
public:
    int f;
//    int g;
};


int main() {
    int sizes[] = {sizeof(C), sizeof(B)};

    Tree t(2, sizes, 1, true);

    printf ("Vector = %d x %d\n", t.graph.cellsize, t.graph.capacity);

    register int a, b, c, d;
    a = t.AddNode();
    b = t.AddNode();
    c = t.AddNode();
    //t.Print();
    t.AddEdge(a, b);
    //t.Print();
    t.AddEdge(c, b);
    //t.Print();
    t.AddEdge(a, c);

    d = t.AddNode();

    C *a1, *b1, *c1, *d1;

    a1 = (C*)t.GetDataRow(a, 0);
    a1->f = 5;

    b1 = (C*)t.GetDataRow(b, 0);
    b1->f = 6;

    c1 = (C*)t.GetDataRow(c, 0);
    c1->f = 11;

    d1 = (C*)t.GetDataRow(d, 0);
    d1->f = 9;

    a1 = (C*)t.GetDataRow(a, 0);
    b1 = (C*)t.GetDataRow(b, 0);
    c1 = (C*)t.GetDataRow(c, 0);
    d1 = (C*)t.GetDataRow(d, 0);

    cout << "Row 1 = " << a1->f << " " << b1->f << " " << c1->f << " " << d1->f << " ";


    B *a2, *b2, *c2, *d2;

    a2 = (B*)t.GetDataRow(a, 1);
    a2->b = 5;

    b2 = (B*)t.GetDataRow(b, 1);
    b2->b = 6;

    c2 = (B*)t.GetDataRow(c, 1);
    c2->b = 22;

    d2 = (B*)t.GetDataRow(d, 1);
    d2->b = 9;

    a2 = (B*)t.GetDataRow(a, 1);
    b2 = (B*)t.GetDataRow(b, 1);
    c2 = (B*)t.GetDataRow(c, 1);
    d2 = (B*)t.GetDataRow(d, 1);

    cout << "Row 2 = " << a2->b << " " << b2->b << " " << c2->b << " " << d2->b << " ";


    t.Print();


    return 555;
}
