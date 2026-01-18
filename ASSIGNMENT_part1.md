# Reconnaissance Mission: Assignment Overview (Part 1)

## General Idea

In this assignment, you are running a **Reconnaissance Mission** with a swarm of drones. The drones scout a 3D arena, report sensitive intel, and avoid collisions while a headquarters **Tower** coordinates the mission. Because the data is sensitive, reconnaissance information must only be exchanged at **close proximity**.

This project guides you through building the system from scratch, using MPI for distributed communication and OpenGL/GLUT for visualization. You will design the architecture, implement the algorithms, and optimize for performance and scalability.

## What You Will Learn (and Gain)
- How to model a distributed multi-agent system using MPI ranks.
- How to design message flows for sensitive reconnaissance data.
- How to integrate real-time visualization for mission monitoring.
- How to implement collision detection and basic coordination logic.
- How to scale performance using OpenMP/SIMD in later stages.

---

## What Each Part Covers

- **Part 1 (this file):** Establish reconnaissance roles, build core drone ↔ Tower communication, visualize drones, and implement basic motion and proximity detection.
- **Part 2:** Ensure the project is fully MPI-based (if not already), add the collision avoidance algorithm, and formalize mission logic and sensitive-data communication rules.
- **Part 3:** Build the mission dashboard/log server and apply performance optimizations (OpenMP, SIMD, communication reduction strategies).

---

## MPI Primer (Short Intro)

MPI (Message Passing Interface) lets multiple processes communicate in a distributed system. Each process has a **rank** (ID). You will typically launch the system with `mpirun` or `mpiexec`, and each process can decide its role based on its rank:

- **Rank 0**: Tower (headquarters)
- **Rank 1..N**: Drones
- **Optional extra rank**: World/GUI process (or integrate into the Tower)

For Part 1, MPI is *recommended* but **not mandatory yet**. You can prototype single-process logic first, but the architecture must be MPI-ready.

---

## Core Components (You Must Implement in Part 1)

### 1. Drone Class
- Position (x, y, z)
- Velocity (vx, vy, vz)
- Unique ID (rank or assigned ID)
- Simple movement logic (random or planned path)

### 2. Tower (Headquarters)
- Has a fixed **location** on the map (belongs to a cell).
- Receives drone positions and sensitive reconnaissance reports only when drones are **nearby**.
- Calculates distances between drones.
- If any drones are too close, prints a **collision warning**.

### 3. World (Visualization)
- Responsible for drawing the arena and drones.
- Can be a separate MPI rank for scalability or integrated into the Tower for simplicity.

---

## Part 1 Requirements

1. **Drone ↔ Tower Communication**
  - Drones send their positions to the Tower regularly.
  - Tower keeps a global list of drone positions.

2. **Movement and Visualization**
  - Drones move (random or planned).
  - World (or Tower) visualizes drone positions in the GUI.

3. **Proximity Detection (Print Only)**
  - Drones themselves can print a message if they get too close.
  - **Tower must also compute distances between drones and print a warning** when a collision risk is detected.

4. **MPI Usage (Optional for Part 1, Required Later)**
  - You may prototype this in a single process.
  - If you do use MPI already, it should be cleanly structured so Part 2 builds on it.

5. **OpenMP (Optional in Part 1)**
  - You may use OpenMP to accelerate distance checks in the Tower if desired.

---

## Templates (Starting Point Suggestions)

### Minimal MPI Skeleton
```cpp
int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Tower (headquarters)
    } else {
        // Drone
    }

    MPI_Finalize();
    return 0;
}
```

### Example GUI Run (Template)
```sh
mpirun -np 4 ./mpi_drones
```
- **Rank 0**: Tower (also runs GUI if you integrate it here)
- **Ranks 1-3**: Drones

---

## Summary of Part 1 Deliverable

By the end of Part 1 you should have:
- A basic **Drone class** with movement.
- A **Tower** that receives positions and detects collisions.
- A **World/GUI** that visualizes drones.
- Basic MPI structure (optional but recommended).

Part 1 sets the stage for full MPI and collision avoidance logic in Part 2.
