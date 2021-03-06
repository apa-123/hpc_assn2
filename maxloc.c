#include "stdlib.h"
#include <omp.h>
#include <sys/time.h>
#include <stdio.h>

// function with timer
double mysecond(){
  struct timeval tp;
  struct timezone tzp;
  int i;

  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
 }

int main(int argc, char *argv[]) {
        double t1, t2; // timers
        double x[1000000] = { };
        srand(time(0)); // seed
        for(int i=0; i < 1000000;i++){
        // Generate random number between 0 and 1
                x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
        }

/**     // serial
        double maxval = 0.0;
        int maxloc = 0;
        t1 = mysecond();
        for (int i=0; i < 1000000; i++){
                if (x[i] > maxval)
                        maxval = x[i]; maxloc = i;
        }
        t2 = mysecond();
        printf("Execution time: %11.8f s\n", (t2 - t1));

        // omp parallel, 32 threads
        double maxval = 0.0;
        int maxloc = 0;
        omp_set_num_threads(32);
        t1 = mysecond();
        #pragma omp parallel for
	for (int i=0; i < 1000000; i++){
                if (x[i] > maxval)
                        maxval = x[i]; maxloc = i;
        }
        t2 = mysecond();
        printf("Execution time: %11.8f s\n", (t2 - t1));

        // omp critical
        int maxloc[32], mloc;
        double maxval[32], mval;
        double maxval = 0.0;
        int maxloc = 0;
        omp_set_num_threads(4);
        t1 = mysecond();
        #pragma omp parallel for
        for (int i=0; i < 1000000; i++){
                #pragma omp critical
                {
                        if (x[i] > maxval) {
                                maxval = x[i]; maxloc = i;
                        }
                }
        }
        t2 = mysecond();
        printf("Execution time: %11.8f s\n", (t2 - t1));

        int maxloc[32] = { };
        int mloc = maxloc[0];
        double maxval[32] = { };
        double mval = maxval[0];
        t1 = mysecond();
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
        t2 = mysecond();
        printf("Execution time: %11.8f s\n", (t2 - t1));
**/
        typedef struct { double val; int loc; char pad[128]; } tvals;
        tvals maxinfo[32] = { }; // size = num of threads
        t1 = mysecond();
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
        t2 = mysecond();
        printf("Execution time: %11.8f s\n", (t2 - t1));

        return 0;
}
