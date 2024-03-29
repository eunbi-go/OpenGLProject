#pragma once

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Cube.h"

class MovingEnemy : public Cube
{
public:
	MovingEnemy();
	virtual ~MovingEnemy();

	enum DIR { RIGHT, LEFT, DIR_END };

public:
	virtual void Initialize() override;
	virtual int Update(float deltaTime) override;
	virtual void Late_Update(float deltaTime) override;
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

private:
	void RenderChild(GLuint _program);

private:
	class Object* _child = nullptr;
	double	_childRot = 0.f;
	DIR	_eDir = DIR_END;
	double	_dirTime = 0.0;
};

#endif // !__ENEMY_H__
