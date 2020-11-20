#include "stdafx.h"
#include "Survivor.h"
#include "ServerInfo.h"
#include "Notice.h"
#include "Util.h"
#include "GameMain.h"
#include "DSProtocol.h"
#include "MemScript.h"
#include "CashShop.h"
CSurvivor g_Survivor;

CSurvivor::CSurvivor()
{
	this->JoiningTimer	= -2;
	this->ActiveEvent	= -1;
	this->EventType		= -1;
	this->StartedAtTick = -1;
	this->MinutesShowing= 3;
	this->State			= SURVIVOR_STATE_IDLE;
	this->WinnerIndex	= 0;
}

CSurvivor::~CSurvivor()
{
}

void CSurvivor::ClearSchedule()
{
	for(int i=0; i<MAX_SURVIVOR_SCHEDULE; i++)
	{
		SurvivorSchedule[i].DayOfWeek = -1;
		SurvivorSchedule[i].Hour = -1;
		SurvivorSchedule[i].Minute = -1;
		SurvivorSchedule[i].Type = -1;
		SurvivorSchedule[i].Enable = 0;
	}
}

void CSurvivor::LoadSchedule()
{
	this->ClearSchedule();

	CMemScript* lpScript = new(std::nothrow) CMemScript;

	if(lpScript == NULL)
	{
		return;
	}

	if(lpScript->SetBuffer("..\\Data\\Event\\PKEvent.dat") == 0)
	{
		delete lpScript;
		return;
	}

	int counter = 0;

	try
	{
		while ( true )
		{
			if( lpScript->GetToken() == 2 )
			{
				break;
			}

			SurvivorSchedule[counter].Type		= lpScript->GetNumber();
			SurvivorSchedule[counter].DayOfWeek = lpScript->GetAsNumber();
			SurvivorSchedule[counter].Hour		= lpScript->GetAsNumber();
			SurvivorSchedule[counter].Minute	= lpScript->GetAsNumber();
			SurvivorSchedule[counter].Enable	= 1;
			counter++;
		}
	}

	catch(...)
	{
		delete lpScript;
		//MessageBox(0,gServerInfo.SURVIVORSCHEDULE,"Error!",0);
		return;
	}

	//LogAddTD("[Survivor Event] %s loaded with %d scheduled events", gServerInfo.SURVIVORSCHEDULE, counter);

	delete lpScript;
}

void CSurvivor::Run()
{
	if(this->JoiningTimer == -1)
	{

		//Players are signed to Survivor, waiting for the event start count down
		if(this->State == SURVIVOR_STATE_JOIN_TIMER)
		{
			// Check the amount of signed players
			this->PlayerCount = 0;
			for ( int n = OBJECT_START_USER ; n < MAX_OBJECT ; n++)
			{
				if ( gObj[n].Type == OBJECT_USER && gObj[n].SurvivorState == 1)
				{
					this->PlayerCount++;
				}
			}

			if(this->PlayerCount < gServerInfo.SurvivorMinimumPlayers)
			{
				// Announce the event cancelation due to lack of players
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gServerInfo.SurvivorMsg[20]);
				LogAdd(LOG_BLACK,"[Survivor] Event %d canceled due to lack of players",this->ActiveEvent);
				this->ClearEventData();
			}
			else
			{
				this->PrepareToBattle();
			}		
		}

		//Players inside the survivor map, waiting for the battle to start
		if(this->State == SURVIVOR_STATE_PREPARE)
		{
			int passedMinutes = (int) (((GetTickCount() - this->StartedAtTick) / 1000) / 60);
			int minutesToShow = 2 - passedMinutes;

			if( minutesToShow > 0 && minutesToShow == this->MinutesShowing)
			{
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gServerInfo.SurvivorMsg[13],this->MinutesShowing);
				LogAdd(LOG_BLACK,"[Survivor] Battle %d starts in %d minutes",this->ActiveEvent,this->MinutesShowing);
				this->MinutesShowing--;
			}

			if(minutesToShow <= 0)
			{
				this->State = SURVIVOR_STATE_BATTLE;
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gServerInfo.SurvivorMsg[14]);
				LogAdd(LOG_BLACK,"[Survivor] Battle %d started",this->ActiveEvent);
				this->BattleStartTick = GetTickCount();
			}
		}

		//Battle running
		if(this->State == SURVIVOR_STATE_BATTLE)
		{
			this->RunningBattle();
		}
	}
	else if(this->JoiningTimer > -1) // works!
	{
		int passedMinutes = (int) (((GetTickCount() - this->StartedAtTick) / 1000) / 60);
		int minutesToShow = 3 - passedMinutes;

		if( minutesToShow == this->MinutesShowing)
		{
			//show minutes
			if(minutesToShow > 0)
			{
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gServerInfo.SurvivorMsg[0],gServerInfo.SurvivorMsg[(this->EventType + 3)],this->MinutesShowing);
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gServerInfo.SurvivorMsg[1]);
				LogAdd(LOG_BLACK,"[Survivor] Event %d starts in %d minutes",this->ActiveEvent,this->MinutesShowing);
			}
			
			this->MinutesShowing--;
			this->JoiningTimer--;

			if(this->JoiningTimer < 0)
				this->JoiningTimer = -1;
		}
	}
	else
	{
		CTime tCurrentTime = CTime::GetTickCount();

		int iDayOfWeek = tCurrentTime.GetDayOfWeek();
		int iHour = tCurrentTime.GetHour();
		int iMinute = tCurrentTime.GetMinute();

		for(int i=0; i<MAX_SURVIVOR_SCHEDULE; i++)
		{
			if (SurvivorSchedule[i].Enable == 0)
			{
				return;
			}

			if( SurvivorSchedule[i].DayOfWeek == -1 || SurvivorSchedule[i].DayOfWeek == iDayOfWeek )
			{
				if(SurvivorSchedule[i].Hour == -1 || SurvivorSchedule[i].Hour == iHour)
				{
					if(SurvivorSchedule[i].Minute == iMinute)
					{
						if(this->State == SURVIVOR_STATE_IDLE)
						{
							this->StartCycle(i,SurvivorSchedule[i].Type);
							LogAdd(LOG_BLACK,"[Survivor] Starting event cycle %d",i);
						}
						return;
					}
				}
			}		
		}
	}
}

