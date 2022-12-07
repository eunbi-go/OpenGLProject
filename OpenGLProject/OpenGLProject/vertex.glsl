#version 330
//--- in_Position: attribute index 0 
//--- in_Color: attribute index 1

layout (location = 0) in vec3 in_Position; //--- ��ġ ����: attribute position 0
layout (location = 1) in vec3 in_Color; //--- �÷� ����: attribute position 1

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

uniform int isGlu;
uniform vec3 uniformC;

out vec3 out_Color; //--- �����׸�Ʈ ���̴����� ����

void main(void) 
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(in_Position, 1.0);
	if (isGlu == 10) out_Color = uniformC;
	out_Color = in_Color;
}