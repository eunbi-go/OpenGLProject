#version 330

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Color;
//layout (location = 2) in vec2 in_TexCoord;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;

uniform int isGlu;
uniform vec3 uniformC;

out vec3 out_Color;

void main(void)
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(in_Position, 1.0);
	if (isGlu == 10) out_Color = uniformC;
	out_Color = in_Color;
}