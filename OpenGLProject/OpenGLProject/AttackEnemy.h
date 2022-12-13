#pragma once

#ifndef __ATTACKENEMY_H__
#define __ATTACKENEMY_H__

#include "Cube.h"

class AttackEnemy : public Cube
{
public:
	AttackEnemy();
	virtual ~AttackEnemy();

	enum DIR { RIGHT, LEFT, DIR_END };

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(GLuint _program) override;
	virtual void Release() override;

private:
	void RenderChild(GLuint _program);

private:
	class Object* _leftLeg;
	class Object* _rightLeg;
	class Object* _ring;

	float	_ringRot = 0.f;
};

#endif // !__ATTACKENEMY_H__