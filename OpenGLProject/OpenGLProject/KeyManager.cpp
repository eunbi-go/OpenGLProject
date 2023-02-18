#include "stdafx.h"
#include "KeyManager.h"

KeyManager* KeyManager::_instance = nullptr;

KeyManager::KeyManager()
{
	ZeroMemory(_keyState, sizeof(_keyState));
}


KeyManager::~KeyManager()
{
}

bool KeyManager::Key_Pressing(int _key)
{
	if (GetAsyncKeyState(_key) & 0x8000)
		return true;
	return false;
}

bool KeyManager::Key_Down(int _key)
{
	if (!_keyState[_key] && (GetAsyncKeyState(_key) & 0x8000))
	{
		_keyState[_key] = !_keyState[_key];
		return true;
	}
	return false;
}

void KeyManager::Key_Update()
{
	for (int i = 0; i < VK_MAX; ++i)
	{
		if (_keyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			_keyState[i] = !_keyState[i];
		if (!_keyState[i] && (GetAsyncKeyState(i) & 0x8000))
			_keyState[i] = !_keyState[i];
	}
}
