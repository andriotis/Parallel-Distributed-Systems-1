# How to evaluate my code

There are four implementations to evaluate:

* sequential
* pthreads
* cilk
* openmp

To do so, you need only one think, the hpc container from the course I took at university. To download it follow the link below, it has all the information you need.

https://github.com/AUTh-csal/Docker

After you have successfully downloaded and installed the container, you have to download the source code.

Either clone it or download the [zip](https://github.com/andriotis/pds-assignment-1/archive/refs/heads/main.zip) <strong>inside a folder the container can see</strong>.

Now you are ready to evaluate! The number of triangles for each matrix are:

* Number of triangles for each graph
* belgium_osm: 2.420
* com-Youtube: 3.056.386
* mycielskian13 : 0
* dblp-2010 : 1.676.652

## Sequential Implementation

1. Create the executables <code>make sequential</code>

2. Run seq providing the filepath of the .mtx file <code>./seq \<filepath\></code>

e.g if I wanted to evaluate mycielskian13.mtx the command would be <code>./seq ./matrices/mycielskian13.mtx</code>

## PThreads Implementation

1. Create the executables using <code>make pthreads</code>

2. Run pthreads providing the filepath of the .mtx file and the number of threads you want <code>./pthreads \<filepath\> \<number of threads\></code>

e.g if I wanted to evaluate dblp-2010.mtx the command would be <code>./pthreads ./matrices/dblp-2010.mtx 4</code>

## Cilk Implementation

1. Create the executables using <code>make cilk</code>

2. Run cilk providing the filepath of the .mtx file and the number of threads you want <code>./cilk \<filepath\> CILK_NWORKERS=\<number of threads\></code>

e.g if I wanted to evaluate com-Youtube.mtx the command would be <code>./cilk ./matrices/com-Youtube.mtx CILK_NWORKERS=4</code>

## OpenMP Implementation

1. Create the executables using <code>make openmp</code>

2. Run omp providing the filepath of the .mtx file and the number of threads you want <code>./omp \<filepath\> \<number of threads\></code>

e.g if I wanted to evaluate belgium_osm.mtx the command would be <code>./omp ./matrices/belgium_osm.mtx 4</code>

## Thanks for the evaluation! If you encountered any problem, please send me an email or a direct message.

Nikos Andriotis
