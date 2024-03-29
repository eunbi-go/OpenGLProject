#pragma once

#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(GLuint _program, GLuint _texProgram);
	void Release();

public:
	SCENEID GetCurrentSceneType();
	void ChangeToStage();

public:
	class Object* Get_Player();
	double Get_DeltaTime();
	void Start_CameraShake();
};

#endif