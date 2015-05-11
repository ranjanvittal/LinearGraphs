#include "graph.h"
#include "random.h"
#include "../tree.h"
#include "graphMat.h"
#include "satellite.h"
#include <iostream>
#include <ctime>
#include <sys/time.h>


#include "parameters.h"
int ov = 0;
long long CURRENT_TIME() {
    timeval tv;
    gettimeofday(&tv, NULL);
    long long current_time = tv.tv_usec + tv.tv_sec*1000000;
    return current_time;
}

using namespace std;

int maps[TREE_SIZE+3];

void pre_set(int run_type, Tree t, void* to_set) {
	if(run_type == 1)
	{
		A* node = (A*) to_set;
		node->len = 100;
		for(int i = 0; i < 100; i++)
		{
			node->a[i] = i;
		}
	}

	else if(run_type == 2)
	{
		B* node = (B*) to_set;
		node->len = 200;
		for(int i = 0; i < 200; i++)
		{
			node->a[i] = i;
		}

	}

	else if(run_type == 3)
	{
		C* node = (C*) to_set;
		node->len = 300;
		for(int i = 0; i < 300; i++)
		{
			node->a[i] = i;
		}

	}

	else if(run_type == 4)
	{
		D* node = (D*) to_set;
		node->len = 400;
		for(int i = 0; i < 400; i++)
		{
			node->a[i] = i;
		}

	}

	else if(run_type == 5)
	{
		E* node = (E*) to_set;
		node->len = 500;
		for(int i = 0; i < 500; i++)
		{
			node->a[i] = i;
		}

	}

	else if(run_type == 6)
	{
		F* node = (F*) to_set;
		node->len = 600;
		for(int i = 0; i < 600; i++)
		{
			node->a[i] = i;
		}

	}
}

timespec TimeDifference(timespec start, timespec end)
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}



void initLinTreeDFS (){
	int i;
	for (i = 0; i < TREE_SIZE; i++){
        maps[i] = 0;
	}
}


void pre_visit(A* val, int id) {
	int i;
	// cout << id << endl;
	for(i = 0; i < 100; i++) {
		val->a[i] += 1;
		ov++;
	}
}

void pre_visit(B* val, int id) {
	int i;
	// cout << id << endl;
	for(i = 0; i < 200; i++) {
		val->a[i] += 1;
		ov++;
	}
}

void pre_visit(C* val, int id) {
	int i;
	// cout << id << endl;
	for(i = 0; i < 300; i++) {
		val->a[i] += 1;
		ov++;
	}
}

void pre_visit(D* val, int id) {
	int i;
	// cout << id << endl;
	for(i = 0; i < 400; i++) {
		val->a[i] += 1;
		ov++;
	}
}

void pre_visit(E* val, int id) {
	int i;
	// cout << id << endl;
	for(i = 0; i < 500; i++) {
		val->a[i] += 1;
		ov++;
	}
}

void pre_visit(F* val, int id) {
	int i;
	// cout << id << endl;
	for(i = 0; i < 600; i++) {
		val->a[i] += 1;
		ov++;
	}
}

int pre_visit(Tree* tree, int id){
	static int count = 0;

    if (maps[id] == 0) {
		//printf ("%d\n", ++count);
        maps[id] = 1;
        int i;
        A* val = (A*) tree->GetDataRow(id, 0);
        switch(val->len) {
        	case 100 : {pre_visit((A*) val, id); break;}
        	case 200 : {pre_visit((B*) val, id); break;}
        	case 300 : {pre_visit((C*) val, id); break;}
        	case 400 : {pre_visit((D*) val, id); break;}
        	case 500 : {pre_visit((E*) val, id); break;}
        	case 600 : {pre_visit((F*) val, id); break;}
        }

        return 1;
    }
    else return 0;
}




void dummy2(Tree* t, int n1){
    return;
}

