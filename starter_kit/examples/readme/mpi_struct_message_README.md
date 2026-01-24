# MPI Struct Message Example

This example demonstrates sending a struct with position data between MPI ranks.

## Build

```bash
mpic++ mpi_struct_message.cpp ../modules/World.cpp ../modules/Drone.cpp ../modules/Tower.cpp -o mpi_struct_message
```

## Run

Use 2 ranks:

```bash
mpirun -np 2 ./mpi_struct_message
```

## Requirements
- MPI (OpenMPI or MPICH)
- C++ compiler (g++)
