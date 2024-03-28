//TODO: variant 8
#include <GL/freeglut.h>
#include <iostream>

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void drawTrain() {
    // Draw train components here
    // Example: Draw a cube as the body of the train
    glutSolidCube(1.0);

    // Example: Draw wheels
    glTranslatef(-0.5, -0.5, -0.5);
    glutSolidSphere(0.2, 20, 20);
    glTranslatef(1.0, 0.0, 0.0);
    glutSolidSphere(0.2, 20, 20);
    glTranslatef(0.0, 0.0, 1.0);
    glutSolidSphere(0.2, 20, 20);
    glTranslatef(-1.0, 0.0, 0.0);
    glutSolidSphere(0.2, 20, 20);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up the view
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Draw the train
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0); // Red color
    glTranslatef(0.0, 0.0, 0.0); // Translate to desired position
    drawTrain();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Train");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

