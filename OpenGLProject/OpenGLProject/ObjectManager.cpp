#include "stdafx.h"
#include "ObjectManager.h"
#include "Object.h"

ObjectManager* ObjectManager::_pInstance = nullptr;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	Release();
}

void ObjectManager::Update(float deltaTime)
{
	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		for (auto iter = _listObj[i].begin(); iter != _listObj[i].end();)
		{
			if (!(*iter))
				continue;
			int isDeath = (*iter)->Update(deltaTime);
			if (isDeath == DEATH)
			{
				SAFE_DELETE(*iter);
				iter = _listObj[i].erase(iter);
			}
			else if (isDeath == ALIVE)
				++iter;
		}
	}

}

void ObjectManager::Late_Update(float deltaTime)
{
	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		for (auto& pObj : _listObj[i])
			pObj->Late_Update(deltaTime);
	}
}

void ObjectManager::Render(GLuint _program, GLuint _texProgram)
{
	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		if (i != OBJID::TEXTURED_RECT)
		{
			glUseProgram(_program);
			for (auto& pObj : _listObj[i])
			{
				if (!pObj)
					continue;
				pObj->Render(_program, _texProgram);
			}
		}
		else
		{
			glUseProgram(_texProgram);
			for (auto& pObj : _listObj[i])
			{
				if (!pObj)
					continue;
				pObj->Render(_program, _texProgram);
			}
		}
	}
}

void ObjectManager::Release()
{
	for (int i = 0; i < OBJID::OBJID_END; ++i)
	{
		for_each(_listObj[i].begin(), _listObj[i].end(), Safe_Delete<Object*>);
		_listObj[i].clear();
	}
}

Object* ObjectManager::Get_Player()
{
	if (_listObj[OBJID::PLAYER].empty()) return nullptr;
	else return _listObj[OBJID::PLAYER].front();
}
