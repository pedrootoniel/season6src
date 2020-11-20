// CustomWing.cpp: implementation of the CItemOption class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemOption.h"
#include "MemScript.h"

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

void CItemOption::Load(char* path) // OK
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

void CItemOption::SetInfo(ItemOption_Data info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_OPTION_ITEM)
	{
		return;
	}

	this->m_CustomOptionInfo[info.Index] = info;
}
