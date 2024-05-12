#include "GL/freeglut.h"
#include <iostream>

GLubyte first[32] = {0xff, 0xff, 
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x3,  0xc0,
    0x7,  0xe0,
    0xf,  0xf0,
    0x1f, 0xf8,
    0x1f,  0xf8,
    0x1f, 0xf8,
    0x1f, 0xf8,
    0xe,  0x78,
    0xc, 0x30,
    
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00};

GLubyte second[32] = {
    0x00, 0x00,

    0x0, 0x80,
    0x0, 0x80,
    0x1, 0xc0,
    0x1, 0xc0,
    0x1, 0xc0,
    0x3, 0xe0,
    0x1f, 0xfc,
    0x7f, 0xff,
    0x1f, 0xfc,
    0x3, 0xe0,
    0x1, 0xc0,
    0x1, 0xc0,
    0x1, 0xc0,
    0x0, 0x80,
    0x0, 0x80,
};

GLfloat randomValue() { return ((GLfloat)(rand() % 11)) * 0.1f; }

void filling(int x, int y, int size, float range) {
  int sizesAmount = (int)range / 16;
  for (int j = 0; j < sizesAmount; j++) {
    glColor3d(randomValue(), randomValue(), randomValue());
    if (j + 1 < (sizesAmount / 2) + 1) {
      glRasterPos2i(x - (0.5 + 1 + j) * size, y);
      glBitmap(size, size, 0.0, 0.0, 0.0, 0.0, first);
      continue;
    }
    if (j + 1 == (sizesAmount / 2) + 1) {
      glRasterPos2i(x - 0.5 * size, y);
      glBitmap(size, size, 0.0, 0.0, 0.0, 0.0, first);
      continue;
    }
    glRasterPos2i(x + (sizesAmount - j - 0.5) * size, y);
    glBitmap(size, size, 0.0, 0.0, 0.0, 0.0, first);
  }
}

void SetupRC() { glClearColor(0.0f, 0.0f, 0.0f, 0.0f); }

void ChangeSize(int w, int h) {
  if (h == 0)
    h = 1;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(10, (GLfloat)w, 0.0f, (GLfloat)h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void RenderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glColor3f(1.0f, 1.0f, 1.0f);
  float x = 248, y = 136, size = 16, range = 16;
  for (int i = 0; i < 15; i++) {
    if (i == 0 || i == 14) {
      glRasterPos2i(x - size / 2, y);
      glBitmap(size, size, 0.0, 0.0, 0.0, 0.0, second);
      y += size;
      continue;
    }
    filling(x, y, size, range);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(x - range / 2 - size, y);
    glBitmap(size, size, 0.0, 0.0, 0.0, 0.0, second);
    glRasterPos2i(x + range / 2, y);
    glBitmap(size, size, 0.0, 0.0, 0.0, 0.0, second);
    y += size;
    if (i < 7) {
      range += 2 * size;
      continue;
    }
    range -= 2 * size;
  }
  glutSwapBuffers();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(512, 512);
  glutCreateWindow("Task 1");
  glutReshapeFunc(ChangeSize);
  glutDisplayFunc(RenderScene);
  SetupRC();
  glutMainLoop();
  return 0;
}
