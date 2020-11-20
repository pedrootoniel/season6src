// CustomQuiz.cpp: implementation of the CCustomQuiz class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommandManager.h"
#include "CustomQuiz.h"
#include "DSProtocol.h"
#include "ItemBagManager.h"
#include "Map.h"
#include "MapManager.h"
#include "MemScript.h"
#include "Message.h"
#include "Notice.h"
#include "ServerInfo.h"
#include "ScheduleManager.h"
#include "User.h"
#include "Util.h"
#include "Viewport.h"
#include "CashShop.h"
CCustomQuiz gCustomQuiz;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomQuiz::CCustomQuiz() // OK
{
	this->m_CustomQuiz.clear();

	this->Active		=  0;
	this->IndexSelected = -1;
	this->IndexInfo		= -1;

	for(int n=0;n < MAX_CUSTOM_QUIZ;n++)
	{
		CUSTOM_QUIZ_INFO* lpInfo = &this->m_CustomQuizInfo[n];

		lpInfo->Index = n;
		lpInfo->State = CUSTOM_QUIZ_STATE_BLANK;
		lpInfo->RemainTime = 0;
		lpInfo->TargetTime = 0;
		lpInfo->TickCount = GetTickCount();
		lpInfo->AlarmMinSave = -1;
		lpInfo->AlarmMinLeft = -1;
	}
}

CCustomQuiz::~CCustomQuiz() // OK
{

}

void CCustomQuiz::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_QUIZ;n++)
	{
		if(gServerInfo.m_CustomQuizSwitch == 0)
		{
			this->SetState(&this->m_CustomQuizInfo[n],CUSTOM_QUIZ_STATE_BLANK);
		}
		else
		{
			this->SetState(&this->m_CustomQuizInfo[n],CUSTOM_QUIZ_STATE_EMPTY);
		}
	}
}

void CCustomQuiz::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	for(int n=0;n < MAX_CUSTOM_QUIZ;n++)
	{
		this->m_CustomQuizInfo[n].StartTime.clear();
	}

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_QUIZ_START_TIME info;

					int index = lpMemScript->GetNumber();

					info.Year = lpMemScript->GetAsNumber();

					info.Month = lpMemScript->GetAsNumber();

					info.Day = lpMemScript->GetAsNumber();

					info.DayOfWeek = lpMemScript->GetAsNumber();

					info.Hour = lpMemScript->GetAsNumber();

					info.Minute = lpMemScript->GetAsNumber();

					info.Second = lpMemScript->GetAsNumber();

					this->m_CustomQuizInfo[index].StartTime.push_back(info);
				}
				else if(section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					int index = lpMemScript->GetNumber();

					strcpy_s(this->m_CustomQuizInfo[index].RuleInfo.Name,lpMemScript->GetAsString());

					this->m_CustomQuizInfo[index].RuleInfo.AlarmTime = lpMemScript->GetAsNumber();

					this->m_CustomQuizInfo[index].RuleInfo.EventTime = lpMemScript->GetAsNumber();

				}
				else if(section == 2)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOMQUIZ_QUESTION info_question;
					
					info_question.Index = lpMemScript->GetNumber();

					info_question.Value1 = lpMemScript->GetAsNumber();

					info_question.Value2 = lpMemScript->GetAsNumber();

					info_question.Value3 = lpMemScript->GetAsNumber();
					
					strcpy_s(info_question.Question,lpMemScript->GetAsString());

					strcpy_s(info_question.Answer,lpMemScript->GetAsString());

					this->m_CustomQuiz.insert(std::pair<int,CUSTOMQUIZ_QUESTION>(info_question.Index,info_question));
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomQuiz::MainProc() // OK
{
	for(int n=0;n < MAX_CUSTOM_QUIZ;n++)
	{
		CUSTOM_QUIZ_INFO* lpInfo = &this->m_CustomQuizInfo[n];

		if((GetTickCount()-lpInfo->TickCount) >= 1000)
		{
			lpInfo->TickCount = GetTickCount();

			lpInfo->RemainTime = (int)difftime(lpInfo->TargetTime,time(0));

			switch(lpInfo->State)
			{
				case CUSTOM_QUIZ_STATE_BLANK:
					this->ProcState_BLANK(lpInfo);
					break;
				case CUSTOM_QUIZ_STATE_EMPTY:
					this->ProcState_EMPTY(lpInfo);
					break;
				case CUSTOM_QUIZ_STATE_START:
					this->ProcState_START(lpInfo);
					break;
			}
		}
	}
}

