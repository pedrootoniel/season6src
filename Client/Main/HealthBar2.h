#pragma once
#include "Object.h"
#include "Protocol.h"
#ifdef NOLOAD
#pragma pack(push, 1)
struct PMSG_TARGETDATA_REQ
{
	PSWMSG_HEAD header;
	int			aIndex;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PMSG_TARGETDATA_ANS
{
	PSWMSG_HEAD header;
	int aIndex;
    bool isMonster;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PMSG_TARGET_MONSTER_DATA : PMSG_TARGETDATA_ANS
{
    int Life;
    int MaxLife;
    short Level;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PMSG_TARGET_PLAYER_DATA : PMSG_TARGET_MONSTER_DATA
{
	int	RankTitle;
	int	SurvivorDie;
	int	SurvivorKill;
    int SD;
    int MaxSD;

};
#pragma pack(pop)

class cHPBar
{
public:
	void		Load();
	DWORD		m_TargetUpdateTick;
	bool		PlayerHPBar;
	bool		TitleBar;
	bool		LifeBar;
	int			SurvivorKill;
	int			SurvivorDie;
	// -- Title Load
    void        LoadRankTitle();
    static void DrawRankTitle_1 ( int Title, int PosX, int PosY );
    static void DrawRankTitle_2 ( int Title, int PosX, int PosY );
	int RankTextColor[15];
	// --
	static char* ParsingHP(DWORD Num);
	char* del_char(char* s, char c);
	static void DrawHP();
	void SetTargetData(PMSG_TARGETDATA_ANS * lpMsg);

};
extern cHPBar gHPBar;
#endif