#include "stdafx.h"
#include "CollisionManager.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Cube.h"

CollisionManager* CollisionManager::_pInstance = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::CollisionCheck(Object* player, list<Object*> src)
{
	for (auto& Src : src)
	{
		CollisionBox c1, c2;
		c1.maxX = static_cast<Cube*>(player)->GetX() + static_cast<Cube*>(player)->GetBoundingSize();
		c1.minX = static_cast<Cube*>(player)->GetX() - static_cast<Cube*>(player)->GetBoundingSize();
		c1.maxZ = static_cast<Cube*>(player)->GetZ() + static_cast<Cube*>(player)->GetBoundingSize();
		c1.minZ = static_cast<Cube*>(player)->GetZ() - static_cast<Cube*>(player)->GetBoundingSize();

		c2.maxX = static_cast<Cube*>(Src)->GetX() + static_cast<Cube*>(Src)->GetBoundingSize();
		c2.minX = static_cast<Cube*>(Src)->GetX() - static_cast<Cube*>(Src)->GetBoundingSize();
		c2.maxZ = static_cast<Cube*>(Src)->GetZ() + static_cast<Cube*>(Src)->GetBoundingSize();
		c2.minZ = static_cast<Cube*>(Src)->GetZ() - static_cast<Cube*>(Src)->GetBoundingSize();

		if (IsCollision(&c1, &c2)) {
			int a = 0;
		}
	}
}

bool CollisionManager::IsCollision(CollisionBox* obj1, CollisionBox* obj2)
{
	obj1->lengthX = abs(obj1->maxX - obj1->minX);
	obj1->lengthZ = abs(obj1->maxZ - obj1->minZ);

	obj2->lengthX = abs(obj2->maxX - obj2->minX);
	obj2->lengthZ = abs(obj2->maxZ - obj2->minZ);

	if ((obj2->minX + obj2->lengthX > obj1->minX + obj1->lengthX) && (obj1->minX + obj1->lengthX > obj2->minX) &&
		(obj2->minZ + obj2->lengthZ > obj1->minZ) && (obj1->minZ + obj1->lengthZ > obj2->minZ)) 
		return true;

	return false;
}
