#pragma once

#ifndef __CUBE_H__
#define __CUBE_H__

#include "Object.h"

class Cube : public Object
{
public:
	Cube();
	virtual ~Cube();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(GLuint _program) override;
	virtual void Release() override;

public:
	void UpdateBuffer();

public:
	void SetPos(glm::vec3 pos) { trans = glm::mat4(1.0f); trans = glm::translate(trans, glm::vec3(pos.x, pos.y, pos.z)); }
	void SetScale(glm::vec3 s) { scale = glm::scale(scale, glm::vec3(s.x, s.y, s.z)); }
	void SetRotateX(float radian) { rotateRadian = radian;  rotation = glm::rotate(rotation, glm::radians(rotateRadian), glm::vec3(1.0, 0.0, 0.0)); }
	void SetRotateY(float radian) { rotateRadian = radian;  rotation = glm::rotate(rotation, glm::radians(rotateRadian), glm::vec3(0.0, 1.0, 0.0)); }
	void SetRotateZ(float radian) { rotateRadian = radian;  rotation = glm::rotate(rotation, glm::radians(rotateRadian), glm::vec3(0.0, 0.0, 1.0)); }


public:
	GLuint vaoHandle;
	GLuint vboHandles[2];
	GLuint indexBufferObject;

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 finalMat = glm::mat4(1.0f);

	GLfloat rotateRadian;
};

#endif // !__CUBE_H__