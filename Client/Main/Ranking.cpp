#include "stdafx.h"
#include "Ranking.h"
#include "Import.h"
#include "Interface.h"
#include "Util.h"
#include "RankingEx.h"
#include "Controller.h"
#include "PartySearch.h"
#include "Console.h"
#include "User.h"
#include "Config.h"
cRanking gRanking;

cRanking::cRanking()
{
	this->Active = true;
	this->Show = false;
	this->StartX = 0;
	this->StartY = 0;
	this->Page = 1;
	//ZeroMemory(&RankingChar,sizeof(RankingChar));
}

cRanking::~cRanking()
{
}

void cRanking::ImageLoad()
{
	pLoadImage("Custom\\Interface\\top.tga", 100037, 0x2601, 0x2900, 1, 0);
}

void cRanking::RecvInfo(DGCharTop * lpMsg)
{
	for(int i=0;i<MAXTOP;i++)
		{
			strncpy(this->RankingChar[i].Name,lpMsg->tp[i].Name,11);
			this->RankingChar[i].Class = lpMsg->tp[i].Class;
			this->RankingChar[i].level = lpMsg->tp[i].level;
			this->RankingChar[i].Reset = lpMsg->tp[i].Reset;
			this->RankingChar[i].Map = lpMsg->tp[i].Map;
			strncpy(this->RankingChar[i].Guild,lpMsg->tp[i].Guild,9);
			//g_Console.AddMessage(3,"%s %s",lpMsg->tp[i].Name,lpMsg->tp[i].Guild);
		}
}


void cRanking::Draw()
{
	if( !this->Active ) return;

	if(!this->Show) return;

	pSetCursorFocus = true;

	pDrawGUI(100037, StartX + 100, StartY + 10, 445, 364);
	//0x7EC5, 36, 29, 415, 30);
	pDrawGUI(0x7EC5, StartX + 505, StartY + 83, 36, 29);
	int TitleX = StartX + 150;
	int TitleY = StartY + 120;

	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "(N)");

	TitleX += 20;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Name");

	TitleX += 80;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Class");

	TitleX += 70;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Level");

	TitleX += 40;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Reset");

	if(gConfig.CustomerName == 1996)
	{
		TitleX += 50;
		gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Map");
	}

	TitleX += 55;
	gInterface.DrawFormat(eGold, TitleX, TitleY, 100, 1, "Guild");


	//pDrawGUI(0x7B67, StartX + 10 + 20, TitleY+10 , 150, 2);
	//pDrawGUI(0x7B67, StartX + 10 + 20+150, TitleY+10 , 150, 2);
	//pDrawGUI(0x7B67, StartX + 10 + 20+150+150, TitleY+10 , 150, 2);
	//pDrawGUI(0x7B67, StartX + 10 + 20+150+150+90, TitleY+10 , 150, 2);
	
	int InfoY = StartY + 135;

	int c = 0;

	for(int i = 0; i < 15; i++)
	{
		int InfoX = StartX + 150;
		int up = i + ( ( this->Page - 1 ) * 15 );

		if(this->RankingChar[up].Name[0] == NULL) continue;

		DWORD Color;

		if(c == 0 )
		{
			Color = eWhite;
		}
		else
		{
			Color = eShinyGreen;
		}

		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d", up+1);

		InfoX += 20;
		char NameID[11];
		memcpy(NameID, this->RankingChar[up].Name, sizeof(this->RankingChar[up].Name));
		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1,NameID);

		InfoX += 80;
		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, CharacterCode(this->RankingChar[up].Class));

		InfoX += 70;
		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].level);

		InfoX += 40;
		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, "%d",this->RankingChar[up].Reset);

		if(gConfig.CustomerName == 1996)
		{
			InfoX += 50;
			gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, gObjUser.GetMapName(RankingChar[up].Map)); //g_szMapName[RankingChar[up].Map]
		}
		

		InfoX += 55;

		char GuildID[9];
		memcpy(GuildID, this->RankingChar[up].Guild, sizeof(this->RankingChar[up].Guild));

		gInterface.DrawFormat(Color, InfoX, InfoY, 100, 1, GuildID);

		//pDrawGUI(0x7B67, StartX + 10 + 20, InfoY+10 , 150, 2);
		//pDrawGUI(0x7B67, StartX + 10 + 20+150, InfoY+10 , 150, 2);
		//pDrawGUI(0x7B67, StartX + 10 + 20+150+150, InfoY+10 , 150, 2);
		//pDrawGUI(0x7B67, StartX + 10 + 20+150+150+90, InfoY+10 , 150, 2);

		InfoY+=12;
		c++;
		if(c==2)c=0;
	}

	DWORD Delay = (GetTickCount() - this->ClickTime);

	int ButX = 210;
	int ButY = 90;

	pDrawGUI(0x7BAA, StartX+60+ButX, StartY+275+ButY , 17, 17);
	
	if(gInterface.CursorZoneButton(StartX+60+ButX, StartY+275+ButY, StartX+60+17+ButX, StartY+275+17+ButY))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
			if(this->Page != 1) this->Page--;
		}
		pDrawColorButton(0x7BAA, StartX+60+ButX, StartY+275+ButY, 17, 17, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	gInterface.DrawFormat(eRed, StartX+96+ButX, StartY+277+ButY, 100, 1, "Page: %d/%d", this->Page,10);


	pDrawGUI(0x7BAB, StartX+150+ButX, StartY+275+ButY , 17, 17);

	if(gInterface.CursorZoneButton(StartX+150+ButX, StartY+275+ButY, StartX+150+17+ButX, StartY+275+17+ButY))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
			if(this->Page != 10) this->Page++;
		}
		pDrawColorButton(0x7BAB, StartX+150+ButX, StartY+275+ButY, 17, 17, 0, 0, pMakeColor(255, 204, 20, 130));
	}
	//pDrawGUI(0x7EC5, StartX + 505, StartY + 83, 36, 29);
	if(gInterface.CursorZoneButton(StartX+505, StartY + 83, StartX + 541, StartY + 119))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			this->ClickTime = GetTickCount();
			gRanking.Show = false;
			pSetCursorFocus = false;
		}
		pDrawColorButton(0x7EC5, StartX + 505, StartY + 83, 36, 29, 0, 0, pMakeColor(255, 204, 20, 130));
	}
}

