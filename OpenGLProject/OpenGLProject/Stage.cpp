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
	static_cast<Cube*>(_player)->SetColor(COLOR::BLUE);
	static_cast<Cube*>(_player)->SetPos(glm::vec3(0.0, 0.0, 0));
	static_cast<Cube*>(_player)->SetScale(glm::vec3(1.f, 1.f, 1.f));
	ObjectManager::Get_Instance()->Add_Object(_player, OBJID::PLAYER);

	{
		// Test Block
		Object* obj = nullptr;
		obj = new Cube;
		obj->Initialize();
		static_cast<Cube*>(obj)->SetColor(COLOR::RED);
		static_cast<Cube*>(obj)->SetPos(glm::vec3(0.5, 0.0, 0.0));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::BLOCK);
	}

	{
		// Ground
		Object* obj = nullptr;
		obj = new Cube;
		obj->Initialize();
		static_cast<Cube*>(obj)->SetColor(COLOR::GREEN);
		static_cast<Cube*>(obj)->SetPos(glm::vec3(0.0, -2.5, 0.0));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(20.f, 0.1f, 1000.f));
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::GROUND);
	}
}

void Stage::Update()
{
	ObjectManager::Get_Instance()->Update();

	for (auto& obj : ObjectManager::Get_Instance()->Get_List(OBJID::ENEMY)) static_cast<Cube*>(obj)->UpdateCollisionBox();
	for (auto& obj : ObjectManager::Get_Instance()->Get_List(OBJID::BLOCK)) static_cast<Cube*>(obj)->UpdateCollisionBox();
	static_cast<Cube*>(_player)->UpdateCollisionBox();



	CollisionManager::Get_Instance()->CollisionCheck(
		ObjectManager::Get_Instance()->Get_Player(), ObjectManager::Get_Instance()->Get_List(OBJID::BLOCK));
}

void Stage::Late_update()
{
	ObjectManager::Get_Instance()->Late_Update();
}

void Stage::Render(GLuint _program)
{
	ObjectManager::Get_Instance()->Render(_program);
}

void Stage::Release()
{
}
