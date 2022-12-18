#include "stdafx.h"
#include "Player.h"
#include "Timer.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	SetScale(glm::vec3(0.9f, 0.8f, 0.9f));
	_movingSpeed = 20.f;
	UpdateBuffer();

	_leftLeg = new Cube;
	_leftLeg->Initialize();
	static_cast<Cube*>(_leftLeg)->SetScale(glm::vec3(0.3f, 0.8f, 0.3f));

	_rightLeg = new Cube;
	_rightLeg->Initialize();
	static_cast<Cube*>(_rightLeg)->SetScale(glm::vec3(0.3f, 0.8f, 0.3f));

	_leftArm = new Cube;
	_leftArm->Initialize();
	static_cast<Cube*>(_leftArm)->SetScale(glm::vec3(0.2f, 0.6f, 0.2f));

	_rightArm = new Cube;
	_rightArm->Initialize();
	static_cast<Cube*>(_rightArm)->SetScale(glm::vec3(0.2f, 0.6f, 0.2f));

	_head = new Cube;
	_head->Initialize();
	static_cast<Cube*>(_head)->SetScale(glm::vec3(0.7f, 0.7f, 0.7f));
}

int Player::Update()
{
	if (_isJump) Jump();
	else if (_isMoveStop)
	{
		_rightLegRot = -35.f;
		_leftLegRot = 35.f;
		_isLegMius = false;
	}

	ApplyItemEffect();

	UpdateChild();

	return OBJ_NOEVENET;
}

void Player::Late_Update()
{
}

void Player::Render(GLuint _program)
{
	glm::mat4 finalMat = trans * rotation* scale;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);

	RenderChild(_program);
}

void Player::Release()
{
}

void Player::ApplyItemEffect()
{
	// ALPHA
	if (_playerItem[ITEMTYPE::ALPHA]) {
		_alphaTime += Timer::Get_Instance()->Get_DeltaTime();

		_isCollision = false;
		_isMove = true;

		if (_alphaTime >= 5.f) {
			_isCollision = true;
			_alphaTime = 0.f;
			_playerItem[ITEMTYPE::ALPHA] = false;
		}
	}

	// SPEEDUP
	if (_playerItem[ITEMTYPE::SPEEDUP]) {
		_speedupTime += Timer::Get_Instance()->Get_DeltaTime();
	
		_movingSpeed = 10.f;
	
		if (_speedupTime >= 5.f) {
			_movingSpeed = 5.f;
			_speedupTime = 0.f;
			_playerItem[ITEMTYPE::SPEEDUP] = false;
		}
	}
}

void Player::UpdateChild()
{
	if (_eCurMoveDir != MOVE_END && !_isMoveStop)
	{
		_movingSec += Timer::Get_Instance()->Get_DeltaTime();
		if (_movingSec > 1.f)
		{
			_movingSec = 0.f;
			_isMoveStop = true;

			_rightLegRot = -35.f;
			_leftLegRot = 35.f;
			_isLegMius = false;

			_rightArmRot = -35.f;
			_leftArmRot = 35.f;
			_isArmMius = false;
		}
	}

	if (_isJump || !_isMoveStop)
	{
		// leg
		if (_rightLegRot > 35.f && !_isLegMius)
		{
			_isLegMius = true;
		}
		else if (_rightLegRot < -35.f && _isLegMius)
			_isLegMius = false;
		if (_isLegMius)
		{
			_rightLegRot -= Timer::Get_Instance()->Get_DeltaTime() * 100.f;
			_leftLegRot += Timer::Get_Instance()->Get_DeltaTime() * 100.f;
		}
		else
		{
			_rightLegRot += Timer::Get_Instance()->Get_DeltaTime() * 100.f;
			_leftLegRot -= Timer::Get_Instance()->Get_DeltaTime() * 100.f;
		}

		// arm
		if (_leftArmRot > 35.f && !_isArmMius)
		{
			_isArmMius = true;
		}
		else if (_leftArmRot < -35.f && _isArmMius)
			_isArmMius = false;
		if (_isArmMius)
		{
			_leftArmRot -= Timer::Get_Instance()->Get_DeltaTime() * 100.f;
			_rightArmRot += Timer::Get_Instance()->Get_DeltaTime() * 100.f;
		}
		else
		{
			_leftArmRot += Timer::Get_Instance()->Get_DeltaTime() * 100.f;
			_rightArmRot -= Timer::Get_Instance()->Get_DeltaTime() * 100.f;
		}
	}
}

