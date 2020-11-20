// CustomAttack.h: interface for the CCustomAttack class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "User.h"

#if USE_OFFEXP_RELOAD == TRUE
struct OFFEXP_DATA
{
	char Account[11];
	char Password[11];
	char Name[11];
	char IP[16];
	int SkillID;
	int UseBuffs;
	int Pick;
};
#endif

class CCustomAttack
{
public:
	CCustomAttack();
	virtual ~CCustomAttack();
	void ReadCustomAttackInfo(char* section,char* path);
	void CommandCustomAttack(LPOBJ lpObj,char* arg);
	void CommandCustomAttackOffline(LPOBJ lpObj,char* arg);
	bool GetAttackSkill(LPOBJ lpObj,int* SkillNumber);
	bool GetTargetMonster(LPOBJ lpObj,int SkillNumber,int* MonsterIndex);
	bool CheckRequireMoney(LPOBJ lpObj);
	void OnAttackClose(LPOBJ lpObj);
	void OnAttackSecondProc(LPOBJ lpObj);
	void OnAttackAlreadyConnected(LPOBJ lpObj);
	void OnAttackMonsterAndMsgProc(LPOBJ lpObj);
	void ElfBuffs(LPOBJ lpObj);
	void SendSkillAttack(LPOBJ lpObj,int aIndex,int SkillNumber);
	void SendMultiSkillAttack(LPOBJ lpObj,int aIndex,int SkillNumber);
	void SendDurationSkillAttack(LPOBJ lpObj,int aIndex,int SkillNumber);
#if USE_OFFEXP_RELOAD == TRUE
	void RestoreOffline();
	OFFEXP_DATA* GetOffExpInfo(LPOBJ lpObj);
	OFFEXP_DATA* GetOffExpInfoByAccount(LPOBJ lpObj);
	void LoadOffExp(char* path);
	void AddToList(LPOBJ lpObj);
	void DelFromList(char* account);
	void WriteToFile();
#endif
public:
	int m_CustomAttackSwitch;
	int m_CustomAttackEnable[4];
	int m_CustomAttackRequireLevel[4];
	int m_CustomAttackRequireReset[4];
	char m_CustomAttackCommandSyntax[32];
	char m_CustomAttackText1[128];
	char m_CustomAttackText2[128];
	char m_CustomAttackText3[128];
	char m_CustomAttackText4[128];
	char m_CustomAttackText5[128];
	char m_CustomAttackText6[128];
	int m_CustomAttackOfflineSwitch;
	int m_CustomAttackOfflineGPGain;
	int m_CustomAttackOfflineEnable[4];
	int m_CustomAttackOfflineRequireLevel[4];
	int m_CustomAttackOfflineRequireReset[4];
	int m_CustomAttackOfflineRequireMoney[4];
	char m_CustomAttackOfflineCommandSyntax[32];
	char m_CustomAttackOfflineText1[128];
	char m_CustomAttackOfflineText2[128];
	char m_CustomAttackOfflineText3[128];
	char m_CustomAttackOfflineText4[128];
	char m_CustomAttackOfflineText5[128];
	char m_CustomAttackOfflineText6[128];
#if USE_OFFEXP_RELOAD == TRUE
	std::map<std::string,OFFEXP_DATA> m_Data;
	int AccountsRestored;
#endif
};

extern CCustomAttack gCustomAttack;
