#include "stdafx.h"
#include "CustomWeapons.h"
#include "MemScript.h"

CCustomWeapons gCustomWeapons;

CCustomWeapons::CCustomWeapons() // OK
{
	this->Init();
}

CCustomWeapons::~CCustomWeapons() // OK
{

}

void CCustomWeapons::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_WEAPONS;n++)
	{
		this->m_CustomWeaponsInfo[n].Index = -1;
	}
}

void CCustomWeapons::Load(char* path)
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

			CUSTOM_WEAPONS_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomItemIndexCount = 0;

			info.Index = CustomItemIndexCount++;

			info.ItemIndex = lpMemScript->GetNumber();

			info.Type = lpMemScript->GetAsNumber();

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomWeapons::SetInfo(CUSTOM_WEAPONS_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_WEAPONS)
	{
		return;
	}

	this->m_CustomWeaponsInfo[info.Index] = info;
}
