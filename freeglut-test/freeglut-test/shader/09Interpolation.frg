#version 430  //告诉编译器我们的目标GLSL编译器版本是4.3

// 接受vs传来的插值后的颜色值
in vec4 Color;

out vec4 FragColor;

void main()
{
    // 颜色值作为片段着色器fs的输出
    FragColor = Color;
}