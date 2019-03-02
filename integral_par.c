#include <stdio.h>
#include <math.h>
#include <omp.h>

/**
	calcula la integral desde a hasta b utilizando a rpoximacion trapezoidal
*/

int main(int argc, char** argv) {
	
	double a = 10;       //limites de integracion     
	double b = 1000000; 

	int n = 4194304; /* subdivisiones = 2^22 */
	double h = (b - a) / n; /* ancho de las subdivisiones */
	double integral; /* resultado */

	double f(double x);
	integral = (sin(a) + sin(b))/2.0;
	int i;

	double start_time, run_time;

	start_time = omp_get_wtime();

	omp_set_num_threads(omp_get_num_procs());
	#pragma omp parallel for shared (a, n, h) private(i) reduction(+: integral)
	for(i = 1; i < n; i++) {
		integral += sin(a+i*h);
	}
	integral = integral * h;

	run_time = omp_get_wtime() - start_time;

	printf("Con n = %d trapezoides, la integral de %f hasta %f es %f\ncalculado en: %f",n, a, b, integral, integral);
}