#include "mpi.h"
#include <iostream>
#include<time.h>

#define SIZE 100
#define KEY 95

using namespace std;


int main(int argc, char *argv[])
{
	int rank, size, segmentSize, startPos, endPos, found = -1, finalFound = -1;
	int array[SIZE];

	srand((int)time(NULL) + 1);

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		cout << "The randomly generated array is: " << endl << endl;
		for (int i = 0; i < SIZE; i++) {
			array[i] = rand() % 100;
			cout << array[i] << " ";
		}
		cout << endl << endl;
		cout << "The searched number is: " << KEY << endl << endl;
	}

	segmentSize = SIZE / size;
	if (SIZE % size != 0)
		++segmentSize;

	MPI_Bcast(array, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

	startPos = rank * segmentSize;
	endPos = startPos + segmentSize - 1;

	for (int i = startPos; i <= endPos; i++) {
		if (array[i] == KEY) {
			found = i;
			cout << "Number found on position: " << i << ", rank: " << rank << endl << endl;
		}
	}

	MPI_Reduce(&found, &finalFound, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		if (finalFound == -1) {
			cout << "The number wasn`t found " << endl << endl;
		}
		else {
			cout << "The final position the number was found on is: " << finalFound << endl << endl;
		}
	}

	MPI_Finalize();
}