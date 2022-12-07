#include "stdafx.h"
#include "MainGame.h"
#include "SceneManager.h"
MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	SceneManager::Get_Instance()->Scene_Change(SceneManager::SCENEID::STAGE);
}

void MainGame::Update()
{
	SceneManager::Get_Instance()->Update();
}

void MainGame::Late_Update()
{
	SceneManager::Get_Instance()->Late_Update();
}

void MainGame::Render(GLuint _program)
{
	SceneManager::Get_Instance()->Render(_program);
}

void MainGame::Release()
{
}
