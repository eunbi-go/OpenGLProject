#include "stdafx.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
	Release();
}

void Item::Initialize()
{
	Cube::Initialize();
}

int Item::Update(float deltaTime)
{
	return Cube::Update(deltaTime);
}

void Item::Late_Update(float deltaTime)
{
}

void Item::Render(GLuint _program, GLuint _texProgram)
{
	glm::mat4 finalMat = _trans * _rotation * _scale;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(_vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}

void Item::Release()
{
}
