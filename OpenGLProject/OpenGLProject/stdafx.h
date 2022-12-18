#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

//#include <stdlib.h>
#include <stdio.h>

// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <random>
#include <time.h>
#include <algorithm>

// 사운드파일 추가
#include <io.h>
#include "fmod.h"
#pragma comment (lib, "fmodex_vc.lib")


// 동영상
#include <Vfw.h>
#pragma comment (lib, "Vfw32.lib")

using namespace std;


enum OBJID {PLAYER, ENEMY, ITEM, BLOCK, BULLET, TEXTURED_RECT, OBJID_END};
enum MOVE {MOVE_FORWARD, MOVE_BACK, MOVE_RIGHT, MOVE_LEFT, MOVE_TO_PLAYER, MOVE_END};
enum ITEMTYPE { ALPHA, SPEEDUP, LIGHT, ITEM_END };
enum TEX_TYPE { GROUND, BUTTON, TEX_TYPE_END };
enum SCENEID { LOGO, STAGE, SCENE_END };

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }

#define OBJ_DEAD 1
#define OBJ_NOEVENET 0

template <typename T>
void Safe_Delete(T& _Dst)
{
	if (_Dst)
	{
		delete _Dst;
		_Dst = nullptr;
	}
}

struct CollisionBox
{
	float	maxX;
	float	minX;
	float	maxZ;
	float	minZ;
	float	lengthX;
	float	lengthZ;
};