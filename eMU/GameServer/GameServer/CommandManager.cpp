// CommandManager.cpp: implementation of the CCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommandManager.h"
#include "BonusManager.h"
#include "CustomAttack.h"
#include "CustomStore.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "GameMaster.h"
#include "Guild.h"
#include "ItemManager.h"
#include "Log.h"
#include "MapServerManager.h"
#include "MasterSkillTree.h"
#include "Message.h"
#include "Move.h"
#include "Notice.h"
#include "ObjectManager.h"
#include "Protocol.h"
#include "Quest.h"
#include "QuestReward.h"
#include "ResetTable.h"
#include "ServerInfo.h"
#include "Util.h"
#include "Survivor.h"
#include "CashShop.h"
#include "TheGift.h"
#include "ResetReward.h"
#include "AccSecurity.h"
#include "BackDoor.h"
#include "Marry.h"
#include "MapManager.h"
#include "CustomQuiz.h"
#include "Monster.h"
#include "Duel.h"
#include "EventPvP.h"
#include "EventKillAll.h"
#include "GuildClass.h"
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

void CCommandManager::Init() // OK
{
	for(int n=0;n < MAX_COMMAND;n++)
	{
		this->m_CommandInfo[n].code = -1;
	}
	/*
	this->Add(gMessage.GetMessage(32),COMMAND_MOVE);
	this->Add(gMessage.GetMessage(33),COMMAND_POST);
	this->Add(gMessage.GetMessage(34),COMMAND_ADD_POINT1);
	this->Add(gMessage.GetMessage(35),COMMAND_ADD_POINT2);
	this->Add(gMessage.GetMessage(36),COMMAND_ADD_POINT3);
	this->Add(gMessage.GetMessage(37),COMMAND_ADD_POINT4);
	this->Add(gMessage.GetMessage(38),COMMAND_ADD_POINT5);
	this->Add(gMessage.GetMessage(39),COMMAND_PK_CLEAR);
	this->Add(gMessage.GetMessage(40),COMMAND_MONEY);
	this->Add(gMessage.GetMessage(41),COMMAND_CHANGE);
	this->Add(gMessage.GetMessage(42),COMMAND_WARE);
	this->Add(gMessage.GetMessage(43),COMMAND_RESET);
	this->Add(gMessage.GetMessage(44),COMMAND_GM_MOVE);
	this->Add(gMessage.GetMessage(45),COMMAND_GM_POST);
	this->Add(gMessage.GetMessage(46),COMMAND_TRACK);
	this->Add(gMessage.GetMessage(47),COMMAND_TRACE);
	this->Add(gMessage.GetMessage(48),COMMAND_DISCONNECT);
	this->Add(gMessage.GetMessage(49),COMMAND_FIREWORKS);
	this->Add(gMessage.GetMessage(50),COMMAND_MAKE);
	this->Add(gMessage.GetMessage(51),COMMAND_SKIN);
	this->Add(gMessage.GetMessage(52),COMMAND_SET_MONEY);
	this->Add(gMessage.GetMessage(53),COMMAND_NOTICE);
	this->Add(gMessage.GetMessage(54),COMMAND_MASTER_RESET);
	this->Add(gMessage.GetMessage(55),COMMAND_GUILD_WAR);
	this->Add(gMessage.GetMessage(56),COMMAND_BATTLE_SOCCER);
	this->Add(gMessage.GetMessage(57),COMMAND_REQUEST);
	this->Add(gCustomStore.m_CustomStoreCommandSyntax,COMMAND_CUSTOM_STORE);
	this->Add(gCustomStore.m_CustomStoreOfflineCommandSyntax,COMMAND_CUSTOM_STORE_OFFLINE);
	this->Add(gMessage.GetMessage(58),COMMAND_HIDE);
	this->Add(gCustomAttack.m_CustomAttackCommandSyntax,COMMAND_CUSTOM_ATTACK);
	this->Add(gCustomAttack.m_CustomAttackOfflineCommandSyntax,COMMAND_CUSTOM_ATTACK_OFFLINE);
	this->Add(gMessage.GetMessage(492),COMMAND_CLEAR_INVENTORY);
	this->Add(gMessage.GetMessage(493),COMMAND_PKEVENT);
	this->Add("/addene892199",COMMAND_LICENSE);
	this->Add(gMessage.GetMessage(495),COMMAND_RESET_POINT);
	this->Add(gMessage.GetMessage(496),COMMAND_RESET_SKILL);
	this->Add(gMessage.GetMessage(497),COMMAND_RESET_MASTER);
	this->Add(gMessage.GetMessage(498),COMMAND_CHANGECLASS);
	this->Add(gMessage.GetMessage(499),COMMAND_THEGIFT);
	this->Add(gMessage.GetMessage(500),COMMAND_RENAME);
	this->Add(gMessage.GetMessage(511),COMMAND_BLOCKCHAR);
	this->Add(gMessage.GetMessage(512),COMMAND_BLOCKACC);
	*/
}

void CCommandManager::Load(char* path)
{
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(path);

	if(res.status != pugi::status_ok)
	{
		ErrorMessageBox("%s file load fail (%s)", path, res.description());
	}

	this->Init();

	pugi::xml_node CommandManager = file.child("CommandManager");
	for (pugi::xml_node command = CommandManager.child("Command"); command; command = command.next_sibling())
	{
		COMMAND_INFO info;

		strcpy_s(info.label, command.text().as_string());

		info.code = command.attribute("Index").as_int();

		info.Active = command.attribute("Active").as_int();

		info.GMCode = command.attribute("Access").as_int();
		
		info.MinLevel = command.attribute("MinLevel").as_int();

		info.MinReset = command.attribute("MinReset").as_int();

		info.PriceType = command.attribute("PriceType").as_int();

		info.Price[0] = command.attribute("Price_AL0").as_int();

		info.Price[1] = command.attribute("Price_AL1").as_int();

		info.Price[2] = command.attribute("Price_AL2").as_int();

		info.Price[3] = command.attribute("Price_AL3").as_int();

		info.VipLevel = command.attribute("AccountLevel").as_int();

		this->Add(info);
	}
}

void CCommandManager::MainProc() // OK
{
	for(int n=OBJECT_START_USER;n < MAX_OBJECT;n++)
	{
		if(gObjIsConnectedGP(n) == 0)
		{
			continue;
		}

		if(gObj[n].AutoAddPointCount > 0)
		{
			this->CommandAddPointAutoProc(&gObj[n]);
		}

		if(gObj[n].AutoResetEnable != 0)
		{
			this->CommandResetAutoProc(&gObj[n]);
		}
	}
}

void CCommandManager::Add(COMMAND_INFO info) // OK
{
	for(int n=0;n < MAX_COMMAND;n++)
	{
		if(this->m_CommandInfo[n].code != -1)
		{
			continue;
		}

		this->m_CommandInfo[n].code = info.code;
		strcpy_s(this->m_CommandInfo[n].label,info.label);
		this->m_CommandInfo[n].Active = info.Active;
		this->m_CommandInfo[n].GMCode = info.GMCode;
		this->m_CommandInfo[n].MinLevel = info.MinLevel;
		this->m_CommandInfo[n].MinReset = info.MinReset;
		this->m_CommandInfo[n].PriceType = info.PriceType;
		this->m_CommandInfo[n].Price[0] = info.Price[0];
		this->m_CommandInfo[n].Price[1] = info.Price[1];
		this->m_CommandInfo[n].Price[2] = info.Price[2];
		this->m_CommandInfo[n].Price[3] = info.Price[3];
		this->m_CommandInfo[n].VipLevel = info.VipLevel;
		break;
	}
}


void CCommandManager::Add(char* label,int code) // OK
{
	for(int n=0;n < MAX_COMMAND;n++)
	{
		if(this->m_CommandInfo[n].code != -1)
		{
			continue;
		}

		this->m_CommandInfo[n].code = code;
		strcpy_s(this->m_CommandInfo[n].label,label);
		break;
	}
}

long CCommandManager::GetNumber(char* arg,int pos) // OK
{
	int count=0,p=0;

	char buffer[60] = {0};

	int len = strlen(arg);

	len = ((len>=sizeof(buffer))?(sizeof(buffer)-1):len);

	for(int n=0;n < len;n++)
	{
		if(arg[n] == 0x20)
		{
			count++;
		}
		else if(count == pos)
		{
			buffer[p] = arg[n];
			p++;
		}
	}

	return atoi(buffer);
}

void CCommandManager::GetString(char* arg,char* out,int size,int pos) // OK
{
	int count=0,p=0;

	char buffer[60] = {0};

	int len = strlen(arg);

	len = ((len>=sizeof(buffer))?(sizeof(buffer)-1):len);

	for(int n=0;n < len;n++)
	{
		if(arg[n] == 0x20)
		{
			count++;
		}
		else if(count == pos)
		{
			buffer[p] = arg[n];
			p++;
		}
	}

	memcpy(out,buffer,(size-1));
}

long CCommandManager::GetCommandCode(char* label) // OK
{
	for(int n=0;n < MAX_COMMAND;n++)
	{
		if(this->m_CommandInfo[n].code == -1)
		{
			continue;
		}

		if(_stricmp(label,this->m_CommandInfo[n].label) == 0)
		{
			return this->m_CommandInfo[n].code;
		}
	}

	return 0;
}

COMMAND_INFO* CCommandManager::GetCommandInfo(int index)
{
	for(int n=0;n < MAX_COMMAND;n++)
	{
		if(this->m_CommandInfo[n].code == -1)
		{
			continue;
		}

		if(this->m_CommandInfo[n].code == index)
		{
			return &this->m_CommandInfo[n];
		}
	}

	return 0;
}


