#include "stdafx.h"
#include "Util.h"
#include "Log.h"
#include "user.h"
#include "LuckyNumber.h"
#include "CashShop.h"
#include "Notice.h"
#include "Protocol.h"
#include "Message.h"
#include "MemScript.h"
cLuckyNumber gLuckyNumber;

cLuckyNumber::cLuckyNumber() // OK
{

}

cLuckyNumber::~cLuckyNumber() // OK
{

}

void cLuckyNumber::Start(LPOBJ lpUser, LUCKYNUMBER_REQ *aRecv)
{
	if(this->Enable == 0)
	{
		gNotice.GCNoticeSend(lpUser->Index,1,0,0,0,0,0,this->msg[0]);
		return;
	}

	if(lpUser->WCoinCaRecv < this->TicketPrice * aRecv->lines)
	{
		gNotice.GCNoticeSend(lpUser->Index,1,0,0,0,0,0,this->msg[1],this->TicketPrice * aRecv->lines);
		return;
	}
	this->TicketID = rand();
	if (aRecv->lines == 1)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		srand(time(0));
		this->Number[0] = 100 + rand() % 899;
		gLog.Output(LOG_MINIGAME,"[LOTTO] TICKET ID: %d LUCKY NUMBER: %d PLAYER: %s NUMBER: %d",this->TicketID,this->LuckyNumber,lpUser->Name,this->Number[0]);
		if(Number[0] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);
			this->MakeLuckyNumber(lpUser->Index);
			
		}
		LuckyNumberData(lpUser->Index);
	}

	else if (aRecv->lines == 2)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice*2,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		srand(time(0));
		this->Number[0] = 100 + rand() % 899;
		this->Number[1] = 100 + rand() % 899;
		gLog.Output(LOG_MINIGAME,"[LOTTO] TICKET ID: %d LUCKY NUMBER: %d PLAYER: %s NUMBER: %d | %d",this->TicketID,this->LuckyNumber,lpUser->Name,this->Number[0],this->Number[1]);
		if(Number[0] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);				
		}
		if(Number[1] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);	
			this->MakeLuckyNumber(lpUser->Index);
		}
		LuckyNumberData(lpUser->Index);
	}
	else if (aRecv->lines == 3)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice*3,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		srand(time(0));
		this->Number[0] = 100 + rand() % 899;
		this->Number[1] = 100 + rand() % 899;
		this->Number[2] = 100 + rand() % 899;
		gLog.Output(LOG_MINIGAME,"[LOTTO] TICKET ID: %d LUCKY NUMBER: %d PLAYER: %s NUMBER: %d | %d | %d",this->TicketID,this->LuckyNumber,lpUser->Name,this->Number[0],this->Number[1],this->Number[2]);
		if(Number[0] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);			
		}
		if(Number[1] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);			
		}
		if(Number[2] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);
			this->MakeLuckyNumber(lpUser->Index);
		}		
		LuckyNumberData(lpUser->Index);
	}

	else if (aRecv->lines == 4)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice * 4,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		srand(time(0));
		this->Number[0] = 100 + rand() % 899;
		this->Number[1] = 100 + rand() % 899;
		this->Number[2] = 100 + rand() % 899;
		this->Number[3] = 100 + rand() % 899;
		gLog.Output(LOG_MINIGAME,"[LOTTO] TICKET ID: %d LUCKY NUMBER: %d PLAYER: %s NUMBER: %d | %d | %d | %d",this->TicketID,this->LuckyNumber,lpUser->Name,this->Number[0],this->Number[1],this->Number[2],this->Number[3]);

		if(Number[0] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);			
		}
		if(Number[1] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);			
		}
		if(Number[2] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);		
		}
		if(Number[3] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);	
			this->MakeLuckyNumber(lpUser->Index);
		}			
		LuckyNumberData(lpUser->Index);
	}	

	else if (aRecv->lines == 5)
	{
		gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice*5,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		//gCashShop.GDCashShopSubPointSaveSend(lpUser->Index,0,this->TicketPrice,0,0);
		srand(time(0));
		this->Number[0] = 100 + rand() % 899;
		this->Number[1] = 100 + rand() % 899;
		this->Number[2] = 100 + rand() % 899;
		this->Number[3] = 100 + rand() % 899;
		this->Number[4] = 100 + rand() % 899;
		gLog.Output(LOG_MINIGAME,"[LOTTO] TICKET ID: %d LUCKY NUMBER: %d PLAYER: %s NUMBER: %d | %d | %d | %d | %d",this->TicketID,this->LuckyNumber,lpUser->Name,this->Number[0],this->Number[1],this->Number[2],this->Number[3],this->Number[4]);
		if(Number[0] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);				
		}
		if(Number[1] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);			
		}
		if(Number[2] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);				
		}
		if(Number[3] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);					
		}	
		if(Number[4] == this->LuckyNumber)
		{
			gCashShop.GDCashShopAddPointSaveSend(lpUser->Index,0,this->WinPrice,0,0);
			this->MakeLuckyNumber(lpUser->Index);
		}			
		LuckyNumberData(lpUser->Index);
	}		
}
void cLuckyNumber::MakeLuckyNumber(int aIndex)
{
		srand(time(0));
		this->LuckyNumber = 100 +rand() %899;
		LuckyNumberData(aIndex);
}