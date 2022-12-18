#pragma once

#ifndef __OBJECT_H__
#define __OBJECT_H__


class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(GLuint _program) = 0;
	virtual void Release() = 0;

public:
	CollisionBox GetCollisionBox() { return _collisionBox; }

public:
	void SetDead() { _isDead = true; }

protected:
	CollisionBox	_collisionBox;
	bool	_isDead = false;
};

#endif // !__OBJECT_H__