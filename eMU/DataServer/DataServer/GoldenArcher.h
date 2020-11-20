#pragma once

#include "DataServerProtocol.h"

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
  /*<thisrel this+0x0>*/ /*|0x3|*/ struct PSBMSG_HEAD header;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
  /*<thisrel this+0x8>*/ /*|0x1|*/ unsigned char Pos;
  /*<thisrel this+0x9>*/ /*|0xb|*/ char szUID[11];
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
  /*<thisrel this+0x0>*/ /*|0x3|*/ struct PSBMSG_HEAD header;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int iINDEX;
  /*<thisrel this+0x8>*/ /*|0xb|*/ char szUID[11];
  /*<thisrel this+0x13>*/ /*|0x1|*/ bool result;
  /*<thisrel this+0x14>*/ /*|0x2|*/ short nEVENT_CHIPS;
  /*<thisrel this+0x18>*/ /*|0x4|*/ int iMUTO_NUM;
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

class CGoldenArcher
{
public:
	CGoldenArcher();
	virtual ~CGoldenArcher();
	void GDEventChipInfo(PMSG_REQ_VIEW_EC_MN* lpMsg, int aIndex);
	void GDRegEventChips(PMSG_REQ_REGISTER_EVENTCHIP * lpMsg, int aIndex);
	void GDResetEventChip(PMSG_REQ_RESET_EVENTCHIP * lpMsg, int aIndex);
};

extern CGoldenArcher gGoldenArcher;