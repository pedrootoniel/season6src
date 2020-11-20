#pragma once

#include "User.h"

#define MAX_TVTEVENT 10
#define MAX_TVTEVENT_USER 20

enum eTvTEventState
{
	TVT_EVENT_STATE_BLANK = 0,
	TVT_EVENT_STATE_EMPTY = 1,
	TVT_EVENT_STATE_STAND = 2,
	TVT_EVENT_STATE_START = 3,
	TVT_EVENT_STATE_CLEAN = 4,
};

enum eTvTTeams
{
	TVT_BLUETEAM = 1,
	TVT_REDTEAM = 2,
};

struct TVT_EVENT_START_TIME
{
	int Year;
	int Month;
	int Day;
	int DayOfWeek;
	int Hour;
	int Minute;
	int Second;
};

struct TVT_EVENT_USER
{
	void Reset() // OK
	{
		this->Index = -1;
		this->Available = false;
		this->Team = -1;
		this->Kills = 0;
		this->Deaths = 0;
	}

	int Index;
	bool Available;
	int Team;
	int Kills;
	int Deaths;
};

struct TVT_EVENT_RULE_INFO
{
	char Name[32];
	int AlarmTime;
	int StandTime;
	int EventTime;
	int CloseTime;
	int ReqItemCount;
	int ReqItemIndex;
	int ReqItemLevel;
	int EventMap;
	int WaitingGate;
	int BluTeamGate;
	int RedTeamGate;
	int SetSkin;
	int RewardItemCount;
	int ItemRewardIndex;
	int ItemRewardLevel;
	int RewardWCoinC;
	int RewardWCoinP;
	int RewardWCoinG;
};

struct TVT_EVENT_INFO
{
	int Index;
	int State;
	int RemainTime;
	int TargetTime;
	int TickCount;
	int EnterEnabled;
	int AlarmMinSave;
	int AlarmMinLeft;
	// ----
	int TotalPlayer;
	int ScoreBlue;
	int ScoreRed;
	// ----
	TVT_EVENT_RULE_INFO RuleInfo;
	TVT_EVENT_USER User[MAX_TVTEVENT_USER];
	std::vector<TVT_EVENT_START_TIME> StartTime;
};

class CTvTEvent
{
public:
	CTvTEvent();
	virtual ~CTvTEvent();
	void Init();
	void ReadTvTEventInfo(char* section,char* path);
	void Load(char * path);
	void MainProc();
	void ProcState_BLANK(TVT_EVENT_INFO* lpInfo);
	void ProcState_EMPTY(TVT_EVENT_INFO* lpInfo);
	void ProcState_STAND(TVT_EVENT_INFO* lpInfo);
	void ProcState_START(TVT_EVENT_INFO* lpInfo);
	void ProcState_CLEAN(TVT_EVENT_INFO* lpInfo);
	void SetState(TVT_EVENT_INFO* lpInfo,int state);
	void SetState_BLANK(TVT_EVENT_INFO* lpInfo);
	void SetState_EMPTY(TVT_EVENT_INFO* lpInfo);
	void SetState_STAND(TVT_EVENT_INFO* lpInfo);
	void SetState_START(TVT_EVENT_INFO* lpInfo);
	void SetState_CLEAN(TVT_EVENT_INFO* lpInfo);
	void CheckSync(TVT_EVENT_INFO* lpInfo);
	int GetState(int index);
	bool Dialog(LPOBJ lpObj, LPOBJ lpNpc);
	bool CheckEnterEnabled(LPOBJ lpObj);
	bool CheckReqItems(TVT_EVENT_INFO* lpInfo, LPOBJ lpObj);
	int GetEnterEnabled(int index);
	int GetEnteredUserCount(int index);
	bool CheckEnteredUser(int index,int aIndex);
	bool CheckPlayerTarget(LPOBJ lpObj);
	bool CheckPlayerJoined(LPOBJ lpObj,LPOBJ lpTarget);
	bool CheckSelfTeam(LPOBJ lpObj,LPOBJ lpTarget);
	bool CheckAttack(LPOBJ lpObj,LPOBJ lpTarget);
	bool AddUser(TVT_EVENT_INFO* lpInfo,int aIndex);
	bool DelUser(TVT_EVENT_INFO* lpInfo,int aIndex);
	TVT_EVENT_USER* GetUser(TVT_EVENT_INFO* lpInfo,int aIndex);
	void CleanUser(TVT_EVENT_INFO* lpInfo);
	void ClearUser(TVT_EVENT_INFO* lpInfo);
	void CheckUser(TVT_EVENT_INFO* lpInfo);
	int GetUserCount(TVT_EVENT_INFO* lpInfo);
	bool GetUserRespawnLocation(LPOBJ lpObj,int* gate,int* map,int* x,int* y,int* dir,int* level);
	void DivisionTeam(TVT_EVENT_INFO* lpInfo);
	int ReturnMaxReset(TVT_EVENT_INFO* lpInfo);
	void UserDieProc(LPOBJ lpObj,LPOBJ lpTarget);

	void NoticeSendToAll(TVT_EVENT_INFO* lpInfo,int type,char* message,...);
public:
	int m_TvTEventSwitch;
	int m_TvTEventNPCId;
	int m_TvTEventNPCMap;
	int m_TvTEventNPCX;
	int m_TvTEventNPCY;
	char m_TvTEventText1[128];
	char m_TvTEventText2[128];
	char m_TvTEventText3[128];
	char m_TvTEventText4[128];
	char m_TvTEventText5[128];
	char m_TvTEventText6[128];
	char m_TvTEventText7[128];
	TVT_EVENT_INFO m_TvTEventInfo[MAX_TVTEVENT];
}; extern CTvTEvent gTvTEvent;