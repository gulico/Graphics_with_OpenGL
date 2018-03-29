// Task4.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "opencv2\core.hpp"
#include "opencv2\imgcodecs.hpp"
#include "opencv2\imgproc.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>

#pragma comment(lib,"glew32d.lib")
#include<iostream>
using namespace std;
using namespace cv;

float IMG_HEIGHT(600);
float IMG_WIDTH(600);
int KERNEL_SIZE = 13;
Mat IMG_MAT;
Mat IMG_GRAY;
Mat IMG_RGB[3];
Mat IMG_BOX_FILTER;//�˲�
Mat IMG_VERT_EDGE;//ˮƽ
Mat IMG_HORZ_EDGE;//��ֱ
Mat IMG_ALL_EDGE;//����
Mat IMG_ABS_IMG_VERT_EDGE;
Mat IMG_ABS_IMG_HORZ_EDGE;
Mat GRAD;
Mat BOX_KERNEL = Mat::ones(Size(KERNEL_SIZE, KERNEL_SIZE), CV_32F) / (float)(KERNEL_SIZE * KERNEL_SIZE);
Mat VERT_GRAD_KERNEL = (Mat_<float>(3, 3) << 0, 0, 0, -1, 0, 1, 0, 0);
Mat HORZ_GRAD_KERNEL = (Mat_<float>(3, 3) << 0, -1, 0, 0, 0, 0, 1, 0);
Mat ALL_GRAD_KERNEL = (Mat_<float>(3, 3) << 0, -1, 0, -1, 0, 1, 1, 0);

void init(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, IMG_WIDTH,0, IMG_HEIGHT);
}
void loadImage(){
	Mat img_bgr = cv::imread("tiger-03.jpg", cv::IMREAD_COLOR); 
	// ͼ����Y�᷽��ľ���ת 
	flip(img_bgr, img_bgr, 1);
	// ��ͼ��� BGR ��ɫģʽת��Ϊ RGB��ɫģʽ 
	Mat img_rgb; 
	cvtColor(img_bgr, img_rgb, COLOR_BGR2RGB); 
	// ��ȡͼ���С���߶ȶ�Ӧ�������������ȶ�Ӧ������ 
	MatSize img_size = img_rgb.size;
	IMG_HEIGHT = img_size[0]; 
	IMG_WIDTH = img_size[1]; 
	// ��ͼ����Z����ʱ����ת180�� 
	Mat M = cv::getRotationMatrix2D(cv::Point2f(IMG_WIDTH / 2, IMG_HEIGHT / 2), 180.0, 1.0); 
	warpAffine(img_rgb, IMG_MAT, M, cv::Size(IMG_WIDTH, IMG_HEIGHT));

	cvtColor(IMG_MAT, IMG_GRAY, CV_RGB2GRAY);//ת��Ϊ�Ҷ�ͼ
	split(IMG_MAT, IMG_RGB);//ͨ���ָ�
	filter2D(IMG_MAT, IMG_BOX_FILTER, -1, BOX_KERNEL);
	//filter2D(IMG_GRAY, IMG_HORZ_EDGE, -1, HORZ_GRAD_KERNEL);//ˮƽ�ݶ�
	//filter2D(IMG_GRAY, IMG_VERT_EDGE, -1, VERT_GRAD_KERNEL);//��ֱ�ݶ�
	//filter2D(IMG_GRAY, IMG_ALL_EDGE, -1, ALL_GRAD_KERNEL);//�����ݶ�
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0, 0);
	//glutPostRedisplay();
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, IMG_MAT.data);//����RGBͼ��
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, IMG_GRAY.data);//�Ҷ�ͼ
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_RED, GL_UNSIGNED_BYTE, IMG_RGB[0].data);//��ʾREDͨ��ͼ
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_BLUE, GL_UNSIGNED_BYTE, IMG_RGB[1].data);//��ʾBLUEͨ��ͼ
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_GREEN, GL_UNSIGNED_BYTE, IMG_RGB[2].data);//��ʾGREENͨ��ͼ
	
	glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, IMG_BOX_FILTER.data);//�˲�
	
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, IMG_HORZ_EDGE.data);//ˮƽ�ݶ�

	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, IMG_VERT_EDGE.data);//��ֱ�ݶ�

	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, IMG_ALL_EDGE.data);//�����ݶ�


	glutSwapBuffers();
	//glEnd();
	glFlush();
}
int _tmain(int argc, char** argv)
{
	//if (argc > 1){
		loadImage();

		glutInit(&argc, argv);
		glutInitContextVersion(4, 3);
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glutInitWindowPosition(50, 100);
		glutInitWindowSize(IMG_WIDTH, IMG_HEIGHT);
		glutCreateWindow("��ϰ��άͼ��Ļ�������");

		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glewExperimental = GL_TRUE;

		glewInit();
		init();
		glutMainLoop();
	//}
//	else{
//		cout << "Usage:" << argv[0] << "image_file_name" << endl;
	//}

	return 0;
}
