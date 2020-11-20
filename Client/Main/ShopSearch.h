#pragma once
// ----------------------------------------------------------------------------------------------
#define SHOPSEARCH TRUE
#include "stdafx.h"
#include "Protocol.h"
#include "Defines.h"
//#include "ProtocolDefine.h"
//#include "OffTrade.h"
// ----------------------------------------------------------------------------------------------

#define pGameIndex    *(DWORD*)0x87935A8

#if(SHOPSEARCH==TRUE)
// ----------------------------------------------------------------------------------------------
struct GC_PersonalShopInfo
{
	WORD aIndex;
	char Name[11];
	char PersonalText[36];
	BYTE Value;
};
// ----------------------------------------------------------------------------------------------
struct CG_PersonalPage
{
	PSBMSG_HEAD h;
	BYTE Page;
};
// ----------------------------------------------------------------------------------------------
struct PMSG_REQ_BUYLIST_FROM_PSHOP
{
	PSBMSG_HEAD header; // C1:3F:05
	BYTE index[2];
	char name[10];	// 6
};
// ----------------------------------------------------------------------------------------------
struct PersonalShop_DATA
{
	WORD aIndex;
	char Name[11];
	char PersonalText[36];
	BYTE Value;
};
// ----------------------------------------------------------------------------------------------

class PersonalShopEx
{
public:
	// -> Load
	void BindImages();
	// Draw Interface
	void Draw();
	// -> Controller
	void Button(DWORD Event);
	// -> Protocol
	void GC_Recv(LPBYTE aRecv);
	void CG_Send();
	// -> Hook
	// -> Other
	int Page;
	int TotalShop;
	int aTargetIndex;
	char TargetName[11];
	PersonalShop_DATA PShop[10];
};
extern PersonalShopEx g_PersonalShopEx;
// ----------------------------------------------------------------------------------------------

#endif