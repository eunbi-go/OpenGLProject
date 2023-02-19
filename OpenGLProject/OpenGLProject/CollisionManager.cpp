#include "stdafx.h"
#include "CollisionManager.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Cube.h"
#include "Player.h"
#include "Item.h"
#include "Camera.h"

CollisionManager* CollisionManager::_pInstance = nullptr;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Collision_PlayerToBlock(Object* player, list<Object*> src)
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

		if (static_cast<Player*>(player)->GetIsCollision() && IsCollision(&c1, &c2)) {
			static_cast<Player*>(player)->SetIsMove(false);

			if (static_cast<Cube*>(player)->GetMoveDir() == MOVE::MOVE_RIGHT) {
				static_cast<Player*>(player)->SetIsRight(true);
			}
			else if (static_cast<Cube*>(player)->GetMoveDir() == MOVE::MOVE_LEFT) {
				static_cast<Player*>(player)->SetIsLeft(true);
			}
			else if (static_cast<Cube*>(player)->GetMoveDir() == MOVE::MOVE_FORWARD) {
				static_cast<Player*>(player)->SetIsForward(true);
			}
			else if (static_cast<Cube*>(player)->GetMoveDir() == MOVE::MOVE_BACK) {
				static_cast<Player*>(player)->SetIsBack(true);
			}
		}
	}
}

void CollisionManager::Collision_PlayerToItem(Object* player, list<Object*> src)
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

		if (static_cast<Player*>(player)->GetIsCollision() && IsCollision(&c1, &c2)) {
			if (static_cast<Item*>(Src)->GetItemType() == ALPHA) static_cast<Player*>(player)->SetItemOn(ALPHA);
			else if (static_cast<Item*>(Src)->GetItemType() == SPEEDUP)
			{
				static_cast<Player*>(player)->SetItemOn(SPEEDUP);
				static_cast<Player*>(player)->SetIsSpeedUp(true);
			}

			static_cast<Cube*>(Src)->SetDead();
		}
	}
}

void CollisionManager::Collision_PlayerToBullet(Object* player, list<Object*> src)
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

		if (static_cast<Player*>(player)->GetIsCollision() && IsCollision(&c1, &c2)) 
		{
			static_cast<Cube*>(Src)->SetDead();

			if (static_cast<Player*>(player)->GetIsAlpha())
				break;
			//static_cast<Cube*>(player)->SetPos(glm::vec3(0.0, 0.0, 0));
			//static_cast<Player*>(player)->SetIsRespawn(true);
			Camera::Get_Instance()->SetIsShake(true);
		}
	}
}

void CollisionManager::Collision_PlayerToEnemy(Object* player, list<Object*> src)
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

		if (static_cast<Player*>(player)->GetIsCollision() && IsCollision(&c1, &c2)
			&& !static_cast<Player*>(player)->GetIsAlpha()) {
			//static_cast<Cube*>(Src)->SetDead();
			static_cast<Cube*>(player)->SetPos(glm::vec3(0.0, 0.0, 0));
			static_cast<Player*>(player)->SetIsRespawn(true);
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
