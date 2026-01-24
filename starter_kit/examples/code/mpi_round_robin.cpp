#include <mpi.h>
#include <unistd.h>  // for sleep function

#include <iostream>
#include <vector>
int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank = 0;
    int size = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        if (rank == 0) {
            std::cout << "Run with at least 2 ranks." << std::endl;
        }
        MPI_Finalize();
        return 0;
    }

    const int next = (rank + 1) % size;
    const int prev = (rank - 1 + size) % size;
    const int root = 0;

    int token = 0;
    while (1) {
        if (rank == root) {
            sleep(1);

            MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
            std::cout << "Rank " << rank << " sent token: " << token << std::endl;
            MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Rank " << rank << " received token: " << token << std::endl;
            std::cout << "Round-robin complete. Final token: " << token << std::endl;
        } else {
            MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::cout << "Rank " << rank << " received token: " << token << std::endl;
            token += 1;
            sleep(1);

            MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
            std::cout << "Rank " << rank << " sent token: " << token << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}
