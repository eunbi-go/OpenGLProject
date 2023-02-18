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
	virtual int Update(float deltaTime) override;
	virtual void Late_Update(float deltaTime) override;
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

public:
	void UpdateBuffer();
	void RenderFinalMatrix(GLuint _program);

public:
	void Move();
	void Move2();
	void SetMoveDir(MOVE move) { _eCurMoveDir = move; }

	void Jump();


public:
	glm::mat4 Get_Translation() { return _trans; }
	float GetX() { return _trans[3][0]; }
	float GetY() { return _trans[3][1]; }
	float GetZ() { return _trans[3][2]; }
	float GetBoundingSize() { return _boundingSize; }
	MOVE GetMoveDir() { return _eCurMoveDir; }
	Cube* GetParent() { return _parent; }

public:
	void SetPos(glm::vec3 pos) { _trans = glm::mat4(1.0f); _trans = glm::translate(_trans, glm::vec3(pos.x, pos.y, pos.z)); }
	void SetScale(glm::vec3 s) { _scale = glm::scale(_scale, glm::vec3(s.x, s.y, s.z)); }
	void SetRotateX(float radian) { _rotateRadian = radian;  _rotation = glm::rotate(_rotation, glm::radians(_rotateRadian), glm::vec3(1.0, 0.0, 0.0)); }
	void SetRotateY(float radian) { _rotateRadian = radian;  _rotation = glm::rotate(_rotation, glm::radians(_rotateRadian), glm::vec3(0.0, 1.0, 0.0)); }
	void SetRotateZ(float radian) { _rotateRadian = radian;  _rotation = glm::rotate(_rotation, glm::radians(_rotateRadian), glm::vec3(0.0, 0.0, 1.0)); }
	void SetFinalMat(glm::mat4 finalM) { _finalMat = finalM; }
	void SetBoundingSize(float size) { _boundingSize = size; }
	void SetColor(float x, float y, float z);
	void SetParent(Cube* parent) { _parent = parent; }

public:
	GLuint _vaoHandle = 0;
	GLuint _vboHandles[2] = {};
	GLuint _indexBufferObject = 0;

	GLfloat	_colors[24] = {};

	glm::mat4 _trans = glm::mat4(1.0f);
	glm::mat4 _rotation = glm::mat4(1.0f);
	glm::mat4 _scale = glm::mat4(1.0f);
	glm::mat4 _finalMat = glm::mat4(1.0f);

	GLfloat _rotateRadian = 0.f;
	GLfloat _movingSpeed = 5.f;

	MOVE	_ePreMoveDir = MOVE::MOVE_END;
	MOVE	_eCurMoveDir = MOVE::MOVE_END;

	bool	_isJump = false;
	GLfloat	_jumpTime = 0.f;
	GLfloat	_jumpHeight = 0.f;
	GLfloat	_jumpPower = 4.f;

	float	_boundingSize = 0.2f;

	glm::vec3 _speed = glm::vec3(1.f);

	Cube* _parent = nullptr;
};

#endif // !__CUBE_H__