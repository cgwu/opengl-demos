// freeglut-test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);	// 清空颜色缓冲池
	glColor3f(1.0f, .0f, 0.0f);
	//glRectf(-0.5f, -0.5f, 0.9f, 0.9f);
	//glRectf(.0f, .0f, 0.9f, 0.9f);
	glRectf(10.0f, 20.0f, 100.0f, 200.0f); 
	glFlush();	//执行OpenGL指令列表中的指令
}

int main_freeglut_test(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(600, 400);
	glutCreateWindow("第一个OpenGL程序");
	glutDisplayFunc(&myDisplay);
	glOrtho(.0f, 300.0f, .0f, 300.0f, 1.0f, -1.0f);	//指定坐标空间 (左下角为0,0)
	//glOrtho(300.0f, .0f, 300.0f, .0f, 1.0f, -1.0f);	//指定坐标空间 (右上角为0,0)
	glClearColor(.0f, .0f, 1.0f, 1.0f);	//使用蓝色清空背景底
	glutMainLoop();		// 消息循环（处理OS消息，如键盘、鼠标事件）
    return 0;
}

