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
void saxpy(int *A,int *B,int *C,int N){
    int ai = threadIdx.y * blockDim.x;
    int bi = threadIdx.x;
    int ci = threadIdx.x + threadIdx.y * blockDim.x ;
    int result = 0;
    if(ci < N*N) {
      for(int i = 0; i < N; i++) {
          result += A[ai] * B[bi];
          ai++;
          bi += N;
      }
      C[ci] = result + C[ci];
    } 
}

//CPU function, N matrix width
void saxpy_h(int *A1,int *B1, int *C1, int N){
    int ai, bi, result;
    for(int i = 0; i < N*N; i++) {
	ai = (i - i%N)/N; 
        bi = i%N;
        result = 0;
	for(int j = 0; j < N; j++) {
	    result = A1[ai] * B1[bi];
            ai++;
	    bi += N;
        }      
        C1[i] = result + C1[i];
    }
}

int main(int argc,char **argv) {
    printf("Begin \n");
    //Matrix side size 
    int n = 2500;

    //memory allocation	
    a = (int *) malloc(n*n*sizeof(int));
    b = (int *) malloc(n*n*sizeof(int));
    c = (int *) malloc(n*n*sizeof(int));
    c2 = (int *) malloc(n*n*sizeof(int));

    int *a_d,*b_d,*c_d;
   
    // Data filling
    for(int i=0; i<n*n; i++)
    a[i]=i,b[i]=i,c[i];


    printf("Allocating device memory on host..\n");
   //GPU memory allocation
    cudaMalloc((void **) &a_d, n*n*sizeof(int));
    cudaMalloc((void **) &b_d, n*n*sizeof(int));
    cudaMalloc((void **) &c_d, n*n*sizeof(int));

    printf("Copying to device..\n");
    cudaMemcpy(a_d, a, n*n*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(b_d, b, n*n*sizeof(int), cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(10,10);
    dim3 numBlocks((n*n)/(10*10),1);

    clock_t start_d=clock();
    printf("Doing GPU matrix saxpy\n");
    saxpy<<<numBlocks, threadsPerBlock>>>(a_d, b_d, c_d, n);
    cudaCheckError();

    //Wait for kernel call to finish
    cudaDeviceSynchronize();

    clock_t end_d = clock();
    

    printf("Doing CPU Vector add\n");
    clock_t start_h = clock();
    saxpy_h(a, b, c2, n);
    clock_t end_h = clock();
	
    //Time computing
    double time_d = (double)(end_d-start_d)/CLOCKS_PER_SEC;
    double time_h = (double)(end_h-start_h)/CLOCKS_PER_SEC;

    //Copying data back to host, this is a blocking call and will not start until all kernels are finished
    cudaMemcpy(c, c_d, n*n*sizeof(int), cudaMemcpyDeviceToHost);
    printf("n = %d \t GPU time = %fs \t CPU time = %fs\n", n, time_d, time_h);

    //Free GPU memory
    cudaFree(a_d);
    cudaFree(b_d);
    cudaFree(c_d);
    return 0;
}
