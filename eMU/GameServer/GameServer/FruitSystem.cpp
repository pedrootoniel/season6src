#include "stdafx.h"
#include "FruitSystem.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "ItemManager.h"
#include "ServerInfo.h"
#include "Notice.h"
#include "Util.h"
#include "MemScript.h"
#include "ObjectManager.h"

CFruitSystem gFruitSystem;

CFruitSystem::CFruitSystem()
{
	
}

CFruitSystem::~CFruitSystem()
{
	
}

void CFruitSystem::InitUser(LPOBJ lpObj)
{
	lpObj->FruitData.Strength	= 0;
	lpObj->FruitData.Dexterity	= 0;
	lpObj->FruitData.Vitality	= 0;
	lpObj->FruitData.Energy		= 0;
	lpObj->FruitData.Leadership	= 0;
}

void CFruitSystem::GDSavePoint(int aIndex)
{
	if( !gObjIsConnected(aIndex) )
	{
		return;
	}
	// ----
	LPOBJ lpUser = &gObj[aIndex];
	// ----
	FRUIT_SAVE_POINT pRequest;
	pRequest.h.set(0xD9, 0x19, sizeof(pRequest));
	memcpy(pRequest.Name, lpUser->Name, sizeof(lpUser->Name));
	pRequest.Index	= aIndex;
	pRequest.Strength		= lpUser->FruitData.Strength;
	pRequest.Dexterity		= lpUser->FruitData.Dexterity;
	pRequest.Vitality		= lpUser->FruitData.Vitality;
	pRequest.Energy	= lpUser->FruitData.Energy;
	pRequest.Leadership		= lpUser->FruitData.Leadership;
	gDataServerConnection.DataSend((BYTE*)&pRequest,pRequest.h.size);
}
// -------------------------------------------------------------------------------

void CFruitSystem::GDReqPoint(int aIndex)
{
	// ----
	LPOBJ lpUser = &gObj[aIndex];
	// ----
	FRUIT_REQ_POINT pRequest;
	pRequest.h.set(0xD9, 0x18, sizeof(pRequest));
	memcpy(pRequest.Name, lpUser->Name, sizeof(lpUser->Name));
	pRequest.Index = aIndex;
	gDataServerConnection.DataSend((BYTE*)&pRequest,pRequest.h.size);
}
// -------------------------------------------------------------------------------

void CFruitSystem::DGGetPoint(FRUIT_GET_POINT * aRecv)
{
	// ----
	LPOBJ lpUser = &gObj[aRecv->Index];
	// ----
	if( aRecv->Strength < 0 )
	{
		aRecv->Strength = 0;
	}
	if( aRecv->Dexterity < 0 )
	{
		aRecv->Dexterity = 0;
	}
	if (aRecv->Vitality < 0)
	{
		aRecv->Vitality = 0;
	}
	if (aRecv->Energy < 0)
	{
		aRecv->Energy= 0;
	}
	if( aRecv->Leadership < 0 )
	{
		aRecv->Leadership = 0;
	}
	// ----
	lpUser->FruitData.Strength		= aRecv->Strength;
	lpUser->FruitData.Dexterity		= aRecv->Dexterity;
	lpUser->FruitData.Vitality		= aRecv->Vitality;
	lpUser->FruitData.Energy	= aRecv->Energy;
	lpUser->FruitData.Leadership	= aRecv->Leadership;
	this->GCFruitClientSend(lpUser->Index);
}
// -------------------------------------------------------------------------------

