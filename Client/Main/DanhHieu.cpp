#include "stdafx.h"
#include "DanhHieu.h"
#include "Protocol.h"
DanhHieu gDanhHieu;

DanhHieu::DanhHieu()
{
	ZeroMemory(&this->m_RankTitle, sizeof(this->m_RankTitle));
}
// -------------------------------------------------------------------------------

DanhHieu::~DanhHieu()
{
	// ----
}


void DanhHieu::GetInfo(PMSG_HORNOR_UPD * aRecv)
{
	this->m_RankSlot		=	aRecv->RankSlot;
	this->m_RankTitle[0]	=	aRecv->RankTitle[0];
	this->m_RankTitle[1]	=	aRecv->RankTitle[1];
	this->m_RankTitle[2]	=	aRecv->RankTitle[2];
	this->m_RankTitle[3]	=	aRecv->RankTitle[3];
	this->m_RankTitle[4]	=	aRecv->RankTitle[4];
	this->m_RankTitle[5]	=	aRecv->RankTitle[5];
	this->m_RankTitle[6]	=	aRecv->RankTitle[6];
	this->m_RankTitle[7]	=	aRecv->RankTitle[7];
	this->m_RankTitle[8]	=	aRecv->RankTitle[8];
	this->m_RankTitle[9]	=	aRecv->RankTitle[9];
	this->m_RankTitle[10]	=	aRecv->RankTitle[10];
	this->m_RankTitle[11]	=	aRecv->RankTitle[11];
	this->m_RankTitle[12]	=	aRecv->RankTitle[12];
	this->m_RankTitle[13]	=	aRecv->RankTitle[13];
	this->m_RankTitle[14]	=	aRecv->RankTitle[14];
	this->m_RankTitle[15]	=	aRecv->RankTitle[15];
	this->m_RankTitle[16]	=	aRecv->RankTitle[16];
	this->m_RankTitle[17]	=	aRecv->RankTitle[17];
	this->m_RankTitle[18]	=	aRecv->RankTitle[18];
	this->m_RankTitle[19]	=	aRecv->RankTitle[19];
	this->IsSurvivor	=	aRecv->IsSurvivor;
	this->SurvivorPlayer	=	aRecv->SurvivorPlayer;
}

void DanhHieu::Active(int Type, int Number)
{
	ACTIVE_TITLE_REQ pRequest;
	pRequest.h.set(0xFB, 0x12, sizeof(pRequest));
	pRequest.Type = Type;
	pRequest.Number = Number;
	DataSend((BYTE*)&pRequest, pRequest.h.size);
}

void DanhHieu::Deactive()
{
	DEACTIVE_TITLE_REQ pRequest;
	pRequest.h.set(0xFB, 0x14, sizeof(pRequest));
	DataSend((BYTE*)&pRequest, pRequest.h.size);
}
// -------------------------------------------------------------------------------

void DanhHieu::BuyTitle(int Number)
{
	BUY_TITLE_REQ pMsg;
	pMsg.h.set(0xFB, 0x13, sizeof(pMsg));
	pMsg.Number = Number;
	DataSend((BYTE*)&pMsg, pMsg.h.size);
}