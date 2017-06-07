#include <omp.h>
#include <stdio.h>
static unsigned long num_steps = 5e11;
double step,step_sqr;
//#define NUM_THREADS 4
void main (){
   unsigned long i;
   //int report_count=10;
   //int should_report;
   double sum[20];
   double pi;
   int id;
   int nthreads;
   step = 1.0/(double) num_steps;
   step_sqr=step*step;
   #pragma omp parallel shared(sum) private(id)
   {
// Moving x within the parallel region actually sped this up
      double x_sqr;
      id = omp_get_thread_num();
      sum[id] = 0.0;
      double to_add;
      if(id==0){
        nthreads = omp_get_num_threads();
        printf("Number of threads = %d \n", nthreads);
      }
      printf("Thread %d starting...\n", id);
   #pragma omp for schedule(static) private(x_sqr)
         for (i=1; i < num_steps; i++){
            //x = i *step;
            x_sqr=i*i*step_sqr;
            //to_add = 4.0/(1.0+x*x);
            //sum[id] += to_add;
            sum[id] += 4.0/(1.0+x_sqr);
            //printf("Thread %d : i= %d | x= %.10f | to_add= %.10f  | sum[%d]= %.6f\n", id, i, x, to_add, id, sum[id]);
            //printf("%d,%d,%.10f,%.10f,%.6f\n", id, i, x, to_add,sum[id]);
         }

     printf("Thread %d done.\n", id);
// Parallel region over
}
     //printf("Number of threads = %d \n", nthreads);
     for(i=0, pi=3.0; i<nthreads ;i++){
      pi += sum[i];
      //printf("pi=%.16f\n",pi);
     }
     pi*=step;
     printf("\npi=%.16f\n",pi);
}
