#include "stdafx.h"
#include "ChangeClass.h"
#include "Notice.h"
#include "MasterSkillTree.h"
#include "ObjectManager.h"
#include "ServerInfo.h"
#include "DSProtocol.h"
#include "Util.h"
#include "CashShop.h"
#include "Message.h"

cChangeClass gChangeClass;

cChangeClass::cChangeClass()
{
	this->Init();
}

cChangeClass::~cChangeClass()
{
	
}

void cChangeClass::Init()
{
	for (int i=0; i<MAX_ACCOUNT_LEVEL;i++)
	{
		this->m_Price[i] = 0;
		this->m_PriceType[i] = 0;
	}
}

void cChangeClass::Load(char* path)
{
	this->m_PriceType[0] = GetPrivateProfileInt("Common", "PriceType_AL0", 0, path);
	this->m_PriceType[1] = GetPrivateProfileInt("Common", "PriceType_AL1", 0, path);
	this->m_PriceType[2] = GetPrivateProfileInt("Common", "PriceType_AL2", 0, path);
	this->m_PriceType[3] = GetPrivateProfileInt("Common", "PriceType_AL3", 0, path);

	this->m_Price[0] = GetPrivateProfileInt("Common", "Price_AL0", 0, path);
	this->m_Price[1] = GetPrivateProfileInt("Common", "Price_AL1", 0, path);
	this->m_Price[2] = GetPrivateProfileInt("Common", "Price_AL2", 0, path);
	this->m_Price[3] = GetPrivateProfileInt("Common", "Price_AL3", 0, path);
}

void cChangeClass::SendData(int aIndex)
{
	PMSG_CHANGECLASS_DATA pRequest;
	pRequest.Head.set(0xFB,0x08, sizeof(pRequest));

	pRequest.PriceType = this->m_PriceType[gObj[aIndex].AccountLevel];
	pRequest.Price = this->m_Price[gObj[aIndex].AccountLevel];

	DataSend(aIndex, (LPBYTE)&pRequest, sizeof(pRequest));
}

void cChangeClass::RecvChangeClass(CG_CHANGECLASS_RECV* Data, int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gChangeClass.m_PriceType[lpObj->AccountLevel] == 0)
	{
		if (lpObj->Money < gChangeClass.m_Price[lpObj->AccountLevel])
		{
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "You do not have enough Zen");
			return;
		}
	}
	else if (gChangeClass.m_PriceType[lpObj->AccountLevel] == 1)
	{
		if (lpObj->WCoinCaRecv < gChangeClass.m_Price[lpObj->AccountLevel])
		{
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "You do not have enough wCoinC!");
			return;
		}
	}
	else if (gChangeClass.m_PriceType[lpObj->AccountLevel] == 2)
	{
		if (lpObj->WCoinPaRecv < gChangeClass.m_Price[lpObj->AccountLevel])
		{
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "You do not have enough wCoinP");
			return;
		}
	}
	else if (gChangeClass.m_PriceType[lpObj->AccountLevel] == 3)
	{
		if (lpObj->GPointaRecv < gChangeClass.m_Price[lpObj->AccountLevel])
		{
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "You do not have enough GoblinPoint");
			return;
		}
	}
	// ----
	for( int i = 0; i < 12; i++ )
	{
		if( lpObj->Inventory[i].IsItem() )
		{
			gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "You must remove all items!");
			return;
		}
	}

	gChangeClass.ChangeClass(lpObj,Data->Type);
}

void cChangeClass::ChangeClass(LPOBJ lpObj, int Class)
{
	int NextClass = 0;
	switch(Class)
	{
		case 0:
			NextClass = CLASS_DW;
			break;
		case 16:
			NextClass = CLASS_DK;
			break;
		case 32:
			NextClass = CLASS_FE;
			break;
		case 48:
			NextClass = CLASS_MG;
			break;
		case 64:
			NextClass = CLASS_DL;
			break;
		case 80:
			NextClass = CLASS_SU;
			break;
		case 96:
			NextClass = CLASS_RF;
			break;
	}


	int CurrentPoint = lpObj->MasterLevel;

	lpObj->MasterPoint = CurrentPoint;

	for(int n=0;n < MAX_SKILL_LIST;n++)
	{
		lpObj->Skill[n].Clear();
	}

	for(int n=0;n < MAX_MASTER_SKILL_LIST;n++)
	{
		lpObj->MasterSkill[n].Clear();
	}

	gMasterSkillTree.GCMasterSkillListSend(lpObj->Index);
	gSkillManager.GCSkillListSend(lpObj,0);
	gMasterSkillTree.GCMasterInfoSend(lpObj);
	gEffectManager.ClearAllEffect(lpObj);

	if (this->m_PriceType[lpObj->AccountLevel] == 0)
	{
		lpObj->Money -= this->m_Price[lpObj->AccountLevel];
		GCMoneySend(lpObj->Index, lpObj->Money);
	}
	else if (this->m_PriceType[lpObj->AccountLevel] == 1)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,this->m_Price[lpObj->AccountLevel],0,0);
	}
	else if (this->m_PriceType[lpObj->AccountLevel] == 2)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,0,this->m_Price[lpObj->AccountLevel],0);
	}
	else if (this->m_PriceType[lpObj->AccountLevel] == 3)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,0,0,this->m_Price[lpObj->AccountLevel]);
	}

	lpObj->DBClass = Class;
	memset(lpObj->Quest, (BYTE)-1, sizeof(lpObj->Quest));

	if( lpObj->PartyNumber >= 0 )
	{
		gParty.DelMember(lpObj->PartyNumber, lpObj->Index);
		lpObj->PartyTargetUser	= -1;
	}

	gObjectManager.CharacterCalcAttribute(lpObj->Index);

	GCNewCharacterInfoSend(lpObj);

	GDCharacterInfoSaveSend(lpObj->Index);
	// ----
	//gObjMoveGate(lpObj->Index, gDefaultClassInfo.m_DefaultClassInfo[NextClass].StartGate);

	gObjectManager.CharacterGameCloseSet(lpObj->Index, 1);
}
