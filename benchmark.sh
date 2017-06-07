#!/bin/bash
for nthreads in {1..24}
do
   export OMP_NUM_THREADS=$nthreads
   echo "_______"
   time ./omp_pi
   echo "_______"
done
