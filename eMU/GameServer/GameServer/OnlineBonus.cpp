#include "StdAfx.h"
#include "OnlineBonus.h"
#include "user.h"
#include "GameMain.h"
#include "MemScript.h"
#include "CashShop.h"
#include "DSProtocol.h"
#include "Notice.h"
#include "Message.h"

cOnlineBonus gOnlineBonus;

cOnlineBonus::cOnlineBonus()
{
	this->Init();
}

cOnlineBonus::~cOnlineBonus()
{
}

void cOnlineBonus::Init()
{
	this->m_IsLoaded			= false;

	for (int i = 0; i < 4; i++)
	{
		this->m_TimeBonusOn[i]			= false;
		this->m_TimeBonusAdd[i]			= 0;
		this->m_TimeBonusInterval[i]	= 0;
	}
}

void cOnlineBonus::Load()
{
	this->Init();
	this->ReadData("..\\Data\\Custom\\OnlineBonus.txt");
}

void cOnlineBonus::ReadData(char * lpszFileName)
{
	this->m_IsLoaded = false;
	int Category;
	int TimeBonusCount = 0;

	CMemScript* lpScript = new(std::nothrow) CMemScript;

	if(lpScript == NULL)
	{
		return;
	}

	if(lpScript->SetBuffer(lpszFileName) == 0)
	{
		delete lpScript;
		return;
	}

	try
	{
		while(true)
		{
			if( lpScript->GetToken() == 2 )
			{
				break;
			}

			Category = lpScript->GetNumber();

			while(true)
			{
				if( Category == 0 )			//-> Time Bonus
				{
					if(strcmp("end",lpScript->GetAsString()) == 0)
					{
						break;
					}
					this->m_TimeBonusOn[TimeBonusCount] = lpScript->GetNumber();
					this->m_TimeBonusAdd[TimeBonusCount] = lpScript->GetAsNumber();
					this->m_TimeBonusInterval[TimeBonusCount] = lpScript->GetAsNumber();
					TimeBonusCount++;
				}
			}
		}
	}
	catch(...)
	{
		delete lpScript;
		MessageBox(0,lpszFileName,"Error!",0);
		return;
	}

	this->m_IsLoaded = true;

	delete lpScript;
}

void cOnlineBonus::AddTimeBonus(int UserIndex)
{
	if( !this->m_IsLoaded )
	{
		return;
	}

	int BonusGained[] = { 0, 0, 0, 0 };

	for (int i = 0; i < 4; i++)
	{
		if (this->m_TimeBonusOn[i] != 1)
			continue;

		if (this->m_TimeBonusInterval[i] > 0 && gObj[UserIndex].m_OnlineBonusTime[i] % this->m_TimeBonusInterval[i] != 0)
			continue;

		gObj[UserIndex].m_OnlineBonusTime[i] = 0;
		BonusGained[i] = this->m_TimeBonusAdd[i];

		if (i == 0 && this->m_TimeBonusAdd[i] > 0)
			gCashShop.GDCashShopAddPointSaveSend(gObj[UserIndex].Index,0,this->m_TimeBonusAdd[i],0,0);
		else if (i == 1 && this->m_TimeBonusAdd[i] > 0)
			gCashShop.GDCashShopAddPointSaveSend(gObj[UserIndex].Index,0,0,this->m_TimeBonusAdd[i],0);
		else if (i == 2 && this->m_TimeBonusAdd[i] > 0)
			gCashShop.GDCashShopAddPointSaveSend(gObj[UserIndex].Index,0,0,0,this->m_TimeBonusAdd[i]);
		else if (i == 3 && this->m_TimeBonusAdd[i] > 0)
			gObj[UserIndex].Money += this->m_TimeBonusAdd[i];
			GCMoneySend(UserIndex,gObj[UserIndex].Money);

	}
	this->SendRcvNotify(UserIndex, BonusGained[0], BonusGained[1], BonusGained[2], BonusGained[3]);
}

void cOnlineBonus::SendRcvNotify(int UserIndex, int CoinC, int CoinP, int CoinG, int Zen)
{
	if( CoinC > 0 )
	{
		gNotice.GCNoticeSend(gObj[UserIndex].Index,1,0,0,0,0,0,gMessage.GetMessage(580),CoinC);
	}

	if( CoinP > 0 )
	{
		
		gNotice.GCNoticeSend(gObj[UserIndex].Index,1,0,0,0,0,0,gMessage.GetMessage(581),CoinP);
	}

	if (CoinG > 0)
	{
		gNotice.GCNoticeSend(gObj[UserIndex].Index,1,0,0,0,0,0,gMessage.GetMessage(582),CoinG);
	}

	if (Zen > 0)
	{
		gNotice.GCNoticeSend(gObj[UserIndex].Index,1,0,0,0,0,0,"You received %d Zen!",Zen);
	}
}

