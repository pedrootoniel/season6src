// CustomItem.h: interface for the cCustomPet class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_PET_ITEM 350

struct CUSTOM_PET_INFO
{
	int Index;
	int	ItemType;
	int ItemIndex;
	char ModelName[32];
};

class cCustomPet
{
public:
	cCustomPet();
	virtual ~cCustomPet();
	void Init();
	void Load(char* path);
	void SetInfo(CUSTOM_PET_INFO info);
public:
	CUSTOM_PET_INFO m_CustomPetInfo[MAX_PET_ITEM];
};

extern cCustomPet gCustomPet2;
