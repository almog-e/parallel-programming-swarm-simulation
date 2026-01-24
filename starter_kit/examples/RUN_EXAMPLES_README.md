# How to Run Each Example (Linux)

This guide explains how to build and run each example in the `starter_kit/examples` directory on Linux.

---

## 1. MPI Round Robin
**File:** mpi_round_robin.cpp

### Build:
```bash
mpic++ mpi_round_robin.cpp ../modules/World.cpp ../modules/Drone.cpp ../modules/Tower.cpp -o mpi_round_robin
```

### Run (with 4 ranks):
```bash
mpirun -np 4 ./mpi_round_robin
```

---

## 2. MPI Struct Message
**File:** mpi_struct_message.cpp

### Build:
```bash
mpic++ mpi_struct_message.cpp ../modules/World.cpp ../modules/Drone.cpp ../modules/Tower.cpp -o mpi_struct_message
```

### Run (with 2 ranks):
```bash
mpirun -np 2 ./mpi_struct_message
```

---

## 3. GUI Moving Dot
**File:** gui_moving_dot.cpp

### Build (requires GLUT):
```bash
sudo apt-get install freeglut3-dev   # if not installed

# Compile:
g++ gui_moving_dot.cpp -lglut -lGL -o gui_moving_dot
```

### Run:
```bash
./gui_moving_dot
```

---

## 4. Go Server + C++ Client

### Go Server
**File:** go_server/main.go

#### Run:
```bash
cd go_server
# If Go is installed:
go run main.go
```

### C++ Client
**File:** cpp_to_go_client.cpp

#### Build:
```bash
g++ cpp_to_go_client.cpp -o cpp_to_go_client
```

#### Run (in a separate terminal, after starting the Go server):
```bash
./cpp_to_go_client
```

---

For more details, see the comments in each example file.
