#include "stdafx.h"
#include "EventTimerText.h"
#include "MemScript.h"

CEventText gEventText;

CEventText::CEventText()
{
	
}

CEventText::~CEventText()
{
	
}

void CEventText::Init()
{
	for	(int i=0;i<MAX_TIMER_TEXT;i++)
	{
		this->m_EventTextInfo[i].Index = -1;
	}
}

void CEventText::Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

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

			EVENT_TEXT_INFO info;

			memset(&info,0,sizeof(info));
			
			info.Index = lpMemScript->GetNumber();

			strcpy_s(info.EventText,lpMemScript->GetAsString());

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CEventText::SetInfo(EVENT_TEXT_INFO info)
{
	if(info.Index < 0 || info.Index >= MAX_TIMER_TEXT)
	{
		return;
	}

	this->m_EventTextInfo[info.Index] = info;
}
