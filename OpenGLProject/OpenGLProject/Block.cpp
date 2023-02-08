#include "stdafx.h"
#include "Block.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Initialize()
{
	Cube::Initialize();
}

int Block::Update()
{
	return Cube::Update();
}

void Block::Late_Update()
{
}

void Block::Render(GLuint _program, GLuint _texProgram)
{
	glm::mat4 finalMat = _trans * _rotation * _scale;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(_vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}

void Block::Release()
{
}
