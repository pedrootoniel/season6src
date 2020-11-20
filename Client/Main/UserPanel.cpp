#include "stdafx.h"
#include "UserPanel.h"
#include "User.h"
#include "Interface.h"
#include "NewInterface.h"
#include "Console.h"
#include "Controller.h"
#include "Smithy.h"
#include "Config.h"
#include "Ranking.h"
#include "NewsBoard.h"
#include "CustomMessage.h"
#include "LuckySpin.h"
#include "EventTimer.h"
// -------------------------------------------------------------------------------

UserPanel gUserPanel;
// -------------------------------------------------------------------------------

UserPanel::UserPanel()
{
	this->Init();
}
// -------------------------------------------------------------------------------

UserPanel::~UserPanel()
{

}
// -------------------------------------------------------------------------------


void UserPanel::DrawUserPanel()
{
	if (!gNewInterface.m_Data[eUserPanel].OnShow)
	{
		return;
	}
	
	if (gNewInterface.m_Data[eUserPanel].OpenedValue > 397)
	{
		gNewInterface.m_Data[eUserPanel].OpenedValue-=4;
	}

	float StartX = 125;
	float Width = 375;

	gNewInterface.DrawBarForm(StartX,gNewInterface.m_Data[eUserPanel].OpenedValue,Width,30,gConfig.MenuBackground.Red,gConfig.MenuBackground.Green,gConfig.MenuBackground.Blue,gConfig.MenuBackground.Alpha);

	gInterface.DrawAnimatedGUI(eARROW_LEFT,StartX+3,gNewInterface.m_Data[eUserPanel].OpenedValue+3);

	gInterface.DrawAnimatedGUI(eARROW_RIGHT,StartX+Width-(23),gNewInterface.m_Data[eUserPanel].OpenedValue+3);

	int count = 0;
	
		char szMenu[21][64];
		memcpy(szMenu[0],gCustomMessage.GetMessage(229),sizeof(szMenu[0]));
		memcpy(szMenu[1],gCustomMessage.GetMessage(230),sizeof(szMenu[1]));
		memcpy(szMenu[2],gCustomMessage.GetMessage(231),sizeof(szMenu[2]));
		memcpy(szMenu[3],gCustomMessage.GetMessage(232),sizeof(szMenu[3]));
		memcpy(szMenu[4],gCustomMessage.GetMessage(127),sizeof(szMenu[4]));
		memcpy(szMenu[5],gCustomMessage.GetMessage(122),sizeof(szMenu[5]));
		memcpy(szMenu[6],gCustomMessage.GetMessage(233),sizeof(szMenu[6]));
		memcpy(szMenu[7],gCustomMessage.GetMessage(234),sizeof(szMenu[7]));
		memcpy(szMenu[8],gCustomMessage.GetMessage(235),sizeof(szMenu[8]));
		memcpy(szMenu[9],gCustomMessage.GetMessage(236),sizeof(szMenu[9]));
		memcpy(szMenu[10],gCustomMessage.GetMessage(237),sizeof(szMenu[10]));
		memcpy(szMenu[11],gCustomMessage.GetMessage(238),sizeof(szMenu[11]));
		memcpy(szMenu[12],gCustomMessage.GetMessage(239),sizeof(szMenu[12]));
		memcpy(szMenu[13],gCustomMessage.GetMessage(240),sizeof(szMenu[13]));
		memcpy(szMenu[14],gCustomMessage.GetMessage(241),sizeof(szMenu[14]));
		memcpy(szMenu[15],gCustomMessage.GetMessage(242),sizeof(szMenu[15]));
		memcpy(szMenu[16],gCustomMessage.GetMessage(243),sizeof(szMenu[16]));
		memcpy(szMenu[17],gCustomMessage.GetMessage(244),sizeof(szMenu[17]));
		memcpy(szMenu[18],gCustomMessage.GetMessage(251),sizeof(szMenu[18]));
		memcpy(szMenu[19],gCustomMessage.GetMessage(253),sizeof(szMenu[19]));
		memcpy(szMenu[20],gCustomMessage.GetMessage(255),sizeof(szMenu[20]));

	for	(int i=this->StartIndex;i<USER_PANEL_BUTTONS;i++)
	{
		if (count==MAX_ON_PAGE)
		{
			return;
		}

		if (this->ButtonsArr[i] != 1)
		{
			continue;
		}
		gNewInterface.DrawButton(eUserPanelBtn1+i,StartX+25+(55*count),gNewInterface.m_Data[eUserPanel].OpenedValue+5,50,20,&gConfig.MenuButton,&gConfig.MenuButtonClick,&gConfig.MenuButtonHover,szMenu[i]);
		count++;
	}
	
}

