#include "floydwarshall.h"


void input_graph(int **graph, int n)
{
	int y, x;

  	printf("Enter the vertices:\n");
	for(y = 0; y < n ; y++)
	{
		for(x = 0 ; x <= y; x++)
		{
			if(x == y) 
			{
				// Initialize to 0 same node distances
				graph[y][x] = 0;
			}
			else 
			{
				scanf("%d", &graph[y][x]);
				graph[x][y] = graph[y][x];
			}
		}
	}
}

void print_graph(int **graph, int n)
{
	int y, x;
	printf("Matrix of input data:\n");
	printf("----------------------------------\n");
	for(y = 0; y < n ; y++)
	{
		for(x = 0; x < n; x++)
			printf("%d ", graph[x][y]);
		printf("\n");
	}
	printf("----------------------------------\n");
}

void main()
{
	int n, i;

  	printf("Enter the number of nodes:\n");
	scanf("%d", &n);

	// Alocate graph array
	int **graph = malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) 
         graph[i] = malloc(n * sizeof(int));

	// input graph vertices
	input_graph(graph, n);

	// print graph vertices
	print_graph(graph, n);

	//solve_rec(graph, n);
	solve(graph, n);
	
	for (i = 0; i < n; i++) 
         free(graph[i]);
	free(graph);
  	printf("Execution completed.\n");
}

