#pragma once

#define MAX_COMBO_INFO 128

struct COMBO_SKILL_INFO
{
	WORD Stage;
	WORD Skill;
	DWORD Delay;
};

class CComboSkillData
{
public:
	CComboSkillData();

	void Load(char* path);
	void SetInfo(COMBO_SKILL_INFO info);
	COMBO_SKILL_INFO* GetInfoBySkill(WORD skill);
	DWORD GetSkillDelay(WORD skill);
	int	GetSkillType(WORD skill);

private:
	int m_Count;
	COMBO_SKILL_INFO m_Info[MAX_COMBO_INFO];
};

extern CComboSkillData gComboSkillData;