#pragma once

#define MAX_TIMER_TEXT 500

struct EVENT_TEXT_INFO
{
	int Index;
	char EventText[50];
};

class CEventText
{
public:
	CEventText();
	virtual ~CEventText();
	void Init();
	void Load(char* path);
	void SetInfo(EVENT_TEXT_INFO info);
	//----
	EVENT_TEXT_INFO m_EventTextInfo[MAX_TIMER_TEXT];
};

extern CEventText gEventText;