#pragma once

#ifndef __COLLISIONMANAGER_H__
#define __COLLISIONMANAGER_H__

class Object;

class CollisionManager
{
private:
	CollisionManager();
	~CollisionManager();

public:
	void Collision_PlayerToBlock(Object* player, list<Object*> src);
	void Collision_PlayerToItem(Object* player, list<Object*> src);
	void Collision_PlayerToBullet(Object* player, list<Object*> src);
	void Collision_PlayerToEnemy(Object* player, list<Object*> src);

private:
	bool IsCollision(CollisionBox* obj1, CollisionBox* obj2);

public:
	static CollisionManager* Get_Instance()
	{
		if (!_pInstance)
			_pInstance = new CollisionManager;
		return _pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(_pInstance);
	}

private:
	static CollisionManager* _pInstance;

};



#endif