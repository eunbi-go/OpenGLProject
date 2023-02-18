#pragma once

#ifndef __BULLET_H__
#define __BULLET_H__

#include "Cube.h"

class Bullet : public Cube
{
public:
	Bullet();
	virtual ~Bullet();

public:
	virtual void Initialize() override;
	virtual int Update(float deltaTime) override;
	virtual void Late_Update(float deltaTime) override;
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

private:
	double	_lifeTime = 0.f;
};

#endif // !__BULLET_H__