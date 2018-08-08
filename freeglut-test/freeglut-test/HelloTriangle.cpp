
#include "stdafx.h"

GLuint VBO_TRIANGLE;	//���㻺��������VBO_TRIANGLEs��,�����洢����

/**
* ��Ⱦ�ص�����
*/
static void RenderSceneCB() {
	// �����ɫ����
	glClear(GL_COLOR_BUFFER_BIT);

	// ������������
	glEnableVertexAttribArray(0);
	// ��GL_ARRAY_BUFFER������
	glBindBuffer(GL_ARRAY_BUFFER, VBO_TRIANGLE);
	// ���߹�����������bufer�е�����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// ��ʼ���Ƽ���ͼ��(����һ����)
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//  ���ö�������
	glDisableVertexAttribArray(0);

	// ����ǰ�󻺴�
	glutSwapBuffers();
	glFlush();
}

/**
* �������㻺����
*/
static void CreateVertexBuffer()
{
	// ����������������������
	glm::vec3 vecPt[3];
	vecPt[0] = glm::vec3(-1.0f, -1.0f, 0.0f) / 2.0f;
	vecPt[1] = glm::vec3(1.0f, -1.0f, 0.0f) / 2.0f;
	vecPt[2] = glm::vec3(0.0f, 1.0f, 0.0f) / 2.0f;

	// ����������
	glGenBuffers(1, &VBO_TRIANGLE);
	// ��GL_ARRAY_BUFFER������
	glBindBuffer(GL_ARRAY_BUFFER, VBO_TRIANGLE);
	// �󶨶�������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vecPt), vecPt, GL_STATIC_DRAW);
	//std::cout << sizeof(Vertices) << std::endl;	//12
}

int main_HelloTriangle(int argc, char *argv[])
{
	// ��ʼ��GLUT
	glutInit(&argc, argv);

	// ��ʾģʽ��˫���塢RGBA
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	// ��������
	glutInitWindowSize(480, 320);      // ���ڳߴ�
	glutInitWindowPosition(100, 100);  // ����λ��
	glutCreateWindow("Tutorial 02");   // ���ڱ���
									   // ��ʼ��Ⱦ
	glutDisplayFunc(RenderSceneCB);

	// ���GLEW�Ƿ����������Ҫ��GLUT��ʼ��֮��
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	// ������պ����ɫֵ
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// �������㻺����
	CreateVertexBuffer();

	// ֪ͨ��ʼGLUT���ڲ�ѭ��
	glutMainLoop();

	return 0;
}