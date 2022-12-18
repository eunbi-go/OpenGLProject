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
	virtual void Render(GLuint _program, GLuint _texProgram) override;
	virtual void Release() override;

private:
	void CreateBlock();
	void CreateEnemy();
	void CreateItem();

	vector<glm::vec3> BlockPos;
	vector<glm::vec3> MovingEnemyPos;
	vector<glm::vec3> AttackEnemyPos;
	vector<glm::vec3> ItemPos;
};

#endif // !__STAGE_H__