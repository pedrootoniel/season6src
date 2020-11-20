#pragma once
#include "Protocol.h"
#include "Interface.h"
#include <vector>

#define MAX_ITEM_SPIN 12

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

struct CG_LUCKYSPIN_REQ
{
	PSBMSG_HEAD	h;
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
	void SwitchLuckySpinWindowState();
	void CGLuckySpinSend();
	void GCLuckySpinInit(GC_LuckySpinInit* aRecv);
	void GCItemSend(GC_LuckySpin_Data* aRecv);
	void LuckySpinData(GC_LuckySpinUpdateData * aRecv);
	void Draw();
	void EventWindow_Main(DWORD Event);
	std::vector<LuckySpin_Data> itemdata;
	DWORD StartRoll;
	int RollNumber;
};
extern CLuckySpin gLuckySpin;