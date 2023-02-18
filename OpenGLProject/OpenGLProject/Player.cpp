#include "stdafx.h"
#include "Player.h"
#include "Timer.h"
#include "KeyManager.h"
#include "Camera.h"

random_device rdAColor;
mt19937 genAColor(rdAColor());
uniform_real_distribution<> randomAC(0.0, 1.0);

Player::Player()
{
	_movingSpeed = 3.f;
}

Player::~Player()
{
	Release();
}

void Player::Initialize()
{
	SetScale(glm::vec3(0.9f, 0.8f, 0.9f));
	_movingSpeed = 3.f;

	Cube::Initialize();

	_leftLeg = new Cube;
	static_cast<Cube*>(_leftLeg)->SetScale(glm::vec3(0.3f, 0.8f, 0.3f));
	static_cast<Cube*>(_leftLeg)->SetColor(1.0f, 0.f, 1.0f);
	_leftLeg->Initialize();

	_rightLeg = new Cube;
	static_cast<Cube*>(_rightLeg)->SetScale(glm::vec3(0.3f, 0.8f, 0.3f));
	static_cast<Cube*>(_rightLeg)->SetColor(1.0f, 0.f, 1.0f);
	_rightLeg->Initialize();

	_leftArm = new Cube;
	static_cast<Cube*>(_leftArm)->SetScale(glm::vec3(0.2f, 0.6f, 0.2f));
	static_cast<Cube*>(_leftArm)->SetColor(0.f, 0.f, 1.f);
	_leftArm->Initialize();

	_rightArm = new Cube;
	static_cast<Cube*>(_rightArm)->SetScale(glm::vec3(0.2f, 0.6f, 0.2f));
	static_cast<Cube*>(_rightArm)->SetColor(0.f, 0.f, 1.f);
	_rightArm->Initialize();

	_head = new Cube;
	static_cast<Cube*>(_head)->SetScale(glm::vec3(0.7f, 0.7f, 0.7f));
	static_cast<Cube*>(_head)->SetColor(0.5f, 0.0f, 0.7f);
	static_cast<Cube*>(_head)->SetParent(static_cast<Cube*>(this));
	_head->Initialize();
}

int Player::Update(float deltaTime)
{
	if (_isJump) Jump();

	else if (_isMoveStop)
	{
		_rightLegRot = -35.f;
		_leftLegRot = 35.f;
		_isLegMius = false;
	}

	// 殿加款悼 贸府
	glm::vec3 pos = glm::vec3(0.f);

	if (KeyManager::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		_isMoveStop = false;
		_isMove = true;
		_trans = glm::translate(_trans, glm::vec3(-deltaTime * _movingSpeed, 0.f, 0.f));

	}
	if (KeyManager::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		_isMoveStop = false;
		_isMove = true;
		_trans = glm::translate(_trans, glm::vec3(deltaTime * _movingSpeed, 0.f, 0.f));
	}
	if (KeyManager::Get_Instance()->Key_Pressing(VK_UP))
	{
		_isMoveStop = false;
		_isMove = true;
		_trans = glm::translate(_trans, glm::vec3(0.f, 0.f, deltaTime * -_movingSpeed));
	}
	if (KeyManager::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		_isMoveStop = false;
		_isMove = true;
		_trans = glm::translate(_trans, glm::vec3(0.f, 0.f, deltaTime * _movingSpeed));
	}
	if (KeyManager::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		_isJump = true;
	}

	pos = { _trans[3][0], _trans[3][1], _trans[3][2] };
	Camera::Get_Instance()->SetPos(pos);

	ApplyItemEffect();

	UpdateChild();

	return Cube::Update(deltaTime);
}

void Player::Late_Update(float deltaTime)
{
}

void Player::Render(GLuint _program, GLuint _texProgram)
{
	glm::mat4 finalMat = _trans * _rotation* _scale;
	unsigned int modelLocation = glGetUniformLocation(_program, "modelTransform");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(finalMat));
	glBindVertexArray(_vaoHandle);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, 0);

	RenderChild(_program);
}

void Player::Release()
{
	SAFE_DELETE(_head);
	SAFE_DELETE(_leftLeg);
	SAFE_DELETE(_rightLeg);
	SAFE_DELETE(_leftArm);
	SAFE_DELETE(_rightArm);
}

