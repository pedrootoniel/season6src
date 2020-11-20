// CustomItem.cpp: implementation of the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomItem.h"
#include "CustomWing.h"
#include "Defines.h"
CCustomItem gCustomItem;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomItem::CCustomItem() // OK
{
	this->Init();
}

CCustomItem::~CCustomItem() // OK
{

}

void CCustomItem::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		this->m_CustomItemInfo[n].Index = -1;
	}
}

void CCustomItem::Load(CUSTOM_ITEM_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomItem::SetInfo(CUSTOM_ITEM_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_ITEM)
	{
		return;
	}

	this->m_CustomItemInfo[info.Index] = info;
}

CUSTOM_ITEM_INFO* CCustomItem::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_ITEM)
	{
		return 0;
	}

	if(this->m_CustomItemInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomItemInfo[index];
}

CUSTOM_ITEM_INFO* CCustomItem::GetInfoByItem(int ItemType) // OK
{
	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		CUSTOM_ITEM_INFO* lpInfo = this->GetInfo(n);

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
BOOL CCustomItem::CheckCustomItemByItem(int ItemIndex) // OK
{
	if(this->GetInfoByItem(ItemIndex) != 0)
	{
		return 1;
	}

	return 0;
}
BOOL CCustomItem::GetCustomItemColor(int ItemIndex,float* ItemColor) // OK
{
	for( int i = 0; i < MAX_CUSTOM_ITEM; i++ )
	{
		if( ITEM2(this->m_CustomItemInfo[i].ItemType, this->m_CustomItemInfo[i].ItemIndex) == ItemIndex )
		{
			if(this->m_CustomItemInfo[i].ColorR >= 1 && this->m_CustomItemInfo[i].ColorR >= 1 && this->m_CustomItemInfo[i].ColorR >= 1)
			{
				ItemColor[0] = (float)(this->m_CustomItemInfo[i].ColorR/255.0f);
				ItemColor[1] = (float)(this->m_CustomItemInfo[i].ColorG/255.0f);
				ItemColor[2] = (float)(this->m_CustomItemInfo[i].ColorB/255.0f);
			}
			if(this->m_CustomItemInfo[i].ColorR == 0 && this->m_CustomItemInfo[i].ColorR == 0 && this->m_CustomItemInfo[i].ColorR == 0)
			{
				ItemColor[0] = (float)(0.0f);
				ItemColor[1] = (float)(0.0f);
				ItemColor[2] = (float)(0.0f);
			}
			return 1;
		}
	}
	return false;
}
