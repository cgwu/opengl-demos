#version 430  //告诉编译器我们的目标GLSL编译器版本是4.3


layout (location = 0) in vec3 Position;

uniform mat4 gWorld;

// 顶点着色器输出的颜色值
out vec4 Color;

void main()
{
    gl_Position = gWorld * vec4(Position, 1.0);
    // 颜色插值
    Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
	//Color = vec4(Position,1.0);
}