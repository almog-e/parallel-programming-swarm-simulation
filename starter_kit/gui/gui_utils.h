#ifndef GUI_UTILS_H
#define GUI_UTILS_H

#include <GL/glut.h>

void drawGrid3D(float min, float max, float step);
void drawAxes(float length);
void drawDot(float x, float y, float z, float r, float g, float b, float size);
void drawDotWithLabel(float x, float y, float z, int dotIndex, float r, float g, float b, float size);
void setCamera(float centerX, float centerY, float centerZ);
void keyboard(int key, int x, int y);
void keyboard_ascii(unsigned char key, int x, int y);

#endif // GUI_UTILS_H
