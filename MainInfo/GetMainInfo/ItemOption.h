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
	void Load(char* path);
	void SetInfo(ItemOption_Data info);
public:
	ItemOption_Data m_CustomOptionInfo[MAX_OPTION_ITEM];
};

extern CItemOption gItemOption;
