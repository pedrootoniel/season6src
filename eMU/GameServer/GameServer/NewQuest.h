#pragma once
// -------------------------------------------------------------------------
#include "Protocol.h"
#include "user.h"
// -------------------------------------------------------------------------

#define MAX_QUESTS 300
// -------------------------------------------------------------------------

struct QUESTDATA
{
	int q_Index;
	int q_MobID;
	int q_MobCnt;
	int q_Type;
	int q_ItemID;
	int q_ItemLvl;
	char szHint[255];
};

struct NPCDATA
{
};

// -------------------------------------------------------------------------

class CQuestSystem
{
public:
	CQuestSystem();
	virtual ~CQuestSystem();
	void Init();
	void Load(char *filename);
	void SetInfo(QUESTDATA info);
	// ----
	bool Dialog(LPOBJ lpUser, LPOBJ lpNpc);
	void TalkToNpc(int aIndex);
	bool GetQuest(int index);
	void MonsterKill(LPOBJ lpObj, LPOBJ lpTarget);
	// ----
	void SendMsg(int aIndex, int type, char* szMsg, ...);
	//void MonsterBarAdd(int aIndex, int MonsterID);
	void MakeItem(LPOBJ lpObj, int QuestIndex);
	// ----
	//void Effect(LPOBJ lpUser);
	// ----
	int Enable;
	int ID;
	int Map;
	int X;
	int Y;
	// ----
	int q_Index;
	int q_MobID;
	int q_MobCnt;
	int q_Type;
	int q_ItemID;
	int q_ItemLvl;
	char szHint[255];
	// ----
	QUESTDATA m_Quest[MAX_QUESTS];
	// ----
}; extern CQuestSystem gCustomQuest;
// -------------------------------------------------------------------------