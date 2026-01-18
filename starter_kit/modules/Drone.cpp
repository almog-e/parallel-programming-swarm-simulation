#include "Drone.h"

void Drone::step(float dt) {
  position[0] += velocity[0] * dt;
  position[1] += velocity[1] * dt;
  position[2] += velocity[2] * dt;
}
