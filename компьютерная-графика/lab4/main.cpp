// TODO: variant 8
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
const float PI = 3.14159265358979323846;
double angle = 0;

class Train {
private:
public:
  void drawCube(double sizes[], double position[]) {
    double baseX = sizes[0];
    double baseY = sizes[1];
    double baseZ = sizes[2];

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(position[0], position[1], position[2]);
    glVertex3f(position[0], position[1], position[2] + baseZ);
    glVertex3f(position[0] + baseX, position[1], position[2] + baseZ);
    glVertex3f(position[0] + baseX, position[1], position[2]);
    glVertex3f(position[0], position[1], position[2]);

    glVertex3f(position[0], position[1], position[2]);
    glVertex3f(position[0], position[1] + baseY, position[2]);
    glVertex3f(position[0], position[1] + baseY, position[2] + baseZ);
    glVertex3f(position[0], position[1], position[2] + baseZ);
    glVertex3f(position[0], position[1], position[2]);

    glVertex3f(position[0], position[1], position[2]);
    glVertex3f(position[0], position[1] + baseY, position[2]);
    glVertex3f(position[0] + baseX, position[1] + baseY, position[2]);
    glVertex3f(position[0] + baseX, position[1], position[2]);
    glVertex3f(position[0], position[1], position[2]);

    glVertex3f(position[0] + baseX, position[1], position[2]);
    glVertex3f(position[0] + baseX, position[1] + baseY, position[2]);
    glVertex3f(position[0] + baseX, position[1] + baseY, position[2] + baseZ);
    glVertex3f(position[0] + baseX, position[1], position[2] + baseZ);
    glVertex3f(position[0] + baseX, position[1], position[2]);

    glVertex3f(position[0], position[1], position[2] + baseZ);
    glVertex3f(position[0], position[1] + baseY, position[2] + baseZ);
    glVertex3f(position[0] + baseX, position[1] + baseY, position[2] + baseZ);
    glVertex3f(position[0] + baseX, position[1], position[2] + baseZ);
    glVertex3f(position[0], position[1], position[2] + baseZ);

    glVertex3f(position[0], position[1] + baseY, position[2]);
    glVertex3f(position[0], position[1] + baseY, position[2] + baseZ);
    glVertex3f(position[0] + baseX, position[1] + baseY, position[2] + baseZ);
    glVertex3f(position[0] + baseX, position[1] + baseY, position[2]);
    glVertex3f(position[0], position[1] + baseY, position[2]);

    glEnd();
  }

  void drawVerticalCylinder(float position[], float radius, float height,
                            int segments) {
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i) {
      float theta =
          2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
      float x = radius * cos(theta);
      float z = radius * sin(theta);

      // Bottom circle
      glVertex3f(x, 0.0f, z);
      // Top circle
      glVertex3f(x, height, z);
    }
    glEnd();

