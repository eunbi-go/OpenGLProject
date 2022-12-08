#include "stdafx.h"
#include "Player.h"

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
