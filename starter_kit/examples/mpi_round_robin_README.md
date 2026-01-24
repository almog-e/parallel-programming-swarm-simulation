# MPI Round Robin Example

This example demonstrates passing a token through MPI ranks in a ring.

## Build

```bash
mpic++ mpi_round_robin.cpp ../modules/World.cpp ../modules/Drone.cpp ../modules/Tower.cpp -o mpi_round_robin
```

## Run

Use at least 2 ranks:

```bash
mpirun -np 4 ./mpi_round_robin
```

## Requirements
- MPI (OpenMPI or MPICH)
- C++ compiler (g++)
