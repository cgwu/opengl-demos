/*
复合变换
https://blog.csdn.net/cordova/article/details/52571920

OpenGL 矩阵变换GLM库的使用
https://blog.csdn.net/fu_shuwu/article/details/72874480
*/

#include "stdafx.h"

static GLuint VBO;
static GLuint IBO;		// 索引缓冲对象的句柄
static GLuint gWorldLocation;	// 平移变换一致变量的句柄引用

// 定义要读取的顶点着色器脚本和片断着色器脚本的文件名，作为文件读取路径
//（这样的话shader.vs和shader.fs文件要放到工程的根目录下，保证下面定义的是这两个文件的文件路径）
static const char* pVSFileName = "shader/09Interpolation.vert";
static const char* pFSFileName = "shader/09Interpolation.frg";

/**
* 渲染回调函数
*/
static void RenderSceneCB() {
	// 清空颜色缓存
	glClear(GL_COLOR_BUFFER_BIT);

	// 维护一个不断慢慢增大的静态浮点数
	static float Scale = 0.0f;
	Scale += 0.01f;

	/*
	Pipeline p;
	p.Scale(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f));
	p.WorldPos(sinf(Scale), 0.0f, 0.0f);
	p.Rotate(sinf(Scale) * 90.0f, sinf(Scale) * 90.0f, sinf(Scale) * 90.0f);
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, (const GLfloat*)p.GetWorldTrans());
	*/

	// 参考: https://blog.csdn.net/lixiaoguang20/article/details/79483080
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	Model = glm::translate(Model, glm::vec3(sinf(Scale), 0.0f, 0.0f));	//平移
	Model = glm::rotate(Model, sinf(Scale) * 90.0f, glm::vec3(1.0f, 1.0f, 1.0f));	//旋转
	Model = glm::scale(Model, glm::vec3(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f))); //缩放
	
	/*
	glm::mat4 Model2 = glm::mat4(1.0f);
	Model2 = glm::scale(Model2, glm::vec3(sinf(Scale * 0.1f), sinf(Scale * 0.1f), sinf(Scale * 0.1f)));
	Model2 = glm::rotate(Model2, sinf(Scale) * 90.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	Model2 = glm::translate(Model2, glm::vec3(sinf(Scale), 0.0f, 0.0f));	//平移
	assert(Model == Model2);	//证明： scale, rotate, translate 该调用与次序无关。
	*/

	// 将构建好的"复合转换矩阵"加载到shader中
	//glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World[0][0]);
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &Model[0][0]);

	// 开启顶点属性
	glEnableVertexAttribArray(0);

	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 告诉管线怎样解析bufer中的数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// 每次在绘制之前绑定索引缓冲
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	// 索引绘制图形
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	// 开始绘制几何图形(绘制一个点)
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//  禁用顶点数据
	glDisableVertexAttribArray(0);

	// 交换前后缓存
	glutSwapBuffers();
	glFlush();
}


static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	// 将渲染回调注册为全局闲置回调
	glutIdleFunc(RenderSceneCB);
}


/**
* 创建顶点缓冲器
*/
static void CreateVertexBuffer()
{
	// 创建三角形三个顶点数组
	glm::vec3 vecPt[4];
	vecPt[0] = glm::vec3(-1.0f, -1.0f, 0.0f);
	vecPt[1] = glm::vec3(0.0f, -1.0f, 1.0f);
	vecPt[2] = glm::vec3(1.0f, -1.0f, 0.0f);
	vecPt[3] = glm::vec3(0.0f, 1.0f, 0.0f);

	// 创建缓冲器
	glGenBuffers(1, &VBO);
	// 绑定GL_ARRAY_BUFFER缓冲器
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 绑定顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vecPt), vecPt, GL_STATIC_DRAW);
	//std::cout << sizeof(Vertices) << std::endl;	//12
}

// 创建索引缓冲器
static void CreateIndexBuffer()
{
	// 四个三角形面的顶点索引集
	unsigned int Indices[] = { 
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 
	};
	// 创建缓冲区
	glGenBuffers(1, &IBO);
	// 绑定缓冲区
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	// 添加缓冲区数据
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
}

// 使用shader文本编译shader对象，并绑定shader都想到着色器程序中
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	// 根据shader类型参数定义两个shader对象
	GLuint ShaderObj = glCreateShader(ShaderType);
	// 检查是否定义成功
	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}

	// 定义shader的代码源
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);// 编译shader对象

	// 检查和shader相关的错误
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}

	// 将编译好的shader对象绑定到program object程序对象上
	glAttachShader(ShaderProgram, ShaderObj);
}

// 编译着色器函数
static void CompileShaders()
{
	// 创建着色器程序
	GLuint ShaderProgram = glCreateProgram();
	// 检查是否创建成功
	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	// 存储着色器文本的字符串缓冲
	std::string vs, fs;
	// 分别读取着色器文件中的文本到字符串缓冲区
	vs = loadFileContent(pVSFileName);
	fs = loadFileContent(pFSFileName);
	if (vs == "" || fs == "") {
		cerr << "Shader file content is empty!" << endl;
		exit(1);
	}
	// 添加顶点着色器和片段着色器
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	// 链接shader着色器程序，并检查程序相关错误
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// 检查验证在当前的管线状态程序是否可以被执行
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}

	// 设置到管线声明中来使用上面成功建立的shader程序
	glUseProgram(ShaderProgram);

	// 查询获取一致变量的位置
	gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
	assert(gWorldLocation != 0xFFFFFFFF);
}

int main(int argc, char *argv[])
{
	// 初始化GLUT
	glutInit(&argc, argv);

	// 显示模式：双缓冲、RGBA
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	// 窗口设置
	glutInitWindowSize(800, 600);      // 窗口尺寸
	glutInitWindowPosition(100, 100);  // 窗口位置
	glutCreateWindow("Shader Demo");   // 窗口标题
									   // 开始渲染
	InitializeGlutCallbacks();

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
	CreateIndexBuffer();

	// 编译着色器
	CompileShaders();

	// 通知开始GLUT的内部循环
	glutMainLoop();

	return 0;
}