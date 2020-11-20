// Interface.cpp: implementation of the Interface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Interface.h"
#include "Defines.h"
#include "Offset.h"
#include "Protocol.h"
#include "Reconnect.h"
#include "Camera.h"
#include "Object.h"
#include "array.h"
#include "CustomMessage.h"
#include "CustomFog.h"
#include "HealthBar.h"
#include "PrintPlayer.h"
#include "Import.h"
#include "User.h"
#include "TMemory.h"
#include <time.h>
#include "LoadMap.h"
#include "Font.h"
#include "DanhHieu.h"
#include "CustomTitle.h"
#include "Other.h"
#include "CustomPet.h"
#include "CSmithItem.h"
#include "Smithy.h"
#include "LicenseInfo.h"
#include "PartySearch.h"
#include "PartySearchSettings.h"
#include "Protect.h"
#include "Util.h"
#include "ChangeClass.h"
#include "BuyVip.h"
#include "NewInterface.h"
#include "ShopSearch.h"
#include "Ranking.h"
#include "NewsBoard.h"
#include "Controller.h"
#include "LuckySpin.h"
#include "Config.h"
#include "UserPanel.h"
#include "EventTimer.h"
#include "Minimap.h"
#include "NewParty.h"
#include "HealthBar.h"


Interface	gInterface;

DWORD		AddSomeShine_Buff;
DWORD		AddSomeShine_Pointer;
DWORD		ServerExtern_Buff;
char	ServerExtern_LevelBuff[40];
DWORD		StaffNameColor_Buff;
lpCharObj	StaffNameColor_lpView;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Interface::Interface() //ok
{
	ZeroMemory(this->Data, sizeof(this->Data));
}

Interface::~Interface() //ok
{

}

Naked(StaffNameColor)
{
	_asm
	{
		mov ecx, dword ptr ss:[ebp+0x10]
		mov StaffNameColor_Buff, ecx
	}
	// ----
	StaffNameColor_lpView = &*(ObjectCharacter*)(*(DWORD*)(StaffNameColor_Buff + 0x00));
	// ----
	if( !strncmp(StaffNameColor_lpView->Name, "xGOD", 5) )
	{
		pSetTextColor(pTextThis(), 255, 60, 160, 255);
	}
	else
	{
		pSetTextColor(pTextThis(), 100, 250, 250, 255);
	}
	
	_asm
	{
		mov StaffNameColor_Buff, 0x00598C9A
		jmp StaffNameColor_Buff
	}
}

Naked(AddSomeShine)
{
	_asm
	{
		Mov eax, dword ptr ds:[ecx + 0x30]
		Mov AddSomeShine_Buff, eax
	}
	if(AddSomeShine_Buff == 349 || AddSomeShine_Buff == 406 || AddSomeShine_Buff == 407 || AddSomeShine_Buff == 408 )
	{
		_asm
		{
			mov AddSomeShine_Buff, 0x005E4979
				jmp AddSomeShine_Buff
		}
	}
	else
	{
		_asm
		{
			mov AddSomeShine_Buff, 0x005E4A3C
				jmp AddSomeShine_Buff
		}
	}
}

char sub_810700(LPVOID This)
{
	return 0;
}

Naked(ChangeServerName)
{
	wsprintf(ServerExtern_LevelBuff, gCustomMessage.GetMessage(5));
	//ServerExtern_LevelBuff = gCustomMessage.GetMessage(5);
	_asm
	{
		lea eax, ServerExtern_LevelBuff
		push eax
	}
	_asm
	{
		mov ServerExtern_Buff, 0x0095414D
		jmp ServerExtern_Buff
	}
}

void Interface::DrawCSServer(BYTE Red, BYTE Green, BYTE Blue, BYTE Opacity)
{

	if (*(DWORD*)(MAIN_SCREEN_STATE) == 2)
	{
		pDrawImage(iBg1, 0.0f, 0.0f, 160.0f, 240.0f, 1, 1, 1.0f, 1.0f, 1, 1, 1);
		pDrawImage(iBg2, 160.0f, 0.0f, 160.0f, 240.0f, 1, 1, 1.0f, 1.0f, 1, 1, 1);
		pDrawImage(iBg3, 320.0f, 0.0f, 160.0f, 240.0f, 1, 1, 1.0f, 1.0f, 1, 1, 1);
		pDrawImage(iBg4, 480.0f, 0.0f, 160.0f, 240.0f, 1, 1, 1.0f, 1.0f, 1, 1, 1);
		pDrawImage(iBg5, 0.0f, 240.0f, 160.0f, 240.0f, 1, 1, 1.0f, 1.0f, 1, 1, 1);
		pDrawImage(iBg6, 160.0f, 240.0f, 160.0f, 240.0f, 1, 1, 1.0f, 1.0f, 1, 1, 1);
		pDrawImage(iBg7, 320.0f, 240.0f, 160.0f, 240.0f, 1, 1, 1.0f, 1.0f, 1, 1, 1);
		pDrawImage(iBg8, 480.0f, 240.0f, 160.0f, 240.0f, 1, 1, 1.0f, 1.0f, 1, 1, 1);
		//-------------------
		//pDrawImage(iLogo, 250.0f, 50.0f, 140.0f, 70.0f, 0, 0, 1.0f, 1.0f, 1, 1, 1);

		Font[ARIAL_14]->DrawText(0, 470, Fcolor->White, Fcolor->Trans25, 640, (LPINT)3, gCustomMessage.GetMessage(31));
	}

	pSetTextColor(pTextThis(), Red, Green, Blue, Opacity);
}


void Interface::Work()
{
	ReconnectMainProc();
	gObjUser.Refresh();
	gNewInterface.Work();
	gInterface.DrawAutoInfo();
	gInterface.DrawUserPanel();
	//gInterface.DrawGamblingPanel();
	gInterface.RolltheDice();
	gInterface.TitleSystem();
	gInterface.DrawMiniMap();
	gInterface.HUDEvent();
	gInterface.HeadsTails();
	gInterface.DrawLuckyNumber();
	//gInterface.DrawTitleManagerButton();
	//gInterface.DrawSmithItem();
	gSmithy.Draw();
	g_PersonalShopEx.Draw();
	gRanking.Draw();
	gInterface.DrawPartySearchWindow();
	gInterface.DrawPartySettingsWindow();
	gInterface.DrawStatsAddWindow();
	gInterface.DrawResetStatsWindow();
	gInterface.DrawOffExpWindow();
	gInterface.DrawAccountSecurityPW();
	gInterface.DrawAccountSecurity();
	gInterface.DrawChangingClassWindow();
	gInterface.DrawVipWindow();
	gInterface.DrawRename();
	gInterface.DrawPSHOP();
	gInterface.DrawPSHOP_OFFMODE();
	gInterface.DrawJewelsBank();
	gInterface.DrawRPS();
	gInterface.DrawNewsWindow();
	gInterface.DrawFruit();
	//gInterface.DrawAttention();
	gLuckySpin.Draw();
	gInterface.DrawGiftCode();
	gInterface.DrawUsersPanel();
	gInterface.PartyInterface();
	gInterface.DrawEventTableWindow();
	gInterface.DrawWarehouseUI();
	if(strcmp(gLicenseInfo.RFbt,"2") == 0)
	{
	gInterface.DrawDragonLeft();
	gInterface.DrawDragonRight();
	}
	if(strcmp(gLicenseInfo.RFbt,"1") == 0)
	{
	gInterface.DrawDragonLeft();
	gInterface.DrawDragonRight();
	}
	
	pDrawInterface();
	if(strcmp(gLicenseInfo.RFbt,"2") == 0)
	{
	gInterface.DrawS2Interface();
	gInterface.DrawExpBar();
	gInterface.DrawMenuButton();
	}
	if(strcmp(gLicenseInfo.RFbt,"1") == 0)
	{
	gInterface.DrawS2Interface();
	gInterface.DrawExpBar();
	gInterface.DrawMenuButton1();
	}

}

void Interface::Load()
{
	this->BindObject(eUSERSPANEL_BUTTON, 0x788C, 16, 12, 175.5, 1);
	this->BindObject(eUSERSPANELBG, 0x787A, 37, 18, 173, 0);
	gSmithy.BindImg();
	g_PersonalShopEx.BindImages();
	this->BindObject(eARROW_LEFT,0x7E59,20,22,-1,-1);
	this->BindObject(eARROW_RIGHT,0x7E5A,20,22,-1,-1);
	this->BindObject(eTitleManagerButton, 0x7E4B, 73, 26, 462, 367);
	this->BindObject(eSmithItemButton, 0x7E4B, 73, 26, 560, 367);
	this->BindObject(ePartySearchButton, 0x7A5E, 108, 28, 491, 363);
	//
	this->BindObject(eUNCHECK_2, iOptionCheck, 15, 15, 175, 60);
	this->BindObject(eUNCHECK_3, iOptionCheck, 15, 15, 175, 90);
	this->BindObject(eUNCHECK_6, iOptionCheck, 15, 15, 195, 90);
	this->BindObject(eUNCHECK_4, iOptionCheck, 15, 15, 175, 120);
	this->BindObject(eUNCHECK_5, iOptionCheck, 15, 15, 175, 150);
	this->BindObject(eCHECKED_2, iOptionCheck, 15, 15, 175, 60);
	this->BindObject(eCHECKED_3, iOptionCheck, 15, 15, 175, 90);
	this->BindObject(eCHECKED_6, iOptionCheck, 15, 15, 195, 90);
	this->BindObject(eCHECKED_4, iOptionCheck, 15, 15, 175, 120);
	this->BindObject(eCHECKED_5, iOptionCheck, 15, 15, 175, 150);
	this->BindObject(eBUTTON3_1, iGfxBtnSmall, 52, 21, 90, 250);
	//this->BindObject(eBUTTON4_1, iGfxBtnSmall, 52, 21, 130, 250);
	//
	this->BindObject(eUSERSPANEL_MAIN, 0x7A5A, 222, 263, 1, 20.0);

	this->BindObject(eNewButton1, iGfxBtnSmall, 52, 21, 30, 210);
	this->BindObject(eNewButton2, iGfxBtnSmall, 52, 21, 90, 210);
	this->BindObject(eNewButton3, iGfxBtnSmall, 52, 21, 150, 210);
	//--
	this->BindObject(eEmptySmall1, iGfxBtn, 64, 29, 10, 70);
	this->BindObject(eEmptySmall2, iGfxBtn, 64, 29, 80, 70);
	this->BindObject(eEmptySmall3, iGfxBtn, 64, 29, 150, 70);
	this->BindObject(eEmptySmall5, iGfxBtn, 64, 29, 10, 130);
	this->BindObject(eEmptySmall6, iGfxBtn, 64, 29, 80, 130);
	this->BindObject(eEmptySmall7, iGfxBtn, 64, 29, 150, 130);
	this->BindObject(eEmptySmall8, iGfxBtn, 64, 29, 10, 190);
	this->BindObject(eEmptySmall9, iGfxBtn, 64, 29, 80, 190);
	this->BindObject(eEmptySmall10, iGfxBtn, 64, 29, 150, 190);

	this->BindObject(eEmptySmall4, iGfxBtnSmall, 52, 21, 90, 250);//Close


	this->BindObject(ROLLDICE_CLOSE, 0x7EC5, 36, 29, 415, 30);
	this->BindObject(HEADSTAILS_CLOSE, 0x7EC5, 36, 29, 415, 30);
	this->BindObject(LUCKYNUMBER_CLOSE, 0x7EC5, 36, 29, 415, 30);
	this->BindObject(TITLEMANAGER_CLOSE, 0x7EC5, 36, 29, 388, 95);
	//--
	this->BindObject(eSkillBox, iNewSkillBox, 32, 38, 305, 443);
	this->BindObject(eDragonLeft, iDragonLeft, 108, 45, 0, 388);
	this->BindObject(eDragonRight, iDragonRight, 108, 45, 532, 388);
	this->BindObject(eParty, iNewParty, 25, 25, 348, 449);
	this->BindObject(eCharacter, iNewCharacter, 25, 25, 379, 449);
	this->BindObject(eInventory, iNewInventory, 25, 25, 409, 449);
	this->BindObject(eFriend, iNewWinpush, 54, 20, 581, 432);
	this->BindObject(eFastMenu, iNewFastMenu, 55, 21, 5, 432);
	this->BindObject(ePkMenu,0x9A52,54,20,581,456);
	//--
	this->BindObject(eRollMain, iRollMain, 250, 380, 200, 300);
	this->BindObject(eRollOver, iRollOver, 72, 13, 228, 52);
	this->BindObject(eRollUnder, iRollUnder, 72, 13, 228, 67);
	this->BindObject(eRollUp, iRollUp, 15, 13, 342, 52);
	this->BindObject(eRollDown, iRollDown, 15, 13, 342, 67);
	this->BindObject(eRollButtonA, iRollButton, 17, 13, 310, 375);
	this->BindObject(eRollButtonB, iRollButton, 17, 13, 335, 375);
	this->BindObject(eRollStart, iRollStart, 62, 21, 365, 372);
	//--
	this->BindObject(eFlipMain, 0x9690, 250, 380, 200, 300);
	this->BindObject(eFlipHeads, 0x9691, 30, 30, 235, 50);
	this->BindObject(eFlipTails, 0x9693, 30, 30, 290, 50);
	this->BindObject(eFlipButtonA, iRollButton, 17, 13, 310, 375);
	this->BindObject(eFlipButtonB, iRollButton, 17, 13, 335, 375);
	this->BindObject(eFlipStart, iRollStart, 62, 21, 365, 372);
	//--
	this->BindObject(eLuckyMain, 0x9670, 250, 380, 200, 300);
	this->BindObject(eLuckyButtonA, iRollButton, 17, 13, 310, 375);
	this->BindObject(eLuckyButtonB, iRollButton, 17, 13, 335, 375);
	this->BindObject(eLuckyStart, iRollStart, 62, 21, 365, 372);
	//--
	this->BindObject(eTitle,0x9921, 165, 146, -1, -1);
	this->BindObject(eClickLeft,0x9923, 12, 12, -1, -1);
	this->BindObject(eClickRight,0x9924, 12, 12, -1, -1);
	this->BindObject(eRankSlot1,0x9925, 28, 11, -1, -1);
	this->BindObject(eRankBuy,0x9925, 28, 11, -1, -1);
	this->BindObject(eRankDeactive,0x9925, 28, 11, -1, -1);
	//--
	/*
	this->BindObject(eSMITH_MAIN, 0x7A5A, 222, 383, -1, -1);
	this->BindObject(eSMITH_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eSMITH_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eSMITH_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eSMITH_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eSMITH_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eSMITH_BUY, 0x7A5E, 128, 29, -1, -1);
	//--
	//Add Remove
	this->BindObject(eSMITH_ITEMTYPE, 0x7C0D, 16, 15, 215, 70);
	this->BindObject(eSMITH_ITEMTYPE_1, 0xAA4, 16, 15, 273, 70);
	this->BindObject(eSMITH_ITEMINDEX, 0x7C0D, 17, 18, 208, 103);
	this->BindObject(eSMITH_ITEMINDEX_1, 0xAA4, 17, 18, 400, 103);
	this->BindObject(eSMITH_DAYS, 0x7C0D, 16, 15, 340, 70);
	this->BindObject(eSMITH_DAYS_1, 0xAA4, 16, 15, 393, 70);
	this->BindObject(eSMITH_LEVEL, 0x7C0D, 16, 15, 340, 153);
	this->BindObject(eSMITH_LEVEL_1, 0xAA4, 16, 15, 380, 153);
	this->BindObject(eSMITH_OPT, 0x7C0D, 16, 15, 340, 213);
	this->BindObject(eSMITH_OPT_1, 0xAA4, 16, 15, 380, 213);
	//Uncheck - Check
	this->BindObject(eSMITH_SKILL, 0x7B69, 15, 15, 380, 175);
	this->BindObject(eSMITH_SKILL_1, 0x7B69, 15, 15, 380, 175);
	this->BindObject(eSMITH_LUCK, 0x7B69, 15, 15, 380, 195);
	this->BindObject(eSMITH_LUCK_1, 0x7B69, 15, 15, 380, 195);
	this->BindObject(eSMITH_EXC, 0x7B69, 15, 15, 380, 235);
	this->BindObject(eSMITH_EXC_1, 0x7B69, 15, 15, 380, 235);
	this->BindObject(eSMITH_EXC1, 0x7B69, 15, 15, 380, 255);
	this->BindObject(eSMITH_EXC1_1, 0x7B69, 15, 15, 380, 255);
	this->BindObject(eSMITH_EXC2, 0x7B69, 15, 15, 380, 275);
	this->BindObject(eSMITH_EXC2_1, 0x7B69, 15, 15, 380, 275);
	this->BindObject(eSMITH_EXC3, 0x7B69, 15, 15, 380, 295);
	this->BindObject(eSMITH_EXC3_1, 0x7B69, 15, 15, 380, 295);
	this->BindObject(eSMITH_EXC4, 0x7B69, 15, 15, 380, 315);
	this->BindObject(eSMITH_EXC4_1, 0x7B69, 15, 15, 380, 315);
	this->BindObject(eSMITH_EXC5, 0x7B69, 15, 15, 380, 335);
	this->BindObject(eSMITH_EXC5_1, 0x7B69, 15, 15, 380, 335);
	*/
	//-- Party Search
	this->BindObject(ePARTYSETTINGS_MAIN, 0x7A5A, 222, 345, -1, -1);
	this->BindObject(ePARTYSETTINGS_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(ePARTYSETTINGS_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(ePARTYSETTINGS_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(ePARTYSETTINGS_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(ePARTYSETTINGS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(ePARTYSETTINGS_SYSTEM_ACTIVE, 0x7BAE, 15, 15, 380, 83);
	this->BindObject(ePARTYSETTINGS_ONLY_GUILD, 0x7BAE, 15, 15, 380, 135); 
	this->BindObject(ePARTYSETTINGS_ONE_CLASS, 0x7BAE, 15, 15, 380, 157); 
	this->BindObject(ePARTYSETTINGS_DARK_WIZARD, 0x7BAE, 15, 15, 380, 180);
	this->BindObject(ePARTYSETTINGS_DARK_KNIGHT, 0x7BAE, 15, 15, 380, 203);
	this->BindObject(ePARTYSETTINGS_ELF, 0x7BAE, 15, 15, 380, 226);
	this->BindObject(ePARTYSETTINGS_MAGIC_GLADIATOR, 0x7BAE, 15, 15, 380, 249);
	this->BindObject(ePARTYSETTINGS_DARK_LORD, 0x7BAE, 15, 15, 380, 272);
	this->BindObject(ePARTYSETTINGS_SUMMONER, 0x7BAE, 15, 15, 380, 295);
	this->BindObject(ePARTYSETTINGS_RAGE_FIGHTER, 0x7BAE, 15, 15, 380, 328);
	this->BindObject(ePARTYSETTINGS_LEVEL_MINUS, 0x7C0D, 16, 15, 355, 110);
	this->BindObject(ePARTYSETTINGS_LEVEL_PLUS, 0x7AA4, 16, 15, 398, 110);
	this->BindObject(ePARTYSETTINGS_OK, 0x7A5B, 54, 30, -1, -1);
	//
	this->BindObject(ePARTYSEARCH_MAIN, 0x7A5A, 222, 345, -1, -1);
	this->BindObject(ePARTYSEARCH_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(ePARTYSEARCH_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(ePARTYSEARCH_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(ePARTYSEARCH_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(ePARTYSEARCH_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(ePARTYSEARCH_LEFT, 0x7E56, 20, 23, -1, -1);
	this->BindObject(ePARTYSEARCH_RIGHT, 0x7E57, 20, 23, -1, -1);
	//
	this->BindObject(eSTATSADD_MAIN, 0x7A5A, 222, 226, -1, -1);
	this->BindObject(eSTATSADD_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eSTATSADD_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eSTATSADD_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eSTATSADD_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eSTATSADD_TEXTBOX01, 0x9206, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX01, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX02, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX03, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX04, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX05, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_BTN_OK, 0x7A5B, 54, 30, -1, -1);
	//
	this->BindObject(eRESETSTATS_MAIN, 0x7A5A, 222, 140, -1, -1);
	this->BindObject(eRESETSTATS_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eRESETSTATS_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eRESETSTATS_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eRESETSTATS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eRESETSTATS_POINT, 0x7B68, 10, 10, -1, -1);
	this->BindObject(eRESETSTATS_CHECK_WC, 0x7BAE, 15, 15, 390, 132);
	this->BindObject(eRESETSTATS_CHECK_STAT, 0x7BAE, 15, 15, 390, 152);
	this->BindObject(eRESETMASTER_CHECK_WC, 0x7BAE, 15, 15, 390, 172);
	this->BindObject(eRESETMASTER_CHECK_STAT, 0x7BAE, 15, 15, 390, 192);
	this->BindObject(eRESETSTATS_BTN_OK, 0x7A5B, 54, 30, -1, -1);
	//
	this->BindObject(eCHARINFO_BTN_STAT, 0x7AA4, 16, 15, 475, 73);
	this->BindObject(eCHARINFO_BTN_RESSTAT, 0x7AA4, 16, 15, 475, 94);
	///
	this->BindObject(eOFFEXP_MAIN, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(eOFFEXP_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eOFFEXP_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eOFFEXP_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eOFFEXP_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eOFFEXP_POINT, 0x7B68, 10, 10, -1, -1);
	this->BindObject(eOFFEXP_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eOFFEXP_FINISH, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eOFFEXP_CHECKBOX_BUFF, 0x7BAE, 15, 15, 390, 220);
	this->BindObject(eOFFEXP_CHECKBOX_PICK_ZEN, 0x7BAE, 15, 15, 390, 260);
	this->BindObject(eOFFEXP_CHECKBOX_PICK_JEWELS, 0x7BAE, 15, 15, 390, 280);
	this->BindObject(eOFFEXP_CHECKBOX_PICK_EXC, 0x7BAE, 15, 15, 390, 300);
	this->BindObject(eOFFEXP_CHECKBOX_PICK_ANC, 0x7BAE, 15, 15, 390, 320);
	this->BindObject(eOFFEXP_CHECKBOX_SELECTED_HELPER, 0x7BAE, 15, 15, 390, 340);
	this->BindObject(eOFFEXP_BTN_OK, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eOFFEXP_SKILL1, 0x7A4C, 20, 28, -1, -1);
	this->BindObject(eOFFEXP_SKILL2, 0x7A4C, 20, 28, -1, -1);
	this->BindObject(eOFFEXP_SKILL3, 0x7A4C, 20, 28, -1, -1);
	//
	this->BindObject(eSECURITY_CHECK_MAIN, 0x7A5A, 222, 110, -1, -1);
	this->BindObject(eSECURITY_CHECK_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eSECURITY_CHECK_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eSECURITY_CHECK_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eSECURITY_CHECK_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eSECURITY_CHECK_BOX, 0x7AA3, 170, 21, 220, 140);
	this->BindObject(eSECURITY_CHECK_OK, 0x7A5F, 62, 27, -1, -1);
	this->BindObject(eSECURITY_CHECK_CLOSE, 0x7A5F, 62, 27, -1, -1);
	//
	this->BindObject(eSECURITY_MAIN, 0x7A5A, 222, 285, -1, -1);
	this->BindObject(eSECURITY_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eSECURITY_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eSECURITY_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eSECURITY_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eSECURITY_TRADE, 0x7BAE, 15, 15, 385, 133);
	this->BindObject(eSECURITY_INVENTORY, 0x7BAE, 15, 15, 385, 153);
	this->BindObject(eSECURITY_WAREHOUSE, 0x7BAE, 15, 15, 385, 173);
	this->BindObject(eSECURITY_PERSONALSHOP, 0x7BAE, 15, 15, 385, 193);
	this->BindObject(eSECURITY_SHOP, 0x7BAE, 15, 15, 385, 213);
	this->BindObject(eSECURITY_CHAOBOX, 0x7BAE, 15, 15, 385, 233);
	this->BindObject(eSECURITY_DELCHAR, 0x7BAE, 15, 15, 385, 253);
	this->BindObject(eSECURITY_SAVE, 0x7A5F, 62, 27, -1, -1);
	//
	this->BindObject(eSELECTCHAR_LEFT, 0x7E56, 20, 23, 285, 410);
	this->BindObject(eSELECTCHAR_RIGHT, 0x7E57, 20, 23, 330, 410);
	//
	this->BindObject(eCHANGINGCLASS_MAIN, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(eCHANGINGCLASS_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCHANGINGCLASS_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCHANGINGCLASS_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCHANGINGCLASS_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCHANGINGCLASS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_INFOBG, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eCHANGINGCLASS_MONEYBG, 0x7A89, 170, 26, -1, -1);
	this->BindObject(eCHANGINGCLASS_DW, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_DK, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_ELF, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_MG, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_DL, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_SUM, 0x7A5E, 106, 29, -1, -1);
	this->BindObject(eCHANGINGCLASS_RF, 0x7A5E, 106, 29, -1, -1);
	//
	this->BindObject(eVIP_MAIN, 0x7A5A, 222, 303, -1, -1);/**/
	this->BindObject(eVIP_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eVIP_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eVIP_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eVIP_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eVIP_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eVIP_INFOBG, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eVIP_MONEYBG, 0x7A89, 170, 26, -1, -1);
	this->BindObject(eVIP_INFO, 0x7A5E, 128, 29, -1, -1);
	this->BindObject(eVIP_SILVER, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(eVIP_GOLD, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(eVIP_PLATINUM, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(eVIP_LEFT, 0x7C0D, 16, 15, 355, 312);
	this->BindObject(eVIP_RIGHT, 0x7AA4, 16, 15, 398, 312);
	//
	this->BindObject(eRENAME_MAIN, 0x7A5A, 222, 110, -1, -1);
	this->BindObject(eRENAME_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eRENAME_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eRENAME_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eRENAME_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eRENAME_BOX, 0x7AA3, 170, 21, 220, 140);
	this->BindObject(eRENAME_OK, 0x7A5F, 62, 27, -1, -1);
	this->BindObject(eRENAME_CLOSE, 0x7A5F, 62, 27, -1, -1);
	//
	this->BindObject(eSHOP_WC, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_WP, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_GP, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_B, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_S, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_C, 0x7E54, 52, 25, -1, -1);
	this->BindObject(eSHOP_OFF, 0x7C04, 36, 27, -1, -1);
	this->BindObject(eSHOP_CLOSE, 0x7A90, 36, 27, -1, -1);

	this->BindObject(eOFFPANEL_MAIN, 0x7A5A, 222, 120, -1, -1);
	this->BindObject(eOFFPANEL_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eOFFPANEL_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eOFFPANEL_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eOFFPANEL_YES, 0x7B12, 54, 30, -1, -1);
	this->BindObject(eOFFPANEL_CANE, 0x7B0C, 54, 30, -1, -1);
	//
	this->BindObject(eJewelsBank,0x9859, 215, 317, -1, -1);
	this->BindObject(eJewels_Des, 0x7AB5, 36, 28, -1, -1);
	this->BindObject(eJewels_Wid, 0x7AB6, 36, 28, -1, -1);
	this->BindObject(eJewels_Close, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eJewels_Bless, 32513, 55, 19, -1, -1);
	this->BindObject(eJewels_Soul, 32513, 55, 19, -1, -1);
	this->BindObject(eJewels_Chaos, 32513, 55, 19, -1, -1);
	this->BindObject(eJewels_Life, 32513, 55, 19, -1, -1);
	this->BindObject(eJewels_Creation, 32513, 55, 19, -1, -1);
	this->BindObject(eJewels_Harmony, 32513, 55, 19, -1, -1);
	this->BindObject(eJewels_Box, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eJewels_OK, 0x7A5B, 54, 30, -1, -1);
	//
	this->BindObject(eRock, 0x9323, 36, 28, -1, -1);
	this->BindObject(ePaper, 0x9324, 36, 28, -1, -1);
	this->BindObject(eScissors, 0x9325, 36, 28, -1, -1);
	this->BindObject(eRPSMODE, 0x9326, 36, 28, -1, -1);
	//
	this->BindObject(eNEWS_MAIN, 0x7A5A, 222, 303, -1, -1);
	this->BindObject(eNEWS_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eNEWS_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eNEWS_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eNEWS_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eNEWS_INFOBG, 0x7E98, 170, 21, -1, -1);
	this->BindObject(eNEWS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(eNEWS_BACK, 0x7A5E, 106, 29, -1, -1);
	//
	this->BindObject(eFruitClose, 0x7EC5, 36, 29, -1, -1);
	//
	this->BindObject(eLuckySpinRoll, 0x788E, 52, 22, -1, -1);
	this->BindObject(eLuckySpinClose, 0x7EC5, 36, 29, -1, -1);
	//
	this->BindObject(eGIFTCODE_MAIN, 0x7A5A, 222, 110, -1, -1);
	this->BindObject(eGIFTCODE_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eGIFTCODE_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eGIFTCODE_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eGIFTCODE_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eGIFTCODE_BOX, 0x7AA3, 170, 21, 220, 140);
	this->BindObject(eGIFTCODE_OK, 0x7A5F, 62, 27, -1, -1);
	this->BindObject(eGIFTCODE_CLOSE, 0x7A5F, 62, 27, -1, -1);
	//
	this->BindObject(ePARTYLEADER, 0x789A, 9, 10, 614, 41);
	this->BindObject(ePARTYLEADER2, 0x789A, 9, 10, 614, 65);
	this->BindObject(ePARTYLEADER3, 0x789A, 9, 10, 614, 89);
	this->BindObject(ePARTYLEADER4, 0x789A, 9, 10, 614, 113);
	//
	this->BindObject(ePARTYTRACE, 0x789B, 9, 10, 600, 17);
	this->BindObject(ePARTYTRACE2, 0x789B, 9, 10, 600, 41);
	this->BindObject(ePARTYTRACE3, 0x789B, 9, 10, 600, 65);
	this->BindObject(ePARTYTRACE4, 0x789B, 9, 10, 600, 89);
	this->BindObject(ePARTYTRACE5, 0x789B, 9, 10, 600, 113);
	this->BindObject(eARROW_LEFT2,0x7E59,20,22,-1,-1);
	this->BindObject(eARROW_RIGHT2,0x7E5A,20,22,-1,-1);
	this->BindObject(eEVENTTABLE_MAIN, 0x7A5A, 190, 428, -1, -1);
	this->BindObject(eEVENTTABLE_TITLE, 0x7A79, 190, 64, -1, -1);
	this->BindObject(eEVENTTABLE_LEFT, 0x7A7B, 21, 320, -1, -1);
	this->BindObject(eEVENTTABLE_RIGHT, 0x7A7C, 21, 320, -1, -1);
	this->BindObject(eEVENTTABLE_FOOTER, 0x7A7D, 190, 45, -1, -1);
	this->BindObject(eEVENTTABLE_DIV, 0x7A62, 183, 21, -1, -1);
	this->BindObject(eEVENTTABLE_CLOSE, 0x7EC5, 36, 29, -1, -1);
	//
	this->BindObject(eWAREHOUSE, 0x7E59, 20, 22, -1, -1);
	this->BindObject(eWAREHOUSE1, 0x7E5A, 20, 22, -1, -1);
	this->BindObject(eWAREHOUSE_OPEN, iGfxBtnSmall, 52, 21, -1, -1);
	//
	SetOp((LPVOID)oLoadSomeForm_Call, this->LoadImages, ASM::CALL);
	SetOp((LPVOID)oAllowGUI_Call1, this->AllowGUI, ASM::CALL);
	SetOp((LPVOID)oAllowGUI_Call2, this->AllowGUI, ASM::CALL);
	SetOp((LPVOID)oDrawInterface2_Call, this->Work2, ASM::CALL);
	SetOp((LPVOID)oDrawInterface_Call, this->Work, ASM::CALL);
	SetRange((LPVOID)0x005E496C,13,ASM::NOP);
	SetOp((LPVOID)0x005E496C,(LPVOID)AddSomeShine,ASM::JMP);
	//-
	//SetRange((LPVOID)0x00954148, 0x5, ASM::NOP);
	//SetOp((LPVOID)0x00954148, (LPVOID)ChangeServerName, ASM::JMP);
	if(gConfig.m_LoginTheme == 1)
	{
		SetOp((LPVOID)0x004D7D13, this->DrawCSServer, ASM::CALL);
	}

	//-> exp 0x00810700
	this->item_post_ = nullptr;
	if(strcmp(gLicenseInfo.RFbt,"1") == 0 || strcmp(gLicenseInfo.RFbt,"2") == 0)
	{
		SetOp((LPVOID)0x0080F865, (LPVOID)sub_810700, ASM::CALL);
	}

	//SetRange((LPVOID)0x00598C7D, 29, ASM::NOP);
	//SetOp((LPVOID)0x00598C7D, (LPVOID)StaffNameColor, ASM::JMP);
	this->DiceType = 1;
	this->DiceNumber = 3;
	this->DiceMoney	= 300;
	this->LastGame2 = 0;
	this->TitleCode = 1;
	this->HeadsTailsMoney = 300;
	this->HeadsTailsType = 1;
	this->LuckyLines	= 1;
	SetCompleteHook(0xFF, 0x004D5EE6, &this->SelectChar);
	gNewInterface.Load();
	this->m_CharacterPage = 1;
	this->VipType = 1;
	this->VipTime = 1;
}


int Interface::LoadImg(char * Folder,DWORD ID)
{
	return pLoadImage(Folder,ID,GL_LINEAR, GL_CLAMP, 1, 0);
}

void Interface::LoadImages()
{
	
	gSmithy.LoadImg();
	gRanking.ImageLoad();
	gInterface.LoadImg("Effect\\flare01.jpg", 52002);
	gInterface.LoadImg("Effect\\JointLaser01.jpg", 52224);
	gInterface.LoadImg("Effect\\hikorora.jpg", 52379);
	gInterface.LoadImg("Effect\\flareBlue.jpg", 52229);
	gInterface.LoadImg("Effect\\shiny06.jpg", 32587);
	gInterface.LoadImg("Effect\\bostar3_R.jpg", 32614);
	gInterface.LoadImg("Custom\\Interface\\UsersPanel_BG.tga", 0x787A);
	gInterface.LoadImg("Custom\\Interface\\UsersPanel.tga", 0x788C);
	gInterface.LoadImg("Custom\\Interface\\Portal.tga", 0x789B);
	gInterface.LoadImg("Custom\\Interface\\jewelbank_main.tga", 0x9859);
	gInterface.LoadImg("Custom\\Interface\\pm_flag.tga", 0x789A);
	gInterface.LoadImg("Logo\\SelectServer1.jpg", iBg1);
	gInterface.LoadImg("Logo\\SelectServer2.jpg", iBg2);
	gInterface.LoadImg("Logo\\SelectServer3.jpg", iBg3);
	gInterface.LoadImg("Logo\\SelectServer4.jpg", iBg4);
	gInterface.LoadImg("Logo\\SelectServer5.jpg", iBg5);
	gInterface.LoadImg("Logo\\SelectServer6.jpg", iBg6);
	gInterface.LoadImg("Logo\\SelectServer7.jpg", iBg7);
	gInterface.LoadImg("Logo\\SelectServer8.jpg", iBg8);

	gInterface.LoadImg("Item\\Newdeath01.tga", iCapeDeath1);
	gInterface.LoadImg("Item\\Newdeath02.tga", iCapeDeath2);
	gInterface.LoadImg("Item\\darklordwing4dd.tga", iCapeLvl4DL);
	gInterface.LoadImg("Item\\darklordwing4de.tga", iCapeLvl4DL2);
	gInterface.LoadImg("Item\\ragefighterwing4db.tga", iCapeLvl4RF);

	gInterface.LoadImg("Custom\\RolltheDice\\rolldice_main.jpg", iRollMain);
	gInterface.LoadImg("Custom\\RolltheDice\\button_up.jpg", iRollUp);
	gInterface.LoadImg("Custom\\RolltheDice\\button_down.jpg", iRollDown);
	gInterface.LoadImg("Custom\\RolltheDice\\button_over.jpg", iRollOver);
	gInterface.LoadImg("Custom\\RolltheDice\\button_under.jpg", iRollUnder);
	gInterface.LoadImg("Custom\\RolltheDice\\button_roll.jpg", iRollStart);
	gInterface.LoadImg("Custom\\RolltheDice\\button_a.jpg", iRollButton);
	gInterface.LoadImg("Custom\\RolltheDice\\number_1.tga", iRollNum1);
	gInterface.LoadImg("Custom\\RolltheDice\\number_2.tga", iRollNum2);
	gInterface.LoadImg("Custom\\RolltheDice\\number_3.tga", iRollNum3);
	gInterface.LoadImg("Custom\\RolltheDice\\number_4.tga", iRollNum4);
	gInterface.LoadImg("Custom\\RolltheDice\\number_5.tga", iRollNum5);
	gInterface.LoadImg("Custom\\RolltheDice\\number_6.tga", iRollNum6);
	//
	gInterface.LoadImg("Custom\\TitleSystem\\title_main.jpg", 39201);
	gInterface.LoadImg("Custom\\TitleSystem\\title_button.tga", 39202);
	gInterface.LoadImg("Custom\\TitleSystem\\click_left.tga", 39203);
	gInterface.LoadImg("Custom\\TitleSystem\\click_right.tga", 39204);
	gInterface.LoadImg("Custom\\TitleSystem\\button.tga", 39205);
	//
	
	gInterface.LoadImg("Custom\\HeadsTails\\bg_main.jpg", 0x9690);
	gInterface.LoadImg("Custom\\HeadsTails\\Heads.tga", 0x9691);
	gInterface.LoadImg("Custom\\HeadsTails\\Heads2.tga", 0x9692);
	gInterface.LoadImg("Custom\\HeadsTails\\Tails.tga", 0x9693);
	gInterface.LoadImg("Custom\\HeadsTails\\Tails2.tga", 0x9694);
	//
	gInterface.LoadImg("Custom\\Interface\\PartySearch_Title.tga", 0x7E98);
	gInterface.LoadImg("Custom\\Interface\\Info_Block.tga", 0x7E99);
	gInterface.LoadImg("Custom\\Interface\\Button.tga", 32513);
	//
	gInterface.LoadImg("Custom\\LuckyNumber\\bg_main.jpg", 0x9670);
	//
	gInterface.LoadImg("Custom\\Interface\\Newui_dialog_btn.tga", iGfxBtn);
	gInterface.LoadImg("Custom\\Interface\\ui-dialog1_hr.tga", iNewuiDialogHr);
	gInterface.LoadImg("Custom\\Interface\\ui_dialog_e.tga", iGfxDialoge);
	gInterface.LoadImg("Custom\\Interface\\Newui_dialog_btn_small.tga", iGfxBtnSmall);
	gInterface.LoadImg("Custom\\Interface\\Newui_dialog_btn_small2.tga", iGfxBtnSmall2);
	
	//
	gInterface.LoadImg("Custom\\Interface\\Title.tga", 0x9205);
	gInterface.LoadImg("Custom\\Interface\\newui_cha_textbox01.tga", 0x9206);

	if(strcmp(gLicenseInfo.RFbt,"2") == 0)
	{	
	gInterface.LoadImg("Custom\\interfaces2\\2Menu01_new.jpg", 31292); //replace
	gInterface.LoadImg("Custom\\interfaces2\\2Menu02.jpg", 31293); //replace
	gInterface.LoadImg("Custom\\interfaces2\\2Menu03_new.jpg", 31294); //replace
	gInterface.LoadImg("Custom\\interfaces2\\none.tga", 31295); //replace
	gInterface.LoadImg("Custom\\interfaces2\\2Menu_Red.jpg", 0x7A42);//replace
	gInterface.LoadImg("Custom\\interfaces2\\2Menu_Green.jpg", 0x7A41);//replace
	gInterface.LoadImg("Custom\\interfaces2\\2Menu_Blue.jpg", 0x7A40);//replace
	gInterface.LoadImg("Custom\\interfaces2\\2Menu04.tga", iDragonLeft);
	gInterface.LoadImg("Custom\\interfaces2\\2Menu05.tga", iDragonRight);
	gInterface.LoadImg("Custom\\interfaces2\\2Menu_Inventory.jpg", iNewInventory);
	gInterface.LoadImg("Custom\\interfaces2\\2Menu_Character.jpg", iNewCharacter);
	gInterface.LoadImg("Custom\\interfaces2\\2Menu_Party.jpg", iNewParty);
	gInterface.LoadImg("Custom\\interfaces2\\2win_push.jpg", iNewWinpush);
	gInterface.LoadImg("Custom\\interfaces2\\2menu01_new2.jpg", iNewFastMenu);
	gInterface.LoadImg("Custom\\interfaces2\\2SkillBox.jpg", iNewSkillBox);
	}

	if(strcmp(gLicenseInfo.RFbt,"1") == 0)
	{	
	gInterface.LoadImg("Custom\\interfaces1\\1Menu01_new.jpg", 31292); //replace
	gInterface.LoadImg("Custom\\interfaces1\\2Menu02.jpg", 31293); //replace
	gInterface.LoadImg("Custom\\interfaces1\\1Menu03_new.jpg", 31294); //replace
	gInterface.LoadImg("Custom\\interfaces1\\none.tga", 31295); //replace
	gInterface.LoadImg("Custom\\interfaces1\\2Menu_Red.jpg", 0x7A42);//replace
	gInterface.LoadImg("Custom\\interfaces1\\2Menu_Green.jpg", 0x7A41);//replace
	gInterface.LoadImg("Custom\\interfaces1\\2Menu_Blue.jpg", 0x7A40);//replace
	gInterface.LoadImg("Custom\\interfaces1\\2Menu04.tga", iDragonLeft);
	gInterface.LoadImg("Custom\\interfaces1\\2Menu05.tga", iDragonRight);
	gInterface.LoadImg("Custom\\interfaces1\\2Menu_Inventory.jpg", iNewInventory);
	gInterface.LoadImg("Custom\\interfaces1\\2Menu_Character.jpg", iNewCharacter);
	gInterface.LoadImg("Custom\\interfaces1\\2Menu_Party.jpg", iNewParty);
	gInterface.LoadImg("Custom\\interfaces1\\2win_push.jpg", iNewWinpush);
	gInterface.LoadImg("Custom\\interfaces1\\2menu01_new2.jpg", iNewFastMenu);
	gInterface.LoadImg("Custom\\interfaces1\\2SkillBox.jpg", iNewSkillBox);
	gInterface.LoadImg("Custom\\interfaces1\\2win_pk.jpg", 0x9A52);
	}
	
	//MiniMap
	gInterface.LoadImg("Custom\\MiniMap\\PlayerPoint.jpg", 0x9180);
	gInterface.LoadImg("Custom\\MiniMap\\null.tga", 0x9181);
	gInterface.LoadImg("Custom\\MiniMap\\navimap01.tga", 0x9182); //00_Lorencia
	gInterface.LoadImg("Custom\\MiniMap\\navimap02.tga", 0x9183); //01_Dungeon
	gInterface.LoadImg("Custom\\MiniMap\\navimap03.tga", 0x9184); //02_Devias
	gInterface.LoadImg("Custom\\MiniMap\\navimap04.tga", 0x9185); //03_Noria
	gInterface.LoadImg("Custom\\MiniMap\\navimap05.tga", 0x9186); //04_Losttower
	gInterface.LoadImg("Custom\\MiniMap\\navimap08.tga", 0x9187); //07_Atlans
	gInterface.LoadImg("Custom\\MiniMap\\navimap09.tga", 0x9188); //08_Tarkan
	gInterface.LoadImg("Custom\\MiniMap\\navimap11.tga", 0x9190); //10_Icarus
	gInterface.LoadImg("Custom\\MiniMap\\navimap25.tga", 0x9191); //24_Kalima
	gInterface.LoadImg("Custom\\MiniMap\\navimap32.tga", 0x9192); //31_LandOfTrial
	gInterface.LoadImg("Custom\\MiniMap\\navimap34.tga", 0x9193); //33_Aida
	gInterface.LoadImg("Custom\\MiniMap\\navimap35.tga", 0x9194); //34_Crywolf
	//gInterface.LoadImg("Custom\\MiniMap\\navimap37.tga", 0x9195); //36_Kalima
	gInterface.LoadImg("Custom\\MiniMap\\navimap38.tga", 0x9196); //37_Kanturu
	gInterface.LoadImg("Custom\\MiniMap\\navimap39.tga", 0x9197); //38_KanturuRemain
	gInterface.LoadImg("Custom\\MiniMap\\navimap40.tga", 0x9198); //39_KanturuBoss
	gInterface.LoadImg("Custom\\MiniMap\\navimap46.tga", 0x9199); //45_IllusionTemple
	gInterface.LoadImg("Custom\\MiniMap\\navimap52.tga", 0x9200); //51_Elbeland
	gInterface.LoadImg("Custom\\MiniMap\\navimap57.tga", 0x9201); //56_SwampOfCalmness
	gInterface.LoadImg("Custom\\MiniMap\\navimap58.tga", 0x9202); //57_Raklion
	gInterface.LoadImg("Custom\\MiniMap\\navimap64.tga", 0x9203); //63_Vulcanus
	gInterface.LoadImg("Custom\\MiniMap\\navimap80.tga", 0x9204); //79_LorenMarket
	gInterface.LoadImg("Custom\\MiniMap\\navimap81.tga", 0x9205); //80_Karutan1
	gInterface.LoadImg("Custom\\MiniMap\\navimap82.tga", 0x9206); //81_Karutan2
	gInterface.LoadImg("Custom\\MiniMap\\navimap92.tga", 0x9207); //83_Archeron
	gInterface.LoadImg("Custom\\MiniMap\\navimap96.tga", 0x9208); //84_Debenter
	gInterface.LoadImg("Custom\\MiniMap\\navimap101.tga", 0x9209); //85_UrkMontain
	gInterface.LoadImg("Custom\\MiniMap\\navimap113.tga", 0x9210); //86_Ferea
	// ----
	gInterface.LoadImg("Custom\\Interface\\event_hud.tga", 0x9696);
	//
	gInterface.LoadImg("Custom\\RPSMode\\rock.tga", 0x9323);
	gInterface.LoadImg("Custom\\RPSMode\\paper.tga", 0x9324);
	gInterface.LoadImg("Custom\\RPSMode\\scissors.tga", 0x9325);
	gInterface.LoadImg("Custom\\RPSMode\\rpsswitch.tga", 0x9326);
	// ---
	gInterface.LoadImg("Custom\\Interface\\itembackpanel.tga", 0x9327);
	
	for (int i = 0; i < MAX_RANK_TITLE; i++)
	{
		if(gCustomTitle.m_CustomTitle[i].TitleCode){
            pLoadImage (gCustomTitle.m_CustomTitle[i].ImgDir, gCustomTitle.m_CustomTitle[i].ImgCode, GL_LINEAR, GL_CLAMP, 1, 0 );
		}
    }
	pLoadSomeForm();
}

void Interface::BindObject(short MonsterID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[MonsterID].EventTick = 0;
	this->Data[MonsterID].OnClick = false;
	this->Data[MonsterID].OnShow = false;
	this->Data[MonsterID].ModelID = ModelID;
	this->Data[MonsterID].Width = Width;
	this->Data[MonsterID].Height = Height;
	this->Data[MonsterID].X = X;
	this->Data[MonsterID].Y = Y;
	this->Data[MonsterID].MaxX = X + Width;
	this->Data[MonsterID].MaxY = Y + Height;
	this->Data[MonsterID].Attribute = 0;
}
int Interface::CDrawText(int x, int y, BYTE *Color, BYTE * BgColor, int width, LPINT align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	pSetTextColor(pTextThis(), Color[0], Color[1], Color[2], Color[3]);
	pSetTextBGColor(pTextThis(), BgColor[0], BgColor[1], BgColor[2], BgColor[3]);

	return pDrawText(pTextThis(), x, y, Buff, width, 0, (LPINT)align, 0);
}

bool Interface::CheckWindow(int WindowID)
{
	return pCheckWindow(pWindowThis(), WindowID);
}

bool Interface::CheckWindowEx(int WindowID)
{
	return this->Data[WindowID].OnShow;
}

int Interface::CloseWindow(int WindowID)
{
	return pCloseWindow(pWindowThis(), WindowID);
}

int Interface::OpenWindow(int WindowID)
{
	return pOpenWindow(pWindowThis(), WindowID);
}

void Interface::OpenWindowEx(int WindowID)
{
	Data[WindowID].Open();
}

void Interface::CloseWindowEx(int WindowID)
{
	Data[WindowID].Close();
}

void Interface::SetTextColor(BYTE Red, BYTE Green, BYTE Blue, BYTE Opacity)
{
	pSetTextColor(pTextThis(), Red, Green, Blue, Opacity);
}

int Interface::DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
    char Buff[2048];
    int BuffLen = sizeof(Buff)-1;
    ZeroMemory(Buff, BuffLen);
    // ----
    va_list args;
    va_start(args, Text);
    int Len = vsprintf_s(Buff, BuffLen, Text, args);
    va_end(args);
    // ----
    int LineCount = 0;
    // ----
    char * Line = strtok(Buff, "\n");
    // ----
    while( Line != NULL )
    {
        pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
        PosY += 10;
        Line = strtok(NULL, "\n");
    }
    // ----
    return PosY;
}

int Interface::DrawMessage(int Mode, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	return pDrawMessage(Buff, Mode);
}

void Interface::DrawBarForm(float PosX,float PosY,float Width,float Height,GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	pSetBlend(1);
	glColor4f(red, green, blue, alpha);
	pDrawBarForm(PosX,PosY,Width,Height,0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
}

bool checkBtn(int obj)
{
	if (gObjUser.m_CursorX < gInterface.Data[obj].X || gObjUser.m_CursorX > gInterface.Data[obj].MaxX || 
		gObjUser.m_CursorY < gInterface.Data[obj].Y || gObjUser.m_CursorY > gInterface.Data[obj].MaxY)
	{
		//g_Console.AddMessage(5,"false!");
		return false;
	}
	return true;
}

void Interface::DrawAnimatedButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	//if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	//{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	//}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
	this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::DrawCheckLineEx(bool isChecked, int PointID, int CheckID, int LineID, float X, float Y, DWORD Color, char* Text)
{
	this->DrawAnimatedGUI(PointID, X+20 , Y-4); // Point
	this->DrawFormat(eWhite, X+50, Y+1, 200, 1, Text);

	if (isChecked)
	{
		this->DrawAnimatedButton(CheckID, X+190, Y-6, 0, 0);
	}
	else
	{
		this->DrawAnimatedButton(CheckID, X+190, Y-6, 0, 15);
	}

	this->DrawAnimatedGUI(LineID, X+33, Y+10);
}

bool Interface::ButtonEx(DWORD Event, int ButtonID, bool Type)
{
	//g_Console.AddMessage(5,"ENTER");
	//if( !this->IsWorkZone(ButtonID) )
	//g_Console.AddMessage(5,"%f - %f | %f - %f", this->Data[ButtonID].X, this->Data[ButtonID].MaxX,this->Data[ButtonID].Y, this->Data[ButtonID].MaxY );
	//if (!this->IsWorkZone(this->Data[ButtonID].X, this->Data[ButtonID].MaxX,this->Data[ButtonID].Y, this->Data[ButtonID].MaxY))
	if (!checkBtn(ButtonID))
	{
		//g_Console.AddMessage(3,"return because its shit");
		return false;
	}

	if( Type == true )
	{
		if( !this->Data[ButtonID].Attribute )
		{
			//g_Console.AddMessage(3,"return2");
			return false;
		}
	}

	// ----
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[ButtonID].EventTick);
	// ----

	if( Event == WM_LBUTTONDOWN  && this->Data[ButtonID].OnClick == false)
	{
		this->Data[ButtonID].OnClick = true;
		//return true;
	}
	if (Event != WM_LBUTTONUP)
	{
		return false;
	}
	/*if(Event == WM_LBUTTONUP && this->Data[ButtonID].OnClick == true)
	{
		this->Data[ButtonID].OnClick = false;
		return true;
	}*/
	// ----
	if( Delay < 500 )
	{
		//g_Console.AddMessage(3,"return3");
		return false;
	}
	// ----
	this->Data[ButtonID].OnClick = false;
	// ----
	this->Data[ButtonID].EventTick = GetTickCount();
	// ----
	//g_Console.AddMessage(3,"return successfully");
	return true;
}

void Interface::TextDraw(int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...)
{
	char TextBuff[1024] = {0};
	va_list va;
	va_start(va, Format);
	vsprintf_s(TextBuff, Format, va);
	va_end(va);

	int v13; // ST1C_4@1
	int v15; // ST20_4@1
	pSetFont(pTextThis(), (int)Font);
	v13 = sub_41FFE0_Addr(pTextThis());
	v15 = sub_420010_Addr(pTextThis());
	SetTextColorByHDC(pTextThis(), Color);
	sub_4200F0_Addr(pTextThis(), Arg7);
	pSetBkColor(pTextThis(),255,255,255,0);
	pDrawText(pTextThis(), PosX, PosY, TextBuff, Width, Arg5, (int*)Align, 0);
	SetTextColorByHDC(pTextThis(), v13);
	sub_4200F0_Addr(pTextThis(), v15);
}


void Interface::PartUPandDNEx(int PointID, int UpID, int DownID, int LineID, float X, float Y, DWORD Color, int Value, char* Text)
{
	this->DrawAnimatedGUI(PointID, X+20 , Y-4); // Point

	this->DrawFormat(eWhite, X+50, Y+1, 200, 1, Text);

	this->DrawAnimatedButton(DownID, X+150, Y-6, 0, 0); // 

	if(checkBtn(DownID) )
	{
		//g_Console.AddMessage(3," %d ", this->Data[DownID].OnClick);
		if( this->Data[DownID].OnClick )
		{
			//g_Console.AddMessage(3,"CLICK!");
			this->DrawAnimatedButton(DownID, X+150, Y-6, 0, 16);
		}
	}

	//this->DrawToolTip(X+x, Y+y, "%d", Value);
	pSetBlend(true);
	this->DrawBarForm(X+168, Y-5,19,13,0.0,0.0,0.0,1.0);//ReqItems
	glColor3f(1,1,1);
	pSetBlend(false);
	char szText[10];
	sprintf(szText,"%d",Value);
	gInterface.TextDraw(X+128, Y-2, 100, 1, eWhite, 0, 3,pFontNormal,"%d",Value);
	//TestDrawText(szText, X+128, Y-2, 100, 1, eWhite, 0, 3,pFontNormal);
	//this->DrawBarForm(X+x, Y+y,w,h,0.04,0.34,0.0,1.0);//ReqItems

	this->DrawAnimatedButton(UpID, X+190, Y-6, 0, 0); // 

	if(checkBtn(UpID) )
	{
		//g_Console.AddMessage(3," %d ", this->Data[UpID].OnClick);
		if( this->Data[UpID].OnClick )
		{
			//g_Console.AddMessage(3,"CLICK!");
			this->DrawAnimatedButton(UpID, X+190, Y-6, 0, 16);
		}
	}


	/*
	 
	this->DrawToolTip(StartX + 174, this->Data[ePARTYSETTINGS_MAIN].Y + 62, "%d", gPartySearchSettings.m_Level);

	if (gPartySearchSettings.m_SystemActive == 0)
	{
		this->DrawColoredButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0, eGray150); // 
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0); // 

		if(this->IsWorkZone(ePARTYSETTINGS_LEVEL_MINUS) )
		{
			if( this->Data[ePARTYSETTINGS_LEVEL_MINUS].OnClick )
			{
				this->DrawButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 16);
			}
		}
	}

	if (gPartySearchSettings.m_SystemActive == 0)
	{
		this->DrawColoredButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0, eGray150); //
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0); //

		if(this->IsWorkZone(ePARTYSETTINGS_LEVEL_PLUS) )
		{
			if( this->Data[ePARTYSETTINGS_LEVEL_PLUS].OnClick )
			{
				this->DrawButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 16);
			}
		}
	} 

	 */

	this->DrawGUI(LineID, X+33, Y+10);
}

void Interface::MiniButtonDraw(int BtnID, float X, float Y, bool isHover, char* Text)
{
	//int x = GetPrivateProfileIntA("Custom", "X", -35, "./Settings.ini");
	//int y = GetPrivateProfileIntA("Custom", "Y", 60, "./Settings.ini");

	if (isHover)
	{
		this->DrawAnimatedButton(BtnID, X, Y, 0, 29);
	}
	else
	{
		this->DrawAnimatedButton(BtnID, X, Y, 0, 0);
	}
	this->DrawFormat(eWhite, X+7, Y+9, 50, 3, Text);
	//this->DrawGUI(LineID, X+33, Y+10);
}

float Interface::DrawRepeatGUI(short MonsterID, float X, float Y, int Count)
{
	float StartY = Y;

	for (int i = 0; i < Count; i++)
	{
		pDrawGUI(this->Data[MonsterID].ModelID, X, StartY, this->Data[MonsterID].Width, this->Data[MonsterID].Height);

		StartY += this->Data[MonsterID].Height;
	}

	return StartY;
}

float Interface::DrawRepeatGUIX(short MonsterID, float X, float Y, int Count)
{
	float StartX = X;

	for (int i = 0; i < Count; i++)
	{
		pDrawGUI(this->Data[MonsterID].ModelID, StartX, Y, this->Data[MonsterID].Width, this->Data[MonsterID].Height);

		StartX += this->Data[MonsterID].Width;
	}

	return StartX;
}

void Interface::DrawGUI(short ObjectID, float PosX, float PosY)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY, this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY, this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::DrawImage(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawImage(this->Data[ObjectID].ModelID, PosX, PosY, this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, ScaleX, ScaleY, 1, 1, 0);
}

void Interface::DrawImage10(short ObjectID, float PosX, float PosY)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawImage(this->Data[ObjectID].ModelID, PosX, PosY, this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, 1.0f, 1.0f, 1, 1, 0);
}

void Interface::DrawMessageBox(LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	CharTest v15;

	LPCSTR pText = Buff;
    sub_409A50_addr(&v15, (int)pText);
	pOpenInfoBox(&v15,-1);
    sub_409AD0_Addr((LPVOID)&v15);
}

bool Interface::CursorZoneButton(float X, float Y, float MaxX, float MaxY)
{
	if( (pCursorX < X || pCursorX > MaxX) || (pCursorY < Y || pCursorY > MaxY) )
	{
		return false;
	}
	// ----
	return true;
}

// ----------------------------------------------------------------------------------------------

void Interface::DrawFormatEx(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen	= sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len	= vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	pDrawColorText(Buff, PosX, PosY, Width, 0, Color, 0, Align);
}
// ----------------------------------------------------------------------------------------------

int Interface::DrawFormat_Ex(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff)-1;
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	int LineCount = 0;
	// ----
	char * Line = strtok(Buff, "/");
	// ----
	while( Line != NULL )
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "/");
	}
	// ----
	return PosY;
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawAnimatedGUI(short ObjectID, float PosX, float PosY)
{
	this->Data[ObjectID].X		= PosX;
	this->Data[ObjectID].Y		= PosY;
	this->Data[ObjectID].MaxX	= PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY	= PosY + this->Data[ObjectID].Height;
	// ----
	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = X;
		this->Data[ObjectID].Y = Y;
		this->Data[ObjectID].MaxX = X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = Y + this->Data[ObjectID].Height;
	}

	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y, this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawColoredAnimatedGUI(short ObjectID, float X, float Y, DWORD Color)
{
	//if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	//{
		this->Data[ObjectID].X		= X;
		this->Data[ObjectID].Y		= Y;
		this->Data[ObjectID].MaxX	= X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY	= Y + this->Data[ObjectID].Height;
	//}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y, 
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}
// ----------------------------------------------------------------------------------------------


int Interface::DrawToolTip(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff);
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	return pDrawToolTip(X, Y, Buff);
}


/*
bool Interface::IsWorkZone(short ObjectID)
{
	float PosX = this->Data[ObjectID].X;
	float MaxX = PosX + this->Data[ObjectID].Width;

	if (pWinWidth == 800)
	{
		if (((float)pCursorX - 16.0 < PosX || (float)pCursorX - 16.0 > MaxX) || ((float)pCursorY < this->Data[ObjectID].Y || (float)pCursorY > this->Data[ObjectID].MaxY))
			return false;
	}
	else if (pWinWidth != 1024)
	{
		if (((float)pCursorX + 16.0 < PosX || (float)pCursorX + 16.0 > MaxX) || ((float)pCursorY < this->Data[ObjectID].Y || (float)pCursorY > this->Data[ObjectID].MaxY))
			return false;
	}
	else
	{
		if (((float)pCursorX< PosX || (float)pCursorX > MaxX) || ((float)pCursorY < this->Data[ObjectID].Y || (float)pCursorY > this->Data[ObjectID].MaxY))
			return false;
	}
	return true;
}
*/
bool Interface::IsWorkZone2(short ObjectID)
{
	float PosX = this->Data[ObjectID].X;
	float MaxX = PosX + this->Data[ObjectID].Width;
	if( ObjectID == eUSERSPANELBG || ObjectID == eUSERSPANEL_BUTTON)
	{
		PosX = this->GetResizeX(ObjectID);
		MaxX = PosX + this->Data[ObjectID].Width;
	}
	if (((float)pCursorX < PosX || (float)pCursorX > MaxX) || ((float)pCursorY < this->Data[ObjectID].Y || (float)pCursorY > this->Data[ObjectID].MaxY))
	{
		return false;
	}

	return true;
}

bool Interface::IsWorkZone(float X, float Y, float MaxX, float MaxY)
{
	if (((float)pCursorX < X || (float)pCursorX > MaxX) || ((float)pCursorY < Y || (float)pCursorY > MaxY))
	{
		return false;
	}
	return true;
}

float Interface::GetResizeX(short ObjectID)
{
	if (pWinWidth == 800)
	{
		return this->Data[ObjectID].X + 16.0f;
	}
	else if (pWinWidth != 1024)
	{
		return this->Data[ObjectID].X - 16.0f;
	}

	return this->Data[ObjectID].X;
}

int Interface::DrawToolTipEx(DWORD Color, int PosX, int PosY, int Width, int Height, int Align, LPCSTR Text, ...)
{
    char Buff[2048];
    char Buff2[2048];
    int BuffLen = sizeof(Buff);
    ZeroMemory(Buff, BuffLen);
    // ----
    va_list args;
    va_start(args, Text);
    int Len = vsprintf_s(Buff, BuffLen, Text, args);
    va_end(args);
    // ----
 
    int LineCount = 0;
 
    strcpy(Buff2,Buff);
 
    char * Line = strtok(Buff2, "\n");
    // ----
    while( Line != NULL )
    {
        LineCount++;
        Line = strtok(NULL, "\n");
    }
 
    pSetBlend(1);
    glColor4f(0.0, 0.0, 0.0, 1.0);
    pDrawBarForm(PosX, PosY, Width, LineCount*10, 0.0f, 0);
    pGLSwitchBlend();
    pGLSwitch();
 
    glColor3f(1.0, 1.0, 1.0);
 
    this->DrawFormat(eWhite, PosX, PosY, Width, Align, Buff);
    return 0;
}
 
void Interface::DrawColoredButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY, DWORD Color)
{
    if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
    {
        this->Data[ObjectID].X = PosX;
        this->Data[ObjectID].Y = PosY;
        this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
        this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
    }
    // ----
    pDrawColorButton(this->Data[ObjectID].ModelID, PosX, PosY,
    this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY, Color);
}

bool Interface::MiniMapCheck()
{
	if (this->CheckWindow(Inventory) ||
		this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(Character) ||
		this->CheckWindow(CommandWindow) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(GensInfo) ||
		this->CheckWindow(Guild) ||
		this->CheckWindow(NPC_Dialog) ||
		this->CheckWindow(NPC_Julia) ||
		this->CheckWindow(NPC_Titus_PK) ||
		this->CheckWindow(OtherStore) ||
		this->CheckWindow(Party) ||
		this->CheckWindow(PetInfo) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Store) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(FriendList) ||
		this->CheckWindow(FastMenu) ||
		this->CheckWindow(MuHelper) ||
		this->CheckWindow(Quest) ||
		this->CheckWindow(Warehouse) ||
		this->CheckWindow(ChatWindow))
		return true;
	return false;
}

bool Interface::CombinedChecks()
{
	if ((this->CheckWindow(Inventory)
		&& this->CheckWindow(ExpandInventory)
		&& this->CheckWindow(Store)) ||
		(this->CheckWindow(Inventory)
			&& this->CheckWindow(Warehouse)
			&& this->CheckWindow(ExpandWarehouse)) ||
			(this->CheckWindow(Inventory)
				&& this->CheckWindow(Character)
				&& this->CheckWindow(Store)))
		return true;
	return false;
}

void Interface::DrawS2Interface()
{
	gInterface.DrawGUI(eSkillBox, 305, 443);
	DWORD X = *(DWORD*)(oUserPreviewStruct + 172);
	DWORD Y = *(DWORD*)(oUserPreviewStruct + 176);
	pDrawInterfaceNumBer(23, 460, X, 0.9f);
	pDrawInterfaceNumBer(44, 460, Y, 0.9f);
	/*
	time_t TimeLocal;
	struct tm * LocalT;
	time(&TimeLocal);
    // ----
	LocalT = localtime(&TimeLocal);
    // ----
    char ServerTime[30];
    sprintf ( ServerTime, "%2d:%02d:%02d", LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec);
	Font[TAHOMA_BOLD_14]->DrawText(15, 460, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, ServerTime);
	*/
}

void Interface::DrawDragonLeft()
{

	if (this->CheckWindow(ChatWindow)
		|| this->CheckWindow(CashShop)
		|| this->CheckWindow(FullMap)
		|| this->CheckWindow(SkillTree))
	{
		return;
	}
	gInterface.DrawGUI(eDragonLeft, 0, 387);

}

void Interface::DrawDragonRight()
{
	if (this->CheckWindow(Inventory) || this->CheckWindow(FriendList)
		|| this->CheckWindow(FastMenu) || this->CheckWindow(CashShop)
		|| this->CheckWindow(MuHelper) || this->CheckWindow(NPC_Titus_PK)
		|| this->CheckWindow(FullMap) || this->CheckWindow(GuildMaster)
		|| this->CheckWindow(Guild) || this->CheckWindow(Character)
		|| this->CheckWindow(Party) || this->CheckWindow(Quest)
		|| this->CheckWindow(GensInfo) || this->CheckWindow(NPC_Julia)
		|| this->CheckWindow(CommandWindow) || this->CheckWindow(Shop)
		|| this->CheckWindow(SkillTree)
		|| pMapNumber == Collosseum || pMapNumber == BloodCastle8
		|| pMapNumber == ChaosCastle7 || pMapNumber == DevilSquare6
		|| pMapNumber == Loren || pMapNumber == DevilSquare
		|| this->showMiniMap == true
		)
	{
		return;
	}
	gInterface.DrawGUI(eDragonRight, 532, 387);

}

void Interface::DrawMenuButton()
{
	if (IsWorkZone2(eParty))
	{
		this->DrawToolTip(345, 435, gCustomMessage.GetMessage(28));
	}
	if (this->CheckWindow(Party))
	{
		gInterface.DrawGUI(eParty, 348, 449);
	}
	if (IsWorkZone2(eCharacter))
	{
		this->DrawToolTip(375, 435, gCustomMessage.GetMessage(26));
	}
	if (this->CheckWindow(Character))
	{
		gInterface.DrawGUI(eCharacter, 378.5f, 449);
	}
	if (IsWorkZone2(eInventory))
	{
		this->DrawToolTip(405, 435, gCustomMessage.GetMessage(27));
	}
	if (this->CheckWindow(Inventory))
	{
		gInterface.DrawGUI(eInventory, 409, 449);
	}
	if (IsWorkZone2(eFriend))
	{
		this->DrawToolTip(580, 420, gCustomMessage.GetMessage(29));
	}
	
	if (this->CheckWindow(FriendList))
	{
		gInterface.DrawGUI(eFriend, 581, 432);
	}
	
	if (IsWorkZone2(eFastMenu))
	{
		this->DrawToolTip(13, 420, gCustomMessage.GetMessage(25));
	}
	if (this->CheckWindow(FastMenu))
	{
		gInterface.DrawGUI(eFastMenu, 5, 432);
	}

}
void Interface::DrawMenuButton1()
{
	if (IsWorkZone2(eParty))
	{
		this->DrawToolTip(345, 435, gCustomMessage.GetMessage(28));
	}
	if (this->CheckWindow(Party))
	{
		gInterface.DrawGUI(eParty, 348, 449);
	}
	if (IsWorkZone2(eCharacter))
	{
		this->DrawToolTip(375, 435, gCustomMessage.GetMessage(26));
	}
	if (this->CheckWindow(Character))
	{
		gInterface.DrawGUI(eCharacter, 378.5f, 449);
	}
	if (IsWorkZone2(eInventory))
	{
		this->DrawToolTip(405, 435, gCustomMessage.GetMessage(27));
	}
	if (this->CheckWindow(Inventory))
	{
		gInterface.DrawGUI(eInventory, 409, 449);
	}
	if(IsWorkZone2(ePkMenu))
	{
		this->DrawToolTip(581, 440, "Guild (G)");
	}
	if(this->CheckWindow(Guild))
	{
		gInterface.DrawGUI(ePkMenu,581,456);
	}

}
void Interface::EventMenuButton(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if (this->CheckWindow(ChaosBox))
	{
		return;
	}

	if (IsWorkZone2(eParty))
	{
		DWORD Delay = (CurrentTick - this->Data[eParty].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eParty].OnClick = true;
			return;
		}
		this->Data[eParty].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eParty].EventTick = GetTickCount();
		if (this->CheckWindow(Party)) {
			this->CloseWindow(Party);
		}
		else {
			this->OpenWindow(Party);
		}
	}
	else if (IsWorkZone2(eCharacter))
	{
		DWORD Delay = (CurrentTick - this->Data[eCharacter].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eCharacter].OnClick = true;
			return;
		}
		this->Data[eCharacter].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eCharacter].EventTick = GetTickCount();
		if (this->CheckWindow(Character)) {
			this->CloseWindow(Character);
		}
		else {
			this->OpenWindow(Character);
		}
	}
	else if (IsWorkZone2(eInventory))
	{
		DWORD Delay = (CurrentTick - this->Data[eInventory].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eInventory].OnClick = true;
			return;
		}
		this->Data[eInventory].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eInventory].EventTick = GetTickCount();
		if (this->CheckWindow(Inventory)) {
			this->CloseWindow(Inventory);
		}
		else {
			this->OpenWindow(Inventory);
		}
	}

	else if (IsWorkZone2(eFriend))
	{
		DWORD Delay = (CurrentTick - this->Data[eFriend].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eFriend].OnClick = true;
			return;
		}
		this->Data[eFriend].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eFriend].EventTick = GetTickCount();
		if (this->CheckWindow(FriendList)) {
			this->CloseWindow(FriendList);
		}
		else {
			this->OpenWindow(FriendList);
		}
	}

	else if (IsWorkZone2(eFastMenu))
	{
		DWORD Delay = (CurrentTick - this->Data[eFastMenu].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eFastMenu].OnClick = true;
			return;
		}
		this->Data[eFastMenu].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eFastMenu].EventTick = GetTickCount();
		if (this->CheckWindow(FastMenu)) {
			this->CloseWindow(FastMenu);
		}
		else {
			this->OpenWindow(FastMenu);
		}
	}
}

void Interface::EventMenuButton1(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if (this->CheckWindow(ChaosBox))
	{
		return;
	}

	if (IsWorkZone2(eParty))
	{
		DWORD Delay = (CurrentTick - this->Data[eParty].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eParty].OnClick = true;
			return;
		}
		this->Data[eParty].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eParty].EventTick = GetTickCount();
		if (this->CheckWindow(Party)) {
			this->CloseWindow(Party);
		}
		else {
			this->OpenWindow(Party);
		}
	}
	else if (IsWorkZone2(eCharacter))
	{
		DWORD Delay = (CurrentTick - this->Data[eCharacter].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eCharacter].OnClick = true;
			return;
		}
		this->Data[eCharacter].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eCharacter].EventTick = GetTickCount();
		if (this->CheckWindow(Character)) {
			this->CloseWindow(Character);
		}
		else {
			this->OpenWindow(Character);
		}
	}
	else if (IsWorkZone2(eInventory))
	{
		DWORD Delay = (CurrentTick - this->Data[eInventory].EventTick);
		if (Event == WM_LBUTTONDOWN) {
			this->Data[eInventory].OnClick = true;
			return;
		}
		this->Data[eInventory].OnClick = false;
		if (Delay < 500) {
			return;
		}
		this->Data[eInventory].EventTick = GetTickCount();
		if (this->CheckWindow(Inventory)) {
			this->CloseWindow(Inventory);
		}
		else {
			this->OpenWindow(Inventory);
		}
	}
	else if (IsWorkZone2(ePkMenu))
	{
		DWORD Delay = (CurrentTick - this->Data[ePkMenu].EventTick);
		if (Event == WM_LBUTTONDOWN){
			this->Data[ePkMenu].OnClick = true;
			return;
		}
		this->Data[ePkMenu].OnClick = false;
		if (Delay < 500){
			return;
		}
		this->Data[ePkMenu].EventTick = GetTickCount();
		if(this->CheckWindow(Guild)){
		this->CloseWindow(Guild);
		}
		else{
			this->OpenWindow(Guild);
		}
	}
}

void Interface::DrawAutoInfo()
{
	if(!this->ShowAutoInfo)
	{
		return;
	}
	pSetTextBGColor(pTextThis(), 0xFF, 0, 0, 0x64);
	//pSetTextColor(pTextThis(), 0xFF, 0x69, 0x19, 0xFF);
	pSetTextColor(pTextThis(), 0xFF, 0xFF, 0xFF, 0xFF);
	pDrawText(pTextThis(), 150,109, gCustomMessage.GetMessage(54), 0, 0, (LPINT)1, 0);

	pSetTextBGColor(pTextThis(), 0, 0, 0, 0);
	pSetTextColor(pTextThis(), 0x0, 0xFF, 0x8B, 0xFF);
	pDrawText(pTextThis(), 150,120, gCustomMessage.GetMessage(55), 0, 0, (LPINT)1, 0);

	pSetTextColor(pTextThis(), 0x0, 0xFF, 0x8B, 0xFF);
	pDrawText(pTextThis(), 150,131, gCustomMessage.GetMessage(56), 0, 0, (LPINT)1, 0);

	pSetTextColor(pTextThis(), 0x0, 0xFF, 0x8B, 0xFF);
	pDrawText(pTextThis(), 150,142, gCustomMessage.GetMessage(57), 0, 0, (LPINT)1, 0);

}

bool Interface::AllowGUI()
{
	/*
	if (gInterface.CheckUserPanel() && gInterface.CheckRolltheDiceWindow())
	{
		return false;
	}
	*/
	return pAllowGUI();
	
}

bool MainWorkZone(int a1, int a2, int a3, int a4)
{
	if (pCursorX >= a1 && pCursorX < a3 + a1 && pCursorY >= a2 && pCursorY < a4 + a2)
		return true;
	return false;
}

void Interface::DrawExpBar()
{
	if (*(DWORD*)MAIN_SCREEN_STATE == 5)
	{
		double ExpNum;
		glColor3f(1.0f, 1.0f, 0.1f);
		pDrawBarForm(221, 436, 1, 5.0f, 0.0f, 0);
		char buff[255];

		DWORD ReadExp = *(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x10);
		DWORD ReadNextExp = *(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x14);


		lpCharObj lpPlayer = &*(ObjectCharacter*)*(DWORD*)MAIN_CHARACTER_STRUCT;

		QWORD CurrentMasterExp;
		QWORD NextMasterExp;
		if (lpPlayer->Level >= 400)
		{
			//Level = *(WORD*)0x87935D8;
			NextMasterExp = *(QWORD*)0x87935E8;
			CurrentMasterExp = *(QWORD*)0x87935E0;
		}
	

		if (lpPlayer->Level >= 400)
		{
			if (NextMasterExp > 0 && CurrentMasterExp > 0)
			{
				double Exp = ((CurrentMasterExp * 100) / (NextMasterExp + (NextMasterExp - CurrentMasterExp))) % 10;
				ExpNum = Exp;
				Exp = Exp * 20;
				Exp = ((Exp > 199) ? 199 : Exp);
				//glColor4f(0.2, 1.0, 0.2, 1.0);
				pDrawBarForm(221, 436, (float)Exp, 5.0, 0.0f, 0);
				glColor4f(1.0, 1.0, 1.0, 0.24f);
				double ExpForm = Exp + 10;
				ExpForm = ((ExpForm > 200) ? 200 : ExpForm);
				pDrawBarForm(221, 436, (float)ExpForm, 5.0, 0.0, 0);
				ExpNum = ((ExpNum > 9) ? 9 : ExpNum);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glEnable(GL_TEXTURE_2D);

				if (MainWorkZone(221, 436, 200, 5))
				{
					wsprintf(buff, "Exp: %u / %u", CurrentMasterExp, NextMasterExp);
					pDrawToolTip(280, 418, buff);
				}
			}
			else
			{
				ExpNum = 0;
			}
		}
		else
		{
			if (ReadExp > 0 && ReadNextExp > 0)
			{
				double Exp = ((ReadExp * 100) / (ReadNextExp + (ReadNextExp - ReadExp))) % 10;
				ExpNum = Exp;
				Exp = Exp * 20;
				Exp = ((Exp > 199) ? 199 : Exp);
				//glColor4f(1.0, 1.0, 0.2f, 1.0);
				pDrawBarForm(221, 436, (float)Exp, 5.0, 0.0f, 0);
				double ExpForm = Exp + 10;
				ExpForm = ((ExpForm > 200) ? 200 : ExpForm);
				glColor4f(1.0f, 1.0f, 1.0f, 0.20000001f);
				pDrawBarForm(221, 436, (float)ExpForm, 5.0, 0.0, 0);
				ExpNum = ((ExpNum > 9) ? 9 : ExpNum);
				glColor4f(1.0, 1.0, 1.0, 1.0);
				glEnable(GL_TEXTURE_2D);
				if (MainWorkZone(221, 436, 200, 5))
				{
					wsprintf(buff, "Exp: %u / %u", ReadExp, ReadNextExp);
					pDrawToolTip(280, 418, buff);
				}
			}
			else
			{
				ExpNum = 0;
			}
		}
		glColor3f(1.0f, 1.0f, 0.7f);
		pDrawInterfaceNumBer(425, 432, (int)ExpNum, 1);
	
		//pGLSwitch();
		//glColor3f(1.0f, 1.0f, 1.0f);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);
	}
}

void Interface::Work2() {
	if (gInterface.item_post_ && pCursorX < 150)
	{
		DrawItem2(pCursorX - 50.0f, pCursorY, gObjUser.PostItemX, gObjUser.PostItemY,gObjUser.PostItemID, gObjUser.PostItemLV, gObjUser.PostItemExc, 0, 0);
		gInterface.DrawItemToolTipText(gInterface.item_post_, pCursorX + 80, pCursorY - 80);
		if (gInterface.last_tickcount_view_ + 100 < GetTickCount()) {
			gInterface.item_post_ = nullptr;
		}
	}
    pDrawInterface2();
}

void Interface::DrawChat ( int mode, char* character, char* message ) {
    PBMSG_CHATPOSTITEM chat;
    memset ( &chat.character_[0], 0, 10 );
    memset ( &chat.message_[0], 0, 89 );
    memcpy ( &chat.character_[0], &character[0], 10 );
    memcpy ( &chat.message_[0], &message[0], strlen ( message ) );
    pHandlePacketChatData ( &chat );

	if (mode >= 1 && mode <= 9 && ChatBoxMuObjectChatDataPtrArrayLength) {
		int index = ChatBoxMuObjectChatDataPtrArrayLength - 1;
		ChatBoxMuObjectChatDataPtrArray[index]->chat_type_ = mode;
	}
}

void Interface::DrawItemToolTipText ( void * item, int x, int y ) {
		static DWORD mem = 0;
		//static DWORD ItemToolTipAdress1 = 0x00861110; //1.04D-> 0x00860FC0
		//static DWORD ItemToolTipAdress2 = 0x00861AA0; //1.04D-> 0x00861950
		//static DWORD ItemToolTipAdress3 = 0x007E3E30; //1.04D-> 0x007E3CE0
		_asm {
		    PUSH 0
		    PUSH 0
		    PUSH 0
		    PUSH item
		    PUSH y
		    PUSH x
			MOV mem,0x00861110
		    CALL mem
		    MOV ECX, EAX
			MOV mem,0x00861AA0
		    CALL mem
		    MOV ECX, EAX
			MOV mem,0x007E3E30
		    CALL mem
		}

}

void Interface::RolltheDice()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Warehouse) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse))
		return;

	if( !this->Data[eRollMain].OnShow )
	{
		return;
	}

	float StartX = 200.0;
	float StartY = 30.0;
	int DiceMoney2 = this->DiceMoney;
	pDrawGUI(iRollMain,200,30,250,380);
	pDrawGUI(iRollOver,228,52,72,13);
	pDrawGUI(iRollUnder,228,67,72,13);
	pDrawGUI(iRollUp,342,52,15,13);
	pDrawGUI(iRollDown,342,67,15,13);
	pDrawGUI(iRollButton,310,375,17,13);//-
	pDrawGUI(iRollButton,335,375,17,13);//+
	pDrawGUI(iRollStart,365,372,62,21);
	Font[TAHOMA_BOLD_17]->DrawText(387, 375, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(23));
	this->DrawFormat(eWhite, StartX + 100, StartY + 325, 35, 3, gCustomMessage.GetMessage(17));
	this->DrawFormat(eOrange, StartX + 117, StartY + 346, 5, 3, "-");
	this->DrawFormat(eOrange, StartX + 142, StartY + 346, 5, 3, "+");
	this->DrawFormat(eOrange, StartX + 25, StartY + 346, 64, 3, gCustomMessage.GetMessage(18));
	this->DrawFormat(eWhite, StartX + 55, StartY + 346, 64, 3, "%d",DiceMoney2);
	//this->DrawFormat(eRed, StartX + 100, StartY + 30, 64, 3, "%d",this->DiceNumber);
	Font[TAHOMA_BOLD_17]->DrawText(StartX + 120, StartY + 27, Fcolor->Gold, Fcolor->Trans, 15, (LPINT)5, "%d",this->DiceNumber);
	this->DrawFormat(eOrange, StartX + 165, StartY + 23, 64, 3, gCustomMessage.GetMessage(20));
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 97, StartY + 75, Fcolor->Orange, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(19));
	this->DrawFormat(eWhite2, StartX + 5, StartY + 93, 64, 3, "BET");
	this->DrawFormat(eWhite180, StartX + 5, StartY + 108, 64, 3, "%d",this->LastBet);
	this->DrawFormat(eWhite2, StartX + 35, StartY + 93, 64, 3, "PAYOUT");
	this->DrawFormat(eWhite2, StartX + 35, StartY + 108, 64, 3, "%f",this->LastPay);
	this->DrawFormat(eWhite2, StartX + 68, StartY + 93, 64, 3, "GAME");
	this->DrawFormat(eWhite2, StartX + 68, StartY + 108, 64, 3, "%d",this->LastGame);
	this->DrawFormat(eWhite2, StartX + 101, StartY + 93, 64, 3, "ROLL");
	this->DrawFormat(eRed, StartX + 101, StartY + 108, 64, 3, "%d",gInterface.TotalPoint);
	this->DrawFormat(eWhite2, StartX + 145, StartY + 93, 64, 3, "PROFIT");
	if(this->Winner == 1)
	{
		this->DrawFormat(eBlue, StartX + 135, StartY + 325, 30, 3, "%d",this->Balance + LastProfit - DiceMoney2);
		this->DrawFormat(eShinyGreen, StartX + 145, StartY + 108, 64, 3, "%d",this->LastProfit);
	}
	else if(this->Winner == 2)
	{
		this->DrawFormat(eBlue, StartX + 135, StartY + 325, 30, 3, "%d",this->Balance - DiceMoney2);
		this->DrawFormat(eRed, StartX + 145, StartY + 108, 64, 3, "0");
	}
	if(this->LastGame2 == 1)
	{this->DrawFormat(eWhite2, StartX + 63, StartY + 108, 64, 3, " > ");
	}else if (this->LastGame2 == 2)
	{
		this->DrawFormat(eWhite2, StartX + 63, StartY + 108, 64, 3, " < ");
	}
	switch(Dice1)
	{
		case 1:
		pDrawGUI(iRollNum1, StartX + 70, StartY + 190, 49, 49); //
		break;
		case 2:
		pDrawGUI(iRollNum2, StartX + 70, StartY + 180, 49, 49); //
		break;
		case 3:
		pDrawGUI(iRollNum3, StartX + 70, StartY + 190, 49, 49); //
		break;
		case 4:
		pDrawGUI(iRollNum4, StartX + 70, StartY + 180, 49, 49); //
		break;
		case 5:
		pDrawGUI(iRollNum5, StartX + 70, StartY + 190, 49, 49); //
		break;
		case 6:
		pDrawGUI(iRollNum6, StartX + 70, StartY + 180, 49, 49); //
		break;
	}

	switch(Dice2)
	{
		case 1:
		pDrawGUI(iRollNum1, StartX + 130, StartY + 180, 49, 49); //
		break;
		case 2:
		pDrawGUI(iRollNum2, StartX + 130, StartY + 190, 49, 49); //
		break;
		case 3:
		pDrawGUI(iRollNum3, StartX + 130, StartY + 180, 49, 49); //
		break;
		case 4:
		pDrawGUI(iRollNum4, StartX + 130, StartY + 190, 49, 49); //
		break;
		case 5:
		pDrawGUI(iRollNum5, StartX + 130, StartY + 180, 49, 49); //
		break;
		case 6:
		pDrawGUI(iRollNum6, StartX + 130, StartY + 190, 49, 49); //
		break;
	}


	if(DiceType == 1)//Over
	{
		this->DrawColoredGUI(eRollOver, StartX + 28, StartY + 22, eShinyGreen);
		switch (DiceNumber)
		{
			case 2:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.01x");
			break;
			case 3:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.07x");
			break;
			case 4:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.18x");
			break;
			case 5:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.36x");
			break;
			case 6:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.68x");
			break;
			case 7:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "2.35x");
			break;
			case 8:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "3.53x");
			break;
			case 9:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "5.88x");
			break;
			case 10:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "11.76x");
			break;
			case 11:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "35.28x");
			break;
		}
	}
	if(DiceType == 2)//Under
	{
		this->DrawColoredGUI(eRollUnder, StartX + 28, StartY + 37,eShinyGreen);
		switch (DiceNumber)
		{
			case 12:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.01x");
			break;
			case 11:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.07x");
			break;
			case 10:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.18x");
			break;
			case 9:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.36x");
			break;
			case 8:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "1.68x");
			break;
			case 7:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "2.35x");
			break;
			case 6:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "3.53x");
			break;
			case 5:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "5.88x");
			break;
			case 4:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "11.76x");
			break;
			case 3:
			this->DrawFormat(eWhite, StartX + 164, StartY + 35, 64, 3, "35.28x");
			break;
		}
	}
	Font[TAHOMA_BOLD_15]->DrawText(255, 53, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(15));
	Font[TAHOMA_BOLD_15]->DrawText(255, 68, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(16));

	pDrawGUI(0x7EC5,415,30,36,29);
	if( this->IsWorkZone2(ROLLDICE_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[ROLLDICE_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(ROLLDICE_CLOSE, this->Data[ROLLDICE_CLOSE].X, this->Data[ROLLDICE_CLOSE].Y, Color);
	}
}
void Interface::EventRolltheDice_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eRollMain].OnShow )
	{
		return;
	}
	
	if (this->IsWorkZone2(eRollOver))
	{
	DWORD Delay = (CurrentTick - this->Data[eRollOver].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRollOver].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eRollOver].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eRollOver].EventTick = GetTickCount();
	this->DiceType	=	1;
	this->DiceNumber = 3;
	}
	else if (this->IsWorkZone2(eRollUnder))
	{
	DWORD Delay = (CurrentTick - this->Data[eRollUnder].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRollUnder].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eRollUnder].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eRollUnder].EventTick = GetTickCount();
	this->DiceType	=	2;
	this->DiceNumber = 3;
	}	

	else if (this->IsWorkZone2(eRollUp))
	{
	DWORD Delay = (CurrentTick - this->Data[eRollUp].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRollUp].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eRollUp].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eRollUp].EventTick = GetTickCount();
	if(DiceType == 1)
	{
		if(DiceNumber >= 11){
			return;
			}else{
			this->DiceNumber	+=	1;}}

		else if (DiceType == 2){
		if(DiceNumber >= 12){
			return;
			}else{
			this->DiceNumber	+=	1;}}
	}
	
	else if (this->IsWorkZone2(eRollDown))
	{
	DWORD Delay = (CurrentTick - this->Data[eRollDown].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRollDown].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eRollDown].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eRollDown].EventTick = GetTickCount();
	if(DiceType == 1)
	{
		if(DiceNumber <= 2){
			return;
			}else{
			this->DiceNumber	-=	1;}}

		else if (DiceType == 2){
		if(DiceNumber <= 3){
			return;
			}else{
			this->DiceNumber	-=	1;}}	
	}
	else if (this->IsWorkZone2(eRollButtonA))
	{
	DWORD Delay = (CurrentTick - this->Data[eRollButtonA].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRollButtonA].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eRollButtonA].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eRollButtonA].EventTick = GetTickCount();
	if(this->DiceMoney <= 100)
	{
		return;
	}
	else if(this->DiceMoney >= 2000)
	{
		this->DiceMoney	-=	1000;
	}
	else
	{
		this->DiceMoney	-=	100;
	}
	}

	else if (this->IsWorkZone2(eRollButtonB))
	{
	DWORD Delay = (CurrentTick - this->Data[eRollButtonB].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRollButtonB].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eRollButtonB].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eRollButtonB].EventTick = GetTickCount();
	if(this->DiceMoney >= 10000)
	{
		return;
	}
	else if(this->DiceMoney >= 1000)
	{
		this->DiceMoney	+=	1000;
	}
	else
	{
		this->DiceMoney	+=	100;
	}
	}
	
	else if (this->IsWorkZone2(eRollStart))
	{
	DWORD Delay = (CurrentTick - this->Data[eRollStart].EventTick);

	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRollStart].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----
	this->Data[eRollStart].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 2000)
	{
		return;
	}
	// ----
	this->Data[eRollStart].EventTick = GetTickCount();
	StartRoll(DiceType,DiceNumber,DiceMoney);
	this->LastBet = DiceMoney;
	this->LastGame = DiceNumber;
	if(DiceType == 1)
	{
		this->LastGame2 = 1;
		switch (DiceNumber)
		{
		case 2:
		this->LastPay = 1.01;
		break;
		case 3:
		this->LastPay = 1.07;
		break;
		case 4:
		this->LastPay = 1.18;
		break;
		case 5:
		this->LastPay = 1.36;
		break;
		case 6:
		this->LastPay = 1.68;
		break;
		case 7:
		this->LastPay = 2.35;
		break;
		case 8:
		this->LastPay = 3.53;
		break;
		case 9:
		this->LastPay = 5.88;
		break;
		case 10:
		this->LastPay = 11.76;
		break;
		case 11:
		this->LastPay = 35.28;
		break;
		}
	}
	else if(DiceType == 2)
	{
		this->LastGame2 = 2;
		switch (DiceNumber)
		{
		case 12:
		this->LastPay = 1.01;
		break;
		case 11:
		this->LastPay = 1.07;
		break;
		case 10:
		this->LastPay = 1.18;
		break;
		case 9:
		this->LastPay = 1.36;
		break;
		case 8:
		this->LastPay = 1.68;
		break;
		case 7:
		this->LastPay = 2.35;
		break;
		case 6:
		this->LastPay = 3.53;
		break;
		case 5:
		this->LastPay = 5.88;
		break;
		case 4:
		this->LastPay = 11.76;
		break;
		case 3:
		this->LastPay = 35.28;
		break;
		}
	}
 }	
	else if (this->IsWorkZone2(ROLLDICE_CLOSE))
	{
	DWORD Delay = (CurrentTick - this->Data[ROLLDICE_CLOSE].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[ROLLDICE_CLOSE].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[ROLLDICE_CLOSE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[ROLLDICE_CLOSE].EventTick = GetTickCount();
	this->CloseRolltheDiceWindow();
	}
}
void Interface::TitleSystem()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Warehouse) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse))
		return;

	if (!this->Data[eTitle].OnShow)
	{
		return;
	}

	this->DrawGUI(eTitle, 250.0f, 100.0f);
	this->DrawGUI(eClickLeft, 275, 135.0f);
	this->DrawGUI(eClickRight, 380, 135.0f);
	int color = gCustomTitle.m_CustomTitle[this->TitleCode - 1].color;
	pDrawGUI(gCustomTitle.m_CustomTitle[this->TitleCode - 1].ImgCode, 305.0f , 105.0f, gCustomTitle.m_CustomTitle[this->TitleCode].width, gCustomTitle.m_CustomTitle[this->TitleCode].height);
	pDrawColorText(gCustomTitle.m_CustomTitle[this->TitleCode - 1].TitleText, 260.0f, 160.0f, 150, 1.5, gHPBar.RankTextColor[color], 32, 3 );
	this->DrawFormat(eWhite, 260.0f, 198.0f, 64, 3, gCustomMessage.GetMessage(50),gCustomTitle.m_CustomTitle[this->TitleCode - 1].AddHP);
	this->DrawFormat(eWhite, 260.0f, 214.0f, 64, 3, gCustomMessage.GetMessage(51),gCustomTitle.m_CustomTitle[this->TitleCode - 1].AddMP);
	if (gDanhHieu.m_RankTitle[TitleCode] == 0){
			this->DrawGUI(eRankBuy, 320.0f, 182.0f);
			this->DrawFormat(eGold, 326.0f, 182.0f, 210, 1, gCustomMessage.GetMessage(52));
		}
	if	(gDanhHieu.m_RankTitle[TitleCode] == 1){
			this->DrawGUI(eRankSlot1, 300.0f, 228.0f);
			this->DrawFormat(eGold, 302.0f, 228.0f, 210, 1, gCustomMessage.GetMessage(53));
			this->DrawGUI(eRankDeactive, 340.0f, 228.0f);
			this->DrawFormat(eGold, 342.0f, 228.0f, 210, 1, gCustomMessage.GetMessage(93));
		}
	pDrawGUI(0x7EC5,388,95,36,29);
	if( this->IsWorkZone2(TITLEMANAGER_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[TITLEMANAGER_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(TITLEMANAGER_CLOSE, this->Data[TITLEMANAGER_CLOSE].X, this->Data[TITLEMANAGER_CLOSE].Y, Color);
	}
}
void Interface::EventTitleSystem_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eTitle].OnShow )
	{
		return;
	}

	// ----
	if (this->IsWorkZone2(eRankBuy))
	{
	DWORD Delay = (CurrentTick - this->Data[eRankBuy].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRankBuy].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----
	this->Data[eRankBuy].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eRankBuy].EventTick = GetTickCount();
		if(gDanhHieu.m_RankTitle[TitleCode] >= 1)
		{return;}
		else{
		gDanhHieu.BuyTitle(TitleCode);
		}
	}
	else if (this->IsWorkZone2(eRankSlot1))
	{
	DWORD Delay = (CurrentTick - this->Data[eRankSlot1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRankSlot1].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----
	this->Data[eRankSlot1].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eRankSlot1].EventTick = GetTickCount();
	this->CloseTitleSystemWindow();
		if(gDanhHieu.m_RankTitle[TitleCode] == 0)
		{return;}
		else{
		gDanhHieu.Active(1,TitleCode);
		}
	}
	else if (this->IsWorkZone2(eRankDeactive))
	{
	DWORD Delay = (CurrentTick - this->Data[eRankDeactive].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eRankDeactive].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----
	this->Data[eRankDeactive].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eRankDeactive].EventTick = GetTickCount();
	this->CloseTitleSystemWindow();
	gDanhHieu.Deactive();
	}
	else if (this->IsWorkZone2(eClickLeft))
	{
	DWORD Delay = (CurrentTick - this->Data[eClickLeft].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eClickLeft].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eClickLeft].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eClickLeft].EventTick = GetTickCount();
	if(this->TitleCode <= 1)
	{return;}else
	this->TitleCode	-=	1;
	}
	else if (this->IsWorkZone2(eClickRight))
	{
	DWORD Delay = (CurrentTick - this->Data[eClickRight].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eClickRight].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eClickRight].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eClickRight].EventTick = GetTickCount();
	if(this->TitleCode >= 20)
	{return;}else
	this->TitleCode	+=	1;
	}

	else if (this->IsWorkZone2(TITLEMANAGER_CLOSE))
	{
	DWORD Delay = (CurrentTick - this->Data[TITLEMANAGER_CLOSE].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[TITLEMANAGER_CLOSE].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[TITLEMANAGER_CLOSE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[TITLEMANAGER_CLOSE].EventTick = GetTickCount();
	this->CloseTitleSystemWindow();
	}
}
void Interface::DrawUserPanel()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(MoveList) ||
		this->CheckWindow(SkillTree))
		return;
	if (!this->ShowUserPanel)
	{
		return;
	}

	pDrawImage(iGfxDialoge, 1, 7, 223, 280, 1, 1, 1.0, 1.0, 1, 1, 0);
	pDrawImage(iNewuiDialogHr, 1, 235, 210, 10, 1, 1, 1.0, 1.0, 1, 1, 0);

	//this->DrawUserPanelMain();
	this->DrawFormat(eGold, 1 , 27, 223, 3, gCustomMessage.GetMessage(5));

	pDrawGUI(iOptionDot,20,65,10,10);
	this->DrawFormat(eWhite, 40 , 65, +120, 2, gCustomMessage.GetMessage(6));
	pDrawGUI(iOptionLine, 50, 75, 82.0, 2.0);

	pDrawGUI(iOptionDot,20,95,10,10);
	this->DrawFormat(eWhite, 40 , 95, +120, 2, gCustomMessage.GetMessage(7));
	pDrawGUI(iOptionLine, 50, 105, 82.0, 2.0);

	pDrawGUI(iOptionDot,20,125,10,10);
	this->DrawFormat(eWhite, 40 , 125, +120, 2, gCustomMessage.GetMessage(8));
	pDrawGUI(iOptionLine, 50, 135, 82.0, 2.0);

	pDrawGUI(iOptionDot,20,155,10,10);
	this->DrawFormat(eWhite, 40 , 155, +120, 2, gCustomMessage.GetMessage(9));
	pDrawGUI(iOptionLine, 50, 165, 82.0, 2.0);

	pDrawGUI(iOptionDot,20,185,10,10);
	this->DrawFormat(eWhite, 40 , 185, +120, 2, gCustomMessage.GetMessage(10));
	pDrawGUI(iOptionLine, 50, 195, 82.0, 2.0);
	
	pDrawButton(iOptionCheck,175,60,15,15,0,15);
	pDrawButton(iOptionCheck,175,120,15,15,0,15);
	pDrawButton(iOptionCheck,175,150,15,15,0,15);
	
	if(gHPBar.LifeBar == true)
	{
		pDrawButton(iOptionCheck,175,60,15,15,0,0);
	}
	if(gObjUser.TitleBarSwitch == 1)
	{
		pDrawButton(iOptionCheck,175,90,15,15,0,15);
		if(gHPBar.TitleBar == true)
		{
			pDrawButton(iOptionCheck,175,90,15,15,0,0);
		}
	}
	if(gObjUser.PlayerHPBarSwitch == 1)
	{
		pDrawButton(iOptionCheck,195,90,15,15,0,15);
		if(gHPBar.PlayerHPBar == true)
		{
			pDrawButton(iOptionCheck,195,90,15,15,0,0);
		}
	}
	if(gFog.EnableFog == true)
	{
		pDrawButton(iOptionCheck,175,120,15,15,0,0);
	}
	if(gInterface.showMiniMap == TRUE)
	{
		pDrawButton(iOptionCheck,175,150,15,15,0,0);
	}

	pDrawButton(iGfxBtnSmall,30,210,52,21,0,0);
	pDrawButton(iGfxBtnSmall,90,210,52,21,0,0);
	pDrawButton(iGfxBtnSmall,150,210,52,21,0,0);
	if(this->IsWorkZone2(eNewButton1))
	{
		float Z = 21.0;
		if(this->Data[eNewButton1].OnClick)
		{
			Z = 42.0;
		}
		pDrawButton(iGfxBtnSmall,30,210,52,21,0,Z);
	}
	else if(this->IsWorkZone2(eNewButton2))
	{
		float Z = 21.0;
		if(this->Data[eNewButton2].OnClick)
		{
			Z = 42.0;
		}
		pDrawButton(iGfxBtnSmall,90,210,52,21,0,Z);
	}
	else if(this->IsWorkZone2(eNewButton3))
	{
		float Z = 21.0;
		if(this->Data[eNewButton3].OnClick)
		{
			Z = 42.0;
		}
		pDrawButton(iGfxBtnSmall,150,210,52,21,0,Z);
	}
	this->DrawFormat(eWhite,30,215,52,3,gCustomMessage.GetMessage(11));
	this->DrawFormat(eWhite,90,215,52,3,gCustomMessage.GetMessage(12));
	this->DrawFormat(eWhite,150,215,52,3,gCustomMessage.GetMessage(13));

	 pDrawButton(iGfxBtnSmall2,90,250,52,22,0,0);
	 if(this->IsWorkZone2(eBUTTON3_1))
		{
			float Z = 23.0;
			if(this->Data[eBUTTON3_1].OnClick)
			{
				Z = 46.0;
			}
			 pDrawButton(iGfxBtnSmall2,90,250,52,22,0,Z);
		}
	this->DrawFormat(eWhite,90,255,52,3,gCustomMessage.GetMessage(14));

	/*
	pDrawButton(iGfxBtnSmall2,130,250,52,22,0,0);
	 if(this->IsWorkZone2(eBUTTON4_1))
		{
			float Z = 23.0;
			if(this->Data[eBUTTON4_1].OnClick)
			{
				Z = 46.0;
			}
			 pDrawButton(iGfxBtnSmall2, 130,250,52,22,0,Z);
		}
		this->DrawFormat(eWhite, 130,255,52,3,gCustomMessage.GetMessage(45));
		*/
}
void Interface::EventUserPanel(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if (!this->ShowUserPanel)
	{
		return;
	}
	if (this->IsWorkZone2(eUNCHECK_2))
	{
		DWORD Delay = (CurrentTick - this->Data[eUNCHECK_2].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eUNCHECK_2].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eUNCHECK_2].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eUNCHECK_2].EventTick = GetTickCount();
		// ----
		if (!this->Data[eCHECKED_2].OnShow)
		{
			this->Data[eCHECKED_2].OnShow = true;
			gHPBar.LifeBar = true;
		}
		else {
			this->Data[eCHECKED_2].OnShow = false;
			gHPBar.LifeBar	= false;
		}
	}
	else if (this->IsWorkZone2(eUNCHECK_3))
	{
		DWORD Delay = (CurrentTick - this->Data[eUNCHECK_3].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eUNCHECK_3].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eUNCHECK_3].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eUNCHECK_3].EventTick = GetTickCount();
		// ----
		if (!this->Data[eCHECKED_3].OnShow)
		{
			this->Data[eCHECKED_3].OnShow = true;
			gHPBar.TitleBar = true;
		}
		else {
			this->Data[eCHECKED_3].OnShow = false;
			gHPBar.TitleBar	= false;
		}
	}
	else if (this->IsWorkZone2(eUNCHECK_4))
	{
		DWORD Delay = (CurrentTick - this->Data[eUNCHECK_4].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eUNCHECK_4].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eUNCHECK_4].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eUNCHECK_4].EventTick = GetTickCount();
		// ----
		if (!this->Data[eCHECKED_4].OnShow)
		{
			this->Data[eCHECKED_4].OnShow = true;
			gFog.EnableFog = true;
		}
		else {
			this->Data[eCHECKED_4].OnShow = false;
			gFog.EnableFog = false;
		}
	}
	else if (this->IsWorkZone2(eUNCHECK_5))
	{
		DWORD Delay = (CurrentTick - this->Data[eUNCHECK_5].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eUNCHECK_5].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eUNCHECK_5].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eUNCHECK_5].EventTick = GetTickCount();
		// ----
		if (!this->Data[eCHECKED_5].OnShow)
		{
			this->Data[eCHECKED_5].OnShow = true;
			gInterface.showMiniMap = TRUE;
		}
		else {
			this->Data[eCHECKED_5].OnShow = false;
			gInterface.showMiniMap = FALSE;
		}
	}
	else if (this->IsWorkZone2(eUNCHECK_6))
	{
		DWORD Delay = (CurrentTick - this->Data[eUNCHECK_6].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eUNCHECK_6].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eUNCHECK_6].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eUNCHECK_6].EventTick = GetTickCount();
		// ----
		if (!this->Data[eCHECKED_6].OnShow)
		{
			this->Data[eCHECKED_6].OnShow = true;
			gHPBar.PlayerHPBar = TRUE;
		}
		else {
			this->Data[eCHECKED_6].OnShow = false;
			gHPBar.PlayerHPBar = FALSE;
		}
	}
	else if (this->IsWorkZone2(eBUTTON3_1))
	{
		DWORD Delay = (CurrentTick - this->Data[eBUTTON3_1].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eBUTTON3_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eBUTTON3_1].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eBUTTON3_1].EventTick = GetTickCount();
		// ----
		this->CloseUserPanel();
		//this->CloseUserPanelMain();
	}
	/*
	else if (this->IsWorkZone2(eBUTTON4_1))
	{
		DWORD Delay = (CurrentTick - this->Data[eBUTTON4_1].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eBUTTON4_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eBUTTON4_1].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eBUTTON4_1].EventTick = GetTickCount();
		// ----
		this->CloseUserPanel();
		this->OpenGamblingPanel();
		USERBUTTON_REQ pRequest;
		pRequest.Head.set(0xFF,0x04,sizeof(pRequest));
		DataSend((BYTE*)&pRequest,pRequest.Head.size);
	}
	*/
	else if (this->IsWorkZone2(eNewButton1))
	{
		DWORD Delay = (CurrentTick - this->Data[eNewButton1].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eNewButton1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eNewButton1].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eNewButton1].EventTick = GetTickCount();
		// ----
		SetFloat((PVOID)0x0D27B1C, 1000.000); //-> Camera Range

	}
	else if (this->IsWorkZone2(eNewButton2))
	{
		DWORD Delay = (CurrentTick - this->Data[eNewButton2].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eNewButton2].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eNewButton2].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eNewButton2].EventTick = GetTickCount();
		// ----
		SetFloat((PVOID)0x0D27B1C, 1080.000); //-> Camera Range

	}
	else if (this->IsWorkZone2(eNewButton3))
	{
		DWORD Delay = (CurrentTick - this->Data[eNewButton3].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eNewButton3].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eNewButton3].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eNewButton3].EventTick = GetTickCount();
		// ----
		SetFloat((PVOID)0x0D27B1C, 1160.000); //-> Camera Range
	}
}
void Interface::DrawMiniMap()
{
	if (gInterface.showMiniMap)
	{
		float MainWidth = 138.0;
		float MainHeight = 265.0;
		float StartY = 264.0;
		float StartX = 512.0;
		// ----
		if (this->MiniMapCheck() || this->CombinedChecks())
		{
			return;
		}
		// ----
		switch (gObjUser.m_MapNumber)
		{
		case 0:    //Lorencia
			//pDrawGUI(0x9182, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9182, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 1:    //Dungeon
			//pDrawGUI(0x9183, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9183, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 2:    //Devias
			//pDrawGUI(0x9184, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9184, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 3:    //Noria
			//pDrawGUI(0x9185, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9185, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 4:    //LostTower
			//pDrawGUI(0x9186, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9186, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 5:    //Exile (disabled)
			return;
			break;
			// --
			// --
		case 7:    //Atlans
			//pDrawGUI(0x9187, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9187, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 8:    //Tarkan
			//pDrawGUI(0x9188, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9188, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 10:    //Icarus
			//pDrawGUI(0x9190, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9190, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 24: //	Kalima1-6
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
			pDrawImage(0x9191, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
		case 31:    //Land of Trials
			//pDrawGUI(0x9191, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9192, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 33:    //Aida
			//pDrawGUI(0x9192, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9193, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 34:    //Crywolf Fortress
			//pDrawGUI(0x9193, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9194, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 36:	//Kalima 7
			pDrawImage(0x9191, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
		case 37:    //Kantru
			//pDrawGUI(0x9194, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9196, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 38:    //Kantru 3
			//pDrawGUI(0x9195, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9197, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
		case 39:
			pDrawImage(0x9198, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 41:    //Barracks
			pDrawGUI(0x9196, StartX, StartY + 30, 128, 128); //
			break;
			// --
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 50:
			pDrawImage(0x9199, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
		case 51:    //Elbeland
			//pDrawGUI(0x9189, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9200, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 56:    //Swamp of Calmness
			//pDrawGUI(0x9197, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9201, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 57:    //Raklion
			//pDrawGUI(0x9198, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9202, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 63:    //Vulcanus
			//pDrawGUI(0x9199, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9203, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 79:
			pDrawImage(0x9204, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
		case 80:    //Kalrutan
			//pDrawGUI(0x9200, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9205, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		case 81:    //Kalrutan 2
			//pDrawGUI(0x9201, StartX, StartY + 30, 128, 128); //
			pDrawImage(0x9206, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
		case 83:	//
			pDrawImage(0x9207, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
		case 84:
			pDrawImage(0x9208, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
		case 85:
			pDrawImage(0x9209, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
		case 86:
			pDrawImage(0x9210, StartX, StartY + 30, 128, 128, 1, 1, 1.0, 1.0, 1, 1, 0);
			break;
			// --
		default: //Default
			return;
			break;
		}
		// ----
		if(pPartyMemberCount != 0)
		{
			for (int i=0;i<gMiniMap.ListsCount;i++)
			{
				if(gObjUser.m_MapNumber == gMiniMap.gPartyInfo[i].map)
				{
					Font[TAHOMA_BOLD_12]->DrawText((float)(StartX - 12 + gMiniMap.gPartyInfo[i].x / 2), (float)(285 - 1 + (255 - gMiniMap.gPartyInfo[i].y) / 2), Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gMiniMap.gPartyInfo[i].name);
					pDrawGUI(0x9180, (float)(StartX - 1 + gMiniMap.gPartyInfo[i].x / 2), (float)(294 - 1 + (255 - gMiniMap.gPartyInfo[i].y) / 2),2,2);
				}
			}
		}
		else
		{
			pDrawGUI(0x9180, (float)(StartX - 1 + gObjUser.lpViewPlayer->MapPosX / 2), (float)(294 - 1 + (255 - gObjUser.lpViewPlayer->MapPosY) / 2),2,2);
		}
	}
}

void Interface::EventMiniMap(DWORD Event)
{

}


void Interface::HUDEvent()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(SkillTree))
		return;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	if(gDanhHieu.IsSurvivor >= 1)
	{
	pDrawGUI(0x9696, MAX_WIN_WIDTH-118, 0, 118, 27); //
	//this->DrawFormat(eWhite, MAX_WIN_WIDTH-110, 3, 70, 3, "%d", gObjUser.SurvivorKill);
	//this->DrawFormat(eWhite, MAX_WIN_WIDTH-82, 3, 70, 3, "%d", gObjUser.SurvivorDie);
	this->DrawFormat(eWhite, MAX_WIN_WIDTH-52, 3, 70, 3, "%d", gDanhHieu.SurvivorPlayer);
	}
}
void Interface::HeadsTails()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Warehouse) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse))
		return;

	if( !this->Data[eFlipMain].OnShow )
	{
		return;
	}
	DWORD CurrentTick = GetTickCount();
	float StartX = 200.0;
	float StartY = 30.0;
	int HeadsTailsMoney2 = this->HeadsTailsMoney;
	pDrawGUI(0x9690,200,30,250,380);
	pDrawGUI(0x9691,235,50,30,30);
	pDrawGUI(0x9693,290,50,30,30);
	pDrawGUI(iRollStart,365,372,62,21);
	Font[TAHOMA_BOLD_17]->DrawText(387, 375, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(24));
	Font[TAHOMA_BOLD_13]->DrawText(240, 45, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(21));
	Font[TAHOMA_BOLD_13]->DrawText(297, 45, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(22));
	this->DrawFormat(eOrange, StartX + 165, StartY + 23, 64, 3, gCustomMessage.GetMessage(20));
	this->DrawFormat(eWhite, StartX + 164, StartY + 33, 64, 3, "1.92x");
	//
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 95, StartY + 71, Fcolor->Orange, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(19));
	//this->DrawFormat(eYellow, StartX + 95, StartY + 72, 64, 3, "History bets");
	this->DrawFormat(eWhite2, StartX + 20, StartY + 85, 64, 3, "GAME");
	this->DrawFormat(eWhite2, StartX + 85, StartY + 85, 64, 3, "BET");
	this->DrawFormat(eWhite2, StartX + 148, StartY + 85, 64, 3, "PROFIT");
	this->DrawFormat(eWhite180, StartX + 85, StartY + 110, 64, 3, "%d",this->HeadsTailsLastBet);
	if(this->HeadsTailsProfit > 0)
	this->DrawFormat(eShinyGreen, StartX + 148, StartY + 110, 64, 3, "%d",this->HeadsTailsProfit);
	else
	this->DrawFormat(eRed, StartX + 148, StartY + 110, 64, 3, "0");
	this->DrawFormat(eWhite, StartX + 100, StartY + 324, 35, 3, gCustomMessage.GetMessage(17));
	//
	pDrawGUI(iRollButton,310,375,17,13);//-
	pDrawGUI(iRollButton,335,375,17,13);//+
	this->DrawFormat(eOrange, StartX + 117, StartY + 346, 5, 3, "-");
	this->DrawFormat(eOrange, StartX + 142, StartY + 346, 5, 3, "+");
	this->DrawFormat(eOrange, StartX + 25, StartY + 346, 64, 3, gCustomMessage.GetMessage(18));
	this->DrawFormat(eWhite, StartX + 55, StartY + 346, 64, 3, "%d",HeadsTailsMoney2);
	//
	//
	DWORD Delay = (CurrentTick - this->Data[eFlipStart].EventTick);

	if(HeadsTailsType == 1)//Heads
	{
		this->DrawColoredGUI(eFlipHeads, 235, 50, eShinyGreen);
		if (Delay < 2000)
		{
		if(this->HeadsTailsWiner == 1)
		{
			pDrawGUI(0x9692, 275, 200, 100, 100); //
		}
		else if(this->HeadsTailsWiner == 2)
		{
			pDrawGUI(0x9694, 275, 200, 100, 100); //
		}
		}

	}
	else if(HeadsTailsType == 2)//Tails
	{
		this->DrawColoredGUI(eFlipTails, 290, 50, eShinyGreen);
		if (Delay < 2000)
		{
		if(this->HeadsTailsWiner == 1)
		{
			pDrawGUI(0x9694, 275, 200, 100, 100); //
		}
		else if(this->HeadsTailsWiner == 2)
		{
			pDrawGUI(0x9692, 275, 200, 100, 100); //
		}
		}
	}
	if(HeadsTailsLastGame == 1)
		pDrawGUI(0x9691,StartX + 38,StartY + 100,30,30);
	else
		pDrawGUI(0x9693,StartX + 38,StartY + 100,30,30);

	if(HeadsTailsWiner == 1)
	{
		this->DrawFormat(eBlue, StartX + 135, StartY + 324, 30, 3, "%d",this->Balance + HeadsTailsProfit - HeadsTailsMoney2);
	}
	else if(HeadsTailsWiner == 2)
	{
		this->DrawFormat(eBlue, StartX + 135, StartY + 324, 30, 3, "%d",this->Balance - HeadsTailsMoney2);
	}

	pDrawGUI(0x7EC5,415,30,36,29);
	if( this->IsWorkZone2(HEADSTAILS_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[HEADSTAILS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(HEADSTAILS_CLOSE, this->Data[HEADSTAILS_CLOSE].X, this->Data[HEADSTAILS_CLOSE].Y, Color);
	}
}
void Interface::EventHeadsTails_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eFlipMain].OnShow )
	{
		return;
	}
	
	if (this->IsWorkZone2(eFlipHeads))
	{
	DWORD Delay = (CurrentTick - this->Data[eFlipHeads].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eFlipHeads].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eFlipHeads].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eFlipHeads].EventTick = GetTickCount();
	this->HeadsTailsType	=	1;
	}
	else if (this->IsWorkZone2(eFlipTails))
	{
	DWORD Delay = (CurrentTick - this->Data[eFlipTails].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eFlipTails].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eFlipTails].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eFlipTails].EventTick = GetTickCount();
	this->HeadsTailsType	=	2;
	}
	else if (this->IsWorkZone2(eFlipButtonA))
	{
	DWORD Delay = (CurrentTick - this->Data[eFlipButtonA].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eFlipButtonA].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eFlipButtonA].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eFlipButtonA].EventTick = GetTickCount();
	if(this->HeadsTailsMoney <= 100)
	{
		return;
	}
	else if(this->HeadsTailsMoney >= 2000)
	{
		this->HeadsTailsMoney	-=	1000;
	}
	else
	{
		this->HeadsTailsMoney	-=	100;}
	}

	else if (this->IsWorkZone2(eFlipButtonB))
	{
	DWORD Delay = (CurrentTick - this->Data[eFlipButtonB].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eFlipButtonB].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eFlipButtonB].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eFlipButtonB].EventTick = GetTickCount();
	if(this->HeadsTailsMoney >= 10000)
	{
		return;
	}
	else if(this->HeadsTailsMoney >= 1000)
	{
		this->HeadsTailsMoney	+=	1000;
	}
	else
	{
		this->HeadsTailsMoney	+=	100;
	}
	}
	else if (this->IsWorkZone2(eFlipStart))
	{
	DWORD Delay = (CurrentTick - this->Data[eFlipStart].EventTick);

	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eFlipStart].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----
	this->Data[eFlipStart].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 2500)
	{
		return;
	}
	// ----
	this->Data[eFlipStart].EventTick = GetTickCount();
	StartFlip(HeadsTailsType,HeadsTailsMoney);
	this->HeadsTailsLastBet = this->HeadsTailsMoney;
	this->HeadsTailsLastGame = this->HeadsTailsType;
	}

	else if (this->IsWorkZone2(HEADSTAILS_CLOSE))
	{
	DWORD Delay = (CurrentTick - this->Data[HEADSTAILS_CLOSE].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[HEADSTAILS_CLOSE].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[HEADSTAILS_CLOSE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[HEADSTAILS_CLOSE].EventTick = GetTickCount();
	this->CloseHeadsTailsWindow();
	}

}
void Interface::DrawLuckyNumber()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Warehouse) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse))
		return;

	if( !this->Data[eLuckyMain].OnShow )
	{
		return;
	}
	//DWORD CurrentTick = GetTickCount();
	float StartX = 200.0;
	float StartY = 30.0;
	pDrawGUI(0x9670,200,30,250,380);
	pDrawGUI(iRollButton,310,375,17,13);//-
	pDrawGUI(iRollButton,335,375,17,13);//+
	pDrawGUI(iRollStart,365,372,62,21);
	Font[TAHOMA_BOLD_17]->DrawText(370, 375, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(44));
	this->DrawFormat(eOrange, StartX + 117, StartY + 346, 5, 3, "-");
	this->DrawFormat(eOrange, StartX + 142, StartY + 346, 5, 3, "+");
	this->DrawFormat(eOrange, StartX + 25, StartY + 346, 64, 3, gCustomMessage.GetMessage(41));
	this->DrawFormat(eWhite, StartX + 55, StartY + 346, 64, 3, "%d",this->LuckyLines);
	//pDrawGUI(0x9670,250,100,170,250);
	Font[TAHOMA_BOLD_17]->DrawText(300, 50, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(32));
	this->DrawFormat(eGold, 300, 100, 50, 3, gCustomMessage.GetMessage(33));
	this->DrawFormat(eRed, 240, 115, 50, 3, gCustomMessage.GetMessage(37));
	this->DrawFormat(eRed, 360, 115, 50, 3, gCustomMessage.GetMessage(38));
	Font[TAHOMA_BOLD_15]->DrawText(255, 130, Fcolor->Gold, Fcolor->Trans, 15, (LPINT)5, "%d",this->LuckyNumber);
	Font[TAHOMA_BOLD_15]->DrawText(375, 130, Fcolor->Gold, Fcolor->Trans, 15, (LPINT)5, "%d",this->LuckyWinPrice);
	//DWORD Delay = (CurrentTick - this->Data[eLuckyStart].EventTick);
	if (this->Data[eLuckyStart].EventTick)
	{
	this->DrawFormat(eGold, 300, 184, 50, 3, gCustomMessage.GetMessage(34));
	this->DrawFormat(eWhite, 240, 200, 50, 3, gCustomMessage.GetMessage(39));
	this->DrawFormat(eWhite, 365, 200, 50, 3, "%s",gObjUser.lpPlayer->Name);
	this->DrawFormat(eWhite, 240, 210, 50, 3, gCustomMessage.GetMessage(40));
	this->DrawFormat(eWhite, 365, 210, 50, 3, "%s",this->LuckyDrawDate);
	this->DrawFormat(eWhite, 240, 220, 50, 3, gCustomMessage.GetMessage(41));
	this->DrawFormat(eWhite, 365, 220, 50, 3, "%d",this->LuckyLastLines);
	this->DrawFormat(eWhite, 240, 230, 50, 3, gCustomMessage.GetMessage(42));
	this->DrawFormat(eWhite, 365, 230, 50, 3, gCustomMessage.GetMessage(43));

	this->DrawFormat(eGold, 297, 245, 60, 3, gCustomMessage.GetMessage(35));
	if(LuckyLastLines == 1)
	{
	this->DrawFormat(eWhite, 280, 265, 5, 3, "1:");
	this->DrawFormat(eSocket, 365, 265, 20, 3, "%d",this->LuckyNumber1[0]);
	}
	else if (LuckyLastLines == 2)
	{
	this->DrawFormat(eWhite, 280, 265, 5, 3, "1:");
	this->DrawFormat(eSocket, 365, 265, 20, 3, "%d",this->LuckyNumber1[0]);
	this->DrawFormat(eWhite, 280, 275, 5, 3, "2:");
	this->DrawFormat(eBlue, 365, 275, 20, 3, "%d",this->LuckyNumber1[1]);
	}
	else if (LuckyLastLines == 3)
	{
	this->DrawFormat(eWhite, 280, 265, 5, 3, "1:");
	this->DrawFormat(eSocket, 365, 265, 20, 3, "%d",this->LuckyNumber1[0]);
	this->DrawFormat(eWhite, 280, 275, 5, 3, "2:");
	this->DrawFormat(eBlue, 365, 275, 20, 3, "%d",this->LuckyNumber1[1]);
	this->DrawFormat(eWhite, 280, 285, 5, 3, "3:");
	this->DrawFormat(ePink, 365, 285, 20, 3, "%d",this->LuckyNumber1[2]);
	}
	else if (LuckyLastLines == 4)
	{
	this->DrawFormat(eWhite, 280, 265, 5, 3, "1:");
	this->DrawFormat(eSocket, 365, 265, 20, 3, "%d",this->LuckyNumber1[0]);
	this->DrawFormat(eWhite, 280, 275, 5, 3, "2:");
	this->DrawFormat(eBlue, 365, 275, 20, 3, "%d",this->LuckyNumber1[1]);
	this->DrawFormat(eWhite, 280, 285, 5, 3, "3:");
	this->DrawFormat(ePink, 365, 285, 20, 3, "%d",this->LuckyNumber1[2]);
	this->DrawFormat(eWhite, 280, 295, 5, 3, "4:");
	this->DrawFormat(eOrange, 365, 295, 20, 3, "%d",this->LuckyNumber1[3]);
	}
	else if (LuckyLastLines == 5)
	{
	this->DrawFormat(eWhite, 280, 265, 5, 3, "1:");
	this->DrawFormat(eSocket, 365, 265, 20, 3, "%d",this->LuckyNumber1[0]);
	this->DrawFormat(eWhite, 280, 275, 5, 3, "2:");
	this->DrawFormat(eBlue, 365, 275, 20, 3, "%d",this->LuckyNumber1[1]);
	this->DrawFormat(eWhite, 280, 285, 5, 3, "3:");
	this->DrawFormat(ePink, 365, 285, 20, 3, "%d",this->LuckyNumber1[2]);
	this->DrawFormat(eWhite, 280, 295, 5, 3, "4:");
	this->DrawFormat(eOrange, 365, 295, 20, 3, "%d",this->LuckyNumber1[3]);
	this->DrawFormat(eWhite, 280, 305, 5, 3, "5:");
	this->DrawFormat(eShinyGreen, 365, 305, 20, 3, "%d",this->LuckyNumber1[4]);
	}

	this->DrawFormat(eWhite, 300, 325, 50, 3, gCustomMessage.GetMessage(36));
	this->DrawFormat(eBlowPink, 300, 335, 50, 3, "#%d",this->LuckyTicketID);
	}
	pDrawGUI(0x7EC5,415,30,36,29);
	if( this->IsWorkZone2(LUCKYNUMBER_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[LUCKYNUMBER_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(LUCKYNUMBER_CLOSE, this->Data[LUCKYNUMBER_CLOSE].X, this->Data[LUCKYNUMBER_CLOSE].Y, Color);
	}
}
void Interface::EventLuckyNumber_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eLuckyMain].OnShow )
	{
		return;
	}
	
	if (this->IsWorkZone2(eLuckyButtonA))
	{
	DWORD Delay = (CurrentTick - this->Data[eLuckyButtonA].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eLuckyButtonA].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eLuckyButtonA].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eLuckyButtonA].EventTick = GetTickCount();
	if(this->LuckyLines <= 1){return;}else{
		this->LuckyLines	-=	1;}
	}

	else if (this->IsWorkZone2(eLuckyButtonB))
	{
	DWORD Delay = (CurrentTick - this->Data[eLuckyButtonB].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eLuckyButtonB].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eLuckyButtonB].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eLuckyButtonB].EventTick = GetTickCount();
	if(this->LuckyLines >= 5){return;}else{
		this->LuckyLines	+=	1;}
	}
	else if (this->IsWorkZone2(eLuckyStart))
	{
	DWORD Delay = (CurrentTick - this->Data[eLuckyStart].EventTick);

	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eLuckyStart].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----
	this->Data[eLuckyStart].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 1500)
	{
		return;
	}
	// ----
	this->Data[eLuckyStart].EventTick = GetTickCount();
	StartLucky(LuckyLines);
	this->LuckyLastLines = this->LuckyLines;
	time_t TimeLocal;
	struct tm * LocalT;
	time(&TimeLocal);
    // ----
	LocalT = localtime(&TimeLocal);
    // ----
	//this->LuckyDrawDate = "%2d:%02d:%02d",LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec;
    sprintf (this->LuckyDrawDate, "%2d:%02d:%02d", LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec);
	//Font[TAHOMA_BOLD_14]->DrawText(15, 460, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, ServerTime);
	}
	else if (this->IsWorkZone2(LUCKYNUMBER_CLOSE))
	{
	DWORD Delay = (CurrentTick - this->Data[LUCKYNUMBER_CLOSE].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[LUCKYNUMBER_CLOSE].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[LUCKYNUMBER_CLOSE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[LUCKYNUMBER_CLOSE].EventTick = GetTickCount();
	this->CloseLuckyNumberWindow();
	}
}

/*
void Interface::DrawGamblingPanel()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(MoveList) ||
		this->CheckWindow(SkillTree))
		return;
	if (!this->ShowExtraPanel)
	{
		return;
	}

	pDrawImage(iGfxDialoge, 1, 7, 223, 280, 1, 1, 1.0, 1.0, 1, 1, 0);
	pDrawImage(iNewuiDialogHr, 1, 235, 210, 10, 1, 1, 1.0, 1.0, 1, 1, 0);

	this->DrawFormat(eGold, 1 , 27, 223, 3, gCustomMessage.GetMessage(45));
	if(this->m_RolltheDiceButton == 1)
	{
		pDrawButton(iGfxBtn, 10, 70, 64.0, 29.0, 0, 0); //80 150 || 130 190
		if (this->IsWorkZone2(eEmptySmall1))
		{
			float PosZ = 30.0f;
			if (this->Data[eEmptySmall1].OnClick)
			{
				PosZ = 60.0f;
			}
			pDrawButton(iGfxBtn, 10, 70, 64.0, 29.0, 0, PosZ);

		}
		this->DrawFormat(eWhite, 12, 79, 64, 3, gCustomMessage.GetMessage(46));
	}
	//-
	if(this->m_HeadsTailsButton == 1)
	{
		pDrawButton(iGfxBtn, 80, 70, 64.0, 29.0, 0, 0);
		if (this->IsWorkZone2(eEmptySmall2))
		{
			float PosZ = 30.0f;
			if (this->Data[eEmptySmall2].OnClick)
			{
				PosZ = 60.0f;
			}
			pDrawButton(iGfxBtn, 80, 70, 64.0, 29.0, 0, PosZ);
		}
		this->DrawFormat(eWhite, 82, 79, 64, 3, gCustomMessage.GetMessage(47));
	}
	//-
	if(this->m_LuckyNumberButton == 1)
	{
		pDrawButton(iGfxBtn, 150, 70, 64.0, 29.0, 0, 0);
		if (this->IsWorkZone2(eEmptySmall3))
		{
			float PosZ = 30.0f;
			if (this->Data[eEmptySmall3].OnClick)
			{
				PosZ = 60.0f;
			}
			pDrawButton(iGfxBtn, 150, 70, 64.0, 29.0, 0, PosZ);
		}
		this->DrawFormat(eWhite, 152, 79, 64, 3, gCustomMessage.GetMessage(48));
	}

	if(this->m_SmithItemButton == 1)
	{
		pDrawButton(iGfxBtn, 10, 130, 64.0, 29.0, 0, 0);
		if (this->IsWorkZone2(eEmptySmall5))
		{
			float PosZ = 30.0f;
			if (this->Data[eEmptySmall5].OnClick)
			{
				PosZ = 60.0f;
			}
			pDrawButton(iGfxBtn, 10, 130, 64.0, 29.0, 0, PosZ);

		}
		this->DrawFormat(eWhite, 12, 139, 64, 3, gCustomMessage.GetMessage(58));
	}
	//-
	if(this->m_TitleManagerButton == 1)
	{
		pDrawButton(iGfxBtn, 80, 130, 64.0, 29.0, 0, 0);
		if (this->IsWorkZone2(eEmptySmall6))
		{
			float PosZ = 30.0f;
			if (this->Data[eEmptySmall6].OnClick)
			{
				PosZ = 60.0f;
			}
			pDrawButton(iGfxBtn, 80, 130, 64.0, 29.0, 0, PosZ);
		}
		this->DrawFormat(eWhite, 82, 139, 64, 3, gCustomMessage.GetMessage(49));
	}
	//-
	if(this->m_PartySearchSettingButton == 1)
	{
		pDrawButton(iGfxBtn, 150, 130, 64.0, 29.0, 0, 0);
		if (this->IsWorkZone2(eEmptySmall7))
		{
			float PosZ = 30.0f;
			if (this->Data[eEmptySmall7].OnClick)
			{
				PosZ = 60.0f;
			}
			pDrawButton(iGfxBtn, 150, 130, 64.0, 29.0, 0, PosZ);
		}
		this->DrawFormat(eWhite, 150, 139, 64, 3, gCustomMessage.GetMessage(95));
	}

	//-
	if(this->m_OffAttackButton == 1)
	{
		pDrawButton(iGfxBtn, 10, 190, 64.0, 29.0, 0, 0);
		if (this->IsWorkZone2(eEmptySmall8))
		{
			float PosZ = 30.0f;
			if (this->Data[eEmptySmall8].OnClick)
			{
				PosZ = 60.0f;
			}
			pDrawButton(iGfxBtn, 10, 190, 64.0, 29.0, 0, PosZ);
		}
		this->DrawFormat(eWhite, 10, 199, 64, 3, "OffAttack");
	}

	//-
	if(this->m_BuyVipButton == 1)
	{
		pDrawButton(iGfxBtn, 80, 190, 64.0, 29.0, 0, 0);
		if (this->IsWorkZone2(eEmptySmall9))
		{
			float PosZ = 30.0f;
			if (this->Data[eEmptySmall9].OnClick)
			{
				PosZ = 60.0f;
			}
			pDrawButton(iGfxBtn, 80, 190, 64.0, 29.0, 0, PosZ);
		}
		this->DrawFormat(eWhite, 80, 199, 64, 3, "Vip System");
	}
	//-
	if(this->m_ChangeClassButton == 1)
	{
		pDrawButton(iGfxBtn, 150, 190, 64.0, 29.0, 0, 0);
		if (this->IsWorkZone2(eEmptySmall10))
		{
			float PosZ = 30.0f;
			if (this->Data[eEmptySmall10].OnClick)
			{
				PosZ = 60.0f;
			}
			pDrawButton(iGfxBtn, 150, 190, 64.0, 29.0, 0, PosZ);
		}
		this->DrawFormat(eWhite, 150, 199, 64, 3, "Change Class");
	}
	//----Close
	 pDrawButton(iGfxBtnSmall2,90,250,52,22,0,0);
	 if(this->IsWorkZone2(eEmptySmall4))
		{
			float Z = 23.0;
			if(this->Data[eEmptySmall4].OnClick)
			{
				Z = 46.0;
			}
			 pDrawButton(iGfxBtnSmall2,90,250,52,22,0,Z);
		}
	this->DrawFormat(eWhite,90,255,52,3,gCustomMessage.GetMessage(14));
}
void Interface::EventGamblingPanel(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if(!this->ShowExtraPanel)
	{
		return;
	}
	if (this->m_RolltheDiceButton == 1)
	{
		if (this->IsWorkZone2(eEmptySmall1))
		{
			DWORD Delay = (CurrentTick - this->Data[eEmptySmall1].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eEmptySmall1].OnClick = true;
				pSetCursorFocus = true;
				return;
			}

			this->Data[eEmptySmall1].OnClick = false;
			pSetCursorFocus = false;

			if (Delay < 500)
			{
				return;
			}

			this->Data[eEmptySmall1].EventTick = GetTickCount();
			this->CloseGamblingPanel();
			this->CloseHeadsTailsWindow();
			this->CloseLuckyNumberWindow();
			this->OpenRolltheDiceWindow();
		}
	}
	if(this->m_HeadsTailsButton == 1)
	{
		if(this->IsWorkZone2(eEmptySmall2))
		{
			DWORD Delay = (CurrentTick - this->Data[eEmptySmall2].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eEmptySmall2].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eEmptySmall2].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eEmptySmall2].EventTick = GetTickCount();
			// ----
			this->CloseGamblingPanel();
			this->CloseRolltheDiceWindow();
			this->CloseLuckyNumberWindow();
			this->OpenHeadsTailsWindow();
		}
	}
	if(this->m_LuckyNumberButton == 1)
	{
		if(this->IsWorkZone2(eEmptySmall3))
		{
			DWORD Delay = (CurrentTick - this->Data[eEmptySmall3].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eEmptySmall3].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eEmptySmall3].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eEmptySmall3].EventTick = GetTickCount();
			// ----
			this->CloseGamblingPanel();
			this->CloseRolltheDiceWindow();
			this->CloseHeadsTailsWindow();
			this->OpenLuckyNumberWindow();
		}
	}
	if (this->m_TitleManagerButton == 1)
	{
		if (this->IsWorkZone2(eEmptySmall6))
		{
		DWORD Delay = (CurrentTick - this->Data[eEmptySmall6].EventTick);
		// ----
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eEmptySmall6].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----

		this->Data[eEmptySmall6].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eEmptySmall6].EventTick = GetTickCount();
		this->CloseGamblingPanel();
		this->OpenTitleSystemWindow();
		this->CloseHeadsTailsWindow();
		this->CloseLuckyNumberWindow();
		this->CloseRolltheDiceWindow();
		//this->CloseSmithItemWindow();
		}
	}
	if (this->m_SmithItemButton == 1)
	{
		if (this->IsWorkZone2(eEmptySmall5))
		{
		DWORD Delay = (CurrentTick - this->Data[eEmptySmall5].EventTick);
		// ----
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eEmptySmall5].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----

		this->Data[eEmptySmall5].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eEmptySmall5].EventTick = GetTickCount();
		this->CloseGamblingPanel();
		this->CloseHeadsTailsWindow();
		this->CloseLuckyNumberWindow();
		this->CloseRolltheDiceWindow();
		this->CloseTitleSystemWindow();
		gSmithy.SwitchSmithyWindowState();
		}
	}
	if (this->m_PartySearchSettingButton == 1)
	{
		if (this->IsWorkZone2(eEmptySmall7))
		{
		DWORD Delay = (CurrentTick - this->Data[eEmptySmall7].EventTick);
		// ----
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eEmptySmall7].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----

		this->Data[eEmptySmall7].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eEmptySmall7].EventTick = GetTickCount();
		gInterface.SwitchPartySettingsWindowState();
		this->CloseGamblingPanel();
		this->CloseTitleSystemWindow();
		this->CloseHeadsTailsWindow();
		this->CloseLuckyNumberWindow();
		this->CloseRolltheDiceWindow();
		//this->CloseSmithItemWindow();
		}
	}

	if (this->m_OffAttackButton == 1)
	{
		if (this->IsWorkZone2(eEmptySmall8))
		{
		DWORD Delay = (CurrentTick - this->Data[eEmptySmall8].EventTick);
		// ----
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eEmptySmall8].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----

		this->Data[eEmptySmall8].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eEmptySmall8].EventTick = GetTickCount();
		this->CloseGamblingPanel();
		this->CloseTitleSystemWindow();
		this->CloseHeadsTailsWindow();
		this->CloseLuckyNumberWindow();
		this->CloseRolltheDiceWindow();
		gInterface.SwitchOffExpWindoState();
		}
	}

	if (this->m_BuyVipButton == 1)
	{
		if (this->IsWorkZone2(eEmptySmall9))
		{
		DWORD Delay = (CurrentTick - this->Data[eEmptySmall9].EventTick);
		// ----
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eEmptySmall9].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----

		this->Data[eEmptySmall9].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eEmptySmall9].EventTick = GetTickCount();
		this->CloseGamblingPanel();
		this->CloseTitleSystemWindow();
		this->CloseHeadsTailsWindow();
		this->CloseLuckyNumberWindow();
		this->CloseRolltheDiceWindow();
		gInterface.BuyVipWindowState();
		}
	}

	if (this->m_ChangeClassButton == 1)
	{
		if (this->IsWorkZone2(eEmptySmall10))
		{
		DWORD Delay = (CurrentTick - this->Data[eEmptySmall10].EventTick);
		// ----
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eEmptySmall10].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----

		this->Data[eEmptySmall10].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eEmptySmall10].EventTick = GetTickCount();
		this->CloseGamblingPanel();
		this->CloseTitleSystemWindow();
		this->CloseHeadsTailsWindow();
		this->CloseLuckyNumberWindow();
		this->CloseRolltheDiceWindow();
		gInterface.ChangingClassWindowState();
		}
	}

	if(this->IsWorkZone2(eEmptySmall4))
	{
		DWORD Delay = (CurrentTick - this->Data[eEmptySmall4].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eEmptySmall4].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eEmptySmall4].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eEmptySmall4].EventTick = GetTickCount();
		// ----
		this->CloseGamblingPanel();
	}
}

*/
void Interface::DrawTitleManagerButton()
{
	
	if(this->CheckWindow(Character))
	{
		this->DrawFormat(eWhite, 447, 374, 150, 3, "Create: %d/%d | Decrease: %d/%d",gObjUser.lpPlayer->FruitAddPoint,gObjUser.lpPlayer->MaxFruitAddPoint,gObjUser.lpPlayer->FruitSubPoint,gObjUser.lpPlayer->MaxFruitSubPoint);
	}
}
void Interface::EventTitleManagerButton_Main(DWORD Event)
{
	/*
	DWORD CurrentTick = GetTickCount();
	if(this->CheckWindow(Character))
	{
	if (this->IsWorkZone2(eTitleManagerButton))
	{
	DWORD Delay = (CurrentTick - this->Data[eTitleManagerButton].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eTitleManagerButton].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eTitleManagerButton].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eTitleManagerButton].EventTick = GetTickCount();
	this->OpenTitleSystemWindow();
	this->CloseHeadsTailsWindow();
	this->CloseLuckyNumberWindow();
	this->CloseRolltheDiceWindow();
	this->CloseSmithItemWindow();
	}
	else if (this->IsWorkZone2(eSmithItemButton))
	{
	DWORD Delay = (CurrentTick - this->Data[eSmithItemButton].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eSmithItemButton].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[eSmithItemButton].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[eSmithItemButton].EventTick = GetTickCount();
	this->OpenSmithItemWindow();
	this->CloseHeadsTailsWindow();
	this->CloseLuckyNumberWindow();
	this->CloseRolltheDiceWindow();
	this->CloseTitleSystemWindow();
	}
	}
	if(this->CheckWindow(CommandWindow))
	{
	if (this->IsWorkZone2(ePartySearchButton))
	{
	DWORD Delay = (CurrentTick - this->Data[ePartySearchButton].EventTick);
	// ----
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[ePartySearchButton].OnClick = true;
		pSetCursorFocus = true;
		return;
	}
	// ----

	this->Data[ePartySearchButton].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->Data[ePartySearchButton].EventTick = GetTickCount();
	gInterface.SwitchPartySettingsWindowState();
	this->CloseTitleSystemWindow();
	this->CloseHeadsTailsWindow();
	this->CloseLuckyNumberWindow();
	this->CloseRolltheDiceWindow();
	this->CloseSmithItemWindow();
	}
	}
	*/
}
/*
void Interface::DrawSmithItem()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Warehouse) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse))
		return;

	if( !this->Data[eSMITH_MAIN].OnShow )
	{
		return;
	}
	// ----
	float MainWidth			= 230.0f;
	float MainHeight		= 313.0f;
	float StartY			= 100.0f;
	float StartX			= (MAX_WIN_WIDTH / 2.0f) - (MainWidth / 2.0f);
	float MainCenter		= StartX + (MainWidth / 3.0f);
	float ButtonX			= MainCenter - (29.0f / 2.0f);
	// ----
	this->DrawGUI(eSMITH_MAIN, StartX, StartY - 78);
	this->DrawGUI(eSMITH_TITLE, StartX, StartY - 80);
	StartY = this->DrawRepeatGUI(eSMITH_FRAME, StartX, StartY - 13.0, 13);
	this->DrawGUI(eSMITH_FOOTER, StartX, StartY + 80);
	pDrawGUI(0x7A7B, StartX, 275, 5, 100); //
	pDrawGUI(0x7A7B, StartX + 221, 276, 5, 100); //
	this->DrawGUI(eSMITH_CLOSE, StartX + MainWidth - this->Data[eSMITH_CLOSE].Width, this->Data[eSMITH_TITLE].Height + this->Data[eSMITH_CLOSE].Height - 78);
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 95, 30, Fcolor->Gold, Fcolor->Trans, 25, (LPINT)5, gCustomMessage.GetMessage(58));
	// ----
	if( this->IsWorkZone2(eSMITH_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eSMITH_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eSMITH_CLOSE, this->Data[eSMITH_CLOSE].X, this->Data[eSMITH_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eSMITH_CLOSE].X + 5, this->Data[eSMITH_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
	}
	this->DrawFormat(eGold, StartX + 30, 50, 210, 1, gCustomMessage.GetMessage(59));
	pDrawGUI(0x7C0D, StartX + 15, 70, 16, 15); //
	pDrawGUI(0x7AA4, StartX + 73, 70, 16, 15); //
	switch (gSmithItem.ItemType)
	{
	case 0:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(60));
		break;
	case 1:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(61));
		break;
	case 2:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(62));
		break;
	case 3:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(63));
		break;
	case 4:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(64));
		break;
	case 5:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(65));
		break;
	case 6:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(66));
		break;
	case 7:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(67));
		break;
	case 8:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(68));
		break;
	case 9:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(69));
		break;
	case 10:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(70));
		break;
	case 11:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(71));
		break;
	}
	this->DrawFormat(eGold, StartX + 160, 50, 210, 1, gCustomMessage.GetMessage(72));
	pDrawGUI(0x7C0D, StartX + 140, 70, 16, 15); //
	pDrawGUI(0x7AA4, StartX + 193, 70, 16, 15); //
	switch (gSmithItem.Days)
	{
	case 0:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 163, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(73));
		break;
	case 1:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 163, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(74));
		break;
	case 2:
		Font[TAHOMA_BOLD_13]->DrawText(StartX + 163, 73, Fcolor->White, Fcolor->Red, 25, (LPINT)5, gCustomMessage.GetMessage(75));
		break;
	}
	//
	pDrawGUI(0x79A2, StartX + 27, 100, 171, 23); //
	pDrawGUI(0x7BAA, StartX + 8, 103, 17, 18);
	pDrawGUI(0x7BAB, StartX + 200, 103, 17, 18);
	switch(gSmithItem.ItemType)
	{
	case 0:
		DrawItem2(StartX + 40,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 1:
		DrawItem2(StartX + 40,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 2:
		DrawItem2(StartX + 40,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 3:
		DrawItem2(StartX + 55,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 4:
		DrawItem2(StartX + 65,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 5:
		DrawItem2(StartX + 55,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 6:
		DrawItem2(StartX + 65,20,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 7:
		DrawItem2(StartX + 65,10,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 8:
		DrawItem2(StartX + 65,15,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 9:
		DrawItem2(StartX + 65,5,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 10:
		DrawItem2(StartX + 65,5,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].ItemName);
		break;
	case 11:
		DrawItem2(StartX + 65,5,100,100,ITEM(gSmithItem.ItemType,gSmithItem.ItemIndex),gSmithItem.mLevel,gSmithItem.mExc,0,0);
		Font[TAHOMA_BOLD_15]->DrawText(StartX + 35, 106, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, "%s",gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].ItemName);
		break;
	}

	//
	this->DrawGUI(eSMITH_DIV, StartX, 130);
	// ----
	for( int i = 0; i < 10; i++ )
	{
		pDrawGUI(iOptionDot,StartX + 15,147 + (20 * i) + 9,10,10);
		pDrawGUI(0x7B5E, StartX + 30, 160 + (20 * i) + 9, 82.0, 2.0);
		pDrawGUI(0x7B5E, StartX + 30 + 82, 160 + (20 * i) + 9, 82.0, 2.0);
	}
	//Level
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 155, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(76));
	pDrawGUI(0x7C0D, StartX + 140, 153, 16, 15); //
	pDrawGUI(0x7AA4, StartX + 180, 153, 16, 15); //
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 155, 155, Fcolor->White, Fcolor->Red, 25, (LPINT)5, "     %d",gSmithItem.mLevel);
	//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 156, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,"%d", gSmithItem.pLevel * gSmithItem.mLevel);
	//Skill
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 175, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(77));
	pDrawButton(iOptionCheck,StartX + 180,175,15,15,0,15);
	if(gSmithItem.mSkill == 1)
	{
		//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 176, Fcolor->Red, Fcolor->Trans, 25, (LPINT)5, "%d",gSmithItem.pSkill);
		pDrawButton(iOptionCheck,StartX + 180,175,15,15,0,0);
	}
	//Luck
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 195, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(78));
	pDrawButton(iOptionCheck,StartX + 180,195,15,15,0,15);
	if(gSmithItem.mLuck == 1)
	{
		//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 196, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,"%d", gSmithItem.pLuck);
		pDrawButton(iOptionCheck,StartX + 180,195,15,15,0,0);
	}
	//Option(Life)
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 215, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(79));
	pDrawGUI(0x7C0D, StartX + 140, 213, 16, 15); //
	pDrawGUI(0x7AA4, StartX + 180, 213, 16, 15); //
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 155, 215, Fcolor->White, Fcolor->Red, 25, (LPINT)5, "     %d",gSmithItem.mOpt);
	//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 215, Fcolor->Red, Fcolor->Trans, 25, (LPINT)5, "%d",gSmithItem.pOpt * gSmithItem.mOpt);
	//
	if(gSmithItem.ItemType <= 5)
	{
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 235, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(80));
	pDrawButton(iOptionCheck,StartX + 180,235,15,15,0,15);
	if(gSmithItem.ExcOption == 32)
	{
		//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 236, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,"%d", gSmithItem.pExc);
		pDrawButton(iOptionCheck,StartX + 180,235,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 255, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(81));
	pDrawButton(iOptionCheck,StartX + 180,255,15,15,0,15);
	if(gSmithItem.ExcOption1 == 16)
	{
		//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 256, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,"%d", gSmithItem.pExc1);
		pDrawButton(iOptionCheck,StartX + 180,255,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 275, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(82));
	pDrawButton(iOptionCheck,StartX + 180,275,15,15,0,15);

	if(gSmithItem.ExcOption2 == 8)
	{
		//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 276, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,"%d", gSmithItem.pExc2);
		pDrawButton(iOptionCheck,StartX + 180,275,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 295, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(83));
	pDrawButton(iOptionCheck,StartX + 180,295,15,15,0,15);
	if(gSmithItem.ExcOption3 == 4)
	{
		//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 296, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,"%d", gSmithItem.pExc3);
		pDrawButton(iOptionCheck,StartX + 180,295,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 315, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(84));
	pDrawButton(iOptionCheck,StartX + 180,315,15,15,0,15);
	if(gSmithItem.ExcOption4 == 2)
	{
		//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 316, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,"%d", gSmithItem.pExc4);
		pDrawButton(iOptionCheck,StartX + 180,315,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 335, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(85));
	pDrawButton(iOptionCheck,StartX + 180,335,15,15,0,15);
	if(gSmithItem.ExcOption5 == 1)
	{
		//Font[TAHOMA_BOLD_13]->DrawText(StartX + 200, 336, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,"%d", gSmithItem.pExc5);
		pDrawButton(iOptionCheck,StartX + 180,335,15,15,0,0);
	}
	}
	if(gSmithItem.ItemType >= 6)
	{
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 235, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(86));
	pDrawButton(iOptionCheck,StartX + 180,235,15,15,0,15);
	if(gSmithItem.ExcOption == 32)
	{
		pDrawButton(iOptionCheck,StartX + 180,235,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 255, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(87));
	pDrawButton(iOptionCheck,StartX + 180,255,15,15,0,15);
	if(gSmithItem.ExcOption1 == 16)
	{
		pDrawButton(iOptionCheck,StartX + 180,255,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 275, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(88));
	pDrawButton(iOptionCheck,StartX + 180,275,15,15,0,15);
	if(gSmithItem.ExcOption2 == 8)
	{
		pDrawButton(iOptionCheck,StartX + 180,275,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 295, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(89));
	pDrawButton(iOptionCheck,StartX + 180,295,15,15,0,15);
	if(gSmithItem.ExcOption3 == 4)
	{
		pDrawButton(iOptionCheck,StartX + 180,295,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 315, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(90));
	pDrawButton(iOptionCheck,StartX + 180,315,15,15,0,15);
	if(gSmithItem.ExcOption4 == 2)
	{
		pDrawButton(iOptionCheck,StartX + 180,315,15,15,0,0);
	}
	//
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 40, 335, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(91));
	pDrawButton(iOptionCheck,StartX + 180,335,15,15,0,15);
	if(gSmithItem.ExcOption5 == 1)
	{
		pDrawButton(iOptionCheck,StartX + 180,335,15,15,0,0);
	}
	}
	// ----
	this->DrawGUI(eSMITH_DIV, StartX, this->Data[eSMITH_FOOTER].Y - 15);
	// ----
	this->DrawGUI(eSMITH_BUY, ButtonX, this->Data[eSMITH_FOOTER].Y + 10);
	Font[TAHOMA_BOLD_17]->DrawText(StartX + 105, this->Data[eSMITH_FOOTER].Y + 15, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(52));
		if( IsWorkZone(eSMITH_BUY) )
		{
			DWORD Color = eGray100;
			// ----
			if( this->Data[eSMITH_BUY].OnClick )
			{
				Color = eGray150;
			}
			// ----
			this->DrawColoredGUI(eSMITH_BUY, this->Data[eSMITH_BUY].X, this->Data[eSMITH_BUY].Y, Color);
		}
	//pDrawGUI(0x7BAA, StartX + 30, this->Data[eSMITH_FOOTER].Y + 5, 17, 18); <
	//pDrawGUI(0x7BAB, StartX + 178, this->Data[eSMITH_FOOTER].Y + 5, 17, 18); >
	if( gSmithItem.ItemType == 0)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithSwordInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	else if( gSmithItem.ItemType == 1)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithAxeInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 2)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithMaceInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 3)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithSpearInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 4)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithBowInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 5)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithStaffInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 6)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithShieldInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 7)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithHelmInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 8)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithArmorInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 9)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithPantInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 10)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithGloveInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
	if( gSmithItem.ItemType == 11)
	{
		switch(gSmithItem.Days)
			{
				case 0:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price1Days + gSmithItem.TotalPrice);
				break;
				case 1:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price7Days + gSmithItem.TotalPrice);
				break;
				case 2:
					Font[TAHOMA_BOLD_13]->DrawText(StartX + 150, 106, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5,gCustomMessage.GetMessage(92), gCustomSmith.m_SmithBootInfo[gSmithItem.ItemIndex].Price30Days + gSmithItem.TotalPrice);
				break;
			}
	}
}
void Interface::EventSmithItem_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	if( !this->Data[eSMITH_MAIN].OnShow )
	{
		return;
	}
	if (this->IsWorkZone2(eSMITH_SKILL))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_SKILL].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_SKILL].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_SKILL].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_SKILL].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_SKILL_1].OnShow)
		{
			this->Data[eSMITH_SKILL_1].OnShow = true;
			gSmithItem.mSkill = 1;
			gSmithItem.TotalPrice += gSmithItem.pSkill;
		}
		else {
			this->Data[eSMITH_SKILL_1].OnShow = false;
			gSmithItem.mSkill = 0;
			gSmithItem.TotalPrice -= gSmithItem.pSkill;
		}
	}
	else if (this->IsWorkZone2(eSMITH_LUCK))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_LUCK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_LUCK].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_LUCK].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_LUCK].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_LUCK_1].OnShow)
		{
			this->Data[eSMITH_LUCK_1].OnShow = true;
			gSmithItem.mLuck = 1;
			gSmithItem.TotalPrice += gSmithItem.pLuck;
		}
		else {
			this->Data[eSMITH_LUCK_1].OnShow = false;
			gSmithItem.mLuck = 0;
			gSmithItem.TotalPrice -= gSmithItem.pLuck;
		}
	}
	else if (this->IsWorkZone2(eSMITH_EXC))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC_1].OnShow)
		{
			this->Data[eSMITH_EXC_1].OnShow = true;
			gSmithItem.ExcOption = 32;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc;
		}
		else {
			this->Data[eSMITH_EXC_1].OnShow = false;
			gSmithItem.ExcOption = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc;
		}
	}
	else if (this->IsWorkZone2(eSMITH_EXC1))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC1].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC1].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC1].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC1_1].OnShow)
		{
			this->Data[eSMITH_EXC1_1].OnShow = true;
			gSmithItem.ExcOption1 = 16;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc1;
		}
		else {
			this->Data[eSMITH_EXC1_1].OnShow = false;
			gSmithItem.ExcOption1 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc1;
		}
	}
	else if (this->IsWorkZone2(eSMITH_EXC2))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC2].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC2].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC2].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC2].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC2_1].OnShow)
		{
			this->Data[eSMITH_EXC2_1].OnShow = true;
			gSmithItem.ExcOption2 = 8;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc2;
		}
		else {
			this->Data[eSMITH_EXC2_1].OnShow = false;
			gSmithItem.ExcOption2 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc2;
		}
	}
	else if (this->IsWorkZone2(eSMITH_EXC3))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC3].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC3].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC3].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC3].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC3_1].OnShow)
		{
			this->Data[eSMITH_EXC3_1].OnShow = true;
			gSmithItem.ExcOption3 = 4;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc3;
		}
		else {
			this->Data[eSMITH_EXC3_1].OnShow = false;
			gSmithItem.ExcOption3 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc3;
		}
	}
	else if (this->IsWorkZone2(eSMITH_EXC4))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC4].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC4].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC4].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC4].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC4_1].OnShow)
		{
			this->Data[eSMITH_EXC4_1].OnShow = true;
			gSmithItem.ExcOption4 = 2;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc4;
		}
		else {
			this->Data[eSMITH_EXC4_1].OnShow = false;
			gSmithItem.ExcOption4 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc4;
		}
	}
	else if (this->IsWorkZone2(eSMITH_EXC5))
	{
		DWORD Delay = (CurrentTick - this->Data[eSMITH_EXC5].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_EXC5].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSMITH_EXC5].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSMITH_EXC5].EventTick = GetTickCount();
		// ----
		if (!this->Data[eSMITH_EXC5_1].OnShow)
		{
			this->Data[eSMITH_EXC5_1].OnShow = true;
			gSmithItem.ExcOption5 = 1;
			gSmithItem.mExc += 1;
			gSmithItem.TotalPrice += gSmithItem.pExc5;
		}
		else {
			this->Data[eSMITH_EXC5_1].OnShow = false;
			gSmithItem.ExcOption5 = 0;
			gSmithItem.mExc -= 1;
			gSmithItem.TotalPrice -= gSmithItem.pExc5;
		}
	}
	else if (this->IsWorkZone2(eSMITH_LEVEL))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_LEVEL].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_LEVEL].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_LEVEL].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_LEVEL].EventTick = GetTickCount();
	if(gSmithItem.mLevel <= 0)
	{return;}
	else
	{
		gSmithItem.mLevel	-=	1;
		gSmithItem.TotalPrice -= gSmithItem.pLevel;
	}
	}
	else if (this->IsWorkZone2(eSMITH_LEVEL_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_LEVEL_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_LEVEL_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_LEVEL_1].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_LEVEL_1].EventTick = GetTickCount();
	if(gSmithItem.mLevel >= gSmithItem.MaxLevel)
	{return;}
	else
	{
		gSmithItem.mLevel	+=	1;
		gSmithItem.TotalPrice += gSmithItem.pLevel;
	}
	}
	else if (this->IsWorkZone2(eSMITH_OPT))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_OPT].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_OPT].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_OPT].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_OPT].EventTick = GetTickCount();
	if(gSmithItem.mOpt <= 0)
	{return;}
	else
	{
		gSmithItem.mOpt	-=	1;
		gSmithItem.TotalPrice -= gSmithItem.pOpt;
	}
	}
	else if (this->IsWorkZone2(eSMITH_OPT_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_OPT_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_OPT_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_OPT_1].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_OPT_1].EventTick = GetTickCount();
	if(gSmithItem.mOpt >= gSmithItem.MaxOpt)
	{return;}
	else
	{
		gSmithItem.mOpt	+=	1;
		gSmithItem.TotalPrice += gSmithItem.pOpt;
	}
	}
	else if (this->IsWorkZone2(eSMITH_ITEMTYPE))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_ITEMTYPE].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_ITEMTYPE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_ITEMTYPE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_ITEMTYPE].EventTick = GetTickCount();
	if(gSmithItem.ItemType <= 0)
	{return;}
	else
	{
		gSmithItem.ItemType	-=	1;
		gSmithItem.ItemIndex = 0;
	}
	}
	else if (this->IsWorkZone2(eSMITH_ITEMTYPE_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_ITEMTYPE_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_ITEMTYPE_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_ITEMTYPE_1].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_ITEMTYPE_1].EventTick = GetTickCount();
	if(gSmithItem.ItemType >= 11)
	{return;}
	else
	{gSmithItem.ItemType	+=	1;
	gSmithItem.ItemIndex = 0;}
	}
	else if (this->IsWorkZone2(eSMITH_DAYS))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_DAYS].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_DAYS].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_DAYS].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_DAYS].EventTick = GetTickCount();
	if(gSmithItem.Days <= 0)
	{return;}
	else
	{gSmithItem.Days	-=	1;}
	}
	else if (this->IsWorkZone2(eSMITH_DAYS_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_DAYS_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_DAYS_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_DAYS_1].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_DAYS_1].EventTick = GetTickCount();
	if(gSmithItem.Days >= 2)
	{return;}
	else
	{gSmithItem.Days	+=	1;}
	}
	else if (this->IsWorkZone2(eSMITH_ITEMINDEX))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_ITEMINDEX].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_ITEMINDEX].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_ITEMINDEX].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_ITEMINDEX].EventTick = GetTickCount();

	if(gSmithItem.ItemIndex <= 0 )
	{return;}

	if (gSmithItem.ItemType == 0)
	{
		if(gSmithItem.ItemIndex == 31)
		{
			gSmithItem.ItemIndex -=	6;
		}
		else
			gSmithItem.ItemIndex -=	1;
	}
	else if (gSmithItem.ItemType == 2)
	{
		if(gSmithItem.ItemIndex == 18)
		{
			gSmithItem.ItemIndex -=	2;
		}
		else
			gSmithItem.ItemIndex -=	1;
	}
	else if(gSmithItem.ItemType == 4)
		{
			if(gSmithItem.ItemIndex == 8 ||
				gSmithItem.ItemIndex == 16||
				gSmithItem.ItemIndex == 24)
				{
				gSmithItem.ItemIndex -=	2;
				}
			else
				gSmithItem.ItemIndex -=	1;
		}
	else if(gSmithItem.ItemType == 7)
		{
			if(gSmithItem.ItemIndex == 16 ||
				gSmithItem.ItemIndex == 11 ||
				gSmithItem.ItemIndex == 24 ||
				gSmithItem.ItemIndex == 33 ||
				gSmithItem.ItemIndex == 38)	
				{
				gSmithItem.ItemIndex -=	2;
				}
			else
				gSmithItem.ItemIndex -=	1;
		}
	else
	{
		gSmithItem.ItemIndex	-=	1;
	}
	}
	else if (this->IsWorkZone2(eSMITH_ITEMINDEX_1))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_ITEMINDEX_1].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_ITEMINDEX_1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_ITEMINDEX_1].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 100)
		{
			return;
		}
	// ----
	this->Data[eSMITH_ITEMINDEX_1].EventTick = GetTickCount();
	if (gSmithItem.ItemType == 0)
	{
		if(gSmithItem.ItemIndex >= 35)
			return;

		if(gSmithItem.ItemIndex == 25)
		{
			gSmithItem.ItemIndex +=	6;
		}
		else
			gSmithItem.ItemIndex +=	1;
	}
	else if (gSmithItem.ItemType == 1)
	{
		if(gSmithItem.ItemIndex >= 8)
		{
			return;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if (gSmithItem.ItemType == 2)
	{
		if(gSmithItem.ItemIndex >= 18)
		{
			return;
		}
		if(gSmithItem.ItemIndex == 16)
		{
			gSmithItem.ItemIndex +=	2;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if (gSmithItem.ItemType == 3)
	{
		if(gSmithItem.ItemIndex >= 11)
		{
			return;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if(gSmithItem.ItemType == 4)
		{
			if(gSmithItem.ItemIndex >= 24)
			{
			return;
			}
			else if(gSmithItem.ItemIndex == 6 ||
				gSmithItem.ItemIndex == 14 ||
				gSmithItem.ItemIndex == 22)
				{
				gSmithItem.ItemIndex +=	2;
				}
			else
				gSmithItem.ItemIndex +=	1;
		}
	else if (gSmithItem.ItemType == 5)
	{
		if(gSmithItem.ItemIndex >= 23)
		{
			return;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if (gSmithItem.ItemType == 6)
	{
		if(gSmithItem.ItemIndex >= 16)
		{
			return;
		}
		else
		gSmithItem.ItemIndex +=	1;
	}
	else if(gSmithItem.ItemType == 7)
		{
			if(gSmithItem.ItemIndex >= 43)
			return;

			else if(gSmithItem.ItemIndex == 14 ||
				gSmithItem.ItemIndex == 19 ||
				gSmithItem.ItemIndex == 22 ||
				gSmithItem.ItemIndex == 31 ||
				gSmithItem.ItemIndex == 36)	
				{
				gSmithItem.ItemIndex +=	2;
				}
			else
				gSmithItem.ItemIndex +=	1;
		}
	else
	{
		if(gSmithItem.ItemIndex >= 43)
		return;
		gSmithItem.ItemIndex	+=	1;
	}
	}
	else if (this->IsWorkZone2(eSMITH_CLOSE))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_CLOSE].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_CLOSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_CLOSE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
		{
			return;
		}
	// ----
	this->Data[eSMITH_CLOSE].EventTick = GetTickCount();
	this->CloseSmithItemWindow();
	}
	else if (this->IsWorkZone2(eSMITH_BUY))
	{
	DWORD Delay = (CurrentTick - this->Data[eSMITH_BUY].EventTick);
	// ----
	if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSMITH_BUY].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
	// ----
	this->Data[eSMITH_BUY].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if (Delay < 500)
		{
			return;
		}
	// ----
	this->Data[eSMITH_BUY].EventTick = GetTickCount();
	if(gSmithItem.ItemType >= 7)
	{
		gSmithItem.mSkill = 0;
	}
	SDHP_BUYSVSHOP pMsg;
	pMsg.h.set(0xFB, 0x08, sizeof(pMsg));
	pMsg.ItemType = gSmithItem.ItemType;
	pMsg.ItemIndex = gSmithItem.ItemIndex;
	pMsg.Days	= gSmithItem.Days;
	pMsg.mLevel = gSmithItem.mLevel;
	pMsg.mSkill = gSmithItem.mSkill;
	pMsg.mLuck = gSmithItem.mLuck;
	pMsg.mOpt = gSmithItem.mOpt;
	pMsg.ExcOption = gSmithItem.ExcOption;
	pMsg.ExcOption1 = gSmithItem.ExcOption1;
	pMsg.ExcOption2 = gSmithItem.ExcOption2;
	pMsg.ExcOption3 = gSmithItem.ExcOption3;
	pMsg.ExcOption4 = gSmithItem.ExcOption4;
	pMsg.ExcOption5 = gSmithItem.ExcOption5;
	pMsg.mExc = gSmithItem.mExc;
	DataSend((BYTE*)&pMsg, pMsg.h.size);
	this->CloseSmithItemWindow();
	}
}
*/
// -----------
void Interface::SwitchPartySettingsWindowState()
{
	Data[ePARTYSETTINGS_MAIN].OnShow == true? Data[ePARTYSETTINGS_MAIN].Close():Data[ePARTYSETTINGS_MAIN].Open();
}

void Interface::DrawPartySettingsWindow()
{
	if( !this->Data[ePARTYSETTINGS_MAIN].OnShow )
	{
		return;
	}
	// ----
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 50.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(ePARTYSETTINGS_MAIN, StartX, StartY + 2);
	this->DrawGUI(ePARTYSETTINGS_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(ePARTYSETTINGS_FRAME, StartX, StartY + 67.0, 16);
	this->DrawGUI(ePARTYSETTINGS_FOOTER, StartX, StartY);
	this->DrawGUI(ePARTYSETTINGS_CLOSE, StartX + MainWidth - this->Data[ePARTYSETTINGS_CLOSE].Width + 2, 49);
	// ----
	if( this->IsWorkZone2(ePARTYSETTINGS_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[ePARTYSETTINGS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(ePARTYSETTINGS_CLOSE, this->Data[ePARTYSETTINGS_CLOSE].X, this->Data[ePARTYSETTINGS_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[ePARTYSETTINGS_CLOSE].X + 5, this->Data[ePARTYSETTINGS_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 60, 210, 3, gCustomMessage.GetMessage(95));
///////////////////////////////////////////ACTIVE SYSTEM///////////////////////////////////////////
	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 33, 200, 1, gCustomMessage.GetMessage(96));

	if (gPartySearchSettings.m_SystemActive == false)
	{
		pDrawButton(iOptionCheck,378,83,15,15,0,15);
		//this->DrawButton(ePARTYSETTINGS_SYSTEM_ACTIVE, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 30, 0, 0);
	}
	else
	{
		pDrawButton(iOptionCheck,378,83,15,15,0,0);
		//this->DrawButton(ePARTYSETTINGS_SYSTEM_ACTIVE, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 30, 0, 15);
	}
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSETTINGS_MAIN].Y + 40); // Äåëèòåëü áîëüøîé
/////////////////////////////////////////ACTIVE SYSTEM END/////////////////////////////////////////

/////////////////////////////////////////////MAX LEVEL/////////////////////////////////////////////
	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN]. Y + 60, 200, 1, gCustomMessage.GetMessage(97));
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSETTINGS_MAIN].Y + 67); // Äåëèòåëü áîëüøîé

	/*int x = GetPrivateProfileIntA("Graphics", "X", 0, "./Settings.ini");
	int y = GetPrivateProfileIntA("Graphics", "Y", 0, "./Settings.ini");
	int w = GetPrivateProfileIntA("Graphics", "W", 0, "./Settings.ini");
	int h = GetPrivateProfileIntA("Graphics", "H", 0, "./Settings.ini");*/
	this->DrawToolTip(StartX + 174, this->Data[ePARTYSETTINGS_MAIN].Y + 62, "%d", gPartySearchSettings.m_Level);

	if (gPartySearchSettings.m_SystemActive == 0)
	{
		this->DrawColoredButton(ePARTYSETTINGS_LEVEL_MINUS, StartX + 150, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0, eGray150); // 
	}
	else
	{
		pDrawGUI(0x7C0D, 355, 110, 16, 15); //
	}

	if (gPartySearchSettings.m_SystemActive == 0)
	{
		this->DrawColoredButton(ePARTYSETTINGS_LEVEL_PLUS, StartX + 193, this->Data[ePARTYSETTINGS_MAIN].Y + 57, 0, 0, eGray150); //
	}
	else
	{
		pDrawGUI(0x7AA4, 398, 110, 16, 15); //
	}

///////////////////////////////////////////MAX LEVEL END///////////////////////////////////////////

///////////////////////////////////////////////GUILD///////////////////////////////////////////////

	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 87, 200, 1, gCustomMessage.GetMessage(98));

	if (gPartySearchSettings.m_SystemActive)
	{
		if (gPartySearchSettings.m_OnlyGuild == false)
		{
			pDrawButton(iOptionCheck,378,135,15,15,0,15);
		}
		else
		{
			pDrawButton(iOptionCheck,378,135,15,15,0,0);
		}
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_ONLY_GUILD, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 83, 0, 30);
	}

	pDrawGUI(0x7B5E, StartX + 30, this->Data[ePARTYSETTINGS_MAIN].Y + 100, 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
	pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[ePARTYSETTINGS_MAIN].Y + 100, 82.0, 2.0); // Äåëèòåëü ìåëêèé 2

	this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 109, 200, 1, gCustomMessage.GetMessage(99));

	if (gPartySearchSettings.m_SystemActive)
	{
		if (gPartySearchSettings.m_OneClass == false)
		{
			pDrawButton(iOptionCheck,378,157,15,15,0,15);
		}
		else
		{
			pDrawButton(iOptionCheck,378,157,15,15,0,0);
		}
	}
	else
	{
		this->DrawButton(ePARTYSETTINGS_ONE_CLASS, ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 105, 0, 30);
	}

	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSETTINGS_MAIN].Y + 115);// 94 // Äåëèòåëü áîëüøîé
/////////////////////////////////////////////GUILD END/////////////////////////////////////////////
	char szCharNames[7][32];
	memcpy(szCharNames[0],pGetTextLine(pTextLineThis,20),sizeof(szCharNames[0]));
	memcpy(szCharNames[1],pGetTextLine(pTextLineThis,21),sizeof(szCharNames[1]));
	memcpy(szCharNames[2],pGetTextLine(pTextLineThis,22),sizeof(szCharNames[2]));
	memcpy(szCharNames[3],pGetTextLine(pTextLineThis,23),sizeof(szCharNames[3]));
	memcpy(szCharNames[4],pGetTextLine(pTextLineThis,24),sizeof(szCharNames[4]));
	memcpy(szCharNames[5],pGetTextLine(pTextLineThis,1687),sizeof(szCharNames[5]));
	memcpy(szCharNames[6],pGetTextLine(pTextLineThis,3150),sizeof(szCharNames[6]));

	int ObjectIDs[7] = 
	{ 
		ePARTYSETTINGS_DARK_WIZARD, 
		ePARTYSETTINGS_DARK_KNIGHT, 
		ePARTYSETTINGS_ELF, 
		ePARTYSETTINGS_MAGIC_GLADIATOR, 
		ePARTYSETTINGS_DARK_LORD, 
		ePARTYSETTINGS_SUMMONER, 
		ePARTYSETTINGS_RAGE_FIGHTER
	};

	for (int i = 0; i<7; i++)
	{
		this->DrawFormat(eWhite, StartX + 40, this->Data[ePARTYSETTINGS_MAIN].Y + 135 + (i * 22), 200, 1, szCharNames[i]);

		bool ClassValue = 0;
		switch (i)
		{
			case 0:
				ClassValue = gPartySearchSettings.m_DarkWizard;
				break;
			case 1:
				ClassValue = gPartySearchSettings.m_DarkKnight;
				break;
			case 2:
				ClassValue = gPartySearchSettings.m_Elf;
				break;
			case 3:
				ClassValue = gPartySearchSettings.m_MagicGladiator;
				break;
			case 4:
				ClassValue = gPartySearchSettings.m_DarkLord;
				break;
			case 5:
				ClassValue = gPartySearchSettings.m_Summoner;
				break;
			case 6:
				ClassValue = gPartySearchSettings.m_RageFighter;
				break;
		}

		if (gPartySearchSettings.m_SystemActive)
		{
			if (ClassValue == false)
			{
				pDrawButton(iOptionCheck,378,180 + (i * 23),15,15,0,15);
				//this->DrawButton(ObjectIDs[i], ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 131 + (i * 22), 0, 0);
			}
			else
			{
				pDrawButton(iOptionCheck,378,180 + (i * 23),15,15,0,0);
				//this->DrawButton(ObjectIDs[i], ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 131 + (i * 22), 0, 15);
			}
		}
		else
		{
			this->DrawButton(ObjectIDs[i], ButtonX + 110, this->Data[ePARTYSETTINGS_MAIN].Y + 131 + (i * 22), 0, 30);
		}

		pDrawGUI(0x7B5E, StartX + 30, this->Data[ePARTYSETTINGS_MAIN].Y + 148 + (i * 22), 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
		pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[ePARTYSETTINGS_MAIN].Y + 148 + (i * 22), 82.0, 2.0); // Äåëèòåëü ìåëêèé 2
	}

	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSETTINGS_MAIN].Y + 290); // Äåëèòåëü áîëüøîé

	//if (gPartySearchSettings.m_SystemActive)
	//{
		this->DrawButton(ePARTYSETTINGS_OK, StartX + this->Data[ePARTYSETTINGS_MAIN].Width/2-this->Data[ePARTYSETTINGS_OK].Width/2, this->Data[ePARTYSETTINGS_MAIN].Y + 310, 0, 0);

		if( this->IsWorkZone2(ePARTYSETTINGS_OK) )
		{
			int ScaleY = 30;
			// ----
			if( this->Data[ePARTYSETTINGS_OK].OnClick )
			{
				ScaleY = 60;
			}
			// ----
			this->DrawButton(ePARTYSETTINGS_OK, StartX + this->Data[ePARTYSETTINGS_MAIN].Width/2-this->Data[ePARTYSETTINGS_OK].Width/2, this->Data[ePARTYSETTINGS_MAIN].Y + 310, 0, ScaleY);
		}
	//}

}
// ----------------------------------------------------------------------------------------------

bool Interface::EventPartySettingsWindow_Main(DWORD Event)
{
	this->EventPartySettingsWindow_Close(Event);
	this->EventPartySettingsWindow_All(Event);
	// ----
	// ----
	return true;
}
// ----------------------------------------------------------------------------------------------

bool Interface::EventPartySettingsWindow_All(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	//DWORD Delay			= (CurrentTick - this->Data[eDIABLO_CLOSE].EventTick);
	if( !this->Data[ePARTYSETTINGS_MAIN].OnShow )
	{
		return false;
	}

	if (IsWorkZone2(ePARTYSETTINGS_SYSTEM_ACTIVE))
	{
		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].OnClick = true;
			return true;
		}
		// ----
		this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_SYSTEM_ACTIVE].EventTick = GetTickCount();
		gPartySearchSettings.m_SystemActive ^= 1;

		for (int i=0;i<gProtect.m_MainInfo.CharacterCount;i++)
		{
			gPartySearchSettings.m_SystemActive==true?gPartySearchSettings.SetClassValue(i,true):gPartySearchSettings.SetClassValue(i,false);
			//gPartySearchSettings.ChangeClassValue(i);
		}
	}

	if (IsWorkZone2(ePARTYSETTINGS_LEVEL_MINUS))
	{
		if (gPartySearchSettings.m_SystemActive == 0)
		{
			return false;
		}

		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_LEVEL_MINUS].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_LEVEL_MINUS].OnClick = true;
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_MINUS].OnClick = false;
		// ----
		if( Delay < 200 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_MINUS].EventTick = GetTickCount();

		gPartySearchSettings.m_Level -= 10;
		if (gPartySearchSettings.m_Level<=0)
		{
			gPartySearchSettings.m_Level = 0;
		}
	}

	if (IsWorkZone2(ePARTYSETTINGS_LEVEL_PLUS))
	{
		if (gPartySearchSettings.m_SystemActive == 0)
		{
			return false;
		}

		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_LEVEL_PLUS].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_LEVEL_PLUS].OnClick = true;
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_PLUS].OnClick = false;
		// ----
		if( Delay < 200 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_LEVEL_PLUS].EventTick = GetTickCount();

		gPartySearchSettings.m_Level += 10;
		if (gPartySearchSettings.m_Level>=400)
		{
			gPartySearchSettings.m_Level = 400;
		}
	}

	if (IsWorkZone2(ePARTYSETTINGS_ONLY_GUILD))
	{
		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_ONLY_GUILD].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_ONLY_GUILD].OnClick = true;
			return true;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONLY_GUILD].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONLY_GUILD].EventTick = GetTickCount();
		gPartySearchSettings.m_OnlyGuild ^= 1;
	}

	if (IsWorkZone2(ePARTYSETTINGS_ONE_CLASS))
	{
		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_ONE_CLASS].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_ONE_CLASS].OnClick = true;
			return true;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONE_CLASS].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_ONE_CLASS].EventTick = GetTickCount();
		gPartySearchSettings.m_OneClass ^= 1;

		for (int i=0;i<gProtect.m_MainInfo.CharacterCount;i++)
		{
			gPartySearchSettings.m_OneClass==false?gPartySearchSettings.SetClassValue(i,true):gPartySearchSettings.SetClassValue(i,false);
			//gPartySearchSettings.ChangeClassValue(i);
		}
	}

	if (IsWorkZone2(ePARTYSETTINGS_OK))
	{
		/*if (gPartySearchSettings.m_SystemActive == 0)
		{
			return false;
		}*/

		DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_OK].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSETTINGS_OK].OnClick = true;
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_OK].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[ePARTYSETTINGS_OK].EventTick = GetTickCount();
		gPartySearchSettings.CGSendPartySearchAdd();
		this->SwitchPartySettingsWindowState();
	}

	int ObjectIDs[7] = 
	{ 
		ePARTYSETTINGS_DARK_WIZARD, 
		ePARTYSETTINGS_DARK_KNIGHT, 
		ePARTYSETTINGS_ELF, 
		ePARTYSETTINGS_MAGIC_GLADIATOR, 
		ePARTYSETTINGS_DARK_LORD, 
		ePARTYSETTINGS_SUMMONER, 
		ePARTYSETTINGS_RAGE_FIGHTER
	};

	for (int i = 0; i<7; i++)
	{
		if (IsWorkZone2(ObjectIDs[i]))
		{
			DWORD Delay			= (CurrentTick - this->Data[ObjectIDs[i]].EventTick);

			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ObjectIDs[i]].OnClick = true;
				return true;
			}
			// ----
			this->Data[ObjectIDs[i]].OnClick = false;
			// ----
			if( Delay < 500 )
			{
				return false;
			}
			// ----
			this->Data[ObjectIDs[i]].EventTick = GetTickCount();
			gPartySearchSettings.ChangeClassValue(i);

			if (gPartySearchSettings.m_OneClass == true)
			{
				gPartySearchSettings.m_OneClass = false;
			}
		}
	}
	return false;
}

bool Interface::EventPartySettingsWindow_Close(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[ePARTYSETTINGS_CLOSE].EventTick);
	// ----
	if( !this->Data[ePARTYSETTINGS_MAIN].OnShow || !IsWorkZone2(ePARTYSETTINGS_CLOSE) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[ePARTYSETTINGS_CLOSE].OnClick = true;
		return true;
	}
	// ----
	this->Data[ePARTYSETTINGS_CLOSE].OnClick = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[ePARTYSETTINGS_CLOSE].EventTick = GetTickCount();
	this->Data[ePARTYSETTINGS_MAIN].Close();
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawPartySearchWindow()
{
	if( !this->Data[ePARTYSEARCH_MAIN].OnShow )
	{
		return;
	}
	// ----
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 50.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(ePARTYSEARCH_MAIN, StartX, StartY + 2);
	this->DrawGUI(ePARTYSEARCH_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(ePARTYSEARCH_FRAME, StartX, StartY + 67.0, 16);
	this->DrawGUI(ePARTYSEARCH_FOOTER, StartX, StartY);
	this->DrawGUI(ePARTYSEARCH_CLOSE, StartX + MainWidth - this->Data[ePARTYSEARCH_CLOSE].Width + 2, 49);
	// ----
	if( this->IsWorkZone2(ePARTYSEARCH_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[ePARTYSEARCH_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(ePARTYSEARCH_CLOSE, this->Data[ePARTYSEARCH_CLOSE].X, this->Data[ePARTYSEARCH_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[ePARTYSEARCH_CLOSE].X + 5, this->Data[ePARTYSEARCH_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 60, 210, 3, gCustomMessage.GetMessage(94));
	// ----
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSEARCH_MAIN].Y + 40); // Äåëèòåëü áîëüøîé
	// ----
	this->DrawFormat(eWhite, StartX + 5, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, gCustomMessage.GetMessage(117));
	// ----
	this->DrawFormat(eWhite, StartX + 45, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, gCustomMessage.GetMessage(119));
	// ----
	this->DrawFormat(eWhite, StartX + 95, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "X");
	// ----
	this->DrawFormat(eWhite, StartX + 115, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, "Y");
	// ----
	//this->DrawFormat(eWhite, StartX + 140, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, gCustomMessage.GetMessage(119));
	// ----
	this->DrawFormat(eWhite, StartX + 140, this->Data[ePARTYSEARCH_MAIN].Y + 56, 50, 3, gCustomMessage.GetMessage(120));
	// ----
	this->DrawGUI(ePARTYSETTINGS_DIV, StartX , this->Data[ePARTYSEARCH_MAIN].Y + 60); // Äåëèòåëü áîëüøîé
	// ----
	if (gPartySearch.CountPages>1)
	{
		this->DrawFormat(eGold, StartX+104, 379, 20, 3, "%d/%d", gPartySearch.Page+1,gPartySearch.CountPages);
	}

	if (gPartySearch.Page+1 > 1)
	{
		this->DrawButton(ePARTYSEARCH_LEFT, StartX+73, 372, 0, 0);
	}

	if (gPartySearch.Page+1 < gPartySearch.CountPages)
	{
		this->DrawButton(ePARTYSEARCH_RIGHT, StartX+73+60, 372, 0, 0);
	}

	int DrawnItems = 0;

	for (int i=0;i<gPartySearch.ListsCount;i++)
	{
		if (DrawnItems >= 10)
		{
			break;
		}

		PARTYLIST* info = gPartySearch.GetPartyList(i+(10*gPartySearch.Page));

		if (info == 0)
		{
			continue;
		}

		pDrawGUI(0x7E98, StartX + 10, this->Data[ePARTYSEARCH_MAIN].Y + 80+(20*i), 170, 21);

		this->DrawFormat(eYellow, StartX + 15, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 1, info->Name);

		this->DrawFormat(eWhite, StartX + 45, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 3, gObjUser.GetMapName(info->Map));

		this->DrawFormat(eWhite, StartX + 95, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 3, "%d", info->X);

		this->DrawFormat(eWhite, StartX + 115, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 3, "%d", info->Y);

		this->DrawFormat(eWhite, StartX + 140, this->Data[ePARTYSEARCH_MAIN].Y + 86+(20*i), 50, 3, "%d / 5", info->Count);

		pDrawGUI(0x7E99, StartX + 178, this->Data[ePARTYSEARCH_MAIN].Y + 80+(i*20), 22, 19);

		if (info->ButtonActive == true)
		{
			pDrawButton(0x7AA4, StartX + 203, this->Data[ePARTYSEARCH_MAIN].Y + 82+(i*20),16, 15, 0, 0);
		}

		int X = StartX + 213;
		int Y = this->Data[ePARTYSEARCH_MAIN].Y + 82+(i*20);
		int MaxX= X + 16;
		int MaxY= Y + 15;

		if (info->ButtonActive == true)
		{
			if (IsWorkZone(X, Y,MaxX, MaxY))
			{
				pDrawColorButton(0x7AA4, StartX + 203, Y,16, 15, 0, 16,eGray100);
			}
		}

		DrawnItems++;
	}

	DrawnItems = 0;

	for (int i=0;i<gPartySearch.ListsCount;i++)
	{
		if (DrawnItems >= 10)
		{
			break;
		}

		PARTYLIST* info = gPartySearch.GetPartyList(i+(10*gPartySearch.Page));

		if (info == 0)
		{
			continue;
		}

		int X = StartX + 188;
		int Y = this->Data[ePARTYSEARCH_MAIN].Y + 80+(i*20);
		int MaxX= X + 22;
		int MaxY= Y + 19;

		if (IsWorkZone(X, Y,MaxX, MaxY))
		{
			this->DrawFormat(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 72, 50, 3, pGetTextLine(pTextLineThis,2371),1,info->Level);

			if (info->DarkWizard == true)
			{
				this->DrawFormat(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 82, 50, 3, "%s", pGetTextLine(pTextLineThis,20));
			}
			if (info->DarkKnight == true)
			{
				//strcat(szText, pGetTextLine(pTextLineThis,21));
				this->DrawFormat(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 92, 50, 3, "%s", pGetTextLine(pTextLineThis,21));
			}
			if (info->Elf == true)
			{
				//strcat(szText, "\nElf");
				this->DrawFormat(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 102, 50, 3, "%s", pGetTextLine(pTextLineThis,22));
			}
			if (info->MagicGladiator == true)
			{
				//strcat(szText, "\nMagic Gladiator");
				this->DrawFormat(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 112, 50, 3, "%s", pGetTextLine(pTextLineThis,23));
			}
			if (info->DarkLord == true)
			{
				//strcat(szText, "\nDark Lord");
				this->DrawFormat(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 122, 50, 3, "%s", pGetTextLine(pTextLineThis,24));
			}
			if (info->Summoner == true)
			{
				//strcat(szText, "\nSummoner");
				this->DrawFormat(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 132, 50, 3, "%s", pGetTextLine(pTextLineThis,1687));
			}
			if (info->RageFighter == true)
			{
				this->DrawFormat(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 142, 50, 3, "%s", pGetTextLine(pTextLineThis,3150));
				//strcat(szText, "\nRage Fighter");
			}
			if (info->OnlyGuild == true)
			{
				//strcat(szText,"\nOnly Guild");
				this->DrawFormat(eWhite, StartX + 230, this->Data[ePARTYSEARCH_MAIN].Y + 152, 50, 3, "%s", pGetTextLine(pTextLineThis,1624));
			}

			//strcat(szText, "\n_____________________");

			//this->DrawToolTipEx(eWhite,StartX + 230,this->Data[ePARTYSEARCH_MAIN].Y + 62+(i*20),100,30,3,szText);
		}

		DrawnItems++;
	}

	if (gPartySearch.Page+1 > 1)
	{
		if( IsWorkZone2(ePARTYSEARCH_LEFT) )
		{
			if( this->Data[ePARTYSEARCH_LEFT].OnClick )
			{
				this->DrawButton(ePARTYSEARCH_LEFT, StartX+73, 372, 0, 46);
				return;
			}
			this->DrawButton(ePARTYSEARCH_LEFT, StartX+73, 372, 0, 23);
		}
	}
	if (gPartySearch.Page+1 < gPartySearch.CountPages)
	{
		if( IsWorkZone2(ePARTYSEARCH_RIGHT) )
		{
			if( this->Data[ePARTYSEARCH_RIGHT].OnClick )
			{
				this->DrawButton(ePARTYSEARCH_RIGHT, StartX+73+60, 372, 0, 46);
				return;
			}
			this->DrawButton(ePARTYSEARCH_RIGHT, StartX+73+60, 372, 0, 23);
		}
	}	
}

void Interface::EventPartySearchWindow_All(DWORD Event)
{
	float StartX			= (MAX_WIN_WIDTH / 2) - (230.0 / 2);
	DWORD CurrentTick	= GetTickCount();
	//DWORD Delay			= (CurrentTick - this->Data[eDIABLO_CLOSE].EventTick);
	if( !this->Data[ePARTYSEARCH_MAIN].OnShow )
	{
		return;
	}

	if (IsWorkZone2(ePARTYSEARCH_CLOSE))
	{
		DWORD Delay			= (CurrentTick - this->Data[ePARTYSEARCH_CLOSE].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSEARCH_CLOSE].OnClick = true;
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_CLOSE].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_CLOSE].EventTick = GetTickCount();
		this->SwitchPartySearchWindowState();
	}
	if( IsWorkZone2(ePARTYSEARCH_LEFT) && gPartySearch.Page+1 > 1)
	{
		DWORD Delay	= (CurrentTick - this->Data[ePARTYSEARCH_LEFT].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSEARCH_LEFT].OnClick = true;
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_LEFT].OnClick = false;
		// ----
		if( Delay < 100 )
		{
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_LEFT].EventTick = GetTickCount();
		// ----
		gPartySearch.Page--;
		//gPartySearch.DrawnItems = 0;
	}
	if( IsWorkZone2(ePARTYSEARCH_RIGHT) && gPartySearch.Page+1 < gPartySearch.CountPages )
	{
		DWORD Delay	= (CurrentTick - this->Data[ePARTYSEARCH_RIGHT].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYSEARCH_RIGHT].OnClick = true;
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_RIGHT].OnClick = false;
		// ----
		if( Delay < 100 )
		{
			return;
		}
		// ----
		this->Data[ePARTYSEARCH_RIGHT].EventTick = GetTickCount();
		// ----
		gPartySearch.Page++;
		//gPartySearch.DrawnItems = 0;
	}

	int DrawnItems = 0;

	for (int i=0;i<gPartySearch.ListsCount;i++)
	{
		if (DrawnItems >= 10)
		{
			break;
		}
		//pDrawButton(0x7AA4, StartX + 203, this->Data[ePARTYSEARCH_MAIN].Y + 82+(i*20),16, 15, 0, 0);
		if (IsWorkZone(StartX + 213,this->Data[ePARTYSEARCH_MAIN].Y + 82+(i*20),StartX + 213 + 16, this->Data[ePARTYSEARCH_MAIN].Y + 82+(i*20)+15))
		{
			DWORD Delay	= (CurrentTick - this->Data[ePARTYSEARCH_RIGHT].EventTick);
			// ----
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ePARTYSEARCH_RIGHT].OnClick = true;
				return;
			}
			// ----
			this->Data[ePARTYSEARCH_RIGHT].OnClick = false;
			// ----
			if( Delay < 100 )
			{
				return;
			}
			// ----
			if (gPartySearch.gPartyList[i+(10*gPartySearch.Page)].ButtonActive == false)
			{
				return;
			}
			// ----
			this->Data[ePARTYSEARCH_RIGHT].EventTick = GetTickCount();
			// ----
			gPartySearch.SendPartyRequest(i+(10*gPartySearch.Page));
			////console.Log("", "Map = %s", pGetMapName(info->Map));
		}
	}
}

void Interface::DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int a6, int a7, float a8, char a9)
{

	pDrawItemModel(PosX, PosY, Width, Height, ItemID, a6, a7, a8, a9);
	/*
	if (gInterface.item_post_ && pCursorX < 150 && gInterface.Data[eUSERSPANEL_MAIN].OnShow == false)
	{
		pDrawItemModel(pCursorX - 90.0f, pCursorY - 80.0f, 100.0f, 100.0f, gUser.PostItemID, 1, 0, 0, 1);

		if (gInterface.last_tickcount_view_ + 100 < GetTickCount()) {
			gInterface.item_post_ = nullptr;
		}
	}

	return pDrawItemModel(PosX, PosY, Width, Height, ItemID, a6, a7, a8, a9);
	*/
}

void testfunc()
{
    glMatrixMode(0x1700u);
    glPopMatrix();
    glMatrixMode(0x1701u);
    glPopMatrix();
}

void Interface::DrawItem2(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse)
{
 
    glMatrixMode(0x1701);
    glPushMatrix();
    glLoadIdentity();
 
    //float X = ull_to_float2(*(QWORD*)0xE61E58);
    //float Y = ull_to_float2(*(QWORD*)0xE61E58+1);
 
    sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);
    //float v2 = (X / (Y / 100.0f)) / 100.0f;//(*(float*)MAIN_RESOLUTION_X / (*(float*)MAIN_RESOLUTION_Y / 100.0f)) / 100.0f;
    float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;
    sub_6358A0_Addr(1.0, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
 
    glMatrixMode(0x1700);
    glPushMatrix();
    glLoadIdentity();
 
    sub_635830_Addr((LPVOID)0x87933A0);
    sub_635DE0_Addr();
    sub_635E40_Addr();
 
    //posX
    //posY
    //Width
    //Height
    //unk
    // 1 - Excellent Effect
    // 1 - Aura +7
    // 1 - original size
    //glClear(0x100u);
    pDrawItemModel(PosX, PosY, Width, Height, ItemID, Level, Excl, Anc, OnMouse);
   
    testfunc();
    //sub_637770_Addr();
 
    glColor3f(1,1,1);
    pSetBlend(false);
}

void Interface::DrawStatsAddWindow()
{
	if (!this->Data[eSTATSADD_MAIN].OnShow)
	{
		return;
	}

	int ObjectCount = 4;
	if ((gObjUser.lpPlayer->Class & 7) == 4)
	{
		ObjectCount = 5;
	}
	char szCharNames[5][32];
	memcpy(szCharNames[0],gCustomMessage.GetMessage(142),sizeof(szCharNames[0]));
	memcpy(szCharNames[1],gCustomMessage.GetMessage(143),sizeof(szCharNames[1]));
	memcpy(szCharNames[2],gCustomMessage.GetMessage(144),sizeof(szCharNames[2]));
	memcpy(szCharNames[3],gCustomMessage.GetMessage(145),sizeof(szCharNames[3]));
	memcpy(szCharNames[4],gCustomMessage.GetMessage(146),sizeof(szCharNames[4]));
	/*
	char szCharNames[5][32] = 
	{
		"Strength:",
		"Agility:",
		"Vitality:",
		"Energy:",
		"Command:",
	};
	*/
	int ObjectIDs[5] = 
	{ 
		eSTATSADD_STATBOX01, 
		eSTATSADD_STATBOX02, 
		eSTATSADD_STATBOX03, 
		eSTATSADD_STATBOX04, 
		eSTATSADD_STATBOX05, 
	};

	if (this->Data[eSTATSADD_MAIN].ByClose == false)
	{
		if (this->Data[eSTATSADD_MAIN].OpenedValue < 0)
		{
			this->Data[eSTATSADD_MAIN].OpenedValue += this->Data[eSTATSADD_MAIN].Speed;

			if (this->Data[eSTATSADD_MAIN].OpenedValue >= -150)
			{
				this->Data[eSTATSADD_MAIN].Speed = 15;
			}

			if (this->Data[eSTATSADD_MAIN].OpenedValue > 0)
			{
				this->Data[eSTATSADD_MAIN].OpenedValue = 0;
			}
		}
	}
	else
	{
		if (this->Data[eSTATSADD_MAIN].OpenedValue > -226)
		{
			this->Data[eSTATSADD_MAIN].OpenedValue -= this->Data[eSTATSADD_MAIN].Speed;

			if (this->Data[eSTATSADD_MAIN].OpenedValue <= -150)
			{
				this->Data[eSTATSADD_MAIN].Speed = 20;
			}

			if (this->Data[eSTATSADD_MAIN].OpenedValue <= -226)
			{
				//this->Data[eSTATSADD_MAIN].OpenedValue = 100;
				this->Data[eSTATSADD_MAIN].Close();
				/*
				this->Data[eSTATSADD_STEP10].Attribute = 0;
				this->Data[eSTATSADD_STEP100].Attribute = 0;
				this->Data[eSTATSADD_STEP1000].Attribute = 0;
				*/
				for (int i=0;i<ObjectCount;i++)
				{
					this->Data[ObjectIDs[i]].Attribute = false;
				}
			}
		}
	}

	float MainWidth			= 230.0;
	float StartY			= 198;
	float StartX			= this->Data[eSTATSADD_MAIN].OpenedValue;
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawAnimatedGUI(eSTATSADD_MAIN, StartX, StartY + 2);
	this->DrawAnimatedGUI(eSTATSADD_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eSTATSADD_FRAME, StartX, StartY + 67.0, 8);
	this->DrawAnimatedGUI(eSTATSADD_FOOTER, StartX, StartY);
	this->DrawAnimatedGUI(eSTATSADD_CLOSE, StartX + MainWidth - this->Data[eSTATSADD_CLOSE].Width, this->Data[eSTATSADD_MAIN].Y - 2);
	// ----

	// ----
	if( this->IsWorkZone2(eSTATSADD_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eSTATSADD_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eSTATSADD_CLOSE, this->Data[eSTATSADD_CLOSE].X, this->Data[eSTATSADD_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eSTATSADD_CLOSE].X + 5, this->Data[eSTATSADD_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
	}
	// ----
	DWORD StatPoints = ViewPoint;
	
	for (int i=0;i<ObjectCount;i++)
	{
		StatPoints -= atoi(this->Data[ObjectIDs[i]].StatValue);
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, this->Data[eSTATSADD_MAIN].Y+8, 210, 3, gCustomMessage.GetMessage(127));
	
	this->DrawAnimatedGUI(eSTATSADD_TEXTBOX01, ButtonX - 35, this->Data[eSTATSADD_MAIN].Y + 28);
	this->DrawFormat(eWhite, StartX - 40, this->Data[eSTATSADD_MAIN].Y + 34, 210, 3, gCustomMessage.GetMessage(128));

	char Value[50];
	ZeroMemory(Value, sizeof(Value));
	pGetMoneyFormat((double)StatPoints, Value, 0);
	GetFormat(Value,',',' ');

	////console.Log("", "Point %d Value %s",StatPoints,Value);

	this->DrawFormat(eWhite, StartX + 45, this->Data[eSTATSADD_MAIN].Y + 34, 210, 3, "%s", Value);

	this->DrawFormat(eWhite, StartX + 10, this->Data[eSTATSADD_MAIN].Y + 55, 210, 3, gCustomMessage.GetMessage(129));
	/*
	this->DrawFormat(eWhite, StartX + 30, this->Data[eSTATSADD_MAIN].Y + 69, 30, 3, "Step value:");

	this->DrawFormat(eWhite, StartX + 80, this->Data[eSTATSADD_MAIN].Y + 70, 10, 3, "10");
	this->DrawFormat(eWhite, StartX + 120, this->Data[eSTATSADD_MAIN].Y + 70, 15, 3, "100");
	this->DrawFormat(eWhite, StartX + 162, this->Data[eSTATSADD_MAIN].Y + 70, 20, 3, "1000");

	if (this->Data[eSTATSADD_STEP10].Attribute == true)
	{
		this->DrawAnimatedButton(eSTATSADD_STEP10, StartX + 90, this->Data[eSTATSADD_MAIN].Y + 66, 0, 15);
	}
	else
	{
		this->DrawAnimatedButton(eSTATSADD_STEP10, StartX + 90, this->Data[eSTATSADD_MAIN].Y + 66, 0, 0);
	}

	if (this->Data[eSTATSADD_STEP100].Attribute == true)
	{
		this->DrawAnimatedButton(eSTATSADD_STEP100, StartX + 135, this->Data[eSTATSADD_MAIN].Y + 66, 0, 15);
	}
	else
	{
		this->DrawAnimatedButton(eSTATSADD_STEP100, StartX + 135, this->Data[eSTATSADD_MAIN].Y + 66, 0, 0);
	}

	if (this->Data[eSTATSADD_STEP1000].Attribute == true)
	{
		this->DrawAnimatedButton(eSTATSADD_STEP1000, StartX + 180, this->Data[eSTATSADD_MAIN].Y + 66, 0, 15);
	}
	else
	{
		this->DrawAnimatedButton(eSTATSADD_STEP1000, StartX + 180, this->Data[eSTATSADD_MAIN].Y + 66, 0, 0);
	}*/

	if (this->Data[eSTATSADD_MAIN].FirstLoad == true)
	{
		this->Data[eSTATSADD_STATBOX01].Attribute = 1;
	}

	for (int i=0;i<ObjectCount;i++)
	{
		if (this->Data[eSTATSADD_MAIN].FirstLoad == true)
		{
			sprintf(this->Data[ObjectIDs[i]].StatValue, "0");
		}
		this->DrawAnimatedGUI(ObjectIDs[i], ButtonX - 35, this->Data[eSTATSADD_MAIN].Y + 63 + ((i+1)*21));
		this->DrawFormat(eWhite, StartX - 38, this->Data[eSTATSADD_MAIN].Y + 69 + ((i+1)*21), 210, 3, szCharNames[i]);
		this->DrawFormat(eWhite, StartX + 45, this->Data[eSTATSADD_MAIN].Y + 69 + ((i+1)*21), 210, 3, this->Data[ObjectIDs[i]].StatValue);
	}

	for (int i=0;i<ObjectCount;i++)
	{
		if (this->Data[ObjectIDs[i]].Attribute == 1)
		{
			DWORD Color = eGray100;
			this->DrawColoredAnimatedGUI(ObjectIDs[i], ButtonX - 35, this->Data[eSTATSADD_MAIN].Y + 63 + ((i+1)*21), Color);
		}
	}

	this->DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, this->Data[eSTATSADD_MAIN].Y + 194, 0, 0);

	if( this->IsWorkZone2(eSTATSADD_BTN_OK) )
	{
		int ScaleY = 30;
		// ----
		if( this->Data[eSTATSADD_BTN_OK].OnClick )
		{
			ScaleY = 60;
		}
		// ----
		this->DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, this->Data[eSTATSADD_MAIN].Y + 194, 0, ScaleY);
	}

	//login_me
	//newui_button_cancel
	//newui_button_ok
	if (this->Data[eSTATSADD_MAIN].FirstLoad == true)
	{
		this->Data[eSTATSADD_MAIN].FirstLoad = false;
	}
}
// ----------------------------------------------------------------------------------------------

void Interface::EventStatsAddWindow(DWORD Event)
{
	this->EventStatsAddWindow_Close(Event);
}

void Interface::EventStatsAddWindow_Close(DWORD Event)
{
	if (!this->Data[eSTATSADD_MAIN].OnShow)
	{
		return;
	}

	DWORD CurrentTick	= GetTickCount();

	int ObjectIDs[5] = 
	{ 
		eSTATSADD_STATBOX01, 
		eSTATSADD_STATBOX02, 
		eSTATSADD_STATBOX03, 
		eSTATSADD_STATBOX04, 
		eSTATSADD_STATBOX05,
	};

	int ObjectCount = 4;
	if ((gObjUser.lpPlayer->Class & 7) == 4)
	{
		ObjectCount = 5;
	}

	for (int i=0;i<ObjectCount;i++)
	{
		if (IsWorkZone2(ObjectIDs[i]))
		{
			DWORD Delay			= (CurrentTick - this->Data[ObjectIDs[i]].EventTick);
			// ----
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			this->Data[ObjectIDs[i]].OnClick = false;
			// ----
			if( Delay < 500 )
			{
				return;
			}
			this->Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j=0;j<ObjectCount;j++)
			{
				this->Data[ObjectIDs[j]].Attribute = 0;
			}

			this->Data[ObjectIDs[i]].Attribute = 1;
		}
	}

	for (int i = 5; i<5; i++)
	{
		if (IsWorkZone2(ObjectIDs[i]))
		{
			DWORD Delay			= (CurrentTick - this->Data[ObjectIDs[i]].EventTick);
			// ----
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			this->Data[ObjectIDs[i]].OnClick = false;
			// ----
			if( Delay < 500 )
			{
				return;
			}
			this->Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j=5;j<8;j++)
			{
				this->Data[ObjectIDs[j]].Attribute = 0;
			}

			this->Data[ObjectIDs[i]].Attribute = 1;
		}
	}


	if (IsWorkZone2(eSTATSADD_BTN_OK))
	{
		DWORD Delay			= (CurrentTick - this->Data[eSTATSADD_BTN_OK].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eSTATSADD_BTN_OK].OnClick = true;
			return;
		}
		// ----
		this->Data[eSTATSADD_BTN_OK].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eSTATSADD_BTN_OK].EventTick = GetTickCount();
		Data[eSTATSADD_MAIN].CloseAnimated(15);
		PMSG_UPDATE_STATS_SEND pMsg;
		pMsg.Str = atoi(this->Data[eSTATSADD_STATBOX01].StatValue);
		pMsg.Agi = atoi(this->Data[eSTATSADD_STATBOX02].StatValue);
		pMsg.Vit = atoi(this->Data[eSTATSADD_STATBOX03].StatValue);
		pMsg.Ene = atoi(this->Data[eSTATSADD_STATBOX04].StatValue);
		pMsg.Com = 0;
		if (ObjectCount == 5)
		{
			pMsg.Com = atoi(this->Data[eSTATSADD_STATBOX05].StatValue);
		}
		CGSendStatsAdd(pMsg);
	}
	
	if (IsWorkZone2(eSTATSADD_CLOSE))
	{
		DWORD Delay			= (CurrentTick - this->Data[eSTATSADD_CLOSE].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eSTATSADD_CLOSE].OnClick = true;
			return;
		}
		// ----
		this->Data[eSTATSADD_CLOSE].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eSTATSADD_CLOSE].EventTick = GetTickCount();
		Data[eSTATSADD_MAIN].CloseAnimated(15);
	}

	// ----
	return;
}

// ----------------------------------------------------------------------------------------------
void Interface::EventCharacterWindow(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	//DWORD Delay			= (CurrentTick - this->Data[eCHARINFO_BTN_STAT].EventTick);
	// ----
	if( !this->CheckWindow(Character))
	{
		return;
	}
	// ----
	if (IsWorkZone2(eCHARINFO_BTN_STAT))
	{
		//if (gConfig.GetCustomState(CUSTOM_STATSADD) == 0)
		//{
		//	return;
		//}
		DWORD Delay			= (CurrentTick - this->Data[eCHARINFO_BTN_STAT].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eCHARINFO_BTN_STAT].OnClick = true;
			return;
		}
		// ----
		this->Data[eCHARINFO_BTN_STAT].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eCHARINFO_BTN_STAT].EventTick = GetTickCount();
		this->SwitchStatsWindowState();
		////console.Log("", "AddStat switchstate");
	}
	
	if (IsWorkZone2(eCHARINFO_BTN_RESSTAT))
	{
		DWORD Delay			= (CurrentTick - this->Data[eCHARINFO_BTN_RESSTAT].EventTick);

		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eCHARINFO_BTN_RESSTAT].OnClick = true;
			return;
		}
		// ----
		this->Data[eCHARINFO_BTN_RESSTAT].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eCHARINFO_BTN_RESSTAT].EventTick = GetTickCount();
		this->SwitchResetStatsWindowState();
	}
	//if( !this->CheckWindow(Character) || !IsWorkZone(eCHARINFO_BTN_STAT) )
	//{
	//	return;
	//}
	//// ----
	//if( Event == WM_LBUTTONDOWN )
	//{
	//	this->Data[eCHARINFO_BTN_STAT].OnClick = true;
	//	return;
	//}
	//// ----
	//this->Data[eCHARINFO_BTN_STAT].OnClick = false;
	//// ----
	//if( Delay < 500 )
	//{
	//	return;
	//}
	//// ----
	//this->Data[eCHARINFO_BTN_STAT].EventTick = GetTickCount();
	//this->SwitchStatsWindowState();
}

void Interface::DrawResetStatsWindow()
{
	if( !this->Data[eRESETSTATS_MAIN].OnShow )
	{
		return;
	}
	// ----
	float MainWidth			= 230.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	// ----

	this->DrawGUI(eRESETSTATS_MAIN, StartX, StartY + 2);
	this->DrawGUI(eRESETSTATS_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eRESETSTATS_FRAME, StartX, StartY + 67.0, 2);
	this->DrawGUI(eRESETSTATS_FOOTER, StartX, StartY);
	this->DrawGUI(eRESETSTATS_CLOSE, StartX + MainWidth - this->Data[eRESETSTATS_CLOSE].Width, this->Data[eRESETSTATS_TITLE].Height + this->Data[eRESETSTATS_CLOSE].Height + 2);

	// ----
	if( this->IsWorkZone2(eRESETSTATS_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eRESETSTATS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eRESETSTATS_CLOSE, this->Data[eRESETSTATS_CLOSE].X, this->Data[eRESETSTATS_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eRESETSTATS_CLOSE].X + 5, this->Data[eRESETSTATS_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
	}
	// ----

	int x = GetPrivateProfileIntA("Custom", "X", -35, "./Settings.ini");
	int y = GetPrivateProfileIntA("Custom", "Y", 60, "./Settings.ini");

	int StatPoints = ViewStrength + ViewDexterity + ViewVitality + ViewEnergy + ViewLeadership;

	StatPoints -= (gObjUser.d_Strength + gObjUser.d_Dexterity + gObjUser.d_Vitality + gObjUser.d_Energy + gObjUser.d_Leadership);

	/*
	if (this->Data[eRESETSTATS_CHECK_STAT].Attribute == true)
	{
		StatPoints -= gObjUser.m_CustomResetPointPriceZen(ViewAccountLevel);
		if (StatPoints < 0)
		{
			StatPoints = 0;
		}
	}
	*/

	this->DrawFormat(eGold, StartX + 10, 110, 210, 3, gCustomMessage.GetMessage(122));
	//Reset Point
	if(this->m_ResetPointCheckBox == 1)
	{
		this->DrawGUI(eRESETSTATS_POINT, StartX + 25 , this->Data[eRESETSTATS_MAIN].Y + 33); // Point
		this->DrawFormat(eWhite, StartX + 40, this->Data[eRESETSTATS_MAIN].Y + 34, 100, 1, gCustomMessage.GetMessage(123), gObjUser.GetResetPointPriceWC(ViewAccountLevel)); // Text
		pDrawGUI(0x7B5E, StartX + 30, this->Data[eRESETSTATS_MAIN].Y + 45, 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
		pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[eRESETSTATS_MAIN].Y + 45, 82.0, 2.0); // Äåëèòåëü ìåëêèé 2
	}
	if(this->m_ResetPointCheckBox1 == 1)
	{
		this->DrawGUI(eRESETSTATS_POINT, StartX + 25 , this->Data[eRESETSTATS_MAIN].Y + 53); // Point
		this->DrawFormat(eWhite, StartX + 40, this->Data[eRESETSTATS_MAIN].Y + 54, 100, 1, gCustomMessage.GetMessage(124), gObjUser.GetResetPointPriceZen(ViewAccountLevel)); // Text
		pDrawGUI(0x7B5E, StartX + 30, this->Data[eRESETSTATS_MAIN].Y + 65, 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
		pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[eRESETSTATS_MAIN].Y + 65, 82.0, 2.0); // Äåëèòåëü ìåëêèé 2
	}
	if(this->m_ResetMasterSkillCheckBox == 1)
	{
		//Master Point Reset
		this->DrawGUI(eRESETSTATS_POINT, StartX + 25 , this->Data[eRESETSTATS_MAIN].Y + 73); // Point
		this->DrawFormat(eWhite, StartX + 40, this->Data[eRESETSTATS_MAIN].Y + 74, 115, 1, gCustomMessage.GetMessage(125), gObjUser.GetResetMasterSkillPriceWC(ViewAccountLevel)); // Text
		pDrawGUI(0x7B5E, StartX + 30, this->Data[eRESETSTATS_MAIN].Y + 85, 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
		pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[eRESETSTATS_MAIN].Y + 85, 82.0, 2.0); // Äåëèòåëü ìåëêèé 2
	}
	if(this->m_ResetMasterSkillCheckBox1 == 1)
	{
		this->DrawGUI(eRESETSTATS_POINT, StartX + 25 , this->Data[eRESETSTATS_MAIN].Y + 93); // Point
		this->DrawFormat(eWhite, StartX + 40, this->Data[eRESETSTATS_MAIN].Y + 94, 115, 1, gCustomMessage.GetMessage(126), gObjUser.GetResetMasterSkillPriceZen(ViewAccountLevel)); // Text
		pDrawGUI(0x7B5E, StartX + 30, this->Data[eRESETSTATS_MAIN].Y + 105, 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
		pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[eRESETSTATS_MAIN].Y + 105, 82.0, 2.0); // Äåëèòåëü ìåëêèé 2
	}
	if(this->m_ResetPointCheckBox == 1)
	{
		//Reset Point
		if (this->Data[eRESETSTATS_CHECK_WC].Attribute == true)
		{
			this->DrawButton(eRESETSTATS_CHECK_WC, 385, 132, 0, 15);
		}
		else
		{
			this->DrawButton(eRESETSTATS_CHECK_WC, 385, 132, 0, 0);
		}
	}
	if(this->m_ResetPointCheckBox1 == 1)
	{
		if (this->Data[eRESETSTATS_CHECK_STAT].Attribute == true)
		{
			this->DrawButton(eRESETSTATS_CHECK_STAT, 385, 152, 0, 15);
		}
		else
		{
			this->DrawButton(eRESETSTATS_CHECK_STAT, 385, 152, 0, 0);
		}
	}

	//this->DrawFormat(eYellow, StartX + 50, this->Data[eRESETSTATS_MAIN].Y + 75, 45, 3, "Reward Points:");
	//pDrawGUI(0x7895, StartX + 120, this->Data[eRESETSTATS_MAIN].Y + 71.5, 50, 16);
	//this->DrawFormat(eWhite, StartX + 110, this->Data[eRESETSTATS_MAIN].Y + 75, 50, 3, "%d", StatPoints);
	if(this->m_ResetMasterSkillCheckBox == 1)
	{
		//Master Point Reset
		if (this->Data[eRESETMASTER_CHECK_WC].Attribute == true)
		{
			this->DrawButton(eRESETMASTER_CHECK_WC, 385, 172, 0, 15);
		}
		else
		{
			this->DrawButton(eRESETMASTER_CHECK_WC, 385, 172, 0, 0);
		}
	}
	if(this->m_ResetMasterSkillCheckBox1 == 1)
	{
		if (this->Data[eRESETMASTER_CHECK_STAT].Attribute == true)
		{
			this->DrawButton(eRESETMASTER_CHECK_STAT, 385, 192, 0, 15);
		}
		else
		{
			this->DrawButton(eRESETMASTER_CHECK_STAT, 385, 192, 0, 0);
		}
	}
	this->Data[eRESETSTATS_BTN_OK].Attribute = false;

	if (this->Data[eRESETSTATS_CHECK_WC].Attribute || this->Data[eRESETSTATS_CHECK_STAT].Attribute || this->Data[eRESETMASTER_CHECK_WC].Attribute || this->Data[eRESETMASTER_CHECK_STAT].Attribute)
	{
		this->DrawButton(eRESETSTATS_BTN_OK, StartX + 85, this->Data[eRESETSTATS_MAIN].Y + 108, 0, 0);

		if( this->IsWorkZone2(eRESETSTATS_BTN_OK) )
		{
			int ScaleY = 30;
			// ----
			if( this->Data[eRESETSTATS_BTN_OK].OnClick )
			{
				ScaleY = 60;
			}
			// ----
			this->DrawButton(eRESETSTATS_BTN_OK, StartX + 85, this->Data[eRESETSTATS_MAIN].Y + 108, 0, ScaleY);
		}
		this->Data[eRESETSTATS_BTN_OK].Attribute = true;
	}
}

void Interface::EventResetStatsWindow(DWORD Event)
{
	if ( !this->Data[eRESETSTATS_MAIN].OnShow)
	{
		return;
	}

	this->EventResetStatsWindow_Close(Event);

	int eObjectIDs[4] = 
	{
		eRESETSTATS_CHECK_WC,
		eRESETSTATS_CHECK_STAT,
		eRESETMASTER_CHECK_WC,
		eRESETMASTER_CHECK_STAT,
	};

	DWORD CurrentTick	= GetTickCount();

	for (int i=0; i<4; i++)
	{
		DWORD Delay			= (CurrentTick - this->Data[eObjectIDs[i]].EventTick);
		// ----
		if(!IsWorkZone2(eObjectIDs[i]) )
		{
			continue;
		}
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eObjectIDs[i]].OnClick = true;
			break;;
		}
		// ----
		this->Data[eObjectIDs[i]].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			break;
		}
		// ----
		this->Data[eObjectIDs[i]].EventTick = GetTickCount();
		if(this->m_ResetPointCheckBox == 1)
		{
			if (eObjectIDs[i] == eRESETSTATS_CHECK_WC)
			{
				this->Data[eRESETSTATS_CHECK_WC].Attribute = 1;
				this->Data[eRESETSTATS_CHECK_STAT].Attribute = 0;
				this->Data[eRESETMASTER_CHECK_WC].Attribute = 0;
				this->Data[eRESETMASTER_CHECK_STAT].Attribute = 0;
			}
		}
		if(this->m_ResetPointCheckBox1 == 1)
		{
			if (eObjectIDs[i] == eRESETSTATS_CHECK_STAT)
			{
				this->Data[eRESETSTATS_CHECK_STAT].Attribute = 1;
				this->Data[eRESETSTATS_CHECK_WC].Attribute = 0;
				this->Data[eRESETMASTER_CHECK_WC].Attribute = 0;
				this->Data[eRESETMASTER_CHECK_STAT].Attribute = 0;
			}
		}
		if(this->m_ResetMasterSkillCheckBox == 1)
		{
			//Reset Master Point
			if (eObjectIDs[i] == eRESETMASTER_CHECK_WC)
			{
				this->Data[eRESETMASTER_CHECK_WC].Attribute = 1;
				this->Data[eRESETMASTER_CHECK_STAT].Attribute = 0;
				this->Data[eRESETSTATS_CHECK_WC].Attribute = 0;
				this->Data[eRESETSTATS_CHECK_STAT].Attribute = 0;
			}
		}
		if(this->m_ResetMasterSkillCheckBox1 == 1)
		{
			if (eObjectIDs[i] == eRESETMASTER_CHECK_STAT)
			{
				this->Data[eRESETMASTER_CHECK_STAT].Attribute = 1;
				this->Data[eRESETMASTER_CHECK_WC].Attribute = 0;
				this->Data[eRESETSTATS_CHECK_WC].Attribute = 0;
				this->Data[eRESETSTATS_CHECK_STAT].Attribute = 0;
			}
		}
	}

	DWORD Delay			= (CurrentTick - this->Data[eRESETSTATS_BTN_OK].EventTick);
	// ----
	if( !IsWorkZone2(eRESETSTATS_BTN_OK) || !this->Data[eRESETSTATS_BTN_OK].Attribute )
	{
		return;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eRESETSTATS_BTN_OK].OnClick = true;
		return;
	}
	// ----
	this->Data[eRESETSTATS_BTN_OK].OnClick = false;
	// ----
	if( Delay < 500 )
	{
		return;
	}
	// ----
	this->Data[eRESETSTATS_BTN_OK].EventTick = GetTickCount();
	if(this->m_ResetPointCheckBox == 1)
	{
		//Reset Point
		if (this->Data[eRESETSTATS_CHECK_WC].Attribute == true)
		{
			CGSendResetStats(0);
		}
	}
	if(this->m_ResetPointCheckBox1 == 1)
	{
		if (this->Data[eRESETSTATS_CHECK_STAT].Attribute == true)
		{
			CGSendResetStats(1);
		}
	}
	if(this->m_ResetMasterSkillCheckBox == 1)
	{
		//Reset Master Skill
		if (this->Data[eRESETMASTER_CHECK_WC].Attribute == true)
		{
			CGSendResetStats(2);
		}
	}
	if(this->m_ResetMasterSkillCheckBox1 == 1)
	{
		if (this->Data[eRESETMASTER_CHECK_STAT].Attribute == true)
		{
			CGSendResetStats(3);
		}
	}
	this->SwitchResetStatsWindowState();
}

void Interface::EventResetStatsWindow_Close(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eRESETSTATS_CLOSE].EventTick);
	// ----
	if( !this->Data[eRESETSTATS_MAIN].OnShow || !IsWorkZone2(eRESETSTATS_CLOSE) )
	{
		return;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eRESETSTATS_CLOSE].OnClick = true;
		return;
	}
	// ----
	this->Data[eRESETSTATS_CLOSE].OnClick = false;
	// ----
	if( Delay < 500 )
	{
		return;
	}
	// ----
	this->Data[eRESETSTATS_CLOSE].EventTick = GetTickCount();
	this->SwitchResetStatsWindowState();
	
}

// ----------------------------------------------------------------------------------------------

void Interface::DrawOffExpWindow()
{
	if( !this->Data[eOFFEXP_MAIN].OnShow )
	{
		return;
	}
	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(eOFFEXP_MAIN, StartX, StartY + 2);
	this->DrawGUI(eOFFEXP_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eOFFEXP_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eOFFEXP_FOOTER, StartX, StartY);
	this->DrawGUI(eOFFEXP_CLOSE, StartX + MainWidth - this->Data[eOFFEXP_CLOSE].Width, this->Data[eOFFEXP_TITLE].Height + this->Data[eOFFEXP_CLOSE].Height + 2);
    // ----
    if( this->IsWorkZone2(eOFFEXP_CLOSE) )
    {
        DWORD Color = eGray100;
        // ----
        if( this->Data[eOFFEXP_CLOSE].OnClick )
        {
            Color = eGray150;
        }
        // ----
        this->DrawColoredGUI(eOFFEXP_CLOSE, this->Data[eOFFEXP_CLOSE].X, this->Data[eOFFEXP_CLOSE].Y, Color);
        this->DrawToolTip(this->Data[eOFFEXP_CLOSE].X + 5, this->Data[eOFFEXP_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
    }
	// ----

	this->DrawFormat(eGold, StartX + 10, 110, 210, 3, gCustomMessage.GetMessage(130));

	this->DrawFormat(eWhite, StartX + 10, 135, 210, 3, gCustomMessage.GetMessage(131), gObjUser.lpPlayer->Name);

	pDrawGUI(0x7B5E, StartX + 30, this->Data[eOFFEXP_MAIN].Y + 43, 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
	pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[eOFFEXP_MAIN].Y + 43, 82.0, 2.0); // Äåëèòåëü ìåëêèé 2

	this->DrawFormat(eWhite, StartX + 10, 150, 210, 3, gCustomMessage.GetMessage(132));

	pDrawGUI(0x7B5E, StartX + 30, this->Data[eOFFEXP_MAIN].Y + 78, 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
	pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[eOFFEXP_MAIN].Y + 78, 82.0, 2.0); // Äåëèòåëü ìåëêèé 2

	/*int x = GetPrivateProfileIntA("Custom", "X", 0, "./Settings.ini");
	int y = GetPrivateProfileIntA("Custom", "Y", 0, "./Settings.ini");*/

	int ObjectIDs[7] = 
	{
		eOFFEXP_CHECKBOX_BUFF,
		0,
		eOFFEXP_CHECKBOX_PICK_ZEN,
		eOFFEXP_CHECKBOX_PICK_JEWELS,
		eOFFEXP_CHECKBOX_PICK_EXC,
		eOFFEXP_CHECKBOX_PICK_ANC,
		eOFFEXP_CHECKBOX_SELECTED_HELPER
	};
	char szText[7][64];
	memcpy(szText[0],gCustomMessage.GetMessage(133),sizeof(szText[0]));
	memcpy(szText[1],gCustomMessage.GetMessage(134),sizeof(szText[1]));
	memcpy(szText[2],gCustomMessage.GetMessage(135),sizeof(szText[2]));
	memcpy(szText[3],gCustomMessage.GetMessage(136),sizeof(szText[3]));
	memcpy(szText[4],gCustomMessage.GetMessage(137),sizeof(szText[4]));
	memcpy(szText[5],gCustomMessage.GetMessage(138),sizeof(szText[5]));
	memcpy(szText[6],gCustomMessage.GetMessage(139),sizeof(szText[6]));
	/*
	char szText[7][64] = 
	{
		"Auto Buff",
		"NULL",
        "Pick up Zen",
        "Pick up Jewels",
        "Pick up Excellent Items",
        "Pick up Ancient Items",
		"Pick up selected items from list in MuHelper"
	};
	*/
	
	for (int i=0;i<8;i++)
	{
		pDrawGUI(0x7B5E, StartX + 30, this->Data[eOFFEXP_MAIN].Y + 114+(20*i), 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
		pDrawGUI(0x7B5E, StartX + 30 + 82, this->Data[eOFFEXP_MAIN].Y + 114+(20*i), 82.0, 2.0); // Äåëèòåëü ìåëêèé 2

		if (i!=1&&i!=7)
		{
			int btn = 1;
			if (i==0 && gOfflineMode.DrawBuff == 0)
			{
				btn = 0;
				//continue;
			}

			if ((i>=2 && i<=6) && gOfflineMode.DrawPick == 0)
			{
				btn = 0;
				//continue;
			}

			this->DrawGUI(eOFFEXP_POINT, StartX + 30 , this->Data[eOFFEXP_MAIN].Y + 120+(20*i)); //
			this->DrawFormat(eWhite, StartX + 45, this->Data[eOFFEXP_MAIN].Y + 121+(20*i), 200, 1, szText[i]);
			if (btn==1)
			{
				this->DrawButton(ObjectIDs[i], 385, 220+(20*i), 0, 15*gOfflineMode.GetCheckBox(i));
			}
			else
			{
				this->DrawColoredButton(ObjectIDs[i], 385, 220+(20*i), 0, 15*gOfflineMode.GetCheckBox(i),eGray150);
			}
			
		}
	}

	this->DrawFormat(eGold, StartX + 10, this->Data[eOFFEXP_MAIN].Y + 141, 210, 3, gCustomMessage.GetMessage(140));

	this->DrawGUI(eOFFEXP_BTN_OK, ButtonX-3, this->Data[eOFFEXP_FOOTER].Y + 10);
	this->DrawFormat(eWhite, StartX + 5, this->Data[eOFFEXP_FOOTER].Y + 20, 210, 3, gCustomMessage.GetMessage(141));

	if( IsWorkZone2(eOFFEXP_BTN_OK) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eOFFEXP_BTN_OK].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eOFFEXP_BTN_OK, this->Data[eOFFEXP_BTN_OK].X, this->Data[eOFFEXP_BTN_OK].Y, Color);
	}

	gOfflineMode.DrawSkill(0, StartX);
	gOfflineMode.DrawSkill(1, StartX);
	gOfflineMode.DrawSkill(2, StartX);

	for (int i=0; i<=2; i++)
	{
		if (gOfflineMode.SkillsIndex[i] == 0)
		{
			continue;
		}

		if (this->IsWorkZone(StartX + (50*(i+1)), this->Data[eOFFEXP_MAIN].Y + 83, StartX + (50*(i+1))+20, this->Data[eOFFEXP_MAIN].Y + 83 + 28))
		{
			this->DrawToolTipEx(eWhite,StartX + (50*(i+1))-14, this->Data[eOFFEXP_MAIN].Y + 123,50,30,3,gOfflineMode.SkillsName[i]);
		}
	}
	//this->DrawGUI(eCHARINFO_BTN_RESSTAT, 385, 300);
	//this->DrawGUI(eCHARINFO_BTN_RESSTAT, 385, 320);
}
// ----------------------------------------------------------------------------------------------

bool Interface::EventOffExpWindow_Main(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();

	if( !this->Data[eOFFEXP_MAIN].OnShow)
	{
		return false;
	}

	if (IsWorkZone2(eOFFEXP_CLOSE))
	{
		DWORD Delay			= (CurrentTick - this->Data[eOFFEXP_CLOSE].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eOFFEXP_CLOSE].OnClick = true;
			return true;
		}
		// ----
		this->Data[eOFFEXP_CLOSE].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[eOFFEXP_CLOSE].EventTick = GetTickCount();
		//this->CloseTeleportPanelWindow();
		//this->Data[eTELEPORTPANEL_MAIN].Close();
		this->SwitchOffExpWindoState();
		// ----
		return false;
	}

	if (IsWorkZone2(eOFFEXP_BTN_OK))
	{
		DWORD Delay			= (CurrentTick - this->Data[eOFFEXP_FINISH].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eOFFEXP_FINISH].OnClick = true;
			return true;
		}
		// ----
		this->Data[eOFFEXP_FINISH].OnClick = false;;
		// ----
		if( Delay < 500 )
		{
			return false;
		}
		// ----
		this->Data[eOFFEXP_FINISH].EventTick = GetTickCount();
		gOfflineMode.SendOffExpData();
		this->SwitchOffExpWindoState();
	}

	int ObjectIDs[7] = 
	{
		eOFFEXP_CHECKBOX_BUFF,
		0,
		eOFFEXP_CHECKBOX_PICK_ZEN,
		eOFFEXP_CHECKBOX_PICK_JEWELS,
		eOFFEXP_CHECKBOX_PICK_EXC,
		eOFFEXP_CHECKBOX_PICK_ANC,
		eOFFEXP_CHECKBOX_SELECTED_HELPER
	};

	for (int i=0;i<7;i++)
	{
		if (i==1) continue;

		if (i==0 && gOfflineMode.DrawBuff == 0)
		{
			continue;
		}

		if ((i>=2 && i<=6) && gOfflineMode.DrawPick == 0)
		{
			continue;
		}

		if (this->IsWorkZone2(ObjectIDs[i]))
		{
			DWORD Delay	= (CurrentTick - this->Data[ObjectIDs[i]].EventTick);
			// ----
			if( !this->Data[eOFFEXP_MAIN].OnShow)
			{
				return false;
			}
			// ----
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ObjectIDs[i]].OnClick = true;
				return false;
			}
			// ----
			this->Data[ObjectIDs[i]].OnClick = false;
			// ----
			if( Delay < 200 )
			{
				return false;
			}
			// ----
			this->Data[ObjectIDs[i]].EventTick	= GetTickCount();
			gOfflineMode.ChangeCheckBox(i);
			//this->SwitchSettingsWindowState();
			//gConfig.SetSettingsInfo(i);
			////console.Log("", "Index = %d",i);
			// ----
		}
	}

	for (int i=0; i<=2; i++)
	{
		if (gOfflineMode.SkillsIndex[i] == 0)
		{
			continue;
		}

		float X = gOfflineMode.GetSkillX(i);
		float Y = gOfflineMode.GetSkillY(i);

		if (this->IsWorkZone(X,Y,X+20,Y+28))
		{
			DWORD Delay			= (CurrentTick - gOfflineMode.m_SkillCoord[i].EventTick);

			if( Event == WM_LBUTTONDOWN )
			{
				//this->Data[ObjectIDs[i]].OnClick = true;
				continue;
			}
			// ----
			//this->Data[ObjectIDs[i]].OnClick = false;
			// ----
			if( Delay < 500 )
			{
				continue;
			}

			gOfflineMode.m_SkillCoord[i].EventTick = GetTickCount();
			//this->DrawToolTip(StartX + (50*(i+1)), this->Data[eOFFEXP_MAIN].Y + 123, gOfflineMode.SkillsName[i]);

			if (gOfflineMode.SkillsData[i] == 0)
			{
				return false;
			}

			////console.Log("", "Pressed %d Delay:%d", i, Delay);

			gOfflineMode.ClearSelectedSkill();
			gOfflineMode.SelectedSkill[i] = true;
		}
	}
	return false;
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawAccountSecurityPW()
{
	if( !this->Data[eSECURITY_CHECK_MAIN].OnShow )
	{
		return;
	}

	//pSetCursorFocus = true;

	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 130;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	gInterface.DrawAnimatedGUI(eSECURITY_CHECK_MAIN, StartX+4, StartY + 4);
	gInterface.DrawAnimatedGUI(eSECURITY_CHECK_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eSECURITY_CHECK_FRAME, StartX, StartY + 67.0, 0);
	gInterface.DrawAnimatedGUI(eSECURITY_CHECK_FOOTER, StartX, StartY);
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, gCustomMessage.GetMessage(147));
	// ---- 
	//pDrawGUI(0x7AA3,230,140,170,21);
	this->DrawGUI(eSECURITY_CHECK_BOX,230,140);
	if (this->Data[eSECURITY_CHECK_BOX].Attribute == 1)
	{
		DWORD Color = eGray100;
		//this->DrawColoredAnimatedGUI(ObjectIDs[i], ButtonX - 35, this->Data[eSTATSADD_MAIN].Y + 63 + ((i+1)*21), Color);
		gInterface.DrawColoredGUI(eSECURITY_CHECK_BOX, gInterface.Data[eSECURITY_CHECK_BOX].X, gInterface.Data[eSECURITY_CHECK_BOX].Y, Color);
	}
	gInterface.DrawFormat(eGold, 240, 144, 50, 3, gCustomMessage.GetMessage(157));
	this->DrawFormat(eWhite, 280, 144, 150, 3, this->Data[eSECURITY_CHECK_BOX].StatValue);
	gInterface.DrawAnimatedGUI(eSECURITY_CHECK_OK, StartX+30, StartY /*- 5*/);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5 + 5, 50, 3, gCustomMessage.GetMessage(113));

	if( gInterface.IsWorkZone2(eSECURITY_CHECK_OK) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eSECURITY_CHECK_OK].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eSECURITY_CHECK_OK, gInterface.Data[eSECURITY_CHECK_OK].X, gInterface.Data[eSECURITY_CHECK_OK].Y, Color);
	}
	// ---- 
	gInterface.DrawAnimatedGUI(eSECURITY_CHECK_CLOSE, StartX + 70 + 62, StartY /*- 5*/ );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5 + 5, 50, 3, gCustomMessage.GetMessage(14));

	if( gInterface.IsWorkZone2(eSECURITY_CHECK_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eSECURITY_CHECK_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eSECURITY_CHECK_CLOSE, gInterface.Data[eSECURITY_CHECK_CLOSE].X, gInterface.Data[eSECURITY_CHECK_CLOSE].Y, Color);
	}
}

void Interface::EventAccountSecurityPW_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eSECURITY_CHECK_MAIN].OnShow )
	{
		return;
	}
	
	if (this->IsWorkZone2(eSECURITY_CHECK_BOX))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_CHECK_BOX].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_CHECK_BOX].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_CHECK_BOX].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_CHECK_BOX].EventTick = GetTickCount();
		//Func
		this->Data[eSECURITY_CHECK_BOX].Attribute = 1;
	}

	if (this->IsWorkZone2(eSECURITY_CHECK_OK))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_CHECK_OK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_CHECK_OK].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_CHECK_OK].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_CHECK_OK].EventTick = GetTickCount();
		//Func
		PMSG_SECURITY_PW_SEND pMsg;
		pMsg.SecretNumber = atoi(this->Data[eSECURITY_CHECK_BOX].StatValue);
		pMsg.header.set(0xFF,0x02,sizeof(pMsg));
		DataSend((BYTE*)&pMsg,pMsg.header.size);
		this->CloseAccountSecurityPWWindow();
		sprintf(this->Data[eSECURITY_CHECK_BOX].StatValue, "0");
	}

	if (this->IsWorkZone2(eSECURITY_CHECK_CLOSE))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_CHECK_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_CHECK_CLOSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_CHECK_CLOSE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_CHECK_CLOSE].EventTick = GetTickCount();
		//Func
		this->CloseAccountSecurityPWWindow();
		sprintf(this->Data[eSECURITY_CHECK_BOX].StatValue, "0");
	}
}

// ----------------------------------------------------------------------------------------------

void Interface::DrawAccountSecurity()
{
	if( !this->Data[eSECURITY_MAIN].OnShow )
	{
		return;
	}
	// ----
	float MainWidth			= 230.0;
	float StartY			= 50.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(eSECURITY_MAIN, StartX, StartY + 2);
	this->DrawGUI(eSECURITY_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eSECURITY_FRAME, StartX, StartY, 16);
	this->DrawGUI(eSECURITY_FOOTER, StartX, StartY);
	// ----
	Font[TAHOMA_BOLD_15]->DrawText(StartX + 80, 58, Fcolor->Gold, Fcolor->Trans, 30, (LPINT)5, gCustomMessage.GetMessage(147));
	//
	pDrawGUI(0x7AA3,235,90,170,21);
	this->DrawFormat(eGold, 220, 95, 100, 3, gCustomMessage.GetMessage(148));
	Font[TAHOMA_BOLD_14]->DrawText(335, 94, Fcolor->Green, Fcolor->Trans, 25, (LPINT)5, gCustomMessage.GetMessage(149));
	this->DrawGUI(eSECURITY_DIV, StartX , 110);
	for( int i = 0; i < 7; i++ )
	{
		pDrawGUI(iOptionDot,StartX + 15,127 + (20 * i) + 9,10,10);
		pDrawGUI(0x7B5E, StartX + 30, 140 + (20 * i) + 9, 82.0, 2.0);
		pDrawGUI(0x7B5E, StartX + 30 + 82, 140 + (20 * i) + 9, 82.0, 2.0);
	}
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 40, 135, Fcolor->White, Fcolor->Trans, 25, (LPINT)5, gCustomMessage.GetMessage(150));
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 40, 155, Fcolor->White, Fcolor->Trans, 25, (LPINT)5, gCustomMessage.GetMessage(151));
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 40, 175, Fcolor->White, Fcolor->Trans, 25, (LPINT)5, gCustomMessage.GetMessage(152));
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 40, 195, Fcolor->White, Fcolor->Trans, 25, (LPINT)5, gCustomMessage.GetMessage(153));
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 40, 215, Fcolor->White, Fcolor->Trans, 25, (LPINT)5, gCustomMessage.GetMessage(154));
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 40, 235, Fcolor->White, Fcolor->Trans, 25, (LPINT)5, gCustomMessage.GetMessage(155));
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 40, 255, Fcolor->White, Fcolor->Trans, 25, (LPINT)5, "Delete Character Lock");

	if (gObjUser.TradeLock == 1)
	{
		this->DrawButton(eSECURITY_TRADE,380, 133, 0, 15);
	}
	else
	{
		this->DrawButton(eSECURITY_TRADE,380, 133, 0, 0);
	}

	if (gObjUser.InventoryLock == 1)
	{
		this->DrawButton(eSECURITY_INVENTORY,380, 153, 0, 15);
	}
	else
	{
		this->DrawButton(eSECURITY_INVENTORY,380, 153, 0, 0);
	}

	if (gObjUser.WareLock == 1)
	{
		this->DrawButton(eSECURITY_WAREHOUSE,380, 173, 0, 15);
	}
	else
	{
		this->DrawButton(eSECURITY_WAREHOUSE,380, 173, 0, 0);
	}

	if (gObjUser.PShopLock == 1)
	{
		this->DrawButton(eSECURITY_PERSONALSHOP,380, 193, 0, 15);
	}
	else
	{
		this->DrawButton(eSECURITY_PERSONALSHOP,380, 193, 0, 0);
	}

	if (gObjUser.ShopLock == 1)
	{
		this->DrawButton(eSECURITY_SHOP,380, 213, 0, 15);
	}
	else
	{
		this->DrawButton(eSECURITY_SHOP,380, 213, 0, 0);
	}

	if (gObjUser.ChaosMixLock == 1)
	{
		this->DrawButton(eSECURITY_CHAOBOX,380, 233, 0, 15);
	}
	else
	{
		this->DrawButton(eSECURITY_CHAOBOX,380, 233, 0, 0);
	}

	if (gObjUser.DelCharLock == 1)
	{
		this->DrawButton(eSECURITY_DELCHAR,380, 253, 0, 15);
	}
	else
	{
		this->DrawButton(eSECURITY_DELCHAR,380, 253, 0, 0);
	}

	this->DrawGUI(eSECURITY_DIV, StartX , 265);
	DrawAnimatedGUI(eSECURITY_SAVE, StartX + 85, 280);
	Font[TAHOMA_BOLD_15]->DrawText(StartX + 105, 287, Fcolor->White, Fcolor->Trans, 25, (LPINT)5, gCustomMessage.GetMessage(156));

}

void Interface::EventAccountSecurity_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eSECURITY_MAIN].OnShow )
	{
		return;
	}
	
	if (this->IsWorkZone2(eSECURITY_TRADE))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_TRADE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_TRADE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_TRADE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_TRADE].EventTick = GetTickCount();
		//Func
		if(gObjUser.TradeLock == 1)
		{ gObjUser.TradeLock = 0; }
		else
		{ gObjUser.TradeLock = 1; }
	}
	
	if (this->IsWorkZone2(eSECURITY_INVENTORY))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_INVENTORY].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_INVENTORY].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_INVENTORY].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_INVENTORY].EventTick = GetTickCount();
		//Func
		if(gObjUser.InventoryLock == 1)
		{ gObjUser.InventoryLock = 0; }
		else
		{ gObjUser.InventoryLock = 1; }
	}

	if (this->IsWorkZone2(eSECURITY_WAREHOUSE))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_WAREHOUSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_WAREHOUSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_WAREHOUSE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_WAREHOUSE].EventTick = GetTickCount();
		//Func
		if(gObjUser.WareLock == 1)
		{ gObjUser.WareLock = 0; }
		else
		{ gObjUser.WareLock = 1; }
	}	
	
	if (this->IsWorkZone2(eSECURITY_SHOP))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_SHOP].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_SHOP].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_SHOP].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_SHOP].EventTick = GetTickCount();
		//Func
		if(gObjUser.ShopLock == 1)
		{ gObjUser.ShopLock = 0; }
		else
		{ gObjUser.ShopLock = 1; }
	}	
	
	if (this->IsWorkZone2(eSECURITY_PERSONALSHOP))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_PERSONALSHOP].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_PERSONALSHOP].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_PERSONALSHOP].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_PERSONALSHOP].EventTick = GetTickCount();
		//Func
		if(gObjUser.PShopLock == 1)
		{ gObjUser.PShopLock = 0; }
		else
		{ gObjUser.PShopLock = 1; }
	}

	if (this->IsWorkZone2(eSECURITY_CHAOBOX))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_CHAOBOX].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_CHAOBOX].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_CHAOBOX].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_CHAOBOX].EventTick = GetTickCount();
		//Func
		if(gObjUser.ChaosMixLock == 1)
		{ gObjUser.ChaosMixLock = 0; }
		else
		{ gObjUser.ChaosMixLock = 1; }
	}

	if (this->IsWorkZone2(eSECURITY_DELCHAR))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_DELCHAR].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_DELCHAR].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_DELCHAR].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_DELCHAR].EventTick = GetTickCount();
		//Func
		if(gObjUser.DelCharLock == 1)
		{ gObjUser.DelCharLock = 0; }
		else
		{ gObjUser.DelCharLock = 1; }
	}

	if (this->IsWorkZone2(eSECURITY_SAVE))
	{
		DWORD Delay = (CurrentTick - this->Data[eSECURITY_SAVE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eSECURITY_SAVE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eSECURITY_SAVE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eSECURITY_SAVE].EventTick = GetTickCount();
		//Func
		GCAccountSecuritySave();
		this->CloseAccountSecurityWindow();
	}
}

// ----------------------------------------------------------------------------------------------

void Interface::SelectChar()
{
	if (gProtect.m_MainInfo.ExpandedCharacter == 0)
	{
		((void(__cdecl*)())0x005BB0B0)();
		return;
	}

	gObjUser.Refresh();

	if(*(DWORD*)(MAIN_SCREEN_STATE) == ObjState::SwitchCharacter)
	{
		gInterface.DrawFormat(eGold, 306, 418, 25, 3, "Page: %d", gInterface.m_CharacterPage);

		if (gInterface.m_CharacterPage > 1)
		{
			gInterface.DrawButton(eSELECTCHAR_LEFT, 285, 410, 0, 0);

			if( gInterface.IsWorkZone2(eSELECTCHAR_LEFT) )
			{
				if( gInterface.Data[eSELECTCHAR_LEFT].OnClick )
				{
					gInterface.DrawButton(eSELECTCHAR_LEFT, 285, 410, 0, 46);
				}
				else
				{
					gInterface.DrawButton(eSELECTCHAR_LEFT, 285, 410, 0, 23);
				}
			}
		}
		if (gInterface.m_CharacterPage < 5)
		{
			gInterface.DrawButton(eSELECTCHAR_RIGHT, 330, 410, 0, 0);

			if( gInterface.IsWorkZone2(eSELECTCHAR_RIGHT) )
			{
				if( gInterface.Data[eSELECTCHAR_RIGHT].OnClick )
				{
					gInterface.DrawButton(eSELECTCHAR_RIGHT, 330, 410, 0, 46);
				}
				else
				{
					gInterface.DrawButton(eSELECTCHAR_RIGHT, 330, 410, 0, 23);
				}
			}
		}

	}

	((void(__cdecl*)())0x005BB0B0)();
}
// ----------------------------------------------------------------------------------------------

void Interface::EventSelectChar(DWORD Event)
{
	if (gProtect.m_MainInfo.ExpandedCharacter == 0)
	{
		return;
	}

	DWORD CurrentTick	= GetTickCount();
	// ----
	if(*(DWORD*)(MAIN_SCREEN_STATE) != ObjState::SwitchCharacter)
	{
		return;
	}
	// ----
	if( IsWorkZone2(eSELECTCHAR_LEFT) )
	{
		if (this->m_CharacterPage <= 1)
		{
			return;
		}

		DWORD Delay	= (CurrentTick - this->Data[eSELECTCHAR_LEFT].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eSELECTCHAR_LEFT].OnClick = true;
			return;
		}
		// ----
		this->Data[eSELECTCHAR_LEFT].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eSELECTCHAR_LEFT].EventTick = GetTickCount();
		// ----
		this->m_CharacterPage--;
		CGSendMultiChar(this->m_CharacterPage);
		((int(__cdecl*)(int Num)) 0x0057D620)(-1);
		*(BYTE*)0xE8CB4E = 0;
		*(DWORD*)(MAIN_SCREEN_STATE) = SwitchCharacter;
		*(DWORD*)0x87935A4 = 50;
		////console.Log("", "LEFT! %d", this->m_CharacterPage);
	}
	else if( IsWorkZone2(eSELECTCHAR_RIGHT) )
	{
		if (this->m_CharacterPage >= 5)
		{
			return;
		}

		DWORD Delay	= (CurrentTick - this->Data[eSELECTCHAR_RIGHT].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eSELECTCHAR_RIGHT].OnClick = true;
			return;
		}
		// ----
		this->Data[eSELECTCHAR_RIGHT].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eSELECTCHAR_RIGHT].EventTick = GetTickCount();
		// ----
		this->m_CharacterPage++;
		CGSendMultiChar(this->m_CharacterPage);
		((int(__cdecl*)(int Num)) 0x0057D620)(-1);
		*(BYTE*)0xE8CB4E = 0;
		*(DWORD*)(MAIN_SCREEN_STATE) = SwitchCharacter;
		*(DWORD*)0x87935A4 = 50;
		////console.Log("", "RIGHT! %d", this->m_CharacterPage);
	}
}
// ----------------------------------------------------------------------------------------------
void Interface::DrawChangingClassWindow()
{
	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow )
	{
		return;
	}
	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(eCHANGINGCLASS_MAIN, StartX, StartY + 2);
	this->DrawGUI(eCHANGINGCLASS_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eCHANGINGCLASS_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eCHANGINGCLASS_FOOTER, StartX, StartY);
	this->DrawGUI(eCHANGINGCLASS_CLOSE, StartX + MainWidth - this->Data[eCHANGINGCLASS_CLOSE].Width, this->Data[eCHANGINGCLASS_TITLE].Height + this->Data[eCHANGINGCLASS_CLOSE].Height + 2);
	// ----
	if( this->IsWorkZone2(eCHANGINGCLASS_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_CLOSE, this->Data[eCHANGINGCLASS_CLOSE].X, this->Data[eCHANGINGCLASS_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eCHANGINGCLASS_CLOSE].X + 5, this->Data[eCHANGINGCLASS_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 110, 210, 3, gCustomMessage.GetMessage(158));
	// ----
	if (gChangeClass.m_PriceType == 0)
	{
		this->DrawFormat(eGold, StartX + 30, 355, 210, 1, gCustomMessage.GetMessage(159));
	}
	else if (gChangeClass.m_PriceType == 1)
	{
		this->DrawFormat(eGold, StartX + 30, 355, 210, 1, gCustomMessage.GetMessage(160));
	}
	else if (gChangeClass.m_PriceType == 2)
	{
		this->DrawFormat(eGold, StartX + 30, 355, 210, 1, gCustomMessage.GetMessage(161));
	}
	else if (gChangeClass.m_PriceType == 3)
	{
		this->DrawFormat(eGold, StartX + 30, 355, 210, 1, gCustomMessage.GetMessage(162));
	}
	this->DrawGUI(eCHANGINGCLASS_MONEYBG, StartX + 30, 365);
	// ----
	char MoneyBuff[50], MoneyBuff2[50];
	ZeroMemory(MoneyBuff, sizeof(MoneyBuff));
	ZeroMemory(MoneyBuff2, sizeof(MoneyBuff2));
	// ----
	//if( gObjUser.m_CreditsCount
	//	< gChangeClass.m_Price )
	//{
	//	pGetMoneyFormat((double)gChangeClass.m_Price, 
	//		MoneyBuff, 0);
	//	pGetMoneyFormat((double)gChangeClass.m_Price - gObjUser.m_CreditsCount, 
	//		MoneyBuff2, 0);
	//	this->DrawFormat(eRed, StartX + 70, 369, 170, 1, "%s\n(Need still %s)", 
	//		MoneyBuff, MoneyBuff2);
	//}
	//else
	//{
	pGetMoneyFormat((double)gChangeClass.m_Price, 
		MoneyBuff, 0);
	this->DrawFormat(eGold, StartX + 70, 372, 70, 1, "%s", 
		MoneyBuff);
	//}
	// ----
	/*this->DrawFormat(eRed, StartX + 10, 330, 210, 3, "Warning!", MoneyBuff, MoneyBuff2);
	this->DrawFormat(eBlue, StartX + 10, 338, 210, 3, "Before make changing class need remove all items from inventory", MoneyBuff, MoneyBuff2);*/
	// ----
	this->DrawGUI(eCHANGINGCLASS_DW, ButtonX - 57, this->Data[eCHANGINGCLASS_MAIN].Y + 30);
	//this->DrawFormat(eWhite, StartX - 45, this->Data[eCHANGINGCLASS_MAIN].Y + 40, 210, 3, "Dark Wizard class");
	this->DrawFormat(eWhite, StartX - 45, this->Data[eCHANGINGCLASS_MAIN].Y + 40, 210, 3, gCustomMessage.GetMessage(163),pGetTextLine(pTextLineThis,20));
	//pGetTextLine
	// ----
	this->DrawGUI(eCHANGINGCLASS_DK, ButtonX + 52, this->Data[eCHANGINGCLASS_MAIN].Y + 30);
	this->DrawFormat(eWhite, StartX + 62, this->Data[eCHANGINGCLASS_MAIN].Y + 40, 210, 3, gCustomMessage.GetMessage(163),pGetTextLine(pTextLineThis,21));
	// ----
	this->DrawGUI(eCHANGINGCLASS_ELF, ButtonX - 57, this->Data[eCHANGINGCLASS_MAIN].Y + 60);
	this->DrawFormat(eWhite, StartX - 45, this->Data[eCHANGINGCLASS_MAIN].Y + 70, 210, 3, gCustomMessage.GetMessage(163),pGetTextLine(pTextLineThis,22));
	// ----
	this->DrawGUI(eCHANGINGCLASS_MG, ButtonX + 52, this->Data[eCHANGINGCLASS_MAIN].Y + 60);
	this->DrawFormat(eWhite, StartX + 62, this->Data[eCHANGINGCLASS_MAIN].Y + 70, 210, 3, gCustomMessage.GetMessage(163),pGetTextLine(pTextLineThis,23));
	// ----
	this->DrawGUI(eCHANGINGCLASS_DL, ButtonX - 57, this->Data[eCHANGINGCLASS_MAIN].Y + 90);
	this->DrawFormat(eWhite, StartX - 45, this->Data[eCHANGINGCLASS_MAIN].Y + 100, 210, 3, gCustomMessage.GetMessage(163),pGetTextLine(pTextLineThis,24));
	// ----
	if (gProtect.m_MainInfo.CharacterCount>=6)
	{
		this->DrawGUI(eCHANGINGCLASS_SUM, ButtonX + 52, this->Data[eCHANGINGCLASS_MAIN].Y + 90);
		this->DrawFormat(eWhite, StartX + 62, this->Data[eCHANGINGCLASS_MAIN].Y + 100, 210, 3, gCustomMessage.GetMessage(163),pGetTextLine(pTextLineThis,1687));
	}
	// ----
	if (gProtect.m_MainInfo.CharacterCount>=7)
	{
		this->DrawGUI(eCHANGINGCLASS_RF, ButtonX, this->Data[eCHANGINGCLASS_MAIN].Y + 120);
		this->DrawFormat(eWhite, StartX + 8, this->Data[eCHANGINGCLASS_MAIN].Y + 130, 210, 3, gCustomMessage.GetMessage(163),pGetTextLine(pTextLineThis,3150));
	}
	// ----
	this->DrawGUI(eCHANGINGCLASS_DIV, StartX, this->Data[eCHANGINGCLASS_MAIN].Y + 212);
	// ----
	this->Data[eCHANGINGCLASS_DW].Attribute = true;
	this->Data[eCHANGINGCLASS_DK].Attribute = true;
	this->Data[eCHANGINGCLASS_ELF].Attribute = true;
	this->Data[eCHANGINGCLASS_MG].Attribute = true;
	this->Data[eCHANGINGCLASS_DL].Attribute = true;
	this->Data[eCHANGINGCLASS_SUM].Attribute = true;
	this->Data[eCHANGINGCLASS_RF].Attribute = true;
	// ----
	if( IsWorkZone2(eCHANGINGCLASS_DW) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_DW].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_DW, this->Data[eCHANGINGCLASS_DW].X, this->Data[eCHANGINGCLASS_DW].Y, Color);
	}
	if( IsWorkZone2(eCHANGINGCLASS_DK) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_DK].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_DK, this->Data[eCHANGINGCLASS_DK].X, this->Data[eCHANGINGCLASS_DK].Y, Color);
	}
	if( IsWorkZone2(eCHANGINGCLASS_ELF) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_ELF].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_ELF, this->Data[eCHANGINGCLASS_ELF].X, this->Data[eCHANGINGCLASS_ELF].Y, Color);
	}
	if( IsWorkZone2(eCHANGINGCLASS_MG) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_MG].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_MG, this->Data[eCHANGINGCLASS_MG].X, this->Data[eCHANGINGCLASS_MG].Y, Color);
	}
	if( IsWorkZone2(eCHANGINGCLASS_DL) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eCHANGINGCLASS_DL].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eCHANGINGCLASS_DL, this->Data[eCHANGINGCLASS_DL].X, this->Data[eCHANGINGCLASS_DL].Y, Color);
	}
	if( IsWorkZone2(eCHANGINGCLASS_SUM) )
	{
		if (gProtect.m_MainInfo.CharacterCount>=6)
		{
			DWORD Color = eGray100;
			// ----
			if( this->Data[eCHANGINGCLASS_SUM].OnClick )
			{
				Color = eGray150;
			}
			// ----
			this->DrawColoredGUI(eCHANGINGCLASS_SUM, this->Data[eCHANGINGCLASS_SUM].X, this->Data[eCHANGINGCLASS_SUM].Y, Color);
		}
	}
	if( IsWorkZone2(eCHANGINGCLASS_RF) )
	{
		if (gProtect.m_MainInfo.CharacterCount>=7)
		{
			DWORD Color = eGray100;
			// ----
			if( this->Data[eCHANGINGCLASS_RF].OnClick )
			{
				Color = eGray150;
			}
			// ----
			this->DrawColoredGUI(eCHANGINGCLASS_RF, this->Data[eCHANGINGCLASS_RF].X, this->Data[eCHANGINGCLASS_RF].Y, Color);
		}
	}

}
// ----------------------------------------------------------------------------------------------

void Interface::EventChangingClassWindow_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eCHANGINGCLASS_MAIN].OnShow )
	{
		return;
	}

	if (this->IsWorkZone2(eCHANGINGCLASS_DW))
	{
		DWORD Delay = (CurrentTick - this->Data[eCHANGINGCLASS_DW].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCHANGINGCLASS_DW].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_DW].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_DW].EventTick = GetTickCount();
		//Func
		gChangeClass.SendChangeClass(0);
	}

	if (this->IsWorkZone2(eCHANGINGCLASS_DK))
	{
		DWORD Delay = (CurrentTick - this->Data[eCHANGINGCLASS_DK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCHANGINGCLASS_DK].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_DK].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_DK].EventTick = GetTickCount();
		//Func
		gChangeClass.SendChangeClass(16);
	}

	if (this->IsWorkZone2(eCHANGINGCLASS_ELF))
	{
		DWORD Delay = (CurrentTick - this->Data[eCHANGINGCLASS_ELF].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCHANGINGCLASS_ELF].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_ELF].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_ELF].EventTick = GetTickCount();
		//Func
		gChangeClass.SendChangeClass(32);
	}

	if (this->IsWorkZone2(eCHANGINGCLASS_MG))
	{
		DWORD Delay = (CurrentTick - this->Data[eCHANGINGCLASS_MG].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCHANGINGCLASS_MG].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_MG].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_MG].EventTick = GetTickCount();
		//Func
		gChangeClass.SendChangeClass(48);
	}

	if (this->IsWorkZone2(eCHANGINGCLASS_DL))
	{
		DWORD Delay = (CurrentTick - this->Data[eCHANGINGCLASS_DL].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCHANGINGCLASS_DL].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_DL].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_DL].EventTick = GetTickCount();
		//Func
		gChangeClass.SendChangeClass(64);
	}

	if (this->IsWorkZone2(eCHANGINGCLASS_SUM))
	{
		if (gProtect.m_MainInfo.CharacterCount<6)
		{
			return;
		}
		DWORD Delay = (CurrentTick - this->Data[eCHANGINGCLASS_SUM].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCHANGINGCLASS_SUM].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_SUM].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_SUM].EventTick = GetTickCount();
		//Func
		gChangeClass.SendChangeClass(80);
	}

	if (this->IsWorkZone2(eCHANGINGCLASS_RF))
	{
		if (gProtect.m_MainInfo.CharacterCount<7)
		{
			return;
		}
		DWORD Delay = (CurrentTick - this->Data[eCHANGINGCLASS_RF].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCHANGINGCLASS_RF].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_RF].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_RF].EventTick = GetTickCount();
		//Func
		gChangeClass.SendChangeClass(96);
	}

	if (this->IsWorkZone2(eCHANGINGCLASS_CLOSE))
	{
		DWORD Delay = (CurrentTick - this->Data[eCHANGINGCLASS_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eCHANGINGCLASS_CLOSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_CLOSE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eCHANGINGCLASS_CLOSE].EventTick = GetTickCount();
		//Func
		this->Data[eCHANGINGCLASS_MAIN].Close();
	}
}
// ----------------------------------------------------------------------------------------------
void Interface::DrawVipWindow()
{
	if( !this->Data[eVIP_MAIN].OnShow )
	{
		return;
	}
	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(eVIP_MAIN, StartX, StartY + 2);
	this->DrawGUI(eVIP_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eVIP_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eVIP_FOOTER, StartX, StartY);
	this->DrawGUI(eVIP_CLOSE, StartX + MainWidth - this->Data[eVIP_CLOSE].Width, this->Data[eVIP_TITLE].Height + this->Data[eVIP_CLOSE].Height + 2);
	// ----
	if( this->IsWorkZone2(eVIP_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eVIP_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eVIP_CLOSE, this->Data[eVIP_CLOSE].X, this->Data[eVIP_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eVIP_CLOSE].X + 5, this->Data[eVIP_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 110, 210, 3, gCustomMessage.GetMessage(164));
	// ----
	/*
	this->DrawGUI(eVIP_INFOBG, StartX + 30, 132);
	this->DrawFormat(eGold, StartX + 35, 137, 70, 3, gCustomMessage.GetMessage(165));
	this->DrawFormat(eWhite, StartX + 135, 137, 70, 1, gCustomMessage.GetMessage(62), gBuyVip.m_Price_AL1);
	*/
	this->DrawGUI(eVIP_INFOBG, StartX + 30, 152);
	this->DrawFormat(eGold, StartX + 35, 157, 70, 3, gCustomMessage.GetMessage(92));
	switch (this->VipType)
	{
		case 1:
			this->DrawFormat(eWhite, StartX + 135, 157, 70, 1, gCustomMessage.GetMessage(62), gBuyVip.m_Price_AL1 + this->VipTime * gBuyVip.m_TimePrice);
		break;
		case 2:
			this->DrawFormat(eWhite, StartX + 135, 157, 70, 1, gCustomMessage.GetMessage(62), gBuyVip.m_Price_AL2 + this->VipTime * gBuyVip.m_TimePrice);
		break;
		case 3:
			this->DrawFormat(eWhite, StartX + 135, 157, 70, 1, gCustomMessage.GetMessage(62), gBuyVip.m_Price_AL3 + this->VipTime * gBuyVip.m_TimePrice);
		break;
	}
	/*
	this->DrawGUI(eVIP_INFOBG, StartX + 30, 172);
	this->DrawFormat(eGold, StartX + 35, 177, 70, 3, gCustomMessage.GetMessage(167));
	this->DrawFormat(eWhite, StartX + 135, 177, 70, 1, gCustomMessage.GetMessage(62), gBuyVip.m_Price_AL3);
	*/
	// ----
	this->DrawGUI(eVIP_DIV, StartX, 185);
	// ----
	this->DrawFormat(eGold, StartX + 30, 220, 210, 1, gCustomMessage.GetMessage(168));
	this->DrawFormat(eGold, StartX + 80, 220, 210, 1, gCustomMessage.GetMessage(169));
	this->DrawFormat(eGold, StartX + 130, 220, 210, 1, gCustomMessage.GetMessage(170));
	//this->DrawFormat(eGold, StartX + 180, 220, 210, 1, gCustomMessage.GetMessage(171));
	// ----
	for( int i = 0; i < 5; i++ )
	{
		pDrawGUI(0x7B5E, StartX + 30, 225 + (24 * i) + 9, 82.0, 2.0);
		pDrawGUI(0x7B5E, StartX + 30 + 82, 225 + (24 * i) + 9, 82.0, 2.0);

	}
	this->DrawFormat(eWhite, StartX + 30, 241, 210, 1, gCustomMessage.GetMessage(165));
	this->DrawFormat(eWhite, StartX + 80, 241, 210, 1, "%d", gBuyVip.m_Exp_AL1);
	this->DrawFormat(eWhite, StartX + 130, 241, 210, 1, "%d", gBuyVip.m_Drop_AL1);
	if(this->VipType == 1)
	{
		this->DrawButton(eVIP_SILVER, 378, 239, 0, 15);
	}
	else
	{
		this->DrawButton(eVIP_SILVER, 378, 239, 0, 0);
	}
	//this->DrawFormat(eWhite, StartX + 180, 225 + 12, 210, 1, gCustomMessage.GetMessage(172));

	this->DrawFormat(eWhite, StartX + 30, 266, 210, 1, gCustomMessage.GetMessage(166));
	this->DrawFormat(eWhite, StartX + 80, 266, 210, 1, "%d", gBuyVip.m_Exp_AL2);
	this->DrawFormat(eWhite, StartX + 130, 266, 210, 1, "%d", gBuyVip.m_Drop_AL2);
	if(this->VipType == 2)
	{
		this->DrawButton(eVIP_GOLD, 378, 264, 0, 15);
	}
	else
	{
		this->DrawButton(eVIP_GOLD, 378, 264, 0, 0);
	}
	//this->DrawFormat(eWhite, StartX + 180, 225 + 24,210, 1, gCustomMessage.GetMessage(172));

	this->DrawFormat(eWhite, StartX + 30, 291, 210, 1, gCustomMessage.GetMessage(167));
	this->DrawFormat(eWhite, StartX + 80, 291, 210, 1, "%d", gBuyVip.m_Exp_AL3);
	this->DrawFormat(eWhite, StartX + 130, 291, 210, 1, "%d", gBuyVip.m_Drop_AL3);
	if(this->VipType == 3)
	{
		this->DrawButton(eVIP_PLATINUM, 378, 289, 0, 15);
	}
	else
	{
		this->DrawButton(eVIP_PLATINUM, 378, 289, 0, 0);
	}
	this->DrawFormat(eGold, StartX + 30, 316, 210, 1, gCustomMessage.GetMessage(171));
	pDrawGUI(0x7C0D, 355, 312, 16, 15); //
	this->DrawFormat(eRed, StartX + 180, 315, 210, 1, "%d",this->VipTime);
	pDrawGUI(0x7AA4, 398, 312, 16, 15); //
	//this->DrawFormat(eWhite, StartX + 180, 225 + 36,210, 1, gCustomMessage.GetMessage(172));
	/*
	this->DrawGUI(eVIP_SILVER, ButtonX -45, this->Data[eVIP_MAIN].Y + 99);
	this->DrawFormat(eWhite, StartX - 15, this->Data[eVIP_MAIN]. Y + 105, 120, 3, gCustomMessage.GetMessage(165));
	// ----
	this->DrawGUI(eVIP_GOLD, ButtonX + 25, this->Data[eVIP_MAIN].Y + 99);
	this->DrawFormat(eWhite, StartX + 35, this->Data[eVIP_MAIN]. Y + 105, + 160, 3, gCustomMessage.GetMessage(166));
	// ----
	this->DrawGUI(eVIP_PLATINUM, ButtonX + 92, this->Data[eVIP_MAIN].Y + 99);
	this->DrawFormat(eWhite, StartX + 84, this->Data[eVIP_MAIN]. Y + 105, 200, 3, gCustomMessage.GetMessage(167));
	// ----
	*/
	this->DrawGUI(eVIP_INFO, ButtonX, this->Data[eVIP_FOOTER].Y + 10);
	this->DrawFormat(eWhite, StartX + 8, this->Data[eVIP_FOOTER].Y + 20, 210, 3, gCustomMessage.GetMessage(173));
	
	this->DrawGUI(eVIP_DIV, StartX, this->Data[eVIP_FOOTER].Y - 10);
	// ----
	if( IsWorkZone2(eVIP_INFO) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eVIP_INFO].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eVIP_INFO, this->Data[eVIP_INFO].X, this->Data[eVIP_INFO].Y, Color);
	}
	if( IsWorkZone2(eVIP_SILVER) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eVIP_SILVER].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eVIP_SILVER, this->Data[eVIP_SILVER].X, this->Data[eVIP_SILVER].Y, Color);
	}
	if( IsWorkZone2(eVIP_GOLD) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eVIP_GOLD].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eVIP_GOLD, this->Data[eVIP_GOLD].X, this->Data[eVIP_GOLD].Y, Color);
	}
	if( IsWorkZone2(eVIP_PLATINUM) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eVIP_PLATINUM].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eVIP_PLATINUM, this->Data[eVIP_PLATINUM].X, this->Data[eVIP_PLATINUM].Y, Color);
	}
}
// ----------------------------------------------------------------------------------------------
void Interface::EventVipWindow_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eVIP_MAIN].OnShow )
	{
		return;
	}

	if (this->IsWorkZone2(eVIP_INFO))
	{
		DWORD Delay = (CurrentTick - this->Data[eVIP_INFO].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eVIP_INFO].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eVIP_INFO].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eVIP_INFO].EventTick = GetTickCount();
		//Func
		gBuyVip.SendBuyVip(this->VipType,this->VipTime); //Vip Status
		this->Data[eVIP_MAIN].Close();
	}

	if (this->IsWorkZone2(eVIP_SILVER))
	{
		DWORD Delay = (CurrentTick - this->Data[eVIP_SILVER].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eVIP_SILVER].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eVIP_SILVER].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eVIP_SILVER].EventTick = GetTickCount();
		//Func
		//gBuyVip.SendBuyVip(1); //Vip Silver
		//this->Data[eVIP_MAIN].Close();
		this->VipType = 1;
	}

	if (this->IsWorkZone2(eVIP_GOLD))
	{
		DWORD Delay = (CurrentTick - this->Data[eVIP_GOLD].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eVIP_GOLD].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eVIP_GOLD].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eVIP_GOLD].EventTick = GetTickCount();
		//Func
		//gBuyVip.SendBuyVip(2); //Vip Gold
		//this->Data[eVIP_MAIN].Close();
		this->VipType = 2;
	}

	if (this->IsWorkZone2(eVIP_PLATINUM))
	{
		DWORD Delay = (CurrentTick - this->Data[eVIP_PLATINUM].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eVIP_PLATINUM].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eVIP_PLATINUM].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eVIP_PLATINUM].EventTick = GetTickCount();
		//Func
		//gBuyVip.SendBuyVip(3); //Vip Platinum
		//this->Data[eVIP_MAIN].Close();
		this->VipType = 3;
	}

	if (this->IsWorkZone2(eVIP_LEFT))
	{
		DWORD Delay = (CurrentTick - this->Data[eVIP_LEFT].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eVIP_LEFT].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eVIP_LEFT].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eVIP_LEFT].EventTick = GetTickCount();
		//Func
		if(this->VipTime <= 1)
			return;
		else
			this->VipTime -= 1;
	}

	if (this->IsWorkZone2(eVIP_RIGHT))
	{
		DWORD Delay = (CurrentTick - this->Data[eVIP_RIGHT].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eVIP_RIGHT].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eVIP_RIGHT].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 100)
		{
			return;
		}
		// ----
		this->Data[eVIP_RIGHT].EventTick = GetTickCount();
		//Func
		if(this->VipTime >= 30)
			return;
		else
			this->VipTime += 1;
	}

	if (this->IsWorkZone2(eVIP_CLOSE))
	{
		DWORD Delay = (CurrentTick - this->Data[eVIP_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eVIP_CLOSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eVIP_CLOSE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eVIP_CLOSE].EventTick = GetTickCount();
		//Func
		this->Data[eVIP_MAIN].Close();
	}
}

// ----------------------------------------------------------------------------------------------

void Interface::DrawRename()
{
	if( !this->Data[eRENAME_MAIN].OnShow )
	{
		return;
	}

	//pSetCursorFocus = true;

	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 130;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	gInterface.DrawAnimatedGUI(eRENAME_MAIN, StartX+4, StartY + 4);
	gInterface.DrawAnimatedGUI(eRENAME_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eRENAME_FRAME, StartX, StartY + 67.0, 0);
	gInterface.DrawAnimatedGUI(eRENAME_FOOTER, StartX, StartY);
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, gCustomMessage.GetMessage(174));
	// ---- 
	//pDrawGUI(0x7AA3,230,140,170,21);
	this->DrawGUI(eRENAME_BOX,230,140);
	if (this->Data[eRENAME_BOX].Attribute == 1)
	{
		DWORD Color = eGray100;
		//this->DrawColoredAnimatedGUI(ObjectIDs[i], ButtonX - 35, this->Data[eSTATSADD_MAIN].Y + 63 + ((i+1)*21), Color);
		gInterface.DrawColoredGUI(eRENAME_BOX, gInterface.Data[eRENAME_BOX].X, gInterface.Data[eRENAME_BOX].Y, Color);
	}
	gInterface.DrawFormat(eGold, 235, 144, 70, 3, gCustomMessage.GetMessage(175));
	this->DrawFormat(eWhite, 280, 144, 150, 3, this->Data[eRENAME_BOX].StatValue);
	gInterface.DrawAnimatedGUI(eRENAME_OK, StartX+30, StartY /*- 5*/);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5 + 5, 50, 3, gCustomMessage.GetMessage(113));

	if( gInterface.IsWorkZone2(eRENAME_OK) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eRENAME_OK].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eRENAME_OK, gInterface.Data[eRENAME_OK].X, gInterface.Data[eRENAME_OK].Y, Color);
	}
	// ---- 
	gInterface.DrawAnimatedGUI(eRENAME_CLOSE, StartX + 70 + 62, StartY /*- 5*/ );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5 + 5, 50, 3, gCustomMessage.GetMessage(14));

	if( gInterface.IsWorkZone2(eRENAME_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eRENAME_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eRENAME_CLOSE, gInterface.Data[eRENAME_CLOSE].X, gInterface.Data[eRENAME_CLOSE].Y, Color);
	}
}

void Interface::EventRename_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eRENAME_MAIN].OnShow )
	{
		return;
	}
	
	if (this->IsWorkZone2(eRENAME_BOX))
	{
		DWORD Delay = (CurrentTick - this->Data[eRENAME_BOX].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eRENAME_BOX].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eRENAME_BOX].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eRENAME_BOX].EventTick = GetTickCount();
		//Func
		this->Data[eRENAME_BOX].Attribute = 1;
	}

	if (this->IsWorkZone2(eRENAME_OK))
	{
		DWORD Delay = (CurrentTick - this->Data[eRENAME_OK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eRENAME_OK].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eRENAME_OK].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eRENAME_OK].EventTick = GetTickCount();
		//Func
		PMSG_RENAME_SEND pMsg;
		memcpy(pMsg.Name,this->Data[eRENAME_BOX].StatValue,sizeof(pMsg.Name));
		//pMsg.Name = this->Data[eRENAME_BOX].StatValue;
		pMsg.header.set(0xFF,0x03,sizeof(pMsg));
		DataSend((BYTE*)&pMsg,pMsg.header.size);
		this->RenameState();
		sprintf(this->Data[eRENAME_BOX].StatValue, "");
	}

	if (this->IsWorkZone2(eRENAME_CLOSE))
	{
		DWORD Delay = (CurrentTick - this->Data[eRENAME_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eRENAME_CLOSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eRENAME_CLOSE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eRENAME_CLOSE].EventTick = GetTickCount();
		//Func
		this->RenameState();
		sprintf(this->Data[eRENAME_BOX].StatValue, "");
	}
}
// ----------------------------------------------------------------------------------------------

void Interface::DrawPSHOP()
{
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);

	if (this->CheckWindow(ObjWindow::Store))
	{
		if (this->m_PShopCurrency == 1)
		{
			if(this->PShop == 0)
			{
				this->DrawFormat(eRed, StartX + 35, StartY + 76, +125, 3, gCustomMessage.GetMessage(176));

				if(this->m_PSWcoinC == 1)
				{
					this->DrawGUI(eSHOP_WC, StartX + 70, StartY + 90);
					this->DrawFormat(eWhite, StartX + 80, StartY + 97, 100.0f, 1.0f, gCustomMessage.GetMessage(180));
				}

				if(this->m_PSBless == 1)
				{
					this->DrawGUI(eSHOP_B, StartX + 70, StartY + 120);
					this->DrawFormat(eYellow, StartX + 85, StartY + 127, 100.0f, 1.0f, gCustomMessage.GetMessage(177));
				}

				if(this->m_PSWcoinP == 1)
				{
					this->DrawGUI(eSHOP_WP, StartX + 125, StartY + 90);
					this->DrawFormat(eWhite, StartX + 135, StartY + 97, 100.0f, 1.0f, gCustomMessage.GetMessage(181));
				}

				if(this->m_PSSoul == 1)
				{
					this->DrawGUI(eSHOP_S, StartX + 125, StartY + 120);
					this->DrawFormat(eYellow, StartX + 140, StartY + 127, 100.0f, 1.0f, gCustomMessage.GetMessage(178));
				}

				if(this->m_PSWcoinG == 1)
				{
					this->DrawGUI(eSHOP_GP, StartX + 180, StartY + 90);
					this->DrawFormat(eWhite, StartX + 187, StartY + 97, 100.0f, 1.0f, gCustomMessage.GetMessage(182));
				}

				if(this->m_PSChaos == 1)
				{
					this->DrawGUI(eSHOP_C, StartX + 180, StartY + 120);
					this->DrawFormat(eYellow, StartX + 195, StartY + 127, 100.0f, 1.0f, gCustomMessage.GetMessage(179));
				}
			}
			if(this->PShop == 1)
			{
				this->DrawGUI(eSHOP_CLOSE, StartX + 149, StartY + 291);
			}
		}
		
		if (this->m_PShopOffStore == 1)
		{
			this->DrawGUI(eSHOP_OFF, StartX + 190, StartY + 291);
			if( IsWorkZone2(eSHOP_OFF) )
			{
				this->DrawToolTip(StartX + 190, StartY + 275, gCustomMessage.GetMessage(183));
			}
		}

		/*
	DWORD ClickTime;
	DWORD Delay = (GetTickCount() - ClickTime);
	if(CursorZoneButton(StartX + 149, StartY + 291, StartX + 171, StartY + 310))
	{
		if(gController.wMouse == WM_LBUTTONDOWN && Delay > 300)
		{
			ClickTime = GetTickCount();
			USERBUTTON_REQ pMsg;
			pMsg.Head.set(0xFF,0x23,sizeof(pMsg));
			DataSend((BYTE*)&pMsg,pMsg.Head.size);
			this->PShop = 0;
			pDrawMessage("123321",1);
			pSetCursorFocus = false;

		}
		this->DrawToolTip(StartX + 149, StartY + 291, gCustomMessage.GetMessage(183));
	}
	*/
	}
	// ----
}

void Interface::EventPSHOP_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->CheckWindow(ObjWindow::Store) )
	{
		return;
	}
	if (this->m_PSBless == 1)
	{
		if (this->IsWorkZone2(eSHOP_B))
		{
			DWORD Delay = (CurrentTick - this->Data[eSHOP_B].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eSHOP_B].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eSHOP_B].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eSHOP_B].EventTick = GetTickCount();
			//Func
			USERBUTTON_REQ pMsg;
			pMsg.Head.set(0xFB,0x20,sizeof(pMsg));
			DataSend((BYTE*)&pMsg,pMsg.Head.size);
		}
	}
		//
	if (this->m_PSSoul == 1)
	{
		if (this->IsWorkZone2(eSHOP_S))
		{
			DWORD Delay = (CurrentTick - this->Data[eSHOP_S].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eSHOP_S].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eSHOP_S].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eSHOP_S].EventTick = GetTickCount();
			//Func
			USERBUTTON_REQ pMsg;
			pMsg.Head.set(0xFB,0x21,sizeof(pMsg));
			DataSend((BYTE*)&pMsg,pMsg.Head.size);		
		}
	}
		//
	if (this->m_PSChaos == 1)
	{
		if (this->IsWorkZone2(eSHOP_C))
		{
			DWORD Delay = (CurrentTick - this->Data[eSHOP_C].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eSHOP_C].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eSHOP_C].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eSHOP_C].EventTick = GetTickCount();
			//Func
			USERBUTTON_REQ pMsg;
			pMsg.Head.set(0xFB,0x22,sizeof(pMsg));
			DataSend((BYTE*)&pMsg,pMsg.Head.size);		
		}
	}
		//
	if (this->m_PSWcoinC == 1)
	{
		if (this->IsWorkZone2(eSHOP_WC))
		{
			DWORD Delay = (CurrentTick - this->Data[eSHOP_WC].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eSHOP_WC].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eSHOP_WC].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eSHOP_WC].EventTick = GetTickCount();
			//Func
			USERBUTTON_REQ pMsg;
			pMsg.Head.set(0xFB,0x23,sizeof(pMsg));
			DataSend((BYTE*)&pMsg,pMsg.Head.size);		
		}
	}
		//
	if (this->m_PSWcoinP == 1)
	{
		if (this->IsWorkZone2(eSHOP_WP))
		{
			DWORD Delay = (CurrentTick - this->Data[eSHOP_WP].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eSHOP_WP].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eSHOP_WP].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eSHOP_WP].EventTick = GetTickCount();
			//Func
			USERBUTTON_REQ pMsg;
			pMsg.Head.set(0xFB,0x24,sizeof(pMsg));
			DataSend((BYTE*)&pMsg,pMsg.Head.size);		
		}
	}
		//
	if (this->m_PSWcoinG == 1)
	{
		if (this->IsWorkZone2(eSHOP_GP))
		{
			DWORD Delay = (CurrentTick - this->Data[eSHOP_GP].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eSHOP_GP].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eSHOP_GP].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eSHOP_GP].EventTick = GetTickCount();
			//Func
			USERBUTTON_REQ pMsg;
			pMsg.Head.set(0xFB,0x25,sizeof(pMsg));
			DataSend((BYTE*)&pMsg,pMsg.Head.size);		
		}
	}
		if (this->IsWorkZone2(eSHOP_CLOSE))
		{
			DWORD Delay = (CurrentTick - this->Data[eSHOP_CLOSE].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eSHOP_CLOSE].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eSHOP_CLOSE].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eSHOP_CLOSE].EventTick = GetTickCount();
			//Func
			USERBUTTON_REQ pMsg;
			pMsg.Head.set(0xFF,0x23,sizeof(pMsg));
			DataSend((BYTE*)&pMsg,pMsg.Head.size);
			this->PShop = 0;
		}
	//
	if (this->m_PShopOffStore == 1)
	{
		if (this->IsWorkZone2(eSHOP_OFF))
		{
			DWORD Delay = (CurrentTick - this->Data[eSHOP_OFF].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eSHOP_OFF].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eSHOP_OFF].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eSHOP_OFF].EventTick = GetTickCount();
			//Func
			this->PSHOP_OFFMODE_STATE();
		}
	}
}

void Interface::DrawPSHOP_OFFMODE()
{
	if( !this->Data[eOFFPANEL_MAIN].OnShow )
	{
		return;
	}
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 80.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	this->DrawGUI(eOFFPANEL_MAIN, StartX, StartY + 2);
	this->DrawGUI(eOFFPANEL_TITLE, StartX, StartY);
	//StartY = this->DrawRepeatGUI(eOFFPANEL_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eOFFPANEL_FOOTER, StartX, StartY + 75);

	this->DrawFormat(eGold, StartX + 10, 90, 210, 3, "Offline Store System");
	this->DrawFormat(eWhite, StartX + 10, 130, 210, 3, "Leave your Character in OFFSTORE mode?");
	this->DrawGUI(eOFFPANEL_YES, StartX + 30, StartY + 75);
	this->DrawGUI(eOFFPANEL_CANE, StartX + 140, StartY + 75);
}

void Interface::EventPSHOP_OFFMODE(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if(!this->Data[eOFFPANEL_MAIN].OnShow)
	{
		return;
	}

	if (this->IsWorkZone2(eOFFPANEL_YES))
	{
		DWORD Delay = (CurrentTick - this->Data[eOFFPANEL_YES].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eOFFPANEL_YES].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eOFFPANEL_YES].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eOFFPANEL_YES].EventTick = GetTickCount();
		//Func
		USERBUTTON_REQ pMsg;
		pMsg.Head.set(0xFB,0x26,sizeof(pMsg));
		DataSend((BYTE*)&pMsg,pMsg.Head.size);
		this->PSHOP_OFFMODE_STATE();
	}
	//
	if (this->IsWorkZone2(eOFFPANEL_CANE))
	{
		DWORD Delay = (CurrentTick - this->Data[eOFFPANEL_CANE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eOFFPANEL_CANE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eOFFPANEL_CANE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eOFFPANEL_CANE].EventTick = GetTickCount();
		//Func
		this->PSHOP_OFFMODE_STATE();
	}
}

void Interface::DrawJewelsBank()
{
	if (!this->Data[eJewelsBank].OnShow)
	{
		return;
	}
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);


	this->DrawGUI(eJewelsBank, StartX, StartY + 2);

	this->DrawFormat(eGold, StartX + 10, 110, 210, 3, gCustomMessage.GetMessage(184));
	//
	this->DrawGUI(eJewels_Des, StartX + 20, 150);
	if( gInterface.IsWorkZone2(eJewels_Des) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eJewels_Des].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawToolTip(StartX + 23, 135, gCustomMessage.GetMessage(185));
		gInterface.DrawColoredGUI(eJewels_Des, gInterface.Data[eJewels_Des].X, gInterface.Data[eJewels_Des].Y, Color);
	}

	this->DrawGUI(eJewels_Wid, StartX + 160, 150);
	if( gInterface.IsWorkZone2(eJewels_Wid) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eJewels_Wid].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawToolTip(StartX + 163, 135, gCustomMessage.GetMessage(186));
		gInterface.DrawColoredGUI(eJewels_Wid, gInterface.Data[eJewels_Wid].X, gInterface.Data[eJewels_Wid].Y, Color);
	}
	//
	this->DrawFormat(eWhite, StartX + 25, 215, 210, 1, gCustomMessage.GetMessage(187));
	this->DrawFormat(eWhite, StartX + 25, 232, 210, 1, gCustomMessage.GetMessage(188));
	this->DrawFormat(eWhite, StartX + 25, 249, 210, 1, gCustomMessage.GetMessage(189));
	this->DrawFormat(eWhite, StartX + 25, 266, 210, 1, gCustomMessage.GetMessage(190));
	this->DrawFormat(eWhite, StartX + 25, 283, 210, 1, gCustomMessage.GetMessage(191));
	this->DrawFormat(eWhite, StartX + 25, 300, 210, 1, gCustomMessage.GetMessage(192));

	this->DrawFormat(eGold, StartX + 180, 215, 150, 1, "%d", gObjUser.m_Bless);
	this->DrawFormat(eGold, StartX + 180, 232, 150, 1, "%d", gObjUser.m_Soul);
	this->DrawFormat(eGold, StartX + 180, 249, 150, 1, "%d", gObjUser.m_Life);
	this->DrawFormat(eGold, StartX + 180, 266, 150, 1, "%d", gObjUser.m_Chaos);
	this->DrawFormat(eGold, StartX + 180, 283, 150, 1, "%d", gObjUser.m_Creation);
	this->DrawFormat(eGold, StartX + 180, 300, 150, 1, "%d", gObjUser.m_Harmony);

	if (this->Data[eJewels_Des].Attribute == 1 || this->Data[eJewels_Wid].Attribute == 1)
	{
		this->DrawGUI(eJewels_Bless,StartX + 25,315);
		this->DrawFormat(eGold, StartX + 35, 319, 210, 1, gCustomMessage.GetMessage(193));
		this->DrawGUI(eJewels_Soul,StartX + 80,315);
		this->DrawFormat(eGold, StartX + 90, 319, 210, 1, gCustomMessage.GetMessage(194));
		this->DrawGUI(eJewels_Chaos,StartX + 135,315);
		this->DrawFormat(eGold, StartX + 142, 319, 210, 1, gCustomMessage.GetMessage(195));
		this->DrawGUI(eJewels_Life,StartX + 25,335);
		this->DrawFormat(eGold, StartX + 35, 339, 210, 1, gCustomMessage.GetMessage(196));
		this->DrawGUI(eJewels_Creation,StartX + 80,335);
		this->DrawFormat(eGold, StartX + 85, 339, 210, 1, gCustomMessage.GetMessage(197));
		this->DrawGUI(eJewels_Harmony,StartX + 135,335);
		this->DrawFormat(eGold, StartX + 139, 339, 210, 1, gCustomMessage.GetMessage(198));
		//
		if (JewelsType == 0)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredGUI(eJewels_Bless, gInterface.Data[eJewels_Bless].X, gInterface.Data[eJewels_Bless].Y, Color);
		}
		else if(JewelsType == 1)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredGUI(eJewels_Soul, gInterface.Data[eJewels_Soul].X, gInterface.Data[eJewels_Soul].Y, Color);
		}
		else if(JewelsType == 2)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredGUI(eJewels_Chaos, gInterface.Data[eJewels_Chaos].X, gInterface.Data[eJewels_Chaos].Y, Color);
		}
		else if(JewelsType == 3)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredGUI(eJewels_Life, gInterface.Data[eJewels_Life].X, gInterface.Data[eJewels_Life].Y, Color);
		}
		else if(JewelsType == 4)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredGUI(eJewels_Creation, gInterface.Data[eJewels_Creation].X, gInterface.Data[eJewels_Creation].Y, Color);
		}
		else if(JewelsType == 5)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredGUI(eJewels_Harmony, gInterface.Data[eJewels_Harmony].X, gInterface.Data[eJewels_Harmony].Y, Color);
		}
		//
		this->DrawGUI(eJewels_Box,StartX + 25,358);
		if(this->Data[eJewels_Des].Attribute == 1)
		{
			this->DrawFormat(eWhite, StartX + 33, 362, 210, 1, gCustomMessage.GetMessage(199));
		}
		if(this->Data[eJewels_Wid].Attribute == 1)
		{
			this->DrawFormat(eWhite, StartX + 33, 362, 210, 1, gCustomMessage.GetMessage(200));
		}
		this->DrawFormat(eExcellent, StartX + 100, 362, 100, 3, this->Data[eJewels_Box].StatValue);
		if (this->Data[eJewels_Box].Attribute == 1)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredGUI(eJewels_Box, gInterface.Data[eJewels_Box].X, gInterface.Data[eJewels_Box].Y, Color);
		}
		this->DrawGUI(eJewels_OK,StartX + 80, 385);
	}

	this->DrawGUI(eJewels_Close, StartX + MainWidth - this->Data[eJewels_Close].Width - 10.0f, this->Data[eVIP_TITLE].Height + this->Data[eJewels_Close].Height);
	// ----
	if( this->IsWorkZone2(eJewels_Close) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eJewels_Close].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eJewels_Close, this->Data[eJewels_Close].X, this->Data[eJewels_Close].Y, Color);
		this->DrawToolTip(this->Data[eJewels_Close].X + 5, this->Data[eJewels_Close].Y + 25, gCustomMessage.GetMessage(14));
	}
}

void Interface::EventJewelsBank(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if(!this->Data[eJewelsBank].OnShow)
	{
		return;
	}
	if (this->IsWorkZone2(eJewels_Des))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Des].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Des].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Des].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Des].EventTick = GetTickCount();
		//Func
		this->Data[eJewels_Des].Attribute = 1;
		this->Data[eJewels_Wid].Attribute = 0;
	}
	else if (this->IsWorkZone2(eJewels_Wid))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Wid].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Wid].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Wid].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Wid].EventTick = GetTickCount();
		//Func
		this->Data[eJewels_Wid].Attribute = 1;
		this->Data[eJewels_Des].Attribute = 0;
	}
	else if (this->IsWorkZone2(eJewels_Bless))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Bless].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Bless].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Bless].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Bless].EventTick = GetTickCount();
		//Func
		this->JewelsType = 0;
	}
	else if (this->IsWorkZone2(eJewels_Soul))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Soul].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Soul].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Soul].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Soul].EventTick = GetTickCount();
		//Func
		this->JewelsType = 1;
	}
	else if (this->IsWorkZone2(eJewels_Chaos))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Chaos].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Chaos].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Chaos].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Chaos].EventTick = GetTickCount();
		//Func
		this->JewelsType = 2;
	}
	else if (this->IsWorkZone2(eJewels_Life))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Life].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Life].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Life].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Life].EventTick = GetTickCount();
		//Func
		this->JewelsType = 3;
	}
	else if (this->IsWorkZone2(eJewels_Creation))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Creation].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Creation].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Creation].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Creation].EventTick = GetTickCount();
		//Func
		this->JewelsType = 4;
	}
	else if (this->IsWorkZone2(eJewels_Harmony))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Harmony].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Harmony].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Harmony].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Harmony].EventTick = GetTickCount();
		//Func
		this->JewelsType = 5;
	}
	else if (this->IsWorkZone2(eJewels_Box))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Box].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Box].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Box].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Box].EventTick = GetTickCount();
		//Func
		this->Data[eJewels_Box].Attribute = 1;
	}
	else if (this->IsWorkZone2(eJewels_OK))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_OK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_OK].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_OK].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_OK].EventTick = GetTickCount();
		//Func
		if(this->Data[eJewels_Des].Attribute == 1)
		{
			CGSendDepositJewels(JewelsType,atoi(this->Data[eJewels_Box].StatValue));
		}
		if(this->Data[eJewels_Wid].Attribute == 1)
		{
			CGSendWithdrawJewels(JewelsType,atoi(this->Data[eJewels_Box].StatValue));
		}
		this->Data[eJewels_Des].Attribute = 0;
		this->Data[eJewels_Wid].Attribute = 0;
		sprintf(this->Data[eJewels_Box].StatValue, "0");
		this->JewelsBank_State();
	}
	else if (this->IsWorkZone2(eJewels_Close))
	{
		DWORD Delay = (CurrentTick - this->Data[eJewels_Close].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eJewels_Close].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eJewels_Close].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eJewels_Close].EventTick = GetTickCount();
		//Func
		this->Data[eJewels_Des].Attribute = 0;
		this->Data[eJewels_Wid].Attribute = 0;
		sprintf(this->Data[eJewels_Box].StatValue, "0");
		this->JewelsBank_State();
	}
}

void Interface::DrawRPS()
{
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	if (this->m_RPSMode == 1)
	{
		if (this->CheckWindow(ObjWindow::Trade))
		{
			this->DrawGUI(eRPSMODE, StartX + 110, StartY + 290);

			if( this->IsWorkZone2(eRPSMODE) )
			{
				DWORD Color = eGray100;
				// ----
				if( this->Data[eRPSMODE].OnClick )
				{
					Color = eGray150;
				}
				// ----
				this->DrawToolTip(StartX + 105, StartY + 280, gCustomMessage.GetMessage(201));
				this->DrawColoredGUI(eRPSMODE, this->Data[eRPSMODE].X, this->Data[eRPSMODE].Y, Color);
			}
			if (this->Data[eRPSMODE].Attribute == 1)
			{
				this->DrawGUI(eRock, StartX + 20, StartY + 50);
				this->DrawGUI(ePaper, StartX + 20, StartY + 85);
				this->DrawGUI(eScissors, StartX + 20, StartY + 120);

				if( this->IsWorkZone2(eRock) )
				{
					DWORD Color = eGray100;
					// ----
					if( this->Data[eRock].OnClick )
					{
						Color = eGray150;
					}
					// ----
					this->DrawColoredGUI(eRock, this->Data[eRock].X, this->Data[eRock].Y, Color);
				}
				if( this->IsWorkZone2(ePaper))
				{
					DWORD Color = eGray100;
					// ----
					if( this->Data[ePaper].OnClick )
					{
						Color = eGray150;
					}
					// ----
					this->DrawColoredGUI(ePaper, this->Data[ePaper].X, this->Data[ePaper].Y, Color);
				}
				if( this->IsWorkZone2(eScissors))
				{
					DWORD Color = eGray100;
					// ----
					if( this->Data[eScissors].OnClick )
					{
						Color = eGray150;
					}
					// ----
					this->DrawColoredGUI(eScissors, this->Data[eScissors].X, this->Data[eScissors].Y, Color);
				}
				if (this->Data[eRock].Attribute == 1)
				{
					DWORD Color = eYellow;
					gInterface.DrawColoredGUI(eRock, gInterface.Data[eRock].X, gInterface.Data[eRock].Y, Color);
				}
				if (this->Data[ePaper].Attribute == 1)
				{
					DWORD Color = eYellow;
					gInterface.DrawColoredGUI(ePaper, gInterface.Data[ePaper].X, gInterface.Data[ePaper].Y, Color);
				}
				if (this->Data[eScissors].Attribute == 1)
				{
					DWORD Color = eYellow;
					gInterface.DrawColoredGUI(eScissors, gInterface.Data[eScissors].X, gInterface.Data[eScissors].Y, Color);
				}
			}
		}
		// ----
	}
}

void Interface::EventRPS_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->CheckWindow(ObjWindow::Trade) )
	{
		return;
	}

	if (this->m_RPSMode == 1)
	{
		if (this->IsWorkZone2(eRock))
		{
			DWORD Delay = (CurrentTick - this->Data[eRock].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eRock].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eRock].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eRock].EventTick = GetTickCount();
			//Func
			RPSMode(1);
			pDrawMessage(gCustomMessage.GetMessage(202),1);
			this->Data[eRock].Attribute = 1;
			this->Data[ePaper].Attribute = 0;
			this->Data[eScissors].Attribute = 0;
		}
		//
		else if (this->IsWorkZone2(ePaper))
		{
			DWORD Delay = (CurrentTick - this->Data[ePaper].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[ePaper].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[ePaper].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[ePaper].EventTick = GetTickCount();
			//Func
			RPSMode(2);
			pDrawMessage(gCustomMessage.GetMessage(203),1);
			this->Data[eRock].Attribute = 0;
			this->Data[ePaper].Attribute = 1;
			this->Data[eScissors].Attribute = 0;
		}
		//
		else if (this->IsWorkZone2(eScissors))
		{
			DWORD Delay = (CurrentTick - this->Data[eScissors].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eScissors].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eScissors].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eScissors].EventTick = GetTickCount();
			//Func
			this->Data[eRock].Attribute = 0;
			this->Data[ePaper].Attribute = 0;
			this->Data[eScissors].Attribute = 1;
			RPSMode(3);
			pDrawMessage(gCustomMessage.GetMessage(204),1);
		}
		else if (this->IsWorkZone2(eRPSMODE))
		{
			DWORD Delay = (CurrentTick - this->Data[eRPSMODE].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eRPSMODE].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[eRPSMODE].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			// ----
			this->Data[eRPSMODE].EventTick = GetTickCount();
			//Func
			this->Data[eRPSMODE].Attribute = 1;
		}
	}
}

void Interface::DrawNewsWindow()
{
	if( !this->Data[eNEWS_MAIN].OnShow )
	{
		return;
	}
	// ----
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	this->DrawGUI(eNEWS_MAIN, StartX, StartY + 2);
	this->DrawGUI(eNEWS_TITLE, StartX, StartY);
	StartY = this->DrawRepeatGUI(eNEWS_FRAME, StartX, StartY + 67.0, 13);
	this->DrawGUI(eNEWS_FOOTER, StartX, StartY);
	this->DrawGUI(eNEWS_CLOSE, StartX + MainWidth - this->Data[eNEWS_CLOSE].Width, this->Data[eNEWS_TITLE].Height + this->Data[eNEWS_CLOSE].Height + 2);
	// ----
	if( this->IsWorkZone2(eNEWS_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eNEWS_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eNEWS_CLOSE, this->Data[eNEWS_CLOSE].X, this->Data[eNEWS_CLOSE].Y, Color);
		this->DrawToolTip(this->Data[eNEWS_CLOSE].X + 5, this->Data[eNEWS_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
	}
	// ----
	this->DrawFormat(eGold, StartX + 10, 110, 210, 3, gCustomMessage.GetMessage(205));
	// ----
	if( this->Data[eNEWS_MAIN].Attribute == 0 )
	{
		for( int i = 0; i < gNewsBoard.m_LoadedCount; i++ )
		{
			this->DrawGUI(eNEWS_INFOBG, StartX + 30, 140 + (i * 21));
			// ----
			if( IsWorkZone(StartX + 30, 140 + (i * 21), StartX + 200, 160 + (i * 21)) )
			{
				this->DrawColoredGUI(eNEWS_INFOBG, StartX + 30,  140 + (i * 21), pMakeColor(255, 204, 20, 200));
			}
			// ----
			this->DrawFormat(eGold, StartX + 18, 142 + (i * 21), 65, 3, gNewsBoard.m_Data[i].Title.Date);
			this->DrawFormat(eOrange, StartX + 18, 148 + (i * 21), 65, 3, gNewsBoard.m_Data[i].Title.Time);
			this->DrawFormat(eWhite, StartX + 80, 145 + (i * 21), 190, 1, gNewsBoard.m_Data[i].Title.Text);
		}
		// ----
		this->DrawFormat(eBlue, StartX + 8, 130, 210, 3, gCustomMessage.GetMessage(206), gNewsBoard.m_LastRefreshMin);
	}
	else
	{
		BYTE ID = this->Data[eNEWS_MAIN].Attribute - 10;
		// ----
		this->DrawGUI(eNEWS_INFOBG, StartX + 30, 140);
		this->DrawFormat(eGold, StartX + 18, 142, 65, 3, gNewsBoard.m_Data[ID].Title.Date);
		this->DrawFormat(eOrange, StartX + 18, 148, 65, 3, gNewsBoard.m_Data[ID].Title.Time);
		this->DrawFormat(eWhite, StartX + 80, 145, 190, 1, gNewsBoard.m_Data[ID].Title.Text);
		this->DrawFormat(eWhite, StartX + 15, 170, 200, 1, gNewsBoard.m_Data[ID].Text);
		// ----
		this->DrawGUI(eNEWS_BACK, ButtonX, this->Data[eNEWS_FOOTER].Y + 10);
		this->DrawFormat(eWhite, StartX + 8, this->Data[eNEWS_FOOTER].Y + 20, 210, 3, gCustomMessage.GetMessage(115));
		this->DrawGUI(eNEWS_DIV, StartX, this->Data[eNEWS_FOOTER].Y - 10);
		// ----
		if( IsWorkZone2(eNEWS_BACK) )
		{
			DWORD Color = eGray100;
			// ----
			if( this->Data[eNEWS_BACK].OnClick )
			{
				Color = eGray150;
			}
			// ----
			this->DrawColoredGUI(eNEWS_BACK, this->Data[eNEWS_BACK].X, this->Data[eNEWS_BACK].Y, Color);
		}
		// ----
		this->DrawFormat(eBlue, StartX + 8, 130, 210, 3, gCustomMessage.GetMessage(206), gNewsBoard.m_Data[ID].LastRefreshMin);
	}
}

bool Interface::EventNewsWindow_Main(DWORD Event)
{
	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	// ----
	for( int i = 0; i < gNewsBoard.m_LoadedCount; i++ )
	{
		if( this->IsWorkZone(StartX + 30, 140 + (i * 21), StartX + 200, 161 + (i * 21)) )
		{
			if( Event == WM_LBUTTONDOWN && this->Data[eNEWS_MAIN].Attribute == 0 )
			{
				this->Data[eNEWS_MAIN].Attribute = i + 10;
				gNewsBoard.ReqOpenItem(i);
			}
		}
	}
	// ----
	this->EventNewsWindow_Close(Event);
	this->EventNewsWindow_Back(Event);
	// ----
	return true;
}

bool Interface::EventNewsWindow_Close(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eNEWS_CLOSE].EventTick);
	// ----
	if( !this->Data[eNEWS_MAIN].OnShow || !IsWorkZone2(eNEWS_CLOSE) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eNEWS_CLOSE].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eNEWS_CLOSE].OnClick = false;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eNEWS_CLOSE].EventTick	= GetTickCount();
	this->Data[eNEWS_MAIN].Attribute	= 0;
	this->Data[eNEWS_MAIN].Close();
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool Interface::EventNewsWindow_Back(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - this->Data[eNEWS_BACK].EventTick);
	// ----
	if( !this->Data[eNEWS_MAIN].OnShow || !IsWorkZone2(eNEWS_BACK) )
	{
		return false;
	}
	// ----
	if( Event == WM_LBUTTONDOWN )
	{
		this->Data[eNEWS_BACK].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}
	// ----
	this->Data[eNEWS_BACK].OnClick = false;;
	pSetCursorFocus = false;
	// ----
	if( Delay < 500 )
	{
		return false;
	}
	// ----
	this->Data[eNEWS_BACK].EventTick = GetTickCount();
	this->Data[eNEWS_MAIN].Attribute = 0;
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------
void Interface::DrawFruit()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(MoveList) ||
		this->CheckWindow(SkillTree))
		return;

	if( !this->Data[eFruitMain].OnShow )
	{
		return;
	}

	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 80.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	pDrawImage(iGfxDialoge, StartX + 50, StartY + 50, 150, 200, 1, 1, 1.0, 1.0, 1, 1, 0); //223 280
	pDrawImage(iNewuiDialogHr, StartX + 50, StartY + 115, 145, 5, 1, 1, 1.0, 1.0, 1, 1, 0); //235 210

	this->DrawFormat(eGold, StartX + 15, StartY + 63, 223, 3, gCustomMessage.GetMessage(244));
	int TotalPoint;
	TotalPoint = gObjUser.FStrength + gObjUser.FDexterity + gObjUser.FVitality + gObjUser.FEnergy + gObjUser.FLeadership;
    glColor4f(0.0, 0.0, 0.0, 0.7);
	float BarWidth = 130.1f * (TotalPoint / (TotalPoint + gObjUser.FMaxPoint * 1.0f));
    pDrawBarForm((float)StartX + 60, (float)StartY + 85, 130, 10.0, 0, 0);
	pDrawBarForm((float)StartX + 160, (float)StartY + 134, 30, 13.0, 0, 0);
	pDrawBarForm((float)StartX + 160, (float)StartY + 154, 30, 13.0, 0, 0);
	pDrawBarForm((float)StartX + 160, (float)StartY + 174, 30, 13.0, 0, 0);
	pDrawBarForm((float)StartX + 160, (float)StartY + 194, 30, 13.0, 0, 0);
	pDrawBarForm((float)StartX + 160, (float)StartY + 214, 30, 13.0, 0, 0);
	glColor3f(2.0, 2.0, 0.0);
    pDrawBarForm((float)StartX + 62, (float)StartY + 87, BarWidth, 6, 0, 0);
	this->DrawItem2(StartX + 40,StartY + 100,50,50,ITEM(13,15),SET_ITEMOPT_LEVEL(3),0,0,0); //Str
	this->DrawItem2(StartX + 40,StartY + 120,50,50,ITEM(13,15),SET_ITEMOPT_LEVEL(2),0,0,0); //Agi
	this->DrawItem2(StartX + 40,StartY + 140,50,50,ITEM(13,15),SET_ITEMOPT_LEVEL(1),0,0,0); //Vit
	this->DrawItem2(StartX + 40,StartY + 160,50,50,ITEM(13,15),SET_ITEMOPT_LEVEL(0),0,0,0); //Ene
	this->DrawItem2(StartX + 40,StartY + 180,50,50,ITEM(13,15),SET_ITEMOPT_LEVEL(4),0,0,0); //Cmd
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 100, StartY + 100, Fcolor->Gold, Fcolor->Trans, 30, (LPINT)5, gCustomMessage.GetMessage(245),TotalPoint,gObjUser.FMaxPoint);
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 85, StartY + 135, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, gCustomMessage.GetMessage(246));
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 85, StartY + 155, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, gCustomMessage.GetMessage(247));
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 85, StartY + 175, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, gCustomMessage.GetMessage(248));
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 85, StartY + 195, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, gCustomMessage.GetMessage(249));
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 85, StartY + 215, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, gCustomMessage.GetMessage(250));

	Font[TAHOMA_BOLD_13]->DrawText(StartX + 165, StartY + 135, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, "%d",gObjUser.FStrength);
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 165, StartY + 155, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, "%d",gObjUser.FDexterity);
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 165, StartY + 175, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, "%d",gObjUser.FVitality);
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 165, StartY + 195, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, "%d",gObjUser.FEnergy);
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 165, StartY + 215, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, "%d",gObjUser.FLeadership);

	this->DrawGUI(eFruitClose,StartX + 165, StartY + 55);
	if( this->IsWorkZone2(eFruitClose) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eFruitClose].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eFruitClose, this->Data[eFruitClose].X, this->Data[eFruitClose].Y, Color);
	}
}

void Interface::EventFruitWindow_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !gInterface.Data[eFruitMain].OnShow )
	{
		return;
	}

	if (this->IsWorkZone2(eFruitClose))
	{
		DWORD Delay = (CurrentTick - this->Data[eFruitClose].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eFruitClose].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eFruitClose].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eFruitClose].EventTick = GetTickCount();
		//Func
		this->Fruit_State();
	}
}
// ----------------------------------------------------------------------------------------------
void Interface::DrawAttention()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(MoveList) ||
		this->CheckWindow(SkillTree))
		return;

	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 80.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	pSetBlend(true);
    glColor4f(0.0, 0.0, 0.0, 0.4);
    pDrawBarForm(StartX + 50, StartY + 50, 150, 100.0, 0, 0);
	pGLSwitchBlend();	// for blend objects	
	glColor3f(1.0, 1.0, 1.0);
	pGLSwitch();
	pSetBlend(false);

	pDrawImage(iNewuiDialogHr, StartX + 60, StartY + 65, 130, 4, 1, 1, 1.0, 1.0, 1, 1, 0); //235 210
	Font[TAHOMA_BOLD_13]->DrawText(StartX + 110, StartY + 55, Fcolor->Gold, Fcolor->Trans, 30, (LPINT)5, "Attention");
	pDrawImage(iNewuiDialogHr, StartX + 60, StartY + 110, 130, 4, 1, 1, 1.0, 1.0, 1, 1, 0); //235 210
	pDrawButton(iGfxBtnSmall2, StartX + 100, StartY + 120,52,22,0,0);

}
// ----------------------------------------------------------------------------------------------
void Interface::DrawGiftCode()
{
	if( !this->Data[eGIFTCODE_MAIN].OnShow )
	{
		return;
	}

	//pSetCursorFocus = true;

	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 130;
	float StartY			= 100.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);
	// ----
	gInterface.DrawAnimatedGUI(eGIFTCODE_MAIN, StartX+4, StartY + 4);
	gInterface.DrawAnimatedGUI(eGIFTCODE_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eGIFTCODE_FRAME, StartX, StartY + 67.0, 0);
	gInterface.DrawAnimatedGUI(eGIFTCODE_FOOTER, StartX, StartY);
	// ----
	gInterface.DrawFormat(eGold, StartX + 10, 110, 210, 3, gCustomMessage.GetMessage(253));
	// ---- 
	//pDrawGUI(0x7AA3,230,140,170,21);
	this->DrawGUI(eGIFTCODE_BOX,230,140);
	if (this->Data[eGIFTCODE_BOX].Attribute == 1)
	{
		DWORD Color = eGray100;
		//this->DrawColoredAnimatedGUI(ObjectIDs[i], ButtonX - 35, this->Data[eSTATSADD_MAIN].Y + 63 + ((i+1)*21), Color);
		gInterface.DrawColoredGUI(eGIFTCODE_BOX, gInterface.Data[eGIFTCODE_BOX].X, gInterface.Data[eGIFTCODE_BOX].Y, Color);
	}
	gInterface.DrawFormat(eGold, 240, 144, 50, 3, gCustomMessage.GetMessage(254));
	this->DrawFormat(eWhite, 280, 144, 150, 3, this->Data[eGIFTCODE_BOX].StatValue);
	gInterface.DrawAnimatedGUI(eGIFTCODE_OK, StartX+30, StartY /*- 5*/);
	gInterface.DrawFormat(eWhite, StartX + 35, StartY+5 + 5, 50, 3, gCustomMessage.GetMessage(113));

	if( gInterface.IsWorkZone2(eGIFTCODE_OK) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eGIFTCODE_OK].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eGIFTCODE_OK, gInterface.Data[eGIFTCODE_OK].X, gInterface.Data[eGIFTCODE_OK].Y, Color);
	}
	// ---- 
	gInterface.DrawAnimatedGUI(eGIFTCODE_CLOSE, StartX + 70 + 62, StartY /*- 5*/ );
	gInterface.DrawFormat(eWhite, StartX + 75 + 62, StartY+5 + 5, 50, 3, gCustomMessage.GetMessage(14));

	if( gInterface.IsWorkZone2(eGIFTCODE_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[eGIFTCODE_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(eGIFTCODE_CLOSE, gInterface.Data[eGIFTCODE_CLOSE].X, gInterface.Data[eGIFTCODE_CLOSE].Y, Color);
	}
}

void Interface::EventGiftCode_Main(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();

	if( !this->Data[eGIFTCODE_MAIN].OnShow )
	{
		return;
	}
	
	if (this->IsWorkZone2(eGIFTCODE_BOX))
	{
		DWORD Delay = (CurrentTick - this->Data[eGIFTCODE_BOX].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eGIFTCODE_BOX].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eGIFTCODE_BOX].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eGIFTCODE_BOX].EventTick = GetTickCount();
		//Func
		this->Data[eGIFTCODE_BOX].Attribute = 1;
	}

	if (this->IsWorkZone2(eGIFTCODE_OK))
	{
		DWORD Delay = (CurrentTick - this->Data[eGIFTCODE_OK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eGIFTCODE_OK].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eGIFTCODE_OK].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eGIFTCODE_OK].EventTick = GetTickCount();
		//Func
		PMSG_GIFTCODE_SEND pMsg;
		pMsg.ID = atoi(this->Data[eGIFTCODE_BOX].StatValue);
		pMsg.header.set(0xFF,0x25,sizeof(pMsg));
		DataSend((BYTE*)&pMsg,pMsg.header.size);
		this->Data[eGIFTCODE_MAIN].Close();
		sprintf(this->Data[eGIFTCODE_BOX].StatValue, "0");
	}

	if (this->IsWorkZone2(eGIFTCODE_CLOSE))
	{
		DWORD Delay = (CurrentTick - this->Data[eGIFTCODE_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eGIFTCODE_CLOSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eGIFTCODE_CLOSE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		this->Data[eGIFTCODE_CLOSE].EventTick = GetTickCount();
		//Func
		this->Data[eGIFTCODE_MAIN].Close();
		sprintf(this->Data[eGIFTCODE_BOX].StatValue, "0");
	}
}


void Interface::DrawUsersPanel()
{
	float PosX = this->GetResizeX(eUSERSPANELBG);
	// ----
	if( this->CheckWindow(CashShop)
		||	this->CheckWindow(SkillTree)
		||	this->CheckWindow(FullMap) 
		||	this->CheckWindow(MoveList) 
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store)) 
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		return;
	}
	// ----
#ifdef __POS_CUR__
	this->DrawFormat(eAncient, gObjUser.m_CursorX + 25, gObjUser.m_CursorY - 10, 100, 1, "X[%d] Y[%d]", gObjUser.m_CursorX, gObjUser.m_CursorY);
#endif

	this->DrawGUI(eUSERSPANELBG, PosX, 0);
	this->DrawGUI(eUSERSPANEL_BUTTON, PosX +2, 1);
	// ----
	if( IsWorkZone2(eUSERSPANEL_BUTTON) )
	{
		this->DrawToolTip(PosX +2 - 5, 25, "Users Panel");
		// ----
		if( this->Data[eUSERSPANEL_BUTTON].OnClick )
		{
			this->DrawColoredGUI(eUSERSPANEL_BUTTON, PosX +2, 1, pMakeColor(40, 20, 3, 130));
			return;
		}
		// ----
		this->DrawColoredGUI(eUSERSPANEL_BUTTON, PosX +2, 1, pMakeColor(255, 204, 20, 200));
	}
}

// ----------------------------------------------------------------------------------------------

void Interface::EventUsersPanel(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	// ----
	if( this->CheckWindow(CashShop)
		||	this->CheckWindow(SkillTree)
		||	this->CheckWindow(FullMap) 
		||	this->CheckWindow(MoveList) 
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(ExpandInventory) 
		&& this->CheckWindow(Store)) 
		||  (this->CheckWindow(Inventory) 
		&& this->CheckWindow(Warehouse) 
		&& this->CheckWindow(ExpandWarehouse)) )
	{
		return;
	}
	// ----
	if( IsWorkZone2(eUSERSPANEL_BUTTON) )
	{
		DWORD Delay	= (CurrentTick - this->Data[eUSERSPANEL_BUTTON].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eUSERSPANEL_BUTTON].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eUSERSPANEL_BUTTON].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eUSERSPANEL_BUTTON].EventTick = GetTickCount();
		// ----
		gUserPanel.UserPanelSwitchState();
	}
}

int  getNumberOfDays(int month, int year)
{
	//leap year condition, if month is 2
	if( month == 2)
	{
		if((year%400==0) || (year%4==0 && year%100!=0))	
		{
			return 29;
		}
		else	
		{
			return 28;
		}
	}
	//months which has 31 days
	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8
	||month == 10 || month==12)	
	{
		return 31;
	}
	
	return 30;
} 

void Interface::DrawEventTableWindow()
{

	if( !this->Data[eEVENTTABLE_MAIN].OnShow )
	{
		return;
	}

	pSetCursorFocus = true;

	float MainWidth			= 190.0;
	float MainHeight		= this->Data[eEVENTTABLE_MAIN].Height;
	float StartY			= 0;
	float StartX			= MAX_WIN_WIDTH - this->Data[eEVENTTABLE_MAIN].Width;
	float MainCenter		= StartX + (MainWidth / 3);
	//int x = GetPrivateProfileIntA("Graphics", "X", 0, "./Settings.ini");
	//int y = GetPrivateProfileIntA("Graphics", "Y", 60, "./Settings.ini");

	this->DrawGUI(eEVENTTABLE_MAIN, StartX, StartY);
	this->DrawGUI(eEVENTTABLE_LEFT,StartX,StartY+this->Data[eEVENTTABLE_TITLE].Height);
	this->DrawGUI(eEVENTTABLE_RIGHT,MAX_WIN_WIDTH-this->Data[eEVENTTABLE_LEFT].Width,StartY+this->Data[eEVENTTABLE_TITLE].Height);
	this->DrawGUI(eEVENTTABLE_TITLE, StartX, StartY);
	this->DrawGUI(eEVENTTABLE_FOOTER, StartX, 384);
	this->DrawGUI(eEVENTTABLE_CLOSE, StartX + MainWidth - this->Data[eEVENTTABLE_CLOSE].Width+3, -1);
	// ----
	//gNewInterface.TextDraw(StartX + MainWidth/2,MainHeight-50,0,1,eGold,0,eCenter,gFont[ARIAL_BLACK_16]->m_Font,"%d / %d",gEventTimer.m_CurrentPage+1,gEventTimer.m_PageCount+1);

	Font[TAHOMA_BOLD_13]->DrawText(StartX + 87,MainHeight-50, Fcolor->White, Fcolor->Trans, 15, (LPINT)5, "%d / %d",gEventTimer.m_CurrentPage+1,gEventTimer.m_PageCount+1);

	gInterface.DrawGUI(eARROW_LEFT2,StartX+60,MainHeight-57);

	gInterface.DrawGUI(eARROW_RIGHT2,StartX+110,MainHeight-57);
	// ----
	//gNewInterface.TextDraw(StartX+MainWidth/2,StartY+12,0,1,eWhite,0,8,pFontBold,"[Event Table]"); // Window Name
	Font[TAHOMA_BOLD_14]->DrawText(StartX+70,StartY+12, Fcolor->Red, Fcolor->Trans, 15, (LPINT)5, gCustomMessage.GetMessage(256));
	// ----
	int max_per_page = 20;
	int count = 0;

	//g_Console.AddMessage(5,"MaxGroup = %d",gEventTimer.m_MaxGroup);
	CTime local_time(time(0) - this->m_TimeDiff);

	/*
	int font = ARIAL_BLACK_16;

	if (*(DWORD*)MAIN_RESOLUTION == 1)
	{
		font = ARIAL_BLACK_12;
	}
	else if (*(DWORD*)MAIN_RESOLUTION == 2)
	{
		font = ARIAL_BLACK_13;
	}
	else if (*(DWORD*)MAIN_RESOLUTION == 3)
	{
		font = ARIAL_BLACK_14;
	}
	else if (*(DWORD*)MAIN_RESOLUTION == 15)
	{
		font = ARIAL_BLACK_12;
	}
	else if (*(DWORD*)MAIN_RESOLUTION == 17)
	{
		font = ARIAL_BLACK_14;
	}
	*/
	int group = -1;
	for (group=gEventTimer.m_CurrentPage*max_per_page;group<gEventTimer.m_MaxGroup+1;group++) // switch for all grouos
	{
		if (count >= max_per_page)
		{
			break;
		}
		CTime min_time = (local_time.GetTime() + 86400);
		int min_index = -1;
		std::vector<EVENTTIMER_INFO> mTimer = gEventTimer.getEventTimerByGroup(group); // get all events for this group

		for	(int i=0;i<mTimer.size();i++) //switch for all events in this group
		{
			if (mTimer.at(i).DayOfWeek == -1)
			{
				CTime eventtime(local_time.GetYear(),local_time.GetMonth(),local_time.GetDay(),mTimer.at(i).Hour,mTimer.at(i).Minute,0,-1); //get time for this event
				
				if (eventtime < local_time) 
				{
					eventtime+=86400; // åñëè åâåíò óæå áûë ñåãîäíÿ, òî ïðèáàâëÿåì ñóòêè, ñëåäîâàòåëüíî åâåíò äîëæåí áûòü çàâòðà
				}
				
				if (eventtime < min_time)
				{
					min_time = eventtime;
					min_index = i;
				}

			}
			else
			{
				for	(int j=0;j<8;j++)
				{
					int year = local_time.GetYear();
					int month = local_time.GetMonth();
					int day = local_time.GetDay();

					if (local_time.GetDay()+j > getNumberOfDays(month,year))
					{
						day = local_time.GetDay()+j - getNumberOfDays(month,year);
						if (month+1>12)
						{
							year++;
							month = 1;
						}
						else
						{
							month++;
						}
						
					}

					//CTime eventTime(local_time.GetYear(),local_time.GetMonth(),local_time.GetDay()+j,gEventTimer.m_EventTimerInfo[i].Hour,gEventTimer.m_EventTimerInfo[i].Minute,0,-1);
					CTime eventTime(year,month,day,gEventTimer.m_EventTimerInfo[i].Hour,gEventTimer.m_EventTimerInfo[i].Minute,0,-1);
					if (eventTime.GetDayOfWeek() == mTimer.at(i).DayOfWeek)
					{
						if (eventTime.GetDay() == local_time.GetDay() && eventTime.GetHour() <= local_time.GetHour() && eventTime.GetMinute() < local_time.GetMinute())
						{
							continue;
						}
				
						min_time = eventTime;
						min_index = i;
					}
				}
			}
		}

		if (min_index != -1)
		{
			CTimeSpan lol = min_time-local_time;

			//gNewInterface.TextDraw(StartX+15,StartY+55+(count*15),0,1,eGold,0,eLeftToRight,gFont[font]->m_Font,"%d. %s:",group+1,mTimer[min_index].Name);
			//gNewInterface.TextDraw(StartX+15,StartY+55+(count*15),0,1,eGold,0,eLeftToRight,gFont[font]->m_Font,"%d. %s:",group+1,gEventTimer.GetText(mTimer.at(min_index).TextIndex));
			//gNewInterface.TextDraw(StartX+MainWidth-15,StartY+55+(count*15),0,1,eBlue,0,eRightToLeft,gFont[font]->m_Font,"%dd %dh %dm %ds",(int)lol.GetDays(),lol.GetHours(),lol.GetMinutes(),lol.GetSeconds());
			Font[TAHOMA_BOLD_13]->DrawText(StartX+15,StartY+55+(count*15), Fcolor->White, Fcolor->Trans, 15, (LPINT)5, "%d. %s:",group+1,gEventTimer.GetText(mTimer.at(min_index).TextIndex));
			Font[TAHOMA_BOLD_13]->DrawText(StartX + 120,StartY+55+(count*15), Fcolor->Orange, Fcolor->Trans, 15, (LPINT)5, "%dd %dh %dm %ds",(int)lol.GetDays(),lol.GetHours(),lol.GetMinutes(),lol.GetSeconds());

			pDrawGUI(0x7B5E, StartX+13, StartY+55+(count*15)+10, 82.0, 2.0); // Äåëèòåëü ìåëêèé 1
			pDrawGUI(0x7B5E, StartX+13 + 82, StartY+55+(count*15)+10, 82.0, 2.0); // Äåëèòåëü ìåëêèé 2

			count++;
		}
	}
	// ----
	if( this->IsWorkZone2(eEVENTTABLE_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eEVENTTABLE_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eEVENTTABLE_CLOSE, StartX + MainWidth - this->Data[eEVENTTABLE_CLOSE].Width+3, -1, Color);
		this->DrawToolTip(this->Data[eEVENTTABLE_CLOSE].X + 5, this->Data[eEVENTTABLE_CLOSE].Y + 24, "Close");
	}

	if( this->IsWorkZone2(eARROW_LEFT2) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eARROW_LEFT2].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eARROW_LEFT2, StartX+60,MainHeight-57, Color);
	}

	if( this->IsWorkZone2(eARROW_RIGHT2) )
	{
		DWORD Color = eGray100;
		// ----
		if( this->Data[eARROW_RIGHT2].OnClick )
		{
			Color = eGray150;
		}
		// ----
		this->DrawColoredGUI(eARROW_RIGHT2, StartX+110,MainHeight-57, Color);
	}
}

void Interface::EventEventTableWindow(DWORD Event)
{
	if (!this->Data[eEVENTTABLE_MAIN].OnShow)
	{
		return;
	}

	DWORD CurrentTick	= GetTickCount();

	if (this->IsWorkZone2(eEVENTTABLE_CLOSE))
	{
		DWORD Delay			= (CurrentTick - this->Data[eEVENTTABLE_CLOSE].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eEVENTTABLE_CLOSE].OnClick = true;
			return;
		}
		// ----
		this->Data[eEVENTTABLE_CLOSE].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eEVENTTABLE_CLOSE].EventTick = GetTickCount();
		gEventTimer.EventTimerSwitch();
	}
	else if(this->IsWorkZone2(eARROW_LEFT2))
	{
		DWORD Delay			= (CurrentTick - this->Data[eARROW_LEFT2].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eARROW_LEFT2].OnClick = true;
			return;
		}
		// ----
		this->Data[eARROW_LEFT2].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eARROW_LEFT2].EventTick = GetTickCount();
		//
		if (gEventTimer.m_CurrentPage > 0)
			gEventTimer.m_CurrentPage--;
	}
	else if (this->IsWorkZone2(eARROW_RIGHT2))
	{
		DWORD Delay			= (CurrentTick - this->Data[eARROW_RIGHT2].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eARROW_RIGHT2].OnClick = true;
			return;
		}
		// ----
		this->Data[eARROW_RIGHT2].OnClick = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eARROW_RIGHT2].EventTick = GetTickCount();
		//
		if (gEventTimer.m_CurrentPage<gEventTimer.m_PageCount)
		{
			gEventTimer.m_CurrentPage++;
		}
	}
	// ----
}
//
// ----------------------------------------------------------------------------------------------

void Interface::DrawWarehouseUI()
{
	if( !this->Data[eWAREHOUSE_MAIN].OnShow)
	{
		return;
	}


	float MainWidth			= 230.0;
	float MainHeight		= 313.0;
	float StartY			= 80.0;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	pSetBlend(true);
    glColor4f(0.0, 0.0, 0.0, 0.4);
    pDrawBarForm(StartX + 50, StartY + 50, 150, 100.0, 0, 0);
	pGLSwitchBlend();	// for blend objects	
	glColor3f(1.0, 1.0, 1.0);
	pGLSwitch();
	pSetBlend(false);

	Font[TAHOMA_BOLD_14]->DrawText(StartX + 100, StartY + 54, Fcolor->Gold, Fcolor->Trans, 30, (LPINT)5, gCustomMessage.GetMessage(258));
	pDrawImage(iNewuiDialogHr, StartX + 60, StartY + 65, 130, 4, 1, 1, 1.0, 1.0, 1, 1, 0); //235 210
	this->DrawGUI(eWAREHOUSE,StartX + 80, StartY + 78);
	Font[TAHOMA_BOLD_14]->DrawText(StartX + 120, StartY + 85, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, "%d/%d", gObjUser.m_WarehouseNumber + 1,gObjUser.m_MaxWarehouse +1);
	this->DrawGUI(eWAREHOUSE1,StartX + 150, StartY + 78);
	pDrawImage(iNewuiDialogHr, StartX + 60, StartY + 110, 130, 4, 1, 1, 1.0, 1.0, 1, 1, 0); //235 210
	this->DrawGUI(eWAREHOUSE_OPEN,StartX + 100, StartY + 120);
	//pDrawButton(iGfxBtnSmall2, StartX + 100, StartY + 120,52,22,0,0);
	Font[TAHOMA_BOLD_15]->DrawText(StartX + 115, StartY + 125, Fcolor->White, Fcolor->Trans, 30, (LPINT)5, gCustomMessage.GetMessage(259));
}

void Interface::EventWarehouseUI(DWORD Event)
{
	if( !this->Data[eWAREHOUSE_MAIN].OnShow)
	{
		return;
	}

	DWORD CurrentTick	= GetTickCount();
	// ----
	if( IsWorkZone2(eWAREHOUSE) )
	{
		DWORD Delay	= (CurrentTick - this->Data[eWAREHOUSE].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eWAREHOUSE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eWAREHOUSE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eWAREHOUSE].EventTick = GetTickCount();
		// ----
		if (gObjUser.m_WarehouseNumber > 0)
		{
			gObjUser.m_WarehouseNumber--;
		}
	}
	else if( IsWorkZone2(eWAREHOUSE1) )
	{
		DWORD Delay	= (CurrentTick - this->Data[eWAREHOUSE1].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eWAREHOUSE1].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eWAREHOUSE1].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eWAREHOUSE1].EventTick = GetTickCount();
		// ----
		if (gObjUser.m_WarehouseNumber < gObjUser.m_MaxWarehouse)
		{
			gObjUser.m_WarehouseNumber++;
		}
	}
	else if( IsWorkZone2(eWAREHOUSE_OPEN) )
	{
		DWORD Delay	= (CurrentTick - this->Data[eWAREHOUSE_OPEN].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[eWAREHOUSE_OPEN].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[eWAREHOUSE_OPEN].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[eWAREHOUSE_OPEN].EventTick = GetTickCount();
		// ----
		PMSG_CHANGEWAREHOUSE_RECV pRequest;
		pRequest.Number = gObjUser.m_WarehouseNumber;
		pRequest.header.set(0xFF,0xE5,sizeof(pRequest));
		DataSend((BYTE*)&pRequest,pRequest.header.size);
		gInterface.Data[eWAREHOUSE_MAIN].OnShow = false;
	}
}
// ----------------------------------------------------------------------------------------------
void Interface::PartyInterface()
{
	if (this->MiniMapCheck() || this->CombinedChecks())
		{
			return;
		}
if(gInterface.m_PartyTrace == 1)
{
	if(pPartyMemberCount == 2)
	{
		pDrawGUI(0x789B, 600, 17, 9.0, 10.0);
		pDrawGUI(0x789B, 600, 41, 9.0, 10.0);
	}
	else if(pPartyMemberCount == 3)
	{
		pDrawGUI(0x789B, 600, 17, 9.0, 10.0);
		pDrawGUI(0x789B, 600, 41, 9.0, 10.0);
		pDrawGUI(0x789B, 600, 65, 9.0, 10.0);
	}
	else if(pPartyMemberCount == 4)
	{
		pDrawGUI(0x789B, 600, 17, 9.0, 10.0);
		pDrawGUI(0x789B, 600, 41, 9.0, 10.0);
		pDrawGUI(0x789B, 600, 65, 9.0, 10.0);	
		pDrawGUI(0x789B, 600, 89, 9.0, 10.0);
	}
	else if(pPartyMemberCount == 5)
	{
		pDrawGUI(0x789B, 600, 17, 9.0, 10.0);
		pDrawGUI(0x789B, 600, 41, 9.0, 10.0);
		pDrawGUI(0x789B, 600, 65, 9.0, 10.0);
		pDrawGUI(0x789B, 600, 89, 9.0, 10.0);
		pDrawGUI(0x789B, 600, 113, 9.0, 10.0);
	}
}
if(gInterface.m_PartyLeader == 1)
{
	if(pPartyMemberCount == 2)
	{
		pDrawGUI(0x789A, 614, 41, 9.0, 10.0);
	}
	else if(pPartyMemberCount == 3)
	{
		pDrawGUI(0x789A, 614, 41, 9.0, 10.0);
		pDrawGUI(0x789A, 614, 65, 9.0, 10.0);
	}
	else if(pPartyMemberCount == 4)
	{
		pDrawGUI(0x789A, 614, 41, 9.0, 10.0);
		pDrawGUI(0x789A, 614, 65, 9.0, 10.0);
		pDrawGUI(0x789A, 614, 89, 9.0, 10.0);
	}
	else if(pPartyMemberCount == 5)
	{
		pDrawGUI(0x789A, 614, 41, 9.0, 10.0);
		pDrawGUI(0x789A, 614, 65, 9.0, 10.0);
		pDrawGUI(0x789A, 614, 89, 9.0, 10.0);
		pDrawGUI(0x789A, 614, 113, 9.0, 10.0);
	}
}
}

void Interface::EventPartyInterface(DWORD Event)
{

	if (this->MiniMapCheck() || this->CombinedChecks())
		{
			return;
		}

	DWORD CurrentTick	= GetTickCount();
	// ----
	if(gInterface.m_PartyLeader == 1)
	{
		if( IsWorkZone2(ePARTYLEADER) )
		{
			DWORD Delay	= (CurrentTick - this->Data[ePARTYLEADER].EventTick);
			// ----
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ePARTYLEADER].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[ePARTYLEADER].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if( Delay < 500 )
			{
				return;
			}
			// ----
			this->Data[ePARTYLEADER].EventTick = GetTickCount();
			// ----
			GC_PARTYNEWLEADER pRequest;

			pRequest.h.set(0xFF,0x15,sizeof(pRequest));
			pRequest.id = (BYTE)1;
			DataSend((BYTE*)&pRequest,pRequest.h.size);
		}
		else if( IsWorkZone2(ePARTYLEADER2) )
		{
			DWORD Delay	= (CurrentTick - this->Data[ePARTYLEADER2].EventTick);
			// ----
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ePARTYLEADER2].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[ePARTYLEADER2].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if( Delay < 500 )
			{
				return;
			}
			// ----
			this->Data[ePARTYLEADER2].EventTick = GetTickCount();
			// ----
			GC_PARTYNEWLEADER pRequest;

			pRequest.h.set(0xFF,0x15,sizeof(pRequest));
			pRequest.id = (BYTE)2;
			DataSend((BYTE*)&pRequest,pRequest.h.size);
		}
		else if( IsWorkZone2(ePARTYLEADER3) )
		{
			DWORD Delay	= (CurrentTick - this->Data[ePARTYLEADER3].EventTick);
			// ----
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ePARTYLEADER3].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[ePARTYLEADER3].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if( Delay < 500 )
			{
				return;
			}
			// ----
			this->Data[ePARTYLEADER3].EventTick = GetTickCount();
			// ----
			GC_PARTYNEWLEADER pRequest;

			pRequest.h.set(0xFF,0x15,sizeof(pRequest));
			pRequest.id = (BYTE)3;
			DataSend((BYTE*)&pRequest,pRequest.h.size);
		}
		else if( IsWorkZone2(ePARTYLEADER4) )
		{
			DWORD Delay	= (CurrentTick - this->Data[ePARTYLEADER4].EventTick);
			// ----
			if( Event == WM_LBUTTONDOWN )
			{
				this->Data[ePARTYLEADER4].OnClick = true;
				pSetCursorFocus = true;
				return;
			}
			// ----
			this->Data[ePARTYLEADER4].OnClick = false;
			pSetCursorFocus = false;
			// ----
			if( Delay < 500 )
			{
				return;
			}
			// ----
			this->Data[ePARTYLEADER4].EventTick = GetTickCount();
			// ----
			GC_PARTYNEWLEADER pRequest;

			pRequest.h.set(0xFF,0x15,sizeof(pRequest));
			pRequest.id = (BYTE)4;
			DataSend((BYTE*)&pRequest,pRequest.h.size);
		}
	}
if(gInterface.m_PartyTrace == 1)
{
	if( IsWorkZone2(ePARTYTRACE) )
	{
		DWORD Delay	= (CurrentTick - this->Data[ePARTYTRACE].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYTRACE].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[ePARTYTRACE].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[ePARTYTRACE].EventTick = GetTickCount();
		// ----
		GC_PARTYNEWLEADER pRequest;

		pRequest.h.set(0xFF,0x26,sizeof(pRequest));
		pRequest.id = (BYTE)0;
		DataSend((BYTE*)&pRequest,pRequest.h.size);
	}
	else if( IsWorkZone2(ePARTYTRACE2) )
	{
		DWORD Delay	= (CurrentTick - this->Data[ePARTYTRACE2].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYTRACE2].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[ePARTYTRACE2].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[ePARTYTRACE2].EventTick = GetTickCount();
		// ----
		GC_PARTYNEWLEADER pRequest;

		pRequest.h.set(0xFF,0x26,sizeof(pRequest));
		pRequest.id = (BYTE)1;
		DataSend((BYTE*)&pRequest,pRequest.h.size);
	}
	else if( IsWorkZone2(ePARTYTRACE3) )
	{
		DWORD Delay	= (CurrentTick - this->Data[ePARTYTRACE3].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYTRACE3].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[ePARTYTRACE3].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[ePARTYTRACE3].EventTick = GetTickCount();
		// ----
		GC_PARTYNEWLEADER pRequest;

		pRequest.h.set(0xFF,0x26,sizeof(pRequest));
		pRequest.id = (BYTE)2;
		DataSend((BYTE*)&pRequest,pRequest.h.size);
	}
	else if( IsWorkZone2(ePARTYTRACE4) )
	{
		DWORD Delay	= (CurrentTick - this->Data[ePARTYTRACE4].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYTRACE4].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[ePARTYTRACE4].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[ePARTYTRACE4].EventTick = GetTickCount();
		// ----
		GC_PARTYNEWLEADER pRequest;

		pRequest.h.set(0xFF,0x26,sizeof(pRequest));
		pRequest.id = (BYTE)3;
		DataSend((BYTE*)&pRequest,pRequest.h.size);
	}
	else if( IsWorkZone2(ePARTYTRACE5) )
	{
		DWORD Delay	= (CurrentTick - this->Data[ePARTYTRACE5].EventTick);
		// ----
		if( Event == WM_LBUTTONDOWN )
		{
			this->Data[ePARTYTRACE5].OnClick = true;
			pSetCursorFocus = true;
			return;
		}
		// ----
		this->Data[ePARTYTRACE5].OnClick = false;
		pSetCursorFocus = false;
		// ----
		if( Delay < 500 )
		{
			return;
		}
		// ----
		this->Data[ePARTYTRACE5].EventTick = GetTickCount();
		// ----
		GC_PARTYNEWLEADER pRequest;

		pRequest.h.set(0xFF,0x26,sizeof(pRequest));
		pRequest.id = (BYTE)4;
		DataSend((BYTE*)&pRequest,pRequest.h.size);
	}	
}
}
// ----------------------------------------------------------------------------------------------


void Interface::ControlTextBox(DWORD Event)
{

	if (this->Data[eSTATSADD_MAIN].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 4;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 5;
		}

		int SelectedIndex = 0;

		if (Event == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Event == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Event == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Event >= 0x30 && Event <= 0x39) || (Event >= 0x60 && Event <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Event);
			if (Symbol == 0)
			{
				return;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return;
		}
		int ObjectIDs[5] = 
		{ 
			eSTATSADD_STATBOX01, 
			eSTATSADD_STATBOX02, 
			eSTATSADD_STATBOX03, 
			eSTATSADD_STATBOX04, 
			eSTATSADD_STATBOX05, 
		};

		for (int i=0;i<ObjectCount;i++)
		{	
			if (this->Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					this->Data[ObjectIDs[i]].StatValue[strlen(this->Data[ObjectIDs[i]].StatValue)-1]= '\0';

					if (strlen(this->Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(this->Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(this->Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					this->Data[ObjectIDs[i]].Attribute = 0;

					if (i==ObjectCount-1)
					{
						this->Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						this->Data[ObjectIDs[i+1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(this->Data[ObjectIDs[i]].StatValue)<8)
					{
						if (!strcmp(this->Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(this->Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(this->Data[ObjectIDs[i]].StatValue, Value);
						}	
					}			
				}
			}
		}

		int StatPoints = 0;

		for (int i=0; i<ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(this->Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(this->Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(this->Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
		return;
	}
	
	else if (this->Data[eSECURITY_CHECK_MAIN].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;


		if (Event == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Event == VK_DELETE)
		{
			IsDelete = true;
		}
		else if ((Event >= 0x30 && Event <= 0x39) || (Event >= 0x60 && Event <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Event);
			if (Symbol == 0)
			{
				return;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return;
		}

		int	ObjectID = eSECURITY_CHECK_BOX;

			if (this->Data[eSECURITY_CHECK_BOX].Attribute == 1)
			{
				//SelectedIndex = i;
				if (IsBackspace == true)
				{
					this->Data[ObjectID].StatValue[strlen(this->Data[ObjectID].StatValue)-1]= '\0';

					if (strlen(this->Data[ObjectID].StatValue) == 0)
					{
						strcpy_s(this->Data[ObjectID].StatValue, "0");
					}
					//break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(this->Data[ObjectID].StatValue, "0");
				}

				else
				{
					if (strlen(this->Data[ObjectID].StatValue)<7)
					{
						if (!strcmp(this->Data[ObjectID].StatValue, "0"))
						{
							strcpy_s(this->Data[ObjectID].StatValue, Value);
						}
						else
						{
							strcat_s(this->Data[ObjectID].StatValue, Value);
						}	
					}			
				}
			}

		return;
	}
	
	else if (this->Data[eRENAME_MAIN].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;


		if (Event == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Event == VK_DELETE)
		{
			IsDelete = true;
		}
		else if ((Event >= 0x41 && Event <= 0x5A) ||(Event >= 0x30 && Event <= 0x39) || (Event >= 0x60 && Event <= 0x69) || (Event = 0xA0) || (Event = 0xA1))
		{
			int Symbol = GetSymbolFromVK(Event);
			if (Symbol == 0)
			{
				return;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return;
		}

			if (this->Data[eRENAME_BOX].Attribute == 1)
			{
				//SelectedIndex = i;
				if (IsBackspace == true)
				{
					this->Data[eRENAME_BOX].StatValue[strlen(this->Data[eRENAME_BOX].StatValue)-1]= '\0';

					if (strlen(this->Data[eRENAME_BOX].StatValue) == 0)
					{
						strcpy_s(this->Data[eRENAME_BOX].StatValue, "0");
					}
					//break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(this->Data[eRENAME_BOX].StatValue, "0");
				}

				else
				{
					if (strlen(this->Data[eRENAME_BOX].StatValue)<10)
					{
						if (!strcmp(this->Data[eRENAME_BOX].StatValue, "0"))
						{
							strcpy_s(this->Data[eRENAME_BOX].StatValue, Value);
						}
						else
						{
							strcat_s(this->Data[eRENAME_BOX].StatValue, Value);
						}	
					}			
				}
			}

		return;
	}

	else if (this->Data[eJewelsBank].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;


		if (Event == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Event == VK_DELETE)
		{
			IsDelete = true;
		}
		else if ((Event >= 0x30 && Event <= 0x39) || (Event >= 0x60 && Event <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Event);
			if (Symbol == 0)
			{
				return;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return;
		}

		int	ObjectID = eJewels_Box;

			if (this->Data[eJewels_Box].Attribute == 1)
			{
				//SelectedIndex = i;
				if (IsBackspace == true)
				{
					this->Data[ObjectID].StatValue[strlen(this->Data[ObjectID].StatValue)-1]= '\0';

					if (strlen(this->Data[ObjectID].StatValue) == 0)
					{
						strcpy_s(this->Data[ObjectID].StatValue, "0");
					}
					//break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(this->Data[ObjectID].StatValue, "0");
				}

				else
				{
					if (strlen(this->Data[ObjectID].StatValue)<5)
					{
						if (!strcmp(this->Data[ObjectID].StatValue, "0"))
						{
							strcpy_s(this->Data[ObjectID].StatValue, Value);
						}
						else
						{
							strcat_s(this->Data[ObjectID].StatValue, Value);
						}	
					}			
				}
			}

		return;
	}

	else if (this->Data[eGIFTCODE_MAIN].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;


		if (Event == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Event == VK_DELETE)
		{
			IsDelete = true;
		}
		else if ((Event >= 0x30 && Event <= 0x39) || (Event >= 0x60 && Event <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Event);
			if (Symbol == 0)
			{
				return;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return;
		}

		int	ObjectID = eGIFTCODE_BOX;

			if (this->Data[eGIFTCODE_BOX].Attribute == 1)
			{
				//SelectedIndex = i;
				if (IsBackspace == true)
				{
					this->Data[ObjectID].StatValue[strlen(this->Data[ObjectID].StatValue)-1]= '\0';

					if (strlen(this->Data[ObjectID].StatValue) == 0)
					{
						strcpy_s(this->Data[ObjectID].StatValue, "0");
					}
					//break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(this->Data[ObjectID].StatValue, "0");
				}

				else
				{
					if (strlen(this->Data[ObjectID].StatValue)<7)
					{
						if (!strcmp(this->Data[ObjectID].StatValue, "0"))
						{
							strcpy_s(this->Data[ObjectID].StatValue, Value);
						}
						else
						{
							strcat_s(this->Data[ObjectID].StatValue, Value);
						}	
					}			
				}
			}

		return;
	}

	return;
}

