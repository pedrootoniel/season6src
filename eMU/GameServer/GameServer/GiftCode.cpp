// Gate.cpp: implementation of the CGate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommandManager.h"
#include "GiftCode.h"
#include "GensSystem.h"
#include "Log.h"
#include "Map.h"
#include "MapManager.h"
#include "MemScript.h"
#include "Message.h"
#include "Notice.h"
#include "Util.h"

CGiftCode gGiftCode;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGiftCode::CGiftCode() // OK
{
	this->m_GiftCodeInfo.clear();
}

CGiftCode::~CGiftCode() // OK
{

}

void CGiftCode::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_GiftCodeInfo.clear();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			GIFTCODE_INFO info;

			info.Index = lpMemScript->GetNumber();

			strcpy_s(info.GiftName,lpMemScript->GetAsString());

			info.GiftCount = lpMemScript->GetAsNumber();

			info.SetID = lpMemScript->GetAsNumber();

			info.WeaponID = lpMemScript->GetAsNumber();

			info.PetID = lpMemScript->GetAsNumber();

			info.BuffID = lpMemScript->GetAsNumber();

			info.ItemTime = lpMemScript->GetAsNumber();

			this->m_GiftCodeInfo.insert(std::pair<int,GIFTCODE_INFO>(info.Index,info));
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool CGiftCode::GetInfo(int index,GIFTCODE_INFO* lpInfo) // OK
{
	std::map<int,GIFTCODE_INFO>::iterator it = this->m_GiftCodeInfo.find(index);

	if(it == this->m_GiftCodeInfo.end())
	{
		return 0;
	}
	else
	{
		(*lpInfo) = it->second;
		return 1;
	}
}

bool CGiftCode::GetInfoByName(char* message,GIFTCODE_INFO* lpInfo) // OK
{
	char command[32] = {0};

	memset(command,0,sizeof(command));

	gCommandManager.GetString(message,command,sizeof(command),0);


	for(std::map<int,GIFTCODE_INFO>::iterator it=this->m_GiftCodeInfo.begin();it != this->m_GiftCodeInfo.end();it++)
	{
		if(_stricmp(it->second.GiftName,command) == 0)
		{
			(*lpInfo) = it->second;
			return 1;
		}
	}

	return 0;
}
void CGiftCode::RecvDS(DGGiftCode *Recv)
{
	for(int i=0;i<MAX_GIFTCODE;i++)
	{
		strncpy(this->GiftCode[i].GiftName,Recv->tp[i].GiftName,11);
		this->GiftCode[i].GiftCount = Recv->tp[i].GiftCount;
		//LogAdd(LOG_BLUE,"%s %d %d %d %d %s",RankingChar[i].Name,RankingChar[i].Class,RankingChar[i].level,RankingChar[i].Reset,RankingChar[i].Map,RankingChar[i].Guild);
	}
}
void CGiftCode::GetMove(LPOBJ lpObj,int index) // OK
{
	/*
	GIFTCODE_INFO CustomMoveInfo;

	if(this->GetInfo(index,&CustomMoveInfo) == 0)
	{
		return;
	}

	if(CustomMoveInfo.GiftCount < 1)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"GiftCode nay da duoc nhan het");
		return;
	}

	if(lpObj->Interface.use != 0 || lpObj->Teleport != 0 || lpObj->DieRegen != 0 || lpObj->PShopOpen != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(226));
		return;
	}

	gObjTeleport(lpObj->Index,CustomMoveInfo.Map,CustomMoveInfo.X,CustomMoveInfo.Y);
	gLog.Output(LOG_COMMAND,"[CustomMove][%s][%s] - (MoveIndex: %d)",lpObj->Account,lpObj->Name,index);
	*/
}