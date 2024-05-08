#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
// Глобальные переменные
GLfloat fLowLight[4] = {0.25, 0.25, 0.25, 1.0}; // Цвет тумана
// Коды и координаты источников света
GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightPos[] = {-75.0f, 150.0f, -50.0f, 0.0f};
GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
typedef GLfloat GLTVector3[3];
typedef GLfloat GLTVector2[2]; // Двукомпонентный вектор с плавающей запятой
typedef GLfloat GLTVector3[3]; // Трехомпонентный вектор с плавающей запятой
typedef GLfloat
    GLTVector4[4]; // Четырехкомпонентный вектор с плавающей //запятой
typedef GLfloat
    GLTMatrix[16]; // Основноц столбец матрицы 4х4 с плавающей //запятой
// Матрица преобразования, дающая проекцию тени
GLTMatrix shadowMat;

// Масштабирование скалярного вектора
void gltScaleVector(GLTVector3 vVector, const GLfloat fScale) {
  vVector[0] *= fScale;
  vVector[1] *= fScale;
  vVector[2] *= fScale;
}

// Возвращает длину вектора в квадрате
GLfloat gltGetVectorLengthSqrd(const GLTVector3 vVector) {
  return (vVector[0] * vVector[0]) + (vVector[1] * vVector[1]) +
         (vVector[2] * vVector[2]);
}

// Возвращает длину вектора
GLfloat gltGetVectorLength(const GLTVector3 vVector) {
  return (GLfloat)sqrt(gltGetVectorLengthSqrd(vVector));
}

// Вычитание одного вектора из другого
void gltSubtractVectors(const GLTVector3 vFirst, const GLTVector3 vSecond,
                        GLTVector3 vResult) {
  vResult[0] = vFirst[0] - vSecond[0];
  vResult[1] = vFirst[1] - vSecond[1];
  vResult[2] = vFirst[2] - vSecond[2];
}

// Вычислить векторное произведение двух векторов
void gltVectorCrossProduct(const GLTVector3 vU, const GLTVector3 vV,
                           GLTVector3 vResult) {
  vResult[0] = vU[1] * vV[2] - vV[1] * vU[2];
  vResult[1] = -vU[0] * vV[2] + vV[0] * vU[2];
  vResult[2] = vU[0] * vV[1] - vV[0] * vU[1];
}

// Масштабирование вектора по длине - создание единичсного вектора
void gltNormalizeVector(GLTVector3 vNormal) {
  GLfloat fLength = 1.0f / gltGetVectorLength(vNormal);
  gltScaleVector(vNormal, fLength);
}

// Три точки на плоскости расположены против часовой стрелки, вычисление
// нормали

void gltGetNormalVector(const GLTVector3 vP1, const GLTVector3 vP2,
                        const GLTVector3 vP3, GLTVector3 vNormal) {
  GLTVector3 vV1, vV2;
  gltSubtractVectors(vP2, vP1, vV1);
  gltSubtractVectors(vP3, vP1, vV2);
  gltVectorCrossProduct(vV1, vV2, vNormal);
  gltNormalizeVector(vNormal);
}

// Полученные три коэффициента уравнения плоскости дают три точки на поверхности
void gltGetPlaneEquation(GLTVector3 vPoint1, GLTVector3 vPoint2,
                         GLTVector3 vPoint3, GLTVector3 vPlane) {
  // Получение нормали из трех точек. Нормаль – первые три коэффициента
  // уравнения плоскости
  gltGetNormalVector(vPoint1, vPoint2, vPoint3, vPlane);
  // Итоговый коэффициент находится обратной подстановкой
  vPlane[3] = -(vPlane[0] * vPoint3[0] + vPlane[1] * vPoint3[1] +
                vPlane[2] * vPoint3[2]);
}

// Создание матрицы теневой проекции из коэффициентов уравнения плоскости и //
// положениесвета.Возвращаемое значение хранится в
void gltMakeShadowMatrix(GLTVector3 vPoints[3], GLTVector4 vLightPos,
                         GLTMatrix destMat) {
  GLTVector4 vPlaneEquation;
  GLfloat dot;
  gltGetPlaneEquation(vPoints[0], vPoints[1], vPoints[2], vPlaneEquation);
  // Скалярное произведение положение конуса и света
  dot = vPlaneEquation[0] * vLightPos[0] + vPlaneEquation[1] * vLightPos[1] +
        vPlaneEquation[2] * vLightPos[2] + vPlaneEquation[3] * vLightPos[3];
  // Проецируем
  // Первый столбец
  destMat[0] = dot - vLightPos[0] * vPlaneEquation[0];
  destMat[4] = 0.0f - vLightPos[0] * vPlaneEquation[1];
  destMat[8] = 0.0f - vLightPos[0] * vPlaneEquation[2];
  destMat[12] = 0.0f - vLightPos[0] * vPlaneEquation[3];
  // Второй столбец
  destMat[1] = 0.0f - vLightPos[1] * vPlaneEquation[0];
  destMat[5] = dot - vLightPos[1] * vPlaneEquation[1];
  destMat[9] = 0.0f - vLightPos[1] * vPlaneEquation[2];
  destMat[13] = 0.0f - vLightPos[1] * vPlaneEquation[3];
  // Третий столбец
  destMat[2] = 0.0f - vLightPos[2] * vPlaneEquation[0];
  destMat[6] = 0.0f - vLightPos[2] * vPlaneEquation[1];
  destMat[10] = dot - vLightPos[2] * vPlaneEquation[2];
  destMat[14] = 0.0f - vLightPos[2] * vPlaneEquation[3];
  // Четвертый столбец
  destMat[3] = 0.0f - vLightPos[3] * vPlaneEquation[0];
  destMat[7] = 0.0f - vLightPos[3] * vPlaneEquation[1];
  destMat[11] = 0.0f - vLightPos[3] * vPlaneEquation[2];
  destMat[15] = dot - vLightPos[3] * vPlaneEquation[3];
}