void CFruitSystem::GCFruitClientSend(int aIndex)
{
	//Send to Client
	if (!gObjIsConnectedGP(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	FRUIT_CLIENT_SEND pMsg;
	pMsg.header.set(0xFB, 0x23, sizeof(pMsg));
	// ----
	pMsg.Strength = lpObj->FruitData.Strength;
	pMsg.Dexterity = lpObj->FruitData.Dexterity;
	pMsg.Vitality = lpObj->FruitData.Vitality;
	pMsg.Energy = lpObj->FruitData.Energy;
	pMsg.Leadership = lpObj->FruitData.Leadership;
	pMsg.MaxPoint = gServerInfo.m_FruitMaxPointValue;
	// ----
	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}

bool CFruitSystem::UseFruitAddPoint(LPOBJ lpObj,int type) // OK
{
	FRUIT_RESULT_SEND pMsg;

	pMsg.header.set(0x2C,sizeof(pMsg));

	if(lpObj->Level < 10)
	{
		pMsg.result = 2;
		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
		return 0;
	}

	if(type == 4 && lpObj->Class != CLASS_DL)
	{
		pMsg.result = 2;
		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
		return 0;
	}

	for(int n=0;n < INVENTORY_WEAR_SIZE;n++)
	{
		if(lpObj->Inventory[n].IsItem() != 0)
		{
			pMsg.result = 16;
			DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
			return 0;
		}
	}
	int TotalPoint = lpObj->FruitData.Strength + lpObj->FruitData.Dexterity + lpObj->FruitData.Vitality + lpObj->FruitData.Energy + lpObj->FruitData.Leadership;

	if(TotalPoint >= gServerInfo.m_FruitMaxPointValue)
	{
		pMsg.result = 37;
		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
		return 0;
	}

	int* stat;

	switch(type)
	{
		case 0:
			stat = &lpObj->FruitData.Strength;
			break;
		case 1:
			stat = &lpObj->FruitData.Dexterity;
			break;
		case 2:
			stat = &lpObj->FruitData.Vitality;
			break;
		case 3:
			stat = &lpObj->FruitData.Energy;
			break;
		case 4:
			stat = &lpObj->FruitData.Leadership;
			break;
		default:
			pMsg.result = 33;
			DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
			return 0;
	}

	if((*stat) >= gServerInfo.m_MaxStatPoint[lpObj->AccountLevel])
	{
		pMsg.result = 33;
		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
		return 0;
	}

	if((GetLargeRand()%100) < gServerInfo.m_FruitAddPointSuccessRate[lpObj->AccountLevel])
	{
		//int amount = gServerInfo.m_FruitAddPointMin+(GetLargeRand()%((gServerInfo.m_FruitAddPointMax-gServerInfo.m_FruitAddPointMin)+1));

		//amount = (((lpObj->FruitAddPoint+amount)>this->GetMaxFruitPoint(lpObj))?(this->GetMaxFruitPoint(lpObj)-lpObj->FruitAddPoint):amount);

		//amount = ((((*stat)+amount)>gServerInfo.m_MaxStatPoint[lpObj->AccountLevel])?(gServerInfo.m_MaxStatPoint[lpObj->AccountLevel]-(*stat)):amount);

		int amount = rand() % gServerInfo.m_FruitAddPointMax + gServerInfo.m_FruitAddPointMin; 

		(*stat) += amount;

		//lpObj->FruitAddPoint += amount;

		pMsg.result = 0;

		pMsg.value = amount;

		pMsg.type = ((type<4)?(3-type):type);

		#if(GAMESERVER_EXTRA==1)
		pMsg.ViewValue = amount;
		pMsg.ViewPoint = lpObj->LevelUpPoint;
		pMsg.ViewStrength = lpObj->Strength;
		pMsg.ViewDexterity = lpObj->Dexterity;
		pMsg.ViewVitality = lpObj->Vitality;
		pMsg.ViewEnergy = lpObj->Energy;
		pMsg.ViewLeadership = lpObj->Leadership;
		#endif

		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);

		gObjectManager.CharacterCalcAttribute(lpObj->Index);

		this->GCFruitClientSend(lpObj->Index);

	}
	else
	{
		pMsg.result = 1;

		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
	}

	return 1;
}

bool CFruitSystem::UseFruitSubPoint(LPOBJ lpObj,int type) // OK
{
	FRUIT_RESULT_SEND pMsg;

	pMsg.header.set(0x2C,sizeof(pMsg));

	if(lpObj->Level < 10)
	{
		pMsg.result = 5;
		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
		return 0;
	}

	if(type == 4 && lpObj->Class != CLASS_DL)
	{
		pMsg.result = 5;
		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
		return 0;
	}

	for(int n=0;n < INVENTORY_WEAR_SIZE;n++)
	{
		if(lpObj->Inventory[n].IsItem() != 0)
		{
			pMsg.result = 16;
			DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
			return 0;
		}
	}
	/*
	if(lpObj->FruitSubPoint >= this->GetMaxFruitPoint(lpObj))
	{
		pMsg.result = 37;
		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
		return 0;
	}
	*/
	int* stat;

	switch(type)
	{
		case 0:
			stat = &lpObj->FruitData.Strength;
			break;
		case 1:
			stat = &lpObj->FruitData.Dexterity;
			break;
		case 2:
			stat = &lpObj->FruitData.Vitality;
			break;
		case 3:
			stat = &lpObj->FruitData.Energy;
			break;
		case 4:
			stat = &lpObj->FruitData.Leadership;
			break;
		default:
			pMsg.result = 38;
			DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
			return 0;
	}

	if((*stat) <= gDefaultClassInfo.GetCharacterDefaultStat(lpObj->Class,type))
	{
		pMsg.result = 38;
		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
		return 0;
	}

	if((GetLargeRand()%100) < gServerInfo.m_FruitSubPointSuccessRate[lpObj->AccountLevel])
	{
		//int amount = gServerInfo.m_FruitSubPointMin+(GetLargeRand()%((gServerInfo.m_FruitSubPointMax-gServerInfo.m_FruitSubPointMin)+1));

		//amount = (((lpObj->FruitSubPoint+amount)>this->GetMaxFruitPoint(lpObj))?(this->GetMaxFruitPoint(lpObj)-lpObj->FruitSubPoint):amount);

		//amount = ((((*stat)-amount)<gDefaultClassInfo.GetCharacterDefaultStat(lpObj->Class,type))?((*stat)-gDefaultClassInfo.GetCharacterDefaultStat(lpObj->Class,type)):amount);

		int amount = rand() % gServerInfo.m_FruitSubPointMax + gServerInfo.m_FruitSubPointMin; 

		(*stat) -= amount;

		//lpObj->LevelUpPoint += amount;

		//lpObj->FruitSubPoint += amount;

		pMsg.result = 3;

		pMsg.value = amount;

		pMsg.type = ((type<4)?(3-type):type);

		#if(GAMESERVER_EXTRA==1)
		pMsg.ViewValue = amount;
		pMsg.ViewPoint = lpObj->LevelUpPoint;
		pMsg.ViewStrength = lpObj->Strength;
		pMsg.ViewDexterity = lpObj->Dexterity;
		pMsg.ViewVitality = lpObj->Vitality;
		pMsg.ViewEnergy = lpObj->Energy;
		pMsg.ViewLeadership = lpObj->Leadership;
		#endif

		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);

		gObjectManager.CharacterCalcAttribute(lpObj->Index);

		this->GCFruitClientSend(lpObj->Index);
	}
	else
	{
		pMsg.result = 4;

		DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);
	}

	return 1;
}
