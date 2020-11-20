#pragma once

#include "Protocol.h"

struct EVENTTIMER_INFO
{
	int Group;
	int DayOfWeek;
	int Hour;
	int Minute;
	//char Name[50];
	int TextIndex;
};

struct CG_EVENTTIMER_REQ
{
	PSBMSG_HEAD	Head;
	DWORD curtime;
};

struct PMSG_SEND_EVENTTIMER
{
	PSWMSG_HEAD header;
	int Count;
};

struct PMSG_SERVERTIME_SEND
{
	PSBMSG_HEAD	Head;
	// ----
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int seconds;
};

class CEventTimer
{
public:
	CEventTimer();
	virtual ~CEventTimer();
	void Load(char* path);
	void CG_RequestEvents(CG_EVENTTIMER_REQ* aRecv, int aIndex);
	void SendTime(int aIndex);
	// ----
	std::vector<EVENTTIMER_INFO> m_EventTimerInfo;
}; extern CEventTimer gEventTimer;