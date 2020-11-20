#pragma once
#include "stdafx.h"
#include "Protocol.h"

#define MAXTOP	150

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
	PWMSG_HEAD h;
	CharTop	tp[MAXTOP];
};

class cRanking
{
public:
	cRanking();
	~cRanking();

	void ImageLoad();
	void RecvInfo(DGCharTop * lpMsg);
	void Draw();

	bool Active;
	bool Show;
	int StartX;
	int StartY;
	int Page;
	DWORD ClickTime;

	CharTop	RankingChar[MAXTOP];
};
extern cRanking gRanking;
