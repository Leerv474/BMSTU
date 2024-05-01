#include <GL/freeglut_std.h>
#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <cstring>
#include <vector>

unsigned int texture;
float angle = 0;
std::vector<GLfloat> texCoords;
void display() {

  float radius = 2;
  float height = 4;
  float segments = 50;
  const float PI = 3.141592;
  float position[] = {0, -2, 0};
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glBindTexture(GL_TEXTURE_2D, texture);
  glColor3f(1, 1, 1);
  glPushMatrix();
  glTranslatef(position[0], position[1], position[2]);


  // Draw the top and bottom circles
  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0f, 0.0f, 0.0f); // Center of bottom circle
  for (int i = 0; i <= segments; ++i) {
    float theta =
        2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
    float x = radius * cos(theta);
    float z = radius * sin(theta);
    float s = static_cast<float>(i) /
              static_cast<float>(
                  segments); // Calculate texture coordinate in the S direction

    // Bottom circle
    glTexCoord2f(s, 0.0f);
    glVertex3f(x, 0.0f, z);
  }
  glEnd();

  glBegin(GL_TRIANGLE_FAN);
  glVertex3f(0.0f, height, 0.0f); // Center of top circle
  for (int i = 0; i <= segments; ++i) {
    float theta =
        2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
    float x = radius * cos(theta);
    float z = radius * sin(theta);
    float s = static_cast<float>(i) /
              static_cast<float>(
                  segments); // Calculate texture coordinate in the S direction

    // Top circle
    glTexCoord2f(s, 1.0f);
    glVertex3f(x, height, z);
  }
  glEnd();


  glBegin(GL_QUAD_STRIP);
  for (int i = 0; i <= segments; ++i) {
    float theta =
        2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
    float x = radius * cos(theta);
    float z = radius * sin(theta);
    float s = static_cast<float>(i) /
              static_cast<float>(
                  segments); // Calculate texture coordinate in the S direction

    // Bottom circle
    glTexCoord2f(s, 0.0f);
    glVertex3f(x, 0.0f, z);
    // Top circle
    glTexCoord2f(s, 1.0f);
    glVertex3f(x, height, z);
  }
  glEnd();

  glPopMatrix();

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glutSwapBuffers();
}
void Game_Init() {
  int width, height, cnt;
  // загрузим данные картинки
  unsigned char *data = stbi_load("1.jpg", &width, &height, &cnt, 0);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
               cnt == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(data);
}
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspectRatio = (float)w / (float)h;

  // Set up the perspective projection
  float distanceToObject = 10;
  float fov = 60.0f;                       // Field of view in degrees
  float nearPlane = 1.0f;                  // Near clipping plane distance
  float farPlane = distanceToObject + 100; // Far clipping plane distance

  gluPerspective(fov, aspectRatio, nearPlane, farPlane);
  gluLookAt(0.0f, 0.0f, distanceToObject, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}
void spinView(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_LEFT:
    angle += .5f;
    break;
  case GLUT_KEY_RIGHT:
    angle -= .5f;
    break;
  }
  glutPostRedisplay(); // Mark the current window as needing to be redisplayed
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Текстура-файл");
  glutInitWindowSize(500, 500);
  Game_Init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutSpecialFunc(spinView);
  glutMainLoop();
  return 0;
}
