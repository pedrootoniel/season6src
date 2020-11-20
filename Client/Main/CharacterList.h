#pragma once
#include "Protocol.h"

struct PMSG_CHARACTER_INFO
{
	char Name[11];
	int Reset;
	int GReset;
};

struct PMSG_CHARACTER_INFO_DATA
{
	PSWMSG_HEAD header;
	int Count;
};

struct CharacterInfo
{
	int Exist;
	char Name[11];
	int Reset;
};


class cCharacterList
{
public:
	void ClearCharacterList();
	void SetList(PMSG_CHARACTER_INFO_DATA *lpMsg);
	int GetResetByName(char *Name);
	void GetInfo(char* Name, int *Reset);
	// ----
	CharacterInfo CharList[25];
}; extern cCharacterList gCharacterList;