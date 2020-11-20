#include "stdafx.h"
#include "CustomMonster.h"
#include "MemScript.h"

CCustomMonster gCustomMonster; 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomMonster::CCustomMonster() // OK
{
	this->Init();
}

CCustomMonster::~CCustomMonster() // OK
{

}
void CCustomMonster::Init()
{
	for(int n=0;n < MAX_CUSTOM_MONSTER;n++)
	{
		this->m_CustomMonsterInfo[n].Index = -1;
	}
}
void CCustomMonster::Load(char* path) // OK
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

			CUSTOM_MONSTER_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomMonsterIndexCount = 0;

			info.Index = CustomMonsterIndexCount++;

			info.ID = lpMemScript->GetNumber();

			info.Type = lpMemScript->GetAsNumber();

			strcpy_s(info.Name,lpMemScript->GetAsString());

			strcpy_s(info.Dir,lpMemScript->GetAsString());

			strcpy_s(info.Folder,lpMemScript->GetAsString());

			strcpy_s(info.BMDFile,lpMemScript->GetAsString());

			info.Size = lpMemScript->GetAsFloatNumber();

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}
void CCustomMonster::SetInfo(CUSTOM_MONSTER_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_MONSTER)
	{
		return;
	}

	this->m_CustomMonsterInfo[info.Index] = info;
}
