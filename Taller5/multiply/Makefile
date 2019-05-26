NVCC = nvcc

all: matrixMultiply

%.o : %.cu
	$(NVCC) -c $< -o $@

matrixMultiply : matrixMultiply.o
	$(NVCC) $^ -o $@

clean:
	rm -rf *.o *.a matrixMultiply
