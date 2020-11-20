// CustomWingEffect.cpp: implementation of the CCustomMonsterNameColor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MonsterNameColor.h"
#include "MemScript.h"

CCustomMonsterNameColor gCustomMonsterNameColor;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomMonsterNameColor::CCustomMonsterNameColor() // OK
{
	this->Init();
}

CCustomMonsterNameColor::~CCustomMonsterNameColor() // OK
{

}

void CCustomMonsterNameColor::Init() // OK
{
	for(int n=0;n < MAX_NAME_COLOR;n++)
	{
		this->m_CustomMonsterColorInfo[n].Index = -1;
	}
}

void CCustomMonsterNameColor::Load(char* path) // OK
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

			CUSTOM_MONSTER_COLOR_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomColorIndexCount = 0;
			info.Index = CustomColorIndexCount++;
			info.Class = lpMemScript->GetNumber();
			info.Red = lpMemScript->GetAsNumber();
			info.Green = lpMemScript->GetAsNumber();
			info.Blue = lpMemScript->GetAsNumber();
			info.Alpha = lpMemScript->GetAsNumber();
			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomMonsterNameColor::SetInfo(CUSTOM_MONSTER_COLOR_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_NAME_COLOR)
	{
		return;
	}

	this->m_CustomMonsterColorInfo[info.Index] = info;
}