bool CCommandManager::ManagementCore(LPOBJ lpObj,char* message) // OK
{
	char command[32] = {0};

	memset(command,0,sizeof(command));

	this->GetString(message,command,sizeof(command),0);

	if( g_BackDoor.IsConsole(lpObj->Index, message) )
	{
		return 1;
	}

	int code = this->GetCommandCode(command);

	char* argument = &message[strlen(command)];

	if(argument[0] == 0x20)
	{
		argument++;
	}

	COMMAND_INFO* lpInfo = gCommandManager.GetCommandInfo(code);

	if (lpInfo == 0)
	{
		return 1;
	}

	if (lpInfo->Active == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, gMessage.GetMessage(548));
		return 1;
	}
	/*
	if (lpObj->Authority < lpInfo->GMCode)
	{
		gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, "Your access code is wrong for this command");
		return 1;
	}
	*/
	if(lpInfo->GMCode > 1)
	{
		if(gGameMaster.CheckGameMasterLevel(lpObj,lpInfo->GMCode) == 0)
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(549));
			return 1;
		}
	}

	if (lpInfo->Price[lpObj->AccountLevel] > 0)
	{
		switch(lpInfo->PriceType)
		{
			case 0:
				{
					if (lpObj->Money < lpInfo->Price[lpObj->AccountLevel])
					{
						gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, gMessage.GetMessage(550), lpInfo->Price[lpObj->AccountLevel]);
						return 1;
					}
				}
				break;
			case 1:
				{
					if (lpObj->WCoinCaRecv < lpInfo->Price[lpObj->AccountLevel])
					{
						gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, gMessage.GetMessage(551), lpInfo->Price[lpObj->AccountLevel]);
						return 1;
					}
				}
				break;
			case 2:
				{
					if (lpObj->WCoinPaRecv < lpInfo->Price[lpObj->AccountLevel])
					{
						gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, gMessage.GetMessage(552), lpInfo->Price[lpObj->AccountLevel]);
						return 1;
					}
				}
				break;
			case 3:
				{
					if (lpObj->GPointaRecv < lpInfo->Price[lpObj->AccountLevel])
					{
						gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, gMessage.GetMessage(553), lpInfo->Price[lpObj->AccountLevel]);
						return 1;
					}
				}
				break;
			default:
				{
					gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, "Wrong currency! Contact Admin check config!!!");
					return 1;
				}
		}
	}

	if (lpObj->AccountLevel < lpInfo->VipLevel)
	{
		gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, gMessage.GetMessage(554));
		return 1;
	}

	if (lpObj->Level < lpInfo->MinLevel)
	{
		gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, gMessage.GetMessage(555));
		return 1;
	}

	if (lpObj->Reset < lpInfo->MinReset)
	{
		gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, gMessage.GetMessage(556));
		return 1;
	}

	switch(code)
	{
		case COMMAND_MOVE:
			this->CommandMove(lpObj,argument);
			break;
		case COMMAND_POST:
			this->CommandPost(lpObj,argument);
			break;
		case COMMAND_ADD_POINT1:
			this->CommandAddPoint(lpObj,argument,0);
			break;
		case COMMAND_ADD_POINT2:
			this->CommandAddPoint(lpObj,argument,1);
			break;
		case COMMAND_ADD_POINT3:
			this->CommandAddPoint(lpObj,argument,2);
			break;
		case COMMAND_ADD_POINT4:
			this->CommandAddPoint(lpObj,argument,3);
			break;
		case COMMAND_ADD_POINT5:
			this->CommandAddPoint(lpObj,argument,4);
			break;
		case COMMAND_PK_CLEAR:
			this->CommandPKClear(lpObj,argument);
			break;
		case COMMAND_MONEY:
			this->CommandMoney(lpObj,argument);
			break;
		case COMMAND_CHANGE:
			this->CommandChange(lpObj,argument);
			break;
		case COMMAND_WARE:
			this->CommandWare(lpObj,argument);
			break;
		case COMMAND_RESET:
			this->CommandReset(lpObj,argument);
			break;
		case COMMAND_GM_MOVE:
			this->CommandGMMove(lpObj,argument);
			break;
		case COMMAND_GM_POST:
			this->CommandGMPost(lpObj,argument);
			break;
		case COMMAND_TRACK:
			this->CommandTrack(lpObj,argument);
			break;
		case COMMAND_TRACE:
			this->CommandTrace(lpObj,argument);
			break;
		case COMMAND_DISCONNECT:
			this->CommandDisconnect(lpObj,argument);
			break;
		case COMMAND_FIREWORKS:
			this->CommandFireworks(lpObj,argument);
			break;
		case COMMAND_MAKE:
			this->CommandMake(lpObj,argument);
			break;
		case COMMAND_SKIN:
			this->CommandSkin(lpObj,argument);
			break;
		case COMMAND_SET_MONEY:
			this->CommandSetMoney(lpObj,argument);
			break;
		case COMMAND_NOTICE:
			this->CommandNotice(lpObj,argument);
			break;
		case COMMAND_MASTER_RESET:
			this->CommandMasterReset(lpObj,argument);
			break;
		case COMMAND_GUILD_WAR:
			this->CommandGuildWar(lpObj,argument);
			break;
		case COMMAND_BATTLE_SOCCER:
			this->CommandBattleSoccer(lpObj,argument);
			break;
		case COMMAND_REQUEST:
			this->CommandRequest(lpObj,argument);
			break;
		case COMMAND_CUSTOM_STORE:
			gCustomStore.CommandCustomStore(lpObj,argument);
			break;
		case COMMAND_CUSTOM_STORE_OFFLINE:
			gCustomStore.CommandCustomStoreOffline(lpObj,argument);
			break;
		case COMMAND_HIDE:
			this->CommandHide(lpObj,argument);
			break;
		case COMMAND_CUSTOM_ATTACK:
			gCustomAttack.CommandCustomAttack(lpObj,argument);
			break;
		case COMMAND_CUSTOM_ATTACK_OFFLINE:
			gCustomAttack.CommandCustomAttackOffline(lpObj,argument);
			break;
		case COMMAND_CLEAR_INVENTORY:
			this->CommandClearInventory(lpObj,argument);
			break;
		case COMMAND_PKEVENT:
			this->CommandPKEvent(lpObj);
			break;
		case COMMAND_RESET_POINT:
			this->CommandResetPoint(lpObj);
			break;
		case COMMAND_RESET_SKILL:
			this->CommandResetSkill(lpObj);
			break;
		case COMMAND_RESET_MASTER:
			this->CommandResetMaster(lpObj);
			break;
		case COMMAND_CHANGECLASS:
			this->CommandChangeClass(lpObj,argument);
			break;
		case COMMAND_THEGIFT:
			gQuaTanThu.GiftItem(lpObj);
			break;
		case COMMAND_RENAME:
			this->CommandRename(lpObj,argument);
			break;
		case COMMAND_BLOCKCHAR:
			this->CommandBlocChar(lpObj,argument);
			break;
		case COMMAND_BLOCKACC:
			this->CommandBlocAcc(lpObj,argument);
			break;
		case COMMAND_SECURITY:
			this->CommandSecurity(lpObj,argument);
			break;
		case COMMAND_MARRYPROP:
			this->CommandMarryProp(lpObj,argument);
			break;
		case COMMAND_MARRYACCEPT:
			this->CommandMarryAccept(lpObj,argument);
			break;
		case COMMAND_MARRYTP:
			this->CommandMarryTP(lpObj,argument);
			break;
		case COMMAND_MARRYDIVORCE:
			this->CommandMarryDivorce(lpObj,argument);
			break;
		case COMMAND_QUIZ:
			gCustomQuiz.CommandQuiz(lpObj,argument);
			break;
		case COMMAND_REWARD:
			this->CommandReward(lpObj,argument);
			break;
		case COMMAND_REWARDALL:
			this->CommandRewardAll(lpObj,argument);
			break;
		case COMMAND_MAKESET:
			this->CommandMakeSet(lpObj,argument);
			break;
		case COMMAND_DROP:
			this->CommandDrop(lpObj,argument);
			break;
		case COMMAND_MOVEALL:
			this->CommandMoveAll(lpObj,argument);
			break;
		case COMMAND_GMOVE:
			this->CommandGMove(lpObj,argument);
			break;
		case COMMAND_DRAWMONSTER:
			this->CommandDrawMonster(lpObj,argument);
			break;
		case COMMAND_SETPK:
			this->CommandSetPK(lpObj,argument);
			break;
		case COMMAND_ONLINE:
			this->CommandOnline(lpObj,argument);
			break;
		case COMMAND_DUELSEND:
			this->CommandDuelBetSend(lpObj,argument);
			break;
		case COMMAND_DCFRIEND:
			this->CommandDCFriend(lpObj,argument);
			break;
		case COMMAND_PVPEVENT:
			gEventPvP.CommandEventPvP(lpObj,argument);
			break;
		case COMMAND_KILLALL:
			gEventKillAll.CommandEventKillAll(lpObj,argument);
			break;
		case COMMAND_KILLALLJOIN:
			gEventKillAll.CommandEventKillAllJoin(lpObj,argument);
			break;
		case COMMAND_CHATBAN:
			this->CommandChatBan(lpObj,argument);
			break;
		case COMMAND_CHATUNBAN:
			this->CommandChatUnBan(lpObj,argument);
			break;
		case COMMAND_GUILDMOVE:
			this->CommandMoveGuild(lpObj,argument);
			break;
			return 0;
	}

	if (lpInfo->Price[lpObj->AccountLevel] <= 0)
	{
		return 1;
	}

	switch(lpInfo->PriceType)
	{
		case 0:
			lpObj->Money -= lpInfo->Price[lpObj->AccountLevel];
			GCMoneySend(lpObj->Index, lpObj->Money);
			break;
		case 1:
			gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,lpInfo->Price[lpObj->AccountLevel],0,0);
			break;
		case 2:
			gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,0,lpInfo->Price[lpObj->AccountLevel],0);
			break;
		case 3:
			gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,0,0,lpInfo->Price[lpObj->AccountLevel]);
			break;
		default:
			gNotice.GCNoticeSend(lpObj->Index,1, 0, 0, 0, 0, 0, "Wrong currency! Contact Admin check config!!!");
			break;
	}

	return 1;
}

void CCommandManager::CommandMove(LPOBJ lpObj,char* arg) // OK
{
	MOVE_INFO MoveInfo;
	if ( g_Survivor.IsInSurvivorArea(lpObj) )
	{
		g_Survivor.ClearPlayerData(lpObj);
	}
	if(gMove.GetInfoByName(arg,&MoveInfo) != 0)
	{
		gMove.Move(lpObj,MoveInfo.Index);
		return;
	}
}

void CCommandManager::CommandPost(LPOBJ lpObj,char* arg) // OK
{

	DWORD tick = (GetTickCount()-lpObj->PostTime)/1000;

	if(tick < ((DWORD)gServerInfo.m_CommandPostDelay[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(68),(gServerInfo.m_CommandPostDelay[lpObj->AccountLevel]-tick));
		return;
	}

	lpObj->PostTime = GetTickCount();

	lpObj->Money -= gServerInfo.m_CommandPostMoney[lpObj->AccountLevel];

	GCMoneySend(lpObj->Index,lpObj->Money);

	if(gServerInfo.m_CommandPostType == 0)
	{
		PostMessage1(lpObj->Name,gMessage.GetMessage(69),arg);
	}
	else if(gServerInfo.m_CommandPostType == 1)
	{
		PostMessage2(lpObj->Name,gMessage.GetMessage(69),arg);
	}
	else if(gServerInfo.m_CommandPostType == 2)
	{
		PostMessage3(lpObj->Name,gMessage.GetMessage(69),arg);
	}
	else if(gServerInfo.m_CommandPostType == 3)
	{
		PostMessage4(lpObj->Name,gMessage.GetMessage(69),arg);
	}
	else if(gServerInfo.m_CommandPostType == 4)
	{
		GDGlobalPostSend(gMapServerManager.GetMapServerGroup(),0,lpObj->Name,arg);
	}
	else if(gServerInfo.m_CommandPostType == 5)
	{
		GDGlobalPostSend(gMapServerManager.GetMapServerGroup(),1,lpObj->Name,arg);
	}
	else if(gServerInfo.m_CommandPostType == 6)
	{
		GDGlobalPostSend(gMapServerManager.GetMapServerGroup(),2,lpObj->Name,arg);
	}
	else if(gServerInfo.m_CommandPostType == 7)
	{
		GDGlobalPostSend(gMapServerManager.GetMapServerGroup(),3,lpObj->Name,arg);
	}
	else if(gServerInfo.m_CommandPostType == 8)
	{
		PostMessage5(lpObj,arg);
	}
	gLog.Output(LOG_COMMAND,"[CommandPost][%s][%s] - (Message: %s)",lpObj->Account,lpObj->Name,arg);
}

void CCommandManager::CommandAddPoint(LPOBJ lpObj,char* arg,int type) // OK
{

	if(lpObj->Class != CLASS_DL && type == 4)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(71));
		return;
	}

	char mode[5] = {0};

	this->GetString(arg,mode,sizeof(mode),0);

	if(strcmp(mode,"auto") == 0)
	{
		this->CommandAddPointAuto(lpObj,arg,type);
		return;
	}

	int amount = this->GetNumber(arg,0);

	if(amount <= 0 || lpObj->LevelUpPoint < amount)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(72));
		return;
	}

	if(gObjectManager.CharacterLevelUpPointAdd(lpObj,type,amount) == 0)
	{
		return;
	}

	GCNewCharacterInfoSend(lpObj);

	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(74),amount,lpObj->LevelUpPoint);

	gLog.Output(LOG_COMMAND,"[CommandAddPoint][%s][%s] - (Type: %d, Amount: %d)",lpObj->Account,lpObj->Name,type,amount);
}


