#version 430  //���߱��������ǵ�Ŀ��GLSL�������汾��4.3

layout (location = 0) in vec3 Position; // �󶨶��������������ԣ���ʽ���������Ժ�shader���Զ�Ӧӳ��


uniform float gScale;

void main()
{
	// ΪglVertexAttributePointer�ṩ����ֵ
    gl_Position = vec4(gScale * Position.x, gScale * Position.y, Position.z, 1.0); 
}