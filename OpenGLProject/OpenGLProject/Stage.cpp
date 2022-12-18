#include "stdafx.h"
#include "Stage.h"
#include "Object.h"
#include "Cube.h"
#include "Player.h"
#include "Item.h"
#include "MovingEnemy.h"
#include "AttackEnemy.h"
#include "TexturedRect.h"
#include "Block.h"

#include "CollisionManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"

Stage::Stage()
{
}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize()
{
	//SoundManager::Get_Instance()->PlayBGM(L"bgm.mp3");

	{
		// Player
		Object* obj = nullptr;
		obj = new Player;
		obj->Initialize();
		static_cast<Cube*>(obj)->SetPos(glm::vec3(0.0, 0.0, 0));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.3f);
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

	CreateBlock();
	CreateEnemy();
	CreateItem();
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
		ObjectManager::Get_Instance()->Get_Player(), ObjectManager::Get_Instance()->Get_List(OBJID::BULLET));

	CollisionManager::Get_Instance()->Collision_PlayerToEnemy(
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

void Stage::CreateBlock()
{
	float y = 0.0f;

	// block pos
	BlockPos.push_back(glm::vec3(-2.0f, y, -40.f));
	BlockPos.push_back(glm::vec3(2.0f, y, -40.f));
	BlockPos.push_back(glm::vec3(-2.0f, y, -45.f));
	BlockPos.push_back(glm::vec3(2.0f, y, -45.f));
	BlockPos.push_back(glm::vec3(-2.0f, y, -50.f));
	BlockPos.push_back(glm::vec3(2.0f, y, -50.f));

	BlockPos.push_back(glm::vec3(0.f, y, -60.f));

	// create block
	for (int i = 0; i < BlockPos.size(); ++i) {
		Object* obj = nullptr;
		obj = new Block;
		obj->Initialize();
		static_cast<Cube*>(obj)->SetPos(BlockPos[i]);
		static_cast<Cube*>(obj)->SetScale(glm::vec3(5.f, 20.f, 5.f));
		static_cast<Cube*>(obj)->SetBoundingSize(1.5f);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::BLOCK);
	}
}

void Stage::CreateEnemy()
{
	float y = 0.0f;

	// Movnig Enemy Pos
	MovingEnemyPos.push_back(glm::vec3(-1.0f, y, -1.0f));
	MovingEnemyPos.push_back(glm::vec3(1.0f, y, -1.0f));

	MovingEnemyPos.push_back(glm::vec3(-1.8f, y, -20.0f));
	MovingEnemyPos.push_back(glm::vec3(0.0f, y, -20.0f));
	MovingEnemyPos.push_back(glm::vec3(1.8f, y, -20.0f));
	
	MovingEnemyPos.push_back(glm::vec3(0.f, y, -43.0f));
	MovingEnemyPos.push_back(glm::vec3(0.f, y, -48.0f));


	// Attack Enemy Pos
	AttackEnemyPos.push_back(glm::vec3(0.0f, y, -10.0f));
	AttackEnemyPos.push_back(glm::vec3(-1.3f, y, -30.0f));
	AttackEnemyPos.push_back(glm::vec3(1.3f, y, -30.0f));
	AttackEnemyPos.push_back(glm::vec3(-2.0f, y, -60.0f));
	AttackEnemyPos.push_back(glm::vec3(2.0f, y, -60.0f));


	// Create Moving Enemy
	for (int i = 0; i < MovingEnemyPos.size(); ++i) {
		Object* obj = nullptr;
		obj = new MovingEnemy;
		obj->Initialize();
		
		static_cast<Cube*>(obj)->SetPos(MovingEnemyPos[i]);
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.3f);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::ENEMY);
	}

	// Create Attack Enemy
	for (int i = 0; i < AttackEnemyPos.size(); ++i) {
		Object* obj = nullptr;
		obj = new AttackEnemy;
		obj->Initialize();

		static_cast<Cube*>(obj)->SetPos(AttackEnemyPos[i]);
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.3f);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::ENEMY);
	}
}

void Stage::CreateItem()
{
	float y = 0.0f;

	ItemPos.push_back(glm::vec3(-1.8f, y, -60.0f));
	ItemPos.push_back(glm::vec3(1.8f, y, -60.0f));

	{
		Object* obj = nullptr;
		obj = new Item;
		obj->Initialize();

		static_cast<Cube*>(obj)->SetPos(glm::vec3(-1.5f, y, -6.0f));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.3f);
		static_cast<Item*>(obj)->SetItemType(ALPHA);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::ITEM);
	}

	{
		Object* obj = nullptr;
		obj = new Item;
		obj->Initialize();

		static_cast<Cube*>(obj)->SetPos(glm::vec3(1.5f, y, -6.0f));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.3f);
		static_cast<Item*>(obj)->SetItemType(SPEEDUP);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::ITEM);
	}

	{
		Object* obj = nullptr;
		obj = new Item;
		obj->Initialize();

		static_cast<Cube*>(obj)->SetPos(glm::vec3(-1.5f, y, -35.0f));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.3f);
		static_cast<Item*>(obj)->SetItemType(ALPHA);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::ITEM);
	}

	{
		Object* obj = nullptr;
		obj = new Item;
		obj->Initialize();

		static_cast<Cube*>(obj)->SetPos(glm::vec3(1.5f, y, -35.0f));
		static_cast<Cube*>(obj)->SetScale(glm::vec3(1.f, 1.f, 1.f));
		static_cast<Cube*>(obj)->SetBoundingSize(0.3f);
		static_cast<Item*>(obj)->SetItemType(SPEEDUP);
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::ITEM);
	}
}
