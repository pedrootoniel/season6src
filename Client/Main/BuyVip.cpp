#include "stdafx.h"
#include "BuyVip.h"

cBuyVip gBuyVip;

cBuyVip::cBuyVip()
{
	this->Init();
}


cBuyVip::~cBuyVip()
{

}

void cBuyVip::Init()
{
	this->m_Price_AL1 = 0;
	this->m_Price_AL2 = 0;
	this->m_Price_AL3 = 0;
	this->m_Exp_AL1 = 0;
	this->m_Exp_AL2 = 0;
	this->m_Exp_AL3 = 0;
	this->m_Drop_AL1 = 0;
	this->m_Drop_AL2 = 0;
	this->m_Drop_AL3 = 0;
	this->m_TimePrice = 0;
}

void cBuyVip::RecvData(PMSG_BUYAL_DATA* Data)
{
	this->m_Price_AL1 = Data->Price_AL1;
	this->m_Price_AL2 = Data->Price_AL2;
	this->m_Price_AL3 = Data->Price_AL3;
	this->m_Exp_AL1 = Data->Exp_AL1;
	this->m_Exp_AL2 = Data->Exp_AL2;
	this->m_Exp_AL3 = Data->Exp_AL3;
	this->m_Drop_AL1 = Data->Drop_AL1;
	this->m_Drop_AL2 = Data->Drop_AL2;
	this->m_Drop_AL3 = Data->Drop_AL3;
	this->m_TimePrice = Data->TimePrice;
}

void cBuyVip::SendBuyVip(int Type,int Time)
{
	CG_BUYVIP_SEND pRequest;
	pRequest.Head.set(0xFF,0x06,sizeof(pRequest));	
	pRequest.VipType = Type;
	pRequest.VipTime = Time;
	DataSend((BYTE*)&pRequest,pRequest.Head.size);
}