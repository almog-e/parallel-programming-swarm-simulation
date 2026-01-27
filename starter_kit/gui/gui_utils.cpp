// gui_utils.cpp
#include <GL/glut.h>
#include <cstdio>
#include <cmath>
#include "gui_utils.h"

void drawGrid3D(float min, float max, float step) {
  glColor3f(0.3f, 0.3f, 0.3f);
  glLineWidth(1.0f);
  glBegin(GL_LINES);
  int n_steps = static_cast<int>(round((max - min) / step));
  if (n_steps < 1) n_steps = 1;
  float actual_step = (max - min) / n_steps;
  // XY planes at each Z
  for (int zi = 0; zi <= n_steps; ++zi) {
    float z = min + zi * actual_step;
    for (int xi = 0; xi <= n_steps; ++xi) {
      float x = min + xi * actual_step;
      glVertex3f(x, min, z); glVertex3f(x, max, z);
    }
    for (int yi = 0; yi <= n_steps; ++yi) {
      float y = min + yi * actual_step;
      glVertex3f(min, y, z); glVertex3f(max, y, z);
    }
  }
  // XZ planes at each Y
  for (int yi = 0; yi <= n_steps; ++yi) {
    float y = min + yi * actual_step;
    for (int xi = 0; xi <= n_steps; ++xi) {
      float x = min + xi * actual_step;
      glVertex3f(x, y, min); glVertex3f(x, y, max);
    }
    for (int zi = 0; zi <= n_steps; ++zi) {
      float z = min + zi * actual_step;
      glVertex3f(min, y, z); glVertex3f(max, y, z);
    }
  }
  // YZ planes at each X
  for (int xi = 0; xi <= n_steps; ++xi) {
    float x = min + xi * actual_step;
    for (int yi = 0; yi <= n_steps; ++yi) {
      float y = min + yi * actual_step;
      glVertex3f(x, y, min); glVertex3f(x, y, max);
    }
    for (int zi = 0; zi <= n_steps; ++zi) {
      float z = min + zi * actual_step;
      glVertex3f(x, min, z); glVertex3f(x, max, z);
    }
  }
  glEnd();
}

void drawAxes(float length) {
  glLineWidth(3.0f);
  glBegin(GL_LINES);
  // X axis (red)
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-length, 0.0f, 0.0f);
  glVertex3f(length, 0.0f, 0.0f);
  // Y axis (green)
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, -length, 0.0f);
  glVertex3f(0.0f, length, 0.0f);
  // Z axis (blue)
  glColor3f(0.0f, 0.6f, 1.0f);
  glVertex3f(0.0f, 0.0f, -length);
  glVertex3f(0.0f, 0.0f, length);
  glEnd();
}

void drawDot(float x, float y, float z, float r, float g, float b, float size) {
  glColor3f(r, g, b);
  glPointSize(size);
  glBegin(GL_POINTS);
  glVertex3f(x, y, z);
  glEnd();
}

void drawDotWithLabel(float x, float y, float z, int dotIndex, float r, float g, float b, float size) {
  drawDot(x, y, z, r, g, b, size);
  glColor3f(1.0f, 1.0f, 1.0f);
  glRasterPos3f(x, y + 0.05f, z);
  char label[8];
  snprintf(label, sizeof(label), "%d", dotIndex);
  for (char* c = label; *c != '\0'; ++c) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
  }
}

// Camera globals must be declared extern here
extern float g_cam_angle_yaw;
extern float g_cam_angle_pitch;
extern float g_cam_radius;

void setCamera(float centerX, float centerY, float centerZ) {
  float yaw_rad = g_cam_angle_yaw * 3.1415926f / 180.0f;
  float pitch_rad = g_cam_angle_pitch * 3.1415926f / 180.0f;
  float cam_x = g_cam_radius * cosf(pitch_rad) * sinf(yaw_rad);
  float cam_y = g_cam_radius * sinf(pitch_rad);
  float cam_z = g_cam_radius * cosf(pitch_rad) * cosf(yaw_rad);
  gluLookAt(cam_x, cam_y, cam_z, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
}

void keyboard(int key, int x, int y) {
  float angle_step = 5.0f;
  switch (key) {
  case GLUT_KEY_LEFT:
    g_cam_angle_yaw -= angle_step;
    break;
  case GLUT_KEY_RIGHT:
    g_cam_angle_yaw += angle_step;
    break;
  case GLUT_KEY_UP:
    g_cam_angle_pitch += angle_step;
    if (g_cam_angle_pitch > 89.0f)
      g_cam_angle_pitch = 89.0f;
    break;
  case GLUT_KEY_DOWN:
    g_cam_angle_pitch -= angle_step;
    if (g_cam_angle_pitch < -89.0f)
      g_cam_angle_pitch = -89.0f;
    break;
  }
  glutPostRedisplay();
}

void keyboard_ascii(unsigned char key, int x, int y) {
  switch (key) {
  case '+':
  case '=':
    g_cam_radius -= 0.1f;
    if (g_cam_radius < 0.5f)
      g_cam_radius = 0.5f;
    break;
  case '-':
  case '_':
    g_cam_radius += 0.1f;
    if (g_cam_radius > 10.0f)
      g_cam_radius = 10.0f;
    break;
  }
  glutPostRedisplay();
}
