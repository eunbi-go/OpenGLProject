#include "stdafx.h"
#include "AttackEnemy.h"

#include "ObjectManager.h"
#include "Timer.h"

AttackEnemy::AttackEnemy()
{
}

AttackEnemy::~AttackEnemy()
{
}

void AttackEnemy::Initialize()
{
	_movingSpeed = 2.f;

	_leftLeg = new Cube;
	_leftLeg->Initialize();
	static_cast<Cube*>(_leftLeg)->SetScale(glm::vec3(0.3f, 0.8f, 0.3f));

	_rightLeg = new Cube;
	_rightLeg->Initialize();
	static_cast<Cube*>(_rightLeg)->SetScale(glm::vec3(0.3f, 0.8f, 0.3f));

	_ring = new Cube;
	_ring->Initialize();
	static_cast<Cube*>(_ring)->SetScale(glm::vec3(0.3f, 0.3f, 0.3f));

	UpdateBuffer();
}

int AttackEnemy::Update()
{
	_ringRot += Timer::Get_Instance()->Get_DeltaTime() * 100.f;
	if (_ringRot > 360.f)
		_ringRot = 1.f;

	return OBJ_NOEVENET;
}

void AttackEnemy::Late_Update()
{
}

void AttackEnemy::Render(GLuint _program)
{
	glm::mat4 finalMat = trans * rotation * scale;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);

	RenderChild(_program);
}

void AttackEnemy::Release()
{
}

void AttackEnemy::RenderChild(GLuint _program)
{
	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 t1 = glm::mat4(1.f);
		glm::mat4 t2 = glm::mat4(1.f);

		t1 = glm::translate(t1, glm::vec3(trans[3][0], trans[3][1], trans[3][2]));
		t2 = glm::translate(t2, glm::vec3(-0.1f, -0.2f, 0.f));

		childMat = t1 * t2 * static_cast<Cube*>(_leftLeg)->scale;
		static_cast<Cube*>(_leftLeg)->SetFinalMat(childMat);
		static_cast<Cube*>(_leftLeg)->RenderFinalMatrix(_program);
	}

	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 t1 = glm::mat4(1.f);
		glm::mat4 t2 = glm::mat4(1.f);

		t1 = glm::translate(t1, glm::vec3(trans[3][0], trans[3][1], trans[3][2]));
		t2 = glm::translate(t2, glm::vec3(0.1f, -0.2f, 0.f));

		childMat = t1 * t2 * static_cast<Cube*>(_rightLeg)->scale;
		static_cast<Cube*>(_rightLeg)->SetFinalMat(childMat);
		static_cast<Cube*>(_rightLeg)->RenderFinalMatrix(_program);
	}

	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 t1 = glm::mat4(1.f);
		glm::mat4 t2 = glm::mat4(1.f);
		glm::mat4 r = glm::mat4(1.f);

		t1 = glm::translate(t1, glm::vec3(trans[3][0], trans[3][1], trans[3][2]));
		t2 = glm::translate(t2, glm::vec3(0.4f, 0.0f, 0.f));
		r = glm::rotate(r, glm::radians(_ringRot), glm::vec3(0.f, 1.f, 0.f));
		childMat = t1 * r * t2 * static_cast<Cube*>(_ring)->scale;
		static_cast<Cube*>(_ring)->SetFinalMat(childMat);
		static_cast<Cube*>(_ring)->RenderFinalMatrix(_program);
	}
}
