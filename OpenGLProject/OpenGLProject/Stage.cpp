#include "stdafx.h"
#include "Stage.h"
#include "Object.h"
#include "Cube.h"
#include "Player.h"
#include "Item.h"

#include "ObjectManager.h"
#include "CollisionManager.h"

Stage::Stage()
{
}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	// Player
	_player = new Player;
	_player->Initialize();
	static_cast<Cube*>(_player)->SetPos(glm::vec3(0.0, 0.0, 0));
	static_cast<Cube*>(_player)->SetScale(glm::vec3(1.f, 1.f, 1.f));
	ObjectManager::Get_Instance()->Add_Object(_player, OBJID::PLAYER);

	{
		// Test Block
		Object* obj = nullptr;
		obj = new Cube;
		obj->Initialize();
		static_cast<Cube*>(obj)->SetPos(glm::vec3(0.5, 0.0, 0.0));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
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
