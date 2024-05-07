#include "GL/freeglut.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include "tga.h"

GLint Gw = 1000;
GLint Gh = 1000;

GLfloat randomValue() {
	return ((GLfloat)(rand() % 11)) * 0.1f;
}

void display(void) {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	Tga image = Tga("image.tga");
	glRasterPos2i(480, 237);
	glDrawPixels(image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetPixels().data());
	glutSwapBuffers();
}

void ChangeSize(int w, int h) {
	if (h == 0) h = 1;
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

void ProcessMenu(int value) {
	switch (value) {
	case 0:
		glPixelTransferf(GL_RED_SCALE, 1.0f);
		glPixelTransferf(GL_GREEN_SCALE, 0.0f);
		glPixelTransferf(GL_BLUE_SCALE, 0.0f);
		break;
	case 1:
		glPixelTransferf(GL_RED_SCALE, 0.0f);
		glPixelTransferf(GL_GREEN_SCALE, 1.0f);
		glPixelTransferf(GL_BLUE_SCALE, 0.0f);
		break;
	case 2:
		glPixelTransferf(GL_RED_SCALE, 0.0f);
		glPixelTransferf(GL_GREEN_SCALE, 0.0f);
		glPixelTransferf(GL_BLUE_SCALE, 1.0f);
		break;
	default:
		glPixelTransferf(GL_RED_SCALE, randomValue());
		glPixelTransferf(GL_GREEN_SCALE, randomValue());
		glPixelTransferf(GL_BLUE_SCALE, randomValue());
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	srand(time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(Gw, Gh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Task 3");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(display);
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Just red", 0);
	glutAddMenuEntry("Just green", 1);
	glutAddMenuEntry("Just blue", 2);
	glutAddMenuEntry("Random", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
