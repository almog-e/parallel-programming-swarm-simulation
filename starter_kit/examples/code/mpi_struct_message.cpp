#include <mpi.h>

#include <array>
#include <iostream>

struct StatusMessage {
  int drone_id;
  float x;
  float y;
  float z;
};

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Datatype message_type;
  int lengths[2] = {1, 3};
  MPI_Aint displacements[2];
  MPI_Datatype types[2] = {MPI_INT, MPI_FLOAT};

  StatusMessage sample{};
  MPI_Aint base_address = 0;
  MPI_Get_address(&sample, &base_address);
  MPI_Get_address(&sample.drone_id, &displacements[0]);
  MPI_Get_address(&sample.x, &displacements[1]);
  displacements[0] -= base_address;
  displacements[1] -= base_address;

  MPI_Type_create_struct(2, lengths, displacements, types, &message_type);
  MPI_Type_commit(&message_type);

  if (rank == 0) {
    StatusMessage msg{1, 2.5f, 1.0f, 0.0f};
    MPI_Send(&msg, 1, message_type, 1, 42, MPI_COMM_WORLD);
    std::cout << "Tower sent status to drone 1." << std::endl;
  } else if (rank == 1) {
    StatusMessage msg{};
    MPI_Recv(&msg, 1, message_type, 0, 42, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "Drone " << msg.drone_id << " position: (" << msg.x << ", "
              << msg.y << ", " << msg.z << ")" << std::endl;
  }

  MPI_Type_free(&message_type);
  MPI_Finalize();
  return 0;
}
