#ifndef LINEAR_TREE
#define LINEAR_TREE

#include "dynarray.h"

#define DEFAULT_DEGREE 3



struct Node {
    int id;
    int extension;
    int sat_id;

    //Should be the last attribute
    int edge[1];
};





class Tree{

public:

    /*
    Tree Constructor taking parameters as :
        hcount = Number of hierarchies
        sizes = Array with sizes of each hierarchy
        dd = Default degree for optimum construction
        undir = Is the graph undirected?
    */
    Tree(int hcount, int sizes[], int dd = DEFAULT_DEGREE, bool undir = false);




    /*
    GetDataRow
        Returns the data of a node corresponding to a class hierarchy

        Parameters
            node_id = ID of the node whose data you want
            sat_row = Index of the class hierarchy whose data you want
    */
    void * GetDataRow(int node_id, int sat_row);




    /*
    GetDataRow
        Returns all data of a node in the form of an array of pointers.

        Parameters
            node_id = ID of the node whose data you want
            ptrs = Array of pointers appropriately sized. If this is NULL,
                   then an array is allocated by GetData
    */
    void ** GetData(int node_id, void** ptrs);




    /*
    AddNode
        Adds a node to the graph

    */
    int AddNode ();




    /*
    AddEdge
        Adds an edge to the graph

        Parameters
            node_id1 = First node
            node_id2 = Second node
    */
    void AddEdge (int node_id1, int node_id2);


    /*
    AddEdge
        Adds an edge to the graph

        Parameters
            node_id1 = First node
            node_id2 = Second node
    */
    void AddDirectedEdge(int id1, int id2);



    /*
    IsNeighbour
        Checks if two nodes are neighbours

        Parameters
            node_id1 = First node
            node_id2 = Second node
    */
    bool IsNeighbour(int node_id1, int node_id2);


    /*
    Print
        Used for development, testing and design purposes.

        We use the output of this to contemplate what further
        improvements can be inducted into the project.

    */
    void Print();




    /*
        Sort based on comparion
        *compare = Element comparator function that accepts arguments node1, node2, and a map
                   (Note that third parameter must be there)

        map = A map of comparison that is passed as-is to the compare function
                   (pass NULL if this is unnecessary)

        This is also the wrapper for SortPrivate function.

    */
    void Sort(int (*compare) (int node1, int node2, void* map), void* map);


    //The vector storing nodes
    Vector graph;

    /*
        Function to go through the nodes in a DFS manner and do previsit and postvisit
        on the nodes.
        Parameters :
            node_id: Root node
            previsit : Function executed on visiting the node.
            postvisit: Function executed after traversing the subtree rooted at the node and returning to the parent

    */
    void DFS (int node_id, int (*previsit) (int node_id), void (*postvisit) (int node_id) );
    int DFSOptimizer(int rootnode);


private:
    //The default number of edges stored in each node
    int default_degree;



    //Whether the graph is undirected
    bool undirected;

    //Number of nodes in the graph so far
    int node_count;

    //Array of vectors to store satellite data
    Vector* sat;

    //Number of class hierarchies to be stored as satellite data
    int sat_rows;

    //Helper function
    int AddNodePrivate (Node* nParent);

    //Sort Helper
    int* main_cells;

    // Used for swapping
    Node* tempnode;

    // Private function used to sort based on comparison. More of a sort helper.
    void SortPrivate(int (*compare) (int node1, int node2, void* map), void* map, int n, int start);

    /* Partitioning for Sorting */
    int Partition(int n, int start, int (*compare) (int node1, int node2, void* map), void* map);

    /* Swapping two nodes by taking their node id's */
    void Swap( int a, int b);

    /* Swapping two satellite by taking their node id's */
    void SatSwap( int a, int b);

    /* Partitioning for Sorting */
    int SatPartition(int n, int start);

    /* Sorting satellite data */
    void SatSort();
    void SatSortPrivate(int n, int start);
};



#endif