void CSurvivor::StartCycle(int i, int Type)
{
	this->State = SURVIVOR_STATE_JOIN_TIMER;
	this->JoiningTimer = 3;
	this->ActiveEvent = i;
	this->EventType = Type;
	this->StartedAtTick = GetTickCount();
	this->MinutesShowing= 3;
}


bool CSurvivor::IsInSurvivorArea(LPOBJ lpObj)
{
	if(lpObj->SurvivorState > 0 && lpObj->Map == gServerInfo.SurvivorMap)
	{
		if(lpObj->X >= gServerInfo.SurvivorX1 && lpObj->X <= gServerInfo.SurvivorX2)
		{
			if(lpObj->Y >= gServerInfo.SurvivorY1 && lpObj->Y <= gServerInfo.SurvivorY2)
			{
				return true;
			}
		}
	}	
	return false;
}

bool CSurvivor::IsIntruder(LPOBJ lpObj)
{
	if(lpObj->Authority == 32)
		return false;

	if(lpObj->Live == 0)
		return false;

	if(lpObj->SurvivorState == 2)
		return false;

	if(lpObj->Map == gServerInfo.SurvivorMap)
	{
		if(lpObj->X >= gServerInfo.SurvivorX1 && lpObj->X <= gServerInfo.SurvivorX2)
		{
			if(lpObj->Y >= gServerInfo.SurvivorY1 && lpObj->Y <= gServerInfo.SurvivorY2)
			{
				return true;
			}
		}
	}

	return false;
}

bool CSurvivor::IsOutruder(LPOBJ lpObj)
{
	if(lpObj->SurvivorState == 2)
	{
		if(lpObj->Map != gServerInfo.SurvivorMap)
			return true;
	
		if(lpObj->X < gServerInfo.SurvivorX1 || lpObj->X > gServerInfo.SurvivorX2)
			return true;
		
		if(lpObj->Y < gServerInfo.SurvivorY1 || lpObj->Y > gServerInfo.SurvivorY2)
			return true;
	}
	return false;
}

void CSurvivor::ClearEventData()
{
	this->State = SURVIVOR_STATE_IDLE;
	this->JoiningTimer	= -2;
	this->ActiveEvent	= -1;
	//this->EventType		= -1;
	this->StartedAtTick = -1;
	this->MinutesShowing= 3;

	for ( int n = OBJECT_START_USER ; n < MAX_OBJECT ; n++)
	{
		if ( gObj[n].Type == OBJECT_USER && gObj[n].SurvivorState > 0)
		{
			this->ClearPlayerData( &gObj[n] );
		}
	}
}

void CSurvivor::ClearPlayerData(LPOBJ lpObj)
{
	lpObj->SurvivorKillCount = 0;
	lpObj->SurvivorDieCount = 0;
	lpObj->SurvivorState = 0;
	lpObj->PKLevel = lpObj->Survivor_old_PK_Level;
	GCPKLevelSend(lpObj->Index, lpObj->PKLevel);
}

