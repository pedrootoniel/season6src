#include "stdafx.h"
#include "GoldenArcher.h"
#include "GameMain.h"
#include "ItemManager.h"
#include "ServerInfo.h"
#include "Notice.h"
#include "ItemBagManager.h"
#include "Util.h"

CGoldenArcher gGoldenArcher;

CGoldenArcher::CGoldenArcher()
{
	
}

CGoldenArcher::~CGoldenArcher()
{
	
}

void CGoldenArcher::GoldenArcherNPC(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (lpObj->Interface.state > 0)
	{
		return;
	}
	PMSG_REQ_VIEW_EC_MN pMsg;
	// ----
	pMsg.header.set(0x1B,0x00,sizeof(pMsg));
	pMsg.aIndex				= lpObj->Index;
	memcpy(pMsg.AccountID,lpObj->Account,sizeof(pMsg.AccountID));
	// ----
	gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
	// ----
	lpObj->Interface.type	= INTERFACE_GOLDEN_ARCHER;
	lpObj->Interface.state	= 0;
	lpObj->Interface.use	= 1;
}

void CGoldenArcher::RecvGoldenArcher(PMSG_ANS_VIEW_EC_MN* aRecv)
{
	LPOBJ lpObj = &gObj[aRecv->iINDEX];

	PMSG_EVENTCHIPINFO pMsg;

	pMsg.h.set(0x94, sizeof(pMsg));
	pMsg.Type = 0;
	pMsg.ChipCount = aRecv->nEVENT_CHIPS;
	lpObj->EventChipCount = aRecv->nEVENT_CHIPS;

	DataSend(lpObj->Index, (LPBYTE)&pMsg, pMsg.h.size);

	lpObj->UseEventServer = FALSE;
}

void CGoldenArcher::CGRegEventChipRecv(PMSG_REGEVENTCHIP* lpMsg, int aIndex) 
{
	if ( !EVENCHIP_TYPE_RANGE(lpMsg->Type) )
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if ( lpObj->Interface.type == INTERFACE_TRADE )
	{
		//LogAdd(LOG_RED, "[EventChip] [%s][%s] Attempted ItemCopy using Trade Window", lpObj->Account, lpObj->Name);
		return;
	}

	if ( lpObj->Interface.type == INTERFACE_CHAOS_BOX )
	{
		//LogAdd(LOG_RED, "[EventChip] [%s][%s] Attempted ItemCopy using ChaosBox Window", lpObj->Account, lpObj->Name);
		return;
	}

	if ( lpObj->UseEventServer != FALSE )
	{
		PMSG_REGEVENTCHIP_RESULT Result;

		Result.h.set(0x95, sizeof(Result));
		Result.ChipCount = -1;
		Result.Type = lpMsg->Type;

		//LogAdd(LOG_RED, "[EventChip] [%s][%s] Not Found EventChip (RegEventchip) #1 %d", lpObj->Account, lpObj->Name, lpMsg->ChipPos);
		DataSend(lpObj->Index, (LPBYTE)&Result, Result.h.size);
		return;
	}

	int Pos = lpMsg->ChipPos + INVENTORY_WEAR_SIZE;
	CItem * sitem = &lpObj->Inventory[Pos];

	if ( !sitem->IsItem() )
	{
		PMSG_REGEVENTCHIP_RESULT Result;

		Result.h.set(0x95, sizeof(Result));
		Result.ChipCount = -1;
		Result.Type = lpMsg->Type;

		//LogAddTD("[EventChip] [%s][%s] Not Found EventChip (RegEventchip) #2 %d", lpObj->AccountID, lpObj->Name, lpMsg->ChipPos);
		DataSend(lpObj->Index, (LPBYTE)&Result, Result.h.size);
		return;
	}

	lpObj->UseEventServer = TRUE;

	switch ( lpMsg->Type )
	{
		case 0x00:
			if ( sitem->m_Index == GET_ITEM(14,21) && sitem->m_Level == 0 )
			{
				PMSG_REQ_REGISTER_EVENTCHIP pMsg;

				pMsg.header.set(0x1B,0x01,sizeof(pMsg));
				pMsg.iINDEX = aIndex;
				pMsg.Pos = Pos;
				memcpy(pMsg.szUID,lpObj->Account,sizeof(pMsg.szUID));

				gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
			}
			else
			{
				PMSG_REGEVENTCHIP_RESULT Result;

				Result.h.set(0x95, sizeof(Result));
				Result.ChipCount = -1;
				Result.Type = 0x00;

				//LogAddTD("[EventChip] [%s][%s] Not Found EventChip (RegEventchip) #3 %d", lpObj->AccountID, lpObj->Name, lpMsg->ChipPos);

				DataSend(lpObj->Index, (LPBYTE)&Result, Result.h.size);
				lpObj->UseEventServer = FALSE;
			}
			break;
		case 0x01:
			if ( sitem->m_Index == GET_ITEM(14,21) && sitem->m_Level == 1 )
			{
				/*PMSG_REQ_REGISTER_STONES pMsg;

				pMsg.header.set(0x1B,0x01,sizeof(pMsg));
				pMsg.iINDEX = aIndex;
				pMsg.iPosition = Pos;
				strcpy(pMsg.szUID, lpObj->Account);

				gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);*/
				LogAdd(LOG_RED, "Register Stones, please contact support!");

				//LogAddTD("[Stone] [%s][%s] Register Stone (Stone Pos:%d, Serial:%u)", lpObj->AccountID, lpObj->Name, lpMsg->ChipPos, sitem->m_Number);
			}
			else
			{
				PMSG_REGEVENTCHIP_RESULT Result;

				Result.h.set(0x95, sizeof(Result));
				Result.ChipCount = -1;
				Result.Type = 0x01;

				//LogAddTD("[Stone] [%s][%s] Not Found EventChip (Stone Pos: %d)", lpObj->AccountID, lpObj->Name, lpMsg->ChipPos);

				DataSend(lpObj->Index, (LPBYTE)&Result, Result.h.size);
				lpObj->UseEventServer = FALSE;
			}
			break;
		default:
			lpObj->UseEventServer = FALSE;
			break;
	}
}

