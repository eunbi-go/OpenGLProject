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
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

public:
	void UpdateBuffer();
	void RenderFinalMatrix(GLuint _program);

public:
	void Move();
	void SetMoveDir(MOVE move) { _eCurMoveDir = move; }

	void Jump();

	glm::mat4 Get_Translation() { return trans; }
	float GetX() { return trans[3][0]; }
	float GetY() { return trans[3][1]; }
	float GetZ() { return trans[3][2]; }
	float GetBoundingSize() { return _boundingSize; }
	MOVE GetMoveDir() { return _eCurMoveDir; }

public:
	void SetPos(glm::vec3 pos) { trans = glm::mat4(1.0f); trans = glm::translate(trans, glm::vec3(pos.x, pos.y, pos.z)); }
	void SetScale(glm::vec3 s) { scale = glm::scale(scale, glm::vec3(s.x, s.y, s.z)); }
	void SetRotateX(float radian) { rotateRadian = radian;  rotation = glm::rotate(rotation, glm::radians(rotateRadian), glm::vec3(1.0, 0.0, 0.0)); }
	void SetRotateY(float radian) { rotateRadian = radian;  rotation = glm::rotate(rotation, glm::radians(rotateRadian), glm::vec3(0.0, 1.0, 0.0)); }
	void SetRotateZ(float radian) { rotateRadian = radian;  rotation = glm::rotate(rotation, glm::radians(rotateRadian), glm::vec3(0.0, 0.0, 1.0)); }
	void SetFinalMat(glm::mat4 finalM) { finalMat = finalM; }
	void SetBoundingSize(float size) { _boundingSize = size; }
	void SetColor(float x, float y, float z);

public:
	GLuint vaoHandle;
	GLuint vboHandles[2];
	GLuint indexBufferObject;

	GLfloat	colors[24];

	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 finalMat = glm::mat4(1.0f);

	GLfloat rotateRadian;
	GLfloat _movingSpeed = 5.f;

	MOVE	_ePreMoveDir = MOVE::MOVE_END;
	MOVE	_eCurMoveDir = MOVE::MOVE_END;

	bool	_isJump = false;
	GLfloat	_jumpTime = 0.f;
	GLfloat	_jumpHeight = 0.f;
	GLfloat	_jumpPower = 4.f;

	float	_boundingSize = 0.2f;
};

#endif // !__CUBE_H__