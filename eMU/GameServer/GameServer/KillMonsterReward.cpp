#include "StdAfx.h"
#include "KillMonsterReward.h"
#include "user.h"
#include "GameMain.h"
#include "MemScript.h"
#include "CashShop.h"
#include "DSProtocol.h"
#include "Notice.h"
#include "Message.h"
ShopPointEx g_ShopPointEx;

ShopPointEx::ShopPointEx()
{
	this->Init();
}

ShopPointEx::~ShopPointEx()
{
}

void ShopPointEx::Init()
{
	this->m_IsLoaded			= false;
	this->m_MonsterLoaded		= 0;

	for( int i = 0; i < MAX_SHOPPOINTEX_MONSTER; i++ )
	{
		this->m_MonsterBonus[i].MonsterID	= -1;
		this->m_MonsterBonus[i].MapNumber	= -1;
		this->m_MonsterBonus[i].AddCoinC	= 0;
		this->m_MonsterBonus[i].AddCoinP	= 0;
		this->m_MonsterBonus[i].AddCoinG	= 0;
		//this->m_MonsterBonus[i].AddUpPoint	= 0;
	}
}

void ShopPointEx::Load()
{
	this->Init();
	this->ReadData("..\\Data\\Custom\\KillMonsterReward.txt");
}

void ShopPointEx::ReadData(char * lpszFileName)
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
				if( Category == 0 )	//-> Monster Bonus
				{
					if(strcmp("end",lpScript->GetAsString()) == 0)
					{
						break;
					}

					int Slot = this->m_MonsterLoaded;

					this->m_MonsterBonus[Slot].MonsterID = lpScript->GetNumber();
					this->m_MonsterBonus[Slot].MapNumber = lpScript->GetAsNumber();
					this->m_MonsterBonus[Slot].AddCoinC = lpScript->GetAsNumber();
					this->m_MonsterBonus[Slot].AddCoinP = lpScript->GetAsNumber();
					this->m_MonsterBonus[Slot].AddCoinG = lpScript->GetAsNumber();
					//this->m_MonsterBonus[Slot].AddUpPoint = lpScript->GetAsNumber();
					this->m_MonsterLoaded++;
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

	//LogAddTD("[GameShop] %s is loaded (Monsters: %d)", lpszFileName, this->m_MonsterLoaded);
	delete lpScript;
}

int ShopPointEx::GetMonsterSlot(int Class, int Map)
{
	for( int i = 0; i < this->m_MonsterLoaded; i++ )
	{
		if( this->m_MonsterBonus[i].MonsterID != Class )
		{
			continue;
		}

		if( this->m_MonsterBonus[i].MapNumber != Map && this->m_MonsterBonus[i].MapNumber != -1 )
		{
			continue;
		}

		return i;
	}

	return -1;
}

void ShopPointEx::AddMonsterBonus(int UserIndex, int MonsterIndex)
{
	if( !this->m_IsLoaded )
	{
		return;
	}

	int MonsterSlot = this->GetMonsterSlot(gObj[MonsterIndex].Class, gObj[MonsterIndex].Map);

	if( MonsterSlot == -1 )
	{
		return;
	}
	//gObj[UserIndex].LevelUpPoint += this->m_MonsterBonus[MonsterSlot].AddUpPoint;
	gCashShop.GDCashShopAddPointSaveSend(gObj[UserIndex].Index,0,this->m_MonsterBonus[MonsterSlot].AddCoinC,this->m_MonsterBonus[MonsterSlot].AddCoinP,this->m_MonsterBonus[MonsterSlot].AddCoinG);
	gNotice.GCNoticeSend(gObj[UserIndex].Index,1,0,0,0,0,0,gMessage.GetMessage(583),this->m_MonsterBonus[MonsterSlot].AddCoinC,this->m_MonsterBonus[MonsterSlot].AddCoinP,this->m_MonsterBonus[MonsterSlot].AddCoinG);
}

void ShopPointEx::SendRcvNotify(int UserIndex, int CoinC, int CoinP, int CoinG)
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
}

