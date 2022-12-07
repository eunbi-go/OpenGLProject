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
	void Render(GLuint _program);
	void Release();

public:
	//GLuint _program;
};

#endif