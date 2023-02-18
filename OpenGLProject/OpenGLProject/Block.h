#pragma once
#include "Cube.h"

class Block : public Cube
{
public:
	Block();
	~Block();

public:
	virtual void Initialize() override;
	virtual int Update(float deltaTime) override;
	virtual void Late_Update(float deltaTime) override;
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

};

