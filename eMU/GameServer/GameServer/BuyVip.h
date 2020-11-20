#pragma once

#include "Protocol.h"
#include "User.h"

struct PMSG_BUYAL_DATA
{
	PSBMSG_HEAD	Head;
	int Price_AL1;
	int Price_AL2;
	int Price_AL3;
	int Exp_AL1;
	int Exp_AL2;
	int Exp_AL3;
	int Drop_AL1;
	int Drop_AL2;
	int Drop_AL3;
	int	TimePrice;
};

struct CG_BUYVIP_RECV
{
	PSBMSG_HEAD	Head;
	int VipType;
	int	VipTime;
};

class cBuyAccountLevel
{
public:
	cBuyAccountLevel();
	virtual ~cBuyAccountLevel();
	void Init();
	void Load(char* path);
	void SendInfo(int aIndex);
	void RecvBuyVip(CG_BUYVIP_RECV* Data, int aIndex);
	bool CheckReq(int Type, LPOBJ lpObj);
	void CheckStatus(LPOBJ lpObj);
	//
	int m_Price_AL1;
	int m_Price_AL2;
	int m_Price_AL3;
	int	m_VipTime;
}; extern cBuyAccountLevel gBuyAccountLevel;