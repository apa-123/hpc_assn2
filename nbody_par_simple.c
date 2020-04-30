#include <stdio.h>      /* printf */
#include <stdlib.h>     /* srand, rand */
#include <string.h>
#include <math.h>       /* fabs */
#include <omp.h>

#define X 0
#define Y 1
#define G 1.0
#define DIM 2
typedef double vect_t[DIM];

int main() {
	int n = 500;
	float delta_t = 0.05;
	int T = 100;
	float x_diff;
	float y_diff;
	float dist;
	float dist_cubed; 
	float forcex;
	float forcey;

	vect_t* forces = malloc(n * sizeof(vect_t));
	vect_t* vel = malloc(n*sizeof(vect_t));
	vect_t* pos = malloc(n*sizeof(vect_t));
	vect_t* old_pos = malloc(n*sizeof(vect_t));
	double* mass = malloc(n*sizeof(int));

	for (int step = 0; step <= T; step++) { 
		memset(forces, 0, n*sizeof(vect_t));
		memset(vel, 0, n*sizeof(vect_t));
		memset(pos, 0, n*sizeof(vect_t));
		memset(old_pos, 0, n*sizeof(vect_t));
		// initialization
        #pragma omp parallel for schedule(static, 5)
   // 	#pragma omp parallel for schedule (guided, 5)
			for (int q = 0; q < n; q++) {
				forces[step][q] = 0;
				pos[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
				pos[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;

				old_pos[q][X] = pos[q][X];
				old_pos[q][Y] = pos[q][Y];

				vel[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
				vel[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;

				mass[q] = fabs((rand() / (double)(RAND_MAX)) * 2 - 1);
			}


// Simple algorithm 
    #pragma omp parallel for schedule(static, 5)
//    #pragma omp parallel for schedule (guided, 5)
		for (int q = 0; q < n; q++) {
			for (int k = 0; k < n && k != q; k++) {
			    x_diff = pos[q][X] - pos[k][X];
			    y_diff = pos[q][Y] - pos[k][Y];
			    dist = sqrt(x_diff * x_diff + y_diff * y_diff);
			    dist_cubed = dist * dist * dist;
			    forces[q][X] = G * mass[q] * mass[k]/dist_cubed * x_diff;
			    forces[q][Y] = G * mass[q] * mass[k]/dist_cubed * y_diff;
			}
		}
	for (int q = 0; q < n-1; q++) { 
		pos[q][X] += delta_t * vel[q][X];
		pos[q][Y] += delta_t * vel[q][Y];
		vel[q][X] += delta_t/mass[q] * forces[q][X];
		vel[q][Y] += delta_t/mass[q] * forces[q][Y];
	}
	}
	// #pragma omp parallel for
		for (int i = 0; i < n; i++) {
			printf("position: %f %f ", pos[i][X], pos[i][Y]);
			printf("velocity: %f %f\n",vel[i][X], vel[i][Y]);
		}
	return 0;
} 