void Player::RenderChild(GLuint _program)
{
	// head
	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 t1 = glm::mat4(1.f);
		glm::mat4 t2 = glm::mat4(1.f);

		t1 = glm::translate(t1, glm::vec3(trans[3][0], trans[3][1], trans[3][2]));
		t2 = glm::translate(t2, glm::vec3(0.f, 0.3f, 0.f));

		childMat = t1 * t2 * static_cast<Cube*>(_head)->scale;
		static_cast<Cube*>(_head)->SetFinalMat(childMat);
		static_cast<Cube*>(_head)->RenderFinalMatrix(_program);
	}

	// arm
	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 t1 = glm::mat4(1.f);
		glm::mat4 t2 = glm::mat4(1.f);
		glm::mat4 r = glm::mat4(1.f);

		t1 = glm::translate(t1, glm::vec3(trans[3][0], trans[3][1], trans[3][2]));
		t2 = glm::translate(t2, glm::vec3(-0.2f, 0.0f, 0.f));
		if (_isJump || !_isMoveStop)
			r = glm::rotate(r, glm::radians(_leftArmRot), glm::vec3(1.f, 0.f, 0.f));

		childMat = t1 * r * t2 * static_cast<Cube*>(_leftArm)->scale;
		static_cast<Cube*>(_leftArm)->SetFinalMat(childMat);
		static_cast<Cube*>(_leftArm)->RenderFinalMatrix(_program);
	}

	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 t1 = glm::mat4(1.f);
		glm::mat4 t2 = glm::mat4(1.f);
		glm::mat4 r = glm::mat4(1.f);

		t1 = glm::translate(t1, glm::vec3(trans[3][0], trans[3][1], trans[3][2]));
		t2 = glm::translate(t2, glm::vec3(0.2f, 0.0f, 0.f));
		if (_isJump || !_isMoveStop)
			r = glm::rotate(r, glm::radians(_rightArmRot), glm::vec3(1.f, 0.f, 0.f));

		childMat = t1 * r * t2 * static_cast<Cube*>(_rightArm)->scale;
		static_cast<Cube*>(_rightArm)->SetFinalMat(childMat);
		static_cast<Cube*>(_rightArm)->RenderFinalMatrix(_program);
	}

	// leg
	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 t1 = glm::mat4(1.f);
		glm::mat4 t2 = glm::mat4(1.f);
		glm::mat4 r = glm::mat4(1.f);

		t1 = glm::translate(t1, glm::vec3(trans[3][0], trans[3][1], trans[3][2]));
		t2 = glm::translate(t2, glm::vec3(-0.1f, -0.2f, 0.f));
		if (_isJump || !_isMoveStop)
			r = glm::rotate(r, glm::radians(_leftLegRot), glm::vec3(1.f, 0.f, 0.f));

		childMat = t1 * r * t2 * static_cast<Cube*>(_leftLeg)->scale;
		static_cast<Cube*>(_leftLeg)->SetFinalMat(childMat);
		static_cast<Cube*>(_leftLeg)->RenderFinalMatrix(_program);
	}

	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 t1 = glm::mat4(1.f);
		glm::mat4 t2 = glm::mat4(1.f);
		glm::mat4 r = glm::mat4(1.f);

		t1 = glm::translate(t1, glm::vec3(trans[3][0], trans[3][1], trans[3][2]));
		t2 = glm::translate(t2, glm::vec3(0.1f, -0.2f, 0.f));
		if (_isJump || !_isMoveStop)
			r = glm::rotate(r, glm::radians(_rightLegRot), glm::vec3(1.f, 0.f, 0.f));

		childMat = t1 * r * t2 * static_cast<Cube*>(_rightLeg)->scale;
		static_cast<Cube*>(_rightLeg)->SetFinalMat(childMat);
		static_cast<Cube*>(_rightLeg)->RenderFinalMatrix(_program);
	}
}
