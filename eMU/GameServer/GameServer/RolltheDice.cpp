#include "stdafx.h"
#include "Util.h"
#include "user.h"
#include "Log.h"
#include "RolltheDice.h"
#include "CashShop.h"
#include "Notice.h"
#include "Protocol.h"
#include "Message.h"
cRolltheDice gRolltheDice;

cRolltheDice::cRolltheDice() // OK
{
}

cRolltheDice::~cRolltheDice() // OK
{

}
void cRolltheDice::StartRoll(LPOBJ lpUser, ROLL_DICE_REQ *aRecv)
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
	srand(time(0));
	Dice1=rand()%6 + 1;
	Dice2=rand()%6 + 1;
	TotalPoint=Dice1+Dice2;
	int kq2 = (float)(aRecv->Money * 1.01);
	int kq3	= (float)(aRecv->Money * 1.07);
	int kq4	= (float)(aRecv->Money * 1.18);
	int kq5	= (float)(aRecv->Money * 1.36);
	int kq6	= (float)(aRecv->Money * 1.68);
	int kq7	= (float)(aRecv->Money * 2.35);
	int kq8	= (float)(aRecv->Money * 3.53);
	int kq9	= (float)(aRecv->Money * 5.88);
	int kq10	= (float)(aRecv->Money * 11.76);
	int kq11	= (float)(aRecv->Money * 35.28);
	gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,tiencuoc,0,0);
	if(aRecv->Type	== 1) // Over
	{
		if (TotalPoint > aRecv->Number)
		{
			switch (aRecv->Number)
			{
			case 2:
				this->LastProfit = kq2;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq2,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.01x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq2);
				break;
			case 3:
				this->LastProfit = kq3;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq3,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.07x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq3);
				break;
			case 4:
				this->LastProfit = kq4;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq4,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.18x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq4);
				break;
			case 5:
				this->LastProfit = kq5;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq5,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.36x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq5);
				break;
			case 6:
				this->LastProfit = kq6;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq6,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.68x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq6);
				break;
			case 7:
				this->LastProfit = kq7;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq7,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 2.35x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq7);
				break;
			case 8:
				this->LastProfit = kq8;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq8,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 3.53x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq8);
				break;
			case 9:
				this->LastProfit = kq9;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq9,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 5.88x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq9);
				break;
			case 10:
				this->LastProfit = kq10;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq10,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 11.76x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq10);
				//gNotice.GCNoticeSendToAll(0,0,0,0,0,0,"[ROLL THE DICE]Player: %s WINNER %d wCoinC",lpUser->Name,kq10);
				break;
			case 11:
				this->LastProfit = kq11;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq11,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 35.28x GAME: > %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq11);
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,this->msg[2],lpUser->Name,kq11);
				break;
			}
			this->Winner = 1;
		}
		else
		{
			this->Winner = 2;
			gLog.Output(LOG_MINIGAME,"[ROLL THE DICE LOSER] PLAYER: %s BET: %d GAME: > %d ROLL: %d PROFIT: -%d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,tiencuoc);
		}
		RolltheDiceData(lpUser->Index);
	}
	else if(aRecv->Type	== 2) // Under
	{
		if (TotalPoint < aRecv->Number)
		{
			switch (aRecv->Number)
			{
			case 12:
				this->LastProfit = kq2;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq2,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.01x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq2);
				break;
			case 11:
				this->LastProfit = kq3;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq3,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.07x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq3);
				break;
			case 10:
				this->LastProfit = kq4;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq4,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.18x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq4);
				break;
			case 9:
				this->LastProfit = kq5;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq5,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.36x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq5);
				break;
			case 8:
				this->LastProfit = kq6;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq6,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 1.68x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq6);
				break;
			case 7:
				this->LastProfit = kq7;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq7,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 2.35x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq7);
				break;
			case 6:
				this->LastProfit = kq8;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq8,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 3.53x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq8);
				break;
			case 5:
				this->LastProfit = kq9;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq9,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 5.88x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq9);
				break;
			case 4:
				this->LastProfit = kq10;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq10,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 11.76x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq10);
				//gNotice.GCNoticeSendToAll(0,0,0,0,0,0,"[ROLL THE DICE]Player: %s WINNER %d wCoinC",lpUser->Name,kq10);
				break;
			case 3:
				this->LastProfit = kq11;
				gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,kq11,0,0);
				gLog.Output(LOG_MINIGAME,"[ROLL THE DICE] PLAYER: %s BET: %d PAYOUT: 35.28x GAME: < %d ROLL: %d PROFIT: %d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,kq11);
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,this->msg[2],lpUser->Name,kq11);
				break;
			}
			this->Winner = 1;
		}
		else
		{
			this->Winner = 2;
			gLog.Output(LOG_MINIGAME,"[ROLL THE DICE LOSER] PLAYER: %s BET: %d GAME: < %d ROLL: %d PROFIT: -%d",lpUser->Name,tiencuoc,aRecv->Number,TotalPoint,tiencuoc);
		}
			RolltheDiceData(lpUser->Index);
	}
}