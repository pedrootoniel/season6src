// CustomWingEffect.h: interface for the CCustomMonsterNameColor class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_NAME_COLOR 100

struct CUSTOM_MONSTER_COLOR_INFO
{
	int		Index;
	WORD	Class;
	int		Red;
	int		Green;
	int		Blue;
	int		Alpha;
};

class CCustomMonsterNameColor
{
public:
	CCustomMonsterNameColor();
	virtual ~CCustomMonsterNameColor();
	void Init();
	void Load(CUSTOM_MONSTER_COLOR_INFO* info);
	void SetInfo(CUSTOM_MONSTER_COLOR_INFO info);
	CUSTOM_MONSTER_COLOR_INFO* GetNPCNameByIndex(int index);
public:
	CUSTOM_MONSTER_COLOR_INFO m_CustomMonsterColorInfo[MAX_NAME_COLOR];
};

extern CCustomMonsterNameColor gCustomMonsterNameColor;
