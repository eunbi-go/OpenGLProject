#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__


class Scene
{
public:
	Scene();
	~Scene();

public:
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Late_update(float deltaTime) = 0;
	virtual void Render(GLuint _program, GLuint _texProgram) = 0;
	virtual void Release() = 0;
};

#endif // !__SCENE_H__
