#pragma once

#include "Protocol.h"

#define MAX_EVENTCHIP_TYPE	5

#define EVENCHIP_TYPE_RANGE(x)  ( ((x)<0)?FALSE:((x)>MAX_EVENTCHIP_TYPE-1)?FALSE:TRUE )

// --------------------------------------------------------
// GameServer -> DataServer
// --------------------------------------------------------
struct PMSG_REQ_VIEW_EC_MN
{
	PSBMSG_HEAD header;
	// ----
	int		aIndex;
	char	AccountID[11];
};

struct PMSG_REQ_REGISTER_EVENTCHIP
{
	PSBMSG_HEAD header;
	int iINDEX;	// 4
	BYTE Pos;	// 8
	char szUID[11];	// 9
};

struct PMSG_REQ_REGISTER_STONES
{
	PSBMSG_HEAD header;
	int iINDEX;	// 4
	BYTE iPosition;	// 8
	char szUID[11];	// 9
};

struct PMSG_REQ_RESET_EVENTCHIP
{
	PSBMSG_HEAD header;	// C1:[04:Rena] [09:Stone]
	int iINDEX;	// 4
	char szUID[11];	// 8
};
// --------------------------------------------------------

// --------------------------------------------------------
// DataServer -> GameServer
// --------------------------------------------------------
struct PMSG_ANS_VIEW_EC_MN
{
	struct PSBMSG_HEAD header;
	int iINDEX;
	char szUID[11];
	bool result;
	short nEVENT_CHIPS;
	int iMUTO_NUM;
};

struct PMSG_ANS_REGISTER_EVENTCHIP
{
	PSBMSG_HEAD header;
	int iINDEX;	// 4
	BYTE Pos;	// 8
	char szUID[11];	// 9
	bool bSUCCESS;	// 14
	int nEVENT_CHIPS;	// 16
};

struct PMSG_ANS_RESET_EVENTCHIP
{
    PSBMSG_HEAD header;//0x0
    int iINDEX;//0x04
    char szUID[11];//0x08
    bool bSUCCESS;//0x13
};
// --------------------------------------------------------

// --------------------------------------------------------
// GameServer -> Client
// --------------------------------------------------------
struct PMSG_EVENTCHIPINFO
{
	PBMSG_HEAD h;	// C1:94
	BYTE Type;	// 3
	int ChipCount;	// 4
	short MutoNum[3];	// 6
};
// --------------------------------------------------------

// --------------------------------------------------------
// Client -> GameServer
// --------------------------------------------------------
struct PMSG_REGEVENTCHIP
{
	PBMSG_HEAD h;
	BYTE Type;	// 3
	BYTE ChipPos;	// 4
};

// --------------------------------------------------------

struct PMSG_REGEVENTCHIP_RESULT
{
	PBMSG_HEAD h;	// C1:95
	BYTE Type;	// 3
	int ChipCount;	// 4
};
// --------------------------------------------------------

class CGoldenArcher
{
public:
	CGoldenArcher();
	virtual ~CGoldenArcher();
	void GoldenArcherNPC(LPOBJ lpNpc, LPOBJ lpObj);
	void RecvGoldenArcher(PMSG_ANS_VIEW_EC_MN* aRecv);
	void CGRegEventChipRecv(PMSG_REGEVENTCHIP* lpMsg, int aIndex);
	void DGResultRegEventChip(PMSG_ANS_REGISTER_EVENTCHIP * aRecv);
	void DGRecvChangeRena( PMSG_ANS_RESET_EVENTCHIP* aRecv);
	void GCUseEndEventChipRecv(int aIndex);
}; extern CGoldenArcher gGoldenArcher;