// CommandManager.h: interface for the CCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Protocol.h"
#include "User.h"

#define MAX_COMMAND 70

enum eCommandNumber
{
	COMMAND_MOVE = 1,
	COMMAND_POST = 2,
	COMMAND_ADD_POINT1 = 3,
	COMMAND_ADD_POINT2 = 4,
	COMMAND_ADD_POINT3 = 5,
	COMMAND_ADD_POINT4 = 6,
	COMMAND_ADD_POINT5 = 7,
	COMMAND_PK_CLEAR = 8,
	COMMAND_MONEY = 9,
	COMMAND_CHANGE = 10,
	COMMAND_WARE = 11,
	COMMAND_RESET = 12,
	COMMAND_GM_MOVE = 13,
	COMMAND_GM_POST = 14,
	COMMAND_TRACK = 15,
	COMMAND_TRACE = 16,
	COMMAND_DISCONNECT = 17,
	COMMAND_FIREWORKS = 18,
	COMMAND_MAKE = 19,
	COMMAND_SKIN = 20,
	COMMAND_SET_MONEY = 21,
	COMMAND_NOTICE = 22,
	COMMAND_MASTER_RESET = 23,
	COMMAND_GUILD_WAR = 24,
	COMMAND_BATTLE_SOCCER = 25,
	COMMAND_REQUEST = 26,
	COMMAND_CUSTOM_STORE = 27,
	COMMAND_CUSTOM_STORE_OFFLINE = 28,
	COMMAND_HIDE = 29,
	COMMAND_CUSTOM_ATTACK = 30,
	COMMAND_CUSTOM_ATTACK_OFFLINE = 31,
	COMMAND_CLEAR_INVENTORY = 32,
	COMMAND_PKEVENT	=	33,
	COMMAND_RESET_POINT  = 34,
	COMMAND_RESET_SKILL = 35,
	COMMAND_RESET_MASTER = 36,
	COMMAND_CHANGECLASS = 37,
	COMMAND_THEGIFT	=	38,
	COMMAND_RENAME	=	39,
	COMMAND_BLOCKACC = 40,
	COMMAND_BLOCKCHAR = 41,
	COMMAND_SECURITY = 42,
	COMMAND_MARRYPROP = 43,
	COMMAND_MARRYACCEPT = 44,
	COMMAND_MARRYTP = 45,
	COMMAND_MARRYDIVORCE = 46,
	COMMAND_QUIZ = 47,
	COMMAND_REWARD = 48,
	COMMAND_REWARDALL = 49,
	COMMAND_MAKESET = 50,
	COMMAND_DROP = 51,
	COMMAND_MOVEALL = 52,
	COMMAND_GMOVE = 53,
	COMMAND_DRAWMONSTER = 54,
	COMMAND_SETPK = 55,
	COMMAND_ONLINE = 56,
	COMMAND_DUELSEND = 57,
	COMMAND_DCFRIEND = 58,
	COMMAND_PVPEVENT = 59,
	COMMAND_KILLALL = 60,
	COMMAND_KILLALLJOIN = 61,
	COMMAND_CHATBAN = 62,
	COMMAND_CHATUNBAN = 63,
	COMMAND_GUILDMOVE = 64,
};

//**********************************************//
//********** DataServer -> GameServer **********//
//**********************************************//

struct SDHP_COMMAND_RESET_RECV
{
	PSBMSG_HEAD header; // C1:0F:00
	WORD index;
	char account[11];
	char name[11];
	UINT ResetDay;
	UINT ResetWek;
	UINT ResetMon;
};

struct SDHP_COMMAND_MASTER_RESET_RECV
{
	PSBMSG_HEAD header; // C1:0F:01
	WORD index;
	char account[11];
	char name[11];
	UINT MasterResetDay;
	UINT MasterResetWek;
	UINT MasterResetMon;
};

struct SDHP_COMMAND_RENAME_RECV
{
	PSBMSG_HEAD header; // C1:0F:05
	WORD index;
	char account[11];
	char name[11];
	char newname[11];
	BYTE result;
};

//**********************************************//
//********** GameServer -> DataServer **********//
//**********************************************//

