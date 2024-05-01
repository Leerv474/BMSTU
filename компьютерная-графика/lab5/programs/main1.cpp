#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/freeglut_std.h>
#include <cstring>
#include <iostream>

unsigned int texture;
// зададим массив коордтнат квадрата
float vertex[] = {-1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
// масив который хранит текстурные координаты для каждой вершины
float texCoord[] = {0, 0, 1, 0, 1, 1, 0, 1};
// процедура для создания квадрата и
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  // Активные цвета текстуры
  glColor3f(1, 1, 1);
  glPushMatrix();
  // Установка состояние для OpenGL, означающее, что мы будем использовать
  glEnableClientState(GL_VERTEX_ARRAY);
  // Установка состояние для OpenGL, означающее, что мы будем использовать
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  // Установка массива вершинных координат квадрата
  glVertexPointer(3, GL_FLOAT, 0, vertex);
  // Установка массива текстурных координат
  glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
  // Выводит примитивы по данным в массиве для квадрата
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glPopMatrix();
  glutSwapBuffers();
}
void Text_Init() {
  // процедура для создания текстуры
  int width, height;
  width = 2;
  height = 2;
  // создаем двумерный массив 2 на 2 текселя
  struct {
    unsigned char r, g, b, a;
  } data[2][2];
  memset(data, 0, sizeof(data));
  // задаем цвет для каждого текселя структуры
  data[0][0].r = 100;
  data[0][0].b = 200;
  data[1][0].g = 155;
  data[0][1].g = 155;
  data[1][1].r = 100;
  data[1][1].b = 200;
  // Создадим имена текстур. 1-количество текстур.
  glGenTextures(1, &texture);
  // выбирает указанную текстуру как активную для наложения ее на объекты. После
  glBindTexture(GL_TEXTURE_2D, texture);
  // Основные настройки текстуры
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  // Отключаем активную текстуру
  glBindTexture(GL_TEXTURE_2D, 0);
}
void processMenu(int value) {
  switch (value) {
  case 0:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Handle menu option 0
    break;
  case 1:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Handle menu option 1
    break;
    // Add more cases for other menu items as needed
  }
  glutPostRedisplay();
}
void createMenu() {
  int menu = glutCreateMenu(processMenu);
  glutAddMenuEntry("Option 1", 0);
  glutAddMenuEntry("Option 2", 1);
  // Add more menu items as needed
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Текстура-квадраты");
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  Text_Init();
  createMenu();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
