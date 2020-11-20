#include "stdafx.h"
#include "OfflineMode.h"
#include "Interface.h"
#include "Console.h"
#include "Util.h"
#include "User.h"

cOfflineMode gOfflineMode;

cOfflineMode::cOfflineMode()
{
	this->OfflineType = -1;
	this->SkillsData[0] = 0;
	this->SkillsData[1] = 0;
	this->SkillsData[2] = 0;
	this->SkillsIndex[0] = 0;
	this->SkillsIndex[1] = 0;
	this->SkillsIndex[2] = 0;

	for (int i=3; i<3;i++)
	{
		this->m_SkillCoord[i].EventTick = 0;
		this->m_SkillCoord[i].StartX = 0;
		this->m_SkillCoord[i].StartY = 0;
	}

	this->ClearSelectedSkill();
}

cOfflineMode::~cOfflineMode()
{
	
}

void cOfflineMode::CGOfflineModeSend()
{
	PMSG_OFFLINEMODE_REQ pRequest;
	pRequest.Head.set(0xFF,0x0A,sizeof(pRequest));

	DataSend((BYTE*)&pRequest,pRequest.Head.size);
}

void cOfflineMode::GCOfflineModeRecv(PMSG_OFFLINEMODE_REQ* Data)
{
	////console.Log("", "OffType = %d", Data->OffType);
	this->OfflineType = Data->OffType;
	this->SkillsData[0] = Data->SkillData[0];
	this->SkillsData[1] = Data->SkillData[1];
	this->SkillsData[2] = Data->SkillData[2];
	this->SkillsIndex[0] = Data->SkillIndex[0];
	this->SkillsIndex[1] = Data->SkillIndex[1];
	this->SkillsIndex[2] = Data->SkillIndex[2];
	this->DrawBuff = Data->DrawBuff;
	this->DrawPick = Data->DrawPick;

	g_Console.AddMessage(1, "skill = %d,%d,%d", Data->SkillIndex[0], Data->SkillIndex[1], Data->SkillIndex[2]);

	memcpy(this->SkillsName[0],Data->SkillName[0],sizeof(this->SkillsName[0]));
	memcpy(this->SkillsName[1],Data->SkillName[1],sizeof(this->SkillsName[1]));
	memcpy(this->SkillsName[2],Data->SkillName[2],sizeof(this->SkillsName[2]));
	if (!gObjUser.lpViewPlayer->InSafeZone)
	{
		gInterface.Data[eOFFEXP_MAIN].Open();
		this->ClearSelectedSkill();
	}
	else
	{
		gInterface.DrawMessageBox("You can't open offexp window when you not in field");
	}
}

