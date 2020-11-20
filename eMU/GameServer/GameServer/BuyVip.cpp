#include "stdafx.h"
#include "BuyVip.h"
#include "ServerInfo.h"
#include "Notice.h"
#include "Message.h"
#include "JSProtocol.h"
#include "CashShop.h"
#include "Util.h"

cBuyAccountLevel gBuyAccountLevel;

cBuyAccountLevel::cBuyAccountLevel()
{
	this->Init();
}

cBuyAccountLevel::~cBuyAccountLevel()
{
	
}

void cBuyAccountLevel::Init()
{
	this->m_Price_AL1 = 0;
	this->m_Price_AL2 = 0;
	this->m_Price_AL3 = 0;
	this->m_VipTime = 0;
}

void cBuyAccountLevel::Load(char* path)
{
	this->m_Price_AL1				= GetPrivateProfileInt("Common", "Price_AL1", 0, path);
	this->m_Price_AL2				= GetPrivateProfileInt("Common", "Price_AL2", 0, path);
	this->m_Price_AL3				= GetPrivateProfileInt("Common", "Price_AL3", 0, path);
	this->m_VipTime					= GetPrivateProfileInt("Common", "PricePerDay", 0, path);
}

void cBuyAccountLevel::SendInfo(int aIndex)
{
	PMSG_BUYAL_DATA pRequest;
	pRequest.Head.set(0xFB,0x09, sizeof(pRequest));

	pRequest.Price_AL1 = this->m_Price_AL1;
	pRequest.Price_AL2 = this->m_Price_AL2;
	pRequest.Price_AL3 = this->m_Price_AL3;

	pRequest.Exp_AL1 = gServerInfo.m_AddExperienceRate[1];
	pRequest.Exp_AL2 = gServerInfo.m_AddExperienceRate[2];
	pRequest.Exp_AL3 = gServerInfo.m_AddExperienceRate[3];

	pRequest.Drop_AL1 = gServerInfo.m_ItemDropRate[1];
	pRequest.Drop_AL2 = gServerInfo.m_ItemDropRate[2];
	pRequest.Drop_AL3 = gServerInfo.m_ItemDropRate[3];

	pRequest.TimePrice = this->m_VipTime;

	DataSend(aIndex, (LPBYTE)&pRequest, sizeof(pRequest));
}

bool cBuyAccountLevel::CheckReq(int Type, LPOBJ lpObj)
{

	if (Type == 1)
	{
		if (lpObj->WCoinCaRecv < this->m_Price_AL1)
		{
			return false;
		}
	}

	if (Type == 2)
	{
		if (lpObj->WCoinCaRecv < this->m_Price_AL2)
		{
			return false;
		}
	}

	if (Type == 3)
	{
		if (lpObj->WCoinCaRecv < this->m_Price_AL3)
		{
			return false;
		}
	}
	return true;
}

void cBuyAccountLevel::RecvBuyVip(CG_BUYVIP_RECV* Data, int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->AccountLevel == 2 && Data->VipType == 1 || lpObj->AccountLevel == 3 && Data->VipType == 2)
	{
		return;
	}

	int Price = 0;
	if (Data->VipType == 1)
	{
		Price += this->m_Price_AL1;
	}
	else if (Data->VipType == 2)
	{
		Price += this->m_Price_AL2;
	}
	else if (Data->VipType == 3)
	{
		Price += this->m_Price_AL3;
	}

	int VipTime = 0;

	VipTime = Data->VipTime * 86400;

	Price += Data->VipTime * this->m_VipTime;

	if(lpObj->WCoinCaRecv < Price)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(628),Price);
		return;
	}

	gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,Price,0,0);

	GJAccountLevelSaveSend(lpObj->Index,Data->VipType,VipTime);
	GJAccountLevelSend(lpObj->Index);

	gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(629));

}

void cBuyAccountLevel::CheckStatus(LPOBJ lpObj)
{
	char szStatus[50];

	if (lpObj->AccountLevel < 1)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "[VIP] You do not have VIP status. Buy it!");
		return;
	}

	switch (lpObj->AccountLevel)
	{
		case 1: sprintf(szStatus, "Silver");	break;
		case 2: sprintf(szStatus, "Gold");		break;
		case 3: sprintf(szStatus, "Platinum");	break;
	}
	//this->SendMsg(lpObj->m_Index, 0, "@[VIP] You used %s vip status. Time left: %d", szStatus, lpObj->AccountExpireDate);
	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage((  248+lpObj->AccountLevel)),lpObj->AccountExpireDate);
}