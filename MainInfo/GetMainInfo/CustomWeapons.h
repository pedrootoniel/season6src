#pragma once

#define MAX_CUSTOM_WEAPONS	500

struct CUSTOM_WEAPONS_INFO
{
	int Index;
	int ItemIndex;
	BYTE Type;
};

class CCustomWeapons
{
public:
	CCustomWeapons();
	virtual ~CCustomWeapons();
	void Init();
	void Load(char* path);
	void SetInfo(CUSTOM_WEAPONS_INFO info);
public:
	CUSTOM_WEAPONS_INFO m_CustomWeaponsInfo[MAX_CUSTOM_WEAPONS];
};

extern CCustomWeapons gCustomWeapons;