void cOfflineMode::DrawSkill(int Skill, int StartX)
{
	float PosX = StartX + (50*(Skill+1));
	float PosY = gInterface.Data[eOFFEXP_MAIN].Y + 83;
	float ScaleX = 0;
	float ScaleY = 0;
	int SkillPattern = 0x7A4C;
	bool DrawSkill = 0;
	
	if (this->SelectedSkill[Skill] == true)
	{
		pSetBlend(1);
		glColor4f(255.0, 0.0, 0.0, 1.0);
		pDrawBarForm(PosX-1, PosY-1, 22, 30, 0.0f, 0);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
	}

	#pragma region Выбор скилла
	if (this->SkillsData[Skill] != 0)
	{
		switch (this->SkillsIndex[Skill])
		{
			case SKILL_ICE_STORM:
				ScaleX = 6*20;
				ScaleY = 4*28;
				SkillPattern = 0x7A4C;
				DrawSkill = 1;
				break;
			case SKILL_EVIL_SPIRIT:
				ScaleX = 0;
				ScaleY = 1*28;
				SkillPattern = 0x7A4C;
				DrawSkill = 1;
				break;
			case SKILL_INFERNO:
				ScaleX = 5*20;
				ScaleY = 1*28;
				SkillPattern = 0x7A4C;
				DrawSkill = 1;
				break;
			case SKILL_TWISTING_SLASH:
				ScaleX = 0;
				ScaleY = 5*28;
				SkillPattern = 0x7A4C;
				DrawSkill = 1;
				break;
			case SKILL_RAGEFUL_BLOW:
				ScaleX = 1*20;
				ScaleY = 5*28;
				SkillPattern = 0x7A4C;
				DrawSkill = 1;
				break;
			case SKILL_FROZEN_STAB:
				ScaleX = 7*20;
				ScaleY = 2*28;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_TRIPLE_SHOT:
				ScaleX = 7*20;
				ScaleY = 2*28;
				SkillPattern = 0x7A4C;
				DrawSkill = 1;
				break;
			case SKILL_FIVE_SHOT:
				ScaleX = 0;
				ScaleY = 8*28;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_ICE_ARROW:
				ScaleX = 2*20;
				ScaleY = 6*28;
				SkillPattern = 0x7A4C;
				DrawSkill = 1;
				break;
			case SKILL_LIGHTNING_STORM:
				ScaleX = 2*20;
				ScaleY = 8*28;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_SWORD_SLASH:
				ScaleX = 1*20;
				ScaleY = 8*28;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_POWER_SLASH:
				ScaleX = 7*20;
				ScaleY = 6*28;
				SkillPattern = 0x7A4C;
				DrawSkill = 1;
				break;
			case SKILL_BIRDS:
				ScaleX = 3*20;
				ScaleY = 8*28;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_FIRE_BURST:
				ScaleX = 4*20;
				ScaleY = 0;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_FIRE_SCREAM:
				ScaleX = 5*20;
				ScaleY = 2*28;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_RED_STORM:
				ScaleX = 2*20;
				ScaleY = 3*28;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_CHAIN_LIGHTNING:
				ScaleX = 1*20;
				ScaleY = 3*28;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_GHOST_PHANTOM:
				ScaleX = 11*20;
				ScaleY = 3*28;
				SkillPattern = 0x7A4D;
				DrawSkill = 1;
				break;
			case SKILL_DRAGON_LORE:
				ScaleX = 4*20;
				ScaleY = 0;
				SkillPattern = 0x7A4F;
				DrawSkill = 1;
				break;
			case SKILL_DARK_SIDE:
				ScaleX = 3*20;
				ScaleY = 0;
				SkillPattern = 0x7A4F;
				DrawSkill = 1;
				break;
			case SKILL_LARGE_RING_BLOWER:
				ScaleX = 0;
				ScaleY = 0;
				SkillPattern = 0x7A4F;
				DrawSkill = 1;
				break;
		}
	}
	else
	{
		switch (this->SkillsIndex[Skill])
		{
			case SKILL_ICE_STORM:
				ScaleX = 6*20;
				ScaleY = 4*28;
				SkillPattern = 0x7A52;
				DrawSkill = 1;
				break;
			case SKILL_EVIL_SPIRIT:
				ScaleX = 0;
				ScaleY = 1*28;
				SkillPattern = 0x7A52;
				DrawSkill = 1;
				break;
			case SKILL_INFERNO:
				ScaleX = 5*20;
				ScaleY = 1*28;
				SkillPattern = 0x7A52;
				DrawSkill = 1;
				break;
			case SKILL_TWISTING_SLASH:
				ScaleX = 0;
				ScaleY = 5*28;
				SkillPattern = 0x7A52;
				DrawSkill = 1;
				break;
			case SKILL_RAGEFUL_BLOW:
				ScaleX = 1*20;
				ScaleY = 5*28;
				SkillPattern = 0x7A52;
				DrawSkill = 1;
				break;
			case SKILL_FROZEN_STAB:
				ScaleX = 7*20;
				ScaleY = 2*28;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_TRIPLE_SHOT:
				ScaleX = 7*20;
				ScaleY = 2*28;
				SkillPattern = 0x7A52;
				DrawSkill = 1;
				break;
			case SKILL_FIVE_SHOT:
				ScaleX = 0;
				ScaleY = 8*28;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_LIGHTNING_STORM:
				ScaleX = 2*20;
				ScaleY = 8*28;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_SWORD_SLASH:
				ScaleX = 1*20;
				ScaleY = 8*28;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_POWER_SLASH:
				ScaleX = 7*20;
				ScaleY = 6*28;
				SkillPattern = 0x7A52;
				DrawSkill = 1;
				break;
			case SKILL_BIRDS:
				ScaleX = 3*20;
				ScaleY = 8*28;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_FIRE_BURST:
				ScaleX = 4*20;
				ScaleY = 0;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_FIRE_SCREAM:
				ScaleX = 5*20;
				ScaleY = 2*28;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_RED_STORM:
				ScaleX = 2*20;
				ScaleY = 3*28;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_CHAIN_LIGHTNING:
				ScaleX = 1*20;
				ScaleY = 3*28;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_GHOST_PHANTOM:
				ScaleX = 11*20;
				ScaleY = 3*28;
				SkillPattern = 0x7A53;
				DrawSkill = 1;
				break;
			case SKILL_DRAGON_LORE:
				ScaleX = 4*20;
				ScaleY = 0;
				SkillPattern = 0x7A55;
				DrawSkill = 1;
				break;
			case SKILL_DARK_SIDE:
				ScaleX = 3*20;
				ScaleY = 0;
				SkillPattern = 0x7A55;
				DrawSkill = 1;
				break;
			case SKILL_LARGE_RING_BLOWER:
				ScaleX = 0;
				ScaleY = 0;
				SkillPattern = 0x7A55;
				DrawSkill = 1;
				break;
		}
	}
	#pragma endregion 
	
	if (DrawSkill)
	{
		this->m_SkillCoord[Skill].StartX = PosX;
		this->m_SkillCoord[Skill].StartY = PosY;
		pDrawButton(SkillPattern, PosX, PosY, 20, 28, ScaleX, ScaleY);
	}
}

