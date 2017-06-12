// Use OpenMP to split up pi calculation between multiple threads
// Each thread does some portion of an integral
/******************************************************************************/
// Usage: omp_pi [options]
//
// Options:
//  -n <num_steps> Sets the number of steps to use for integral (default = 1e4)
/******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
unsigned long num_steps;
double step,step_sqr;
char * program_name;

void usage() {
    printf("Usage is %s [options]\n",program_name);
    printf("Options:\n");
    printf("-n <grid_pts>   Sets number of grid points to use (default=1e4)\n");
    exit(8);
}

void set_args(int argc, char* argv[],unsigned long* num_steps) {
    int num_steps_IsSet=0;
    int len;
    // Parse arguments
    while ((argc >1) && (argv[1][0] == '-')) {
// argv[1][1] is the option character
        switch(argv[1][1]) {
        case 'n':
            // set num_steps
            len = strlen(argv[2]);
            char* end_ptr = (argv[2]+len-1);
            *num_steps=strtoul(argv[2],&end_ptr,10);
            num_steps_IsSet=1;
            break;
        default:
            printf("Bad option %s\n",argv[1]);
            usage();
            break;
        }
        argv+=2;
        argc-=2;
    }
    // Set defaults if necessary
    if(!num_steps_IsSet) {
        *num_steps=1e4;
    }
}




void main (int argc, char* argv[]) {
    program_name = argv[0];

    unsigned long i;
    double sum[40];
    double pi;
    int id;
    int nthreads;

    set_args(argc,argv,&num_steps);
    printf("num_steps=%lu\n",num_steps );
    step = 1.0/(double) num_steps;
    step_sqr=step*step;
    #pragma omp parallel shared(sum) private(id)
    {
        double x_sqr;
        id = omp_get_thread_num();
        sum[id] = 0.0;
        double to_add;
        if(id==0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d \n", nthreads);
        }
        printf("Thread %d starting...\n", id);

        #pragma omp for schedule(dynamic) private(x_sqr)
        for (i=1; i < num_steps; i++) {
            x_sqr=i*i*step_sqr;
            sum[id] += 4.0/(1.0+x_sqr);
        }
        printf("Thread %d done.\n", id);
    }
// Parallel region over
    //printf("Number of threads = %d \n", nthreads);
    for(i=0, pi=3.0; i<nthreads ; i++) {
        pi += sum[i];
    }
    pi*=step;
    printf("\npi=%.16f\n",pi);
}
