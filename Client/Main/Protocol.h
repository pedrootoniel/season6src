#pragma once

#define SET_NUMBERHB(x) ((BYTE)((DWORD)(x)>>(DWORD)8))
#define SET_NUMBERLB(x) ((BYTE)((DWORD)(x)&0xFF))
#define SET_NUMBERHW(x) ((WORD)((DWORD)(x)>>(DWORD)16))
#define SET_NUMBERLW(x) ((WORD)((DWORD)(x)&0xFFFF))
#define SET_NUMBERHDW(x) ((DWORD)((QWORD)(x)>>(QWORD)32))
#define SET_NUMBERLDW(x) ((DWORD)((QWORD)(x)&0xFFFFFFFF))

#define MAKE_NUMBERW(x,y) ((WORD)(((BYTE)((y)&0xFF))|((BYTE)((x)&0xFF)<<8)))
#define MAKE_NUMBERDW(x,y) ((DWORD)(((WORD)((y)&0xFFFF))|((WORD)((x)&0xFFFF)<<16)))
#define MAKE_NUMBERQW(x,y) ((QWORD)(((DWORD)((y)&0xFFFFFFFF))|((DWORD)((x)&0xFFFFFFFF)<<32)))
#define LODWORD(h)				((DWORD)(__int64(h) & __int64(0xffffffff)))   
#define HIDWORD(h)				((DWORD)(__int64(h) >> __int64(32)))
#include "Defines.h"
//**********************************************//
//************ Packet Base *********************//
//**********************************************//


/////////////////////////////////////
struct PBMSG_HEAD
{
	void set(BYTE head,BYTE size) // OK
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
	}

	void setE(BYTE head,BYTE size) // OK
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
	}

	BYTE type;
	BYTE size;
	BYTE head;
};

struct PSBMSG_HEAD
{
	void set(BYTE head,BYTE subh,BYTE size) // OK
	{
		this->type = 0xC1;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head,BYTE subh,BYTE size) // OK
	{
		this->type = 0xC3;
		this->size = size;
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size;
	BYTE head;
	BYTE subh;
};

struct PWMSG_HEAD
{
	void set(BYTE head,WORD size) // OK
	{
		this->type = 0xC2;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
	}

