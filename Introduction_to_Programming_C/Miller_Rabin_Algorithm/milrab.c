#include <stdio.h>
#include <time.h>
#define MINNUM 3990000000
#define MAXNUM 4010000000

#define TRUE 1
#define FALSE 0

/*Miller Rabin Function */
unsigned int miller()
{ 				
	unsigned int n, r , d, j,  check_next_a, primecount=0;  
	unsigned int rloop , d_save; /*Those two variables, save d,r values for next loops */
	unsigned long long a; /* ULL otherwise a^d mod n overflows, casting can be used too*/
	unsigned long long x=1;
	
	// Start with odd number and take only odd numbers
	for (n = MINNUM + 1 ; n <= MAXNUM-1 ; n += 2)
	{
		// if not divided by 3
		if (n % 3 !=  0 && n % 7 != 0 && n % 5 != 0)
		{
			check_next_a = FALSE;
			r = 0;

			// Create (2^r)*d= n-1
			// d = previous double
			// count how many times we have exact divisions with 2
			for (d = n - 1; d % 2 == 0; d /= 2)
			{
				  r++;
			}	
			
			d_save = d; //saves d for each j loop

			// Start checking the 3 alpha's, j rotates them
			for(j = 1; j <= 3; j++)
			{
				if (j == 1) a = 2;
				else if (j == 2) a = 7;
				else if (j == 3) a = 61;
			
			    d = d_save;
				x = 1;
				// Calculate x = a^d mod n
				while (d > 0)					
		    	{ 
		        	// When d is odd 
		        	if (d & 1) 			//Same as if ( d % 2 != 0)
		            	x = (x * a) % n; 
		  
		  	      	// When d is even 
		    	    d = d >> 1; 		//Same as y = y / 2 
		    	    a = (a * a) % n; 
					 
			   	} 
						 	
				// Miller Rabin's conditions
				if (x == 1 || x == n-1)
				{
					// Check next a if exists
					continue;
				}
			
				check_next_a = FALSE;
				rloop = r; 				/* rloop saves r's value for each loop */
				// Loop r - 1 times
				while (--rloop > 0) 
			    { 
			 		x = (x * x) % n; 										 
					if (x == n-1)
					{
						// Check next a if exists
						check_next_a = TRUE;
						break;
					}
					// Extra optimization not in assignemt instructions (++ Time)
			        if (x == 1)
					{
						// Check next a if exists
						check_next_a = FALSE;
						break;
					}
					
			    } 	// end of while
				if (check_next_a)
				{
					continue;
				}
				else
				{
					break;
				}
			}	// end of for 

			if (j > 3)
				primecount++;

		}	//end of if (n % 3 !=  0)
	}	// end of for 
	return primecount;
}


/*Deterministic function */
unsigned int deterministic()
{
    int primecount = 0;
    char isprime;									/*TRUE=1 FALSE=0 */
    unsigned int i,j;  								/* i,j are counters*/
    for (i = MINNUM+1; i <= MAXNUM-1 ; i=i+2)
    {
    	isprime = 1;
    	if(i%3!=0)
		{
		
        	for (j = 5; j * j <= i ; j=j+6) 
        	{  
            	if ( i%j == 0 || i%(j+2) == 0)
            	{   
			
		    	isprime = 0;
                break;
                
            	}
        	}
        	
        	if (isprime == 1) 
			{
				primecount++;
			}
    
    	}
	}
    return primecount;
}



int main()
{
	unsigned int deter_result,miller_result;
	
	/*Welcome message */
	printf("Checking range [%lu,%lu] for primes...\n",MINNUM,MAXNUM);
	
	/* Timing deterministic algorithm*/
	clock_t begin = clock();
	deter_result=deterministic();
	clock_t end = clock();

	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	
	printf("Deterministic algorithm: Found %d primes in %.2f secs\n",deter_result,time_spent);
	
	/* Timing miller-rabin algorithm*/
	clock_t start = clock();
	miller_result=miller();
	clock_t stop = clock();
	
	double	time_spent_miller = (double)(stop - start) / CLOCKS_PER_SEC;
	
	printf("Miller-Rabin algorithm: Found %d primes in %.2f secs\n",miller_result,time_spent_miller);
	
}


