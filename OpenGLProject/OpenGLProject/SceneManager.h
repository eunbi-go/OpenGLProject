#pragma once

#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	
public:


public:
	void Scene_Change(SCENEID _eScene);
	void Update(float deltaTime);
	void Late_Update(float deltaTime);
	void Render(GLuint _program, GLuint _texProgram);
	void Release();

public:
	SCENEID GetCurrentSceneType() { return _eCurScene; }

public:
	static SceneManager* Get_Instance()
	{
		if (!_pInstance)
			_pInstance = new SceneManager;
		return _pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(_pInstance);
	}


private:
	static SceneManager* _pInstance;

	Scene*				_pScene = nullptr;
	SCENEID				_ePreScene = SCENEID::SCENE_END;
	SCENEID				_eCurScene = SCENEID::SCENE_END;
};


#endif // !__SCENEMANAGER_H__


