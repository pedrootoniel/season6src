#include "StdAfx.h"
#include "user.h"
#include "AccSecurity.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "Path.h"
#include "MemScript.h"
#include "Util.h"
#include "CashShop.h"
#include "Message.h"
#include "Notice.h"
cAccSecurity gAccSecurity;

cAccSecurity::cAccSecurity() // OK
{

}

cAccSecurity::~cAccSecurity() // OK
{

}

void cAccSecurity::GDSaveData(int aIndex)
{
	LPOBJ lpUser = &gObj[aIndex];
	// ----
	ACC_SECURITY_DATA_SAVE pRequest;
	pRequest.header.set(0xD9, 0x13, sizeof(pRequest));
	memcpy(pRequest.account, lpUser->Account, 11);
	pRequest.index	= aIndex;
	pRequest.TradeLock		= lpUser->TradeLock;
	pRequest.InventoryLock	= lpUser->InventoryLock;
	pRequest.WareLock		= lpUser->WareLock;
	pRequest.ShopLock		= lpUser->ShopLock;
	pRequest.PShopLock		= lpUser->PShopLock;
	pRequest.ChaosMixLock	= lpUser->ChaosMixLock;
	pRequest.DelCharLock	= lpUser->DelCharLock;
	gDataServerConnection.DataSend((BYTE*)&pRequest,pRequest.header.size);
}
// -------------------------------------------------------------------------------

void cAccSecurity::GDReqData(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	ACC_SECURITY_REQ pMsg;
	pMsg.header.set(0xD9,0x12,sizeof(pMsg));
	pMsg.index = aIndex;
	memcpy(pMsg.account,lpObj->Account,sizeof(pMsg.account));
	gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

}
// -------------------------------------------------------------------------------
void cAccSecurity::SecurityData(ACC_SECURITY_DATA * aRecv)
{
	// ----
	LPOBJ lpUser = &gObj[aRecv->index];
	// ----
	if( aRecv->SecurityPass < 0 )
	{
		aRecv->SecurityPass = 0;
	}
	if( aRecv->SecurityLock < 0 )
	{
		aRecv->SecurityLock = 0;
	}
	if( aRecv->TradeLock < 0 )
	{
		aRecv->TradeLock = 0;
	}
	if( aRecv->InventoryLock < 0 )
	{
		aRecv->InventoryLock = 0;
	}
	else if( aRecv->WareLock < 0 )
	{
		aRecv->WareLock = 0;
	}
	else if( aRecv->ShopLock < 0 )
	{
		aRecv->ShopLock = 0;
	}
	else if( aRecv->PShopLock < 0 )
	{
		aRecv->PShopLock = 0;
	}
	else if( aRecv->ChaosMixLock < 0 )
	{
		aRecv->ChaosMixLock = 0;
	}
	else if( aRecv->DelCharLock < 0 )
	{
		aRecv->DelCharLock = 0;
	}
	// ----
	lpUser->SecurityPass	= aRecv->SecurityPass;
	lpUser->TradeLock		= aRecv->TradeLock;
	lpUser->InventoryLock	= aRecv->InventoryLock;
	lpUser->WareLock		= aRecv->WareLock;
	lpUser->ShopLock		= aRecv->ShopLock;
	lpUser->PShopLock		= aRecv->PShopLock;
	lpUser->ChaosMixLock	= aRecv->ChaosMixLock;
	lpUser->DelCharLock		= aRecv->DelCharLock;
	GCAccountSecuritySend(lpUser->Index);
}

// -------------------------------------------------------------------------------

void cAccSecurity::gObjAccountSecurityPW(PMSG_SECURITY_PW_RECV* lpMsg, int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->SecurityPass == lpMsg->SecretNumber)
	{
		lpObj->SecurityLock = 0;
		PMSG_ACCSECURITY_OPEN pMsg;
		pMsg.header.set(0xF3, 0xF5, sizeof(pMsg));
		DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
	else
		gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(515));
}

// -------------------------------------------------------------------------------
void cAccSecurity::gObjAccountSecuritySave(PMSG_ACCOUNT_SECURITY_RECV* aRecv,int index)
{
	if(gObjIsConnected(index) == 0)
	{
		return;
	}
	LPOBJ lpUser = &gObj[index];
	
	if(lpUser->SecurityLock == 1)
	{
		gNotice.GCNoticeSend(index,1,0,0,0,0,0,gMessage.GetMessage(515));
		return;
	}
	lpUser->TradeLock = aRecv->TradeLock;
	lpUser->InventoryLock = aRecv->InventoryLock;
	lpUser->WareLock = aRecv->WareLock;
	lpUser->ShopLock = aRecv->ShopLock;
	lpUser->PShopLock = aRecv->PShopLock;
	lpUser->ChaosMixLock = aRecv->ChaosMixLock;
	lpUser->DelCharLock = aRecv->DelCharLock;
	gNotice.GCNoticeSend(index,1,0,0,0,0,0,gMessage.GetMessage(516));
	this->GDSaveData(index);
	GCAccountSecuritySend(index);
}
// -------------------------------------------------------------------------------