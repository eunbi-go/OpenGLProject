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
	virtual void Update(float deltaTime) override;
	virtual void Late_update(float deltaTime) override;
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

private:
	void CreateBlock();
	void CreateEnemy();
	void CreateItem();

	vector<glm::vec3> _blockPos;
	vector<glm::vec3> _movingEnemyPos;
	vector<glm::vec3> _attackEnemyPos;
	vector<glm::vec3> _itemPos;
};

#endif // !__STAGE_H__