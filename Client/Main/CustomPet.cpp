// CustomItem.cpp: implementation of the cCustomPet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomPet.h"
#include "Defines.h"
cCustomPet gCustomPet2;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cCustomPet::cCustomPet() // OK
{
	this->Init();
}

cCustomPet::~cCustomPet() // OK
{

}

void cCustomPet::Init() // OK
{
	for(int n=0;n < MAX_PET_ITEM;n++)
	{
		this->m_CustomPetInfo[n].Index = -1;
	}
}

void cCustomPet::Load(CUSTOM_PET_INFO* info) // OK
{
	for(int n=0;n < MAX_PET_ITEM;n++)
	{
		this->SetInfo(info[n]);
	}
}

void cCustomPet::SetInfo(CUSTOM_PET_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_PET_ITEM)
	{
		return;
	}

	this->m_CustomPetInfo[info.Index] = info;
}

CUSTOM_PET_INFO* cCustomPet::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_PET_ITEM)
	{
		return 0;
	}

	if(this->m_CustomPetInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomPetInfo[index];
}

CUSTOM_PET_INFO* cCustomPet::GetInfoByItem(int ItemType) // OK
{
	for(int n=0;n < MAX_PET_ITEM;n++)
	{
		CUSTOM_PET_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->ItemType == ItemType)
		{
			return lpInfo;
		}
	}

	return 0;
}
BOOL cCustomPet::CheckCustomItemByItem(int ItemIndex) // OK
{
	if(this->GetInfoByItem(ItemIndex) != 0)
	{
		return 1;
	}

	return 0;
}