    // Draw the top and bottom circles
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // Center of bottom circle
    for (int i = 0; i <= segments; ++i) {
      float theta =
          2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
      float x = radius * cos(theta);
      float z = radius * sin(theta);

      // Bottom circle
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

      // Top circle
      glVertex3f(x, height, z);
    }
    glEnd();
    glPopMatrix();
  }

  void drawWheel(float position[], float radius, float height, int segments) {
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i) {
      float theta =
          2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
      float x = radius * cos(theta);
      float y = radius * sin(theta);

      // Bottom circle
      glVertex3f(0, y, x);
      // Top circle
      glVertex3f(height, y, x);
    }
    glEnd();

    // Draw the top and bottom circles
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // Center of bottom circle
    for (int i = 0; i <= segments; ++i) {
      float theta =
          2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
      float x = radius * cos(theta);
      float y = radius * sin(theta);

      // Bottom circle
      glVertex3f(0, y, x);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, height); // Center of top circle
    for (int i = 0; i <= segments; ++i) {
      float theta =
          2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
      float x = radius * cos(theta);
      float y = radius * sin(theta);

      // Top circle
      glVertex3f(height, y, x);
    }
    glEnd();
    glPopMatrix();
  }
  void drawHorizontalCylinder(float position[], float radius, float height,
                              int segments) {
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i) {
      float theta =
          2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
      float x = radius * cos(theta);
      float y = radius * sin(theta);

      // Bottom circle
      glVertex3f(x, y, 0.0f);
      // Top circle
      glVertex3f(x, y, height);
    }
    glEnd();

    // Draw the top and bottom circles
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f); // Center of bottom circle
    for (int i = 0; i <= segments; ++i) {
      float theta =
          2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
      float x = radius * cos(theta);
      float y = radius * sin(theta);

      // Bottom circle
      glVertex3f(x, y, 0.0f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, height); // Center of top circle
    for (int i = 0; i <= segments; ++i) {
      float theta =
          2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
      float x = radius * cos(theta);
      float y = radius * sin(theta);

      // Top circle
      glVertex3f(x, y, height);
    }
    glEnd();
    glPopMatrix();
  }


  void drawTrain() {
    drawCube(new double[]{300, 75, 900}, new double[]{100, -75, 50});
    drawCube(new double[]{500, 50, 1000}, new double[]{0, 0, 0});
    drawCube(new double[]{400, 350, 200}, new double[]{50, 50, 50});
    drawCube(new double[]{400, 225, 400}, new double[]{50, 50, 250});
    drawHorizontalCylinder(new float[]{250, 150, 650}, 125, 200, 50);
    drawVerticalCylinder(new float[]{250, 275, 750}, 50, 150, 40);
    drawHorizontalCylinder(new float[]{50, 50, 950}, 30, 80, 20);
    drawHorizontalCylinder(new float[]{450, 50, 950}, 30, 80, 20);
    drawVerticalCylinder(new float[]{50, 50, 950}, 15, 80, 20);
    drawVerticalCylinder(new float[]{450, 50, 950}, 30, 80, 20);
    drawHorizontalCylinder(new float[]{60, 150, 950}, 50, 20, 20);
    drawHorizontalCylinder(new float[]{440, 150, 950}, 50, 20, 20);
    drawWheel(new float[]{75, -60, 200}, 75, 20, 20);
    drawWheel(new float[]{400, -60, 200}, 75, 20, 20);
    drawWheel(new float[]{75, -60, 400}, 75, 20, 20);
    drawWheel(new float[]{400, -60, 400}, 75, 20, 20);
    drawWheel(new float[]{75, -60, 800}, 75, 20, 20);
    drawWheel(new float[]{400, -60, 800}, 75, 20, 20);
  }
} train;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Установка света
    glEnable(GL_LIGHTING);

    // Источник света 1
    GLfloat light_position1[] = { 100.0f, 100.0f, 100.0f, 1.0f };
    GLfloat light_color1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color1);
    glEnable(GL_LIGHT0);

    // Источник света 2
    GLfloat light_position2[] = { -100.0f, 100.0f, 100.0f, 1.0f };
    GLfloat light_color2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color2);
    glEnable(GL_LIGHT1);

    // Источник света 3
    GLfloat light_position3[] = { -100.0f, 100.0f, -100.0f, 1.0f };
    GLfloat light_color3[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT2, GL_POSITION, light_position3);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color3);
    glEnable(GL_LIGHT2);

    // Источник света 4
    GLfloat light_position4[] = { 100.0f, 100.0f, -100.0f, 1.0f };
    GLfloat light_color4[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT3, GL_POSITION, light_position4);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_color4);
    glEnable(GL_LIGHT3);

    // Источник света 5
    GLfloat light_position5[] = { 0.0f, -100.0f, 0.0f, 1.0f };
    GLfloat light_color5[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT4, GL_POSITION, light_position5);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light_color5);
    glEnable(GL_LIGHT4);
}

void menu(int value) {
    switch (value) {
    case 1:
        glEnable(GL_LIGHT0);
        break;
    case 2:
        glDisable(GL_LIGHT0);
        break;
    case 3:
        glEnable(GL_LIGHT1);
        break;
    case 4:
        glDisable(GL_LIGHT1);
        break;
    case 5:
        glEnable(GL_LIGHT2);
        break;
    case 6:
        glDisable(GL_LIGHT2);
        break;
    case 7:
        glEnable(GL_LIGHT3);
        break;
    case 8:
        glDisable(GL_LIGHT3);
        break;
    case 9:
        glEnable(GL_LIGHT4);
        break;
    case 10:
        glDisable(GL_LIGHT4);
        break;
    }
    glutPostRedisplay();
} // МЕНЮШКА

void createMenu() {
    int menu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Enable Light 1", 1);
    glutAddMenuEntry("Disable Light 1", 2);
    glutAddMenuEntry("Enable Light 2", 3);
    glutAddMenuEntry("Disable Light 2", 4);
    glutAddMenuEntry("Enable Light 3", 5);
    glutAddMenuEntry("Disable Light 3", 6);
    glutAddMenuEntry("Enable Light 4", 7);
    glutAddMenuEntry("Disable Light 4", 8);
    glutAddMenuEntry("Enable Light 5", 9);
    glutAddMenuEntry("Disable Light 5", 10);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    // Set up the view
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    train.drawTrain();
    // Draw the train
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);    // Red color
    glTranslatef(0.0, 0.0, 0.0); // Translate to desired position
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspectRatio = (float)w / (float)h;

    // Set up the perspective projection
    float distanceToObject = 2000;
    float fov = 60.0f;                        // Field of view in degrees
    float nearPlane = 1000.0f;                // Near clipping plane distance
    float farPlane = distanceToObject + 2000; // Far clipping plane distance

    gluPerspective(fov, aspectRatio, nearPlane, farPlane);
    gluLookAt(0.0f, 0.0f, distanceToObject, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void spinView(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        angle += 5.0f;
        break;
    case GLUT_KEY_RIGHT:
        angle -= 5.0f;
        break;
    }
    glutPostRedisplay(); // Mark the current window as needing to be redisplayed
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(100, 100);
    glutCreateWindow("3D Train");
    init();
    createMenu();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(spinView);
    glutMainLoop();
    return 0;
}
