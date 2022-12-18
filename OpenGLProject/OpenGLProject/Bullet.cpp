#include "stdafx.h"
#include "Bullet.h"

#include "Timer.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
}

int Bullet::Update()
{
	if (_isDead)
		return OBJ_DEAD;

	_lifeTime += Timer::Get_Instance()->Get_DeltaTime();
	if (_lifeTime >= 3.f)
		return OBJ_DEAD;

	Move();
	return OBJ_NOEVENET;
}

void Bullet::Late_Update()
{
}

void Bullet::Render(GLuint _program, GLuint _texProgram)
{
	glm::mat4 finalMat = trans * rotation * scale;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}

void Bullet::Release()
{
}
