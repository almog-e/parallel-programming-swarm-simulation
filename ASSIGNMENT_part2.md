# Part 2: Full MPI, Mission Logic, and Collision Avoidance (Reconnaissance)

## 1. Collision Avoidance (What You Must Implement)

Each drone must avoid collisions with other drones using a distance-based approach:

1. **Distance Check:**
  - Each drone calculates the Euclidean distance to every other drone (initially, all-pairs check).
  - If the distance to any other drone is less than a safety threshold (e.g., 1.5 units), the drone must trigger an avoidance maneuver.
  - **Improvement:** you can also check adjacent cells, not just the same cell, for better safety.

2. **Avoidance Maneuver:**
  - When a collision is imminent, the drone should change its velocity or direction to move away from the closest drone(s).
  - You may use a simple repulsion vector, random nudge, or a more advanced steering behavior.

**Tip:** Once you implement cell partitioning as an improvement, you will only need to check cellmates, making your system much more efficient.

---

## 2. Mission Logic (What the Drones Should Do)

Each drone's mission is to explore and cover as much of the arena as possible:

1. **Coverage Grid:**
  - The arena is divided into cells. Each drone keeps track of which cells it has visited.
  - The Tower can aggregate this information to track global coverage.

2. **Exploration:**
  - Drones should move from cell to cell, aiming to visit unvisited cells.
  - You may implement a simple random walk, greedy nearest-unvisited-cell, or another exploration strategy.

3. **Reporting:**
  - Drones periodically report their visited cells to the Tower.
  - Because reconnaissance data is sensitive, **visited-cell intel is classified** and must only be delivered in **close proximity** (same cell as the Tower headquarters).

4. **Collaboration:**
  - Drones may share their visited cells with **nearby** drones only (same cell or adjacent cells), to avoid redundant exploration.

5. **Mission Completion:**
  - The mission is complete when all cells are visited, or after a set number of steps/time.

**Tip:** Use sets or bitmaps to efficiently track visited/unvisited cells. Design your communication so that coverage information is shared efficiently.

---

## 3. System Requirements (MPI-First)

**You must build:**
- A simulation where multiple drone processes (MPI ranks) explore a 3D arena.
- A central **Tower (headquarters)** process (MPI rank) that coordinates global state and cellmate detection.
- A **World** process (optional, or integrated with Tower) that can broadcast all drone positions and handle visualization.
- A GUI (GLUT/OpenGL) that visualizes the arena and drone activity in real time.

---

## 4. Collision Detection Algorithm
- Divide the arena into 3D grid cells.
- Each drone tracks its current cell and checks for collisions with drones in the same cell (cellmates).
- Use Euclidean distance to detect potential collisions and trigger avoidance maneuvers.
- **Optional optimization:** reduce checks by using cells and adjacent cells.

---

## 5. MPI and Communication
- Use MPI for all inter-process communication.
- Each drone and the tower must run as separate MPI ranks (processes).
- Drones send their cell updates and visited cells to the tower.
- The tower aggregates global coverage and notifies drones of their cellmates.
- Drones can also communicate directly (P2P) to share visited cells and warnings.
- Use both blocking and non-blocking MPI calls, with custom message tags for each type of data.

---

## 6. Communication Patterns
- **Drone ↔ Drone:** Peer-to-peer sharing of visited cells and warnings **only when close** (same cell or adjacent cells).
- **Drone ↔ Tower:** Drones notify the tower of their cell and send visited-cell intel **only when in the same cell as Tower HQ**. Tower sends back aggregated coverage and cellmate notifications.
- **Tower ↔ World/GUI:** Tower can activate the GUI directly, or you can run a separate GUI rank for scalability.

---

## 7. GUI and Arena Designer
- You will receive a GLUT/OpenGL-based GUI and an arena designer.
- Integrate your simulation with the GUI to visualize drones and arena blocks in real time.
- The GUI should launch automatically when running the simulation.

---

## 8. Parallelism and Communication Reduction

Parallelism is part of Part 2 (not just future work):
- Use OpenMP to parallelize expensive loops (e.g., grid initialization, collision checks).
- Use SIMD (e.g., AVX2 intrinsics) for fast vector math in distance calculations.
- **Reduce communication where possible** (example: only notify the Tower when a drone changes cells, or batch updates).
