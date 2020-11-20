#pragma once

#include "Object.h"
#define MAX_CUSTOM_MONSTER		250
#define MONSTER_MODEL	644 //794?

struct CUSTOM_MONSTER_INFO
{
	int Index;
	WORD	ID;
	BYTE	Type;
	char	Name[25];
	char	Dir[50];
	char	Folder[50];
	char	BMDFile[50];
	float	Size;
};
class CCustomMonster
{
public:
	CCustomMonster();
	virtual ~CCustomMonster();
	void Init();
	void Load(CUSTOM_MONSTER_INFO* info);
	void SetInfo(CUSTOM_MONSTER_INFO info);
	CUSTOM_MONSTER_INFO* GetInfo(int index);
	CUSTOM_MONSTER_INFO* GetInfoByID(WORD ID);
	BOOL GetCustomMonsterInfo(WORD ID,BYTE Type,char* Name,char* Dir,char* Folder,char* BMDFile,float Size);

	public:
	CUSTOM_MONSTER_INFO m_CustomMonsterInfo[MAX_CUSTOM_MONSTER];

};
extern CCustomMonster gCustomMonster;