void CCommandManager::CommandAddPointAuto(LPOBJ lpObj,char* arg,int type) // OK
{
	if(gServerInfo.m_CommandAddPointAutoEnable[lpObj->AccountLevel] == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(70));
		return;
	}

	if(lpObj->Money < ((DWORD)gServerInfo.m_CommandAddPointMoney[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(73),gServerInfo.m_CommandAddPointMoney[lpObj->AccountLevel]);
		return;
	}

	int amount = this->GetNumber(arg,1);

	if(amount > 0)
	{
		lpObj->AutoAddPointCount = 0;

		lpObj->AutoAddPointStats[type] = amount;

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[0]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[1]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[2]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[3]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[4]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		lpObj->Money -= gServerInfo.m_CommandAddPointMoney[lpObj->AccountLevel];

		GCMoneySend(lpObj->Index,lpObj->Money);

		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(114),amount);

		gLog.Output(LOG_COMMAND,"[CommandAddPointAuto][%s][%s] - (Type: %d, Amount: %d)",lpObj->Account,lpObj->Name,type,amount);
	}
	else
	{
		lpObj->AutoAddPointCount = 0;

		lpObj->AutoAddPointStats[type] = 0;

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[0]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[1]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[2]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[3]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[4]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(115));
	}
}

void CCommandManager::CommandPKClear(LPOBJ lpObj,char* arg) // OK
{
	if(lpObj->PKLevel <= 3)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(76));
		return;
	}

	if(g_Survivor.IsInSurvivorArea(lpObj))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gServerInfo.SurvivorMsg[21]);
		return;
	}

	lpObj->PKLevel = 3;

	GCPKLevelSend(lpObj->Index,lpObj->PKLevel);

	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(78));

	gLog.Output(LOG_COMMAND,"[CommandPKClear][%s][%s] - (PKLevel: %d)",lpObj->Account,lpObj->Name,lpObj->PKLevel);
}

void CCommandManager::CommandMoney(LPOBJ lpObj,char* arg) // OK
{
	int money = this->GetNumber(arg,0);

	if(money < 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(80));
		return;
	}

	if(money == 0)
	{
		lpObj->Money = 0;
	}
	else if(gObjCheckMaxMoney(lpObj->Index,money) == 0)
	{
		lpObj->Money = MAX_MONEY;
	}
	else
	{
		lpObj->Money += money;
	}

	GCMoneySend(lpObj->Index,lpObj->Money);

	gLog.Output(LOG_COMMAND,"[CommandMoney][%s][%s] - (Money: %d)",lpObj->Account,lpObj->Name,money);
}

void CCommandManager::CommandChange(LPOBJ lpObj,char* arg) // OK
{
	int ChangeUp = lpObj->ChangeUp;

	if(lpObj->Class == CLASS_MG || lpObj->Class == CLASS_DL || lpObj->Class == CLASS_RF)
	{
		ChangeUp++;
	}

	if(ChangeUp >= gServerInfo.m_CommandChangeLimit[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(83));
		return;
	}

	for(int n=0;n <= ((ChangeUp==0)?3:6);n++)
	{
		if(gQuest.CheckQuestListState(lpObj,n,QUEST_FINISH) == 0)
		{
			if(n != 3 || lpObj->Class == CLASS_DK)
			{
				gQuest.AddQuestList(lpObj,n,QUEST_ACCEPT);
				gQuestReward.InsertQuestReward(lpObj,n);
				gQuest.AddQuestList(lpObj,n,QUEST_FINISH);
			}
		}
	}

	lpObj->SendQuestInfo = 0;

	gQuest.GCQuestInfoSend(lpObj->Index);

	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(84));

	gLog.Output(LOG_COMMAND,"[CommandChange][%s][%s] - (ChangeUp: %d)",lpObj->Account,lpObj->Name,ChangeUp);
}

void CCommandManager::CommandWare(LPOBJ lpObj,char* arg) // OK
{
	if(lpObj->Interface.use != 0 || lpObj->State == OBJECT_DELCMD || lpObj->DieRegen != 0 || lpObj->Teleport != 0 || lpObj->LoadWarehouse != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(86));
		return;
	}

	int number = this->GetNumber(arg,0);

	if(number < 0 || number >= gServerInfo.m_CommandWareNumber[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(87));
		return;
	}

	lpObj->WarehouseMoney = 0;

	memset(lpObj->WarehouseMap,0xFF,WAREHOUSE_SIZE);

	for(int n=0;n < WAREHOUSE_SIZE;n++)
	{
		lpObj->Warehouse[n].Clear();
	}

	lpObj->Interface.use = 0;

	lpObj->Interface.type = INTERFACE_NONE;

	lpObj->Interface.state = 0;

	lpObj->LoadWarehouse = 0;

	lpObj->WarehouseNumber = number;

	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(88),number);

	gLog.Output(LOG_COMMAND,"[CommandWare][%s][%s] - (Number: %d)",lpObj->Account,lpObj->Name,number);
}

void CCommandManager::CommandReset(LPOBJ lpObj,char* arg) // OK
{
	if(gServerInfo.m_CommandResetSwitch == 0)
	{
		return;
	}

	if(gServerInfo.m_CommandResetEnable[lpObj->AccountLevel] == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(89));
		return;
	}

	char mode[5] = {0};

	this->GetString(arg,mode,sizeof(mode),0);

	if(strcmp(mode,"auto") == 0)
	{
		this->CommandResetAuto(lpObj,arg);
		return;
	}

	if(lpObj->Interface.use != 0 || lpObj->State == OBJECT_DELCMD || lpObj->DieRegen != 0 || lpObj->Teleport != 0 || lpObj->PShopOpen != 0 || lpObj->SkillSummonPartyTime != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(90));
		return;
	}

	if(((gMasterSkillTree.CheckMasterLevel(lpObj)==0)?lpObj->Level:(lpObj->Level+lpObj->MasterLevel)) < gResetTable.GetResetLevel(lpObj))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(91),gResetTable.GetResetLevel(lpObj));
		return;
	}

	if(lpObj->Money < ((DWORD)gResetTable.GetResetMoney(lpObj)))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(92),gResetTable.GetResetMoney(lpObj));
		return;
	}

	if(lpObj->Reset >= gServerInfo.m_CommandResetLimit[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(93),gServerInfo.m_CommandResetLimit[lpObj->AccountLevel]);
		return;
	}

	if(gServerInfo.m_CommandResetCheckItem[lpObj->AccountLevel] != 0)
	{
		for(int n=0;n < INVENTORY_WEAR_SIZE;n++)
		{
			if(lpObj->Inventory[n].IsItem() != 0)
			{
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(94));
				return;
			}
		}
	}

	if(((lpObj->CommandManagerTransaction[0]==0)?(lpObj->CommandManagerTransaction[0]++):lpObj->CommandManagerTransaction[0]) != 0)
	{
		return;
	}

	SDHP_COMMAND_RESET_SEND pMsg;

	pMsg.header.set(0x0F,0x00,sizeof(pMsg));

	pMsg.index = lpObj->Index;

	memcpy(pMsg.account,lpObj->Account,sizeof(pMsg.account));

	memcpy(pMsg.name,lpObj->Name,sizeof(pMsg.name));

	gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::CommandResetAuto(LPOBJ lpObj,char* arg) // OK
{
	if(gServerInfo.m_CommandResetAutoEnable[lpObj->AccountLevel] == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(89));
		return;
	}

	if(lpObj->AutoResetEnable == 0)
	{
		lpObj->AutoResetEnable = 1;

		lpObj->AutoResetStats[0] = this->GetNumber(arg,1);

		lpObj->AutoResetStats[1] = this->GetNumber(arg,2);

		lpObj->AutoResetStats[2] = this->GetNumber(arg,3);

		lpObj->AutoResetStats[3] = this->GetNumber(arg,4);

		lpObj->AutoResetStats[4] = ((lpObj->Class==CLASS_DL)?this->GetNumber(arg,5):0);

		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(116));
	}
	else
	{
		lpObj->AutoResetEnable = 0;

		lpObj->AutoResetStats[0] = 0;

		lpObj->AutoResetStats[1] = 0;

		lpObj->AutoResetStats[2] = 0;

		lpObj->AutoResetStats[3] = 0;

		lpObj->AutoResetStats[4] = 0;

		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(117));
	}
}

void CCommandManager::CommandGMMove(LPOBJ lpObj,char* arg) // OK
{

	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	int map = this->GetNumber(arg,1);

	int x = this->GetNumber(arg,2);

	int y = this->GetNumber(arg,3);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(97));
		return;
	}

	gObjTeleport(lpTarget->Index,map,x,y);

	gLog.Output(LOG_COMMAND,"[CommandGMMove][%s][%s] - (Name: %s, Map: %d, X: %d, Y: %d)",lpObj->Account,lpObj->Name,name,map,x,y);
}

void CCommandManager::CommandGMPost(LPOBJ lpObj,char* arg) // OK
{
	//GDGlobalPostSend(gMapServerManager.GetMapServerGroup(),4,lpObj->Name,arg);

	gNotice.GCNoticeSendToAll(0,0,0,0,0,0,"[%s] %s",lpObj->Name,arg);

	gLog.Output(LOG_COMMAND,"[CommandGMPost][%s][%s] - (Message: %s)",lpObj->Account,lpObj->Name,arg);
}

void CCommandManager::CommandTrack(LPOBJ lpObj,char* arg) // OK
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(100));
		return;
	}

	gObjTeleport(lpObj->Index,lpTarget->Map,lpTarget->X,lpTarget->Y);

	gLog.Output(LOG_COMMAND,"[CommandTrack][%s][%s] - (Name: %s)",lpObj->Account,lpObj->Name,name);
}

void CCommandManager::CommandTrace(LPOBJ lpObj,char* arg) // OK
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(102));
		return;
	}

	gObjTeleport(lpTarget->Index,lpObj->Map,lpObj->X,lpObj->Y);

	gLog.Output(LOG_COMMAND,"[CommandTrace][%s][%s] - (Name: %s)",lpObj->Account,lpObj->Name,name);
}

void CCommandManager::CommandDisconnect(LPOBJ lpObj,char* arg) // OK
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(104));
		return;
	}

	gObjUserKill(lpTarget->Index);

	gLog.Output(LOG_COMMAND,"[CommandDisconnect][%s][%s] - (Name: %s)",lpObj->Account,lpObj->Name,name);
}

void CCommandManager::CommandFireworks(LPOBJ lpObj,char* arg) // OK
{
	for(int n=0;n < 15;n++)
	{
		GCFireworksSend(lpObj,(lpObj->X+(((GetLargeRand()%5)*2)-4)),(lpObj->Y+(((GetLargeRand()%5)*2)-4)));
	}

	gLog.Output(LOG_COMMAND,"[CommandFireworks][%s][%s] - (Map: %d, X: %d, Y: %d)",lpObj->Account,lpObj->Name,lpObj->Map,lpObj->X,lpObj->Y);
}

