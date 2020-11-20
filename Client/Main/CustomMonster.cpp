#include "stdafx.h"
#include "CustomMonster.h"


CCustomMonster gCustomMonster;

CCustomMonster::CCustomMonster()
{
	this->Init();
}
CCustomMonster::~CCustomMonster()
{

}
void CCustomMonster::Init()
{
	for(int n=0;n < MAX_CUSTOM_MONSTER;n++)
	{
		this->m_CustomMonsterInfo[n].Index = -1;
	}
}
void CCustomMonster::Load(CUSTOM_MONSTER_INFO* info)
{
	for(int n=0;n < MAX_CUSTOM_MONSTER;n++)
	{
		this->SetInfo(info[n]);
	}
}
void CCustomMonster::SetInfo(CUSTOM_MONSTER_INFO info)
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_MONSTER)
	{
		return;
	}

	this->m_CustomMonsterInfo[info.Index] = info;
}
CUSTOM_MONSTER_INFO* CCustomMonster::GetInfo(int index)
{
	if(index < 0 || index >= MAX_CUSTOM_MONSTER)
	{
		return 0;
	}

	if(this->m_CustomMonsterInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomMonsterInfo[index];
}
CUSTOM_MONSTER_INFO* CCustomMonster::GetInfoByID(WORD ID)
{
	for(int n=0;n < MAX_CUSTOM_MONSTER;n++)
	{
		CUSTOM_MONSTER_INFO* lpInfo = this->GetInfo(n);

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
BOOL CCustomMonster::GetCustomMonsterInfo(WORD ID,BYTE Type,char* Name,char* Dir,char* Folder,char* BMDFile,float Size)
{
	CUSTOM_MONSTER_INFO* lpInfo = this->GetInfoByID(ID);
	if(lpInfo == 0)
	{
		return 0;
	}
	Type = (BYTE)(lpInfo->Type);
	Name = (lpInfo->Name);
	Dir = (lpInfo->Dir);
	Folder = (lpInfo->Folder);
	BMDFile = (lpInfo->BMDFile);
	Size = (float)(lpInfo->Size);

	return 1;
}
