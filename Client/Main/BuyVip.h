#pragma once

#include "Protocol.h"

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

struct CG_BUYVIP_SEND
{
	PSBMSG_HEAD	Head;
	int VipType;
	int	VipTime;
};

class cBuyVip
{
public:
	cBuyVip(void);
	virtual ~cBuyVip(void);
	void Init();
	void RecvData(PMSG_BUYAL_DATA* Data);
	void SendBuyVip(int Type,int Time);
	// ----
	int m_Price_AL1;
	int m_Price_AL2;
	int m_Price_AL3;
	int m_Exp_AL1;
	int m_Exp_AL2;
	int m_Exp_AL3;
	int m_Drop_AL1;
	int m_Drop_AL2;
	int m_Drop_AL3;
	int	m_TimePrice;
}; extern cBuyVip gBuyVip;

