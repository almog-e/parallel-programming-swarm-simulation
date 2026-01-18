# Part 3: Mission Dashboard, Optimizations, and SIMD

## 1. Mission Dashboard (Required)

Build a mission dashboard (log server) to collect events from Tower and drones:
- Collision warnings
- Coverage updates
- Performance metrics

This must be implemented and can be a separate process or a lightweight TCP/UDP server. The goal is to centralize debugging information and provide a live mission view.

---

## 2. Performance Optimizations

You should apply and document optimizations such as:
- **OpenMP**: Parallelize collision checks, grid updates, or message handling.
- **SIMD (AVX2)**: Accelerate vector distance calculations.
- **Cell-based filtering**: Reduce pairwise checks by comparing only local neighbors.
- **Communication reduction**: Only send updates when drones change cells or after a timed interval.

---

## 3. SIMD Expectations

Demonstrate at least one SIMD optimization in your code:
- Example: load positions into vector registers and compute distances in batches.
- Compare performance before/after (basic timing is sufficient).

---

## 4. Final Deliverables

- Complete source code for your system.
- A short report describing:
  - Architecture and design decisions.
  - Communication patterns and collision avoidance logic.
  - Where and how OpenMP/SIMD were applied.
  - Any new features or optimizations you implemented.

---

Good luck, and have fun building your own distributed drone simulation!