	void setE(BYTE head,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
};

struct PSWMSG_HEAD
{
	void set(BYTE head,BYTE subh,WORD size) // OK
	{
		this->type = 0xC2;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head,BYTE subh,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = HIBYTE(size);
		this->size[1] = LOBYTE(size);
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
	BYTE subh;
};

//**********************************************//
//************ GameServer -> Client ************//
//**********************************************//
struct PMSG_DAMAGE_RECV
{
	PBMSG_HEAD header; // C1:11
	BYTE index[2];
	BYTE damage[2];
	BYTE type;
	BYTE ShieldDamage[2];
	//EXTRA
	DWORD ViewCurHP;
	DWORD ViewCurSD;
	DWORD ViewDamageHP;
	DWORD ViewDamageSD;
};

struct PMSG_VIEWPORT_DESTROY_RECV
{
	PBMSG_HEAD header; // C1:14
	BYTE count;
};

struct PMSG_VIEWPORT_DESTROY
{
	BYTE index[2];
};

struct PMSG_MONSTER_DIE_RECV
{
	PBMSG_HEAD header; // C1:16
	BYTE index[2];
	BYTE experience[2];
	BYTE damage[2];
	//EXTRA
	DWORD ViewDamageHP;
};

struct PMSG_USER_DIE_RECV
{
	PBMSG_HEAD header; // C1:17
	BYTE index[2];
	BYTE skill[2];
	BYTE killer[2];
};

struct PMSG_LIFE_RECV
{
	PBMSG_HEAD header; // C1:26
	BYTE type;
	BYTE life[2];
	BYTE flag;
	BYTE shield[2];
	//EXTRA
	DWORD ViewHP;
	DWORD ViewSD;
};

struct PMSG_MANA_RECV
{
	PBMSG_HEAD header; // C1:27
	BYTE type;
	BYTE mana[2];
	BYTE bp[2];
	//EXTRA
	DWORD ViewMP;
	DWORD ViewBP;
};

struct PMSG_FRUIT_RESULT_RECV
{
	PBMSG_HEAD header; // C1:2C
	BYTE result;
	WORD value;
	BYTE type;
	//EXTRA
	DWORD ViewValue;
	DWORD ViewPoint;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_REWARD_EXPERIENCE_RECV
{
	PBMSG_HEAD header; // C1:9C
	BYTE index[2];
	WORD experience[2];
	BYTE damage[2];
	//EXTRA
	DWORD ViewDamageHP;
};

struct PMSG_QUEST_REWARD_RECV
{
	PBMSG_HEAD header; // C1:A3
	BYTE index[2];
	BYTE QuestReward;
	BYTE QuestAmount;
	//EXTRA
	DWORD ViewPoint;
};

struct PMSG_MAP_SERVER_MOVE_RECV
{
	PSBMSG_HEAD header; // C1:B1:00
	char IpAddress[16];
	WORD ServerPort;
	WORD ServerCode;
	DWORD AuthCode1;
	DWORD AuthCode2;
	DWORD AuthCode3;
	DWORD AuthCode4;
};

struct PMSG_MAP_SERVER_MOVE_AUTH_RECV
{
	PSBMSG_HEAD header; // C1:B1:01
	BYTE result;
};

struct PMSG_CONNECT_CLIENT_RECV
{
	PSBMSG_HEAD header; // C1:F1:00
	BYTE result;
	BYTE index[2];
	BYTE ClientVersion[5];
};

struct PMSG_CONNECT_ACCOUNT_RECV
{
	PSBMSG_HEAD header; // C1:F1:01
	BYTE result;
};

struct PMSG_CLOSE_CLIENT_RECV
{
	PSBMSG_HEAD header; // C1:F1:02
	BYTE result;
};

struct PMSG_CHARACTER_LIST_RECV
{
	PSBMSG_HEAD header; // C1:F3:00
	BYTE ClassCode;
	BYTE MoveCnt;
	BYTE count;
	BYTE ExtWarehouse;
};

struct PMSG_CHARACTER_INFO_RECV
{
	PSBMSG_HEAD header; // C3:F3:03
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	BYTE Experience[8];
	BYTE NextExperience[8];
	WORD LevelUpPoint;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	WORD Shield;
	WORD MaxShield;
	WORD BP;
	WORD MaxBP;
	DWORD Money;
	BYTE PKLevel;
	BYTE CtlCode;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD Leadership;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	BYTE ExtInventory;
	//EXTRA
	DWORD ViewReset;
	DWORD ViewAccountLevel;
	DWORD ViewPoint;
	DWORD ViewCurHP;
	DWORD ViewMaxHP;
	DWORD ViewCurMP;
	DWORD ViewMaxMP;
	DWORD ViewCurBP;
	DWORD ViewMaxBP;
	DWORD ViewCurSD;
	DWORD ViewMaxSD;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_CHARACTER_REGEN_RECV
{
	PSBMSG_HEAD header; // C3:F3:04
	BYTE X;
	BYTE Y;
	BYTE Map;
	BYTE Dir;
	WORD Life;
	WORD Mana;
	WORD Shield;
	WORD BP;
	BYTE Experience[8];
	DWORD Money;
	//EXTRA
	DWORD ViewCurHP;
	DWORD ViewCurMP;
	DWORD ViewCurBP;
	DWORD ViewCurSD;
};

struct PMSG_LEVEL_UP_RECV
{
	PSBMSG_HEAD header; // C1:F3:05
	WORD Level;
	WORD LevelUpPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
	WORD MaxBP;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	//EXTRA
	DWORD ViewPoint;
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
	DWORD ViewExperience;
	DWORD ViewNextExperience;
};

struct PMSG_LEVEL_UP_POINT_RECV
{
	PSBMSG_HEAD header; // C1:F3:06
	BYTE result;
	WORD MaxLifeAndMana;
	WORD MaxShield;
	WORD MaxBP;
	//EXTRA
	DWORD ViewPoint;
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_MONSTER_DAMAGE_RECV
{
	PSBMSG_HEAD header; // C1:F3:07
	BYTE damage[2];
	BYTE ShieldDamage[2];
	//EXTRA
	DWORD ViewCurHP;
	DWORD ViewCurSD;
	DWORD ViewDamageHP;
	DWORD ViewDamageSD;
};

struct PMSG_MASTER_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F3:50
	WORD MasterLevel;
	BYTE Experience[8];
	BYTE NextExperience[8];
	WORD MasterPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
	WORD MaxBP;
	//EXTRA
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
};

struct PMSG_MASTER_LEVEL_UP_RECV
{
	PSBMSG_HEAD header; // C1:F3:51
	WORD MasterLevel;
	WORD MinMasterLevel;
	WORD MasterPoint;
	WORD MaxMasterLevel;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
	WORD MaxBP;
	//EXTRA
	DWORD ViewMaxHP;
	DWORD ViewMaxMP;
	DWORD ViewMaxBP;
	DWORD ViewMaxSD;
	QWORD ViewMasterExperience;
	QWORD ViewMasterNextExperience;
};

struct PMSG_NEW_CHARACTER_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F3:E0
	WORD Level;
	WORD LevelUpPoint;
	DWORD Experience;
	DWORD NextExperience;
	WORD Strength;
	WORD Dexterity;
	WORD Vitality;
	WORD Energy;
	WORD Leadership;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	WORD BP;
	WORD MaxBP;
	WORD Shield;
	WORD MaxShield;
	WORD FruitAddPoint;
	WORD MaxFruitAddPoint;
	WORD FruitSubPoint;
	WORD MaxFruitSubPoint;
	//EXTRA
	DWORD ViewReset;
	DWORD ViewAccountLevel;
	DWORD ViewPoint;
	DWORD ViewCurHP;
	DWORD ViewMaxHP;
	DWORD ViewCurMP;
	DWORD ViewMaxMP;
	DWORD ViewCurBP;
	DWORD ViewMaxBP;
	DWORD ViewCurSD;
	DWORD ViewMaxSD;
	DWORD ViewStrength;
	DWORD ViewDexterity;
	DWORD ViewVitality;
	DWORD ViewEnergy;
	DWORD ViewLeadership;
};

struct PMSG_NEW_CHARACTER_CALC_RECV
{
	PSBMSG_HEAD header; // C1:F3:E1
	DWORD ViewCurHP;
	DWORD ViewMaxHP;
	DWORD ViewCurMP;
	DWORD ViewMaxMP;
	DWORD ViewCurBP;
	DWORD ViewMaxBP;
	DWORD ViewCurSD;
	DWORD ViewMaxSD;
	DWORD ViewAddStrength;
	DWORD ViewAddDexterity;
	DWORD ViewAddVitality;
	DWORD ViewAddEnergy;
	DWORD ViewAddLeadership;
	DWORD ViewPhysiDamageMin;
	DWORD ViewPhysiDamageMax;
	DWORD ViewMagicDamageMin;
	DWORD ViewMagicDamageMax;
	DWORD ViewCurseDamageMin;
	DWORD ViewCurseDamageMax;
	DWORD ViewMulPhysiDamage;
	DWORD ViewDivPhysiDamage;
	DWORD ViewMulMagicDamage;
	DWORD ViewDivMagicDamage;
	DWORD ViewMulCurseDamage;
	DWORD ViewDivCurseDamage;
	DWORD ViewMagicDamageRate;
	DWORD ViewCurseDamageRate;
	DWORD ViewPhysiSpeed;
	DWORD ViewMagicSpeed;
	DWORD ViewAttackSuccessRate;
	DWORD ViewAttackSuccessRatePvP;
	DWORD ViewDefense;
	DWORD ViewDefenseSuccessRate;
	DWORD ViewDefenseSuccessRatePvP;
	DWORD ViewDamageMultiplier;
	DWORD ViewRFDamageMultiplierA;
	DWORD ViewRFDamageMultiplierB;
	DWORD ViewRFDamageMultiplierC;
	DWORD ViewDarkSpiritAttackDamageMin;
	DWORD ViewDarkSpiritAttackDamageMax;
	DWORD ViewDarkSpiritAttackSpeed;
	DWORD ViewDarkSpiritAttackSuccessRate;
};
/*
struct PMSG_NEW_HEALTH_BAR_RECV
{
	PSWMSG_HEAD header; // C2:F3:E2
	BYTE count;
};

struct PMSG_NEW_HEALTH_RECV
{
	WORD index;
	BYTE type;
	BYTE rate;
};
*/
struct PMSG_NEW_GENS_BATTLE_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F3:E3
	BYTE GensBattleMapCount;
	BYTE GensMoveIndexCount;
	BYTE GensBattleMap[120];
	BYTE GensMoveIndex[120];
};

struct PMSG_NEW_MESSAGE_RECV
{
	PSBMSG_HEAD header; // C1:F3:E4
	char message[128];
};

struct PMSG_ARENA_STATUS_RECV
{
	PSBMSG_HEAD header; // C1:FB:11
	BYTE result;
};

//**********************************************//
//************ Client -> GameServer ************//
//**********************************************//

struct PMSG_INVENTORYITEMMOVE
{
	PBMSG_HEAD h;
	BYTE sFlag;	// 3
	BYTE source_item_num;	// 4
	BYTE sItemInfo[12];	// 5
	BYTE tFlag;	// 0x11
	BYTE target_item_num;	// 0x12
};

struct PMSG_HELPER_START_SEND
{
	PSBMSG_HEAD header; // C1:BF:51
	BYTE type;
};

struct PMSG_PET_ITEM_COMMAND_SEND
{
	PBMSG_HEAD header; // C1:A7
	BYTE type;
	BYTE command;
	BYTE index[2];
};

struct PMSG_CONNECT_ACCOUNT_SEND
{
	#pragma pack(1)
	PSBMSG_HEAD header; // C3:F1:01
	char account[10];
	char password[20];
	DWORD TickCount;
	BYTE ClientVersion[5];
	BYTE ClientSerial[16];
	#pragma pack()
};

struct PMSG_CHARACTER_LIST_SEND
{
	PSBMSG_HEAD header; // C1:F3:00
};

struct PMSG_CHARACTER_INFO_SEND
{
	PSBMSG_HEAD header; // C1:F3:03
	char name[10];
};

struct PMSG_NEW_EVENT_BUTTON_SEND
{
	PSBMSG_HEAD header; // C1:FB:11
	BYTE Event;
};
//---------------------------------------------------------------------------------------------
//->Test
struct PMSG_CHARACTER_COMMAND_SEND
{
	PSBMSG_HEAD header; // C1:FB:01
};
struct PMSG_HEADSTAILS_SEND
{
	PSBMSG_HEAD header; // C1:FB:01
	int	Type;
	float	Money;
};
struct PMSG_NEW_EXTRA_PANEL_SEND
{
	PSBMSG_HEAD header; // C1:FB:10
	BYTE state;
};
struct ROLL_DICE_REQ
{
	PBMSG_HEAD header;
	int	Type; // 
	int	Number; // 
	float	Money; // 
};
struct DICE_UPDATEINFO
{
	PSBMSG_HEAD header; // C1:F3:E3
	int	Dice1;
	int	Dice2;
	int	TotalPoint;
	int	LastProfit;
	int	WCoinC;
	int	Winner;
};
struct HEADSTAILS_UPDATEINFO
{
	PSBMSG_HEAD header; // C1:F3:E3
	int	Winer;
	int	WinerPrice;
	int	WCoinC;
	//int	HeadsTails;
};
struct LUCKYNUMBER_UPDATEINFO
{
	PSBMSG_HEAD header; // C1:F3:E3
	int	WinnerPrice;
	int	LuckyNumber;
	int	Number[5];
	int	TicketID;
};
struct PBMSG_HEAD2
{
public:
	void set( LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};

	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct PWMSG_HEAD2
{
public:
	void set(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERHB(size);
		lpBuf[2] = SET_NUMBERLB(size);
		lpBuf[3] = head;
		lpBuf[4] = sub;
	}

	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
	BYTE subcode;
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct PMSG_DEFAULT2
{
	PBMSG_HEAD header;
	BYTE subcode;
};
#pragma pack(pop)
// ---------------------------------------------------------------------------------

struct PBMSG_CHATPOSTITEM {
    PBMSG_HEAD h;
    char character_[10];  //  3
    char message_[89];  //  D
};


struct PMSG_POSTITEM {
    PBMSG_HEAD h;
    char chatid[10];    //  3
    char chatmsg[60];   //  D
    char item_data[107];
};

struct PMSG_NEW_HEALTH_BAR_RECV
{
	PSWMSG_HEAD header; // C2:F3:E2
	BYTE count;
};

struct PMSG_NEW_HEALTH_RECV
{
	WORD index;
	BYTE type;
	BYTE rate;
	WORD monsterid;
	float Life;
	float MaxLife;
	short Level;
	int Shield;
	int MaxShield;
	BYTE SDrate;
	bool isSameGuild;
	int RankTitle;
	//bool HaveGuild;
	//char GuildName[9];
	//BYTE Mark[64];
};

struct PMSG_RECV_PARTYLIST
{
	PSWMSG_HEAD header;
	int Count;
};

struct PMSG_PARTYSEARCH_PARTYLIST
{
	char Name[11];
	int Map;
	int X;
	int Y;
	int Level;
	bool DarkWizard;
	bool DarkKnight;
	bool Elf;
	bool MagicGladiator;
	bool DarkLord;
	bool Summoner;
	bool RageFighter;
	bool OnlyGuild;
	bool IsSameGuild;
	int Count;
};

struct EXTRA_CPANEL_SENDINFO
{
	PSBMSG_HEAD h;	// C1:01
	BYTE Settings;
	BYTE RolltheDice;
	BYTE HeadsTails;
	BYTE LuckyNumber;
	BYTE SmithItem;
	BYTE TitleManager;
	BYTE PartySearchSetting;
	BYTE OffAttack;
	BYTE BuyVip;
	BYTE ChangeClass;
	BYTE ResetPoint;
	BYTE ResetPoint2;
	BYTE ResetMasterSkill;
	BYTE ResetMasterSkill2;
	BYTE AccountSecurity;
	BYTE JewelsBank;
	BYTE Rename;
	BYTE TopPlayer;
	BYTE PShopCurrency;
	BYTE PShopOffStore;
	BYTE RPSMode;
	BYTE NewsBoard;
	BYTE FruitMain;
	BYTE LuckySpinMain;
	BYTE GiftCode;
	BYTE PSBless;
	BYTE PSSoul;
	BYTE PSChaos;
	BYTE PSWcoinC;
	BYTE PSWcoinP;
	BYTE PSWcoinG;
	BYTE QuickAdd;
	BYTE ResetStat;
	BYTE EventTimer;
	BYTE CustomWare;
	BYTE PartyLeader;
	BYTE PartyTrace;
	BYTE TitleBarSwitch;
	BYTE PlayerHPBarSwitch;
	BYTE SDByPass;
	int	dStrength;
	int	dDexterity;
	int	dVitality;
	int	dEnergy;
	int	dLeadership;
	int CustomResetPointPriceWC[MAX_ACCOUNT_LEVEL];
	int CustomResetPointPriceZen[MAX_ACCOUNT_LEVEL];
	int CustomMasterSkillPriceWC[MAX_ACCOUNT_LEVEL];
	int CustomMasterSkillPriceZen[MAX_ACCOUNT_LEVEL];
	int MaxStatPoint[MAX_ACCOUNT_LEVEL];
	int MaxWarehouse;
};

struct GC_PARTYNEWLEADER
{
	PSBMSG_HEAD h;
	BYTE id;
};

struct PMSG_SMITHY_ANCIENT_RECV
{
	PSWMSG_HEAD header;
	BYTE count;
};

struct PMSG_SMITHY_ANCIENT
{
	int index;
	BYTE options[2];
};

struct PMSG_SMITHY_SOCKET_RECV
{
	PSWMSG_HEAD header;
	BYTE count;
};

struct PMSG_SMITHY_SOCKET
{
	int index;
};

struct PMSG_UPDATE_STATS_SEND
{
	PSBMSG_HEAD header;
	int Str;
	int Agi;
	int Vit;
	int Ene;
	int Com;
};

struct PMSG_RESET_STATS_SEND
{
	PSBMSG_HEAD header;
	int Type;
};

struct PMSG_BALANCE_UPDATE_RECV
{
	PSBMSG_HEAD header;
	DWORD	wCoinC;
	DWORD	wCoinP;
	DWORD	GoblinPoint;
};

struct PMSG_ACCOUNT_SECURITY_RECV
{
	PSBMSG_HEAD header;
	BYTE TradeLock;
	BYTE InventoryLock;
	BYTE WareLock;
	BYTE ShopLock;
	BYTE PShopLock;
	BYTE ChaosMixLock;
	BYTE DelCharLock;
};

struct PMSG_ACCOUNT_SECURITY_SEND
{
	PSBMSG_HEAD header;
	BYTE TradeLock;
	BYTE InventoryLock;
	BYTE WareLock;
	BYTE ShopLock;
	BYTE PShopLock;
	BYTE ChaosMixLock;
	BYTE DelCharLock;
};

struct USERBUTTON_REQ
{
	PSBMSG_HEAD	Head;
};

struct PMSG_SECURITY_PW_SEND
{
	PSBMSG_HEAD header;
	int SecretNumber;
};

struct PMSG_RENAME_SEND
{
	PSBMSG_HEAD header;
	char Name[11];
};

struct PMSG_GIFTCODE_SEND
{
	PSBMSG_HEAD header;
	int ID;
};

struct PMSG_REQ_MULTI_CHAR_SEND
{
	PSBMSG_HEAD header;
	int Page;
};

struct PMSG_CHARACTERPAGE_RECV
{
	PSBMSG_HEAD	header;
	int Page;
};

struct PMSG_JEWELSBANK_SEND
{
	PSBMSG_HEAD header;
	int Type;
	int	Count;
};

struct PMSG_BANKEX_UPDATE_RECV
{
	PSBMSG_HEAD header;
	long	Bless;
	long	Soul;
	long	Chaos;
	long	Creation;
	long	Life;
	long	Harmony;
};

struct RPSMODE_REQ
{
	PSBMSG_HEAD h;
	int			Number;
};

struct PMSG_SEND_CRC{
	PSBMSG_HEAD h;
	DWORD CheckTime;
};

struct PMSG_FRUIT_UPDATE_RECV
{
	PSBMSG_HEAD header;
	int	Strength;
	int	Dexterity;
	int	Vitality;
	int	Energy;
	int	Leadership;
	int MaxPoint;
};

struct PSSHOP_INTERFACE
{
	PSBMSG_HEAD header;
	int result;
};

struct PMSG_CHANGEWAREHOUSE_RECV
{
	PSBMSG_HEAD header;
	int Number;
};

struct PMSG_SERVERTIME_RECV
{
	PSBMSG_HEAD	Head;
	// ----
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int seconds;
};

//**********************************************//
//**********************************************//
//**********************************************//

BOOL ProtocolCoreEx(BYTE head,BYTE* lpMsg,int size,int key);
void GCDamageRecv(PMSG_DAMAGE_RECV* lpMsg);
void GCMonsterDieRecv(PMSG_MONSTER_DIE_RECV* lpMsg);
void GCUserDieRecv(PMSG_USER_DIE_RECV* lpMsg);
void GCLifeRecv(PMSG_LIFE_RECV* lpMsg);
void GCManaRecv(PMSG_MANA_RECV* lpMsg);
void GCFruitResultRecv(PMSG_FRUIT_RESULT_RECV* lpMsg);
void GCRewardExperienceRecv(PMSG_REWARD_EXPERIENCE_RECV* lpMsg);
void GCQuestRewardRecv(PMSG_QUEST_REWARD_RECV* lpMsg);
void GCMapServerMoveRecv(PMSG_MAP_SERVER_MOVE_RECV* lpMsg);
void GCMapServerMoveAuthRecv(PMSG_MAP_SERVER_MOVE_AUTH_RECV* lpMsg);
void GCConnectClientRecv(PMSG_CONNECT_CLIENT_RECV* lpMsg);
void GCConnectAccountRecv(PMSG_CONNECT_ACCOUNT_RECV* lpMsg);
void GCCloseClientRecv(PMSG_CLOSE_CLIENT_RECV* lpMsg);
void GCCharacterListRecv(PMSG_CHARACTER_LIST_RECV* lpMsg);
void GCCharacterInfoRecv(PMSG_CHARACTER_INFO_RECV* lpMsg);
void GCCharacterRegenRecv(PMSG_CHARACTER_REGEN_RECV* lpMsg);
void GCLevelUpRecv(PMSG_LEVEL_UP_RECV* lpMsg);
void GCLevelUpPointRecv(PMSG_LEVEL_UP_POINT_RECV* lpMsg);
void GCMonsterDamageRecv(PMSG_MONSTER_DAMAGE_RECV* lpMsg);
void GCMasterInfoRecv(PMSG_MASTER_INFO_RECV* lpMsg);
void GCMasterLevelUpRecv(PMSG_MASTER_LEVEL_UP_RECV* lpMsg);
void GCNewCharacterInfoRecv(PMSG_NEW_CHARACTER_INFO_RECV* lpMsg);
void GCNewCharacterCalcRecv(PMSG_NEW_CHARACTER_CALC_RECV* lpMsg);
void GCNewHealthBarRecv(PMSG_NEW_HEALTH_BAR_RECV* lpMsg);
void GCNewGensBattleInfoRecv(PMSG_NEW_GENS_BATTLE_INFO_RECV* lpMsg);
void GCNewMessageRecv(PMSG_NEW_MESSAGE_RECV* lpMsg);
void GCEventStatusRecv(PMSG_ARENA_STATUS_RECV* lpMsg);
void StartRoll(int Type, int Number, float Money);
void StartFlip(int Type, float Money);
void StartLucky(int Lines);
void RolltheDiceData(DICE_UPDATEINFO * aRecv);
void HeadsTailsData(HEADSTAILS_UPDATEINFO * aRecv);
void LuckyNumberData(LUCKYNUMBER_UPDATEINFO * aRecv);
bool RecvPostItem(PMSG_POSTITEM* lpMsg);
void GCPartyListRecv(PMSG_RECV_PARTYLIST* lpMsg);
void ExtraCpanelGetInfo(EXTRA_CPANEL_SENDINFO * lpMsg);
void GCSmithyAncRecv(PMSG_SMITHY_ANCIENT_RECV* lpMsg);
void GCSmithySocketRecv(PMSG_SMITHY_SOCKET_RECV* lpMsg);
void CGSendStatsAdd(PMSG_UPDATE_STATS_SEND pMsg);
void CGSendResetStats(int type);
void GCBalanceRecv(PMSG_BALANCE_UPDATE_RECV* lpMsg);
void GCAccountSecurityRecv(PMSG_ACCOUNT_SECURITY_RECV* lpMsg);
void GCAccountSecuritySave();
void CGSendMultiChar(int Page);
void GCSetCharacterPage(PMSG_CHARACTERPAGE_RECV* lpMsg);
void CGSendDepositJewels(int type,int count);
void CGSendWithdrawJewels(int type,int count);
void GCJewelsBankRecv(PMSG_BANKEX_UPDATE_RECV* lpMsg);
void GCFruitRecv(PMSG_FRUIT_UPDATE_RECV* lpMsg);
void RPSMode(int Number);
void UpdateRPSMode();
void CGSendFilesCrc();
void UpdatePShop(PSSHOP_INTERFACE* lpMsg);
void LuckySpinRoll();
void OpenCustomWare();
void RecvServerTime(PMSG_SERVERTIME_RECV* Data);
void DataSend(BYTE* lpMsg,DWORD size);