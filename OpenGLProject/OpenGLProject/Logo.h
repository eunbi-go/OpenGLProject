#pragma once

#ifndef __LOGO_H__
#define __LOGO_H__

#include "Scene.h"
class Logo : public Scene
{
public:
	Logo();
	virtual ~Logo();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_update() override;
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;
};

#endif // !__LOGO_H__
