#version 430  //告诉编译器我们的目标GLSL编译器版本是4.3

layout (location = 0) in vec3 Position;

// 平移变换聚矩阵一致变量
uniform mat4 gWorld;

void main()
{
    // 用平移变换矩阵乘以图形顶点位置对应的4X4矩阵相乘，完成平移变换
    gl_Position = gWorld * vec4(Position, 1.0);
}