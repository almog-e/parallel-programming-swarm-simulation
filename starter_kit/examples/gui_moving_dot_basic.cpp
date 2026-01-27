// Modular Moving Dot Example
// Build: g++ -o gui_moving_dot_basic gui_moving_dot_basic.cpp ../gui/gui_utils.cpp ../collid/collision.cpp -I../gui -I../collid -lGL -lGLU -lglut
// Run:   ./gui_moving_dot_basic

#include "gui_utils.h"
#include "collision.h"
#include <cmath>
#include <cstdio>

// Simulation tick counter
unsigned long g_tick = 0;

#define NUM_DOTS 5
struct Dot {
  float x, y, z;
  float vx, vy, vz;
};
Dot dots[NUM_DOTS];

// Camera globals required by gui_utils
float g_cam_angle_yaw = 0.0f;
float g_cam_angle_pitch = 0.0f;
float g_cam_radius = 2.0f;

void initDots() {
  for (int i = 0; i < NUM_DOTS; ++i) {
    dots[i].x = -0.8f + 1.6f * (float)rand() / RAND_MAX;
    dots[i].y = 0.0f;
    dots[i].z = -0.8f + 1.6f * (float)rand() / RAND_MAX;
    float angle = 2.0f * 3.1415926f * (float)rand() / RAND_MAX;
    float speed = 0.005f + 0.015f * (float)rand() / RAND_MAX;
    dots[i].vx = speed * cosf(angle);
    dots[i].vy = 0.0f;
    dots[i].vz = speed * sinf(angle);
  }
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  setCamera(0.0f, 0.0f, 0.0f);
  drawAxes(1.5f);
  drawGrid3D(-1.5f, 1.5f, 0.3f);
  for (int i = 0; i < NUM_DOTS; ++i) {
    float r = 0.2f + 0.7f * (i % 2);
    float g = 0.8f * ((i+1) % 2);
    float b = 0.2f + 0.7f * ((i+2) % 3 == 0);
    drawDotWithLabel(dots[i].x, dots[i].y, dots[i].z, i, r, g, b, 8.0f);
  }
  glFlush();
}

void timer(int value) {
  // Move all dots
  for (int i = 0; i < NUM_DOTS; ++i) {
    dots[i].x += dots[i].vx;
    dots[i].y += dots[i].vy;
    dots[i].z += dots[i].vz;
    if (dots[i].x > 0.9f || dots[i].x < -0.9f) dots[i].vx = -dots[i].vx;
    if (dots[i].y > 0.9f || dots[i].y < -0.9f) dots[i].vy = -dots[i].vy;
    if (dots[i].z > 0.9f || dots[i].z < -0.9f) dots[i].vz = -dots[i].vz;
  }
  // Collision check
  float min_dist = 0.15f;
  for (int i = 0; i < NUM_DOTS; ++i) {
    for (int j = i + 1; j < NUM_DOTS; ++j) {
      if (check_collision(dots[i].x, dots[i].y, dots[i].z, dots[j].x, dots[j].y, dots[j].z, min_dist)) {
        float dx = dots[j].x - dots[i].x;
        float dy = dots[j].y - dots[i].y;
        float dz = dots[j].z - dots[i].z;
        float dist = std::sqrt(dx*dx + dy*dy + dz*dz);
        float overlap = collision_overlap(dots[i].x, dots[i].y, dots[i].z, dots[j].x, dots[j].y, dots[j].z, min_dist);
        float nx = dx / dist;
        float ny = dy / dist;
        float nz = dz / dist;
        float push = 0.5f * overlap;
        dots[i].x -= nx * push;
        dots[i].y -= ny * push;
        dots[i].z -= nz * push;
        dots[j].x += nx * push;
        dots[j].y += ny * push;
        dots[j].z += nz * push;
        // Swap velocities for bounce effect
        float tmpx = dots[i].vx, tmpy = dots[i].vy, tmpz = dots[i].vz;
        dots[i].vx = dots[j].vx;
        dots[i].vy = dots[j].vy;
        dots[i].vz = dots[j].vz;
        dots[j].vx = tmpx;
        dots[j].vy = tmpy;
        dots[j].vz = tmpz;
      }
    }
  }
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
  initDots();
  glutDisplayFunc(display);
  glutSpecialFunc(keyboard);
  glutKeyboardFunc(keyboard_ascii);
  glutTimerFunc(0, timer, 0);
  glutMainLoop();
  return 0;
}
