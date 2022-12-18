#include "stdafx.h"
#include "MovingEnemy.h"

#include "Timer.h"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dir(0, 1);

MovingEnemy::MovingEnemy()
{
}

MovingEnemy::~MovingEnemy()
{
}

void MovingEnemy::Initialize()
{
	_eDir = static_cast<DIR>(dir(gen));	// 0 or 1
	_movingSpeed = 2.f;

	_child = new Cube;
	static_cast<Cube*>(_child)->SetScale(glm::vec3(0.3f, 0.3f, 0.3f));
	static_cast<Cube*>(_child)->SetColor(0.8f, 1.f, 1.f);	// ¸öÅëº¸´Ù ´õ ¿¬ÇÑ ÇÏ´Ã»ö
	_child->Initialize();

	UpdateBuffer();
}

int MovingEnemy::Update()
{
	_dirTime += Timer::Get_Instance()->Get_DeltaTime();
	if (_dirTime >= 0.5)
	{
		_dirTime = 0.f;
		if (_eDir == LEFT) _eDir = RIGHT;
		else _eDir = LEFT;
	}

	if (_eDir == LEFT) _eCurMoveDir = MOVE::MOVE_LEFT;
	else _eCurMoveDir = MOVE::MOVE_RIGHT;
	Move();

	// child
	_childRot += Timer::Get_Instance()->Get_DeltaTime() * 100.f;
	if (_childRot > 360.f)
		_childRot = 1.f;

	return OBJ_NOEVENET;
}

void MovingEnemy::Late_Update()
{
}

void MovingEnemy::Render(GLuint _program, GLuint _texProgram)
{
	glm::mat4 finalMat = trans * rotation * scale;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);

	// child
	RenderChild(_program);
}

void MovingEnemy::Release()
{
}

void MovingEnemy::RenderChild(GLuint _program)
{
	glm::mat4 childMat = glm::mat4(1.f);
	glm::mat4 r1 = glm::mat4(1.f);
	glm::mat4 t1 = glm::mat4(1.f);
	glm::mat4 t2 = glm::mat4(1.f);

	r1 = glm::rotate(r1, glm::radians((float)_childRot), glm::vec3(0.f, 1.f, 0.f));
	t1 = glm::translate(t1, glm::vec3(trans[3][0], trans[3][1], trans[3][2]));
	t2 = glm::translate(t2, glm::vec3(0.f, 0.5f, 0.f));

	childMat = t1 * r1 * t2 * static_cast<Cube*>(_child)->scale;
	static_cast<Cube*>(_child)->SetFinalMat(childMat);
	static_cast<Cube*>(_child)->RenderFinalMatrix(_program);
}
