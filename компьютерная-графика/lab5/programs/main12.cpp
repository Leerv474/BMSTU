#include "GL/freeglut.h"
#include "GL/gl.h"
#include <GL/freeglut_std.h>
#include <cstring>
#include <iostream>

const int texturesNum = 4;
unsigned int textures[texturesNum];

// зададим массив коордтнат квадрата
float vertex[][12] = {{-2, -2, 0, -2, 0, 0, 0, 0, 0, 0, -2, 0},
                      {0, 0, 0, 0, 2, 0, 2, 2, 0, 2, 0, 0},
                      {0, 0, 0, 2, 0, 0, 2, -2, 0, 0, -2, 0},
                      {0, 0, 0, -2, 0, 0, -2, 2, 0, 0, 2, 0}};
// масив который хранит текстурные координаты для каждой вершины
float texCoord[] = {0, 0, 2, 0, 2, 2, 0, 2};
// процедура для создания квадрата и
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  for (int i = 0; i < texturesNum; i++) {
    glBindTexture(GL_TEXTURE_2D, textures[i]);
    // Активные цвета текстуры
    glColor3f(1, 1, 1);
    glPushMatrix();
    // Установка состояние для OpenGL, означающее, что мы будем использовать
    glEnableClientState(GL_VERTEX_ARRAY);
    // Установка состояние для OpenGL, означающее, что мы будем использовать
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    // Установка массива вершинных координат квадрата
    glVertexPointer(3, GL_FLOAT, 0, vertex[i]);
    // Установка массива текстурных координат
    glTexCoordPointer(2, GL_FLOAT, 0, texCoord);
    // Выводит примитивы по данным в массиве для квадрата
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();
  }
  glutSwapBuffers();
}
void Text_Init() {
  // процедура для создания текстуры
  int width, height;
  width = 2;
  height = 2;
  // создаем двумерный массив 2 на 2 текселя
  char data[][4] = {{50, 100, 50}, {120, 80, 30}, {60, 70, 90}, {90, 50, 20}};
  // задаем цвет для каждого текселя структуры
  // Color variation 1
  // Создадим имена текстур. 1-количество текстур.
  glGenTextures(4, textures);
  // выбирает указанную текстуру как активную для наложения ее на объекты. После
  for (int i = 0; i < texturesNum; i++) {
    glBindTexture(GL_TEXTURE_2D, textures[i]);
    // Основные настройки текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data[i]);
    // Отключаем активную текстуру
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Текстура-квадраты");
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  Text_Init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
