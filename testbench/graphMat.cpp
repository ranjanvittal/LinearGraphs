#include "graphMat.h"
#include "satellite.h"

graphMat::graphMat(bool dir = true)
{
	directed = dir;
	num_nodes = 0;

	for(int i = 0; i < TREE_SIZE; i++)
	{
		present[i]=0;
	}

	for(int i = 0; i < TREE_SIZE; i++)
	{
		for(int j = 0; j < TREE_SIZE; j++)
		{
			adj[i][j] = 0;
		}
	}
}

void graphMat::add_vertex(int num, int run_type)
{
	num_nodes++;
	present[num] = 1;

	if(run_type == 1)
	{
		A* node = new A();

		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type.insert(make_pair(num, run_type));
	}

	else if(run_type == 2)
	{
		B* node = new B();

		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type.insert(make_pair(num, run_type));
	}

	else if(run_type == 3)
	{
		C* node = new C();

		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type.insert(make_pair(num, run_type));
	}

	else if(run_type == 4)
	{
		D* node = new D();

		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type.insert(make_pair(num, run_type));
	}

	else if(run_type == 5)
	{
		E* node = new E();

		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type.insert(make_pair(num, run_type));
	}

	else if(run_type == 6)
	{
		F* node = new F();

		for(int i = 0; i < node->len; i++)
		{
			node->a[i] = i;
		}

		pointer[num] =  node;
		type.insert(make_pair(num, run_type));
	}
}

void graphMat::add_edge(int num1, int num2)
{
	if(directed && 0)
	{
		adj[num1][num2] = 1;
	}

	else
	{
		adj[num1][num2] = 1;
		adj[num2][num1] = 1;
	}
}

void graphMat::dfs(int num)
{
	int store;
	vis[num] = 1;

/*
	static int blah = 0;
	printf ("%d\n", ++blah);
*/
	/*
	if(type[num] == 1)
	{
		// cout<<"Class A Vertex "<<num<<"\n";

		for(int i =0 ;i < ((A*)pointer[num])->len ; i++)
		{
			// cout<<((A*)pointer[num])->a[i]<<" ";
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 2)
	{
		// cout<<"Class B Vertex "<<num<<"\n";

		for(int i =0 ;i < ((B*)pointer[num])->len ; i++)
		{
			// cout<<((B*)pointer[num])->a[i]<<" ";
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 3)
	{
		// cout<<"Class C Vertex "<<num<<"\n";

		for(int i =0 ;i < ((C*)pointer[num])->len ; i++)
		{
			// cout<<((C*)pointer[num])->a[i]<<" ";
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 4)
	{
		// cout<<"Class D Vertex "<<num<<"\n";

		for(int i =0 ;i < ((D*)pointer[num])->len ; i++)
		{
			// cout<<((D*)pointer[num])->a[i]<<" ";
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 5)
	{
		// cout<<"Class E Vertex "<<num<<"\n";

		for(int i =0 ;i < ((E*)pointer[num])->len ; i++)
		{
			// cout<<((E*)pointer[num])->a[i]<<" ";
		}

		// cout<<"\n\n";
	}

	else if(type[num] == 6)
	{
		// cout<<"Class F Vertex "<<num<<"\n";

		for(int i =0 ;i < ((F*)pointer[num])->len ; i++)
		{
			// cout<<((F*)pointer[num])->a[i]<<" ";
		}

		// cout<<"\n\n";
	}
	*/

	for(int i = 0; i < TREE_SIZE; i++)
	{
		if(/*present[i] == 1 && */vis[i]  == 0 && adj[num][i] == 1)
		{
			dfs( i );
		}
	}
}

void graphMat::init_dfs()
{
	for(int i = 0; i < TREE_SIZE; i++)
	{
		vis[i] = 0;
	}

	dfs(0);
	/*
	for(int i = 0; i < TREE_SIZE; i++)
	{
		if(vis[i] == 0 && present[i] == 1)
		{
			dfs(i);
		}
	}
	*/

}
