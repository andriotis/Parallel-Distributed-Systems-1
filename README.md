# How to evaluate my code

There are four implementations to evaluate:

* sequential
* pthreads
* cilk
* openmp

To do so, you need only one think, the hpc container from the course I took at university. To download it follow the link below, it has all the information you need.

https://github.com/AUTh-csal/Docker

After you have successfully downloaded and installed the container, you have to download the source code.

Either clone it or download the [zip](https://github.com/andriotis/pds-assignment-1/archive/refs/heads/main.zip) **inside a folder the container can see**.

Now you are ready to evaluate! The number of triangles for each matrix are:

|Matrices|Triangles|
|:-----------:|:-----------:|
|belgium_osm|2,420|
|com-Youtube|3,056,386|
|mycielskian13|0|
|dblp-2010|1,676,652|

---
**NOTE 💡**

You need start the container and execute the following commands inside it.

---

## Sequential Implementation

1. Create the executables `make sequential`

2. Run seq providing the filepath of the .mtx file

`./seq \<filepath\>`

e.g if I wanted to evaluate **mycielskian13** the command would be

`./seq ./matrices/mycielskian13.mtx`

## PThreads Implementation

1. Create the executables using `make pthreads`

2. Run pthreads providing the filepath of the .mtx file and the number of threads you want

`./pthreads \<filepath\> \<number of threads\>`

e.g if I wanted to evaluate **dblp-2010** with **4** threads, the command would be

`./pthreads ./matrices/dblp-2010.mtx 4`

## Cilk Implementation

1. Create the executables using `make cilk`

2. Run cilk providing the filepath of the .mtx file and the number of threads you want

`./cilk \<filepath\> CILK_NWORKERS=\<number of threads\>`

e.g if I wanted to evaluate **com-Youtube** with **4** workers, the command would be

`./cilk ./matrices/com-Youtube.mtx CILK_NWORKERS=4`

## OpenMP Implementation

1. Create the executables using `make openmp`

2. Run omp providing the filepath of the .mtx file and the number of threads you want

`./omp \<filepath\> \<number of threads\>`

e.g if I wanted to evaluate **belgium_osm** with **4** processes, the command would be

`./omp ./matrices/belgium_osm.mtx 4`

## Thanks for the evaluation! If you encountered any problem, please send me a direct message or an email.

Nikos Andriotis
