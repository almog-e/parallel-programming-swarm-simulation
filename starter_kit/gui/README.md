# gui

Reusable OpenGL/GLUT GUI utilities for 3D visualization. All drawing and camera logic is here.

## Files
- gui_utils.h / gui_utils.cpp: Functions for drawing axes, grids, dots, and labels in 3D.
- Handles camera movement, keyboard controls, and window setup.

## How to Use
- Include "gui_utils.h" in your C++ file.
- Link with gui_utils.cpp when compiling.
- Use provided functions to draw and control your 3D scene.

## Example
```cpp
#include "gui_utils.h"
// ...
drawAxes(1.5f);
drawGrid3D(-1.5f, 1.5f, 0.3f);
drawDot(x, y, z, r, g, b, size);
setCamera(center_x, center_y, center_z);
```

See the examples folder for full demos.