#ifndef GRAPHADJ
#define GRAPHADJ

#include <map>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <climits>
#include <cassert>
#include <time.h>

#include "parameters.h"
using namespace std;

	/*
	Graph implementation using adjacency lists.
	This is the class graph which holds the sattellite data pointer,
	which is actually map from integer in the node of the graph.
	*/
class graph
{
	public:

		/*
		This map variable pointer holds the satellite data
		pointer from each node as a integer.
		*/
		map <int, void*> pointer;


		/*
		This map variable type holds the type of
		satellite data each node holding.
		*/
		map <int, int> type;

		/*
		This is the flag to indicate whether the
		graph is directed or undirected.
		*/
		bool directed;

		//vector<vector<int> > a(r);

		/*
		Variable hold the number of vertices in the graph.
		*/
		int num_nodes;

		/*
		This array of vector holds the adjacency lists of
		all the node in the graph.
		*/
		vector<int> adj[TREE_SIZE];

		/*
		This array is storage whether the node is visited
		or not during the dfs traversal.
		*/
		int vis[TREE_SIZE];

		/*
		This array keep track of the nodes whether they
		are present in the graph or not.
		*/
		int present[TREE_SIZE];


		/*
		This is the constructor for the graph which
		initialises the graph with empty adjacency lists.
		Parameters:
				A bool variable which says whether the graph is directed or not.
		*/
		graph(bool dir);

		/*
		This method is used to add nodes with node number and
		runtime type of the class it wants to hold in the satellite data.
		Parameters:
				Takes two integers one the node number and other is
				runtime type of the satellite data it wants to hold.
		*/
		void add_vertex(int num, int run_type);

		/*
		This method is used to add edges between two nodes.
		Parameters:
				Takes two integers with node numbers as parameters to add a edge.
		*/
		void add_edge(int num1, int num2);

		/*
		This method is to initilize the visited array to
		unvisited before actually executing the dfs method on the graph.
		This method will call the dfs method on all the unvisited nodes on the graph.
		*/
		void init_dfs();

		/*
		This method executes dfs algorithm on the given node.
		Parameters:
				A vertex num to start dfs.
		*/
		void dfs(int num);
};

#endif
