#include "stdafx.h"
#include "User.h"
#include "Protocol.h"
#include "TrayMode.h"
#include "Defines.h"
#include "Reconnect.h"
#include "Camera.h"
#include "Offset.h"
#include "Interface.h"
//#include "ServerInfo.h"
#include "PrintPlayer.h"
#include "HealthBar.h"
#include "Util.h"
#include "Protect.h"
// ----------------------------------------------------------------------------------------------

User	gObjUser;
// ----------------------------------------------------------------------------------------------

void User::Load()
{
	ZeroMemory(&this->lpPlayer, sizeof(this->lpPlayer));
	ZeroMemory(&this->lpViewPlayer, sizeof(this->lpViewPlayer));
	ZeroMemory(&this->lpViewTarget, sizeof(this->lpViewTarget));
	// ----
	//SetCompleteHook(0xFF, 0x0077F822, &this->ChangeCharInfo);
	// ----
	SetCompleteHook(0xFF,0x00520ECF,&this->GetMapName);
	SetCompleteHook(0xFF,0x00520F1F,&this->GetMapName);
	SetCompleteHook(0xFF,0x0063E743,&this->GetMapName);
	SetCompleteHook(0xFF,0x00640EB2,&this->GetMapName);
	SetCompleteHook(0xFF,0x007D2DD9,&this->GetMapName);
	SetCompleteHook(0xFF,0x007E6C0F,&this->GetMapName);
	SetCompleteHook(0xFF,0x0084AEF7,&this->GetMapName);
	////console.Log("User", "Successfully Loaded");
}
// ----------------------------------------------------------------------------------------------

void User::Refresh()
{
	this->lpPlayer			= &*(ObjectCharacter*)*(int*)(MAIN_CHARACTER_STRUCT);
	this->lpViewPlayer		= &*(ObjectPreview*)*(int*)MAIN_PREVIEW_STRUCT;
	this->GetTarget();
	// ----
	this->m_CursorX			= pCursorX;
	this->m_CursorY			= pCursorY;
	this->m_MapNumber		= pMapNumber;
	this->m_MasterLevel		= pMasterLevel;
	this->m_MasterPoint		= pMasterPoint;
	this->m_MasterExp		= pMasterExp;
	this->m_MasterNextExp	= pMasterNextExp;

	if( gTrayMode.InTray )
	{
		if( !this->lpViewPlayer->m_Model.Unknown4)
		{
			gTrayMode.ShowMessage(NIIF_WARNING, gProtect.m_MainInfo.WindowName, "Your character was killed!");
		}
	}
}
// ----------------------------------------------------------------------------------------------

bool User::GetTarget()
{
	if( pViewNPCTargetID != -1 )
	{
		this->lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewNPCTargetID);
		this->m_TargetType	= 1;
		return true;
	}
	else if( pViewAttackTargetID != -1 )
	{
		this->lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewAttackTargetID);
		this->m_TargetType	= 2;
		return true;
	}
	// ----
	if( this->lpViewTarget != 0 )
	{
		ZeroMemory(&this->lpViewTarget, sizeof(this->lpViewTarget));
	}
	// ----
	this->m_TargetType = 0;
	return false;
}

char* User::GetMapName(int MapNumber)
{
	if (MapNumber >= 82 && MapNumber <= 100)
	{
		return pGetTextLine(pTextLineThis, (3170 + MapNumber - 82));
	}
	return pGetMapName(MapNumber);
}

int User::GetActiveSkill()
{
 lpCharObj lpPlayer  = &*(ObjectCharacter*)*(int*)(MAIN_CHARACTER_STRUCT);
 lpViewObj lpViewPlayer  = &*(ObjectPreview*)*(int*)MAIN_PREVIEW_STRUCT;
 return lpPlayer->pMagicList[lpViewPlayer->ActiveMagic];
 //return this->lpPlayer->pMagicList[this->lpViewPlayer->ActiveMagic];
}

