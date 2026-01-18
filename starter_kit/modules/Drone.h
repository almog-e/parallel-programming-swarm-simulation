#pragma once

#include <array>

struct Drone {
  int id = -1;
  std::array<float, 3> position{0.0f, 0.0f, 0.0f};
  std::array<float, 3> velocity{0.0f, 0.0f, 0.0f};

  void step(float dt);
};
