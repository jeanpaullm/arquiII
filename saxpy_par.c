# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>

int main ( int argc, char *argv[] ) {

  int i;
  int m[]= {1000000, 10000000, 100000000}; //tamaños de vector
  int tests =  sizeof(m)/sizeof(m[0]);
  float s = 1.5;
  double start_time, run_time;

  printf("\n Ejecutando SAXPY paralelizado \n");

  printf ( "\n  Procesadores disponibles = %d\n", omp_get_num_procs ( ) );
  printf ( "  Cantidad de hilos = %d\n", omp_get_max_threads ( ) );

  for (int j = 0; j < tests; j++) {

    int n = m[j];

    float* x = ( float * ) malloc ( n * sizeof ( float ) );
    float* y = ( float * ) malloc ( n * sizeof ( float ) );
    float* z = ( float * ) malloc ( n * sizeof ( float ) );

    # pragma omp parallel private ( i )
    {

    # pragma omp for
      for (i = 0; i < n; i++ ) {
        x[i] = ( float ) ( ( i + 1 ) % 7 );
        y[i] = ( float ) ( ( i + 1 ) % 3 );
      }

    start_time = omp_get_wtime();

    # pragma omp for
      for ( i = 0; i < n; i++ ) {
        z[i] = x[i] + s * y[i];
      }

    }
    run_time = omp_get_wtime() - start_time;
    printf("\n ejecutado en %f segundos \n",run_time);

    free ( x );
    free ( y );
    free ( z );
  }   

  return 0;
  
}
