// CustomOnlineLottery.h: interface for the CCustomOnlineLottery class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include "User.h"
#include "Protocol.h"
#pragma once
struct LUCKYNUMBER_REQ
{
	PSBMSG_HEAD header;
	int	lines; // 
};


class cLuckyNumber
{
public:
	// ----

	cLuckyNumber();
	virtual ~cLuckyNumber();
	void Start(LPOBJ lpUser,LUCKYNUMBER_REQ *aRecv);
	void MakeLuckyNumber(int aIndex);
	int	Enable;
	int	WinPrice;
	int	TicketPrice;
	int LuckyNumber;
	int Number[5];
	int	TicketID;
	char msg[5][128];
	// ----
}; extern cLuckyNumber gLuckyNumber;