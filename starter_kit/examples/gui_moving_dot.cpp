// Modular Moving Dot Example
// Build: g++ -o gui_moving_dot gui_moving_dot.cpp ../gui/gui_utils.cpp -I../gui -lGL -lGLU -lglut
// Run:   ./gui_moving_dot

#include "gui_utils.h"
#include <cmath>
#include <cstdio>

// Simulation tick counter
unsigned long g_tick = 0;

// Dot position and velocity
float g_pos_x = -0.9f;
float g_pos_y = 0.0f;
float g_pos_z = 0.0f;
float g_velocity_x = 0.01f;
float g_velocity_y = 0.008f;
float g_velocity_z = 0.012f;

// Camera globals required by gui_utils
float g_cam_angle_yaw = 0.0f;
float g_cam_angle_pitch = 0.0f;
float g_cam_radius = 2.0f;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  setCamera(0.0f, 0.0f, 0.0f);
  drawAxes(1.5f);
  drawGrid3D(-1.5f, 1.5f, 0.3f);
  drawDot(g_pos_x, g_pos_y, g_pos_z, 0.2f, 0.8f, 0.2f, 8.0f);
  glFlush();
}

void timer(int value) {
  g_pos_x += g_velocity_x;
  g_pos_y += g_velocity_y;
  g_pos_z += g_velocity_z;
  if (g_pos_x > 0.9f || g_pos_x < -0.9f)
    g_velocity_x = -g_velocity_x;
  if (g_pos_y > 0.9f || g_pos_y < -0.9f)
    g_velocity_y = -g_velocity_y;
  if (g_pos_z > 0.9f || g_pos_z < -0.9f)
    g_velocity_z = -g_velocity_z;
  g_tick++;
  char title[128];
  snprintf(title, sizeof(title), "Moving Dot 3D GUI Example | Tick: %lu", g_tick);
  glutSetWindowTitle(title);
  glutPostRedisplay();
  glutTimerFunc(16, timer, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Moving Dot 3D GUI Example");
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glPointSize(8.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, 1.0, 1.0, 10.0);
  glutDisplayFunc(display);
  glutSpecialFunc(keyboard);
  glutKeyboardFunc(keyboard_ascii);
  glutTimerFunc(0, timer, 0);
  glutMainLoop();
  return 0;
}