void CCustomQuiz::ProcState_BLANK(CUSTOM_QUIZ_INFO* lpInfo) // OK
{

}

void CCustomQuiz::ProcState_EMPTY(CUSTOM_QUIZ_INFO* lpInfo) // OK
{
	if(lpInfo->RemainTime > 0 && lpInfo->RemainTime <= (lpInfo->RuleInfo.AlarmTime*60))
	{
		if((lpInfo->AlarmMinSave=(((lpInfo->RemainTime%60)==0)?((lpInfo->RemainTime/60)-1):(lpInfo->RemainTime/60))) != lpInfo->AlarmMinLeft)
		{
			lpInfo->AlarmMinLeft = lpInfo->AlarmMinSave;

			gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(621),lpInfo->RuleInfo.Name,(lpInfo->AlarmMinLeft+1));
		}
	}

	if(lpInfo->RemainTime <= 0)
	{
		srand(time(NULL));
		int index = rand() % this->m_CustomQuiz.size();

		CUSTOMQUIZ_QUESTION CustomQuiz;

		if (this->GetInfo(index,&CustomQuiz) == 1)
		{
			gNotice.GCNoticeSendToAll(0,0,0,0,0,0,"[%s] %s",lpInfo->RuleInfo.Name,CustomQuiz.Question);
			gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(622),lpInfo->RuleInfo.Name);

			LogAdd(LOG_BLACK,"[Quiz] Start");

			this->Active		= 1;
			this->IndexSelected = index;
			this->IndexInfo		= lpInfo->Index;
		}
		else
		{
			LogAdd(LOG_BLACK,"[Quiz] Error");
			this->Active		=  0;
			this->IndexSelected = -1;
			this->IndexInfo		= -1;
		}

		this->SetState(lpInfo,CUSTOM_QUIZ_STATE_START);
	}
}

void CCustomQuiz::ProcState_START(CUSTOM_QUIZ_INFO* lpInfo) // OK
{
	if(this->Active == 0)
	{
		LogAdd(LOG_BLACK,"[Quiz] Finish");

		this->IndexSelected = -1;

		this->IndexInfo		= -1;

		this->SetState(lpInfo,CUSTOM_QUIZ_STATE_EMPTY);
	}

	if(lpInfo->RemainTime > 0 && lpInfo->RemainTime <= (lpInfo->RuleInfo.EventTime*60)-1)
	{
		int minutes = lpInfo->RemainTime/60;

		if((lpInfo->RemainTime%60) == 0)
		{
			CUSTOMQUIZ_QUESTION CustomQuiz;

			if (this->GetInfo(this->IndexSelected,&CustomQuiz) == 1)
			{
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,"[%s] %s",lpInfo->RuleInfo.Name,CustomQuiz.Question);
				gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(622),lpInfo->RuleInfo.Name);
			}
		}
	}

	if(lpInfo->RemainTime <= 0)
	{
		gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(623),lpInfo->RuleInfo.Name);

		LogAdd(LOG_BLACK,"[Quiz] Finish");

		this->Active		=  0;

		this->IndexSelected = -1;

		this->IndexInfo		= -1;

		this->SetState(lpInfo,CUSTOM_QUIZ_STATE_EMPTY);
	}
}

void CCustomQuiz::SetState(CUSTOM_QUIZ_INFO* lpInfo,int state) // OK
{
	switch((lpInfo->State=state))
	{
		case CUSTOM_QUIZ_STATE_BLANK:
			this->SetState_BLANK(lpInfo);
			break;
		case CUSTOM_QUIZ_STATE_EMPTY:
			this->SetState_EMPTY(lpInfo);
			break;
		case CUSTOM_QUIZ_STATE_START:
			this->SetState_START(lpInfo);
			break;
	}
}

