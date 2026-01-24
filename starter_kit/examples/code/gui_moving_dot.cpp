
#include <GL/glut.h>
#include <cmath>
#include <cstdio>

// Simulation tick counter
unsigned long g_tick = 0;

// Draws a 3D grid (cube) with lines along X, Y, and Z
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


// Camera rotation angles
float g_cam_angle_yaw = 0.0f;   // left/right
float g_cam_angle_pitch = 0.0f; // up/down

float g_pos_x = -0.9f;
// Camera rotation angles and zoom
float g_cam_radius = 2.0f; // zoom (distance from center)
float g_pos_y = 0.0f;
float g_pos_z = 0.0f;
float g_velocity_x = 0.01f;
float g_velocity_y = 0.008f;
float g_velocity_z = 0.012f;

void keyboard(int key, int x, int y)
{
  float angle_step = 5.0f;
  switch (key)
  {
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
void keyboard_ascii(unsigned char key, int x, int y)
{
  switch (key)
  {
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

void setCamera(float centerX, float centerY, float centerZ)
{
  float yaw_rad = g_cam_angle_yaw * 3.1415926f / 180.0f;
  float pitch_rad = g_cam_angle_pitch * 3.1415926f / 180.0f;
  float cam_x = g_cam_radius * cosf(pitch_rad) * sinf(yaw_rad);
  float cam_y = g_cam_radius * sinf(pitch_rad);
  float cam_z = g_cam_radius * cosf(pitch_rad) * cosf(yaw_rad);
  gluLookAt(cam_x, cam_y, cam_z, centerX, centerY, centerZ, 0.0, 1.0, 0.0);
}

void drawGrid(float grid_min, float grid_max, float grid_step, float z)
{
  glColor3f(0.91f, 0.91f, 0.91f);
  glLineWidth(0.01f);
  glBegin(GL_LINES);
  for (float x = grid_min; x <= grid_max; x += grid_step)
  {
    glVertex3f(x, grid_min, z);
    glVertex3f(x, grid_max, z);
  }
  for (float y = grid_min; y <= grid_max; y += grid_step)
  {
    glVertex3f(grid_min, y, z);
    glVertex3f(grid_max, y, z);
  }
  glEnd();
}

void drawAxes(float length)
{
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

  // Arrowheads
  glLineWidth(2.0f);
  glBegin(GL_LINES);
  // X
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(length, 0.0f, 0.0f);
  glVertex3f(length - 0.15f, 0.08f, 0.0f);
  glVertex3f(length, 0.0f, 0.0f);
  glVertex3f(length - 0.15f, -0.08f, 0.0f);
  // Y
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, length, 0.0f);
  glVertex3f(0.08f, length - 0.15f, 0.0f);
  glVertex3f(0.0f, length, 0.0f);
  glVertex3f(-0.08f, length - 0.15f, 0.0f);
  // Z
  glColor3f(0.0f, 0.6f, 1.0f);
  glVertex3f(0.0f, 0.0f, length);
  glVertex3f(0.0f, 0.08f, length - 0.15f);
  glVertex3f(0.0f, 0.0f, length);
  glVertex3f(0.0f, -0.08f, length - 0.15f);
  glEnd();

  // Labels
  glColor3f(1.0f, 0.0f, 0.0f);
  glRasterPos3f(length + 0.1f, 0.0f, 0.0f);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');
  glColor3f(0.0f, 1.0f, 0.0f);
  glRasterPos3f(0.0f, length + 0.1f, 0.0f);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');
  glColor3f(0.0f, 0.6f, 1.0f);
  glRasterPos3f(0.0f, 0.0f, length + 0.1f);
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Z');
}

void drawDot(float x, float y, float z, float r, float g, float b, float size)
{
  glColor3f(r, g, b);
  glPointSize(size);
  glBegin(GL_POINTS);
  glVertex3f(x, y, z);
  glEnd();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  setCamera(0.0f, 0.0f, 0.0f);
  drawAxes(1.5f);
  drawGrid3D(-1.5f, 1.5f, 0.3f);

  drawDot(g_pos_x, g_pos_y, g_pos_z, 0.2f, 0.8f, 0.2f, 8.0f);
  glFlush();
}
void timer(int value)
{
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
  // Update window title with tick count
  char title[128];
  snprintf(title, sizeof(title), "Moving Dot 3D GUI Example | Tick: %lu", g_tick);
  glutSetWindowTitle(title);
  glutPostRedisplay();
  glutTimerFunc(16, timer, 0);
}

int main(int argc, char **argv)
{
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
