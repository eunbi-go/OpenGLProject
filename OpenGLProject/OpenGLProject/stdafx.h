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

#include <DirectXCollision.h>

using namespace std;

enum OBJID {PLAYER, ENEMY, ITEM, BLOCK, GROUND, OBJID_END};
enum MOVE {MOVE_FORWARD, MOVE_BACK, MOVE_RIGHT, MOVE_LEFT, MOVE_END};
enum ITEMTYPE { ALPHA, SPEEDUP, LIGHT, ITEM_END };
enum COLOR { RED, GREEN, BLUE, PURPLE, COLOR_END };

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