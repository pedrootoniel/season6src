// CustomWing.h: interface for the CItemOption class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_OPTION_ITEM 500

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

class CItemOption
{
public:
	CItemOption();
	virtual ~CItemOption();
	void Init();
	void Load(ItemOption_Data* info);
	void SetInfo(ItemOption_Data info);
	ItemOption_Data* GetInfo(int index);
	ItemOption_Data* GetInfoByItem(int ItemIndex);
	int GetCustomItemIndex(int ItemIndex);
	int GetCustomItemOption(int ItemIndex,int OptionNumber);
public:
	ItemOption_Data m_CustomOptionInfo[MAX_OPTION_ITEM];
};

extern CItemOption gItemOption;
