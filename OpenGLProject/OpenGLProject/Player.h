#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Cube.h"
class Player : public Cube
{
public:
	Player();
	virtual ~Player();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(GLuint _program) override;
	virtual void Release() override;

private:
	void ApplyItemEffect();

public:
	bool GetIsCollision() { return _isCollision; }
	bool GetIsMove() { return _isMove; }
	bool GetIsLeft() { return _isLeftCollision; }
	bool GetIsRight() { return _isRightCollision; }
	bool GetIsForward() { return _isForwardCollision; }
	bool GetIsBack() { return _isBackCollision; }

public:
	void SetItemOn(ITEMTYPE i) { _playerItem[i] = true; }	// test¿ë
	void SetIsMove(bool value) { _isMove = value; }
	void SetIsLeft(bool value) { _isLeftCollision = value; }
	void SetIsRight(bool value) { _isRightCollision = value; }
	void SetIsForward(bool value) { _isForwardCollision = value; }
	void SetIsBack(bool value) { _isBackCollision = value; }

private:
	array<bool, ITEMTYPE::ITEM_END> _playerItem = { false, };

	bool		_isCollision = true;
	bool		_isMove = true;

	GLfloat		_alphaTime = 0.f;
	GLfloat		_speedupTime = 0.f;
	GLfloat		_lightTime = 0.f;

	bool		_isLeftCollision = false;
	bool		_isRightCollision = false;
	bool		_isForwardCollision = false;
	bool		_isBackCollision = false;
};

#endif // !__PLAYER_H__