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
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

private:
	void ApplyItemEffect();
	
	void UpdateChild();
	void RenderChild(GLuint _program);

public:
	void SetItemOn(ITEMTYPE i) { _playerItem[i] = true; }	// test¿ë

private:
	array<bool, ITEMTYPE::ITEM_END> _playerItem = { false, };

	GLfloat		_alphaTime = 0.f;
	GLfloat		_speedupTime = 0.f;
	GLfloat		_lightTime = 0.f;

	class Object* _head;
	class Object* _leftLeg;
	class Object* _rightLeg;
	class Object* _leftArm;
	class Object* _rightArm;

	float	_rightLegRot = -35.f;
	float	_leftLegRot = 35.f;
	bool	_isLegMius = false;

	float	_rightArmRot = -35.f;
	float	_leftArmRot = 35.f;
	bool	_isArmMius = false;

	float	_movingSec = 0.f;
public:
	bool	_isMoveStop = true;
};

#endif // !__PLAYER_H__