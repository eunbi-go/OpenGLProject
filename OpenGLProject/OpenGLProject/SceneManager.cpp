#include "stdafx.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Logo.h"

SceneManager* SceneManager::_pInstance = nullptr;

SceneManager::SceneManager()
	: _pScene(nullptr), _eCurScene(SCENEID::SCENE_END), _ePreScene(SCENEID::SCENE_END)
{
}

SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::Scene_Change(SCENEID _eScene)
{
	_eCurScene = _eScene;
	if (_ePreScene != _eCurScene)
	{
		if (_pScene!= nullptr)
			_pScene->Release();
		SAFE_DELETE(_pScene);

		switch (_eCurScene)
		{
		case LOGO:
			_pScene = new Logo;
			break;

		case STAGE:
			_pScene = new Stage;
			break;
		}
		_pScene->Initialize();
		_ePreScene = _eCurScene;
	}
}

void SceneManager::Update(float deltaTime)
{
	_pScene->Update(deltaTime);
}

void SceneManager::Late_Update(float deltaTime)
{
	_pScene->Late_update(deltaTime);
}

void SceneManager::Render(GLuint _program, GLuint _texProgram)
{
	_pScene->Render(_program, _texProgram);
}

void SceneManager::Release()
{
	SAFE_DELETE(_pScene);
}
