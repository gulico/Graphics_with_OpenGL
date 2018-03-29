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

void drawX(int x,int y,int width){//��������
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
void drawY(int x, int y, int height){//��������
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

void drawFace(double r){//����

	//��
	//glColor3ub(255, 255, 0);//��ɫΪ��ɫ
	glBegin(GL_TRIANGLE_FAN);//���ǻ�
	glVertex2f(0, 0);//Բ��
	for (double angle = 0; angle <= 360; angle = angle + 1){
		glVertex2f(cos(angle*2.0*PI / 360.0)*r, sin(angle*2.0*PI / 360.0)*r);
	}
	glEnd();

	//����
	glColor3ub(0, 0, 0);//��ɫΪ��ɫ
	glBegin(GL_TRIANGLE_FAN);//���ǻ�
	glVertex2f(r / 3, r / 3);//Բ��
	for (double angle = 0; angle <= 360; angle = angle + 1){
		glVertex2f(cos(angle*2.0*PI / 360.0)*(r / 10) + r / 3, sin(angle*2.0*PI / 360.0)*(r / 10) + r / 3);
	}
	glEnd();

	//����
	glColor3ub(0, 0, 0);//��ɫΪ��ɫ
	glBegin(GL_TRIANGLE_FAN);//���ǻ�
	glVertex2f(-r / 3, r / 3);//Բ��
	for (double angle = 0; angle <= 360; angle = angle + 1){
		glVertex2f(cos(angle*2.0*PI / 360.0)*(r / 10) - r / 3, sin(angle*2.0*PI / 360.0)*(r / 10) + r / 3);
	}
	glEnd();

	//���
	glLineWidth(2);
	glColor3ub(0, 0, 0);//��ɫΪ��ɫ
	glBegin(GL_LINE_STRIP);//�Ǳպ��߶�

	for (double angle = 315; angle >= 225; angle = angle - 1){
		glVertex2f(cos(angle*2.0*PI / 360.0)*(r / 2), sin(angle*2.0*PI / 360.0)*(r / 2));
	}
	glEnd();
	//glFlush();
}

void drawElemBody(){
	//glColor3ub(255,255,0);//��ɫΪ��ɫ
	glBegin(GL_TRIANGLE_FAN);//���ǻ�
	glVertex2f(-20, 30);
	glVertex2f(-20, -30);
	glVertex2f(20, -30);
	glVertex2f(20, 30);
	glEnd();

	glLineWidth(2);
	glBegin(GL_LINES);//�Ǳպ��߶�
	glVertex2f(0, 30);
	glVertex2f(0, 60);
	glEnd();
}

void drawRobot(){
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix(); {//��Ŵ���
		glScalef(0.3f, 0.3f, 0.3f);//����
		glTranslatef(-40.f, -150.f, 0.f);//ƽ��
		//glRotatef(0.f, 0.f, 0.f, 1.f);//
		glColor3ub(255, 0, 0);
		drawElemBody();
	}
	glPopMatrix();

	glPushMatrix(); {//���С��
		glScalef(0.3f, 0.3f, 0.3f);//����
		glTranslatef(-40.f, -230.f, 0.f);//ƽ��
		//glRotatef(0.f, 0.f, 0.f, 1.f);//
		glColor3ub(255, 0, 0);
		drawElemBody();
	}
	glPopMatrix();

	glPushMatrix(); {//�ҽŴ���
		glScalef(0.3f, 0.3f, 0.3f);//����
		glTranslatef(40.f, -150.f, 0.f);//ƽ��
		//glRotatef(0.f, 0.f, 0.f, 1.f);//
		glColor3ub(255, 0, 0);
		drawElemBody();
	}
	glPopMatrix();

	glPushMatrix(); {//�ҽ�С��
		glScalef(0.3f, 0.3f, 0.3f);//����
		glTranslatef(40.f, -230.f, 0.f);//ƽ��
		//glRotatef(0.f, 0.f, 0.f, 1.f);//
		glColor3ub(255, 0, 0);
		drawElemBody();
	}
	glPopMatrix();

	glPushMatrix(); {//����
		glTranslatef(0.f, 0.001f, 0.f);//ƽ��
		glColor3ub(0, 0, 255);
		drawElemBody();
	}
	glPopMatrix();

	//����
	glPushMatrix(); {
		glScalef(0.5f, 0.5f, 0.5f);//����
		glTranslatef(0.f, 100.f, 0.f);//ƽ��
		glColor3ub(255,211,155);
		drawFace(35);
	}
	glPopMatrix();

	glPushMatrix(); {//����С��
		glScalef(0.3f, 0.3f, 0.3f);//����
		glTranslatef(-145.f, -30.f, 0.f);//ƽ��
		glRotatef(-30.f, 0.f, 0.f, 1.f);//
		glColor3ub(255, 211, 155);
		drawElemBody();
	}
	glPopMatrix();

	glPushMatrix(); {//���ִ��
		glScalef(0.3f, 0.3f, 0.3f);//����
		glTranslatef(-100.f, 30.f, 0.f);//ƽ��
		glRotatef(-50.f, 0.f, 0.f, 1.f);//
		glColor3ub(0, 0, 255);
		drawElemBody();
	}
	glPopMatrix();

	glPushMatrix(); {//����С��
		glScalef(0.3f, 0.3f, 0.3f);//����
		glTranslatef(180.f, 90.f, 0.f);//ƽ��
		glRotatef(135.f, 0.f, 0.f, 1.f);//
		glColor3ub(255, 211, 155);
		drawElemBody();
	}
	glPopMatrix();

	glPushMatrix(); {//���ִ��
		glScalef(0.3f, 0.3f, 0.3f);//����
		glTranslatef(110.f, 50.f, 0.f);//ƽ��
		glRotatef(90.f, 0.f, 0.f, 1.f);//
		glColor3ub(0, 0, 255);
		drawElemBody();
	}
	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glScalef(1.2f, 1.2f, 1.f);//����
	glRotatef(135.f, 0.f, 0.f, 1.f);//��ת
	glTranslatef(25.f, 25.f, 0.f);//ƽ��
	glColor3ub(255, 255, 0);
	drawFace(35);

	glutSwapBuffers();
	glFlush();
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

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutMainLoop();

	return 0;
}

