#include "Tower.h"

#include <cmath>

bool Tower::detect_collision(const std::vector<std::array<float, 3>> &positions) const {
  for (size_t i = 0; i < positions.size(); ++i) {
    for (size_t j = i + 1; j < positions.size(); ++j) {
      const auto &a = positions[i];
      const auto &b = positions[j];
      const float dx = a[0] - b[0];
      const float dy = a[1] - b[1];
      const float dz = a[2] - b[2];
      const float dist = std::sqrt(dx * dx + dy * dy + dz * dz);
      if (dist < warning_distance) {
        return true;
      }
    }
  }
  return false;
}
