#pragma once
#include "stdafx.h"
#include "protocol.h"

#define MAXTOP 150

struct GDTop
{
	PSWMSG_HEAD h;
	BYTE Result;
};

struct CharTop
{
	char Name[11];
	BYTE Class;
	int level;
	int Reset;
	int Map;
	char Guild[9];
};

struct DGCharTop
{
	PSWMSG_HEAD h;
	CharTop tp[MAXTOP];
};

struct DGCharTop2
{
	PWMSG_HEAD h;
	CharTop	tp[MAXTOP];
};

class cRanking
{
public:
	void SendDS();
	void RecvDS(DGCharTop *Recv);
	void SendUser(LPOBJ lpObj);
	CharTop RankingChar[MAXTOP];
	int FirstTime;
};
extern cRanking gRanking;