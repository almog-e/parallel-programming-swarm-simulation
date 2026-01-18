#pragma once

#include <array>
#include <vector>

struct Tower {
  std::array<float, 3> hq_position{0.0f, 0.0f, 0.0f};
  float warning_distance = 1.5f;

  bool detect_collision(const std::vector<std::array<float, 3>> &positions) const;
};
