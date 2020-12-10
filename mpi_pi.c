//mpicc mpi_pi.c -o mpi_pi -lm
// mpicc mpi_pi.c -o mpi_pi -lm


#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <math.h>

#define ITERATIONS 2e09


int calculatePi(double *pi, int ID, int numprocs)
{   int start, end;   

    start = (ITERATIONS/numprocs) * ID;
    end = (ITERATIONS/numprocs) + 1;
    int i = start;

    do{
        *pi = *pi + (double)(4.0 / ((i*2)+1));
        i++;
        *pi = *pi - (double)(4.0 / ((i*2)+1));
        i++;
    }while(i < end);

    return 0;
}



int main(int argc, char *argv[])
{
	int done = 0, n, myid, numprocs, I, rc, i;
	double PI25DT = 3.141592653589793238462643;
	double local_pi, global_pi;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    if (myid == 0) printf("\nLaunching with %i processes", numprocs);
    calculatePi(&local_pi, myid, numprocs);
	MPI_Reduce(&local_pi, &global_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myid == 0) printf("\npi is approximately %.16f, Error is %.16f\n", global_pi, fabs(global_pi - PI25DT));
	MPI_Finalize();
	return 0; 
}

