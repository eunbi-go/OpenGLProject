#include "stdafx.h"
#include "Stage.h"
#include "Object.h"
#include "Cube.h"
#include "Player.h"
#include "Item.h"
#include "MovingEnemy.h"
#include "AttackEnemy.h"
#include "TexturedRect.h"

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

	{
		// ground
		Object* obj = nullptr;
		obj = new TexturedRect;
		static_cast<TexturedRect*>(obj)->SetTexType(TEX_TYPE::GROUND);
		obj->Initialize();
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::TEXTURED_RECT);
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

void Stage::Render(GLuint _program, GLuint _texProgram)
{
	ObjectManager::Get_Instance()->Render(_program, _texProgram);
}

void Stage::Release()
{
}
