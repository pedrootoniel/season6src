#include "stdafx.h"
#include "EventTimer.h"
#include "MemScript.h"
#include "Util.h"

CEventTimer gEventTimer;

CEventTimer::CEventTimer()
{
	
}

CEventTimer::~CEventTimer()
{
	
}

void CEventTimer::Load(char* path)
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

	this->m_EventTimerInfo.clear();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			EVENTTIMER_INFO info;

			info.Group = lpMemScript->GetNumber();

			info.DayOfWeek = lpMemScript->GetAsNumber();

			info.Hour = lpMemScript->GetAsNumber();

			info.Minute = lpMemScript->GetAsNumber();

			info.TextIndex = lpMemScript->GetAsNumber();
			//strcpy_s(info.Name,lpMemScript->GetAsString());

			this->m_EventTimerInfo.push_back(info);
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;

	//if (this->m_EventTimerInfo.size() > 100)
	//{
	//	ErrorMessageBox("[EventTimer] Out of Range!\nMax Events is 100\nNow %d",this->m_EventTimerInfo.size());
	//}
}

void CEventTimer::CG_RequestEvents(CG_EVENTTIMER_REQ* aRecv, int aIndex)
{
	BYTE send[8192];

	PMSG_SEND_EVENTTIMER pMsg;
	pMsg.header.set(0xF3, 0xF8, sizeof(pMsg));

	int size = sizeof(pMsg);

	pMsg.Count = 0;

	for (int i=0;i<this->m_EventTimerInfo.size();i++)
	{
		/*if (i>=100)
		{
			break;
		}*/

		memcpy(&send[size],&this->m_EventTimerInfo[i],sizeof(this->m_EventTimerInfo[i]));
		size += sizeof(this->m_EventTimerInfo[i]);

		pMsg.Count ++;
	}

	pMsg.header.size[0] = SET_NUMBERHB(size);

	pMsg.header.size[1] = SET_NUMBERLB(size);

	memcpy(send,&pMsg,sizeof(pMsg));
	DataSend(aIndex,send,size);
}

void CEventTimer::SendTime(int aIndex)
{
	PMSG_SERVERTIME_SEND pMsg;
	pMsg.Head.set(0xFB,0x10, sizeof(pMsg));

	CTime ctime(time(0));

	pMsg.year = ctime.GetYear();
	pMsg.month = ctime.GetMonth();
	pMsg.day = ctime.GetDay();
	pMsg.hour = ctime.GetHour();
	pMsg.minute = ctime.GetMinute();
	pMsg.seconds = ctime.GetSecond();

	DataSend(aIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}