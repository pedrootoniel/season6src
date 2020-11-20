#include "User.h"
#include "Protocol.h"
#pragma once
struct HEADS_TAILS_REQ
{
	PSBMSG_HEAD header;
	int	Type; // 
	float Money; // 
};

class cHeadsTails
{
public:
	// ----

	cHeadsTails();
	virtual ~cHeadsTails();
	void StartFlip(LPOBJ lpUser, HEADS_TAILS_REQ *aRecv);
	int	enable;
	int	winrate;
	int	winer;
	int	winerprice;
	char msg[5][128];
	// ----
}; extern cHeadsTails gHeadsTails;