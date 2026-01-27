// collision.cpp
// General collision check for 3D points (spheres)
#include <cmath>

// Returns true if two spheres (at (x1,y1,z1) and (x2,y2,z2) with radius r) overlap
bool check_collision(float x1, float y1, float z1, float x2, float y2, float z2, float min_dist) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;
    float dist2 = dx*dx + dy*dy + dz*dz;
    return (dist2 < min_dist*min_dist && dist2 > 1e-8f);
}

// Returns the overlap distance (positive if overlapping, 0 if not)
float collision_overlap(float x1, float y1, float z1, float x2, float y2, float z2, float min_dist) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;
    float dist = std::sqrt(dx*dx + dy*dy + dz*dz);
    float overlap = min_dist - dist;
    return (overlap > 0.0f) ? overlap : 0.0f;
}
