#include "mpi.h"
#include <iostream>
#include <time.h>

using namespace std;

#define ARRAY_SIZE 100

int* randomNumbersGenerator(int rank) {
	int index;
	int *array = new int[ARRAY_SIZE];

	srand((int)time(NULL) + rank);

	for (index = 0; index < ARRAY_SIZE; index++) {
		array[index] = rand() % 1000;
		cout << array[index] << " ";
	}
	cout << endl;

	return array;
}

int computeSum(int* array) {
	int index;
	int sum = 0;

	for (index = 0; index < ARRAY_SIZE; index++)
		sum += array[index];

	return sum;
}
int main(int argc, char *argv[])
{
	int rank;
	int size;
	int* randomlyGeneratedArray;
	double start_time = 0;
	double end_time = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size)

	if (rank == 0) {
		cout << "Root process" << endl << endl;
	}

	if (rank != 0) {
		start_time = MPI_Wtime();
		cout << "Start time for process " << rank << ": " << start_time << endl << endl;
		cout << "Process " << rank << " elements: " << endl << endl;
		randomlyGeneratedArray = randomNumbersGenerator(rank);
		int sum = computeSum(randomlyGeneratedArray);
		cout << "Sum is:  " << sum << endl << endl;
		end_time = MPI_Wtime();
		cout << "Finish time for process " << rank << ": " << end_time << endl << endl;
		cout << "Time elapsed for process " << rank << ": " << (end_time - start_time) << endl << endl;
	}

	MPI_Finalize();
}