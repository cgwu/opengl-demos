
#include "stdafx.h"

GLuint VBO_TRIANGLE;	//顶点缓冲器对象（VBO_TRIANGLEs）,用来存储顶点

/**
* 渲染回调函数
*/
static void RenderSceneCB() {
	// 清空颜色缓存
	glClear(GL_COLOR_BUFFER_BIT);

	// 开启顶点属性
	glEnableVertexAttribArray(0);
	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO_TRIANGLE);
	// 告诉管线怎样解析bufer中的数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// 开始绘制几何图形(绘制一个点)
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//  禁用顶点数据
	glDisableVertexAttribArray(0);

	// 交换前后缓存
	glutSwapBuffers();
	glFlush();
}

/**
* 创建顶点缓冲器
*/
static void CreateVertexBuffer()
{
	// 创建三角形三个顶点数组
	glm::vec3 vecPt[3];
	vecPt[0] = glm::vec3(-1.0f, -1.0f, 0.0f) / 2.0f;
	vecPt[1] = glm::vec3(1.0f, -1.0f, 0.0f) / 2.0f;
	vecPt[2] = glm::vec3(0.0f, 1.0f, 0.0f) / 2.0f;

	// 创建缓冲器
	glGenBuffers(1, &VBO_TRIANGLE);
	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO_TRIANGLE);
	// 绑定顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vecPt), vecPt, GL_STATIC_DRAW);
	//std::cout << sizeof(Vertices) << std::endl;	//12
}

int main_HelloTriangle(int argc, char *argv[])
{
	// 初始化GLUT
	glutInit(&argc, argv);

	// 显示模式：双缓冲、RGBA
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	// 窗口设置
	glutInitWindowSize(480, 320);      // 窗口尺寸
	glutInitWindowPosition(100, 100);  // 窗口位置
	glutCreateWindow("Tutorial 02");   // 窗口标题
									   // 开始渲染
	glutDisplayFunc(RenderSceneCB);

	// 检查GLEW是否就绪，必须要在GLUT初始化之后！
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	// 缓存清空后的颜色值
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// 创建顶点缓冲器
	CreateVertexBuffer();

	// 通知开始GLUT的内部循环
	glutMainLoop();

	return 0;
}