#ifdef ADJ
void AddEdge (int a, int b, Tree& tree, graph& list, graphMat& matrix){
#else
void AddEdge (int a, int b, Tree& tree, graph& list){
#endif
    list.add_edge(a, b);

	#ifdef ADJ
    matrix.add_edge(a, b);
	#endif

    tree.AddEdge(a, b);
}


#ifdef ADJ
void GenerateTree (Tree& tree, graph& list, graphMat& matrix){
#else
void GenerateTree (Tree& tree, graph& list){
#endif
	srand (time(NULL));

    for(int i = 0; i < TREE_SIZE; i++){

        int v = tree.AddNode();
        int runtype = randomNumber(6,1);
        list.add_vertex(v,runtype);
		#ifdef ADJ
        matrix.add_vertex(v,runtype);
		#endif
		void* val = tree.GetDataRow(v, 0);
		pre_set(runtype, tree, val);
    }

	int component[TREE_SIZE];
	int remaining[TREE_SIZE];

	int i, j;
	for (i = 0; i < TREE_SIZE; i++){
		component[i] = 0;
		remaining[i] = 1;
	}
	component[0] = 0;
	remaining[0] = 0;

	int picked = 1;

	while (picked < TREE_SIZE){
		i = rand() % TREE_SIZE;

		while (remaining[i] == 0){
			i = (i + 1) % TREE_SIZE;
		}

		j = component[rand() % picked];

		component[picked] = i;
		remaining[i] = 0;

		#ifdef ADJ
		AddEdge (i, j, tree, list, matrix);
		#else
		AddEdge (i, j, tree, list);
		#endif
        picked++;
	}
}




/*
Test case 1:
		Build a random graph which essentially have lesser degree nodes.
Parameters:
		Takes references for Tree(Arrayed Tree) , graph(adjacency lists) , graphMat(Addjacency Matrix)
		to populate the graph
*/

// void build_random_graph(graph& g,Tree& t,graphMat& gm){

// 	int vertices  =  randomNumber(99,1);

// 	int edges  =  randomNumber(min(400,vertices*(vertices-1)/2),100);


// 	for(int i = 0;i<edges;i++){

// 		int a = randomNumber(vertices-1,0);
// 		int b = randomNumber(vertices-1,0);
// 		g.add_edge(a,b);
// 		t.AddEdge (a,b);
// 		gm.add_edge(a,b);

// 	}

// }

/*
Test case 2:
		Build a random graph which essentially have higher degree nodes.
Parameters:
		Takes references for Tree(Arrayed Tree) , graph(adjacency lists) , graphMat(Addjacency Matrix)
		to populate the graphs
*/

// void build_over_degree_random_graph(graph& g,Tree& t,graphMat& gm){

// 	int vertices  =  randomNumber(99,1);

// 	int edges  =  randomNumber(min(400,vertices*(vertices-1)/2),100);

// 	for(int i = 0;i<vertices;i++){

// 		int v = t.AddNode();
// 		int runtype  =  randomNumber(6,1);
// 		g.add_vertex(v,runtype);
// 		gm.add_vertex(v,runtype);

// 	}

// 	for(int i = 0;i<vertices;i++){

// 		int deg  =  randomNumber(vertices-1,1);
// 		for(int j = 0;j<deg;j++){
// 			int v  =  randomNumber(vertices-1,1);
// 			g.add_edge(i,v);
// 			t.AddEdge(i,v);
// 			gm.add_edge(i,v);
// 		}

// 	}
// }

/*
Time comparison method which essentially which runs DFS for TIMES(1000) number of times.
*/
#ifdef ADJ
void Time_Comparison(Tree& tree, graph& list, graphMat& matrix){
#else
void Time_Comparison(Tree& tree, graph& list){
#endif

	timespec start, end;


    /*

    Time Evaluation for adjacency lists implemenatation.

    */
	long long st = CURRENT_TIME();
	int val1;
    for(int i = 0;i<TIMES;i++)
    	val1 = list.init_dfs();
	long long en = CURRENT_TIME();
    std::cout << "Normal Graph (Adjacency lists) :\t";
	std::cout << (en - st)/1000000.0;
	std::cout <<" seconds\n" << endl;
	cout << val1 << endl;



    /*

    Time Evaluation for Arrayed tree implemenatation.

    */




    tree.DFSOptimizer (0);
	st = CURRENT_TIME();

    for(int i = 0;i<TIMES;i++){
		initLinTreeDFS();
    	tree.DFS (0, pre_visit, dummy2);
	}
	en = CURRENT_TIME();
    std::cout<<"Arrayed Tree Implementation of Graph :\t";
	std::cout << (en - st)/1000000.0;
	std::cout <<" seconds\n" << endl;
	cout << ov << endl;


	#ifdef ADJ
	/*

	Time Evaluation for adjacency Matrix implemenatation.

	*/
	// start  =  std::clock();
	// for(int i = 0;i<TIMES && 0;i++)
	// 	matrix.init_dfs();
	// duration  =  ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	// std::cout<<"Normal Graph (Adjacency Matrix):\t"<< duration <<" seconds\n";
	#endif

}

int main()
{
	int sizes[2]  =  { sizeof(F), sizeof(B) };
	Tree tree(2, sizes, 2, true);
	graph list(false);

	#ifdef ADJ
	graphMat matrix(false);
	#endif



	/*
	Test case 1:

	*/
	// cout<<"Perfomances : \n\n";

	// cout<< "\nTest case 1: With nodes having lesser degrees\n";
	// graph g(true);
	// graphMat gm(true);
	// Tree t(2, sizes, 2, true);
	// build_random_graph(g,t,gm);
	// // t.Print();
	// Time_Comparison(g,t,gm);


	/*
	Test case 2:
	*/
	cout<< "\n\nTest case 2: With nodes having higher degrees\n";
	/*
	graph g1(true);
	Tree t1(2, sizes, 2, true);
	graphMat gm1(true);
	//build_over_degree_random_graph(g1,t1,gm1);
	*/
	#ifdef ADJ
    GenerateTree(tree, list, matrix);
	#else
	GenerateTree(tree, list);
	#endif
	// t1.Print();

	#ifdef ADJ
	Time_Comparison(tree, list, matrix);
	#else
	Time_Comparison(tree, list);
	#endif


	// int sizes2[]  =  { sizeof(A), sizeof(F) };
	// cout<< "\nTest case 3: With nodes having lesser degrees(With bulk number of variable in each class)\n";
	// graph g2(true);
	// graphMat gm2(true);
	// Tree t2(2, sizes2, 2, true);
	// //build_random_graph(g2,t2,gm2);
	// // t.Print();
	// Time_Comparison(g2,t2,gm2);


	// /*
	// Test case 2:
	// */
	// cout<< "\n\nTest case 4: With nodes having higher degrees(with bulk number of variables in each class)\n";
	// graph g3(true);
	// Tree t3(2, sizes2, 2, true);
	// graphMat gm3(true);
	// build_over_degree_random_graph(g3,t3,gm3);
	// // t1.Print();
	// Time_Comparison(g3,t3,gm3);



	return 0;
}
