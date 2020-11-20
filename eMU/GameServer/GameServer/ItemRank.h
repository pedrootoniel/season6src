// ItemOption.h: interface for the CItemRank class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Item.h"
#include "User.h"

#define MAX_OPTION_ITEM 100

struct ItemOption_Data
{
	int Index;
	int ItemIndex;
	int Option1;
	int Option2;
	int Option3;
	int Option4;
	int Option5;
	int Option6;
};

class CItemRank
{
public:
	CItemRank();
	virtual ~CItemRank();
	void Init();
	void Load(char* path);
	void SetInfo(ItemOption_Data info);
	void InsertOption(LPOBJ lpObj,CItem* lpItem,bool flag);
public:
	ItemOption_Data m_CustomOptionInfo[MAX_OPTION_ITEM];
};

extern CItemRank gItemRank;
