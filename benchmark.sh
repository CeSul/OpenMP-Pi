#!/bin/bash
for nthreads in {1..4}
do
   export OMP_NUM_THREADS=$nthreads
   echo "_______"
   time ./omp_pi -n 1000000000
   echo "_______"
done
