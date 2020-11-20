#include "stdafx.h"
#include "LuckySpin.h"
#include "Interface.h"
#include "Defines.h"
#include "Offset.h"
#include "Item.h"
#include "User.h"
#include "CustomWing.h"
#include "CustomMessage.h"
#include "Protect.h"
#include "PrintPlayer.h"
#include "Console.h"
#include "Font.h"
CLuckySpin gLuckySpin;

CLuckySpin::CLuckySpin()
{
	this->StartRoll = 0;
	this->RollNumber = -1;
	this->itemdata.clear();
}

CLuckySpin::~CLuckySpin()
{
}

void CLuckySpin::SwitchLuckySpinWindowState()
{
	(gInterface.Data[eLuckySpin].OnShow == true)? gInterface.Data[eLuckySpin].Close():this->CGLuckySpinSend();
}

void CLuckySpin::GCLuckySpinInit(GC_LuckySpinInit* aRecv)
{
	if(aRecv->result)
	{
		//this->itemdata.clear();
		gInterface.Data[eLuckySpin].Open();
	}
}

void CLuckySpin::GCItemSend(GC_LuckySpin_Data* aRecv)
{
	LuckySpin_Data pData;
	pData.ItemType = aRecv->ItemType;
	pData.ItemIndex = aRecv->ItemIndex;
	pData.ItemLevel = aRecv->ItemLevel;
	pData.ItemExc = aRecv->ItemExc;
	this->itemdata.push_back(pData);
}

void CLuckySpin::CGLuckySpinSend()
{
	CG_LUCKYSPIN_REQ pRequest;
	pRequest.h.set(0xFF,0x24,sizeof(pRequest));
	DataSend((BYTE*)&pRequest,pRequest.h.size);
}

void CLuckySpin::LuckySpinData(GC_LuckySpinUpdateData * aRecv)
{
	this->StartRoll = 0;
	this->RollNumber = aRecv->RollNumber;
	//g_Console.AddMessage(1,"Roll %d",this->RollNumber);
}