void Player::ApplyItemEffect()
{
	// ALPHA
	if (_playerItem[ITEMTYPE::ALPHA])
	{
		_alphaTime += Timer::Get_Instance()->Get_DeltaTime();
		
		SetColor((float)randomAC(genAColor), (float)randomAC(genAColor), (float)randomAC(genAColor));
		UpdateBuffer();
		
		static_cast<Cube*>(_leftLeg)->SetColor((float)randomAC(genAColor), (float)randomAC(genAColor), (float)randomAC(genAColor));
		static_cast<Cube*>(_leftLeg)->UpdateBuffer();

		static_cast<Cube*>(_rightLeg)->SetColor((float)randomAC(genAColor), (float)randomAC(genAColor), (float)randomAC(genAColor));
		static_cast<Cube*>(_rightLeg)->UpdateBuffer();

		static_cast<Cube*>(_leftArm)->SetColor((float)randomAC(genAColor), (float)randomAC(genAColor), (float)randomAC(genAColor));
		static_cast<Cube*>(_leftArm)->UpdateBuffer();

		static_cast<Cube*>(_rightArm)->SetColor((float)randomAC(genAColor), (float)randomAC(genAColor), (float)randomAC(genAColor));
		static_cast<Cube*>(_rightArm)->UpdateBuffer();

		static_cast<Cube*>(_head)->SetColor((float)randomAC(genAColor), (float)randomAC(genAColor), (float)randomAC(genAColor));
		static_cast<Cube*>(_head)->UpdateBuffer();

		if (_alphaTime >= 5.f)
		{
			SetColor(0.0f, 1.0f, 0.5f);
			UpdateBuffer();

			static_cast<Cube*>(_leftLeg)->SetColor(1.0f, 0.f, 1.0f);
			_leftLeg->Initialize();

			static_cast<Cube*>(_rightLeg)->SetColor(1.0f, 0.f, 1.0f);
			_rightLeg->Initialize();

			static_cast<Cube*>(_leftArm)->SetColor(0.f, 0.f, 1.f);
			_leftArm->Initialize();

			static_cast<Cube*>(_rightArm)->SetColor(0.f, 0.f, 1.f);
			_rightArm->Initialize();

			static_cast<Cube*>(_head)->SetColor(0.5f, 0.0f, 0.7f);
			_head->Initialize();

			_alphaTime = 0.f;
			_playerItem[ITEMTYPE::ALPHA] = false;
		}
	}

	// SPEEDUP
	if (_playerItem[ITEMTYPE::SPEEDUP]) {
		_speedupTime += Timer::Get_Instance()->Get_DeltaTime();
	
		_movingSpeed = 30.f;
	
		if (_speedupTime >= 5.f) {
			_movingSpeed = 20.f;
			_speedupTime = 0.f;
			_isSpeedUp = false;
			_playerItem[ITEMTYPE::SPEEDUP] = false;
		}
	}
}

void Player::UpdateChild()
{
	if (_isMove)
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
	glm::mat4 parentTrans = glm::mat4(1.f);
	parentTrans = static_cast<Cube*>(_head)->GetParent()->Get_Translation();

	// head
	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 trans = glm::mat4(1.f);

		trans = glm::translate(trans, glm::vec3(0.f, 0.3f, 0.f));

		childMat = parentTrans * trans * static_cast<Cube*>(_head)->_scale;
		static_cast<Cube*>(_head)->SetFinalMat(childMat);
		static_cast<Cube*>(_head)->RenderFinalMatrix(_program);
	}

	// arm
	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 trans = glm::mat4(1.f);
		glm::mat4 rotate = glm::mat4(1.f);

		trans = glm::translate(trans, glm::vec3(-0.2f, 0.0f, 0.f));
		if (_isJump || !_isMoveStop)
			rotate = glm::rotate(rotate, glm::radians((float)_leftArmRot), glm::vec3(1.f, 0.f, 0.f));

		childMat = parentTrans * rotate * trans * static_cast<Cube*>(_leftArm)->_scale;
		static_cast<Cube*>(_leftArm)->SetFinalMat(childMat);
		static_cast<Cube*>(_leftArm)->RenderFinalMatrix(_program);
	}

	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 trans = glm::mat4(1.f);
		glm::mat4 rotate = glm::mat4(1.f);

		trans = glm::translate(trans, glm::vec3(0.2f, 0.0f, 0.f));
		if (_isJump || !_isMoveStop)
			rotate = glm::rotate(rotate, glm::radians((float)_rightArmRot), glm::vec3(1.f, 0.f, 0.f));

		childMat = parentTrans * rotate * trans * static_cast<Cube*>(_rightArm)->_scale;
		static_cast<Cube*>(_rightArm)->SetFinalMat(childMat);
		static_cast<Cube*>(_rightArm)->RenderFinalMatrix(_program);
	}

	// leg
	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 trans = glm::mat4(1.f);
		glm::mat4 rotate = glm::mat4(1.f);

		trans = glm::translate(trans, glm::vec3(-0.1f, -0.2f, 0.f));
		if (_isJump || !_isMoveStop)
			rotate = glm::rotate(rotate, glm::radians((float)_leftLegRot), glm::vec3(1.f, 0.f, 0.f));

		childMat = parentTrans * rotate * trans * static_cast<Cube*>(_leftLeg)->_scale;
		static_cast<Cube*>(_leftLeg)->SetFinalMat(childMat);
		static_cast<Cube*>(_leftLeg)->RenderFinalMatrix(_program);
	}

	{
		glm::mat4 childMat = glm::mat4(1.f);
		glm::mat4 trans = glm::mat4(1.f);
		glm::mat4 rotate = glm::mat4(1.f);

		trans = glm::translate(trans, glm::vec3(0.1f, -0.2f, 0.f));
		if (_isJump || !_isMoveStop)
			rotate = glm::rotate(rotate, glm::radians((float)_rightLegRot), glm::vec3(1.f, 0.f, 0.f));

		childMat = parentTrans * rotate * trans * static_cast<Cube*>(_rightLeg)->_scale;
		static_cast<Cube*>(_rightLeg)->SetFinalMat(childMat);
		static_cast<Cube*>(_rightLeg)->RenderFinalMatrix(_program);
	}
}
