# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>

int main ( int argc, char *argv[] ) {
  
  int m[]= {1000000, 10000000, 100000000}; //tamaños de vector

  int tests =  sizeof(m)/sizeof(m[0]);

  float s = 1.5;
  double start_time, run_time;

  printf("\n Ejecutando SAXPY no paralelizado \n");

  for (int j = 0; j < tests; j++) {

    int n = m[j];

    float* x = ( float * ) malloc ( n * sizeof ( float ) );
    float* y = ( float * ) malloc ( n * sizeof ( float ) );
    float* z = ( float * ) malloc ( n * sizeof ( float ) );

    //rellenado del vector
      for (int i = 0; i < n; i++ ) {
        x[i] = ( float ) ( ( i + 1 ) % 7 );
        y[i] = ( float ) ( ( i + 1 ) % 3 );
      }
    
    start_time = omp_get_wtime();

      //operacion
      for (int i = 0; i < n; i++ ) {
        z[i] = x[i] + s * y[i];
      }
    
    run_time = omp_get_wtime() - start_time;

    printf("\n ejecutado en  %f segundos \n",run_time);

    free ( x );
    free ( y );
    free ( z );
  } 

  return 0;
  
}
