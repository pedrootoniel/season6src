#pragma once

#include "StdAfx.h"
#include "Protocol.h"
#include "SetItemType.h"

struct LuckySpin_Data
{
	int ItemType;
	int ItemIndex;
	int ItemLevel;
	int ItemSkill;
	int ItemLuck;
	int ItemOption;
	int ItemExc;
	int ItemTime;
};

struct GC_LuckySpin_Data
{
	PSBMSG_HEAD h;
	int ItemType;
	int ItemIndex;
	int ItemLevel;
	int ItemSkill;
	int ItemLuck;
	int ItemOption;
	int ItemExc;
	int ItemTime;
};

struct GC_LuckySpinInit
{
	PSBMSG_HEAD h;
	bool result;
};

struct GC_LuckySpinRoll
{
	PSBMSG_HEAD header;
};

struct GC_LuckySpinUpdateData
{
	PSBMSG_HEAD header; // C1:F3:E3
	int	RollNumber;
};

class CLuckySpin
{
public:
	CLuckySpin();
	~CLuckySpin();
	void Init();
	void Load();
	void Read(char* filename);
	void GCInitItem(int aIndex);
	void GCItemSend(int aIndex);
	void StartRoll(LPOBJ lpObj);
	void MakeItem(int aIndex);
	int number;
	int TicketType;
	int TicketIndex;
	std::vector<LuckySpin_Data> itemdata;
};
extern CLuckySpin gLuckySpin;