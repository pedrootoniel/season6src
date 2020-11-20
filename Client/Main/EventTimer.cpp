#include "stdafx.h"
#include "EventTimer.h"
#include "UserPanel.h"
#include "Interface.h"

cEventTimer gEventTimer;

cEventTimer::cEventTimer()
{
	this->Init();
}

cEventTimer::~cEventTimer()
{
	
}

void cEventTimer::Init()
{
	memset(this->m_DefaultMessage,0,sizeof(this->m_DefaultMessage));
	for	(int i=0;i<MAX_TIMER_TEXT;i++)
	{
		this->m_EventTextInfo[i].Index = -1;
	}
}

void cEventTimer::Load(EVENT_TEXT_INFO* info) // OK
{
	for(int n=0;n < MAX_TIMER_TEXT;n++)
	{
		this->SetInfo(info[n]);
	}
}

void cEventTimer::SetInfo(EVENT_TEXT_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_TIMER_TEXT)
	{
		return;
	}

	this->m_EventTextInfo[info.Index] = info;
}

EVENT_TEXT_INFO* cEventTimer::GetInfo(int index)
{
	if(index < 0 || index >= MAX_TIMER_TEXT)
	{
		wsprintf(this->m_DefaultMessage,"Text %d out of bound!",index);
		return 0;
	}

	for	(int i=0;i<MAX_TIMER_TEXT;i++)
	{
		if (this->m_EventTextInfo[i].Index == index)
		{
			return &this->m_EventTextInfo[i];
		}
	}

	wsprintf(this->m_DefaultMessage,"Could not find text %d!",index);
	return 0;
}


char* cEventTimer::GetText(int index)
{
	EVENT_TEXT_INFO* lpInfo = this->GetInfo(index);
	if(lpInfo==0){return this->m_DefaultMessage;}
	return lpInfo->EventText;
}

void cEventTimer::EventTimerSwitch()
{

	if (gInterface.Data[eEVENTTABLE_MAIN].OnShow == true)
	{
		gInterface.Data[eEVENTTABLE_MAIN].Close();
	}
	else
	{
		this->RequestEvents();
		//gInterface.Data[eEVENTTABLE_MAIN].Open();
	}
}


void cEventTimer::RequestEvents()
{

	DWORD curtime = time(0);

	EVENTTIMER_REQ pRequest;
	pRequest.Head.set(0xFF,0x1C,sizeof(pRequest));

	pRequest.curtime = time(0);

	DataSend((BYTE*)&pRequest,pRequest.Head.size);
}

void cEventTimer::RecvEventTimer(PMSG_SEND_EVENTTIMER* lpMsg)
{

	this->m_EventTimerInfo.clear();
	this->m_MaxGroup = -1;

	for(int i=0;i<lpMsg->Count;i++)
	{
		EVENTTIMER_INFO* lpInfo = (EVENTTIMER_INFO*)(((BYTE*)lpMsg)+sizeof(PMSG_SEND_EVENTTIMER)+(sizeof(EVENTTIMER_INFO)*i));

		if (lpInfo->Group > this->m_MaxGroup)
		{
			this->m_MaxGroup = lpInfo->Group;
		}

		//g_Console.AddMessage(5,"%d - %d - %d - %d - %d",lpInfo->Group,lpInfo->DayOfWeek,lpInfo->Hour,lpInfo->Minute,lpInfo->TextIndex);

		this->m_EventTimerInfo.push_back(*lpInfo);
	}

	//g_Console.AddMessage(5,"RECV! count:[%d]",this->m_EventTimerInfo.size());

	//this->m_PageCount = (this->m_EventTimerInfo.size()-1)/20;
	this->m_PageCount = this->m_MaxGroup/20;
	this->m_CurrentPage = 0;

	gInterface.Data[eEVENTTABLE_MAIN].Open();
}

std::vector<EVENTTIMER_INFO> cEventTimer::getEventTimerByGroup(int group)
{
	std::vector<EVENTTIMER_INFO> mTimer;
	for	(int i=0;i<this->m_EventTimerInfo.size();i++)
	{
		if (this->m_EventTimerInfo[i].Group == group)
		{
			mTimer.push_back(this->m_EventTimerInfo[i]);
		}
	}

	return mTimer;
}
