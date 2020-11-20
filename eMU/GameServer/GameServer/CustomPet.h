// CustomPet.h: interface for the CCustomPet class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Item.h"
#include "User.h"

#define MAX_CUSTOM_PET 500

struct CUSTOM_PET_INFO
{
	int Index;
	int ItemIndex;
	int IncDamageRate;
	int IncLife;
	int IncMana;
	int IncAttackSpeed;
	int IncDoubleDamageRate;
	char ModelName[32];
};

class CCustomPet
{
public:
	CCustomPet();
	virtual ~CCustomPet();
	void Init();
	void Load(char* path);
	void SetInfo(CUSTOM_PET_INFO info);
	CUSTOM_PET_INFO* GetInfo(int index);
	CUSTOM_PET_INFO* GetInfoByItem(int ItemIndex);
	bool CheckCustomPet(int index);
	bool CheckCustomPetByItem(int ItemIndex);
	int GetCustomPetIndex(int ItemIndex);

	int GetCustomPetDamageRate(int ItemIndex);
	int GetCustomPetLife(int ItemIndex);
	int GetCustomPetMana(int ItemIndex);
	int GetCustomPetAttackSpeed(int ItemIndex);
	int GetCustomPetDoubleDamageRate(int ItemIndex);
	//long GetCustomPetExperienceRate(int ItemIndex);
	//long GetCustomPetMasterExperienceRate(int ItemIndex);
	void CalcCustomPetOption(LPOBJ lpObj,bool flag);
public:
	CUSTOM_PET_INFO m_CustomPetInfo[MAX_CUSTOM_PET];
};

extern CCustomPet gCustomPet;
