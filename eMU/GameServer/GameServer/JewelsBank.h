#pragma once
//----

#include "User.h"
#include "Protocol.h"
//----

struct BANKEX_GD_SAVE_POINT
{
	PSBMSG_HEAD	h;
	// ----
	WORD	UserIndex;
	char	AccountID[11];
	long	Bless;
	long	Soul;
	long	Chaos;
	long	Creation;
	long	Life;
	long	Harmony;
};
// -------------------------------------------------------------------------------

struct BANKEX_GD_REQ_POINT
{
	PSBMSG_HEAD	h;
	// ----
	WORD	UserIndex;
	char	AccountID[11];
};
// -------------------------------------------------------------------------------
struct PMSG_JEWELSBANK_RECV
{
	PSBMSG_HEAD header;
	int Type;
	int	Count;
};
//
struct BANKEX_DG_GET_POINT
{
	PSBMSG_HEAD	h;
	// ----
	WORD	UserIndex;
	long	Bless;
	long	Soul;
	long	Chaos;
	long	Creation;
	long	Life;
	long	Harmony;
};

struct PMSG_BANKEX_UPDATE_SEND
{
	PSBMSG_HEAD header;
	long	Bless;
	long	Soul;
	long	Chaos;
	long	Creation;
	long	Life;
	long	Harmony;
};
// -------------------------------------------------------------------------------

enum eBankExType
{
	BANKEX_BLESS = 0,
	BANKEX_SOUL = 1,
	BANKEX_CHAOS = 2,
	BANKEX_CREATION = 3,
	BANKEX_LIFE = 4,
	BANKEX_HARMONY = 5,
};

class CBankEx
{
public:
	CBankEx();
	virtual ~CBankEx();
	void InitUser(LPOBJ lpObj);
	void GDSavePoint(int aIndex);
	void GDReqPoint(int aIndex);
	void DGGetPoint(BANKEX_DG_GET_POINT * aRecv);
	void GCUpdateBankEx(int aIndex);
	void JewelSend(PMSG_JEWELSBANK_RECV * lpMsg,LPOBJ lpObj);
	void JewelRecv(PMSG_JEWELSBANK_RECV * lpMsg,LPOBJ lpObj);
}; extern CBankEx gBankEx;