#version 430  //���߱��������ǵ�Ŀ��GLSL�������汾��4.3


layout (location = 0) in vec3 Position;

uniform mat4 gWorld;

// ������ɫ���������ɫֵ
out vec4 Color;

void main()
{
    gl_Position = gWorld * vec4(Position, 1.0);
    // ��ɫ��ֵ
    Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
	//Color = vec4(Position,1.0);
}