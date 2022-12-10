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
	void SetItemOn(ITEMTYPE i) { _playerItem[i] = true; }	// test¿ë

private:
	array<bool, ITEMTYPE::ITEM_END> _playerItem = { false, };

	GLfloat		_alphaTime = 0.f;
	GLfloat		_speedupTime = 0.f;
	GLfloat		_lightTime = 0.f;
};

#endif // !__PLAYER_H__