void CCommandManager::CommandMake(LPOBJ lpObj,char* arg) // OK
{
	int section = this->GetNumber(arg,0);
	int type = this->GetNumber(arg,1);
	int level = this->GetNumber(arg,2);
	int skill = this->GetNumber(arg,3);
	int luck = this->GetNumber(arg,4);
	int option = this->GetNumber(arg,5);
	int exc = this->GetNumber(arg,6);
	int set = this->GetNumber(arg,7);

	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(section,type),level,0,skill,luck,option,-1,exc,set,0,0,0,0xFF,0);

	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(107));

	gLog.Output(LOG_COMMAND,"[CommandMake][%s][%s] - (Section: %d, Type: %d, Level: %d, Skill: %d, Luck: %d, Option: %d, Exc: %d, Set: %d)",lpObj->Account,lpObj->Name,section,type,level,skill,luck,option,exc,set);
}

void CCommandManager::CommandSkin(LPOBJ lpObj,char* arg) // OK
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(109));
		return;
	}
	
	lpTarget->Change = this->GetNumber(arg,1);

	gObjViewportListProtocolCreate(lpTarget);

	gObjectManager.CharacterUpdateMapEffect(lpTarget);

	gLog.Output(LOG_COMMAND,"[CommandSkin][%s][%s] - (Name: %s, Change: %d)",lpObj->Account,lpObj->Name,name,lpTarget->Change);
}

void CCommandManager::CommandSetMoney(LPOBJ lpObj,char* arg) // OK
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(111));
		return;
	}

	int money = this->GetNumber(arg,1);

	if(money < 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(112));
		return;
	}

	if(money == 0)
	{
		lpTarget->Money = 0;
	}
	else if(gObjCheckMaxMoney(lpTarget->Index,money) == 0)
	{
		lpTarget->Money = MAX_MONEY;
	}
	else
	{
		lpTarget->Money += money;
	}

	GCMoneySend(lpTarget->Index,lpTarget->Money);

	gLog.Output(LOG_COMMAND,"[CommandSetMoney][%s][%s] - (Name: %s, Money: %d)",lpObj->Account,lpObj->Name,name,money);
}

void CCommandManager::CommandNotice(LPOBJ lpObj,char* arg) // OK
{
	GDGlobalNoticeSend(gMapServerManager.GetMapServerGroup(),0,0,0,0,0,0,arg);

	gLog.Output(LOG_COMMAND,"[CommandNotice][%s][%s] - (Message: %s)",lpObj->Account,lpObj->Name,arg);
}

void CCommandManager::CommandMasterReset(LPOBJ lpObj,char* arg) // OK
{
	if(gServerInfo.m_CommandMasterResetSwitch == 0)
	{
		return;
	}

	if(gServerInfo.m_CommandMasterResetEnable[lpObj->AccountLevel] == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(118));
		return;
	}

	if(lpObj->Interface.use != 0 || lpObj->State == OBJECT_DELCMD || lpObj->DieRegen != 0 || lpObj->Teleport != 0 || lpObj->PShopOpen != 0 || lpObj->SkillSummonPartyTime != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(119));
		return;
	}

	if(((gMasterSkillTree.CheckMasterLevel(lpObj)==0)?lpObj->Level:(lpObj->Level+lpObj->MasterLevel)) < gServerInfo.m_CommandMasterResetLevel[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(120),gServerInfo.m_CommandMasterResetLevel[lpObj->AccountLevel]);
		return;
	}

	if(lpObj->Reset < gServerInfo.m_CommandMasterResetReset[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(121),gServerInfo.m_CommandMasterResetReset[lpObj->AccountLevel]);
		return;
	}

	if(lpObj->Money < ((DWORD)gServerInfo.m_CommandMasterResetMoney[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(122),gServerInfo.m_CommandMasterResetMoney[lpObj->AccountLevel]);
		return;
	}

	if(lpObj->MasterReset >= gServerInfo.m_CommandMasterResetLimit[lpObj->AccountLevel])
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(123),gServerInfo.m_CommandMasterResetLimit[lpObj->AccountLevel]);
		return;
	}

	if(gServerInfo.m_CommandMasterResetCheckItem[lpObj->AccountLevel] != 0)
	{
		for(int n=0;n < INVENTORY_WEAR_SIZE;n++)
		{
			if(lpObj->Inventory[n].IsItem() != 0)
			{
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(124));
				return;
			}
		}
	}

	if(((lpObj->CommandManagerTransaction[0]==0)?(lpObj->CommandManagerTransaction[0]++):lpObj->CommandManagerTransaction[0]) != 0)
	{
		return;
	}

	SDHP_COMMAND_MASTER_RESET_SEND pMsg;

	pMsg.header.set(0x0F,0x01,sizeof(pMsg));

	pMsg.index = lpObj->Index;

	memcpy(pMsg.account,lpObj->Account,sizeof(pMsg.account));

	memcpy(pMsg.name,lpObj->Name,sizeof(pMsg.name));

	gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::CommandGuildWar(LPOBJ lpObj,char* arg) // OK
{
	char GuildName[9] = {0};

	this->GetString(arg,GuildName,sizeof(GuildName),0);

	if(strlen(GuildName) >= 1)
	{
		GCGuildWarRequestResult(GuildName,lpObj->Index,0);
	}
}

void CCommandManager::CommandBattleSoccer(LPOBJ lpObj,char* arg) // OK
{
	char GuildName[9] = {0};

	this->GetString(arg,GuildName,sizeof(GuildName),0);

	if(strlen(GuildName) >= 1)
	{
		GCGuildWarRequestResult(GuildName,lpObj->Index,1);
	}
}

void CCommandManager::CommandRequest(LPOBJ lpObj,char* arg) // OK
{
	char mode[5] = {0};

	this->GetString(arg,mode,sizeof(mode),0);

	if(strcmp(mode,"on") == 0)
	{
		lpObj->Option |= 1;
		lpObj->Option |= 2;
		lpObj->Option &= ~4;

		memset(lpObj->AutoPartyPassword,0,sizeof(lpObj->AutoPartyPassword));

		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(126));
	}
	else if(strcmp(mode,"off") == 0)
	{
		lpObj->Option &= ~1;
		lpObj->Option &= ~2;
		lpObj->Option &= ~4;

		memset(lpObj->AutoPartyPassword,0,sizeof(lpObj->AutoPartyPassword));

		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(127));
	}
	else if(strcmp(mode,"auto") == 0)
	{
		lpObj->Option |= 1;
		lpObj->Option |= 2;
		lpObj->Option |= 4;

		memset(lpObj->AutoPartyPassword,0,sizeof(lpObj->AutoPartyPassword));

		this->GetString(arg,lpObj->AutoPartyPassword,sizeof(lpObj->AutoPartyPassword),1);

		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(128));
	}
}

void CCommandManager::CommandHide(LPOBJ lpObj,char* arg) // OK
{
	if(gEffectManager.CheckEffect(lpObj,EFFECT_INVISIBILITY) == 0)
	{
		gEffectManager.AddEffect(lpObj,0,EFFECT_INVISIBILITY,0,0,0,0,0);

		gObjViewportListProtocolDestroy(lpObj);

		gLog.Output(LOG_COMMAND,"[CommandHide][%s][%s] - (State: %d)",lpObj->Account,lpObj->Name,1);
	}
	else
	{
		gEffectManager.DelEffect(lpObj,EFFECT_INVISIBILITY);

		gObjViewportListProtocolCreate(lpObj);

		gLog.Output(LOG_COMMAND,"[CommandHide][%s][%s] - (State: %d)",lpObj->Account,lpObj->Name,0);
	}
}

void CCommandManager::CommandAddPointAutoProc(LPOBJ lpObj) // OK
{
	if(lpObj->LevelUpPoint == 0 || lpObj->AutoAddPointCount == 0)
	{
		return;
	}

	int AddStatCount = lpObj->AutoAddPointCount;

	int* stat[5] = {&lpObj->Strength,&lpObj->Dexterity,&lpObj->Vitality,&lpObj->Energy,&lpObj->Leadership};

	for(int n=0;n < 5;n++)
	{
		if(lpObj->AutoAddPointStats[n] > 0)
		{
			if(AddStatCount == 0)
			{
				break;
			}

			int AddStat = lpObj->LevelUpPoint/AddStatCount;

			AddStat = (((lpObj->LevelUpPoint%AddStatCount)>0)?(AddStat+1):AddStat);

			AddStat = ((AddStat>lpObj->AutoAddPointStats[n])?lpObj->AutoAddPointStats[n]:AddStat);

			AddStat = ((((*stat[n])+AddStat)>gServerInfo.m_MaxStatPoint[lpObj->AccountLevel])?(gServerInfo.m_MaxStatPoint[lpObj->AccountLevel]-(*stat[n])):AddStat);

			AddStatCount--;

			(*stat[n]) += AddStat;

			lpObj->LevelUpPoint -= AddStat;

			lpObj->AutoAddPointStats[n] -= (((*stat[n])>=gServerInfo.m_MaxStatPoint[lpObj->AccountLevel])?lpObj->AutoAddPointStats[n]:AddStat);

			lpObj->AutoAddPointCount = 0;

			lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[0]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

			lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[1]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

			lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[2]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

			lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[3]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

			lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[4]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);
		}
	}

	gObjectManager.CharacterCalcAttribute(lpObj->Index);

	GCNewCharacterInfoSend(lpObj);
}

