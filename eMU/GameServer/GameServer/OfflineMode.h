#pragma once
// -------------------------------------------------------------------------------
#include "Protocol.h"
// -------------------------------------------------------------------------------
struct PMSG_OFFLINEMODE_REQ
{
	PSBMSG_HEAD	Head;
	// ----
	int OffType;
	int SkillData[3];
	int SkillIndex[3];
	char SkillName[3][32];
	int DrawBuffs;
	int DrawPick;
};

struct PMSG_OFFLINEMODE_DATA_RECV
{
	PSBMSG_HEAD	h;
	// ----
	int SkillID;
	bool UseBuff;
	bool PickZen;
	bool PickJewels;
	bool PickExe;
	bool PickAnc;
	bool PickSelected;
};

enum OffModeType
{
	TYPE_DW,
	TYPE_DK,
	TYPE_FE,
	TYPE_BMG,
	TYPE_EMG,
	TYPE_DL,
	TYPE_SU,
	TYPE_RF,
};
// -------------------------------------------------------------------------------

struct SKILLS_INFO
{
	int SkillID;
	int SkillEffect;
	int Class;
};

class cOfflineMode
{
public:
	cOfflineMode();
	void LoadSkillsInfo(char* path);
	void Load(char* section, char* path);
	void GCOfflineModeSend(int aIndex);
	void CGOfflineModeRecv(int aIndex);
	bool CheckSkill(LPOBJ lpObj, int SkillNumber);
	void CGOfflineModeStartRecv(PMSG_OFFLINEMODE_DATA_RECV* Data, int aIndex);
	void PickItems(LPOBJ lpObj);
#if (USE_OFFLINEMODE_HELPER_PICK == TRUE)
	void GetSelectedItems(LPOBJ lpObj);
#endif
	void UseBuffs(LPOBJ lpObj);
	std::vector<SKILLS_INFO> m_Skills;
	//----
private:
	int CanUseBuffs[MAX_ACCOUNT_LEVEL];
	int CanUsePick[MAX_ACCOUNT_LEVEL];
}; extern cOfflineMode gOfflineMode;