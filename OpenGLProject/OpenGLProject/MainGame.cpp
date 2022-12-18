#include "stdafx.h"
#include "MainGame.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "Timer.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	SoundManager::Get_Instance()->Initialize();
	SceneManager::Get_Instance()->Scene_Change(SceneManager::SCENEID::STAGE);
	Timer::Get_Instance()->Ready_CTimeManager();
}

void MainGame::Update()
{
	SceneManager::Get_Instance()->Update();
}

void MainGame::Late_Update()
{
	SceneManager::Get_Instance()->Late_Update();
	Timer::Get_Instance()->Update_CTimeManager();
}

void MainGame::Render(GLuint _program)
{
	SceneManager::Get_Instance()->Render(_program);
}

void MainGame::Release()
{
	Timer::Destroy_Instance();
	SoundManager::Destroy_Instance();
}

Object* MainGame::Get_Player()
{
	return ObjectManager::Get_Instance()->Get_Player();
}

double MainGame::Get_DeltaTime()
{
	return Timer::Get_Instance()->Get_DeltaTime();
}