void UserPanel::EventUserPanel(DWORD Event,MOUSEHOOKSTRUCTEX* lpMouse)
{
	if (!gNewInterface.m_Data[eUserPanel].OnShow)
	{
		return;
	}

	if (gNewInterface.IsWorkZone(105,397,105+500,397+30))
	{
		if (Event == WM_MOUSEWHEEL)
		{
			if(((int)lpMouse->mouseData) > 0)
			{
				if (this->StartIndex>0)
				{
					this->StartIndex--;
				}
			}

			if(((int)lpMouse->mouseData) < 0)
			{
				if (this->StartIndex<USER_PANEL_BUTTONS - MAX_ON_PAGE)
				{
					this->StartIndex++;
				}
			}
			return;
		}

		DWORD CurrentTick	= GetTickCount();

		for (int i=0;i<USER_PANEL_BUTTONS;i++)
		{
			int index=i+eUserPanelBtn1;

			if (gNewInterface.IsWorkZone(index))
			{
				if (this->ButtonsArr[i] != 1)
				{
					continue;
				}

				DWORD Delay	= (CurrentTick - gNewInterface.m_Data[index].EventTick);

				if( Event == WM_LBUTTONDOWN )
				{
					gNewInterface.m_Data[index].OnClick = true;
					pSetCursorFocus = true;
					continue;
				}

				gNewInterface.m_Data[index].OnClick = false;
				pSetCursorFocus = false;

				if( Delay < 500 )
				{
					continue;
				}

				gNewInterface.m_Data[index].EventTick = GetTickCount();

				/*if (gNewInterface.m_Data[index].Type == objSelectBox)
				{
					gNewInterface.m_Data[index].State ^= 1;
				}*/
				this->UserPanelSwitchState();
				//g_Console.AddMessage(5,"i = %d",i);
				USERBUTTON_REQ pRequest;
				switch (i)
				{
					case 0: //Settings
						gInterface.OpenUserPanel();
						break;
					case 1: //Roll Dice
						gInterface.OpenRolltheDiceWindow();
						break;
					case 2: //Heads Tails
						gInterface.OpenHeadsTailsWindow();
						break;
					case 3: //Lucky Number
						gInterface.OpenLuckyNumberWindow();
						break;
					case 4: //Quick Add
						gInterface.SwitchStatsWindowState();
						break;
					case 5: //Reset Stat
						gInterface.SwitchResetStatsWindowState();
						break;					
					case 6: //Change Class
						gInterface.ChangingClassWindowState();
						break;
					case 7: //Offline Attack
						gInterface.SwitchOffExpWindoState();
						break;
					case 8: //Buy Vip
						gInterface.BuyVipWindowState();
						break;
					case 9: //Title Manager
						gInterface.OpenTitleSystemWindow();
						break;
					case 10: //PartySearch
						gInterface.SwitchPartySettingsWindowState();
						break;
					case 11: //Smithy
						pRequest.Head.set(0xFF,0x04,sizeof(pRequest));
						DataSend((BYTE*)&pRequest,pRequest.Head.size);
						gSmithy.SwitchSmithyWindowState();
						break;
					case 12: //Account Security
						gInterface.AccountSecurityPWState();
						break;
					case 13: //Jewels Bank
						gInterface.JewelsBank_State();
						break;
					case 14: //Rename
						gInterface.RenameState();
						break;
					case 15:
						pRequest.Head.set(0xFF,0x21,sizeof(pRequest));
						DataSend((BYTE*)&pRequest,pRequest.Head.size);
						gRanking.Show = true;
						break;
					case 16:
						gNewsBoard.ReqOpenMain();
						break;
					case 17:
						gInterface.Fruit_State();
						break;
					case 18:
						gLuckySpin.SwitchLuckySpinWindowState();
						break;
					case 19:
						gInterface.GiftCodeState();
						break;
					case 20:
						gEventTimer.EventTimerSwitch();
						break;
					default:
						MessageBox(0,"Error! Contact server administrator","Error [0x01]",0);
				}
				return;
			}
		}

		if (gInterface.IsWorkZone2(eARROW_LEFT))
		{
			DWORD Delay	= (CurrentTick - gInterface.Data[eARROW_LEFT].EventTick);

			if( Event == WM_LBUTTONDOWN )
			{
				gInterface.Data[eARROW_LEFT].OnClick = true;
				pSetCursorFocus = true;
				return;
			}

			gInterface.Data[eARROW_LEFT].OnClick = false;
			pSetCursorFocus = false;

			if( Delay < 300 )
			{
				return;
			}

			gInterface.Data[eARROW_LEFT].EventTick = GetTickCount();

			if (this->StartIndex>0)
			{
				this->StartIndex--;
				for	(int i=eUserPanelBtn1;i<USER_PANEL_BUTTONS+eUserPanelBtn1;i++)
				{
					gNewInterface.m_Data[i].Clear();
				}
			}
		}

		if (gInterface.IsWorkZone2(eARROW_RIGHT))
		{
			DWORD Delay	= (CurrentTick - gInterface.Data[eARROW_RIGHT].EventTick);

			if( Event == WM_LBUTTONDOWN )
			{
				gInterface.Data[eARROW_RIGHT].OnClick = true;
				pSetCursorFocus = true;
				return;
			}

			gInterface.Data[eARROW_RIGHT].OnClick = false;
			pSetCursorFocus = false;

			if( Delay < 300 )
			{
				return;
			}

			int btns=0;
			for	(int i=0;i<USER_PANEL_BUTTONS;i++)
			{
				if (this->ButtonsArr[i] != 1)
				{
					btns++;
				}
			}

			gInterface.Data[eARROW_RIGHT].EventTick = GetTickCount();

			if (this->StartIndex<USER_PANEL_BUTTONS - MAX_ON_PAGE - btns)
			{
				this->StartIndex++;
				for	(int i=eUserPanelBtn1;i<USER_PANEL_BUTTONS+eUserPanelBtn1;i++)
				{
					gNewInterface.m_Data[i].Clear();
				}
			}
		}

		return;
	}
	return;
}

