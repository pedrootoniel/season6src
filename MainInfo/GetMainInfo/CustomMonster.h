#pragma once
#define MAX_CUSTOM_MONSTER		250


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
	void Load(char* path);
	void SetInfo(CUSTOM_MONSTER_INFO info);
public:
	CUSTOM_MONSTER_INFO m_CustomMonsterInfo[MAX_CUSTOM_MONSTER];
};
extern CCustomMonster gCustomMonster; 