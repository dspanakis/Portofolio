#include "floydwarshall.h"
//#define PATH 1

void solve(int **graph, int n)
{
	int i, j, k, x, y;

    int **dist = malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) 
         dist[i] = malloc(n * sizeof(int));

#ifdef PATH	
    int **next = malloc(n * sizeof(int*));
	for (i = 0; i < n; i++) 
         next[i] = malloc(n * sizeof(int));
#endif

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++) 
		{
			dist[i][j] = graph[i][j]; 
			if(dist[i][j]==-1) 
		 	{
		 		dist[i][j] = INFINITE;
		 	}
		}
	}

#ifdef PATH	
	for (i=0; i<n; i++)
	{
        for (j=0; j<n; j++)
		{
            next[i][j] = INFINITE;
        }
    }
#endif

	for (k = 0; k < n; k++) 
    { 
        // Pick all vertices as source one by one 
        for (i = 0; i < n; i++) 
        { 
            // Pick all vertices as destination for the 
            // above picked source 
            for (j = 0; j < n; j++) 
            { 
                // If vertex k is on the shortest path from 
                // i to j, then update the value of dist[i][j] 
                if (dist[i][k] + dist[k][j] < dist[i][j])
				{
				 	dist[i][j] = dist[i][k] + dist[k][j];
#ifdef PATH					 
				 	next[i][j] = k;
#endif		 	
				}			
			} 
        } 
    } 
	printf("Matrix of output data:\n");
	printf("----------------------------------\n");
	for(y = 0; y < n ; y++)
	{
		for(x = 0 ; x <= n && x != y; x++)
		{
			if(dist[x][y]==INFINITE)
				printf("From node %d to node %d: There is no path\n", y, x);
			else
			{
			
				printf("From node %d to node %d: Length of shortest path is %d\n", y, x, dist[y][x]);
#ifdef PATH
				printf("Shortest path is : %d", y);   
				int y1 = y;
				while(y1 != x)
   				{
					y1 = next[y1][x];
   					if (y1 == INFINITE)
   					{
	   					printf(" -> %d", x);
   						break;
 				    }
   					printf(" -> %d", y1);
				}
				printf("\n");
#endif			
			}
		}
		printf("\n");
	}
	printf("----------------------------------\n");

	for (i = 0; i < n; i++) 
         free(dist[i]);
	free(dist);
#ifdef PATH	
	for (i = 0; i < n; i++) 
         (next[i]);
	free(next);
#endif				
}
