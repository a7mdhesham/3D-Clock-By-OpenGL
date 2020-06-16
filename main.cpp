#ifdef _CRT_SECURE_NO_WARNINGS
#undef _CRT_SECURE_NO_WARNINGS
#endif
#define _CRT_SECURE_NO_WARNINGS 1
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) 

#include <iostream>
#include <GL\glut.h>
#include <math.h>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;
int x = 200, y = 200, r = 190;
double PI = 22.0 / 7.0;
float S_angle = 0, M_angle = 0, H_angle = 0;


void drawStrokeText(string str, int x, int y, int z)
{
	glPushMatrix();
	glTranslatef(x, y + 8, z);
	glScalef(0.29f, -0.28f, z);
	for (char& c : str) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	}
	glPopMatrix();
}
void drawTextt(string str, int xp, int yp, int zp)
{
	glPushMatrix();
	glTranslatef(xp, yp + 8, zp);
	glScalef(0.29f, -0.28f, 0.0f);
	for (char& c : str) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
	}
	glPopMatrix();
}
double HourAngle = 0;
double MinAngle = 0;
double SecAngle = 0;

void borders(float zscale = 0.0f) {
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, zscale);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 360; i += 1) {
		if ((i % 30 == 0) || (i % 30 == 1) || (i % 30 == 2) || (i % 30 == 3) || (i % 30 == 4) || (i % 30 == 5) || (i % 30 == 6))
			glColor3f(1.0, 0.0, 0.0);
		else
			glColor3f(225 / 255.0F, 225 / 255.0F, 225 / 255.0F);
		double angle = 2 * PI * i / 360;
		double xf = x + cos(angle) * r;
		double yf = y + sin(angle) * r;
		glVertex2d(xf, yf);
	}
	glEnd();
	glPopMatrix();
}
void numbers() {
	glPushMatrix();
	glTranslatef(-28, 5, 0);
	int hour = 0;
	for (int i = -59; i <= 300; i += 30) {
		hour++;
		double angle = 2 * PI * i / 360;
		double xf = x + cos(angle) * (r - 30);
		double yf = y + sin(angle) * (r - 30);
		drawStrokeText(to_string(hour), xf, yf, 0);
	}

	glPopMatrix();
}
void Arrows(int angle, int arrow_Size, int linewidth, float Red, float Green, float Blue) {
	glPushMatrix();
	glLoadIdentity();
	glColor3f(Red / 255.0F, Green / 255.0F, Blue / 255.0F);
	glLineWidth(3);
	glTranslatef(200, 200, 0);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-200, -200, 0);
	glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(x, arrow_Size);
	glEnd();
	glLineWidth(1);
	glPopMatrix();
}
void display() {
	glClearColor(41 / 255.0F, 41 / 255.0F, 41 / 255.0F, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(225 / 255.0F, 225 / 255.0F, 225 / 255.0F);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearDepth(GLUT_DEPTH);


	borders(1.0);
	Arrows(S_angle, 70, 1, 238, 0, 0);
	Arrows(M_angle, 85, 3, 233, 233, 233);
	Arrows(H_angle, 105, 3, 233, 233, 233);
	numbers();

	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int delay = 1000;
void StepRot(int n)
{
	n++;
	S_angle += 6;
	M_angle += 0.1f;
	H_angle += 360.0F / 216000.0F;
	glutPostRedisplay();
	glutTimerFunc(delay, StepRot, n);
	PlaySound(MAKEINTRESOURCE(101), GetModuleHandle(NULL), SND_RESOURCE);

}
void main(int argc, char** argv) {
	time_t currentTime;
	struct tm *localTime;
	time(&currentTime);
	localTime = localtime(&currentTime);
	int Hour = localTime->tm_hour;
	int Min = localTime->tm_min;
	int Sec = localTime->tm_sec;

	H_angle = 30 * Hour;
	M_angle = 6 * Min;
	S_angle = 6 * Sec;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 400) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - 400) / 2);
	glutInitWindowSize(380,400);
	glutCreateWindow("Analog Clock");
	gluOrtho2D(0, 400, 0, 400);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(delay, StepRot, 0);
	glutMainLoop();
	
}