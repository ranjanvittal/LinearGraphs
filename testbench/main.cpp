#include "graph.h"
#include "random.h"
#include "../tree.h"
#include "graphMat.h"
#include "satellite.h"
#include <iostream>
#include <ctime>
#include <time.h>


#include "parameters.h"



using namespace std;

int maps[TREE_SIZE+3];



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



int pre_visit(int id){
	static int count = 0;

    if (maps[id] == 0) {
		//printf ("%d\n", ++count);
        maps[id] = 1;
        return 1;
    }
    else return 0;
}


void dummy2(int n1){
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
	clock_gettime(CLOCK_USED, &start);
    for(int i = 0;i<TIMES;i++)
    	list.init_dfs();
	clock_gettime(CLOCK_USED, &end);
    std::cout << "Normal Graph (Adjacency lists) :\t";
	std::cout << TimeDifference(start, end).tv_sec << "." << setfill('0') << TimeDifference(start, end).tv_nsec << setfill(' ');
	std::cout <<" seconds\n" << endl;



    /*

    Time Evaluation for Arrayed tree implemenatation.

    */

    tree.DFSOptimizer (0);

	clock_gettime(CLOCK_USED, &start);
    for(int i = 0;i<TIMES;i++){
		initLinTreeDFS();
    	tree.DFS (0, pre_visit, dummy2);
	}
	clock_gettime(CLOCK_USED, &end);
    std::cout<<"Arrayed Tree Implementation of Graph :\t";
	std::cout << TimeDifference(start, end).tv_sec << "." << setfill('0') << TimeDifference(start, end).tv_nsec << setfill(' ');
	std::cout <<" seconds\n" << endl;



	#ifdef ADJ
	/*

	Time Evaluation for adjacency Matrix implemenatation.

	*/
	start  =  std::clock();
	for(int i = 0;i<TIMES && 0;i++)
		matrix.init_dfs();
	duration  =  ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout<<"Normal Graph (Adjacency Matrix):\t"<< duration <<" seconds\n";
	#endif

}

int main()
{
	int sizes[2]  =  { sizeof(A), sizeof(B) };
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