////////////////////////////////////////////////
// Функция, специально прорисовывающая конус
void DrawTeapot(int nShadow) {
  if (nShadow == 0)
    glColor3ub(255, 0, 255);
  else
    glColor3ub(0, 0, 0);
  glScalef(30.0, 30.0, 30.0);
  glPushMatrix();
  glutSolidTeapot(1.0f);
  glPopMatrix();
}

void RenderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBegin(GL_QUADS);
  glColor3ub(0, 0, 80);
  glVertex3f(400.0f, -150.0f, -200.0f);
  glVertex3f(-400.0f, -150.0f, -200.0f);
  glColor3ub(0, 0, 255);
  glVertex3f(-400.0f, -150.0f, 200.0f);
  glVertex3f(400.0f, -150.0f, 200.0f);
  glEnd();
  glPushMatrix();
  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  DrawTeapot(0);
  glPopMatrix();
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glPushMatrix();
  glMultMatrixf((GLfloat *)shadowMat);
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  DrawTeapot(1);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
  glColor3ub(255, 255, 0);
  glutSolidSphere(5.0f, 10, 10);
  glPopMatrix();
  glEnable(GL_DEPTH_TEST);
  glutSwapBuffers();
}

void SetupRC() {
  GLTVector3 points[3] = {{-30.0f, -149.0f, -20.0f},
                          {-30.0f, -149.0f, 20.0f},
                          {40.0f, -149.0f, 20.0f}};
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
  glMateriali(GL_FRONT, GL_SHININESS, 128);
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  gltMakeShadowMatrix(points, lightPos, shadowMat);
}

void SpecialKeys(int key, int x, int y) {
  if (key == GLUT_KEY_UP)
    xRot -= 5.0f;
  if (key == GLUT_KEY_DOWN)
    xRot += 5.0f;
  if (key == GLUT_KEY_LEFT)
    yRot -= 5.0f;
  if (key == GLUT_KEY_RIGHT)
    yRot += 5.0f;
  if (key > 356.0f)
    xRot = 0.0f;
  if (key < -1.0f)
    xRot = 355.0f;
  if (key > 356.0f)
    yRot = 0.0f;
  if (key < -1.0f)
    yRot = 355.0f;
  glutPostRedisplay();
}

void ChangeSize(int w, int h) {
  GLfloat fAspect;
  if (h == 0)
    h = 1;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  fAspect = (GLfloat)w / (GLfloat)h;
  gluPerspective(60.0f, fAspect, 200.0, 500.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -400.0f);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void changefog(int id) {
  switch (id) {
  case 0:
    glDisable(GL_FOG);
    glClearColor(fLowLight[0], fLowLight[1], fLowLight[2], fLowLight[3]);
    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fLowLight);
    glFogf(GL_FOG_START, 100.0f);
    glFogf(GL_FOG_END, 650.0f);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    break;
  case 1:
    glDisable(GL_FOG);
    glClearColor(fLowLight[0], fLowLight[1], fLowLight[2], fLowLight[3]);
    glFogfv(GL_FOG_COLOR, fLowLight);
    glFogf(GL_FOG_DENSITY, 0.005f);
    glFogi(GL_FOG_MODE, GL_EXP);
    glEnable(GL_FOG);
    break;
  case 2:
    glDisable(GL_FOG);
    glClearColor(fLowLight[0], fLowLight[1], fLowLight[2], fLowLight[3]);
    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 0.005f);
    glFogfv(GL_FOG_COLOR, fLowLight);
    glFogi(GL_FOG_MODE, GL_EXP2);
    break;
  }
  glutPostRedisplay();
}

void createMenu() {
  glutCreateMenu(changefog);
  glutAddMenuEntry("GL_LINEAR on", 0);
  glutAddMenuEntry("GL_EXP on", 1);
  glutAddMenuEntry("GL_EXP2 on", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Almazova");
  glutReshapeFunc(ChangeSize);
  glutSpecialFunc(SpecialKeys);
  glutDisplayFunc(RenderScene);
  createMenu();
  SetupRC();
  glutMainLoop();
  return 0;
}
