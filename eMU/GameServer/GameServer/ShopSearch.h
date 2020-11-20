#pragma once
// ----------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Protocol.h"

#define CUSTOM_PERSONAL_SHOP TRUE
// ----------------------------------------------------------------------------------------------

#if(CUSTOM_PERSONAL_SHOP==TRUE)

struct GC_PersonalShopInfo
{
	WORD aIndex;
	char Name[11];
	char PersonalText[36];
	BYTE Value;
};
// ----------------------------------------------------------------------------------------------

struct CG_PersonalPage
{
	PSBMSG_HEAD h;
	BYTE Page;
};
// ----------------------------------------------------------------------------------------------

class PersonalShopEx
{
public:
	void Init();
	void Load();
	void Read(char* File);

	bool NPC_Dialog(LPOBJ lpObj, LPOBJ lpNpc);
	
	void Search(int aIndex, CG_PersonalPage* aRecv);

	int NPC_CLASS;
	int NPC_MAP;
	int NPC_X;
	int NPC_Y;
};
extern PersonalShopEx g_PersonalShopEx;
// ----------------------------------------------------------------------------------------------
#endif