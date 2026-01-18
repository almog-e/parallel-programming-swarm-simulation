#include <GL/glut.h>

float g_pos_x = -0.9f;
float g_pos_y = 0.0f;
float g_velocity = 0.01f;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.2f, 0.8f, 0.2f);
  glBegin(GL_POINTS);
  glVertex2f(g_pos_x, g_pos_y);
  glEnd();
  glFlush();
}

void timer(int value) {
  g_pos_x += g_velocity;
  if (g_pos_x > 0.9f || g_pos_x < -0.9f) {
    g_velocity = -g_velocity;
  }
  glutPostRedisplay();
  glutTimerFunc(16, timer, 0);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Moving Dot GUI Example");
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glPointSize(8.0f);
  glutDisplayFunc(display);
  glutTimerFunc(0, timer, 0);
  glutMainLoop();
  return 0;
}
