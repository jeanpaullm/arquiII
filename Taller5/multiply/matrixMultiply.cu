#include <stdio.h>
#include <cuda.h>

int *a, *b;  // host data
int *c, *c2;  // results

//Cuda error checking - non mandatory
void cudaCheckError() {
 cudaError_t e=cudaGetLastError();
 if(e!=cudaSuccess) {
   printf("Cuda failure %s:%d: '%s'\n",__FILE__,__LINE__,cudaGetErrorString(e));
   exit(0);
 }
}

//GPU kernel
__global__
void matrixMultiply(int* A,int* B,int* C, int N){
    int ai = threadIdx.y * blockDim.x;
    int bi = threadIdx.x;
    int ci = threadIdx.x + threadIdx.y * blockDim.x ;
    int result = 0;
    if(ci < N) {
      for(int i = 0; i < 4; i++){
          result += A[ai] * B[bi];
          ai++;
          bi += 4;
      }
      C[ci] = result;
    }
}

int main(int argc,char **argv) {

    printf("Begin \n");
    //Iterations
    int n=16; //cantidad de elementos de la matriz, x * y
    //Number of blocks
    int nBytes = n*sizeof(int);

    //memory allocation
    a = (int *) malloc(nBytes);
    b = (int *) malloc(nBytes);
    c = (int *) malloc(nBytes);
    c2 = (int *) malloc(nBytes);

    // Data filling
    for(int i=0;i<n;i++)
    a[i]=i,b[i]=i;

    printf("Allocating device memory on host..\n");
   //GPU memory allocation
    int *a_d,*b_d,*c_d;
    cudaMalloc((void **) &a_d, n*sizeof(int));
    cudaMalloc((void **) &b_d, n*sizeof(int));
    cudaMalloc((void **) &c_d, n*sizeof(int));

    printf("Copying to device..\n");
    cudaMemcpy(a_d, a, n*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(b_d, b, n*sizeof(int), cudaMemcpyHostToDevice);

    //Work definition
    dim3 threadsPerBlock(4, 4);
    dim3 numBlocks(1, 1);

    printf("Doing GPU Vector Multiplication\n");
    matrixMultiply<<<numBlocks, threadsPerBlock>>>(a_d, b_d, c_d, n);
    cudaCheckError();

    //Wait for kernel call to finish
    cudaDeviceSynchronize();

    //Copying data back to host, this is a blocking call and will not start until all kernels are finished
    printf("Copying back to host...\n");
    cudaMemcpy(c, c_d, n*sizeof(int), cudaMemcpyDeviceToHost);
    int counter = 0;
    
    printf("A\n");    
    for(int i = 0; i < 4; i++) {
	for(int j = 0; j < 4; j++) {
          printf("%d ",a[counter]);
	  counter++;
	}
	printf("\n");
    }

    counter = 0;

    printf("B\n");    
    for(int i = 0; i < 4; i++) {
	for(int j = 0; j < 4; j++) {
          printf("%d ",b[counter]);
	  counter++;
	}
	printf("\n");
    }
 
    counter = 0;

    printf("C\n");    
    for(int i = 0; i < 4; i++) {
	for(int j = 0; j < 4; j++) {
          printf("%d ",c[counter]);
	  counter++;
	}
	printf("\n");
    }

    //Free GPU memory
    cudaFree(a_d);
    cudaFree(b_d);
    cudaFree(c_d);
    return 0;
}
