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