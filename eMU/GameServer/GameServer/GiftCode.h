// Move.h: interface for the CMove class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Protocol.h"
#include "User.h"

#define MAX_GIFTCODE 20
struct GIFTCODE_INFO
{
	int Index;
	char GiftName[11];
	int GiftCount;
	int	SetID;
	int	WeaponID;
	int	PetID;
	int	BuffID;
	int	ItemTime;
};

struct GiftCode
{
	PSWMSG_HEAD h;
	BYTE Result;
};

struct GiftInfo
{
	int	GiftIndex;
	char GiftName[11];
	int	GiftCount;
};

struct DGGiftCode
{
	PSWMSG_HEAD h;
	GiftInfo	tp[MAX_GIFTCODE];
};

class CGiftCode
{
public:
	CGiftCode();
	virtual ~CGiftCode();
	void Load(char* path);
	void RecvDS(DGGiftCode *Recv);
	void GetMove(LPOBJ lpObj,int index);
    bool GetInfo(int index,GIFTCODE_INFO* lpInfo);
    bool GetInfoByName(char* message,GIFTCODE_INFO* lpInfo);
	GiftInfo GiftCodeInfo[MAX_GIFTCODE];
	GIFTCODE_INFO GiftCode[MAX_GIFTCODE];
private:
	std::map<int,GIFTCODE_INFO> m_GiftCodeInfo;
};

extern CGiftCode gGiftCode;
