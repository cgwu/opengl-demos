#version 430  //告诉编译器我们的目标GLSL编译器版本是4.3

layout (location = 0) in vec3 Position; // 绑定定点属性名和属性，方式二缓冲属性和shader属性对应映射


uniform float gScale;

void main()
{
	// 为glVertexAttributePointer提供返回值
    gl_Position = vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0); 
}