#include "stdafx.h"
#include "SceneManager.h"
#include "Stage.h"

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
		SAFE_DELETE(_pScene);

		switch (_eCurScene)
		{
		case SceneManager::STAGE:
			_pScene = new Stage;
			break;
		}
		_pScene->Initialize();
		_ePreScene = _eCurScene;
	}
}

void SceneManager::Update()
{
	_pScene->Update();
}

void SceneManager::Late_Update()
{
	_pScene->Late_update();
}

void SceneManager::Render(GLuint _program, GLuint _texProgram)
{
	_pScene->Render(_program, _texProgram);
}

void SceneManager::Release()
{
	SAFE_DELETE(_pScene);
}
