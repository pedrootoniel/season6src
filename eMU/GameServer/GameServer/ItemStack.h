// ItemStack.h: interface for the CItemStack class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Item.h"

struct ITEM_STACK_INFO
{
	int Index;
	int Level;
	int MaxStack;
	int CreateItemIndex;
};

class CItemStack
{
public:
	CItemStack();
	virtual ~CItemStack();
	void Load(char* path);
	int GetItemMaxStack(int index, int level);
	int GetCreateItemIndex(int index, int level);
private:
	//std::map<int,ITEM_STACK_INFO> m_ItemStackInfo;
	std::vector<ITEM_STACK_INFO> m_ItemStackInfo;
};

extern CItemStack gItemStack;
