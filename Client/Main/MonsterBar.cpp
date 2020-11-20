#include "StdAfx.h"
#include "MonsterBar.h"

cMonsterBar gMonsterBar;

cMonsterBar::cMonsterBar()
{
	this->m_MonsterBar.clear();
}


cMonsterBar::~cMonsterBar()
{

}

void cMonsterBar::AddMonsterBar(MONSTERBAR_DATA info)
{
	std::map<int,MONSTERBAR_DATA>::iterator it = this->m_MonsterBar.find(info.MonsterID);

	if(it == this->m_MonsterBar.end())
	{
		this->m_MonsterBar.insert(std::pair<int,MONSTERBAR_DATA>(int(info.MonsterID),info));
	}
	else
	{
		it->second = info;
	}
}

void cMonsterBar::DelMonsterBar(MONSTERBAR_DATA info)
{
	std::map<int,MONSTERBAR_DATA>::iterator it = this->m_MonsterBar.find(info.MonsterID);

	if(it != this->m_MonsterBar.end())
	{
		this->m_MonsterBar.erase(it);
	}
}

MONSTERBAR_DATA* cMonsterBar::GetHPBar(int MonsterID)
{
	std::map<int,MONSTERBAR_DATA>::iterator it = this->m_MonsterBar.find(MonsterID);

	if(it != this->m_MonsterBar.end())
	{
		return &it->second;
	}

	return 0;
}