#pragma once
#include "Protocol.h"

struct ACTIVE_TITLE_REQ
{
	PSBMSG_HEAD h;
	int			Type;
	int			Number;
};

struct BUY_TITLE_REQ
{
	PSBMSG_HEAD h;
	int			Number;
};

struct DEACTIVE_TITLE_REQ
{
	PSBMSG_HEAD h;
};

struct PMSG_HORNOR_UPD
{
	PSBMSG_HEAD h;
	int		RankSlot;
	int		RankTitle[20];
	int		SurvivorPlayer;
	int		IsSurvivor;
};

class DanhHieu
{
public:
	DanhHieu();
	~DanhHieu();
	void Active(int Type, int Number);
	void BuyTitle(int Number);
	void GetInfo(PMSG_HORNOR_UPD * aRecv);
	void Deactive();
	//
	int		m_RankSlot;
	int		m_RankTitle[20];
	int		SurvivorPlayer;
	int		IsSurvivor;
	//
}; extern DanhHieu gDanhHieu;
