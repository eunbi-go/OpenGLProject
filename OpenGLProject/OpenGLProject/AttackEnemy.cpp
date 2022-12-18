#include "stdafx.h"
#include "AttackEnemy.h"
#include "Bullet.h"

#include "ObjectManager.h"
#include "Timer.h"
#include "Player.h"

random_device rd1;
mt19937 gen1(rd1());
uniform_int_distribution<int> attackType(1, 2);

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
	static_cast<Cube*>(_leftLeg)->SetScale(glm::vec3(0.3f, 0.8f, 0.3f));
	static_cast<Cube*>(_leftLeg)->SetColor(1.f, 0.7f, 0.9f);
	_leftLeg->Initialize();

	_rightLeg = new Cube;
	static_cast<Cube*>(_rightLeg)->SetScale(glm::vec3(0.3f, 0.8f, 0.3f));
	static_cast<Cube*>(_rightLeg)->SetColor(1.f, 0.7f, 0.9f);
	_rightLeg->Initialize();

	_ring = new Cube;
	static_cast<Cube*>(_ring)->SetScale(glm::vec3(0.3f, 0.3f, 0.3f));
	static_cast<Cube*>(_ring)->SetColor(1.f, 0.f, 0.4f);
	_ring->Initialize();

	UpdateBuffer();
}

int AttackEnemy::Update()
{
	glm::mat4 playerMat = static_cast<Cube*>(ObjectManager::Get_Instance()->Get_Player())->Get_Translation();
	glm::vec3 playerPos = glm::vec3(playerMat[3][0], playerMat[3][1], playerMat[3][2]);
	glm::vec3 pos = glm::vec3(trans[3][0], trans[3][1], trans[3][2]);
	glm::vec3 dir = playerPos - pos;
	dir.y = 0.f;
	glm::vec3 normalDir = glm::normalize(dir);
	glm::quat q;
	q = glm::quatLookAt(normalDir, glm::vec3(0.f, 1.f, 0.f));
	rotation = glm::mat4_cast(q);

	_ringRot += Timer::Get_Instance()->Get_DeltaTime() * 100.f;
	if (_ringRot > 360.f)
		_ringRot = 1.f;

	_attackTime += Timer::Get_Instance()->Get_DeltaTime();
	if (_attackTime > 3.f)
	{
		_attackTime = 0.f;
		Attack();
	}

	return OBJ_NOEVENET;
}

void AttackEnemy::Late_Update()
{
}

void AttackEnemy::Render(GLuint _program, GLuint _texProgram)
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
		_bulletPos = t1 * t2;
		static_cast<Cube*>(_ring)->SetFinalMat(childMat);
		static_cast<Cube*>(_ring)->RenderFinalMatrix(_program);
	}
}

void AttackEnemy::Attack()
{
	if (static_cast<Player*>(ObjectManager::Get_Instance()->Get_Player())->GetZ() < trans[3][2]) return;

	Object* obj = nullptr;
	obj = new Bullet;
	static_cast<Cube*>(obj)->SetPos(glm::vec3(_bulletPos[3][0], _bulletPos[3][1], _bulletPos[3][2]));
	static_cast<Cube*>(obj)->SetScale(glm::vec3(0.4f, 0.4f, 0.4f));
	static_cast<Cube*>(obj)->SetBoundingSize(0.35f);
	static_cast<Cube*>(obj)->SetColor(1.f, 0.8f, 0.8f);
	obj->Initialize();

	int randomValue = attackType(gen1);
	if (randomValue == 1)
		static_cast<Cube*>(obj)->SetMoveDir(MOVE::MOVE_TO_PLAYER);
	else
		static_cast<Cube*>(obj)->SetMoveDir(MOVE::MOVE_BACK);
	ObjectManager::Get_Instance()->Add_Object(obj, OBJID::BULLET);
}
