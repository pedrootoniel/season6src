#include "User.h"
#include "Protocol.h"
#pragma once
struct ROLL_DICE_REQ
{
	PSBMSG_HEAD header;
	int	Type; // 
	int	Number; // 
	float Money; // 
};

class cRolltheDice
{
public:
	// ----

	cRolltheDice();
	virtual ~cRolltheDice();
	void StartRoll(LPOBJ lpUser, ROLL_DICE_REQ *aRecv);
	int Dice1;
	int Dice2;
	int TotalPoint;
	int	LastProfit;
	int	Winner;
	int	enable;
	char msg[5][128];
	// ----
}; extern cRolltheDice gRolltheDice;