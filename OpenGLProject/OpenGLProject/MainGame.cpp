#include "stdafx.h"
#include "MainGame.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "Timer.h"
#include "KeyManager.h"
#include "Camera.h"

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
	SceneManager::Get_Instance()->Scene_Change(SCENEID::LOGO);
	Timer::Get_Instance()->Ready_CTimeManager();
}

void MainGame::Update()
{
	Timer::Get_Instance()->Update_CTimeManager();
	KeyManager::Get_Instance()->Key_Update();

	float deltaTime = (float)Timer::Get_Instance()->Get_DeltaTime();
	SceneManager::Get_Instance()->Update(deltaTime);
	Camera::Get_Instance()->Update(deltaTime);
}

void MainGame::Late_Update()
{
	float deltaTime = (float)Timer::Get_Instance()->Get_DeltaTime();
	SceneManager::Get_Instance()->Late_Update(deltaTime);
}

void MainGame::Render(GLuint _program, GLuint _texProgram)
{
	SceneManager::Get_Instance()->Render(_program, _texProgram);
}

void MainGame::Release()
{
	SoundManager::Destroy_Instance();
	SceneManager::Get_Instance()->Destroy_Instance();
	ObjectManager::Get_Instance()->Destroy_Instance();
	KeyManager::Get_Instance()->Destroy_Instance();
	Timer::Destroy_Instance();
}

SCENEID MainGame::GetCurrentSceneType()
{
	return SceneManager::Get_Instance()->GetCurrentSceneType();
}

void MainGame::ChangeToStage()
{
	SceneManager::Get_Instance()->Scene_Change(SCENEID::STAGE);
}

Object* MainGame::Get_Player()
{
	return ObjectManager::Get_Instance()->Get_Player();
}

double MainGame::Get_DeltaTime()
{
	return Timer::Get_Instance()->Get_DeltaTime();
}

void MainGame::Start_CameraShake()
{
	Camera::Get_Instance()->SetIsShake(true);
}
