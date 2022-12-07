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
};

#endif // !__PLAYER_H__