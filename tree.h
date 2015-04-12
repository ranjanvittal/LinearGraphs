#ifndef LINEAR_TREE
#define LINEAR_TREE

#include "dynarray.h"

#define DEFAULT_DEGREE 3


class Node{
public:
    int id;
    int extension;

    //Should be the last attribute
    int edge[1];
};



class Tree{
public:
    int default_degree;
    Vector graph;
    int cellsize;
    bool undirected;



    Tree(bool undir = false, int dd = DEFAULT_DEGREE){
        default_degree = dd;
        cellsize = sizeof(Node) + (default_degree - 1) * sizeof (int);
        graph.Initialize(cellsize);
        undirected = undir;
    }


    void Print(){
        printf ("\n\n");
        register int i;
        for (i = 0; i < graph.length; i++){
            Node* n = Access(Node*, graph, i);
            printf ("\nCell %d\tNode %d\tNext %d\tEdges", i, n->id, n->extension);

            register int j;
            for (j=0; j < default_degree; j++){
                printf (" %d ", n->edge[j]);
            }
        }
        printf ("\n\n");
    }


    int AddNode (int nid = -1){
        register int id = graph.Extend() - 1;
        register Node* n = Access (Node *, graph, id);

        if(nid == -1)
            n->id = id;
        else
            n->id = nid;

        n->extension = -1;

        register int i;
        for (i = 0; i < default_degree; i++){
            n->edge[i] = -1;
        }

        return id;
    }

    void AddEdge (int id1, int id2) {
        AddDirectedEdge(id1, id2);
        if(undirected)
            AddDirectedEdge(id2, id1);
    }

    void AddDirectedEdge(int id1, int id2) {
        register Node* n1 = Access(Node *, graph, id1);
        if(n1->edge[default_degree-1] == -1) {
            register int i;
            for( i = 0; i < default_degree; i++){
                if(n1->edge[i] == -1) {
                    n1->edge[i] = id2;
                    break;
                }
            }

        }
        else {
            register Node* n1e = Access(Node*, graph, n1->extension);
            if(n1e->edge[default_degree-1] == -1) {
                register int i;
                for( i = 0; i < default_degree; i++){
                    if(n1e->edge[i] == -1){
                        n1e->edge[i] = id2;
                        break;
                    }
                }
            }
            else {
                register int new_extension = AddNode(id1);
                n1e = Access(Node*, graph, new_extension);
                n1e->extension = n1->extension;
                n1->extension = new_extension;
                n1e->edge[0] = id2;
            }
        }

    }

    bool IsNeighbour(int id1, int id2) {
        register Node* n1 = Access(Node *, graph, id1);
        register int i;
        for( i = 0; i < default_degree; i ++ ) {
            if(id2 == n1->edge[i])
                return true;
        }
        register int extension = n1->extension;
        if(n1->extension >= 0)
            return IsNeighbour(extension, id2);
        return false;
    }

};



#endif
