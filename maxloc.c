#include "stdlib.h"
#include <omp.h>

int main(int argc, char *argv[]) {
	double x[1000000] = { };
	srand(time(0)); // seed
	for(int i=0; i < 1000000;i++){
     	// Generate random number between 0 and 1
     		x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
   	}

/**	// serial
	double maxval = 0.0; 
	int maxloc = 0;
	for (int i=0; i < 1000000; i++){
       		if (x[i] > maxval) 
            		maxval = x[i]; maxloc = i;
	}

	// omp parallel, 32 threads
	double maxval = 0.0; 
	int maxloc = 0;
 	omp_set_num_threads(32);
	#pragma omp parallel for
	for (int i=0; i < 1000000; i++){
       		if (x[i] > maxval) 
            		maxval = x[i]; maxloc = i;
	}

	// omp critical
	int maxloc[1000000], mloc;
   	double maxval[1000000], mval;
	double maxval = 0.0; 
	int maxloc = 0;
 	omp_set_num_threads(4);
	#pragma omp parallel for
	for (int i=0; i < 1000000; i++){
		#pragma omp critical
		{
       			if (x[i] > maxval) { 
            			maxval = x[i]; maxloc = i;
			}
		}
	}
	
	int maxloc[1000000] = { };
       	int mloc = maxloc[0];
   	double maxval[1000000] = { };
       	double mval = maxval[0];
	#pragma omp parallel shared (maxval, maxloc)
	{
		int id = omp_get_thread_num();
		maxval[id] = -1000000000000000000000000000000000000;
		#pragma omp for
			for (int i=0; i < 1000000; i++){
       				if (maxval[i] > mval) { 
            				mval = maxval[id]; 
					mloc = maxloc[id];
				}
			}
	}
**/
	typedef struct { double val; int loc; char pad[128]; } tvals;
	tvals maxinfo[1000000] = { };
	#pragma omp parallel shared(maxinfo)
	{
		int id = omp_get_thread_num();
		maxinfo[id].val = -10000000000000000000;
		#pragma omp for
			for (int i=0; i < 1000000; i++){
       				if (x[i] > maxinfo[id].val) { 
            				maxinfo[id].loc = i; 
					maxinfo[id].val = x[i];
				}
			}
	}

	return 0;
}