float cOfflineMode::GetSkillX(int Index)
{
	return this->m_SkillCoord[Index].StartX;
}

float cOfflineMode::GetSkillY(int Index)
{
	return this->m_SkillCoord[Index].StartY;
}

void cOfflineMode::ClearSelectedSkill()
{
	for(int i=0;i<3;i++)
	{
		this->SelectedSkill[i] = false;
	}
}

void cOfflineMode::ChangeCheckBox(int index)
{
	if (index==0)
	{
		this->Checkbox_Data.UseBuff ^= 1;
	}
	else if (index == 2)
	{
		this->Checkbox_Data.PickZen ^= 1;
	}
	else if (index == 3)
	{
		this->Checkbox_Data.PickJewels ^= 1;
	}
	else if (index == 4)
	{
		this->Checkbox_Data.PickExe ^= 1;
	}
	else if (index == 5)
	{
		this->Checkbox_Data.PickAnc ^= 1;
	}
	else if (index == 6)
	{
		this->Checkbox_Data.PickSelected ^= 1;
	}
}

bool cOfflineMode::GetCheckBox(int index)
{
	if (index==0)
	{
		return this->Checkbox_Data.UseBuff;
	}
	else if (index == 2)
	{
		return this->Checkbox_Data.PickZen;
	}
	else if (index == 3)
	{
		return this->Checkbox_Data.PickJewels;
	}
	else if (index == 4)
	{
		return this->Checkbox_Data.PickExe;
	}
	else if (index == 5)
	{
		return this->Checkbox_Data.PickAnc;
	}
	else if (index == 6)
	{
		return this->Checkbox_Data.PickSelected;
	}
}

void cOfflineMode::SendOffExpData()
{
	PMSG_OFFLINEMODE_DATA_SEND pMsg;
	pMsg.header.set(0xFF, 0x14, sizeof(pMsg));

	int index = -1;

	for (int i=0;i<3;i++)
	{
		if (this->SelectedSkill[i] == true) index = i;
	}

	if (index == -1)
	{
		return;
	}

	pMsg.SkillID = this->SkillsIndex[index];
	pMsg.UseBuff = this->Checkbox_Data.UseBuff;
	pMsg.PickZen = this->Checkbox_Data.PickZen;
	pMsg.PickJewels = this->Checkbox_Data.PickJewels;
	pMsg.PickExe = this->Checkbox_Data.PickExe;
	pMsg.PickAnc = this->Checkbox_Data.PickAnc;
	pMsg.PickSelected = this->Checkbox_Data.PickSelected;

	DataSend((BYTE*)&pMsg,pMsg.header.size);

	g_Console.AddMessage(1,"SkillID %d",this->SkillsIndex[index]);
}