#include "stdafx.h"
#include "Stage.h"
#include "Object.h"
#include "Cube.h"
#include "Player.h"
#include "Item.h"
#include "MovingEnemy.h"
#include "AttackEnemy.h"

#include "CollisionManager.h"
#include "ObjectManager.h"

Stage::Stage()
{
}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	{
		// Player
		Object* obj = nullptr;
		obj = new Player;
		obj->Initialize();
		static_cast<Cube*>(obj)->SetPos(glm::vec3(0.0, 0.0, 0));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.2f);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::PLAYER);
	}

	//{
	//	// Enemy
	//	Object* obj = nullptr;
	//	obj = new AttackEnemy;
	//	obj->Initialize();
	//	static_cast<Cube*>(obj)->SetPos(glm::vec3(-1.3, 0.0, -2.0));
	//	static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
	//	ObjectManager::Get_Instance()->Add_Object(obj, OBJID::ENEMY);
	//}

	{
		// Block
		Object* obj = nullptr;
		obj = new Cube;
		obj->Initialize();
		static_cast<Cube*>(obj)->SetPos(glm::vec3(0.5, 0.0, 0.0));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(2.f, 2.f, 2.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.25f);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::BLOCK);
	}

	{
		// Block
		Object* obj = nullptr;
		obj = new Cube;
		obj->Initialize();
		static_cast<Cube*>(obj)->SetPos(glm::vec3(0.5, 0.0, 0.5));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(2.f, 2.f, 2.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.25f);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::BLOCK);
	}

	{
		// Block
		Object* obj = nullptr;
		obj = new Cube;
		obj->Initialize();
		static_cast<Cube*>(obj)->SetPos(glm::vec3(0.5, 0.0, 1.0));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(2.f, 2.f, 2.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.25f);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::BLOCK);
	}
}

void Stage::Update()
{
	ObjectManager::Get_Instance()->Update();
}

void Stage::Late_update()
{
	ObjectManager::Get_Instance()->Late_Update();

	CollisionManager::Get_Instance()->Collision_PlayerToBlock(
		ObjectManager::Get_Instance()->Get_Player(), ObjectManager::Get_Instance()->Get_List(OBJID::BLOCK));

	CollisionManager::Get_Instance()->Collision_PlayerToBullet(
		ObjectManager::Get_Instance()->Get_Player(), ObjectManager::Get_Instance()->Get_List(OBJID::ENEMY));

	CollisionManager::Get_Instance()->Collision_PlayerToItem(
		ObjectManager::Get_Instance()->Get_Player(), ObjectManager::Get_Instance()->Get_List(OBJID::ITEM));

}

void Stage::Render(GLuint _program)
{
	ObjectManager::Get_Instance()->Render(_program);
}

void Stage::Release()
{
}
