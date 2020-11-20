#include "stdafx.h"
#include "JewelsBank.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "ItemManager.h"
#include "ServerInfo.h"
#include "Notice.h"
#include "Util.h"
#include "Message.h"
CBankEx gBankEx;

CBankEx::CBankEx()
{
	
}

CBankEx::~CBankEx()
{
	
}

void CBankEx::InitUser(LPOBJ lpObj)
{
	lpObj->BankEx.JBless		= 0;
	lpObj->BankEx.JSoul			= 0;
	lpObj->BankEx.JChaos		= 0;
	lpObj->BankEx.JCreation		= 0;
	lpObj->BankEx.JLife			= 0;
	lpObj->BankEx.JHarmony		= 0;
}

void CBankEx::GDSavePoint(int aIndex)
{
	if( !gObjIsConnected(aIndex) )
	{
		return;
	}
	// ----
	LPOBJ lpUser = &gObj[aIndex];
	// ----
	BANKEX_GD_SAVE_POINT pRequest;
	pRequest.h.set(0xD9, 0x16, sizeof(pRequest));
	memcpy(pRequest.AccountID, lpUser->Account, sizeof(lpUser->Account));
	pRequest.UserIndex	= aIndex;
	pRequest.Bless		= lpUser->BankEx.JBless;
	pRequest.Soul		= lpUser->BankEx.JSoul;
	pRequest.Chaos		= lpUser->BankEx.JChaos;
	pRequest.Creation	= lpUser->BankEx.JCreation;
	pRequest.Life		= lpUser->BankEx.JLife;
	pRequest.Harmony	= lpUser->BankEx.JHarmony;
	gDataServerConnection.DataSend((BYTE*)&pRequest,pRequest.h.size);
}
// -------------------------------------------------------------------------------

void CBankEx::GDReqPoint(int aIndex)
{
	// ----
	LPOBJ lpUser = &gObj[aIndex];
	// ----
	BANKEX_GD_REQ_POINT pRequest;
	pRequest.h.set(0xD9, 0x15, sizeof(pRequest));
	memcpy(pRequest.AccountID, lpUser->Account, sizeof(lpUser->Account));
	pRequest.UserIndex = aIndex;
	gDataServerConnection.DataSend((BYTE*)&pRequest,pRequest.h.size);
}
// -------------------------------------------------------------------------------

void CBankEx::DGGetPoint(BANKEX_DG_GET_POINT * aRecv)
{
	// ----
	LPOBJ lpUser = &gObj[aRecv->UserIndex];
	// ----
	if( aRecv->Bless < 0 )
	{
		aRecv->Bless = 0;
	}
	if( aRecv->Soul < 0 )
	{
		aRecv->Soul = 0;
	}
	if (aRecv->Chaos < 0)
	{
		aRecv->Chaos = 0;
	}
	if (aRecv->Creation < 0)
	{
		aRecv->Creation = 0;
	}
	if( aRecv->Life < 0 )
	{
		aRecv->Life = 0;
	}
	if( aRecv->Harmony < 0 )
	{
		aRecv->Harmony = 0;
	}
	// ----
	lpUser->BankEx.JBless		= aRecv->Bless;
	lpUser->BankEx.JSoul		= aRecv->Soul;
	lpUser->BankEx.JChaos		= aRecv->Chaos;
	lpUser->BankEx.JCreation	= aRecv->Creation;
	lpUser->BankEx.JLife		= aRecv->Life;
	lpUser->BankEx.JHarmony		= aRecv->Harmony;
	gBankEx.GCUpdateBankEx(lpUser->Index);
}
// -------------------------------------------------------------------------------

