// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>


// TODO: 在此处引用程序需要的其他头文件
#define GLEW_STATIC
//#define FREEGLUT_STATIC

#include <GL/glew.h>		// GLEW扩展库
//#include <GL/glut.h>		// 窗口图形库	std
#include <GL/freeglut.h>	// 窗口图形库 std && ext
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util.h"
