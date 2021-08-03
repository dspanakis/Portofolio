#include "floydwarshall.h"

int solve_recfast_count = 0;
int P_RecFast(int i, int j, int k, int **graph, int graph_results_cache[51][51][51])
{
	solve_recfast_count++;
	int res, cmp_1, cmp_2, cmp_2a, cmp_2b;
	if (k > 0)
	{
		// Take cached result
		cmp_1 = graph_results_cache[i][j][k-1];
		// if not cached
		if (cmp_1 == 0)
		{
			// calculate
			cmp_1 = P_RecFast(i, j, k-1, graph, graph_results_cache);
			// store in cache
			//printf("cmp_1 -> graph_results_cache[%d, %d, %d] = %d\n", i, j, k-1, cmp_1);
			graph_results_cache[i][j][k-1] = cmp_1;
		}

	 	// Take cached result
		cmp_2a = graph_results_cache[i][k][k-1];
		// if not cached
		if (cmp_2a == 0)
		{
			// calculate
			cmp_2a = P_RecFast(i, k , k-1, graph, graph_results_cache);
			// store in cache
			//printf("cmp_2a -> graph_results_cache[%d, %d, %d] = %d\n", i, k, k-1, cmp_2a);
			graph_results_cache[i][k][k-1] = cmp_2a;
		}

	 	// Take cached result
		cmp_2b = graph_results_cache[k][j][k-1];
		// if not cached
		if(cmp_2b == 0)
		{
			//calculate
			cmp_2b = P_RecFast(k, j, k-1, graph, graph_results_cache);
			// store in cache
			//printf("cmp_2b -> graph_results_cache[%d, %d, %d] = %d\n", k, j, k-1, cmp_2b);
			graph_results_cache[k][j][k-1] = cmp_2b;
		}

		cmp_2 = cmp_2a + cmp_2b;
		if(cmp_1 > cmp_2)
		{
			// store in cache
			graph_results_cache[i][j][k] = cmp_2;
			//printf("cmp_2 -> graph_results_cache[%d, %d, %d] = %d\n", i, j, k, cmp_2);
			return cmp_2;
		}
		if(cmp_2 > cmp_1)
		{
			// store in cache
			graph_results_cache[i][j][k] = cmp_1;
			//printf("cmp_1 -> graph_results_cache[%d, %d, %d] = %d\n", i, j, k, cmp_1);
			return cmp_1;
		}
	}
	else
	{
		// store in cache
		graph_results_cache[i][j][k] = graph[i][j];
		//printf("graph[i][j] -> graph_results_cache[%d, %d, %d] = %d\n", i, j, k, cmp_1);
		return graph[i][j];
	}
}


void solve(int **graph, int n)
{
	printf("********************\n");
	printf("Solve recursive fast\n");
	printf("********************\n");
	int i ,j , k, res;

	// 3d array allocation
	/*
	int ***graph_results_cache = (int ***) malloc(n * sizeof(int **));
	for (i = 0; i < n; i++) 
	{
  	    graph_results_cache[i] = (int **) malloc(n * sizeof(int *));
     	for (j = 0; j < n; j++)
     	    graph_results_cache[i][j] = (int *) malloc(n * sizeof(int));
	}
	*/
	int graph_results_cache[51][51][51] = { 0 };
	
	// 3d array init
	for(i = 0; i < n; i++)
		for	(j = 0; j < n; j++)
			for(k = 0; k < n; k++)
				graph_results_cache[i][j][k] = 0;

	// 2d array init
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (graph[i][j] == -1)
				graph[i][j] = INFINITE;

	// Calculate
	for(i= 1; i<n; i++)
	{	
		for(j = 0; j < i; j++)
		{
			k = n - 1;
			res = P_RecFast(i, j, k, graph, graph_results_cache);
			if (res < INFINITE)
				printf("From node %d to node %d: Length of shortest path is %d\n", i, j, res);
			else
				printf("From node %d to node %d: There is no path\n", i, j);
		}
		printf("\n");
	}	
	printf("Solve recursive fast completed\n");
	printf("Recursions: %d\n", solve_recfast_count);

		printf("\n");
}

