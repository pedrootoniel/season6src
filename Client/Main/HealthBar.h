#pragma once

#include "Protocol.h"

#define RGBTOGLFLOAT(x) ((float)x/255.0f)
#define FLOATTORGB(x)	((float)x*255)
#define ABS(x) (((x) < 0) ? (-(x)) : (x))

#define MAX_MAIN_VIEWPORT 400
struct NEW_HEALTH_BAR
{
	WORD index;
	BYTE type;
	BYTE rate;
	WORD monsterid;
	float Life;
	float MaxLife;
	short Level;
	int Shield;
	int MaxShield;
	BYTE SDrate;
	bool isSameGuild;
	int RankTitle;
	//bool HaveGuild;
	//char GuildName[9];
	//BYTE Mark[64];
};

class CHPBar
{
public:
	CHPBar();
	virtual ~CHPBar();
	void ClearNewHealthBar();
	void InsertNewHealthBar(PMSG_NEW_HEALTH_RECV* lpInfo);
	NEW_HEALTH_BAR* GetNewHealthBar(WORD index,BYTE type);
	void DrawHealthBar();
	static void DrawAllHPBars();
	bool IsPartyMember(int ViewportID);
	//int GetCountOfNumbers(int n);
	char* del_char(char* s, char c);
	//char* GetHPValue(int HP);
	char* ParseReducedValue(DWORD Num);
	//void ChangeState();
	// -- Title Load
    void        LoadRankTitle();
    static void DrawRankTitle_1 ( int Title, int PosX, int PosY );
    static void DrawRankTitle_2 ( int Title, int PosX, int PosY );
	int RankTextColor[15];
	//
	DWORD		m_TargetUpdateTick;
	bool		PlayerHPBar;
	bool		TitleBar;
	bool		LifeBar;
	//
}; extern CHPBar gHPBar;
