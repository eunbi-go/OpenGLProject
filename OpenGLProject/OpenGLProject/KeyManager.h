#pragma once

#ifndef __KEYMANAGER_H__
#define __KEYMANAGER_H__

#define VK_MAX 0xff

class KeyManager
{
public:
	KeyManager();
	~KeyManager();

public:
	bool Key_Pressing(int _key);
	bool Key_Down(int _key);
	void Key_Update();

public:
	static KeyManager* Get_Instance()
	{
		if (!_instance)
			_instance = new KeyManager;
		return _instance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(_instance);
	}

private:
	static KeyManager* _instance;
	bool					_keyState[VK_MAX];
};

#endif // !__KEYMANAGER_H__
