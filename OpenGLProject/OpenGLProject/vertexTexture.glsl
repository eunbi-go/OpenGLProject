#version 330 core
layout (location = 0) in vec3 vPos; //--- ��ġ
layout (location = 1) in vec3 vNormal; //--- �븻��
layout (location = 2) in vec2 vTexCoord; //--- �ؽ�ó ��ǥ

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

out vec3 outNormal;
out vec2 TexCoord;

void main()
{
//gl_Position = vec4(vPos, 1.0);
gl_Position = projectionTransform * viewTransform * vec4(vPos, 1.0);
outNormal = vNormal; //--- �븻�� ����
TexCoord = vTexCoord; //--- �ؽ�ó ��ǥ ����
}