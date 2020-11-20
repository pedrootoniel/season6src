#pragma once

#define MAX_CUSTOM_WEAPONS	500

struct CUSTOM_WEAPONS_INFO
{
	int Index;
	int ItemIndex;
	BYTE Type;
};

enum CustomWeaponsTypes
{
	CTYPE_ELF_BOW = 0,
	CTYPE_ELF_CROSSBOW = 1,
	CTYPE_MG = 2,
	CTYPE_RF = 3,
};

class cCustomWeapons
{
public:
	cCustomWeapons();
	virtual ~cCustomWeapons();
	void Init();
	void Load(CUSTOM_WEAPONS_INFO* info);
	void SetInfo(CUSTOM_WEAPONS_INFO info);
	// ----
	bool CheckElfBow(int ItemID);
	bool CheckElfCrossbow(int ItemID);
	bool CheckMG(int ItemID);
	bool CheckRF(int ItemID);
private:
	CUSTOM_WEAPONS_INFO m_CustomWeaponsInfo[MAX_CUSTOM_WEAPONS];
}; extern cCustomWeapons gCustomWeapons;