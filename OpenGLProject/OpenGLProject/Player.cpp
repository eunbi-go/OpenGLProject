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
	UpdateBuffer();
}

int Player::Update()
{
	if (_isJump) Jump();

	ApplyItemEffect();

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
}

void Player::Release()
{
}

void Player::ApplyItemEffect()
{
	// ALPHA
	if (_playerItem[ITEMTYPE::ALPHA]) {
		_alphaTime += Timer::Get_Instance()->Get_DeltaTime();

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
	
	// LIGHT

}
