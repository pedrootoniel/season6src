#pragma once
#include "Protocol.h"

struct MONSTERBAR_DATA
{
	int MonsterID;
	char Text[25];
	BYTE Red;
	BYTE Green;
	BYTE Blue;
	float Opacity;
};

struct PMSG_MONSTERBAR_RECV
{
	PSBMSG_HEAD	h;
	// ----
	int MonsterID;
	char Text[25];
	BYTE Red;
	BYTE Green;
	BYTE Blue;
	float Opacity;
};

class cMonsterBar
{
public:
	cMonsterBar();
	virtual ~cMonsterBar();
	void AddMonsterBar(MONSTERBAR_DATA info);
	void DelMonsterBar(MONSTERBAR_DATA info);
	MONSTERBAR_DATA* GetHPBar(int MonsterID);
public:
	//std::vector<MONSTERBAR_DATA> m_MonsterBar;
	std::map<int,MONSTERBAR_DATA> m_MonsterBar;
}; extern cMonsterBar gMonsterBar;

