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
	virtual int Update(float deltaTime) override;
	virtual void Late_Update(float deltaTime) override;
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

private:
	void RenderChild(GLuint _program);
	void Attack();

private:
	class Object* _leftLeg = nullptr;
	class Object* _rightLeg = nullptr;
	class Object* _ring = nullptr;

	double	_ringRot = 0.f;
	double	_attackTime = 0.0;

	glm::mat4	_bulletPos = glm::mat4(1.f);
};

#endif // !__ATTACKENEMY_H__