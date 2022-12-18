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
	if (_isDead) return OBJ_DEAD;

	return OBJ_NOEVENET;
}

void Item::Late_Update()
{
}

void Item::Render(GLuint _program)
{
	glm::mat4 finalMat = trans * rotation * scale;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}

void Item::Release()
{
}
