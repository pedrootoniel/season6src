#include "stdafx.h"
#include "ComboSkillData.h"
#include "MemScript.h"
#include "Util.h"

CComboSkillData gComboSkillData;

CComboSkillData::CComboSkillData(void)
{
	this->m_Count = 0;
}

void CComboSkillData::Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_Count = 0;

	try
	{
		COMBO_SKILL_INFO info;

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

			memset(&info,NULL,sizeof(info));

			info.Stage = lpMemScript->GetNumber();
			info.Skill = lpMemScript->GetAsNumber();
			info.Delay = lpMemScript->GetAsNumber();

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CComboSkillData::SetInfo(COMBO_SKILL_INFO info)
{
	if(this->m_Count < 0 || this->m_Count >= MAX_COMBO_INFO)
	{
		return;
	}

	this->m_Info[this->m_Count++] = info;
}

COMBO_SKILL_INFO* CComboSkillData::GetInfoBySkill(WORD skill)
{
	for(int i = 0;i <= this->m_Count;i++)
	{
		if(this->m_Info[i].Skill == skill)
		{
			return &this->m_Info[i];
		}
	}

	return NULL;
}

int CComboSkillData::GetSkillType(WORD skill)
{
	COMBO_SKILL_INFO* lpInfo = this->GetInfoBySkill(skill);

	if(lpInfo != NULL)
	{
		return lpInfo->Stage;
	}

	return -1;
}

DWORD CComboSkillData::GetSkillDelay(WORD skill)
{
	COMBO_SKILL_INFO* lpInfo = this->GetInfoBySkill(skill);

	if(lpInfo != NULL)
	{
		return lpInfo->Delay;
	}

	return 0;
}