void CBankEx::GCUpdateBankEx(int aIndex)
{
	//Send to Client
	if (!gObjIsConnectedGP(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	PMSG_BANKEX_UPDATE_SEND pMsg;
	pMsg.header.set(0xFB, 0x21, sizeof(pMsg));
	// ----
	pMsg.Bless = lpObj->BankEx.JBless;
	pMsg.Soul = lpObj->BankEx.JSoul;
	pMsg.Chaos = lpObj->BankEx.JChaos;
	pMsg.Creation = lpObj->BankEx.JCreation;
	pMsg.Life = lpObj->BankEx.JLife;
	pMsg.Harmony = lpObj->BankEx.JHarmony;
	// ----
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

void CBankEx::JewelSend(PMSG_JEWELSBANK_RECV * lpMsg,LPOBJ lpObj)
{
	if(lpMsg->Type == 0) //Bless
	{
		int BlessCount = gItemManager.GetInventoryItemCount(lpObj, GET_ITEM(14, 13), 0);
		if ( lpMsg->Count > BlessCount )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have %d Jewels Bless in Inventory.",BlessCount);
			return;
		}
		gItemManager.DeleteInventoryItemCount(lpObj, GET_ITEM(14, 13), 0, lpMsg->Count);
		lpObj->BankEx.JBless += lpMsg->Count;
		this->GDSavePoint(lpObj->Index);
		this->GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Deposit %d Bless",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 1) // Soul
	{
		int SoulCount = gItemManager.GetInventoryItemCount(lpObj, GET_ITEM(14, 14), 0);
		if ( lpMsg->Count > SoulCount )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have %d Jewels Soul in Inventory.",SoulCount);
			return;
		}
		gItemManager.DeleteInventoryItemCount(lpObj, GET_ITEM(14, 14), 0, lpMsg->Count);
		lpObj->BankEx.JSoul += lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Deposit %d Soul",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 2) //Chaos
	{
		int ChaosCount = gItemManager.GetInventoryItemCount(lpObj, GET_ITEM(12, 15), 0);
		if ( lpMsg->Count > ChaosCount )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have insufficient quantity.");
			return;
		}
		gItemManager.DeleteInventoryItemCount(lpObj, GET_ITEM(12, 15), 0, lpMsg->Count);
		lpObj->BankEx.JChaos += lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Deposit %d Chaos",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 3) // Life
	{
		int LifeCount = gItemManager.GetInventoryItemCount(lpObj, GET_ITEM(14, 16), 0);
		if ( lpMsg->Count > LifeCount )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have insufficient quantity.");
			return;
		}
		gItemManager.DeleteInventoryItemCount(lpObj, GET_ITEM(14, 16), 0, lpMsg->Count);
		lpObj->BankEx.JLife += lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Deposit %d Life",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 4) //Creation
	{
		int CreCount = gItemManager.GetInventoryItemCount(lpObj, GET_ITEM(14, 22), 0);
		if ( lpMsg->Count > CreCount )
		{
			//gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "You have insufficient quantity.");
			return;
		}
		gItemManager.DeleteInventoryItemCount(lpObj, GET_ITEM(14, 22), 0, lpMsg->Count);
		lpObj->BankEx.JCreation += lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Deposit %d Creation",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 5) //Harmony
	{
		int HarmonyCount = gItemManager.GetInventoryItemCount(lpObj, GET_ITEM(14, 42), 0);
		if ( lpMsg->Count > HarmonyCount )
		{
			//gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "You have insufficient quantity.");
			return;
		}
		gItemManager.DeleteInventoryItemCount(lpObj, GET_ITEM(14, 42), 0, lpMsg->Count);
		lpObj->BankEx.JHarmony += lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Deposit %d Harmony",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
}

void CBankEx::JewelRecv(PMSG_JEWELSBANK_RECV * lpMsg,LPOBJ lpObj)
{
	if(lpMsg->Type == 0) //Bless
	{
		if ( lpMsg->Count > lpObj->BankEx.JBless )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have insufficient funds.");
			return;
		}
		int EmptySlot = gItemManager.GetInventoryEmptySlotCount(lpObj);
		if ( EmptySlot < lpMsg->Count )
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(540));
			return;
		}
		for(int n=0;n < lpMsg->Count;n++)
		{
			GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(14, 13),0,0,0,0,0,-1,0,0,0,0,0,0xFF,0);
		}
		lpObj->BankEx.JBless -= lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Widthdraw %d Bless",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 1) //Soul
	{
		if ( lpMsg->Count > lpObj->BankEx.JSoul )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have insufficient funds.");
			return;
		}
		int EmptySlot = gItemManager.GetInventoryEmptySlotCount(lpObj);
		if ( EmptySlot < lpMsg->Count )
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(540));
			return;
		}
		for(int n=0;n < lpMsg->Count;n++)
		{
			GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(14, 14),0,0,0,0,0,-1,0,0,0,0,0,0xFF,0);
		}
		lpObj->BankEx.JSoul -= lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Widthdraw %d Soul",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 2) //Chaos
	{
		if ( lpMsg->Count > lpObj->BankEx.JChaos )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have insufficient funds.");
			return;
		}
		int EmptySlot = gItemManager.GetInventoryEmptySlotCount(lpObj);
		if ( EmptySlot < lpMsg->Count )
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(540));
			return;
		}
		for(int n=0;n < lpMsg->Count;n++)
		{
			GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(12, 15),0,0,0,0,0,-1,0,0,0,0,0,0xFF,0);
		}
		lpObj->BankEx.JChaos -= lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Widthdraw %d Chaos",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 3) //Life
	{
		if ( lpMsg->Count > lpObj->BankEx.JLife )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have insufficient funds.");
			return;
		}
		int EmptySlot = gItemManager.GetInventoryEmptySlotCount(lpObj);
		if ( EmptySlot < lpMsg->Count )
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(540));
			return;
		}
		for(int n=0;n < lpMsg->Count;n++)
		{
			GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, GET_ITEM(14, 16), 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0xFF, 0);
		}
		lpObj->BankEx.JLife -= lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Widthdraw %d Life",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 4) //Creation
	{
		if ( lpMsg->Count > lpObj->BankEx.JCreation )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have insufficient funds.");
			return;
		}
		int EmptySlot = gItemManager.GetInventoryEmptySlotCount(lpObj);
		if ( EmptySlot < lpMsg->Count )
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(540));
			return;
		}
		for(int n=0;n < lpMsg->Count;n++)
		{
			GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, GET_ITEM(14, 22), 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0xFF, 0);
		}
		lpObj->BankEx.JCreation -= lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Widthdraw %d Creation",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
	else if(lpMsg->Type == 5) //Harmony
	{
		if ( lpMsg->Count > lpObj->BankEx.JHarmony )
		{
			//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have insufficient funds.");
			return;
		}
		int EmptySlot = gItemManager.GetInventoryEmptySlotCount(lpObj);
		if ( EmptySlot < lpMsg->Count )
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(540));
			return;
		}
		for(int n=0;n < lpMsg->Count;n++)
		{
			GDCreateItemSend(lpObj->Index, 0xEB, 0, 0, GET_ITEM(14, 42), 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0xFF, 0);
		}
		lpObj->BankEx.JHarmony -= lpMsg->Count;
		gBankEx.GDSavePoint(lpObj->Index);
		gBankEx.GCUpdateBankEx(lpObj->Index);
		LogAdd(LOG_BLACK,"[JewelsBank]ID %s Player %s Widthdraw %d Harmony",lpObj->Account,lpObj->Name,lpMsg->Count);
	}
}