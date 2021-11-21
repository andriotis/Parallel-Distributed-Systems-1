CC = gcc
CILKCC=/usr/local/OpenCilk-9.0.1-Linux/bin/clang

sequential: sequential.c mmio.c utilities.c coo2csc.c
			$(CC) -O3 -c sequential.c mmio.c utilities.c coo2csc.c
			$(CC) sequential.o mmio.o utilities.o coo2csc.o -o seq

pthreads: pthreads.c mmio.c utilities.c coo2csc.c
		$(CC) -O3 -c pthreads.c mmio.c utilities.c coo2csc.c
		$(CC) pthreads.o mmio.o utilities.o coo2csc.o -o pthreads -lpthread 

openmp: openmp.c mmio.c utilities.c coo2csc.c
		$(CC) -O3 -c openmp.c mmio.c utilities.c coo2csc.c
		$(CC) openmp.o mmio.o utilities.o coo2csc.o -o omp -fopenmp

cilk: opencilk.c mmio.c utilities.c coo2csc.c
	$(CILKCC) -O3 -c opencilk.c mmio.c utilities.c coo2csc.c
	$(CILKCC) opencilk.o mmio.o utilities.o coo2csc.o -o cilk -lpthread -fcilkplus 