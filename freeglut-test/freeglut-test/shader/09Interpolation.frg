#version 430  //���߱��������ǵ�Ŀ��GLSL�������汾��4.3

// ����vs�����Ĳ�ֵ�����ɫֵ
in vec4 Color;

out vec4 FragColor;

void main()
{
    // ��ɫֵ��ΪƬ����ɫ��fs�����
    FragColor = Color;
}