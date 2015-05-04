

#include "dynarray.h"
#include "tree.h"

#include <string.h>

#include <stdlib.h>

#include <iostream>

#include <stdio.h>


using namespace std;

static int* map;
int cellsize;

int CompareMap (int n1, int n2, void* vmap);
int DFSPre(int id);





void dummy(int n1){
    return;
}




//int dd = DEFAULT_DEGREE, bool undir = false
Tree::Tree(int hcount, int sizes[], int dd, bool undir) {
    default_degree = dd;
    cellsize = sizeof(Node) + (default_degree - 1) * sizeof (int);
    graph.Initialize(cellsize);
    undirected = undir;
    node_count = 0;


    sat_rows = hcount;
    sat = (Vector*)malloc(sizeof(Vector)*hcount);

    register int i;

    for(i = 0; i < hcount; i++) {
        sat[i].Initialize(sizes[i]);
    }

    main_cells = NULL;
}


void Tree::Print(){
    printf ("\n\n");
    register int i;
    for (i = 0; i < graph.length; i++){
        Node* n = Access(Node*, graph, i);
        printf ("\nCell %d\tNode %d\tNatr %d\tNext %2d\tSatData %d\tEdges", i, n->id, n->natural, n->extension, n->sat_id);

        register int j;
        for (j=0; j < default_degree; j++){
            printf (" %d ", n->edge[j]);
        }
    }

    printf ("\n\nMap:");
    for (i = 0; i < node_count; i++){
        printf (" %2d", map_natural_to_node[i]);
    }

    printf ("\n\n");
}

void * Tree::GetDataRow(int id, int sat_row) {
    id = map_natural_to_node[id];
    register Node* n = Access(Node*, graph, id);
    return Access(void*, sat[sat_row], n->sat_id);
}

void ** Tree::GetData(int id, void** ptrs) {
    register int i;
    if(ptrs == NULL) {
        ptrs = (void**) malloc(sizeof(void*)*sat_rows);
    }

    for(i = 0; i < sat_rows; i++) {
        ptrs[i] = GetDataRow(id, i);
    }

    return (void**) ptrs;
}

int Tree::AddNode (){
    register int id = graph.Extend() - 1;
    register Node* n = Access (Node *, graph, id);

    n->id = id;
    n->sat_id = node_count;
    n->natural = node_count++;
    map_natural_to_node.push_back(id);

    register int i;
    for(i = 0; i < sat_rows; i++) {
        sat[i].Extend();
    }

    n->extension = -1;

    for (i = 0; i < default_degree; i++){
        n->edge[i] = -1;
    }

    return n->natural;
}



int Tree::AddNodePrivate (Node* nParent){
    register int pid, sid, natural;
    pid = nParent->id;
    sid = nParent->sat_id;
    natural = nParent->natural;

    register int id = graph.Extend() - 1;
    register Node* n = Access (Node *, graph, id);


    n->id = pid;
    n->sat_id = sid;
    n->natural = natural;
    n->extension = -1;


    register int i;
    for (i = 0; i < default_degree; i++){
        n->edge[i] = -1;
    }

    return id;
}

void Tree::AddEdge (int id1, int id2) {
    id1 = map_natural_to_node[id1];
    id2 = map_natural_to_node[id2];

    AddDirectedEdge(id1, id2);
    if(undirected)
        AddDirectedEdge(id2, id1);
}

void Tree::AddDirectedEdge(int id1, int id2) {
    register Node* n1 = Access(Node *, graph, id1);
    if(n1->edge[default_degree-1] == -1) {
        register int i;
        for( i = 0; i < default_degree; i++){
            if(n1->edge[i] == -1) {
                n1->edge[i] = id2;
                return;
            }
        }

    }
    else {
        register Node* n1e;

        if (n1->extension != -1){
            n1e = Access(Node*, graph, n1->extension);
            if(n1e->edge[default_degree-1] == -1) {
                register int i;
                for( i = 0; i < default_degree; i++){
                    if(n1e->edge[i] == -1){
                        n1e->edge[i] = id2;
                        return;
                    }
                }
            }

        }

        register int new_extension = AddNodePrivate(n1);

        n1 = Access(Node *, graph, id1);
        n1e = Access(Node*, graph, new_extension);

        n1e->extension = n1->extension;
        n1->extension = new_extension;
        n1e->edge[0] = id2;
    }

}

