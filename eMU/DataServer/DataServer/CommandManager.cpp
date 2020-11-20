// CommandManager.cpp: implementation of the CCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommandManager.h"
#include "QueryManager.h"
#include "SocketManager.h"

CCommandManager gCommandManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommandManager::CCommandManager() // OK
{

}

CCommandManager::~CCommandManager() // OK
{

}

void CCommandManager::GDCommandResetRecv(SDHP_COMMAND_RESET_RECV* lpMsg,int index) // OK
{
	SDHP_COMMAND_RESET_SEND pMsg;

	pMsg.header.set(0x0F,0x00,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));

	memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));

	gQueryManager.ExecQuery("EXEC WZ_GetResetInfo '%s','%s'",lpMsg->account,lpMsg->name);

	gQueryManager.Fetch();

	pMsg.ResetDay = gQueryManager.GetAsInteger("ResetDay");

	pMsg.ResetWek = gQueryManager.GetAsInteger("ResetWek");

	pMsg.ResetMon = gQueryManager.GetAsInteger("ResetMon");

	gQueryManager.Close();

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::GDCommandMasterResetRecv(SDHP_COMMAND_MASTER_RESET_RECV* lpMsg,int index) // OK
{
	SDHP_COMMAND_MASTER_RESET_SEND pMsg;

	pMsg.header.set(0x0F,0x01,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));

	memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));

	gQueryManager.ExecQuery("EXEC WZ_GetMasterResetInfo '%s','%s'",lpMsg->account,lpMsg->name);

	gQueryManager.Fetch();

	pMsg.MasterResetDay = gQueryManager.GetAsInteger("MasterResetDay");

	pMsg.MasterResetWek = gQueryManager.GetAsInteger("MasterResetWek");

	pMsg.MasterResetMon = gQueryManager.GetAsInteger("MasterResetMon");

	gQueryManager.Close();

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::GDCommandRenameRecv(SDHP_COMMAND_RENAME_RECV* lpMsg, int index) // OK
{
	SDHP_COMMAND_RENAME_SEND pMsg;

	pMsg.header.set(0x0F,0x02,sizeof(pMsg));
	
	pMsg.index = lpMsg->index;

	memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));
	
	memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));

	memcpy(pMsg.newname,lpMsg->newname,sizeof(pMsg.newname));

	if(gQueryManager.ExecQuery("EXEC WZ_RenameCharacter '%s','%s','%s'",lpMsg->account,lpMsg->name,lpMsg->newname) == 0 || gQueryManager.Fetch() == SQL_NO_DATA)	
	{
		gQueryManager.Close();
		pMsg.result = 2;
	}	
	else	
	{	
		pMsg.result = gQueryManager.GetResult(0);
		gQueryManager.Close();	
	}

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}
void CCommandManager::GDCommandBlockAccRecv(SDHP_COMMAND_BLOCK_RECV* lpMsg,int index) // OK
{
	gQueryManager.ExecQuery("UPDATE MEMB_INFO SET BLOC_CODE=1 WHERE MEMB___ID='%s'",lpMsg->accountbloc);
	gQueryManager.Close();
}

void CCommandManager::GDCommandBlockCharRecv(SDHP_COMMAND_BLOCK_RECV* lpMsg,int index) // OK
{
	gQueryManager.ExecQuery("UPDATE CHARACTER SET CTLCODE=1 WHERE NAME='%s'",lpMsg->namebloc);
	gQueryManager.Close();
}

void CCommandManager::GDCommandRewardRecv(SDHP_COMMAND_REWARD_RECV* lpMsg,int index) // OK
{
	gQueryManager.ExecQuery("EXEC WZ_SetReward '%s','%s','%s','%s','%d','%d'",lpMsg->account,lpMsg->name,lpMsg->accountGM,lpMsg->nameGM,lpMsg->Type,lpMsg->Value);
	gQueryManager.Close();
}

void CCommandManager::GDCommandRewardAllRecv(SDHP_COMMAND_REWARDALL_RECV* lpMsg,int index) // OK
{
	gQueryManager.ExecQuery("EXEC WZ_SetRewardAll '%s','%s','%d','%d'",lpMsg->accountGM,lpMsg->nameGM,lpMsg->Type,lpMsg->Value);
	gQueryManager.Close();
}

void CCommandManager::GDCommandSetTitleRecv(SETTITLE_GD_SAVE_DATA* lpMsg) // OK
{
	gQueryManager.ExecQuery("UPDATE CharacterTitle SET Slot1 = %d WHERE Name = '%s'",lpMsg->RankSlot1, lpMsg->Name);
	gQueryManager.Close();
}