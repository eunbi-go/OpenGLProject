#pragma once

#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__
class Object;

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

public:
	void Update(float deltaTime);
	void Late_Update(float deltaTime);
	void Render(GLuint _program, GLuint _texProgram);
	void Release();

public:
	void Add_Object(Object* _pObj, OBJID _eID) { _listObj[_eID].emplace_back(_pObj); }

public:
	Object* Get_Player();
	list<Object*>& Get_List(OBJID id) { return _listObj[id]; }

public:
	void SetTexProgram(GLuint program) { _texProgram = program; }

public:
	static ObjectManager* Get_Instance()
	{
		if (!_pInstance)
			_pInstance = new ObjectManager;
		return _pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(_pInstance);
	}


private:
	list<Object*>				_listObj[OBJID::OBJID_END];

	static ObjectManager* _pInstance;
	GLuint _texProgram;
};

#endif // !__OBJECTMANAGER_H__