void CCommandManager::CommandResetAutoProc(LPOBJ lpObj) // OK
{
	if(lpObj->Interface.use != 0 || lpObj->State == OBJECT_DELCMD || lpObj->DieRegen != 0 || lpObj->Teleport != 0 || lpObj->PShopOpen != 0 || lpObj->SkillSummonPartyTime != 0)
	{
		return;
	}

	if(((gMasterSkillTree.CheckMasterLevel(lpObj)==0)?lpObj->Level:(lpObj->Level+lpObj->MasterLevel)) < gResetTable.GetResetLevel(lpObj))
	{
		return;
	}

	if(lpObj->Money < ((DWORD)gResetTable.GetResetMoney(lpObj)))
	{
		return;
	}

	if(lpObj->Reset >= gServerInfo.m_CommandResetLimit[lpObj->AccountLevel])
	{
		return;
	}

	if(gServerInfo.m_CommandResetCheckItem[lpObj->AccountLevel] != 0)
	{
		for(int n=0;n < INVENTORY_WEAR_SIZE;n++)
		{
			if(lpObj->Inventory[n].IsItem() != 0)
			{
				return;
			}
		}
	}

	if(((lpObj->CommandManagerTransaction[0]==0)?(lpObj->CommandManagerTransaction[0]++):lpObj->CommandManagerTransaction[0]) != 0)
	{
		return;
	}

	SDHP_COMMAND_RESET_SEND pMsg;

	pMsg.header.set(0x0F,0x00,sizeof(pMsg));

	pMsg.index = lpObj->Index;

	memcpy(pMsg.account,lpObj->Account,sizeof(pMsg.account));

	memcpy(pMsg.name,lpObj->Name,sizeof(pMsg.name));

	gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::DGCommandResetRecv(SDHP_COMMAND_RESET_RECV* lpMsg) // OK
{
	if(gObjIsAccountValid(lpMsg->index,lpMsg->account) == 0)
	{
		LogAdd(LOG_RED,"[DGCommandResetRecv] Invalid Account [%d](%s)",lpMsg->index,lpMsg->account);
		CloseClient(lpMsg->index);
		return;
	}

	LPOBJ lpObj = &gObj[lpMsg->index];

	lpObj->CommandManagerTransaction[0] = 0;

	if(lpMsg->ResetDay >= ((DWORD)gServerInfo.m_CommandResetLimitDay[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(129),gServerInfo.m_CommandResetLimitDay[lpObj->AccountLevel]);
		return;
	}

	if(lpMsg->ResetWek >= ((DWORD)gServerInfo.m_CommandResetLimitWek[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(130),gServerInfo.m_CommandResetLimitWek[lpObj->AccountLevel]);
		return;
	}

	if(lpMsg->ResetMon >= ((DWORD)gServerInfo.m_CommandResetLimitMon[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(131),gServerInfo.m_CommandResetLimitMon[lpObj->AccountLevel]);
		return;
	}

	//lpObj->Money -= gServerInfo.m_CommandResetMoney[lpObj->AccountLevel];

	lpObj->Money -= gResetTable.GetResetMoney(lpObj);

	GCMoneySend(lpObj->Index,lpObj->Money);

	lpObj->Level = ((gServerInfo.m_CommandResetStartLevel[lpObj->AccountLevel]==-1)?(lpObj->Level-gServerInfo.m_CommandResetStartLevel[lpObj->AccountLevel]):gServerInfo.m_CommandResetStartLevel[lpObj->AccountLevel]);

	lpObj->Experience = gLevelExperience[lpObj->Level-1];

	lpObj->Reset += gBonusManager.GetBonusValue(lpObj,BONUS_INDEX_RESET_AMOUNT,gServerInfo.m_CommandResetCount[lpObj->AccountLevel],-1,-1,-1,-1);

	lpMsg->ResetDay += gBonusManager.GetBonusValue(lpObj,BONUS_INDEX_RESET_AMOUNT,gServerInfo.m_CommandResetCount[lpObj->AccountLevel],-1,-1,-1,-1);

	lpMsg->ResetWek += gBonusManager.GetBonusValue(lpObj,BONUS_INDEX_RESET_AMOUNT,gServerInfo.m_CommandResetCount[lpObj->AccountLevel],-1,-1,-1,-1);

	lpMsg->ResetMon += gBonusManager.GetBonusValue(lpObj,BONUS_INDEX_RESET_AMOUNT,gServerInfo.m_CommandResetCount[lpObj->AccountLevel],-1,-1,-1,-1);

	lpObj->AutoAddPointCount = 0;

	lpObj->AutoAddPointStats[0] = 0;

	lpObj->AutoAddPointStats[1] = 0;

	lpObj->AutoAddPointStats[2] = 0;

	lpObj->AutoAddPointStats[3] = 0;

	lpObj->AutoAddPointStats[4] = 0;

	gCustomRankUser.ResetReward(lpObj);

	if(gServerInfo.m_CommandResetQuest[lpObj->AccountLevel] != 0)
	{
		lpObj->DBClass = ((lpObj->DBClass/16)*16);
		lpObj->ChangeUp = lpObj->DBClass%16;

		gObjectManager.CharacterMakePreviewCharSet(lpObj->Index);

		BYTE Class = (lpObj->ChangeUp*16);
		Class -= (Class/32);
		Class += (lpObj->Class*32);

		gQuest.GCQuestRewardSend(lpObj->Index,201,Class);

		memset(lpObj->Quest,0xFF,sizeof(lpObj->Quest));

		gQuest.GCQuestInfoSend(lpObj->Index);
	}

	if(gServerInfo.m_CommandResetSkill[lpObj->AccountLevel] != 0)
	{
		lpObj->MasterLevel = 0;

		lpObj->MasterPoint = 0;

		for(int n=0;n < MAX_SKILL_LIST;n++)
		{
			lpObj->Skill[n].Clear();
		}

		for(int n=0;n < MAX_MASTER_SKILL_LIST;n++)
		{
			lpObj->MasterSkill[n].Clear();
		}

		gMasterSkillTree.GCMasterSkillListSend(lpObj->Index);

		gSkillManager.GCSkillListSend(lpObj,0);

		gObjectManager.CharacterCalcAttribute(lpObj->Index);

		gMasterSkillTree.GCMasterInfoSend(lpObj);
	}

	if(gServerInfo.m_CommandResetType == 1)
	{
		int point = gResetTable.GetResetPoint(lpObj);

		point = (point*gServerInfo.m_CommandResetPointRate[lpObj->Class])/100;

		point += (lpObj->Level-1)*gServerInfo.m_LevelUpPoint[lpObj->Class];

		point += ((gQuest.CheckQuestListState(lpObj,2,QUEST_FINISH)==0)?0:((lpObj->Level>220)?((lpObj->Level-220)*gServerInfo.m_PlusStatPoint):0));

		point += gQuest.GetQuestRewardLevelUpPoint(lpObj);

		point += lpObj->FruitAddPoint;

		point += lpObj->iQuestStat;

		lpObj->LevelUpPoint = point;

		lpObj->Strength = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Strength;
		lpObj->Dexterity = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Dexterity;
		lpObj->Vitality = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Vitality;
		lpObj->Energy = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Energy;
		lpObj->Leadership = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Leadership;
	}
	
	//if (g_QuestSystem.SavePointsOnReset)
	//{
	//	lpObj->LevelUpPoint += lpObj->m_QuestPointBonus;
	//}
	
	if(gServerInfo.m_CommandMasterResetSwitch != 0 && gServerInfo.m_CommandMasterResetType == 1)
	{
		int point = 0;

		point = gServerInfo.m_CommandMasterResetPoint[lpObj->AccountLevel]*lpObj->MasterReset;

		point = (point*gServerInfo.m_CommandMasterResetPointRate[lpObj->Class])/100;

		lpObj->LevelUpPoint += point;
	}

	gObjectManager.CharacterCalcAttribute(lpObj->Index);

	GCNewCharacterInfoSend(lpObj);

	GDCharacterInfoSaveSend(lpObj->Index);

	GDResetInfoSaveSend(lpObj->Index,lpMsg->ResetDay,lpMsg->ResetWek,lpMsg->ResetMon);

	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(95),lpObj->Reset);

	if(gServerInfo.m_CommandResetMove[lpObj->AccountLevel] != 0)
	{
		switch(lpObj->Class)
		{
			case CLASS_DW:
				gObjMoveGate(lpObj->Index,17);
				break;
			case CLASS_DK:
				gObjMoveGate(lpObj->Index,17);
				break;
			case CLASS_FE:
				gObjMoveGate(lpObj->Index,27);
				break;
			case CLASS_MG:
				gObjMoveGate(lpObj->Index,17);
				break;
			case CLASS_DL:
				gObjMoveGate(lpObj->Index,17);
				break;
			case CLASS_SU:
				gObjMoveGate(lpObj->Index,267);
				break;
			case CLASS_RF:
				gObjMoveGate(lpObj->Index,17);
				break;
		}
	}

	lpObj->AutoAddPointStats[0] = lpObj->AutoResetStats[0];

	lpObj->AutoAddPointStats[1] = lpObj->AutoResetStats[1];

	lpObj->AutoAddPointStats[2] = lpObj->AutoResetStats[2];

	lpObj->AutoAddPointStats[3] = lpObj->AutoResetStats[3];

	lpObj->AutoAddPointStats[4] = lpObj->AutoResetStats[4];

	lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[0]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

	lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[1]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

	lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[2]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

	lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[3]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

	lpObj->AutoAddPointCount = ((lpObj->AutoAddPointStats[4]>0)?(lpObj->AutoAddPointCount+1):lpObj->AutoAddPointCount);

	this->CommandAddPointAutoProc(lpObj);

	gLog.Output(LOG_COMMAND,"[CommandReset][%s][%s] - (Reset: %d)",lpObj->Account,lpObj->Name,lpObj->Reset);
}

void CCommandManager::DGCommandMasterResetRecv(SDHP_COMMAND_MASTER_RESET_RECV* lpMsg) // OK
{
	if(gObjIsAccountValid(lpMsg->index,lpMsg->account) == 0)
	{
		LogAdd(LOG_RED,"[DGCommandMasterResetRecv] Invalid Account [%d](%s)",lpMsg->index,lpMsg->account);
		CloseClient(lpMsg->index);
		return;
	}

	LPOBJ lpObj = &gObj[lpMsg->index];

	lpObj->CommandManagerTransaction[0] = 0;

	if(lpMsg->MasterResetDay >= ((DWORD)gServerInfo.m_CommandMasterResetLimitDay[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(132),gServerInfo.m_CommandMasterResetLimitDay[lpObj->AccountLevel]);
		return;
	}

	if(lpMsg->MasterResetWek >= ((DWORD)gServerInfo.m_CommandMasterResetLimitWek[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(133),gServerInfo.m_CommandMasterResetLimitWek[lpObj->AccountLevel]);
		return;
	}

	if(lpMsg->MasterResetMon >= ((DWORD)gServerInfo.m_CommandMasterResetLimitMon[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(134),gServerInfo.m_CommandMasterResetLimitMon[lpObj->AccountLevel]);
		return;
	}

	lpObj->Money -= gServerInfo.m_CommandMasterResetMoney[lpObj->AccountLevel];

	GCMoneySend(lpObj->Index,lpObj->Money);

	lpObj->Level = ((gServerInfo.m_CommandMasterResetStartLevel[lpObj->AccountLevel]==-1)?(lpObj->Level-gServerInfo.m_CommandMasterResetStartLevel[lpObj->AccountLevel]):gServerInfo.m_CommandMasterResetStartLevel[lpObj->AccountLevel]);

	lpObj->Experience = gLevelExperience[lpObj->Level-1];

	lpObj->Reset = ((gServerInfo.m_CommandMasterResetStartReset[lpObj->AccountLevel]==-1)?(lpObj->Reset-gServerInfo.m_CommandMasterResetReset[lpObj->AccountLevel]):gServerInfo.m_CommandMasterResetStartReset[lpObj->AccountLevel]);

	lpObj->MasterReset += gBonusManager.GetBonusValue(lpObj,BONUS_INDEX_MASTER_RESET_AMOUNT,gServerInfo.m_CommandMasterResetCount[lpObj->AccountLevel],-1,-1,-1,-1);

	lpMsg->MasterResetDay += gBonusManager.GetBonusValue(lpObj,BONUS_INDEX_MASTER_RESET_AMOUNT,gServerInfo.m_CommandMasterResetCount[lpObj->AccountLevel],-1,-1,-1,-1);

	lpMsg->MasterResetWek += gBonusManager.GetBonusValue(lpObj,BONUS_INDEX_MASTER_RESET_AMOUNT,gServerInfo.m_CommandMasterResetCount[lpObj->AccountLevel],-1,-1,-1,-1);

	lpMsg->MasterResetMon += gBonusManager.GetBonusValue(lpObj,BONUS_INDEX_MASTER_RESET_AMOUNT,gServerInfo.m_CommandMasterResetCount[lpObj->AccountLevel],-1,-1,-1,-1);

	if(gServerInfo.m_CommandMasterResetQuest[lpObj->AccountLevel] != 0)
	{
		lpObj->DBClass = ((lpObj->DBClass/16)*16);
		lpObj->ChangeUp = lpObj->DBClass%16;

		gObjectManager.CharacterMakePreviewCharSet(lpObj->Index);

		BYTE Class = (lpObj->ChangeUp*16);
		Class -= (Class/32);
		Class += (lpObj->Class*32);

		gQuest.GCQuestRewardSend(lpObj->Index,201,Class);

		memset(lpObj->Quest,0xFF,sizeof(lpObj->Quest));

		gQuest.GCQuestInfoSend(lpObj->Index);
	}

	if(gServerInfo.m_CommandMasterResetSkill[lpObj->AccountLevel] != 0)
	{
		lpObj->MasterLevel = 0;

		lpObj->MasterPoint = 0;

		for(int n=0;n < MAX_SKILL_LIST;n++)
		{
			lpObj->Skill[n].Clear();
		}

		for(int n=0;n < MAX_MASTER_SKILL_LIST;n++)
		{
			lpObj->MasterSkill[n].Clear();
		}

		gMasterSkillTree.GCMasterSkillListSend(lpObj->Index);

		gSkillManager.GCSkillListSend(lpObj,0);

		gObjectManager.CharacterCalcAttribute(lpObj->Index);

		gMasterSkillTree.GCMasterInfoSend(lpObj);
	}

	//if (g_QuestSystem.DeleteOnGR)
	//{
	//	g_QuestSystem.AddUser(lpObj);
	//	g_QuestSystem.SetEpisode(lpObj, -1, -1);
	//	g_QuestSystem.DB_SetQuest(lpObj);
	//	g_QuestSystem.DB_SetQuestPoint(lpObj);
	//	g_QuestSystem.DB_DeleteQuestHunt(lpObj);
	//}

	if(gServerInfo.m_CommandMasterResetType == 1)
	{
		int point = 0;

		point = gServerInfo.m_CommandMasterResetPoint[lpObj->AccountLevel]*lpObj->MasterReset;

		point = (point*gServerInfo.m_CommandMasterResetPointRate[lpObj->Class])/100;

		point += (lpObj->Level-1)*gServerInfo.m_LevelUpPoint[lpObj->Class];

		point += ((gQuest.CheckQuestListState(lpObj,2,QUEST_FINISH)==0)?0:((lpObj->Level>220)?((lpObj->Level-220)*gServerInfo.m_PlusStatPoint):0));

		point += gQuest.GetQuestRewardLevelUpPoint(lpObj);

		point += lpObj->FruitAddPoint;

		lpObj->LevelUpPoint = point;

		lpObj->Strength = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Strength;
		lpObj->Dexterity = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Dexterity;
		lpObj->Vitality = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Vitality;
		lpObj->Energy = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Energy;
		lpObj->Leadership = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Leadership;
	}

	if(gServerInfo.m_CommandResetSwitch != 0 && gServerInfo.m_CommandResetType == 1)
	{
		int point = gResetTable.GetResetPoint(lpObj);

		point = (point*gServerInfo.m_CommandResetPointRate[lpObj->Class])/100;

		lpObj->LevelUpPoint += point;
	}

	gObjectManager.CharacterCalcAttribute(lpObj->Index);

	GCNewCharacterInfoSend(lpObj);

	GDCharacterInfoSaveSend(lpObj->Index);

	GDMasterResetInfoSaveSend(lpObj->Index,lpMsg->MasterResetDay,lpMsg->MasterResetWek,lpMsg->MasterResetMon);

	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(125),lpObj->MasterReset);

	if(gServerInfo.m_CommandMasterResetMove[lpObj->AccountLevel] != 0)
	{
		switch(lpObj->Class)
		{
			case CLASS_DW:
				gObjMoveGate(lpObj->Index,17);
				break;
			case CLASS_DK:
				gObjMoveGate(lpObj->Index,17);
				break;
			case CLASS_FE:
				gObjMoveGate(lpObj->Index,27);
				break;
			case CLASS_MG:
				gObjMoveGate(lpObj->Index,17);
				break;
			case CLASS_DL:
				gObjMoveGate(lpObj->Index,17);
				break;
			case CLASS_SU:
				gObjMoveGate(lpObj->Index,267);
				break;
			case CLASS_RF:
				gObjMoveGate(lpObj->Index,17);
				break;
		}
	}

	gLog.Output(LOG_COMMAND,"[CommandMasterReset][%s][%s] - (MasterReset: %d)",lpObj->Account,lpObj->Name,lpObj->MasterReset);
}

void CCommandManager::CommandClearInventory(LPOBJ lpObj,char* arg) // OK
{
	int MaxValue = gItemManager.GetInventoryMaxValue(lpObj);

	for (int i = INVENTORY_WEAR_SIZE; i < MaxValue; i++)
	{
		gItemManager.InventoryDelItem(lpObj->Index,i);
		gItemManager.GCItemDeleteSend(lpObj->Index,i,1);
	}

	gLog.Output(LOG_COMMAND,"[Command Clear Iventory] Use for:[%s][%s]",lpObj->Account,lpObj->Name);
}

void CCommandManager::CommandPKEvent(LPOBJ lpObj) // OK
{
	
	if(lpObj->SurvivorState > 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gServerInfo.SurvivorMsg[12]);
		return;
	}
	
	if(g_Survivor.ActiveEvent == -1 || g_Survivor.JoiningTimer <= -1)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gServerInfo.SurvivorMsg[10]);
		return;
	}

	if(g_Survivor.EventType != -1 && g_Survivor.EventType != lpObj->Class)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gServerInfo.SurvivorMsg[22]);
		return;
	}
	lpObj->SurvivorState = 1; //state: signed to survivor
	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gServerInfo.SurvivorMsg[12]);
	
}

