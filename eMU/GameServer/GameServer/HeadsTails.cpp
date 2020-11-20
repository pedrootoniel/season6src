#include "stdafx.h"
#include "Util.h"
#include "user.h"
#include "Log.h"
#include "HeadsTails.h"
#include "CashShop.h"
#include "Notice.h"
#include "Protocol.h"
#include "Message.h"
cHeadsTails gHeadsTails;

cHeadsTails::cHeadsTails() // OK
{
}

cHeadsTails::~cHeadsTails() // OK
{

}
void cHeadsTails::StartFlip(LPOBJ lpUser, HEADS_TAILS_REQ *aRecv)
{
	if(this->enable == 0)
	{
		gNotice.GCNoticeSend(lpUser->Index,1,0,0,0,0,0,this->msg[0]);
		return;
	}
	int tiencuoc = aRecv->Money;
	if(lpUser->WCoinCaRecv < tiencuoc)
	{
		gNotice.GCNoticeSend(lpUser->Index,1,0,0,0,0,0,this->msg[1],tiencuoc);
		return;
	}
	int kq = (float)(aRecv->Money * 1.92);
	gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,tiencuoc,0,0);
	srand(time(0));
	int number = rand() % 100 + 1;  //Generate random number 1 to 100

	if(aRecv->Type = 1) //
	{
        if (number <= this->winrate) // chance win
		{
			this->winer = 1; //This is head
			this->winerprice = kq;
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq,0,0);
			gLog.Output(LOG_MINIGAME,"[Heads-Tails] PLAYER: %s WINNER %d wCoinC",lpUser->Name,kq);
		}
		else{
			this->winer = 2; //This is tail
			this->winerprice = 0;
			gLog.Output(LOG_MINIGAME,"[Heads-Tails] PLAYER: %s LOSER %d wCoinC",lpUser->Name,tiencuoc);
		}
		HeadsTailsData(lpUser->Index);
	}

	else if(aRecv->Type = 2) //
	{
        if (number <= this->winrate) // chance win
		{
			this->winer = 1; //This is tail
			this->winerprice = kq;
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq,0,0);
			gLog.Output(LOG_MINIGAME,"[Heads-Tails] PLAYER: %s WINNER %d wCoinC",lpUser->Name,kq);
		}
		else{
			this->winer = 2; //This is head
			this->winerprice = 0;
			gLog.Output(LOG_MINIGAME,"[Heads-Tails] PLAYER: %s LOSER %d wCoinC",lpUser->Name,tiencuoc);
		}
		HeadsTailsData(lpUser->Index);
	}
}