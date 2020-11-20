// CustomJewel.cpp: implementation of the cCustomTitle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomTitle.h"

cCustomTitle gCustomTitle;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cCustomTitle::cCustomTitle() // OK
{
	this->Init();
}

cCustomTitle::~cCustomTitle() // OK
{

}

void cCustomTitle::Init() // OK
{
	for(int n=0;n < MAX_RANK_TITLE;n++)
	{
		this->m_CustomTitle[n].Index = -1;
	}
}

void cCustomTitle::Load(TITLE_STRUCT* info) // OK
{
	for(int n=0;n < MAX_RANK_TITLE;n++)
	{
		this->SetInfo(info[n]);
	}
}

void cCustomTitle::SetInfo(TITLE_STRUCT info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_RANK_TITLE)
	{
		return;
	}

	this->m_CustomTitle[info.Index] = info;
}

TITLE_STRUCT* cCustomTitle::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_RANK_TITLE)
	{
		return 0;
	}

	if(this->m_CustomTitle[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomTitle[index];
}

TITLE_STRUCT* cCustomTitle::GetInfoTitle(BYTE TitleCode) // OK
{
	for(int n=0;n < MAX_RANK_TITLE;n++)
	{
		TITLE_STRUCT* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->TitleCode == TitleCode)
		{
			return lpInfo;
		}
	}

	return 0;
}

BOOL cCustomTitle::GetTitleInfo(BYTE TitleCode,char* ImgDir,char* TitleText,DWORD ImgCode,float width,float height,int color, int addhp, int addmp)
{
	TITLE_STRUCT* lpInfo = this->GetInfoTitle(TitleCode);
	if(lpInfo == 0)
	{
		return 0;
	}
	ImgDir = (lpInfo->ImgDir);
	TitleText = (lpInfo->TitleText);
	ImgCode = (DWORD)(lpInfo->ImgCode);
	width = (float)(lpInfo->width);
	height = (float)(lpInfo->height);
	color = (lpInfo->color);
	addhp = (lpInfo->AddHP);
	addmp = (lpInfo->AddMP);
	return 1;
}


