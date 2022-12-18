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
	enum SCENEID {
		STAGE, SCENE_END
	};

public:
	void Scene_Change(SCENEID _eScene);
	void Update();
	void Late_Update();
	void Render(GLuint _program, GLuint _texProgram);
	void Release();

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

	Scene*				_pScene;
	SCENEID				_ePreScene;
	SCENEID				_eCurScene;
};


#endif // !__SCENEMANAGER_H__


