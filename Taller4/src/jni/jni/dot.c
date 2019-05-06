# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>
# include <arm_neon.h>

/*
 * SAXPY 
 * z = a * x + y 
 * a = escalar
 * z, x, y = vectores
 */

int main ( int argc, char *argv[] ) {
  
  int m[]= {1000000, 10000000, 100000000}; //tamaños de vector

  int tests =  sizeof(m)/sizeof(m[0]);     //cant de pruebas

  float a = 1.5;
  double start_time, run_time;

  printf("\nEjecutando DOT no paralelizado \n");

  for (int j = 0; j < tests; j++) {

    int n = m[j];

    float* x = ( float * ) malloc ( n * sizeof ( float ) );
    float* y = ( float * ) malloc ( n * sizeof ( float ) );
    float  z = 0;

    //rellenado del vector
      for (int i = 0; i < n; i++) {
        x[i] = ( float ) ( ( i + 1 ) % 7 );
        y[i] = ( float ) ( ( i + 1 ) % 3 );
      }
    
    start_time = omp_get_wtime();

      //dot
      for (int i = 0; i < n; i++ ) {
        z += x[i] * y[i];
      }
    
    run_time = omp_get_wtime() - start_time;

    printf("\n %d elementos\n ejecutado en  %f segundos \n", n, run_time);

    free ( x );
    free ( y );
  } 

	
  printf("\nEjecutando DOT paralelizado \n");

  printf ( "\n Procesadores disponibles = %d\n", omp_get_num_procs ( ) );
  printf ( " Cantidad de hilos = %d\n", omp_get_max_threads ( ) );

  for (int j = 0; j < tests; j++) {

    int n = m[j];

    float* x = ( float * ) malloc ( n * sizeof ( float ) );
    float* y = ( float * ) malloc ( n * sizeof ( float ) );
    float z = 0;

     //rellenado del vector
      for (int i = 0; i < n; i++) {
        x[i] = ( float ) ( ( i + 1 ) % 7 );
        y[i] = ( float ) ( ( i + 1 ) % 3 );
      }
    
    start_time = omp_get_wtime();

    float32x4_t X,Y,Z;

    #pragma omp parallel for
    for (int i = 0; i<n; i+=4){
        X = vld1q_f32(x+i);
        Y = vld1q_f32((y+i));
        X = vmulq_f32(X,Y);
        Z = vaddq_f32(Z,X);  
    }
    
    run_time = omp_get_wtime() - start_time;

    printf("\n %d elementos\n ejecutado en  %f segundos \n", n, run_time);

    free ( x );
    free ( y );
  }   

  return 0;
  
}