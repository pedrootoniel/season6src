#pragma once

#include "User.h"

#define MAX_BOTBUFFER	30
#define MAX_BOTBUFFERSKILLS	5

struct BotBufferBodyItems
{
	int num;
	int level;
	int opt;
	bool Enabled;
};

struct botBufferSkill
{
	WORD skill;
	int time;
};

struct botBufferStruct
{
	int Class;
	int OnlyVip;
	char Name[11];
	BYTE Map;
	BYTE X;
	BYTE Y;
	BYTE Dir;
	BYTE PriceType;
	int PriceCount;
	bool Enabled;
	int index;
	WORD MaxLevel;
	BotBufferBodyItems body[9];
	botBufferSkill skill[MAX_BOTBUFFERSKILLS];
	BYTE SkillCount;
};

class CBotBuffer
{
public:
	CBotBuffer();
	virtual ~CBotBuffer();
	bool Enabled;
	void Load(char* path);
	void MakeBot();
	bool TradeOpen(int aIndex,int bIndex);
	void CheckPrice(int aIndex, int bIndex);
	static void CheckPriceCallback(LPOBJ lpObj,int botindex,LPOBJ lpNpc,DWORD WCoinC,DWORD WCoinP,DWORD GoblinPoint);
	botBufferStruct bot[MAX_BOTBUFFER];
private:
	int GetBotIndex(int aIndex);
}; extern CBotBuffer gBotBuffer;