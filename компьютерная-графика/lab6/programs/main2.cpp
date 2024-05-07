#include "GL/freeglut.h"
#include "tga.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <random>

GLint Gw = 1600;
GLint Gh = 900;

std::vector<std::uint8_t> randomPixels(Tga image) {
  std::vector<std::uint8_t> newPixels(image.GetPixels());
  std::random_device rd;
  std::default_random_engine rng(rd());

  // Shuffle the elements
  std::shuffle(newPixels.begin(), newPixels.end(), rng);
  return newPixels;
}

void display(void) {
  glClearColor(1, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  Tga image = Tga("image.tga");
  for (int i = 0; i < 2; i++) {
    glRasterPos2i(160 + image.GetWidth() * i, 0);
    glDrawPixels(image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE,
                 randomPixels(image).data());
  }
  glRasterPos2i(160, 474);
  glDrawPixels(image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE,
               image.GetPixels().data());
  glRasterPos2i(160 + image.GetWidth(), 474);
  glDrawPixels(image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE,
               randomPixels(image).data());
  glutSwapBuffers();
}

void ChangeSize(int w, int h) {
  if (h == 0)
    h = 1;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  gluOrtho2D(0, (GLfloat)w, 0, (GLfloat)h);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  Gw = w;
  Gh = h;
}

int main(int argc, char *argv[]) {
  srand(time(0));
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(Gw, Gh);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Task 2");
  glutReshapeFunc(ChangeSize);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
