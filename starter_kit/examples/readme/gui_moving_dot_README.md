## Building and Running gui_moving_dot.cpp

To compile and run the 3D moving dot example, you need to link with the GLUT, GLU, and OpenGL libraries. Use the following command:

```
g++ gui_moving_dot.cpp -lglut -lGLU -lGL -o gui_moving_dot
```

Then run the program with:

```
./gui_moving_dot
```

If you encounter errors about `gluLookAt` or `gluPerspective` being undefined, make sure you have included the `-lGLU` flag in your compile command.
# GUI Moving Dot Example

This example demonstrates a minimal GLUT program that moves a dot on the screen.

## Build

Install GLUT if needed:
```bash
sudo apt-get install freeglut3-dev
```

Compile:
```bash
g++ gui_moving_dot.cpp -lglut -lGL -o gui_moving_dot
```

## Run

```bash
./gui_moving_dot
```

## Requirements
- GLUT (freeglut)
- C++ compiler (g++)