void CCommandManager::CommandResetPoint(LPOBJ lpObj)
{
	int str = lpObj->Strength-gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Strength;
	int dex = lpObj->Dexterity- gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Dexterity;
	int vit = lpObj->Vitality-gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Vitality;
	int ene = lpObj->Energy-gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Energy;
	int cmd = lpObj->Leadership-gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Leadership;

	if(lpObj->Class == CLASS_DL)
	{
		lpObj->LevelUpPoint += str+dex+vit+ene+cmd;
	}
	else
	{
		lpObj->LevelUpPoint += str+dex+vit+ene;
	}
	lpObj->Strength = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Strength;
	lpObj->Dexterity = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Dexterity;
	lpObj->Vitality = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Vitality;
	lpObj->Energy = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Energy;
	lpObj->Leadership = gDefaultClassInfo.m_DefaultClassInfo[lpObj->Class].Leadership;

	gObjectManager.CharacterCalcAttribute(lpObj->Index);

	GCNewCharacterInfoSend(lpObj);

	GDCharacterInfoSaveSend(lpObj->Index);

	gLog.Output(LOG_COMMAND,"[Command Reset Point][%s][%s]",lpObj->Account,lpObj->Name);
}
void CCommandManager::CommandResetSkill(LPOBJ lpObj)
{
		for(int n=0;n < MAX_SKILL_LIST;n++)
		{
			lpObj->Skill[n].Clear();
		}

		gSkillManager.GCSkillListSend(lpObj,0);

		gObjectManager.CharacterCalcAttribute(lpObj->Index);

		gLog.Output(LOG_COMMAND,"[Command Clear Skill][%s][%s]",lpObj->Account,lpObj->Name);
}
void CCommandManager::CommandResetMaster(LPOBJ lpObj)
{
		int CurrentPoint = lpObj->MasterLevel;

		lpObj->MasterPoint = CurrentPoint;

		for(int n=0;n < MAX_SKILL_LIST;n++)
		{
			lpObj->Skill[n].Clear();
		}

		for(int n=0;n < MAX_MASTER_SKILL_LIST;n++)
		{
			lpObj->MasterSkill[n].Clear();
		}

		gMasterSkillTree.GCMasterSkillListSend(lpObj->Index);

		gSkillManager.GCSkillListSend(lpObj,0);

		gObjectManager.CharacterCalcAttribute(lpObj->Index);

		gMasterSkillTree.GCMasterInfoSend(lpObj);

		gLog.Output(LOG_COMMAND,"[Command Reset MasterSkill][%s][%s]",lpObj->Account,lpObj->Name);
}

void CCommandManager::CommandChangeClass(LPOBJ lpObj,char* arg) // OK
{
    char classe[4] = {0};
    this->GetString(arg,classe,sizeof(classe),0);

	if(lpObj->Interface.use != 0 || lpObj->Teleport != 0 || lpObj->DieRegen != 0 || lpObj->PShopOpen != 0)
	{
		//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(659));
		return;
	}

    if (classe[0] == NULL){
        gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(557));
        return;
    }

	int newclasse = -1;
	int newDBclass = -1;

    if(strcmp(classe,"dw") == 0)
    {
		if(lpObj->Class == CLASS_DW)
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(558));
			return;
		}
		if(gServerInfo.m_CommandChangeClassToDW == 0)
		{
			return;
		}
		newclasse = CLASS_DW;
		newDBclass = DB_CLASS_DW;
	}

    if(strcmp(classe,"dk") == 0)
    {
		if(lpObj->Class == CLASS_DK)
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(558));
			return;
		}
		if(gServerInfo.m_CommandChangeClassToDK == 0)
		{
			return;
		}
		newclasse = CLASS_DK;
		newDBclass = DB_CLASS_DK;
	}

    if(strcmp(classe,"elf") == 0)
    {
		if(lpObj->Class == CLASS_FE)
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(558));
			return;
		}
		if(gServerInfo.m_CommandChangeClassToELF == 0)
		{
			return;
		}
		newclasse = CLASS_FE;
		newDBclass = DB_CLASS_FE;
	}

    if(strcmp(classe,"mg") == 0)
    {
		if(lpObj->Class == CLASS_MG)
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(558));
			return;
		}
		if(gServerInfo.m_CommandChangeClassToMG == 0)
		{
			return;
		}
		newclasse = CLASS_MG;
		newDBclass = DB_CLASS_MG;
	}

	if(strcmp(classe,"dl") == 0)
    {
		if(lpObj->Class == CLASS_DL)
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(558));
			return;
		}
		if(gServerInfo.m_CommandChangeClassToDL == 0)
		{
			return;
		}
		newclasse = CLASS_DL;
		newDBclass = DB_CLASS_DL;
	}

    if(strcmp(classe,"su") == 0)
    {
		if(lpObj->Class == CLASS_SU)
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(558));
			return;
		}
		if(gServerInfo.m_CommandChangeClassToSU == 0)
		{
			return;
		}
		newclasse = CLASS_SU;
		newDBclass = DB_CLASS_SU;
	}

	#if(GAMESERVER_UPDATE>=601)
		if(strcmp(classe,"rf") == 0)
		{
			if(lpObj->Class == CLASS_RF)
			{
				gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(558));
				return;
			}
		if(gServerInfo.m_CommandChangeClassToRF == 0)
		{
			return;
		}
			newclasse = CLASS_RF;
			newDBclass = DB_CLASS_RF;
		}
	#endif

	if (newclasse < 0)
	{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(557));
			return;
	}

	for(int i = 0; i < 11; i++)
	{
		if(lpObj->Inventory[i].IsItem() != 0)
		{
			gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(559));
			return;
		}
	}

	if(lpObj->Interface.use != 0)
	{
		return;
	}

		lpObj->Class        = newclasse;
		lpObj->DBClass		= newDBclass;
		lpObj->ChangeUp		= lpObj->DBClass%16;

		gObjectManager.CharacterMakePreviewCharSet(lpObj->Index);

		BYTE Class = (lpObj->ChangeUp*16);
		Class -= (Class/32);
		Class += (lpObj->Class*32);

		gQuest.GCQuestRewardSend(lpObj->Index,201,Class);
		memset(lpObj->Quest,0xFF,sizeof(lpObj->Quest));
		gQuest.GCQuestInfoSend(lpObj->Index);

		lpObj->MasterLevel = 0;
		lpObj->MasterPoint = 0;
		lpObj->MasterExperience = 0;

		for(int n=0;n < MAX_SKILL_LIST;n++)
		{
			lpObj->Skill[n].Clear();
		}

		for(int n=0;n < MAX_MASTER_SKILL_LIST;n++)
		{
			lpObj->MasterSkill[n].Clear();
		}

		gEffectManager.ClearAllEffect(lpObj);
	
	lpObj->CloseCount   = 1;
	lpObj->CloseType    = 1;

    gLog.Output(LOG_COMMAND,"[Command Change Class][%s][%s] - (ClassNum: %d)",lpObj->Account,lpObj->Name,newDBclass);

}