void CSurvivor::RunningBattle()
{
	int n;

	this->PlayerCount = 0;

	//Loop to control number of players alive, and intruders and "outruders"
	for(n=OBJECT_START_USER; n < MAX_OBJECT; n++)
	{
		//Check if the player is inside the battle map without the correct status (2)
		if(gServerInfo.SurvivorWinnerByKillCount == 0)
		{
			if(this->IsIntruder(&gObj[n]))
			{
				gObjMoveGate(n, 17);
				LogAdd(LOG_BLACK,"[Survivor] Player %s detected as intruder",&gObj[n].Name);
			}

			//Check if the player has the battle status (2) and is outside the event area
			if(this->IsOutruder(&gObj[n]))
			{
				LogAdd(LOG_BLACK,"[Survivor] Player %s detected outside the event area",&gObj[n].Name);
				this->ClearPlayerData(&gObj[n]);
			}
		}

		//Validate and count player
		if(gObj[n].SurvivorState == 2)
		{
			this->PlayerCount++;
			WinnerIndex = n;
		}
		
	}

	//WTF? No players? End it without winner!
	if(this->PlayerCount == 0)
	{
		LogAdd(LOG_BLACK,"[Survivor] Event ended due to zero players");
		this->ClearEventData();
	}

	//Winner by being the only survivor
	if(this->PlayerCount == 1)
	{
		//Announce the Winner
		gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gServerInfo.SurvivorMsg[17],gObj[WinnerIndex].Name);
		GCFireworksSend(&gObj[this->WinnerIndex],gObj[this->WinnerIndex].X,gObj[this->WinnerIndex].Y);
		LogAdd(LOG_BLACK,"[Survivor] Event ended. Winner: %s :: by being the only survivor",gObj[WinnerIndex].Name);
		//Give prizes here
		this->GiveWinnerPrize(&gObj[this->WinnerIndex]);
		//Function to clear event data
		this->ClearEventData();
	}
	// Event time out
	if( (GetTickCount() - this->BattleStartTick) > (gServerInfo.SurvivorTimeLimit * 60 * 1000) )
	{
		//No winners
		if(gServerInfo.SurvivorWinnerByKillCount == 0)
		{
			//Announce NO Winner
			gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gServerInfo.SurvivorMsg[19]);
			LogAdd(LOG_BLACK,"[Survivor] Event ended by time out, with no winner");
			this->ClearEventData();
		}
		else //Calculate the bigger kill count
		{
			this->WinnerIndex = 0;
			int MaxKillCount = 0;

			for(n=OBJECT_START_USER; n < MAX_OBJECT; n++)
			{
				if(gObj[n].SurvivorState == 2)
				{
					if(gObj[n].SurvivorKillCount > MaxKillCount)
					{
						this->WinnerIndex = n;
						MaxKillCount = gObj[n].SurvivorKillCount;
					}							
				}
			}

			//Announce the Winner by Kill Count
			gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gServerInfo.SurvivorMsg[18],gObj[WinnerIndex].Name);
			GCFireworksSend(&gObj[this->WinnerIndex],gObj[this->WinnerIndex].X,gObj[this->WinnerIndex].Y);
			LogAdd(LOG_BLACK,"[Survivor] Event ended. Winner: %s :: by bigest kill count",gObj[WinnerIndex].Name);

			//Give prizes here
			this->GiveWinnerPrize(&gObj[this->WinnerIndex]);

			//Ends and clear the event
			this->ClearEventData();
		}				
	}
}

void CSurvivor::PrepareToBattle()
{
	LogAdd(LOG_BLACK,"[Survivor] Battle about to start, checking and moving players");
	
	//Loop for all players
	for ( int n = OBJECT_START_USER ; n < MAX_OBJECT ; n++)
	{
		if ( gObj[n].Type == OBJECT_USER && gObj[n].SurvivorState == 1)
		{
			//Teleport players to the battle area
			int goX = gServerInfo.SurvivorX1 + (rand() % (gServerInfo.SurvivorX2 - gServerInfo.SurvivorX1));
			int	goY = gServerInfo.SurvivorY1 + (rand() % (gServerInfo.SurvivorY2 - gServerInfo.SurvivorY1));						
			gObjTeleport(gObj[n].Index, gServerInfo.SurvivorMap, goX, goY);

			//Set event status
			gObj[n].SurvivorState = 2;
			gObj[n].SurvivorKillCount = 0;
			gObj[n].SurvivorDieCount = 0;
			//Clear player buffs
			//gObjClearBuffEffect(&gObj[n], CLEAR_TYPE_NON_PCS_ITEM_EFFECT);

			//Remove from Party
			if(gObj[n].PartyNumber >= 0)
			{
				PMSG_PARTY_DEL_MEMBER_RECV pMsg;
				int pindex = gParty.GetMemberIndex(gObj[n].PartyNumber,pMsg.number);
				if(pindex >= 0)
				{
					pMsg.number = pindex;
					gParty.CGPartyDelMemberRecv(&pMsg, gObj[n].Index);
				}
			}

			//Save old PK level and set murderer to avoid CTRL requirement
			gObj[n].Survivor_old_PK_Level = gObj[n].PKLevel;
			gObj[n].PKLevel = 6;
			GCPKLevelSend(gObj[n].Index, 6);
		}
	}
	this->State = SURVIVOR_STATE_PREPARE;
	this->MinutesShowing= 2;
	this->StartedAtTick = GetTickCount();
}

void CSurvivor::GiveWinnerPrize(LPOBJ lpObj)
{	
	gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,this->wCoinC,this->wCoinP,this->GoblinCoin);
	LogAdd(LOG_RED,"[Survivor] %s got coin reward",lpObj->Name);
}