struct SDHP_COMMAND_RESET_SEND
{
	PSBMSG_HEAD header; // C1:0F:00
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_COMMAND_MASTER_RESET_SEND
{
	PSBMSG_HEAD header; // C1:0F:01
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_COMMAND_RENAME_SEND
{
	PSBMSG_HEAD header; // C1:0F:05
	WORD index;
	char account[11];
	char name[11];
	char newname[11];
};

struct SDHP_COMMAND_BLOCK_SEND
{
    PSBMSG_HEAD header; // C1:0F:06
    WORD index;
	char accountbloc[11];
    char namebloc[11];
};

struct SDHP_COMMAND_UNBLOCK_SEND
{
    PSBMSG_HEAD header; // C1:0F:06
    WORD index;
	char accountbloc[11];
    char namebloc[11];
};

struct SDHP_COMMAND_REWARD_SEND
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

struct SDHP_COMMAND_REWARDALL_SEND
{
	PSBMSG_HEAD header; // C1:0F:04
	WORD index;
	char accountGM[11];
	char nameGM[11];
	UINT Type;
	UINT Value;
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

struct COMMAND_INFO
{
	int code;
	char label[32];
	int	Active;
	int	GMCode;
	int	VipLevel;
	int	MinLevel;
	int	MinReset;
	int	PriceType;
	int	Price[MAX_ACCOUNT_LEVEL];
};

class CCommandManager
{
public:
	CCommandManager();
	virtual ~CCommandManager();
	void Init();
	void Load(char* path);
	void Add(COMMAND_INFO info);
	void MainProc();
	void Add(char* label,int code);
	long GetNumber(char* arg,int pos);
	void GetString(char* arg,char* out,int size,int pos);
	long GetCommandCode(char* label);
	COMMAND_INFO* GetCommandInfo(int index);
	bool ManagementCore(LPOBJ lpObj,char* message);
	void CommandMove(LPOBJ lpObj,char* arg);
	void CommandPost(LPOBJ lpObj,char* arg);
	void CommandAddPoint(LPOBJ lpObj,char* arg,int type);
	void CommandAddPointAuto(LPOBJ lpObj,char* arg,int type);
	void CommandPKClear(LPOBJ lpObj,char* arg);
	void CommandMoney(LPOBJ lpObj,char* arg);
	void CommandChange(LPOBJ lpObj,char* arg);
	void CommandWare(LPOBJ lpObj,char* arg);
	void CommandReset(LPOBJ lpObj,char* arg);
	void CommandResetAuto(LPOBJ lpObj,char* arg);
	void CommandGMMove(LPOBJ lpObj,char* arg);
	void CommandGMPost(LPOBJ lpObj,char* arg);
	void CommandTrack(LPOBJ lpObj,char* arg);
	void CommandTrace(LPOBJ lpObj,char* arg);
	void CommandDisconnect(LPOBJ lpObj,char* arg);
	void CommandFireworks(LPOBJ lpObj,char* arg);
	void CommandMake(LPOBJ lpObj,char* arg);
	void CommandSkin(LPOBJ lpObj,char* arg);
	void CommandSetMoney(LPOBJ lpObj,char* arg);
	void CommandNotice(LPOBJ lpObj,char* arg);
	void CommandMasterReset(LPOBJ lpObj,char* arg);
	void CommandGuildWar(LPOBJ lpObj,char* arg);
	void CommandBattleSoccer(LPOBJ lpObj,char* arg);
	void CommandRequest(LPOBJ lpObj,char* arg);
	void CommandHide(LPOBJ lpObj,char* arg);
	void CommandAddPointAutoProc(LPOBJ lpObj);
	void CommandResetAutoProc(LPOBJ lpObj);
	void DGCommandResetRecv(SDHP_COMMAND_RESET_RECV* lpMsg);
	void DGCommandMasterResetRecv(SDHP_COMMAND_MASTER_RESET_RECV* lpMsg);
	void CommandClearInventory(LPOBJ lpObj,char* arg);
	void CommandPKEvent(LPOBJ lpObj);
	void CommandResetPoint(LPOBJ lpObj);
	void CommandResetSkill(LPOBJ lpObj);
	void CommandResetMaster(LPOBJ lpObj);
	void CommandChangeClass(LPOBJ lpObj,char* arg);
	void CommandRename(LPOBJ lpObj,char* arg);
	void DGCommandRenameRecv(SDHP_COMMAND_RENAME_RECV* lpMsg);
    void CommandBlocAcc(LPOBJ lpObj,char* arg);
    void CommandBlocChar(LPOBJ lpObj,char* arg);
	void CommandSecurity(LPOBJ lpObj,char* arg);
	void CommandMarryProp(LPOBJ lpObj, char* arg);
	void CommandMarryAccept(LPOBJ lpObj, char* arg);
	void CommandMarryTP(LPOBJ lpObj, char* arg);
	void CommandMarryDivorce(LPOBJ lpObj, char* arg);
	void CommandReward(LPOBJ lpObj, char* arg);
	void CommandRewardAll(LPOBJ lpObj, char* arg);
	void CommandMakeSet(LPOBJ lpObj,char* arg);
	void CommandDrop(LPOBJ lpObj,char* arg);
	void CommandMoveAll(LPOBJ lpObj,char* arg);
	void CommandGMove(LPOBJ lpObj,char* arg);
	void CommandDrawMonster(LPOBJ lpObj,char* arg);
	void CommandSetPK(LPOBJ lpObj,char* arg);
	void CommandOnline(LPOBJ lpObj,char* arg);
	void CommandDuelBetSend(LPOBJ lpObj,char* arg);
	void CommandDCFriend(LPOBJ lpObj,char* arg);
	void CommandChatBan(LPOBJ lpObj, char* arg);
	void CommandChatUnBan(LPOBJ lpObj, char* arg);
	void CommandMoveGuild(LPOBJ lpObj,char* arg);
private:
	COMMAND_INFO m_CommandInfo[MAX_COMMAND];
};

extern CCommandManager gCommandManager;