void User::ChangeCharInfo(LPVOID This)
{
	if( !gInterface.CheckWindow(Character))
	{
		return;
	}

		//gInterface.DrawFormat(eShinyGreen, 470, 58, 100, 1, "Level: %d", gObjUser.lpPlayer->Level);
		//gInterface.DrawFormat(eRed, 520, 58, 100, 1, "Reset: %d", ViewReset);
		//gInterface.DrawFormat(eExcellent, 570, 58, 100, 1, "Grand Reset: %d", ViewGReset);
		char Value[50];
		if (gInterface.m_QuickAdd == 1)
		{
			gInterface.DrawButton(eCHARINFO_BTN_STAT, 473, 73, 0, 0);
			gInterface.DrawFormat(eShinyGreen, 492, 76, 100, 1, "Quick add stats");
			pDrawGUI(0x9205, 565, 73, 50, 16);

			ZeroMemory(Value, sizeof(Value));
			pGetMoneyFormat((double)ViewPoint, Value, 0);
			GetFormat(Value,',',' ');

			gInterface.DrawFormat(eBlue, 540, 77, 100, 3, "%s", Value);

			if( gInterface.IsWorkZone2(eCHARINFO_BTN_STAT) )
			{
				if( gInterface.Data[eCHARINFO_BTN_STAT].OnClick )
				{
					gInterface.DrawButton(eCHARINFO_BTN_STAT, 473, 73, 0, 16);
				}
			}
		}	

		if (gInterface.m_ResetStats == 1)
		{
			int StatPoints = ViewStrength + ViewDexterity + ViewVitality + ViewEnergy + ViewLeadership;

			//console.Log("", "[%d] %d %d %d %d %d", StatPoints, ViewStrength,ViewDexterity,ViewVitality,ViewEnergy,ViewLeadership);

			//StatPoints -= (gConfig.Strength + gConfig.Dexterity + gConfig.Vitality + gConfig.Energy + gConfig.Leadership);
			StatPoints -= (gObjUser.d_Strength + gObjUser.d_Dexterity + gObjUser.d_Vitality + gObjUser.d_Energy + gObjUser.d_Leadership);

			gInterface.DrawButton(eCHARINFO_BTN_RESSTAT, 473, 94, 0, 0);
			gInterface.DrawFormat(eShinyGreen, 492, 97, 100, 1, "Reset stats");
			pDrawGUI(0x9205, 565, 94, 50, 16);

			char Value2[50];
			ZeroMemory(Value, sizeof(Value2));
			pGetMoneyFormat((double)StatPoints, Value2, 0);
			GetFormat(Value2,',',' ');

			gInterface.DrawFormat(eBlue, 540, 98, 100, 3, "%s", Value2);

			if( gInterface.IsWorkZone2(eCHARINFO_BTN_RESSTAT) )
			{
				if( gInterface.Data[eCHARINFO_BTN_RESSTAT].OnClick )
				{
					gInterface.DrawButton(eCHARINFO_BTN_RESSTAT, 473, 94, 0, 16);
				}
			}
		}
	else
	{
		((BOOL(__thiscall*)(LPVOID This))0x0077FAE0)(This);
	}
}

int User::GetResetPointPriceWC(int AccountLevel)
{
	return this->m_CustomResetPointPriceWC[AccountLevel];
}


int User::GetResetPointPriceZen(int AccountLevel)
{
	return this->m_CustomResetPointPriceZen[AccountLevel];
}

int User::GetResetMasterSkillPriceWC(int AccountLevel)
{
	return this->m_CustomMasterSkillPriceWC[AccountLevel];
}

int User::GetResetMasterSkillPriceZen(int AccountLevel)
{
	return this->m_CustomMasterSkillPriceZen[AccountLevel];
}

int User::GetMaxStatPoint(int AccountLevel)
{
	return this->m_MaxStatPoint[AccountLevel];
}
