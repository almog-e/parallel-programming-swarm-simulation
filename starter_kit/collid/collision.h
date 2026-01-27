// collision.h
// Header for general collision check for 3D points (spheres)
#pragma once

// Returns true if two spheres (at (x1,y1,z1) and (x2,y2,z2) with radius r) overlap
bool check_collision(float x1, float y1, float z1, float x2, float y2, float z2, float min_dist);

// Returns the overlap distance (positive if overlapping, 0 if not)
float collision_overlap(float x1, float y1, float z1, float x2, float y2, float z2, float min_dist);
