// helloworld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#include <cmath>

#define PI 3.14

#pragma comment(lib, "glew32d.lib")

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawCricle()
{
	glColor3f(1.f, 0.f, 0.f);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (double angle = 360; angle > 0; angle = angle - 1){
		glVertex2f(cos(2 * PI*angle / 360.0)*50, sin(2 * PI*angle / 360.0)*50);
	}
	glEnd();
	glFlush();

	glColor3f(0.f, 1.f, 0.f);
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2f( 0 , 0 );
	glVertex2f(cos(2 * PI * 45 / 360.0) * 50, sin(2 * PI*45 / 360.0) * 50);
	glEnd();
	glFlush();

	glColor3f(0.f, 1.f, 0.f);
	glPointSize(2);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(cos(2 * PI * 45 / 360.0) * 50, sin(2 * PI * 45 / 360.0) * 50);
	glEnd();
	glFlush();
}

void drawCos()
{
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.f, 0.f, 1.f);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	for (double angle = 0; angle <720 ; angle = angle + 1){
		glVertex2f(angle/5-80, cos(2 * PI*angle / 360.0) * 50);
	}
	glEnd();
	glFlush();
}

void drawX(int x,int y,int width){//»­ºá×ø±ê
	glColor3f(0.f, 0.f, 0.f);
	glBegin(GL_LINES);
	glVertex2f(x,y);
	glVertex2f(x+width,y);
	glVertex2f(x + width - cos(2 * PI * 45 / 360.0) * 5, y + sin(2 * PI * 45 / 360.0) * 5);
	glVertex2f(x + width, y);
	glVertex2f(x + width - cos(2 * PI * 45 / 360.0) * 5, y - sin(2 * PI * 45 / 360.0) * 5);
	glVertex2f(x + width, y);
	glEnd();
	glFlush();
}
void drawY(int x, int y, int height){//»­×Ý×ø±ê
	glColor3f(0.f, 0.f, 0.f);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x , y+height);
	glVertex2f(x - cos(2 * PI * 45 / 360.0) * 5, y + height - sin(2 * PI * 45 / 360.0) * 5);
	glVertex2f(x, y + height);
	glVertex2f(x + cos(2 * PI * 45 / 360.0) * 5, y + height - sin(2 * PI * 45 / 360.0) * 5);
	glVertex2f(x, y + height);
	glEnd();
	glFlush();
}

void drawRectangle(int x1,int y1,int x2,int y2){
	//glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
	glFlush();
}

void drawChart(){
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.f, 0.f, 1.f);
	drawRectangle(-5,50,5,0);

	glColor3f(0.f, 1.f, 0.f);
	drawRectangle(10, 25, 20, 0);
	drawRectangle(-20, 25, -10, 0);

	glColor3f(0.f, 1.f, 1.f);
	drawRectangle(30, 10, 40, 0);
	drawRectangle(-40, 10, -30, 0);

	drawX(-50, 0, 120);
	drawY(0, -50, 120);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GLHWORLD");

	glutDisplayFunc(drawChart);
	glutReshapeFunc(reshape);

	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutMainLoop();

	return 0;
}

