// ItemOption.cpp: implementation of the CItemRank class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemRank.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "Util.h"

CItemRank gItemRank;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemRank::CItemRank() // OK
{
	this->Init();
}

CItemRank::~CItemRank() // OK
{

}

void CItemRank::Init() // OK
{
	for(int n=0;n < MAX_OPTION_ITEM;n++)
	{
		this->m_CustomOptionInfo[n].Index = -1;
	}
}

void CItemRank::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			ItemOption_Data info;

			memset(&info,0,sizeof(info));

			static int CustomOptionIndexCount = 0;

			info.Index = CustomOptionIndexCount++;

			info.ItemIndex = lpMemScript->GetNumber();

			info.Option1 = lpMemScript->GetAsNumber();

			info.Option2 = lpMemScript->GetAsNumber();

			info.Option3 = lpMemScript->GetAsNumber();

			info.Option4 = lpMemScript->GetAsNumber();

			info.Option5 = lpMemScript->GetAsNumber();

			info.Option6 = lpMemScript->GetAsNumber(); 

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CItemRank::SetInfo(ItemOption_Data info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_OPTION_ITEM)
	{
		return;
	}

	this->m_CustomOptionInfo[info.Index] = info;
}

void CItemRank::InsertOption(LPOBJ lpObj,CItem* lpItem,bool flag) // OK
{

}