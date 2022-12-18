#include "stdafx.h"
#include "Logo.h"
#include "TexturedRect.h"

#include "ObjectManager.h"

Logo::Logo()
{
}

Logo::~Logo()
{
	Release();
}

void Logo::Initialize()
{
	{
		// ground
		Object* obj = nullptr;
		obj = new TexturedRect;
		static_cast<TexturedRect*>(obj)->SetTexType(TEX_TYPE::BUTTON);
		obj->Initialize();
		ObjectManager::Get_Instance()->Add_Object(obj, OBJID::TEXTURED_RECT);
	}
}

void Logo::Update()
{
	ObjectManager::Get_Instance()->Update();
}

void Logo::Late_update()
{
	ObjectManager::Get_Instance()->Late_Update();
}

void Logo::Render(GLuint _program, GLuint _texProgram)
{
	ObjectManager::Get_Instance()->Render(_program, _texProgram);
}

void Logo::Release()
{
	ObjectManager::Get_Instance()->Release();
}
