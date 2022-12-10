#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__
#include "Cube.h"

class Item : public Cube
{
public:
	Item();
	virtual ~Item();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(GLuint _program) override;
	virtual void Release() override;
	
public:
	const ITEMTYPE GetItemType() { return _itemType; }

public:
	void SetItemType(ITEMTYPE itemType) { _itemType = itemType; }

private:
	ITEMTYPE	_itemType = ITEM_END;
};

#endif