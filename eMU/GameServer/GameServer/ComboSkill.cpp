#include "stdafx.h"
#include "ComboSkill.h"
#include "ComboSkillData.h"

CComboSkill gComboSkill;

void CComboSkill::Init()
{
	this->m_time		= 0;
	this->m_skill[0]	= 0xFFFF;
	this->m_skill[1]	= 0xFFFF;
	this->m_index		= -1;
}

bool CComboSkill::CheckCombo(WORD skill)
{
	int type		= gComboSkillData.GetSkillType(skill);
	DWORD delay		= gComboSkillData.GetSkillDelay(skill);

	if(type == -1)
	{
		this->Init();
		return 0;
	}

	if(type == 0)
	{
		this->m_time		= GetTickCount() + delay;
		this->m_skill[0]	= skill;
		this->m_index		= 0;
		return 0;
	}

	if(type == 1)
	{
		if(this->m_time < GetTickCount())
		{
			this->Init();
			return 0;
		}

		if(this->m_skill[0] == 0xFFFF)
		{
			this->Init();
			return 0;
		}

		if(this->m_index == 0)
		{
			this->m_time		= GetTickCount() + delay;
			this->m_skill[1]	= skill;
			this->m_index		= 1;
			return 0;
		}
		
		if(this->m_index == 1 && this->m_skill[1] != skill)
		{
			this->Init();
			return 1;
		}
	}

	this->Init();
	return 0;
}