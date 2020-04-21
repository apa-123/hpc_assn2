#include <stdio.h>      /* printf */
#include <stdlib.h>     /* srand, rand */
#include <string.h>
#include <math.h>       /* fabs */

#define X 0
#define Y 1
#define G 1.0
#define DIM 2
typedef double vect_t[DIM];

int main(int argc, char *argv[]) {
	n = argv[1];
	delta_t = argv[2]
	T = argv[3]

	vect_t∗ forces = malloc(n∗sizeof(vect_t));
	vect_t* vel = malloc(n*sizeof(vect_t));
	vect_t* pos = malloc(n*sizeof(vect_t));
	vect_t* mass = malloc(n*sizeof(vect_t));
	
	for (int step = 1; step <= n; steps++) { 
		forces = memset(forces, 0, n*sizeof(vect_t));
		vel = memset(vel, 0, n*sizeof(vect_t));
		pos = memset(pos, 0, n*sizeof(vect_t));
		mass = memset(mass, 0, n*sizeof(vect_t));

		// initialization
		for (int q = 0; q < n-1; q++) {
        		forces[q] = 0;
			pos[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
			pos[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;
			pos[q][Z] = (rand() / (double)(RAND_MAX)) * 2 - 1;

			old_pos[i][X] = pos[q][X];
			old_pos[i][Y] = pos[q][Y];
			old_pos[i][Z] = pos[q][Z];

			vel[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
			vel[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;
			vel[q][Z] = (rand() / (double)(RAND_MAX)) * 2 - 1;

			mass[q] = fabs((rand() / (double)(RAND_MAX)) * 2 - 1);
		}
		// not sure if it's till n-1 or n
		for (int q = 0; q < n-1; q++) {
			// compute forces
			for (int k = q+1; k < n-1; k++) {
			    x_diff = pos[q][X] − pos[k][X];
			    y_diff = pos[q][Y] − pos[k][Y];
			    dist = sqrt(x_diff∗x diff + y_diff∗y diff);
			    dist_cubed = dist∗dist∗dist;
			    force_qk[X] = G∗masses[q]∗masses[k]/dist_cubed ∗ x_diff;
			    force_qk[Y] = G∗masses[q]∗masses[k]/dist_cubed ∗ y_diff
			    forces[q][X] += force_qk[X];
			    forces[q][Y] += force_qk[Y];
			    forces[k][X] −= force qk[X];
			    forces[k][Y] −= force qk[Y];
			}
		}
		for (int q = 0; q < n-1; q++) { 
			pos[q][X] += delta_t∗vel[q][X];
			pos[q][Y] += delta_t∗vel[q][Y];
			vel[q][X] += delta_t/masses[q]∗forces[q][X];
			vel[q][Y] += delta_t/masses[q]∗forces[q][Y];

	}
	
	for (int i = 0; i < n; i++) {
		std::cout << "position: " << pos[X] << " " << pos[Y] << std::endl;
		std::cout << "velocity: " << vel[X] << " " << vel[Y] << std::endl;
	}
	return 0;
} 
