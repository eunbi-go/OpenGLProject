#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__
#include "Cube.h"

class Item : public Cube
{
public:
	Item();
	virtual ~Item();

public:
	enum TYPE { ALPHA, SPEEDUP, LIGHT };

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(GLuint _program) override;
	virtual void Release() override;
};

#endif