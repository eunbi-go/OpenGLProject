#include "stdafx.h"
#include "Bullet.h"

#include "Timer.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	Release();
}

void Bullet::Initialize()
{
	UpdateBuffer();
}

int Bullet::Update(float deltaTime)
{
	if (_isDead)
		return DEATH;

	_lifeTime += Timer::Get_Instance()->Get_DeltaTime();
	if (_lifeTime >= 3.f)
		return DEATH;

	Move();
	return ALIVE;
}

void Bullet::Late_Update(float deltaTime)
{
}

void Bullet::Render(GLuint _program, GLuint _texProgram)
{
	glm::mat4 finalMat = _trans * _rotation * _scale;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(_vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);
}

void Bullet::Release()
{
}
