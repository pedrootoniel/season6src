#pragma once

#include "Protocol.h"

#define MAX_TIMER_TEXT 500

struct EVENT_TEXT_INFO
{
	int Index;
	char EventText[50];
};

struct EVENTTIMER_REQ
{
	PSBMSG_HEAD	Head;
	DWORD curtime;
};

struct EVENTTIMER_INFO
{
	int Group;
	int DayOfWeek;
	int Hour;
	int Minute;
	//char Name[50];
	int TextIndex;
};

struct EVENTTIMER
{
	EVENTTIMER_INFO info[10];
};

struct PMSG_SEND_EVENTTIMER
{
	PSWMSG_HEAD header;
	int Count;
};

class cEventTimer
{
public:
	cEventTimer();
	virtual ~cEventTimer();
	void Init();
	void Load(EVENT_TEXT_INFO* info);
	void SetInfo(EVENT_TEXT_INFO info);
	EVENT_TEXT_INFO* GetInfo(int index);
	char* GetText(int index);

	void EventTimerSwitch();
	void RequestEvents();
	void RecvEventTimer(PMSG_SEND_EVENTTIMER* lpMsg);
	std::vector<EVENTTIMER_INFO> getEventTimerByGroup(int group);
	std::vector<EVENTTIMER_INFO> m_EventTimerInfo;
	int m_PageCount;
	int m_CurrentPage;
	int m_MaxGroup;
	char m_DefaultMessage[128];
	EVENT_TEXT_INFO m_EventTextInfo[MAX_TIMER_TEXT];
	// ----
}; extern cEventTimer gEventTimer;