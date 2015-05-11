#include "graph.h"
#include "satellite.h"


graph::graph(bool dir)
{
	directed = dir;
	num_nodes = 0;
	gen = 0;
}


void graph::add_vertex(int num, int run_type)
{
	num_nodes++;
	present[num] = 1;
	if(run_type == 1)
	{
		A* node = new A();
		node->len = 100;
		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type[num] = run_type;
	}

	else if(run_type == 2)
	{
		B* node = new B();
		node->len = 200;
		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type[num] = run_type;
	}

	else if(run_type == 3)
	{
		C* node = new C();
		node->len = 300;
		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type[num] = run_type;
	}

	else if(run_type == 4)
	{
		D* node = new D();
		node->len = 400;
		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type[num] = run_type;
	}

	else if(run_type == 5)
	{
		E* node = new E();
		node->len = 500;
		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type[num] = run_type;
	}

	else if(run_type == 6)
	{
		F* node = new F();
		node->len = 600;
		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type[num] = run_type;
	}
}


void graph::add_edge(int num1, int num2)
{
	if(directed)
	{
		adj[num1].push_back(num2);
	}

	else
	{
		adj[num1].push_back(num2);
		adj[num2].push_back(num1);
	}
}


void graph::dfs(int num)
{
	int store;
	vis[num] = 1;
	//cout<<" , "<<num;

	//static int blah = 0;

	//printf ("%d\n", ++blah);
	//fflush (stdout);


	if(type[num] == 1)
	{
		// cout<<"Class A Vertex "<<num<<"\n";

		for(int i =0 ;i < ((A*)pointer[num])->len ; i++)
		{
			((A*)pointer[num])->a[i] ++;
			gen++;
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 2)
	{
		// cout<<"Class B Vertex "<<num<<"\n";

		for(int i =0 ;i < ((B*)pointer[num])->len ; i++)
		{
			((B*)pointer[num])->a[i] ++;
			gen++;
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 3)
	{
		// cout<<"Class C Vertex "<<num<<"\n";

		for(int i =0 ;i < ((C*)pointer[num])->len ; i++)
		{
			((C*)pointer[num])->a[i] ++;
			gen++;
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 4)
	{
		// cout<<"Class D Vertex "<<num<<"\n";

		for(int i =0 ;i < ((D*)pointer[num])->len ; i++)
		{
			((D*)pointer[num])->a[i] ++;
			gen++;
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 5)
	{
		// cout<<"Class E Vertex "<<num<<"\n";

		for(int i =0 ;i < ((E*)pointer[num])->len ; i++)
		{
			((E*)pointer[num])->a[i] ++;
			gen++;
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 6)
	{
		// cout<<"Class F Vertex "<<num<<"\n";

		for(int i =0 ;i < ((F*)pointer[num])->len ; i++)
		{
			((F*)pointer[num])->a[i] ++;
			gen++;
		}

		// cout<<"\n\n";
	}


	for(int i = 0; i < adj[num].size(); i++)
	{
		if(vis[ adj[num][i] ] == 0)
		{
			dfs( adj[num][i] );
		}
	}
}


int graph::init_dfs()
{
	for(int i = 0; i < num_nodes; i++)
	{
		vis[i] = 0;
	}

	dfs(0);

/*
	for(int i = 0; i < num_nodes; i++)
	{
		if(vis[i] == 0 && present[i]==1)
		{
			dfs(i);
		}
	}
*/
	return gen;
}
