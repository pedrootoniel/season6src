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
	void Load(char* path);
	void SetInfo(CUSTOM_MONSTER_COLOR_INFO info);
public:
	CUSTOM_MONSTER_COLOR_INFO m_CustomMonsterColorInfo[MAX_NAME_COLOR];
};

extern CCustomMonsterNameColor gCustomMonsterNameColor;