void CGoldenArcher::DGResultRegEventChip(PMSG_ANS_REGISTER_EVENTCHIP * aRecv)
{
	PMSG_REGEVENTCHIP_RESULT Result;

	Result.h.set(0x95, sizeof(Result));

	LPOBJ lpObj = &gObj[aRecv->iINDEX];

	if ( aRecv->bSUCCESS == FALSE )
	{
		Result.ChipCount = -1;

	}
	else
	{
		lpObj->EventChipCount = aRecv->nEVENT_CHIPS;
		Result.ChipCount = aRecv->nEVENT_CHIPS;
		gItemManager.InventoryDelItem(lpObj->Index,aRecv->Pos);
		gItemManager.GCItemDeleteSend(lpObj->Index,aRecv->Pos,1);
	}

	Result.Type = 0;

	DataSend(lpObj->Index, (LPBYTE)&Result, Result.h.size);

	lpObj->UseEventServer = FALSE;

	if (aRecv->nEVENT_CHIPS >= gServerInfo.m_GoldenArcherNeedRena)
	{
		//RenaResultWinnerPrize(aIndex);
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "Thanks, get your prize!");
		PMSG_REQ_RESET_EVENTCHIP pMsg;

		pMsg.header.set(0x1B,0x02,sizeof(pMsg));

		pMsg.iINDEX = lpObj->Index;
		memcpy(pMsg.szUID,lpObj->Account,sizeof(pMsg.szUID));
		gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
	}
}

void CGoldenArcher::DGRecvChangeRena( PMSG_ANS_RESET_EVENTCHIP* aRecv)
{
	PMSG_REGEVENTCHIP_RESULT Result;

	Result.h.set(0x95, sizeof(Result));
	LPOBJ lpObj = &gObj[aRecv->iINDEX];

	if ( aRecv->bSUCCESS != FALSE )
	{
		gItemBagManager.DropItemBySpecialValue(ITEM_BAG_GOLDEN_ARCHER,&gObj[lpObj->Index],gObj[lpObj->Index].Map,gObj[lpObj->Index].X,gObj[lpObj->Index].Y);
		lpObj->Money += lpObj->EventChipCount * 3000;
		GCMoneySend(lpObj->Index, lpObj->Money);
	}

	Result.ChipCount = 0;
	lpObj->EventChipCount = 0;

	DataSend(lpObj->Index, (LPBYTE)&Result, Result.h.size);

	lpObj->UseEventServer = FALSE;
}

void CGoldenArcher::GCUseEndEventChipRecv(int aIndex) 
{
	if ( !gObjIsConnectedGP(aIndex))
	{
		return;
	}

	if ( gObj[aIndex].Interface.use && gObj[aIndex].Interface.type == INTERFACE_GOLDEN_ARCHER )
	{
		gObj[aIndex].Interface.state = 0;
		gObj[aIndex].Interface.type = 0;
		gObj[aIndex].Interface.use = 0;
	}
}