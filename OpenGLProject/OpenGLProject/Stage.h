#pragma once

#ifndef __STAGE_H__
#define __STAGE_H__

#include "Scene.h"

class Stage : public Scene
{
public:
	Stage();
	virtual ~Stage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_update() override;
	virtual void Render(GLuint _program) override;
	virtual void Release() override;
};

#endif // !__STAGE_H__