void UserPanel::UserPanelSwitchState()
{
	//gNewInterface.m_Data[eUserPanel].OnShow == true ? gNewInterface.m_Data[eUserPanel].Close() : gNewInterface.m_Data[eUserPanel].Open(430);
	if (gNewInterface.m_Data[eUserPanel].OnShow == true)
	{
		gNewInterface.m_Data[eUserPanel].Close();
	}
	else
	{
		this->StartIndex = 0;
		gNewInterface.m_Data[eUserPanel].Open(430);
	}
}

void UserPanel::Init()
{
	for	(int i=0;i<USER_PANEL_BUTTONS;i++)
	{
		this->ButtonsArr[i] = 0;
	}
	this->StartIndex = 0;
}
// -------------------------------------------------------------------------------

void UserPanel::GetUserPanel()
{
	this->ButtonsArr[Settings] = gInterface.m_SettingButton;
	this->ButtonsArr[RollDice] = gInterface.m_RolltheDiceButton;
	this->ButtonsArr[HeadsTails] = gInterface.m_HeadsTailsButton;
	this->ButtonsArr[LuckyNumber] = gInterface.m_LuckyNumberButton;
	this->ButtonsArr[ChangeClass] = gInterface.m_ChangeClassButton;
	this->ButtonsArr[OffAttack] = gInterface.m_OffAttackButton;
	this->ButtonsArr[BuyVip] = gInterface.m_BuyVipButton;
	this->ButtonsArr[TitleManager] = gInterface.m_TitleManagerButton;
	this->ButtonsArr[PartySearch] = gInterface.m_PartySearchSettingButton;
	this->ButtonsArr[Smithy] = gInterface.m_SmithItemButton;
	this->ButtonsArr[AccSecurity] = gInterface.m_AccountSecurityButton;
	this->ButtonsArr[JewelsBank] = gInterface.m_JewelsBankButton;
	this->ButtonsArr[RenameBox] = gInterface.m_RenameButton;
	this->ButtonsArr[TopPlayer] = gInterface.m_TopPlayer;
	this->ButtonsArr[NewBoard] = gInterface.m_NewsBoard;
	this->ButtonsArr[FruitMain] = gInterface.m_FruitMain;
	this->ButtonsArr[LuckySpin] = gInterface.m_LuckySpinMain;
	this->ButtonsArr[GiftCode] = gInterface.m_GiftCode;
	this->ButtonsArr[QuickAdd] = gInterface.m_QuickAdd;
	this->ButtonsArr[ResetStats] = gInterface.m_ResetStats;
	this->ButtonsArr[EventTimer] = gInterface.m_EventTimer;
}
// ----------------------------------------------------------------------------------------------