#include "stdafx.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Initialize()
{
}

int Item::Update()
{
	return 0;
}

void Item::Late_Update()
{
}

void Item::Render(GLuint _program, GLuint _texProgram)
{
	//glm::mat4 finalMat = trans * rotation * scale;
	//unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	//glBindVertexArray(vaoHandle);
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}

void Item::Release()
{
}