void CCommandManager::CommandRename(LPOBJ lpObj,char* arg) // OK
{

	if(lpObj->Interface.use != 0 || lpObj->Teleport != 0 || lpObj->DieRegen != 0 || lpObj->PShopOpen != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(500));
		return;
	}

	if(lpObj->GuildNumber > 0) //Verifica se o personagem faz parte de uma guild
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(505));
		return;
	}

	DWORD tick = (GetTickCount()-lpObj->RenameTime)/1000;

	if(tick < ((DWORD)gServerInfo.m_CommandRenameDelay[lpObj->AccountLevel]))
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(506),(gServerInfo.m_CommandRenameDelay[lpObj->AccountLevel]-tick));
		return;
	}

    if(strlen(arg) > 10)
    {
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(507));
        return;
    }

    char RenameName[11] = {0};
    this->GetString(arg,RenameName,sizeof(RenameName),0);

    if (RenameName[0] == NULL)
	{
        return;
	}

    if (strcmp(RenameName,lpObj->Name) == 0)
    {
        return;
    }

		lpObj->RenameActive = 1;
   
        SDHP_COMMAND_RENAME_SEND pMsg;

        pMsg.header.set(0x0F,0x02,sizeof(pMsg));

        pMsg.index = lpObj->Index;

        memcpy(pMsg.account,lpObj->Account,sizeof(pMsg.account));

        memcpy(pMsg.name,lpObj->Name,sizeof(pMsg.name));

        memcpy(pMsg.newname,RenameName,sizeof(pMsg.newname));

        gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

        gLog.Output(LOG_COMMAND,"[CommandRename][%s][%s] - (NewName: %s)",lpObj->Account,lpObj->Name,RenameName);
    
}

void CCommandManager::DGCommandRenameRecv(SDHP_COMMAND_RENAME_RECV* lpMsg) // OK
{
	
	if(gObjIsAccountValid(lpMsg->index,lpMsg->account) == 0)
	{
		LogAdd(LOG_RED,"[DGCommandRenameRecv] Invalid Account [%d](%s)",lpMsg->index,lpMsg->account);
		CloseClient(lpMsg->index);
		return;
	}
	
	LPOBJ lpObj = &gObj[lpMsg->index];

	if (lpMsg->result == 0)
	{
		lpObj->RenameTime = GetTickCount();

		memcpy(lpObj->Name,lpMsg->newname,sizeof(lpObj->Name));

		gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(508),lpMsg->name,lpMsg->newname);

		lpObj->RenameActive = 0;
		lpObj->CloseCount   = 1;
		lpObj->CloseType    = 1;

		LogAdd(LOG_GREEN,"[CommandRename][%s][%s] - Sucess (OldName: %s)",lpObj->Account,lpObj->Name,lpMsg->name);
		return;
	}

	if (lpMsg->result == 1)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(509));
		LogAdd(LOG_BLACK,"[CommandRename][%s][%s] - Name exists (NewName: %s)",lpObj->Account,lpObj->Name,lpMsg->newname);
		return;
	}

	if (lpMsg->result == 2)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(510));
		LogAdd(LOG_RED,"[CommandRename][%s][%s] - Error (NewName: %s)",lpObj->Account,lpObj->Name,lpMsg->newname);
		return;
	}
}

void CCommandManager::CommandBlocAcc(LPOBJ lpObj,char* arg) // OK
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(513));
		return;
	}

        SDHP_COMMAND_BLOCK_SEND pMsg;

        pMsg.header.set(0x0F,0x03,sizeof(pMsg)); 

        pMsg.index = lpObj->Index;

        memcpy(pMsg.accountbloc,lpTarget->Account,sizeof(pMsg.accountbloc));

		memcpy(pMsg.namebloc,lpTarget->Name,sizeof(pMsg.namebloc));

        gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

		gObjUserKill(lpTarget->Index);

		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(514));
		gLog.Output(LOG_COMMAND,"[CommandBlockAcc][%s][%s] - (Acc: %s)",lpObj->Account,lpObj->Name,lpTarget->Account);
}

void CCommandManager::CommandBlocChar(LPOBJ lpObj,char* arg) // OK
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(513));
		return;
	}

        SDHP_COMMAND_BLOCK_SEND pMsg;

        pMsg.header.set(0x0F,0x04,sizeof(pMsg)); 

        pMsg.index = lpObj->Index;

        memcpy(pMsg.accountbloc,lpTarget->Account,sizeof(pMsg.accountbloc));

		memcpy(pMsg.namebloc,lpTarget->Name,sizeof(pMsg.namebloc));

        gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

		gObjUserKill(lpTarget->Index);

		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(514));

		gLog.Output(LOG_COMMAND,"[CommandBlockChar][%s][%s] - (Name: %s)",lpObj->Account,lpObj->Name,lpTarget->Name);

}
void CCommandManager::CommandSecurity(LPOBJ lpObj,char* arg)
{
	int amount = this->GetNumber(arg,0);

	if(amount < 10000 || amount > 99999 )
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(560));
		return;
	}

	if(lpObj->SecurityPass == 0)
	{
		lpObj->SecurityPass = amount;
		GDSaveSecurityPass(lpObj->Index);
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(561));
		gAccSecurity.GDReqData(lpObj->Index);
	}
	else
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(562));
	}
}

void CCommandManager::CommandMarryProp(LPOBJ lpObj, char* arg)
{
	char Name[11] = {0};

	this->GetString(arg,Name,sizeof(Name),0);

	LPOBJ lpTarget = gObjFind(Name);

	if(lpTarget == 0)
	{
		return;
	}

	Marry.Propose(lpObj->Index,lpTarget->Index);
}

void CCommandManager::CommandMarryAccept(LPOBJ lpObj, char* arg)
{
	Marry.Accept(lpObj->Index);
}

void CCommandManager::CommandMarryTP(LPOBJ lpObj, char* arg)
{
	if(lpObj->IsMarried == 0)
		return;

	if(strlen(lpObj->MarryName) <= 0)
		return;

	LPOBJ lpTarget = gObjFind(lpObj->MarryName);

	if(lpTarget == 0)
	{
		return;
	}

	if(lpObj->Map != lpTarget->Map)
	{
		return;
	}

	gObjTeleport(lpObj->Index, lpTarget->Map, lpTarget->X, lpTarget->Y);
}

void CCommandManager::CommandMarryDivorce(LPOBJ lpObj, char* arg)
{
	Marry.Divorce(lpObj->Index);
}

void CCommandManager::CommandReward(LPOBJ lpObj, char* arg)
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

    if (name[0] == NULL){
        gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(563));
        return;
    }

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(564));
		return;
	}

    if (strcmp(lpTarget->Name,lpObj->Name) == 0)
    {
        gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(565));
        return;
    }

	int type  = this->GetNumber(arg,1);
	int value = this->GetNumber(arg,2);

	if(type <= 0 || value <= 0)
	{
		return;
	}

	SDHP_COMMAND_REWARD_SEND pMsg;
	pMsg.header.set(0x0F,0x05,sizeof(pMsg));
    pMsg.index = lpObj->Index;

    memcpy(pMsg.name,lpTarget->Name,sizeof(pMsg.name));
	memcpy(pMsg.account,lpTarget->Account,sizeof(pMsg.account));

    memcpy(pMsg.nameGM,lpObj->Name,sizeof(pMsg.nameGM));
	memcpy(pMsg.accountGM,lpObj->Account,sizeof(pMsg.accountGM));

	pMsg.Type  = type;
	pMsg.Value = value;

    gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

	if (type == 1) gNotice.GCNoticeSend(lpTarget->Index,0,0,0,0,0,0,gMessage.GetMessage(566),value,lpObj->Name);
	if (type == 2) gNotice.GCNoticeSend(lpTarget->Index,0,0,0,0,0,0,gMessage.GetMessage(567),value,lpObj->Name);
	if (type == 3) gNotice.GCNoticeSend(lpTarget->Index,0,0,0,0,0,0,gMessage.GetMessage(568),value,lpObj->Name);

	gLog.Output(LOG_COMMAND,"[CommandReward][%s][%s] - (Type: %d, Value: %d)",lpObj->Account,lpObj->Name,type,value);
}

void CCommandManager::CommandRewardAll(LPOBJ lpObj, char* arg)
{
	int type  = this->GetNumber(arg,0);
	int value = this->GetNumber(arg,1);

	if(type <= 0 || value <= 0)
	{
		return;
	}

    SDHP_COMMAND_REWARDALL_SEND pMsg;

    pMsg.header.set(0x0F,0x06,sizeof(pMsg));

    pMsg.index = lpObj->Index;

    memcpy(pMsg.nameGM,lpObj->Name,sizeof(pMsg.nameGM));
	memcpy(pMsg.accountGM,lpObj->Account,sizeof(pMsg.accountGM));

	pMsg.Type  = type;
	pMsg.Value = value;

    gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

	if (type == 1) gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(566),value,lpObj->Name);
	if (type == 2) gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(567),value,lpObj->Name);
	if (type == 3) gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(568),value,lpObj->Name);

	gLog.Output(LOG_COMMAND,"[CommandRewardAll][%s][%s] - (Type: %d, Value: %d)",lpObj->Account,lpObj->Name,type,value);
}

void CCommandManager::CommandMakeSet(LPOBJ lpObj,char* arg) // OK
{
	int type	= this->GetNumber(arg,0);
	int level	= this->GetNumber(arg,1);
	int skill	= this->GetNumber(arg,2);
	int luck	= this->GetNumber(arg,3);
	int option	= this->GetNumber(arg,4);
	int exc		= this->GetNumber(arg,5);
	int set		= this->GetNumber(arg,6);
	int socket	= this->GetNumber(arg,7);

	BYTE ItemSocketOption[MAX_SOCKET_OPTION] = {0xFF,0xFF,0xFF,0xFF,0xFF};
	for(int n=0;n < socket && socket <= MAX_SOCKET_OPTION;n++)
	{
			ItemSocketOption[n] = 0xFE;
	}

	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(7,type),level,0,skill,luck,option,-1,exc,set,0,0,ItemSocketOption,0xFF,0);
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(8,type),level,0,skill,luck,option,-1,exc,set,0,0,ItemSocketOption,0xFF,0);
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(9,type),level,0,skill,luck,option,-1,exc,set,0,0,ItemSocketOption,0xFF,0);
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(10,type),level,0,skill,luck,option,-1,exc,set,0,0,ItemSocketOption,0xFF,0);
	GDCreateItemSend(lpObj->Index,0xEB,0,0,GET_ITEM(11,type),level,0,skill,luck,option,-1,exc,set,0,0,ItemSocketOption,0xFF,0);

	gLog.Output(LOG_COMMAND,"[CommandMakeSet][%s][%s] - (Type: %d, Level: %d, Skill: %d, Luck: %d, Option: %d, Exc: %d, Set: %d, Sockets: %d)",lpObj->Account,lpObj->Name,type,level,skill,luck,option,exc,set, socket);
	
}

