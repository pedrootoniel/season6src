// CustomWing.cpp: implementation of the CItemOption class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemOption.h"
#include "Console.h"
CItemOption gItemOption;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemOption::CItemOption() // OK
{
	this->Init();
}

CItemOption::~CItemOption() // OK
{

}

void CItemOption::Init() // OK
{
	for(int n=0;n < MAX_OPTION_ITEM;n++)
	{
		this->m_CustomOptionInfo[n].Index = -1;
	}
}

void CItemOption::Load(ItemOption_Data* info) // OK
{
	for(int n=0;n < MAX_OPTION_ITEM;n++)
	{
		this->SetInfo(info[n]);
		//g_Console.AddMessage(1,"%d %d %d %d",gItemOption.m_CustomOptionInfo[n].ItemIndex,gItemOption.m_CustomOptionInfo[n].Option1,gItemOption.m_CustomOptionInfo[n].Option2,gItemOption.m_CustomOptionInfo[n].Option3);
	}
}

void CItemOption::SetInfo(ItemOption_Data info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_OPTION_ITEM)
	{
		return;
	}

	this->m_CustomOptionInfo[info.Index] = info;
}

ItemOption_Data* CItemOption::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_OPTION_ITEM)
	{
		return 0;
	}

	if(this->m_CustomOptionInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomOptionInfo[index];
}

ItemOption_Data* CItemOption::GetInfoByItem(int ItemIndex) // OK
{
	for(int n=0;n < MAX_OPTION_ITEM;n++)
	{
		ItemOption_Data* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->ItemIndex == ItemIndex)
		{
			return lpInfo;
		}
	}

	return 0;
}

int CItemOption::GetCustomItemIndex(int ItemIndex) // OK
{
	ItemOption_Data* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return 0;
	}

	return lpInfo->Index;
}

int CItemOption::GetCustomItemOption(int ItemIndex,int OptionNumber) // OK
{
	ItemOption_Data* lpInfo = this->GetInfoByItem(ItemIndex);

	if(lpInfo == 0)
	{
		return 0;
	}

	switch(OptionNumber)
	{
		case 0:
			return lpInfo->Option1;
		case 1:
			return lpInfo->Option2;
		case 2:
			return lpInfo->Option3;
		case 3:
			return lpInfo->Option4;
		case 4:
			return lpInfo->Option5;
		case 5:
			return lpInfo->Option6;
	}

	return 0;
}
