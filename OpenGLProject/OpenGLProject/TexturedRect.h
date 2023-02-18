#pragma once

#ifndef __TEXTUREDRECT_H__
#define __TEXTUREDRECT_H__

#include "Object.h"

class TexturedRect : public Object
{
public:
	TexturedRect();
	virtual ~TexturedRect();

public:
	virtual void Initialize() override;
	virtual int Update(float deltaTime) override;
	virtual void Late_Update(float deltaTime) override;
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

public:
	void UpdateBuffer();
	void UpdateButtonBuffer();

public:
	void SetTexType(TEX_TYPE type) { _type = type; }

public:
	unsigned int VBO = 0, VAO = 0;
	unsigned int texture = 0;
	TEX_TYPE	_type = TEX_TYPE_END;
};

#endif // !__TEXTUREDRECT_H__
