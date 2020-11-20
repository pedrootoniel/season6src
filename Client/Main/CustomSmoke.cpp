#include "stdafx.h"
#include "CustomSmoke.h"


cCustomSmoker gCustomSmoker;

cCustomSmoker::cCustomSmoker()
{
	this->Init();
}
cCustomSmoker::~cCustomSmoker()
{

}
void cCustomSmoker::Init()
{
	for(int n=0;n < MAX_ITEM_SMOKER;n++)
	{
		this->m_ItemSmokerInfo[n].Index = -1;
	}
}
void cCustomSmoker::Load(CUSTOM_SMOKER_INFO* info)
{
	for(int n=0;n < MAX_ITEM_SMOKER;n++)
	{
		this->SetInfo(info[n]);
	}
}
void cCustomSmoker::SetInfo(CUSTOM_SMOKER_INFO info)
{
	if(info.Index < 0 || info.Index >= MAX_ITEM_SMOKER)
	{
		return;
	}

	this->m_ItemSmokerInfo[info.Index] = info;
}
CUSTOM_SMOKER_INFO* cCustomSmoker::GetInfo(int index)
{
	if(index < 0 || index >= MAX_ITEM_SMOKER)
	{
		return 0;
	}

	if(this->m_ItemSmokerInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_ItemSmokerInfo[index];
}

CUSTOM_SMOKER_INFO* cCustomSmoker::GetInfoByID(WORD ID)
{
	for(int n=0;n < MAX_ITEM_SMOKER;n++)
	{
		CUSTOM_SMOKER_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->ID == ID)
		{
			return lpInfo;
		}
	}

	return 0;
}

BOOL cCustomSmoker::GetItemSmokerInfo(WORD ID,float R,float G,float B)
{
	CUSTOM_SMOKER_INFO* lpInfo = this->GetInfoByID(ID);
	if(lpInfo == 0)
	{
		return 0;
	}
	R = (float)(lpInfo->R);
	G = (float)(lpInfo->G);
	B = (float)(lpInfo->B);

	return 1;
}