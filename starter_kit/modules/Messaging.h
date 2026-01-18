#pragma once

#include <array>

constexpr int kTagPosition = 100;
constexpr int kTagIntel = 110;
constexpr int kTagWarning = 120;

struct PositionMessage {
  int id = -1;
  std::array<float, 3> position{0.0f, 0.0f, 0.0f};
};