void CLuckySpin::Draw()
{
	if (gInterface.CheckWindow(CashShop) ||
		gInterface.CheckWindow(ChaosBox) ||
		gInterface.CheckWindow(FullMap) ||
		gInterface.CheckWindow(MoveList) ||
		gInterface.CheckWindow(SkillTree))
		return;

	if( !gInterface.Data[eLuckySpin].OnShow )
	{
		return;
	}

	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 80.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	pDrawImage(iGfxDialoge, StartX - 30, StartY, 310, 340, 1, 1, 1.0, 1.0, 1, 1, 0); //223 280
	Font[TAHOMA_BOLD_16]->DrawText(StartX + 103,StartY + 23, Fcolor->Gold, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(251));
	//
	pDrawImage(0x9327, StartX - 10, StartY + 50, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //1
	pDrawImage(0x9327, StartX + 60, StartY + 50, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //2
	pDrawImage(0x9327, StartX + 130, StartY + 50, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //3
	pDrawImage(0x9327, StartX + 200, StartY + 50, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //4
	//
	pDrawImage(0x9327, StartX - 10, StartY + 120, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //12
	pDrawImage(0x9327, StartX - 10, StartY + 190, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //11
	pDrawImage(0x9327, StartX + 200, StartY + 120, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //5
	pDrawImage(0x9327, StartX + 200, StartY + 190, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //6
	//
	pDrawImage(0x9327, StartX - 10, StartY + 260, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //10
	pDrawImage(0x9327, StartX + 60, StartY + 260, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //9
	pDrawImage(0x9327, StartX + 130, StartY + 260, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //8
	pDrawImage(0x9327, StartX + 200, StartY + 260, 100, 60, 1, 1, 1.0, 1.0, 1, 1, 0); //7
	//
	
	if(this->StartRoll >= 1)
	{
		int ran = rand() % 11; 
		pSetBlend(true);
		switch (ran)
		{
			case 0:
				//pDrawBarForm(StartX - 10, StartY + 50, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX - 10, StartY + 50,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 1:
				//pDrawBarForm(StartX + 60, StartY + 50, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 60, StartY + 50,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 2:
				//pDrawBarForm(StartX + 130, StartY + 50, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 130, StartY + 50,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 3:
				//pDrawBarForm(StartX + 200, StartY + 50, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 200, StartY + 50,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 4:
				//pDrawBarForm(StartX + 200, StartY + 120, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 200, StartY + 120,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 5:
				//pDrawBarForm(StartX + 200, StartY + 190, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 200, StartY + 190,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 6:
				//pDrawBarForm(StartX + 200, StartY + 260, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 200, StartY + 260,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 7:
				//pDrawBarForm(StartX + 130, StartY + 260, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 130, StartY + 260,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 8:
				//pDrawBarForm(StartX + 60, StartY + 260, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 60, StartY + 260,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 9:
				//pDrawBarForm(StartX - 10, StartY + 260, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX - 10, StartY + 260,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 10:
				//pDrawBarForm(StartX - 10, StartY + 190, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX - 10, StartY + 190,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 11:
				//pDrawBarForm(StartX - 10, StartY + 120, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX - 10, StartY + 120,60,60,2.0, 2.0, 0.0, 0.5);
				break;
		}
	}
	
	if(this->RollNumber >= 0)
	{
		//pSetBlend(true);
		switch (RollNumber)
		{
			case 0:
				//pDrawBarForm(StartX - 10, StartY + 50, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX - 10, StartY + 50,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 1:
				//pDrawBarForm(StartX + 60, StartY + 50, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 60, StartY + 50,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 2:
				//pDrawBarForm(StartX + 130, StartY + 50, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 130, StartY + 50,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 3:
				//pDrawBarForm(StartX + 200, StartY + 50, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 200, StartY + 50,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 4:
				//pDrawBarForm(StartX + 200, StartY + 120, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 200, StartY + 120,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 5:
				//pDrawBarForm(StartX + 200, StartY + 190, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 200, StartY + 190,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 6:
				//pDrawBarForm(StartX + 200, StartY + 260, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 200, StartY + 260,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 7:
				//pDrawBarForm(StartX + 130, StartY + 260, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 130, StartY + 260,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 8:
				//pDrawBarForm(StartX + 60, StartY + 260, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX + 60, StartY + 260,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 9:
				//pDrawBarForm(StartX - 10, StartY + 260, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX - 10, StartY + 260,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 10:
				//pDrawBarForm(StartX - 10, StartY + 190, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX - 10, StartY + 190,60,60,2.0, 2.0, 0.0, 0.5);
				break;
			case 11:
				//pDrawBarForm(StartX - 10, StartY + 120, 60, 60, 0, 0);
				gInterface.DrawBarForm(StartX - 10, StartY + 120,60,60,2.0, 2.0, 0.0, 0.5);
				break;
		}
	}
	
	
	gInterface.DrawItem2(StartX - 10,StartY + 50,50,50,ITEM(this->itemdata[0].ItemType,this->itemdata[0].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[0].ItemLevel),this->itemdata[0].ItemExc,0,0);
	gInterface.DrawItem2(StartX + 60,StartY + 50,50,50,ITEM(this->itemdata[1].ItemType,this->itemdata[1].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[1].ItemLevel),this->itemdata[1].ItemExc,0,0);
	gInterface.DrawItem2(StartX + 130,StartY + 50,50,50,ITEM(this->itemdata[2].ItemType,this->itemdata[2].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[2].ItemLevel),this->itemdata[2].ItemExc,0,0);
	gInterface.DrawItem2(StartX + 200,StartY + 50,50,50,ITEM(this->itemdata[3].ItemType,this->itemdata[3].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[3].ItemLevel),this->itemdata[3].ItemExc,0,0);
	gInterface.DrawItem2(StartX + 200,StartY + 120,50,50,ITEM(this->itemdata[4].ItemType,this->itemdata[4].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[4].ItemLevel),this->itemdata[4].ItemExc,0,0);
	gInterface.DrawItem2(StartX + 200,StartY + 190,50,50,ITEM(this->itemdata[5].ItemType,this->itemdata[5].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[5].ItemLevel),this->itemdata[5].ItemExc,0,0);
	gInterface.DrawItem2(StartX + 200,StartY + 260,50,50,ITEM(this->itemdata[6].ItemType,this->itemdata[6].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[6].ItemLevel),this->itemdata[6].ItemExc,0,0);
	gInterface.DrawItem2(StartX + 130,StartY + 260,50,50,ITEM(this->itemdata[7].ItemType,this->itemdata[7].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[7].ItemLevel),this->itemdata[7].ItemExc,0,0);
	gInterface.DrawItem2(StartX + 60,StartY + 260,50,50,ITEM(this->itemdata[8].ItemType,this->itemdata[8].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[8].ItemLevel),this->itemdata[8].ItemExc,0,0);
	gInterface.DrawItem2(StartX,StartY + 260,50,50,ITEM(this->itemdata[9].ItemType,this->itemdata[9].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[9].ItemLevel),this->itemdata[9].ItemExc,0,0);
	gInterface.DrawItem2(StartX,StartY + 190,50,50,ITEM(this->itemdata[10].ItemType,this->itemdata[10].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[10].ItemLevel),this->itemdata[10].ItemExc,0,0);
	gInterface.DrawItem2(StartX,StartY + 120,50,50,ITEM(this->itemdata[11].ItemType,this->itemdata[11].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[11].ItemLevel),this->itemdata[11].ItemExc,0,0);
	
	//
	if(this->RollNumber >= 0)
	{
		Font[TAHOMA_BOLD_14]->DrawText(StartX + 100,StartY + 140, Fcolor->Orange, Fcolor->Trans, 15, (LPINT)5, gItem.getItemName(ITEM(this->itemdata[RollNumber].ItemType,this->itemdata[RollNumber].ItemIndex)));
		gInterface.DrawItem2(StartX + 100,StartY + 150,50,50,ITEM(this->itemdata[RollNumber].ItemType,this->itemdata[RollNumber].ItemIndex),SET_ITEMOPT_LEVEL(this->itemdata[RollNumber].ItemLevel),this->itemdata[RollNumber].ItemExc,0,0);
	}
	gInterface.DrawGUI(eLuckySpinRoll,StartX + 100,StartY + 220);
	Font[TAHOMA_BOLD_15]->DrawText(StartX + 120,StartY + 225, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(252));

	gInterface.DrawGUI(eLuckySpinClose,StartX + 240, StartY + 15);
	if( gInterface.IsWorkZone2(eLuckySpinClose) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eLuckySpinClose].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eLuckySpinClose, gInterface.Data[eLuckySpinClose].X, gInterface.Data[eLuckySpinClose].Y, Color);
	}

}

void CLuckySpin::EventWindow_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !gInterface.Data[eLuckySpin].OnShow )
	{
		return;
	}

	if (gInterface.IsWorkZone2(eLuckySpinRoll))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eLuckySpinRoll].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eLuckySpinRoll].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		gInterface.Data[eLuckySpinRoll].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 6000)
		{
			return;
		}
		// ----
		gInterface.Data[eLuckySpinRoll].EventTick = GetTickCount();
		//Func
		RollNumber = -1;
		CG_LUCKYSPIN_REQ pRequest;
		pRequest.h.set(0xFB,0x29,sizeof(pRequest));
		DataSend((BYTE*)&pRequest,pRequest.h.size);
	}

	if (gInterface.IsWorkZone2(eLuckySpinClose))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eLuckySpinClose].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eLuckySpinClose].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		gInterface.Data[eLuckySpinClose].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eLuckySpinClose].EventTick = GetTickCount();
		//Func
		this->SwitchLuckySpinWindowState();
	}
}
