#include "stdafx.h"
#include "Stage.h"
#include "Object.h"
#include "Cube.h"
#include "Player.h"

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
	// Player
	Object* obj = nullptr;
	obj = new Player;
	obj->Initialize();
	static_cast<Cube*>(obj)->SetPos(glm::vec3(0.0, 0.0, 0));
	static_cast<Cube*>(obj)->SetScale(glm::vec3(2.f, 2.f, 2.f));
	static_cast<Cube*>(obj)->SetRotateX(30.f);
	static_cast<Cube*>(obj)->SetRotateY(-30.f);
	ObjectManager::Get_Instance()->Add_Object(obj, OBJID::PLAYER);
}

void Stage::Update()
{
	ObjectManager::Get_Instance()->Update();
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
