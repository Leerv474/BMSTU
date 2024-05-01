#include <GL/freeglut_std.h>
#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "GL/freeglut.h"
#include "stb_image.h"
#include <math.h>
// Rotation amounts
static GLfloat zPos = -60.0f;
static GLfloat xPos = 0;
unsigned int texture[3];
void ProcessMenu(int value) {
  GLint iLoop;
  for (iLoop = 0; iLoop < 3; iLoop++) {
    glBindTexture(GL_TEXTURE_2D, texture[iLoop]);
    switch (value) {
    case 0:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      break;
    case 1:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      break;
    case 2:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                      GL_NEAREST_MIPMAP_NEAREST);
      break;
    case 3:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                      GL_NEAREST_MIPMAP_LINEAR);
      break;
    case 4:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                      GL_LINEAR_MIPMAP_NEAREST);
      break;
    case 5:
    default:
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                      GL_LINEAR_MIPMAP_LINEAR);
      break;
    }
  }
  glutPostRedisplay();
}
void SetupRC() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // разрешаем наложение текстуры
  glEnable(GL_TEXTURE_2D);
  // функции преобразования цветов источника света, цвета образа текстуры,
  // цвета вершин примитивов и цвета конфигурации текстуры для получения
  // поверхности с наложенной на нее текстурой
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  int width, height, cnt;
  // генерируем 3 текстуры
  glGenTextures(3, texture);
  // flooring
  unsigned char *data1 = stbi_load("floor.jpg", &width, &height, &cnt, 0);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  // создает все изображения MIP-карты
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB,
                    GL_UNSIGNED_BYTE, data1);
  // задаем параметры
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // теперь активных текстур 0
  glBindTexture(GL_TEXTURE_2D, 0);
  // освобождаем память
  stbi_image_free(data1);
  // walls
  unsigned char *data2 = stbi_load("wall.jpg", &width, &height, &cnt, 0);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB,
                    GL_UNSIGNED_BYTE, data2);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data2);
  // ceiling
  unsigned char *data3 = stbi_load("ceiling.jpg", &width, &height, &cnt, 0);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB,
                    GL_UNSIGNED_BYTE, data3);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data3);
}
void SpecialKeys(int key, int x, int y) {
  if (key == GLUT_KEY_UP)
    zPos += 1.0f;
  if (key == GLUT_KEY_DOWN)
    zPos -= 1.0f;
  if (key == GLUT_KEY_RIGHT)
    xPos -= 1.0f;
  if (key == GLUT_KEY_LEFT)
    xPos += 1.0f;
  // Refresh the Window
  glutPostRedisplay();
}
void ChangeSize(int w, int h) {
  GLfloat fAspect;
  // Prevent a divide by zero
  if (h == 0)
    h = 1;
  // Set Viewport to window dimensions
  glViewport(0, 0, w, h);
  fAspect = (GLfloat)w / (GLfloat)h;
  // Reset coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // Produce the perspective projection
  gluPerspective(90.0f, fAspect, 1, 120);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
void RenderScene(void) {
  GLfloat z;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glTranslatef(xPos, 0.0f, zPos);
  // пол
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glBegin(GL_TRIANGLE_FAN);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(20.0f, -10.0f, -20);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(20.0f, -10.0f, 20);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-20.0f, -10.0f, 20.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-20.0f, -10.0f, -20.0f);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.0f, -10.0f, -40.0f);
  glEnd();

  // потолок
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glBegin(GL_TRIANGLE_FAN);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(20.0f, 10.0f, -20);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(20.0f, 10.0f, 20);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-20.0f, 10.0f, 20.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-20.0f, 10.0f, -20.0f);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.0f, 10.0f, -40.0f);
  glEnd();

  glEnable(GL_DEPTH_TEST);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  // front wall left
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-20, 10.0f, -20);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.0f, 10.0f, -40.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0, -10.0f, -40.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-20, -10.0f, -20);
  glEnd();
  // front wall right
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(20, 10.0f, -20);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.0f, 10.0f, -40.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0, -10.0f, -40.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(20, -10.0f, -20);
  glEnd();
  // правая стена
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(20.0f, 10.0f, 20);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(20.0f, 10.0f, -20);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(20.0f, -10.0f, -20);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(20.0f, -10.0f, 20);
  glEnd();

  // левая стена
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-20.0f, -10.0f, 20);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-20.0f, -10.0f, -20.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-20.0f, 10.0f, -20.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-20.0f, 10.0f, 20);
  glEnd();
  // back wall
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(20, 10.0f, 20);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-20.0f, 10.0f, 20.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-20, -10.0f, 20.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(20, -10.0f, 20);
  glEnd();


  glPopMatrix();
  glutSwapBuffers();
}
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Tunnel");
  glutReshapeFunc(ChangeSize);
  glutSpecialFunc(SpecialKeys);
  glutDisplayFunc(RenderScene);
  // настройки меню
  glutCreateMenu(ProcessMenu);
  glutAddMenuEntry("GL_NEAREST", 0);
  glutAddMenuEntry("GL_LINEAR", 1);
  glutAddMenuEntry("GL_NEAREST_MIPMAP_NEAREST", 2);
  glutAddMenuEntry("GL_NEAREST_MIPMAP_LINEAR", 3);
  glutAddMenuEntry("GL_LINEAR_MIPMAP_NEAREST", 4);
  glutAddMenuEntry("GL_LINEAR_MIPMAP_LINEAR", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  SetupRC();
  glutMainLoop();
  return 0;
}
