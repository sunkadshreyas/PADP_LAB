#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <omp.h>

#define PI 3.1415926538837211

int main(int argc, char **argv)
{
    int Noofintervals, i;
    double x, totalsum, h;

    printf("\nEnter number of intervals\n");
    scanf("%d", &Noofintervals);

    /* No. of intervals should be positive integer */
    if (Noofintervals <= 0)
    {
        printf("\n\t\t Number of intervals should be positive integer\n");
        exit(1);
    }

    int l;
    for (l = 1; l <= 16; l = l << 1)
    {
        totalsum = 0.0;
        h = 1.0 / Noofintervals;
        double st = omp_get_wtime();
        omp_set_num_threads(l);
#pragma omp parallel for private(x) reduction(+ \
                                              : totalsum)
        for (i = 1; i < Noofintervals + 1; i++)
        {
            x = h * (i + 0.5);
            totalsum = totalsum + 4.0 / (1.0 + x * x);
        }
        totalsum = totalsum * h;
        printf("\nCalculated PI :  \t%1.15lf  \nError : \t%1.16lf\n", totalsum, fabs(totalsum - PI));
        double end = omp_get_wtime();
        printf("Time taken for %d thread(s) for %d iterations: %lf\n", l, Noofintervals, end - st);
    }
    return 0;
}

// MPI Version

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#define SEED 3655942
i nt main(int argc,char **argv)
{
	
	
	int iter=1000000;
  
	int i,reduced_count,reduced_iter,count=0;
	int rank;
	double pi,x,y,z,t;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank==0)
		t=MPI_Wtime();
	if(rank>0)
	{
		srand(SEED);
		for(i=0;i<iter;i++)
		{
			x=(double)rand()/RAND_MAX;
			y=(double)rand()/RAND_MAX;
			z=x*x+y*y;
			if(z<=1)
				count++;
		}	
	}	
	MPI_Reduce(&count,&reduced_count,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&iter,&reduced_iter,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	reduced_iter=reduced_iter-iter;
	if(rank==0)
	{
		t=MPI_Wtime()-t;
		pi=(double)reduced_count/(double)reduced_iter * 4;
		printf("\npi: %lf time : %lf",pi,t);
	}	
	MPI_Finalize();

	return 0;
}