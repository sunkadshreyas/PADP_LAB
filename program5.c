#include <string.h>
#include <stdio.h>
#include <mpi.h>

#define BUFFER_SIZE 32

char messages[3][20] = {
	"HELLO",
	"RVCE",
	"CSE"
};

int main(int argc, char **argv)
{
	char message[BUFFER_SIZE];
	int root = 0;
	int tag = 0;
	int myRank, numProcs, temp = 1;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	if(myRank == 0)
	{
		for(temp=1; temp<numProcs; temp++)
		{
			strcpy(message, messages[temp-1]);
			MPI_Send(message, BUFFER_SIZE, MPI_CHAR, temp, tag, MPI_COMM_WORLD);
		}
	}
	else
	{
		MPI_Recv(message, BUFFER_SIZE, MPI_CHAR, root, tag, MPI_COMM_WORLD, &status);
		printf("%s is the message received by process of rank %d sent from process of rank %d", message, myRank, status);
	}
	MPI_Finalize();
	return 0;
}