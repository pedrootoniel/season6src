// CustomWingEffect.cpp: implementation of the CCustomMonsterNameColor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MonsterNameColor.h"
#include "Defines.h"
#include "Console.h"
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

void CCustomMonsterNameColor::Load(CUSTOM_MONSTER_COLOR_INFO* info) // OK
{
	for(int n=0;n < MAX_NAME_COLOR;n++)
	{
		this->SetInfo(info[n]);
		//g_Console.AddMessage(1,"%d %d %d %d %d",gCustomMonsterNameColor.m_CustomMonsterColorInfo[n].Class,gCustomMonsterNameColor.m_CustomMonsterColorInfo[n].Red, gCustomMonsterNameColor.m_CustomMonsterColorInfo[n].Green, gCustomMonsterNameColor.m_CustomMonsterColorInfo[n].Blue, gCustomMonsterNameColor.m_CustomMonsterColorInfo[n].Alpha);
	}
}

void CCustomMonsterNameColor::SetInfo(CUSTOM_MONSTER_COLOR_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_NAME_COLOR)
	{
		return;
	}

	this->m_CustomMonsterColorInfo[info.Index] = info;
}

CUSTOM_MONSTER_COLOR_INFO* CCustomMonsterNameColor::GetNPCNameByIndex(int index) // OK
{
	if(index < 0 || index >= MAX_NAME_COLOR)
	{
		return 0;
	}

	if(this->m_CustomMonsterColorInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomMonsterColorInfo[index];
}