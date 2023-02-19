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
	virtual int Update(float deltaTime) override;
	virtual void Late_Update(float deltaTime) override;
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

private:
	void ApplyItemEffect();
	
	void UpdateChild();
	void RenderChild(GLuint _program);

public:
	bool GetIsCollision() { return _isCollision; }
	bool GetIsMove() { return _isMove; }
	bool GetIsLeft() { return _isLeftCollision; }
	bool GetIsRight() { return _isRightCollision; }
	bool GetIsForward() { return _isForwardCollision; }
	bool GetIsBack() { return _isBackCollision; }
	bool GetIsRespawn() { return _isRespawn; }
	bool GetIsSpeedUp() { return _isSpeedUp; }
	bool GetIsAlpha() { return _playerItem[ITEMTYPE::ALPHA]; }

public:
	void SetItemOn(ITEMTYPE i) { _playerItem[i] = true; }
	void SetIsMove(bool value) { _isMove = value; }
	void SetIsLeft(bool value) { _isLeftCollision = value; }
	void SetIsRight(bool value) { _isRightCollision = value; }
	void SetIsForward(bool value) { _isForwardCollision = value; }
	void SetIsBack(bool value) { _isBackCollision = value; }
	void SetIsRespawn(bool value) { _isRespawn = value; }
	void SetIsSpeedUp(bool value) { _isSpeedUp = value; }

private:
	array<bool, ITEMTYPE::ITEM_END> _playerItem = { false, };

	bool		_isCollision = true;
	bool		_isMove = true;
	bool		_isRespawn = false;
	bool		_isSpeedUp = false;

	float		_alphaTime = 0.f;
	float		_speedupTime = 0.f;
	float		_lightTime = 0.f;

	bool		_isLeftCollision = false;
	bool		_isRightCollision = false;
	bool		_isForwardCollision = false;
	bool		_isBackCollision = false;

	class Object* _head = nullptr;
	class Object* _leftLeg = nullptr;
	class Object* _rightLeg = nullptr;
	class Object* _leftArm = nullptr;
	class Object* _rightArm = nullptr;

	float	_rightLegRot = -35.f;
	float	_leftLegRot = 35.f;
	bool	_isLegMius = false;

	float	_rightArmRot = -35.f;
	float	_leftArmRot = 35.f;
	bool	_isArmMius = false;

	float	_movingSec = 0.f;
	float	_rotSpeed = 100.f;
public:
	bool	_isMoveStop = true;
};

#endif // !__PLAYER_H__