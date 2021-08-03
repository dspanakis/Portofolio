#include "floydwarshall.h"

int solve_rec_count = 0;
int P_Rec(int i, int j, int k, int **graph)
{
	int res, cmp_1, cmp_2, cmp_2a, cmp_2b;
	solve_rec_count++;
	if (k > 0)
	{
		cmp_1 = P_Rec(i, j, k-1, graph);
		cmp_2a = P_Rec(i, k, k-1, graph);
		cmp_2b = P_Rec(k, j, k-1, graph);
		cmp_2 = cmp_2a + cmp_2b;
		if(cmp_1 > cmp_2)
			return cmp_2;
		if(cmp_2 > cmp_1)
			return cmp_1;
	}
	else
	{
		return graph[i][j];
	}
}

void solve(int **graph,int n)
{
	printf("====================\n");
	printf("Solve recursive\n");
	printf("====================\n");

	int i ,j , k, res;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (graph[i][j] == -1)
				graph[i][j] = INFINITE;

	for(i= 1; i<n; i++)
	{	
		for(j = 0; j < i; j++)
		{
			k = n - 1;
			res = P_Rec(i, j, k, graph);
			if (res < INFINITE)
				printf("From node %d to node %d: Length of shortest path is %d\n", i, j, res);
			else
				printf("From node %d to node %d: There is no path\n", i, j);
		}
		printf("\n");
	}	
	printf("Solve recursive completed\n");
	printf("Recursions: %d\n", solve_rec_count);
}

