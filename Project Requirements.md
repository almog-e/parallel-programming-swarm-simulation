# Project Requirements
## Distributed Drone Swarm Simulation (MPI)

This document defines the **mandatory requirements**, **optional extensions**, and **evaluation criteria** for the distributed drone swarm simulation project.

---

## 1. System Overview

The system simulates a swarm of autonomous drones exploring a 3D arena.
Each drone runs as an independent MPI process and communicates with a central **Tower (Headquarters)** for coordination, collision avoidance, and mission tracking.

Core goals:
- Distributed simulation using MPI
- Safe navigation with collision avoidance
- Exploration and coverage of a 3D grid
- Real-time visualization
- Performance optimization using OpenMP and SIMD

---

## 2. Process Roles (MPI Ranks)

### Mandatory Roles
- **Tower (Rank 0)**
  - Maintains global state
  - Tracks drone positions and cells
  - Detects collision risks
  - Aggregates exploration coverage
  - Enforces classified-data rules

- **Drone (Rank 1..N)**
  - Autonomous movement and exploration
  - Collision avoidance
  - Local tracking of visited cells
  - Communication with Tower and nearby drones only

### Optional Role
- **World / GUI (Optional Rank)**
  - Visualization only
  - Receives positions from Tower
  - Does not implement mission logic

---

## 3. Arena and Grid

- The arena is a 3D bounded space.
- It is divided into uniform **3D grid cells**.
- Each drone must:
  - Track its current cell
  - Detect when it moves to a new cell
- Cell adjacency is defined as:
  - **26 neighboring cells** (faces + edges + corners)

---

## 4. Collision Avoidance (Mandatory)

### 4.1 Detection
- Drones must check Euclidean distance to other drones.
- A collision risk exists if:
  - `distance < safety_threshold` (default: 1.5 units)
- At minimum, drones must check:
  - All drones in the **same cell**
- Optional improvement:
  - Also check adjacent cells

### 4.2 Avoidance
- When a collision risk is detected, the drone must:
  - Change velocity and/or direction
  - Move away from the closest drone(s)
- Accepted strategies:
  - Repulsion vector
  - Random perturbation
  - Steering-based behavior

### 4.3 Constraints
- Zero actual collisions are allowed.
- Oscillation (“vibration”) behavior should be avoided.

---

## 5. Mission Logic and Exploration

### 5.1 Coverage Tracking
- Each drone maintains a set/bitmap of visited cells.
- The Tower aggregates global coverage.

### 5.2 Exploration Strategy
- Drones should attempt to visit unvisited cells.
- Allowed strategies include:
  - Random walk
  - Greedy nearest-unvisited cell
  - Hybrid approaches

### 5.3 Classified Reconnaissance Data
Reconnaissance data = **visited cell information**

Rules:
- Drone → Tower:
  - **Allowed only if drone is in the same cell as Tower HQ**
- Drone → Drone:
  - **Allowed only if drones are in the same or adjacent cells**
- Violating these rules is considered incorrect behavior.

### 5.4 Mission Completion
The mission ends when:
- 100% of cells are visited
  **OR**
- A predefined maximum number of steps/time is reached

---

## 6. MPI Communication Requirements

### 6.1 General Rules
- All inter-process communication must use MPI.
- Both blocking and non-blocking calls should be used where appropriate.
- Custom MPI message tags must be defined.

### 6.2 Required Message Types
At minimum:
- `POS_UPDATE` – drone position
- `CELL_UPDATE` – current cell
- `VISITED_INTEL` – visited cells (classified)
- `CELLMATES` – drones in same cell
- `COLLISION_WARNING`
- `METRICS` – performance data

### 6.3 Communication Reduction (Mandatory)
- Drones send `CELL_UPDATE` **only when changing cells**
- Position updates are rate-limited (fixed timestep)
- Classified data is never broadcast globally

---

## 7. Visualization (GUI)

- A real-time OpenGL/GLUT GUI must be provided.
- The GUI must display:
  - Arena boundaries
  - Drones (position + ID)
- The GUI:
  - May run in Tower or a separate rank
  - Must not implement mission logic

---

## 8. Mission Dashboard / Log Server (Mandatory)

- A centralized dashboard must collect:
  - Collision warnings
  - Coverage updates
  - Performance metrics
- Implementation options:
  - Separate process
  - TCP / UDP / HTTP server (Go or C++)
- Recommended format:
  - One JSON record per event


---

## 9. Parallelism and Optimization

### 9.1 OpenMP (Mandatory)
Must be used in at least one of:
- Collision detection loops
- Grid initialization
- Message processing

### 9.2 SIMD (Mandatory)
- At least one AVX2-based optimization must be implemented.
- Example:
  - Batch distance computation using vector registers
- A before/after timing comparison is required.


---

## 10. Determinism and Testing

- A fixed random seed must be supported.
- A standard test scenario must be documented:
  - Arena size
  - Grid resolution
  - Number of drones
  - Safety threshold

---

## 11. Final Deliverables

Students must submit:
1. Complete source code
2. `project_requirements.md` (this file)
3. Short report including:
   - Architecture overview
   - Communication patterns
   - Collision avoidance logic
   - OpenMP and SIMD usage
   - Performance results

---

## 12. Optional Extensions (Bonus)

- Adaptive exploration strategies
- Hierarchical cell partitioning
- Advanced steering behaviors
- Additional SIMD optimizations
- Fault tolerance (drone failure handling)

---

## 13. Evaluation Criteria (Summary)

- Correct MPI usage
- Collision-free execution
- Enforcement of classified-data rules
- Quality of architecture
- Measured performance improvements
- Code clarity and documentation