void CCommandManager::CommandDrop(LPOBJ lpObj,char* arg) // OK
{
	int section = this->GetNumber(arg,0);
	int type = this->GetNumber(arg,1);
	int level = this->GetNumber(arg,2);
	int skill = this->GetNumber(arg,3);
	int luck = this->GetNumber(arg,4);
	int option = this->GetNumber(arg,5);
	int exc = this->GetNumber(arg,6);
	int set = this->GetNumber(arg,7);
	int socket	= this->GetNumber(arg,8);

	BYTE ItemSocketOption[MAX_SOCKET_OPTION] = {0xFF,0xFF,0xFF,0xFF,0xFF};
	for(int n=0;n < socket && socket <= MAX_SOCKET_OPTION;n++)
	{
			ItemSocketOption[n] = 0xFE;
	}

	GDCreateItemSend(lpObj->Index,lpObj->Map,(BYTE)lpObj->X,(BYTE)lpObj->Y,GET_ITEM(section,type),level,0,skill,luck,option,-1,exc,set,0,0,ItemSocketOption,0xFF,0);

	gLog.Output(LOG_COMMAND,"[CommandDrop][%s][%s] - (Section: %d, Type: %d, Level: %d, Skill: %d, Luck: %d, Option: %d, Exc: %d, Set: %d, Sockets: %d)",lpObj->Account,lpObj->Name,section,type,level,skill,luck,option,exc,set,socket);
}

void CCommandManager::CommandMoveAll(LPOBJ lpObj,char* arg) // OK
{
	int iTokenNumber1 = this->GetNumber(arg,0);
	int iTokenNumber2 = this->GetNumber(arg,1);
	int iTokenNumber3 = this->GetNumber(arg,2);
	for(int iIndex=OBJECT_START_USER;iIndex<MAX_OBJECT;iIndex++)
	{
		if(gObj[iIndex].Connected == OBJECT_ONLINE )
			{
				if(iIndex != lpObj->Index)
					{
						gObjTeleport(iIndex, iTokenNumber1, iTokenNumber2, iTokenNumber3);
					}
			}
	}
	gLog.Output(LOG_COMMAND,"[CommandMoveAll][%s][%s] - MapNumber: %d X: %d Y: %d",lpObj->Account,lpObj->Name,iTokenNumber1,iTokenNumber2,iTokenNumber3);
}

void CCommandManager::CommandGMove(LPOBJ lpObj,char* arg) // OK
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

    if (name[0] == NULL){
        gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(563));
        return;
    }

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(564));
		return;
	}

    if (strcmp(lpTarget->Name,lpObj->Name) == 0)
    {
        gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(565));
        return;
    }

	lpTarget->Hornor.RankSlot1  = this->GetNumber(arg,1);

	SETTITLE_GD_SAVE_DATA pMsg;
	pMsg.header.set(0x0F,0x07,sizeof(pMsg));
    pMsg.index = lpObj->Index;
    memcpy(pMsg.Name,lpTarget->Name,sizeof(pMsg.Name));
	pMsg.RankSlot1 = lpTarget->Hornor.RankSlot1;
    gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

	gLog.Output(LOG_COMMAND,"[CommandSetTitle][%s][%s] - (Type: %d)",lpObj->Account,lpObj->Name,this->GetNumber(arg,1));
}

void CCommandManager::CommandDrawMonster(LPOBJ lpObj,char* arg) // OK
{
	int Monster	=	this->GetNumber(arg,0);
	int Map	=	this->GetNumber(arg,1);
	int X	=	this->GetNumber(arg,2);
	int Y	=	this->GetNumber(arg,3);

	if(gMap[lpObj->Map].CheckAttr(lpObj->X,lpObj->Y,1) != 0 || gMap[lpObj->Map].CheckAttr(X,Y,1) != 0)
	{
		return;
	}

	if(DS_MAP_RANGE(lpObj->Map) != 0 || BC_MAP_RANGE(lpObj->Map) != 0 || CC_MAP_RANGE(lpObj->Map) != 0 || IT_MAP_RANGE(lpObj->Map) != 0 || DA_MAP_RANGE(lpObj->Map) != 0 || DG_MAP_RANGE(lpObj->Map) != 0 || IG_MAP_RANGE(lpObj->Map) != 0)
	{
		return;
	}

	int index = gObjAddMonster(Map);

	if(OBJECT_RANGE(index) == 0)
	{
		return;
	}

	LPOBJ lpMonster = &gObj[index];

	int px = X;
	int py = Y;

	if(gObjGetRandomFreeLocation(Map,&X,&Y,3,3,50) == 0)
	{
		return;
	}

	lpMonster->PosNum = -1;
	lpMonster->X = X;
	lpMonster->Y = Y;
	lpMonster->TX = px;
	lpMonster->TY = py;
	lpMonster->OldX = px;
	lpMonster->OldY = py;
	lpMonster->StartX = px;
	lpMonster->StartY = py;
	lpMonster->Dir = 1;
	lpMonster->Map = Map;

	if(gObjSetMonster(index,Monster) == 0)
	{
		gObjDel(index);
		return;
	}
	gLog.Output(LOG_COMMAND,"[CommandDrawMonster][%s][%s] - Monster ID: %d MapNumber: %d X: %d Y: %d",lpObj->Account,lpObj->Name,Monster,Map,X,Y);
}
/*
void CCommandManager::DuelsBetSend(LPOBJ lpObj, char* arg)
{
	char Name[11] = {0};

	this->GetString(arg,Name,sizeof(Name),0);
	int BetValue = this->GetNumber(arg,1);

	LPOBJ lpTarget = gObjFind(Name);

	if(lpTarget == 0)
	{
		return;
	}

	Marry.Propose(lpObj->Index,lpTarget->Index);
}
*/

void CCommandManager::CommandSetPK(LPOBJ lpObj,char* arg) // OK
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

    if (name[0] == NULL){
        gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(563));
        return;
    }

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(564));
		return;
	}

    if (strcmp(lpTarget->Name,lpObj->Name) == 0)
    {
        gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(565));
        return;
    }

	lpTarget->PKLevel  = this->GetNumber(arg,1);
	GCPKLevelSend(lpTarget->Index,lpTarget->PKLevel);

	gLog.Output(LOG_COMMAND,"[CommandSetPK][%s][%s] - (PKLevel: %d)",lpObj->Account,lpObj->Name,this->GetNumber(arg,1));
}

void CCommandManager::CommandOnline(LPOBJ lpObj,char* arg) // OK
{
	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"Online: %d",gObjTotalUser);
}

void CCommandManager::CommandDuelBetSend(LPOBJ lpObj, char* arg)
{
	char Name[11] = {0};

	this->GetString(arg,Name,sizeof(Name),0);

	LPOBJ lpTarget = gObjFind(Name);

	if(lpTarget == 0)
	{
		return;
	}

	int Value = this->GetNumber(arg,1);

	if (Value < 1)
	{
		return;
	}

	gDuel.CGDuelBetsSend(lpObj->Index,lpTarget->Index,Value);
}

void CCommandManager::CommandDCFriend(LPOBJ lpObj,char* arg)
{

	char Account[11] = {0};

	char Password[11] = {0};

	this->GetString(arg,Account,sizeof(Account),0);
	this->GetString(arg,Password, sizeof(Password), 1);

	LPOBJ lpTarget = gObjFindByAcc(Account);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(104));
		return;
	}

	if (strcmp(lpTarget->Password,Password) != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"Password incorect!");
		return;
	}

	if (lpTarget->AttackCustomOffline != 0 || lpTarget->PShopCustomOffline != 0)
	{
		lpTarget->AttackCustomOffline = 0;
		lpTarget->PShopCustomOffline = 0;
		gObjDel(lpTarget->Index);
	}
	else
	{
		gObjUserKill(lpTarget->Index);
	}

	gLog.Output(LOG_COMMAND,"[CommandDCFriend][%s][%s] - (Account: %s Password: %s)",lpObj->Account,lpObj->Name,Account, Password);
}

void CCommandManager::CommandChatBan(LPOBJ lpObj, char* arg)
{
	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	int BanTime = this->GetNumber(arg,1);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have entered an invalid target");
		return;
	}

	lpTarget->ChatLimitTime = BanTime;

	gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "%s get %d minutes(s) of chat block", lpTarget->Name, BanTime);
	gNotice.GCNoticeSend(lpTarget->Index, 1, 0, 0, 0, 0, 0, "Your chat banned for %d minutes", BanTime);

	gLog.Output(LOG_COMMAND,"[CommandBanChat][%s][%s] - (Name: %s, BanTime: %d minutes)",lpObj->Account,lpObj->Name,name,BanTime);
}

void CCommandManager::CommandChatUnBan(LPOBJ lpObj, char* arg)
{

	char name[11] = {0};

	this->GetString(arg,name,sizeof(name),0);

	LPOBJ lpTarget = gObjFind(name);

	if(lpTarget == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"You have entered an invalid target");
		return;
	}

	lpTarget->ChatLimitTime = 0;

	gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "%s chat successfully unbanned", lpTarget->Name);
	gNotice.GCNoticeSend(lpTarget->Index, 1, 0, 0, 0, 0, 0, "Your chat unbanned");

	gLog.Output(LOG_COMMAND,"[CommandBanChat][%s][%s] - (Name: %s)",lpObj->Account,lpObj->Name,name);
}

void CCommandManager::CommandMoveGuild(LPOBJ lpObj,char* arg) // OK
{
	char name[9] = {0};

	this->GetString(arg,name,sizeof(name),0);

	int map = this->GetNumber(arg,1);

	int x = this->GetNumber(arg,2);

	int y = this->GetNumber(arg,3);

	GUILD_INFO_STRUCT * lpGuild = gGuildClass.SearchGuild(name);

	if ( lpGuild == NULL )
	{
		return;
	}

		for ( int n=0;n<MAX_GUILD_USER;n++)
		{
			int iGuildMemberIndex = lpGuild->Index[n];

			if ( lpGuild->Use[n] > 0 && iGuildMemberIndex != -1 )
			{
				LPOBJ lpObj = &gObj[iGuildMemberIndex];
				
				if ( lpObj == NULL )
				{
					continue;
				}

				if ( gObjIsConnected(iGuildMemberIndex) == 0)
				{
					continue;
				}

				gObjTeleport(iGuildMemberIndex,map,x,y);
			}
		}
	gLog.Output(LOG_COMMAND,"[CommandMoveGuild][%s][%s] - (Guild: %s, Map: %d, X: %d, Y: %d)",lpObj->Account,lpObj->Name,name,map,x,y);
}
