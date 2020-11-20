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
	void Load(CUSTOM_PET_INFO* info);
	void SetInfo(CUSTOM_PET_INFO info);
	CUSTOM_PET_INFO* GetInfo(int index);
	CUSTOM_PET_INFO* GetInfoByItem(int ItemType);
	BOOL CheckCustomItemByItem(int ItemIndex);
public:
	CUSTOM_PET_INFO m_CustomPetInfo[MAX_PET_ITEM];
};

extern cCustomPet gCustomPet2;