bool Tree::IsNeighbour(int id1, int id2) {
    id1 = map_natural_to_node[id1];
    id2 = map_natural_to_node[id2];

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


void Tree::Sort  (int (*compare) (int natural1, int natural2, void* map), void* map){
    register int l = graph.length;
    main_cells = (int*) malloc (l * sizeof(int));

    register Node* currentnode;
    register int currentid;

    register int i;
    register int j;

    for (i = 0; i < l; i++){
        currentnode = Access(Node *, graph, i);
        main_cells[i] = (i == currentnode->id);
    }

    tempnode = (Node *) malloc (cellsize);

    SortPrivate (compare, map, graph.length, 0);

    free (tempnode);

    int* new_id = (int*) malloc (l * sizeof(int));

    Node * previousnode;
    currentnode = NULL;

    for(i = 0; i < l; i++) {
        previousnode = currentnode;
        currentnode = Access(Node *, graph, i);
        if(main_cells[i] == 1) {
            currentid = currentnode->id;
            new_id[currentid] = i;
            currentnode->id = i;
            currentid = i;

            if (previousnode != NULL){
                previousnode->extension = -1;
            }
        }
        else {
            currentnode->id = currentid;
            previousnode->extension = i;
        }
    }
    currentnode->extension = -1;

    for(i = 0; i < l; i++) {
        currentnode = Access(Node *, graph, i);
        for( j = 0; j < default_degree; j++) {
            if (currentnode->edge[j] != -1){
                currentnode->edge[j] = new_id[currentnode->edge[j]];
            }
        }
    }

/*
    int current_extension;
    Node * prevnode = Access(Node *, graph, 0);

    for(i = 1 ; i < l; i ++ ) {
        currentnode = Access(Node *, graph, i);
        while(currentnode->id == prevnode->id) {
            prevnode->extension = i;
            prevnode = currentnode;
            currentnode = Access(Node *, graph, i);
            i++;
        }
        prevnode = currentnode;
    }
    */



    free (main_cells);
    free (new_id);

    SatSort();
}


void Tree::SortPrivate(int (*compare) (int natural1, int natural2, void* map), void* map, int n, int start){
    static int calls = 0;

    //Print();

    //cout << "Number of calls so far = " << calls++ << "\n";

    if (n <= 1) {
        return;
    }
    else {
        int pivotindex = Partition (n, start, compare, map);
        //cout << "pivotIndex, n = " << pivotindex << ", " << n  << "\n";

        //printf ("Calling first %d, %d\n", pivotindex, start);
        SortPrivate (compare, map, pivotindex - start, start);


        //printf ("Calling second %d, %d\n", (n - pivotindex -1), start + pivotindex + 1);
        SortPrivate (compare, map, (n - (pivotindex - start) -1), pivotindex + 1);

        //printf ("Out\n");
        return;
    }
}










int Tree::Partition(int n, int start, int (*compare) (int node1, int node2, void* map), void* map){
    Swap (start + (rand() % n), start + n -1);


    int currentelement = start;
    int pivotindex = start;
    register int result;

    register Node* currentnode;
    register int currentid;
    int currentn;

    register Node* pivotnode = Access(Node *, graph, start + n-1);
    int pivotn;
    int pivotid = pivotnode->id;
    pivotn = pivotnode->natural;

    while (1){
        currentnode = Access(Node *, graph, currentelement);
        currentid = currentnode->id;
        currentn = currentnode->natural;

        //If compare is 1, then currentid will go earlier in the array
        //cerr << "Current element = " << currentelement << " <= " << graph.length << "\n";


        result = (compare(currentn, pivotn, map) > 0);
        //result = (currentid > pivotid);
        result = result || (main_cells[currentelement] && (currentid == pivotid));

        if ((main_cells[start + n - 1] && (currentid == pivotid))){
            result = 0;
        }

        result = result || (currentelement == start + n - 1);

        result = result || ((currentnode->edge[default_degree-1] == -1) && !main_cells[start + n - 1] && (currentid == pivotid));

        if (result){
            //cerr << "Comparing " << currentid << " with pivot " << pivotid << "(currentelement " << currentelement << ") : " << result << "\n";

            Swap (currentelement, pivotindex);

            //cerr << "currentelement = " << currentelement << "\t limit = " << start + n - 1 << "\n";

            if (currentelement == start + n - 1) {
                //cerr << "\tAL HABIBI EE TU HAIL RUL MAN KI MANN\n";
                return pivotindex;
            }
            //else cerr << "\tAL HABIBI EE TU HAIL RUL MAN KI MANN\n";
            pivotindex++;
        }
        currentelement++;
    }

    return pivotindex;
}







void Tree::Swap( int a, int b){
    if (a == b) return;

    register Node* n1 = Access(Node *, graph, a);
    register Node* n2 = Access(Node *, graph, b);

    memcpy (tempnode, n1, graph.cellsize);
    memcpy (n1, n2, graph.cellsize);
    memcpy (n2, tempnode, graph.cellsize);

    register int temp;

    temp = main_cells[a];
    main_cells[a] = main_cells[b];
    main_cells[b] = temp;

    if(main_cells[a])
        map_natural_to_node[n1->natural] = a;

    if(main_cells[b])
        map_natural_to_node[n2->natural] = b;

    return;
}



void Tree::DFS(int node_id) {
    DFS (node_id, DFSPre, dummy);
}


void Tree::DFS (int node_id, int (*previsit) (int node_id1), void (*postvisit) (int node_id), bool is_natural){
    if(is_natural)
        node_id = map_natural_to_node[node_id];
    //Pre-visit
    if (previsit (node_id) == 0){
        return;
    }

    int currentindex = node_id;
    Node* currentcell = Access(Node *, graph, currentindex);
    register int edge;
    register int neighbour;



    while (1){
        //Print();

        for (edge = 0; edge < default_degree; edge++){
            neighbour = currentcell->edge[edge];
            //cerr << neighbour << endl;
            if (neighbour != -1){
                DFS (neighbour, previsit, postvisit, false);
            }
        }

        if (currentcell->extension == -1){
            break;
        }
        else {
            currentcell = Access(Node *, graph, currentcell->extension);
        }
    }

    postvisit(node_id);
}


int Tree::DFSOptimizer(int rootnode){

    map = (int* ) calloc (graph.length, sizeof(int));

    DFS(rootnode, DFSPre, dummy);


    /*
    //Print Map
    int i;
    for (i = 0; i < graph.length; i++){
        printf ("%d ", map[i]);
    }
    printf ("\n\n");
    */


    Sort  (CompareMap, map);

    free(map);

    return rootnode;
}



int DFSPre(int id){
    //cerr << "DFSPre on node " << id << "\n";


    static int s = 0;
    if (map[id] == 0) {
        map[id] = ++s;
        // cout<<" , "<<id;
        return 1;
    }
    else {
        return 0;
    }
}


int CompareMap (int n1, int n2, void* vmap){
    int* imap = (int*) vmap;

    return (((imap[n1] < imap[n2]) && (imap[n1] > 0)) || (imap[n2] == 0));
}




void Tree::SatSort (){
    int * tempmap;
    tempmap = map;
    map = (int*) malloc (node_count * sizeof(int));

    register int i;
    register Node * n;

    for (i = 0; i < graph.length; i++){
        n = Access(Node *, graph, i);
        if (n->id == i){
            map[n->sat_id] = i;
        }
    }

    SatSortPrivate (node_count, 0);

    free (map);
    map = tempmap;

    int satid;
    for (i = 0; i < graph.length; i++){
        n = Access(Node *, graph, i);
        if (n->id == i){
            satid = n->sat_id;

            while (n->extension != -1){
                n = Access(Node *, graph, n->extension);
                n->sat_id = satid;
            }
        }
    }
}







void Tree::SatSortPrivate(int n, int start){
    //static int calls = 0;

    //Print();

    //cout << "Number of calls so far = " << calls++ << "\n";

    if (n <= 1) {
        return;
    }
    else {
        int pivotindex = SatPartition (n, start);
        //cout << "pivotIndex, n = " << pivotindex << ", " << n  << "\n";

        //printf ("Calling first %d, %d\n", pivotindex, start);
        SatSortPrivate (pivotindex - start, start);


        //printf ("Calling second %d, %d\n", (n - pivotindex -1), start + pivotindex + 1);
        SatSortPrivate ((n - (pivotindex - start) -1), pivotindex + 1);

        //printf ("Out\n");
        return;
    }
}










int Tree::SatPartition(int n, int start){
    SatSwap (start + (rand() % n), start + n -1);


    int currentelement = start;
    int pivotindex = start;

    while (1){
        if (map[currentelement] <= map[start + n - 1]){
            //cerr << "Comparing " << currentid << " with pivot " << pivotid << "(currentelement " << currentelement << ") : " << result << "\n";

            SatSwap (currentelement, pivotindex);

            //cerr << "currentelement = " << currentelement << "\t limit = " << start + n - 1 << "\n";

            if (currentelement == start + n - 1) {
                //cerr << "\tAL HABIBI EE TU HAIL RUL MAN KI MANN\n";
                return pivotindex;
            }
            //else cerr << "\tAL HABIBI EE TU HAIL RUL MAN KI MANN\n";
            pivotindex++;
        }
        currentelement++;
    }

    return pivotindex;
}







void Tree::SatSwap( int a, int b){
    if (a == b) return;

    Node* n1 = Access(Node *, graph, map[a]);
    Node* n2 = Access(Node *, graph, map[b]);
    int temp;
    int i;
    temp = map[a];
    map[a] = map[b];
    map[b] = temp;
    temp = n1->sat_id;
    n1->sat_id = n2->sat_id;
    n2->sat_id = temp;

    void* s1;
    void* s2;
    void* tempsat;

    for(i = 0; i < sat_rows; i++) {
        int cellsize = sat[i].cellsize;
        tempsat = malloc(cellsize);
        s1 = Access(void *, sat[i], a);
        s2 = Access(void *, sat[i], b);
        memcpy (tempsat, s1, cellsize);
        memcpy (s1, s2, cellsize);
        memcpy (s2, tempsat, cellsize);

        free(tempsat);
    }

    return;
}
