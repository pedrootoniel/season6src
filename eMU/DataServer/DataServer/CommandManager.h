// CommandManager.h: interface for the CCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "DataServerProtocol.h"

//**********************************************//
//********** GameServer -> DataServer **********//
//**********************************************//

struct SDHP_COMMAND_RESET_RECV
{
	PSBMSG_HEAD header; // C1:0F:00
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_COMMAND_MASTER_RESET_RECV
{
	PSBMSG_HEAD header; // C1:0F:01
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_COMMAND_RENAME_RECV
{
    PSBMSG_HEAD header; // C1:F0:05
    WORD index;
	char account[11];
    char name[11];
    char newname[11];
};

struct SDHP_COMMAND_REWARD_RECV
{
	PSBMSG_HEAD header; // C1:0F:03
	WORD index;
	char account[11];
	char name[11];
	char accountGM[11];
	char nameGM[11];
	UINT Type;
	UINT Value;
};

struct SDHP_COMMAND_REWARDALL_RECV
{
	PSBMSG_HEAD header; // C1:0F:04
	WORD index;
	char accountGM[11];
	char nameGM[11];
	UINT Type;
	UINT Value;
};


//**********************************************//
//********** DataServer -> GameServer **********//
//**********************************************//

struct SDHP_COMMAND_RESET_SEND
{
	PSBMSG_HEAD header; // C1:0F:00
	WORD index;
	char account[11];
	char name[11];
	UINT ResetDay;
	UINT ResetWek;
	UINT ResetMon;
};

struct SDHP_COMMAND_MASTER_RESET_SEND
{
	PSBMSG_HEAD header; // C1:0F:01
	WORD index;
	char account[11];
	char name[11];
	UINT MasterResetDay;
	UINT MasterResetWek;
	UINT MasterResetMon;
};

struct SDHP_COMMAND_RENAME_SEND
{
    PSBMSG_HEAD header; // C1:0F:05
    WORD index;
	char account[11];
    char name[11];
    char newname[11];
	BYTE result;
};

struct SDHP_COMMAND_BLOCK_RECV
{
    PSBMSG_HEAD header; // C1:F0:06
    WORD index;
	char accountbloc[11];
    char namebloc[11];
};

struct SETTITLE_GD_SAVE_DATA
{
	PSBMSG_HEAD header;
	// ----
	WORD	index;
	char	Name[11];
	int		RankSlot1;
};
//**********************************************//
//**********************************************//
//**********************************************//

class CCommandManager
{
public:
	CCommandManager();
	virtual ~CCommandManager();
	void GDCommandResetRecv(SDHP_COMMAND_RESET_RECV* lpMsg,int index);
	void GDCommandMasterResetRecv(SDHP_COMMAND_MASTER_RESET_RECV* lpMsg,int index);
	void GDCommandRenameRecv(SDHP_COMMAND_RENAME_RECV* lpMsg,int index);
	void GDCommandBlockAccRecv(SDHP_COMMAND_BLOCK_RECV* lpMsg,int index);
	void GDCommandBlockCharRecv(SDHP_COMMAND_BLOCK_RECV* lpMsg,int index);
	void GDCommandRewardRecv(SDHP_COMMAND_REWARD_RECV* lpMsg,int index);
	void GDCommandRewardAllRecv(SDHP_COMMAND_REWARDALL_RECV* lpMsg,int index);
	void GDCommandSetTitleRecv(SETTITLE_GD_SAVE_DATA* lpMsg);
};

extern CCommandManager gCommandManager;
