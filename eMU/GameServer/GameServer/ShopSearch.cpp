#include "StdAfx.h"
#include "ShopSearch.h"
#include "user.h"
#include "GameMain.h"
#include "Path.h"
#include "Util.h"
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_PERSONAL_SHOP==TRUE)

PersonalShopEx g_PersonalShopEx;
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Init()
{

}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Load()
{
	this->Read(gPath.GetFullPath("Custom\\PShopSearch.txt"));
}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Read(char* File)
{
	this->NPC_CLASS = GetPrivateProfileInt("Common", "NPC_CLASS", 0, File);
	this->NPC_MAP = GetPrivateProfileInt("Common", "NPC_MAP", 0, File);
	this->NPC_X = GetPrivateProfileInt("Common", "NPC_X", 0, File);
	this->NPC_Y = GetPrivateProfileInt("Common", "NPC_Y", 0, File);
}
// ----------------------------------------------------------------------------------------------

bool PersonalShopEx::NPC_Dialog(LPOBJ lpObj, LPOBJ lpNpc)
{
	if(lpNpc->Class	== this->NPC_CLASS && lpNpc->Map == this->NPC_MAP && lpNpc->X == this->NPC_X && lpNpc->Y == this->NPC_Y)
	{
		CG_PersonalPage aCG;
		aCG.Page = 0;
		this->Search(lpObj->Index,&aCG);
		return true;
	}
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Search(int aIndex, CG_PersonalPage* aRecv)
{

	LPOBJ lpUser = &gObj[aIndex];

	int Page = aRecv->Page;

	if(Page < 0 )
	{
		Page = 0;
	}

	if(lpUser->AttackCustomOffline != 0 || lpUser->PShopCustomOffline !=0)
	{
		return;
	}

	BYTE SendBuff[5000];
	int datasize = 8;
	short icount = 0;
	BYTE SendCount = 0;

	int StartCount = Page * 10;
	int EndCount =  StartCount + 10;

	for(int n=OBJECT_START_USER;n<MAX_OBJECT;n++)
	{
		LPOBJ lpSearch = &gObj[n];
		if(lpSearch->Connected < OBJECT_PLAYING || !lpSearch->PShopOpen || n == aIndex) 
		{
			continue;
		}

		if( StartCount <= icount && EndCount > icount)
		{
			if(SendCount < 10)
			{
				GC_PersonalShopInfo psi;
				psi.aIndex = n;
				strncpy(psi.Name, lpSearch->Name, 10);
				strncpy(psi.PersonalText, lpSearch->PShopText, 36);
				psi.Value = 0;

				memcpy(&SendBuff[datasize],&psi,sizeof(psi));
				datasize += sizeof(psi);

				SendCount++;
			}
		}

		icount++;
	}

	SendBuff[0]=0xC2;	// packet header
	SendBuff[1]=SET_NUMBERHB(datasize);
	SendBuff[2]=SET_NUMBERLB(datasize);
	SendBuff[3]=0xFA;
	SendBuff[4]=0x09;
	SendBuff[5]=SET_NUMBERHB(icount);
	SendBuff[6]=SET_NUMBERLB(icount);
	SendBuff[7]=SendCount;
	DataSend(aIndex,SendBuff,datasize);
}
#endif