void CCustomQuiz::SetState_BLANK(CUSTOM_QUIZ_INFO* lpInfo) // OK
{

}

void CCustomQuiz::SetState_EMPTY(CUSTOM_QUIZ_INFO* lpInfo) // OK
{
	lpInfo->AlarmMinSave = -1;
	lpInfo->AlarmMinLeft = -1;

	this->CheckSync(lpInfo);
}

void CCustomQuiz::SetState_START(CUSTOM_QUIZ_INFO* lpInfo) // OK
{
	lpInfo->AlarmMinSave = -1;
	lpInfo->AlarmMinLeft = -1;

	lpInfo->RemainTime = lpInfo->RuleInfo.EventTime*60;

	lpInfo->TargetTime = (int)(time(0)+lpInfo->RemainTime);
}

void CCustomQuiz::CheckSync(CUSTOM_QUIZ_INFO* lpInfo) // OK
{
	if(lpInfo->StartTime.empty() != 0)
	{
		this->SetState(lpInfo,CUSTOM_QUIZ_STATE_BLANK);
		return;
	}

	CTime ScheduleTime;

	CScheduleManager ScheduleManager;

	for(std::vector<CUSTOM_QUIZ_START_TIME>::iterator it=lpInfo->StartTime.begin();it != lpInfo->StartTime.end();it++)
	{
		ScheduleManager.AddSchedule(it->Year,it->Month,it->Day,it->Hour,it->Minute,it->Second,it->DayOfWeek);
	}

	if(ScheduleManager.GetSchedule(&ScheduleTime) == 0)
	{
		this->SetState(lpInfo,CUSTOM_QUIZ_STATE_BLANK);
		return;
	}

	lpInfo->RemainTime = (int)difftime(ScheduleTime.GetTime(),time(0));

	lpInfo->TargetTime = (int)ScheduleTime.GetTime();
}

void CCustomQuiz::StartNow() // OK
{


}

bool CCustomQuiz::GetInfo(int index,CUSTOMQUIZ_QUESTION* lpInfo) // OK
{
	std::map<int,CUSTOMQUIZ_QUESTION>::iterator it = this->m_CustomQuiz.find(index);

	if(it == this->m_CustomQuiz.end())
	{
		return 0;
	}
	else
	{
		(*lpInfo) = it->second;
		return 1;
	}
} 

void CCustomQuiz::CommandQuiz(LPOBJ lpObj,char* arg)   
{
	if(gServerInfo.m_CustomQuizSwitch == 0)
	{
		return;
	}

	if(this->Active == 0)
	{
		return;
	}

	char answer[128] = {0};

	//gCommandManager.GetString(arg,answer,sizeof(answer),0); 

	CUSTOMQUIZ_QUESTION CustomQuiz;

	if (this->GetInfo(this->IndexSelected,&CustomQuiz) == 1)
	{
		if(strcmp(_strlwr(arg),_strlwr(CustomQuiz.Answer)) == 0)
		{
			gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(624),this->m_CustomQuizInfo[this->IndexInfo].RuleInfo.Name,lpObj->Name);
			gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(625),this->m_CustomQuizInfo[this->IndexInfo].RuleInfo.Name,CustomQuiz.Answer);

			LogAdd(LOG_BLACK,"[Quiz] Winner: %s",lpObj->Name);

			this->Active		=  0;

			this->m_CustomQuizInfo[this->IndexInfo].RemainTime = 0;
			//-- Reward
			gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0,CustomQuiz.Value1,CustomQuiz.Value2,CustomQuiz.Value3);
			GCFireworksSend(lpObj,lpObj->X,lpObj->Y);
			return;
		}
		else 
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(626),this->m_CustomQuizInfo[this->IndexInfo].RuleInfo.Name);
		}
	}
}