/*
���ϱ任
https://blog.csdn.net/cordova/article/details/52571920

OpenGL ����任GLM���ʹ��
https://blog.csdn.net/fu_shuwu/article/details/72874480
*/

#include "stdafx.h"

static GLuint VBO;
static GLuint IBO;		// �����������ľ��
static GLuint gWorldLocation;	// ƽ�Ʊ任һ�±����ľ������

// ����Ҫ��ȡ�Ķ�����ɫ���ű���Ƭ����ɫ���ű����ļ�������Ϊ�ļ���ȡ·��
//�������Ļ�shader.vs��shader.fs�ļ�Ҫ�ŵ����̵ĸ�Ŀ¼�£���֤���涨������������ļ����ļ�·����
static const char* pVSFileName = "shader/09Interpolation.vert";
static const char* pFSFileName = "shader/09Interpolation.frg";

/**
* ��Ⱦ�ص�����
*/
static void RenderSceneCB() {
	// �����ɫ����
	glClear(GL_COLOR_BUFFER_BIT);

	// ά��һ��������������ľ�̬������
	static float Scale = 0.0f;
	Scale += 0.01f;

	/*
	Pipeline p;
	p.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
	p.WorldPos(sinf(Scale), 0.0f, 0.0f);
	p.Rotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)p.GetWorldTrans());
	*/

	// �ο�: https://blog.csdn.net/lixiaoguang20/article/details/79483080
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	Model = glm::translate(Model, glm::vec3(sinf(Scale), 0.0f, 0.0f));	//ƽ��
	Model = glm::rotate(Model, sinf(Scale) * 90.0f, glm::vec3(1.0f, 1.0f, 1.0f));	//��ת
	Model = glm::scale(Model, glm::vec3(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f))); //����
	
	/*
	glm::mat4 Model2 = glm::mat4(1.0f);
	Model2 = glm::scale(Model2, glm::vec3(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f)));
	Model2 = glm::rotate(Model2, sinf(Scale) * 90.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	Model2 = glm::translate(Model2, glm::vec3(sinf(Scale), 0.0f, 0.0f));	//ƽ��
	assert(Model == Model2);	//֤���� scale, rotate, translate �õ���������޹ء�
	*/

	// �������õ�"����ת������"���ص�shader��
	//glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World[0][0]);
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &Model[0][0]);

	// ������������
	glEnableVertexAttribArray(0);

	// ��GL_ARRAY_BUFFER������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ���߹�����������bufer�е�����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// ÿ���ڻ���֮ǰ����������
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	// ��������ͼ��
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	// ��ʼ���Ƽ���ͼ��(����һ����)
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//  ���ö�������
	glDisableVertexAttribArray(0);

	// ����ǰ�󻺴�
	glutSwapBuffers();
	glFlush();
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	// ����Ⱦ�ص�ע��Ϊȫ�����ûص�
	glutIdleFunc(RenderSceneCB);
}


/**
* �������㻺����
*/
static void CreateVertexBuffer()
{
	// ����������������������
	glm::vec3 vecPt[4];
	vecPt[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	vecPt[1] = glm::vec3(0.0f, -1.0f, 1.0f);
	vecPt[2] = glm::vec3(1.0f, -1.0f, 0.0f);
	vecPt[3] = glm::vec3(0.0f, 1.0f, 0.0f);

	// ����������
	glGenBuffers(1, &VBO);
	// ��GL_ARRAY_BUFFER������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// �󶨶�������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vecPt), vecPt, GL_STATIC_DRAW);
	//std::cout << sizeof(Vertices) << std::endl;	//12
}

// ��������������
static void CreateIndexBuffer()
{
	// �ĸ���������Ķ���������
	unsigned int Indices[] = { 
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 
	};
	// ����������
	glGenBuffers(1, &IBO);
	// �󶨻�����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	// ��ӻ���������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

// ʹ��shader�ı�����shader���󣬲���shader���뵽��ɫ��������
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	// ����shader���Ͳ�����������shader����
	GLuint ShaderObj = glCreateShader(ShaderType);
	// ����Ƿ���ɹ�
	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	// ����shader�Ĵ���Դ
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);// ����shader����

	// ����shader��صĴ���
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	// ������õ�shader����󶨵�program object���������
	glAttachShader(ShaderProgram, ShaderObj);
}

// ������ɫ������
static void CompileShaders()
{
	// ������ɫ������
	GLuint ShaderProgram = glCreateProgram();
	// ����Ƿ񴴽��ɹ�
	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// �洢��ɫ���ı����ַ�������
	std::string vs, fs;
	// �ֱ��ȡ��ɫ���ļ��е��ı����ַ���������
	vs = loadFileContent(pVSFileName);
	fs = loadFileContent(pFSFileName);
	if (vs == "" || fs == "") {
		cerr << "Shader file content is empty!" << endl;
		exit(1);
	}
	// ��Ӷ�����ɫ����Ƭ����ɫ��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	// ����shader��ɫ�����򣬲���������ش���
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// �����֤�ڵ�ǰ�Ĺ���״̬�����Ƿ���Ա�ִ��
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// ���õ�������������ʹ������ɹ�������shader����
	glUseProgram(ShaderProgram);

	// ��ѯ��ȡһ�±�����λ��
	gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
	assert(gWorldLocation != 0xFFFFFFFF);
}

int main(int argc, char *argv[])
{
	// ��ʼ��GLUT
	glutInit(&argc, argv);

	// ��ʾģʽ��˫���塢RGBA
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	// ��������
	glutInitWindowSize(800, 600);      // ���ڳߴ�
	glutInitWindowPosition(100, 100);  // ����λ��
	glutCreateWindow("Shader Demo");   // ���ڱ���
									   // ��ʼ��Ⱦ
	InitializeGlutCallbacks();

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
	CreateIndexBuffer();

	// ������ɫ��
	CompileShaders();

	// ֪ͨ��ʼGLUT���ڲ�ѭ��
	glutMainLoop();

	return 0;
}