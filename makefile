CC=gcc
CFLAGS= -g -fopenmp
OBJS= omp_pi.o

omp_pi:  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lm -o omp_pi

omp_pi.o: omp_pi.c
	$(CC) $(CFLAGS) -c omp_pi.c

clean :
	rm *.o
	rm omp_pi
