// Task4.cpp : 定义控制台应用程序的入口点。
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
Mat IMG_BOX_FILTER;//滤波
Mat IMG_VERT_EDGE;//水平
Mat IMG_HORZ_EDGE;//垂直
Mat IMG_ALL_EDGE;//整体
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
	// 图像沿Y轴方向的镜像翻转 
	flip(img_bgr, img_bgr, 1);
	// 将图像从 BGR 颜色模式转换为 RGB颜色模式 
	Mat img_rgb; 
	cvtColor(img_bgr, img_rgb, COLOR_BGR2RGB); 
	// 获取图像大小（高度对应矩阵的行数，宽度对应列数） 
	MatSize img_size = img_rgb.size;
	IMG_HEIGHT = img_size[0]; 
	IMG_WIDTH = img_size[1]; 
	// 将图像绕Z轴逆时针旋转180度 
	Mat M = cv::getRotationMatrix2D(cv::Point2f(IMG_WIDTH / 2, IMG_HEIGHT / 2), 180.0, 1.0); 
	warpAffine(img_rgb, IMG_MAT, M, cv::Size(IMG_WIDTH, IMG_HEIGHT));

	cvtColor(IMG_MAT, IMG_GRAY, CV_RGB2GRAY);//转化为灰度图
	split(IMG_MAT, IMG_RGB);//通道分割
	filter2D(IMG_MAT, IMG_BOX_FILTER, -1, BOX_KERNEL);
	//filter2D(IMG_GRAY, IMG_HORZ_EDGE, -1, HORZ_GRAD_KERNEL);//水平梯度
	//filter2D(IMG_GRAY, IMG_VERT_EDGE, -1, VERT_GRAD_KERNEL);//垂直梯度
	//filter2D(IMG_GRAY, IMG_ALL_EDGE, -1, ALL_GRAD_KERNEL);//整体梯度
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0, 0);
	//glutPostRedisplay();
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, IMG_MAT.data);//生成RGB图像
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, IMG_GRAY.data);//灰度图
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_RED, GL_UNSIGNED_BYTE, IMG_RGB[0].data);//显示RED通道图
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_BLUE, GL_UNSIGNED_BYTE, IMG_RGB[1].data);//显示BLUE通道图
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_GREEN, GL_UNSIGNED_BYTE, IMG_RGB[2].data);//显示GREEN通道图
	
	glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, IMG_BOX_FILTER.data);//滤波
	
	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, IMG_HORZ_EDGE.data);//水平梯度

	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, IMG_VERT_EDGE.data);//垂直梯度

	//glDrawPixels(IMG_WIDTH, IMG_HEIGHT, GL_LUMINANCE, GL_UNSIGNED_BYTE, IMG_ALL_EDGE.data);//整体梯度


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
		glutCreateWindow("练习二维图像的基本操作");

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
