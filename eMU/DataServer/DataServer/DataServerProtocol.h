#pragma once
#if(DATASERVER_UPDATE>=701)
#define INVENTORY_SIZE 237
#elif(DATASERVER_UPDATE>=602)
#define INVENTORY_SIZE 236
#else
#define INVENTORY_SIZE 108
#endif
#if(DATASERVER_UPDATE>=701)
#define MAX_EFFECT_LIST 32
#else
#define MAX_EFFECT_LIST 16
#endif
#if(DATASERVER_UPDATE>=701)
#define MAX_SKILL_LIST 60
#else
#define MAX_SKILL_LIST 60
#endif
#define SET_NUMBERHB(x) ((BYTE)((DWORD)(x)>>(DWORD)8))
#define SET_NUMBERLB(x) ((BYTE)((DWORD)(x)&0xFF))
#define SET_NUMBERHW(x) ((WORD)((DWORD)(x)>>(DWORD)16))
#define SET_NUMBERLW(x) ((WORD)((DWORD)(x)&0xFFFF))
#define SET_NUMBERHDW(x) ((DWORD)((QWORD)(x)>>(QWORD)32))
#define SET_NUMBERLDW(x) ((DWORD)((QWORD)(x)&0xFFFFFFFF))

#define MAKE_NUMBERW(x,y) ((WORD)(((BYTE)((y)&0xFF))|((BYTE)((x)&0xFF)<<8)))
#define MAKE_NUMBERDW(x,y) ((DWORD)(((WORD)((y)&0xFFFF))|((WORD)((x)&0xFFFF)<<16)))
#define MAKE_NUMBERQW(x,y) ((QWORD)(((DWORD)((y)&0xFFFFFFFF))|((DWORD)((x)&0xFFFFFFFF)<<32)))

//**********************************************//
//************ Packet Base *********************//
//**********************************************//

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
		this->size[0] = SET_NUMBERHB(size);
		this->size[1] = SET_NUMBERLB(size);
		this->head = head;
	}

	void setE(BYTE head,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = SET_NUMBERHB(size);
		this->size[1] = SET_NUMBERLB(size);
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
		this->size[0] = SET_NUMBERHB(size);
		this->size[1] = SET_NUMBERLB(size);
		this->head = head;
		this->subh = subh;
	}

	void setE(BYTE head,BYTE subh,WORD size) // OK
	{
		this->type = 0xC4;
		this->size[0] = SET_NUMBERHB(size);
		this->size[1] = SET_NUMBERLB(size);
		this->head = head;
		this->subh = subh;
	}

	BYTE type;
	BYTE size[2];
	BYTE head;
	BYTE subh;
};

//**********************************************//
//********** GameServer -> DataServer **********//
//**********************************************//


struct SDHP_SERVER_INFO_RECV
{
	PBMSG_HEAD header; // C1:00
	BYTE type;
	WORD ServerPort;
	char ServerName[50];
	WORD ServerCode;
};

struct SDHP_CHARACTER_LIST_RECV
{
	PBMSG_HEAD header; // C1:01
	WORD index;
	char account[11];
};

struct SDHP_CHARACTER_LIST_MULTI_RECV
{
	PBMSG_HEAD header; // C1:01
	WORD index;
	char account[11];
	int Page;
};

struct SDHP_CHARACTER_CREATE_RECV
{
	PBMSG_HEAD header; // C1:02
	WORD index;
	char account[11];
	char name[11];
	BYTE Class;
};

struct SDHP_CHARACTER_DELETE_RECV
{
	PBMSG_HEAD header; // C1:03
	WORD index;
	char account[11];
	char name[11];
	BYTE guild;
	char GuildName[9];
};

struct SDHP_CHARACTER_INFO_RECV
{
	PBMSG_HEAD header; // C1:04
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_CREATE_ITEM_RECV
{
	PBMSG_HEAD header; // C1:07
	WORD index;
	char account[11];
	BYTE X;
	BYTE Y;
	BYTE Map;
	WORD ItemIndex;
	BYTE Level;
	BYTE Dur;
	BYTE Option1;
	BYTE Option2;
	BYTE Option3;
	BYTE NewOption;
	WORD LootIndex;
	BYTE SetOption;
	BYTE JewelOfHarmonyOption;
	BYTE ItemOptionEx;
	BYTE SocketOption[5];
	BYTE SocketOptionBonus;
	DWORD Duration;
};

struct SDHP_OPTION_DATA_RECV
{
	PBMSG_HEAD header; // C1:08
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_PET_ITEM_INFO_RECV
{
	PWMSG_HEAD header; // C2:09
	WORD index;
	char account[11];
	BYTE type;
	BYTE count;
};

struct SDHP_PET_ITEM_INFO1
{
	BYTE slot;
	DWORD serial;
};

struct SDHP_CHARACTER_NAME_CHECK_RECV
{
	PBMSG_HEAD header; // C1:0A
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_CHARACTER_NAME_CHANGE_RECV
{
	PBMSG_HEAD header; // C1:0B
	WORD index;
	char account[11];
	char OldName[11];
	char NewName[11];
};

struct SDHP_CRYWOLF_SYNC_RECV
{
	PBMSG_HEAD header; // C1:1E
	WORD MapServerGroup;
	DWORD CrywolfState;
	DWORD OccupationState;
};

struct SDHP_CRYWOLF_INFO_RECV
{
	PBMSG_HEAD header; // C1:1F
	WORD MapServerGroup;
};

struct SDHP_GLOBAL_POST_RECV
{
	PBMSG_HEAD header; // C1:20
	WORD MapServerGroup;
	BYTE type;
	char name[11];
	char message[60];
};

struct SDHP_GLOBAL_ITEM_POST_RECV
{
	PBMSG_HEAD header; // C1:78
	WORD MapServerGroup;
	char name[11];
    char message[60];
    char item_data[107];
};

struct SDHP_GLOBAL_NOTICE_RECV
{
	PBMSG_HEAD header; // C1:21
	WORD MapServerGroup;
	BYTE type;
	BYTE count;
	BYTE opacity;
	WORD delay;
	DWORD color;
	BYTE speed;
	char message[128];
};

struct SDHP_SNS_DATA_RECV
{
	PBMSG_HEAD header; // C1:24
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_CHARACTER_INFO_SAVE_RECV
{
	PWMSG_HEAD header; // C2:30
	WORD index;
	char account[11];
	char name[11];
	WORD Level;
	BYTE Class;
	DWORD LevelUpPoint;
	DWORD Experience;
	DWORD Money;
	DWORD Strength;
	DWORD Dexterity;
	DWORD Vitality;
	DWORD Energy;
	DWORD Leadership;
	DWORD Life;
	DWORD MaxLife;
	DWORD Mana;
	DWORD MaxMana;
	DWORD BP;
	DWORD MaxBP;
	DWORD Shield;
	DWORD MaxShield;
	BYTE Inventory[INVENTORY_SIZE][16];
	BYTE Skill[MAX_SKILL_LIST][3];
	BYTE Map;
	BYTE X;
	BYTE Y;
	BYTE Dir;
	DWORD PKCount;
	DWORD PKLevel;
	DWORD PKTime;
	BYTE Quest[50];
	WORD FruitAddPoint;
	WORD FruitSubPoint;
	BYTE Effect[MAX_EFFECT_LIST][13];
	#if(DATASERVER_UPDATE>=602)
	BYTE ExtInventory;
	BYTE ExtWarehouse;
	#endif
	BYTE IsMarried;
	char MarryName[11];
	int iQuestIndex;
	int iQuestState;
	int iQuestVar;
	int iQuestStat;
	WORD ChatLimitTime;
};

struct SDHP_INVENTORY_ITEM_SAVE_RECV
{
	PWMSG_HEAD header; // C2:31
	WORD index;
	char account[11];
	char name[11];
	BYTE Inventory[INVENTORY_SIZE][16];
};

struct SDHP_OPTION_DATA_SAVE_RECV
{
	PBMSG_HEAD header; // C1:33
	WORD index;
	char account[11];
	char name[11];
	BYTE SkillKey[20];
	BYTE GameOption;
	BYTE QKey;
	BYTE WKey;
	BYTE EKey;
	BYTE ChatWindow;
	BYTE RKey;
	DWORD QWERLevel;
	#if(DATASERVER_UPDATE>=701)
	BYTE ChangeSkin;
	#endif
};

struct SDHP_PET_ITEM_INFO_SAVE_RECV
{
	PWMSG_HEAD header; // C2:34
	WORD index;
	char account[11];
	BYTE count;
};

struct SDHP_PET_ITEM_INFO_SAVE
{
	DWORD serial;
	BYTE level;
	DWORD experience;
};

struct SDHP_RESET_INFO_SAVE_RECV
{
	PBMSG_HEAD header; // C1:39
	WORD index;
	char account[11];
	char name[11];
	UINT Reset;
	UINT ResetDay;
	UINT ResetWek;
	UINT ResetMon;
};

struct SDHP_MASTER_RESET_INFO_SAVE_RECV
{
	PBMSG_HEAD header; // C1:3A
	WORD index;
	char account[11];
	char name[11];
	UINT Reset;
	UINT MasterReset;
	UINT MasterResetDay;
	UINT MasterResetWek;
	UINT MasterResetMon;
};

struct SDHP_RANKING_DUEL_SAVE_RECV
{
	PBMSG_HEAD header; // C1:3C
	WORD index;
	char account[11];
	char name[11];
	DWORD WinScore;
	DWORD LoseScore;
};

struct SDHP_RANKING_BLOOD_CASTLE_SAVE_RECV
{
	PBMSG_HEAD header; // C1:3D
	WORD index;
	char account[11];
	char name[11];
	DWORD score;
};

struct SDHP_RANKING_CHAOS_CASTLE_SAVE_RECV
{
	PBMSG_HEAD header; // C1:3E
	WORD index;
	char account[11];
	char name[11];
	DWORD score;
};

struct SDHP_RANKING_DEVIL_SQUARE_SAVE_RECV
{
	PBMSG_HEAD header; // C1:3F
	WORD index;
	char account[11];
	char name[11];
	DWORD score;
};

struct SDHP_RANKING_ILLUSION_TEMPLE_SAVE_RECV
{
	PBMSG_HEAD header; // C1:40
	WORD index;
	char account[11];
	char name[11];
	DWORD score;
};

struct SDHP_CREATION_CARD_SAVE_RECV
{
	PBMSG_HEAD header; // C1:42
	WORD index;
	char account[11];
	BYTE ExtClass;
};

struct SDHP_CRYWOLF_INFO_SAVE_RECV
{
	PBMSG_HEAD header; // C1:49
	WORD MapServerGroup;
	DWORD CrywolfState;
	DWORD OccupationState;
};

struct SDHP_SNS_DATA_SAVE_RECV
{
	PWMSG_HEAD header; // C1:4E
	WORD index;
	char account[11];
	char name[11];
	BYTE data[256];
};

struct SDHP_CUSTOM_MONSTER_REWARD_SAVE_RECV
{
	PBMSG_HEAD header; // C1:52
	WORD index;
	char account[11];
	char name[11];
	DWORD MonsterClass;
	DWORD MapNumber;
	DWORD RewardValue1;
	DWORD RewardValue2;
};

struct SDHP_RANKING_CUSTOM_ARENA_SAVE_RECV
{
	PBMSG_HEAD header; // C1:55
	WORD index;
	char account[11];
	char name[11];
	DWORD number;
	DWORD score;
	DWORD rank;
};

struct SDHP_CONNECT_CHARACTER_RECV
{
	PBMSG_HEAD header; // C1:70
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_DISCONNECT_CHARACTER_RECV
{
	PBMSG_HEAD header; // C1:71
	WORD index;
	char account[11];
	char name[11];
};

struct SDHP_GLOBAL_WHISPER_RECV
{
	PBMSG_HEAD header; // C1:72
	WORD index;
	char account[11];
	char name[11];
	char TargetName[11];
	char message[60];
};

//**********************************************//
//********** DataServer -> GameServer **********//
//**********************************************//

struct SDHP_SERVER_INFO_SEND
{
	PBMSG_HEAD header; // C1:00
	BYTE result;
	DWORD ItemCount;
};

struct SDHP_CHARACTER_LIST_SEND
{
	PWMSG_HEAD header; // C2:01
	WORD index;
	char account[11];
	BYTE MoveCnt;
	BYTE ExtClass;
	#if(DATASERVER_UPDATE>=602)
	BYTE ExtWarehouse;
	#endif
	BYTE count;
};

struct SDHP_CHARACTER_LIST
{
	BYTE slot;
	char name[11];
	WORD level;
	BYTE Class;
	BYTE CtlCode;
	BYTE Inventory[60];
	BYTE GuildStatus;
	int Reset;
};

struct SDHP_CHARACTER_CREATE_SEND
{
	PBMSG_HEAD header; // C1:02
	WORD index;
	char account[11];
	char name[11];
	BYTE result;
	BYTE slot;
	BYTE Class;
	BYTE equipment[24];
	WORD level;
};

struct SDHP_CHARACTER_DELETE_SEND
{
	PBMSG_HEAD header; // C1:03
	WORD index;
	char account[11];
	BYTE result;
};

struct SDHP_CHARACTER_INFO_SEND
{
	PWMSG_HEAD header; // C2:04
	WORD index;
	char account[11];
	char name[11];
	BYTE result;
	BYTE Class;
	WORD Level;
	DWORD LevelUpPoint;
	DWORD Experience;
	DWORD Money;
	DWORD Strength;
	DWORD Dexterity;
	DWORD Vitality;
	DWORD Energy;
	DWORD Leadership;
	DWORD Life;
	DWORD MaxLife;
	DWORD Mana;
	DWORD MaxMana;
	DWORD BP;
	DWORD MaxBP;
	DWORD Shield;
	DWORD MaxShield;
	BYTE Inventory[INVENTORY_SIZE][16];
	BYTE Skill[MAX_SKILL_LIST][3];
	BYTE Map;
	BYTE X;
	BYTE Y;
	BYTE Dir;
	DWORD PKCount;
	DWORD PKLevel;
	DWORD PKTime;
	BYTE CtlCode;
	BYTE Quest[50];
	WORD FruitAddPoint;
	WORD FruitSubPoint;
	BYTE Effect[MAX_EFFECT_LIST][13];
	#if(DATASERVER_UPDATE>=602)
	BYTE ExtInventory;
	BYTE ExtWarehouse;
	#endif
	DWORD Reset;
	DWORD MasterReset;
	BYTE TheGift;
	BYTE IsMarried;
	char MarryName[11];
	int iQuestIndex;
	int iQuestState;
	int iQuestVar;
	int iQuestStat;
	WORD ChatLimitTime;
	#if(DATASERVER_UPDATE>=801)
	DWORD UseGuildMatching;
	DWORD UseGuildMatchingJoin;
	#endif
};

struct SDHP_CREATE_ITEM_SEND
{
	PBMSG_HEAD header; // C1:07
	WORD index;
	char account[11];
	BYTE X;
	BYTE Y;
	BYTE Map;
	DWORD Serial;
	WORD ItemIndex;
	BYTE Level;
	BYTE Dur;
	BYTE Option1;
	BYTE Option2;
	BYTE Option3;
	BYTE NewOption;
	WORD LootIndex;
	BYTE SetOption;
	BYTE JewelOfHarmonyOption;
	BYTE ItemOptionEx;
	BYTE SocketOption[5];
	BYTE SocketOptionBonus;
	DWORD Duration;
};

struct SDHP_OPTION_DATA_SEND
{
	PBMSG_HEAD header; // C1:08
	WORD index;
	char account[11];
	char name[11];
	BYTE SkillKey[20];
	BYTE GameOption;
	BYTE QKey;
	BYTE WKey;
	BYTE EKey;
	BYTE ChatWindow;
	BYTE RKey;
	DWORD QWERLevel;
	#if(DATASERVER_UPDATE>=701)
	BYTE ChangeSkin;
	#endif
};

struct SDHP_PET_ITEM_INFO_SEND
{
	PWMSG_HEAD header; // C2:09
	WORD index;
	char account[11];
	BYTE type;
	BYTE count;
};

struct SDHP_PET_ITEM_INFO2
{
	BYTE slot;
	DWORD serial;
	BYTE level;
	DWORD experience;
};

struct SDHP_CHARACTER_NAME_CHECK_SEND
{
	PBMSG_HEAD header; // C1:0A
	WORD index;
	char account[11];
	char name[11];
	BYTE result;
};

struct SDHP_CHARACTER_NAME_CHANGE_SEND
{
	PBMSG_HEAD header; // C1:0B
	WORD index;
	char account[11];
	char OldName[11];
	char NewName[11];
	BYTE result;
};

struct SDHP_CRYWOLF_SYNC_SEND
{
	PBMSG_HEAD header; // C1:1E
	WORD MapServerGroup;
	DWORD CrywolfState;
	DWORD OccupationState;
};

struct SDHP_CRYWOLF_INFO_SEND
{
	PBMSG_HEAD header; // C1:1F
	WORD MapServerGroup;
	DWORD CrywolfState;
	DWORD OccupationState;
};

struct SDHP_GLOBAL_POST_SEND
{
	PBMSG_HEAD header; // C1:20
	WORD MapServerGroup;
	BYTE type;
	char name[11];
	char message[60];
};

struct SDHP_GLOBAL_ITEM_POST_SEND
{
	PBMSG_HEAD header; // C1:78
	WORD MapServerGroup;
	char name[11];
    char message[60];
    char item_data[107];
};

struct SDHP_GLOBAL_NOTICE_SEND
{
	PBMSG_HEAD header; // C1:21
	WORD MapServerGroup;
	BYTE type;
	BYTE count;
	BYTE opacity;
	WORD delay;
	DWORD color;
	BYTE speed;
	char message[128];
};

struct SDHP_SNS_DATA_SEND
{
	PWMSG_HEAD header; // C1:24
	WORD index;
	char account[11];
	char name[11];
	BYTE result;
	BYTE data[256];
};

struct SDHP_GLOBAL_WHISPER_SEND
{
	PBMSG_HEAD header; // C1:72
	WORD index;
	char account[11];
	char name[11];
	BYTE result;
	char TargetName[11];
	char message[60];
};

struct SDHP_GLOBAL_WHISPER_ECHO_SEND
{
	PBMSG_HEAD header; // C1:73
	WORD index;
	char account[11];
	char name[11];
	char SourceName[11];
	char message[60];
};

struct DANHHIEU_GD_REQ_DATA
{
	PSBMSG_HEAD	header;
	WORD index;
	char name[11];
};
//
struct DANHHIEU_DG_GET_DATA
{
	PSBMSG_HEAD header;
	// ----
	WORD	index;
	int		RankSlot1;
	int		RankTitle1;
	int		RankTitle2;
	int		RankTitle3;
	int		RankTitle4;
	int		RankTitle5;
	int		RankTitle6;
	int		RankTitle7;
	int		RankTitle8;
	int		RankTitle9;
	int		RankTitle10;
	int		RankTitle11;
	int		RankTitle12;
	int		RankTitle13;
	int		RankTitle14;
	int		RankTitle15;
	int		RankTitle16;
	int		RankTitle17;
	int		RankTitle18;
	int		RankTitle19;
	int		RankTitle20;
};

struct DANHHIEU_GD_SAVE_DATA
{
	PSBMSG_HEAD header;
	// ----
	WORD	index;
	char	Name[11];
	int		RankSlot1;
	int		RankTitle1;
	int		RankTitle2;
	int		RankTitle3;
	int		RankTitle4;
	int		RankTitle5;
	int		RankTitle6;
	int		RankTitle7;
	int		RankTitle8;
	int		RankTitle9;
	int		RankTitle10;
	int		RankTitle11;
	int		RankTitle12;
	int		RankTitle13;
	int		RankTitle14;
	int		RankTitle15;
	int		RankTitle16;
	int		RankTitle17;
	int		RankTitle18;
	int		RankTitle19;
	int		RankTitle20;
};

struct THEGIFT_GD_SAVE_DATA
{
	PSBMSG_HEAD header;
	WORD	index;
	char	Name[11];
	BYTE	TheGift;
};
//**********************************************//

struct USER_REQ_RANK
{
	PSBMSG_HEAD h;
	char	Name[11];
	int aIndex;
};

struct USER_SEND_RANK
{
	PSBMSG_HEAD h;
	int aIndex;
	char Name[11];
	int Ranking;
};

struct ACC_SECURITY_REQ
{
	PSBMSG_HEAD	header;
	WORD index;
	char account[11];
};

struct ACC_SECURITY_DATA_SEND
{
	PSBMSG_HEAD header;
	// ----
	WORD index;
	int SecurityPass;
	BYTE SecurityLock;
	BYTE TradeLock;
	BYTE InventoryLock;
	BYTE WareLock;
	BYTE ShopLock;
	BYTE PShopLock;
	BYTE ChaosMixLock;
	BYTE DelCharLock;
};

struct ACC_SECURITY_DATA_SAVE
{
	PSBMSG_HEAD header;
	// ----
	WORD index;
	char account[11];
	BYTE SecurityLock;
	BYTE TradeLock;
	BYTE InventoryLock;
	BYTE WareLock;
	BYTE ShopLock;
	BYTE PShopLock;
	BYTE ChaosMixLock;
	BYTE DelCharLock;
};

struct ACCSECURITY_PASS_SAVE
{
	PSBMSG_HEAD header;
	WORD	index;
	char	account[11];
	int		SecurityPass;
};

//**********************************************//
//******************** BankEx ******************//
//**********************************************//

struct BANKEX_GD_SAVE_POINT
{
	PSBMSG_HEAD	h;
	// ----
	WORD	UserIndex;
	char	AccountID[11];
	long	Bless;
	long	Soul;
	long	Chaos;
	long	Creation;
	long	Life;
	long	Harmony;
};
// -------------------------------------------------------------------------------

struct BANKEX_GD_REQ_POINT
{
	PSBMSG_HEAD	h;
	// ----
	WORD	UserIndex;
	char	AccountID[11];
};
// -------------------------------------------------------------------------------

struct BANKEX_DG_GET_POINT
{
	PSBMSG_HEAD	h;
	// ----
	WORD	UserIndex;
	long	Bless;
	long	Soul;
	long	Chaos;
	long	Creation;
	long	Life;
	long	Harmony;
};
// -------------------------------------------------------------------------------
#define MAXTOP 150

struct GDTop
{
	PSWMSG_HEAD h;
	BYTE Result;
};

struct CharTop
{
	char Name[11];
	BYTE Class;
	int level;
	int Reset;
	int Map;
	char Guild[9];
};

struct DGCharTop
{
	PSWMSG_HEAD h;
	CharTop	tp[MAXTOP];
};
// -------------------------------------------------------------------------------
struct FRUIT_REQ_POINT
{
	PSBMSG_HEAD	h;
	// ----
	WORD	Index;
	char	Name[11];
};
// -------------------------------------------------------------------------------
struct FRUIT_GET_POINT
{
	PSBMSG_HEAD	h;
	// ----
	WORD Index;
	int	Strength;
	int	Dexterity;
	int	Vitality;
	int	Energy;
	int	Leadership;
};

struct FRUIT_SAVE_POINT
{
	PSBMSG_HEAD	h;
	// ----
	WORD	Index;
	char	Name[11];
	int	Strength;
	int	Dexterity;
	int	Vitality;
	int	Energy;
	int	Leadership;
};
//

struct GiftCode_GetInfo
{
	PSBMSG_HEAD	h;
	char Name[11];
	int ID;
	short aIndex;
};

struct GiftCode_Data_Struct
{
	BYTE IDCount;
	WORD ItemBagIndex;
	int Zen;
	int wCoinC;
	int wCoinP;
	int GoblinPoint;
	int BuffID;
	int BuffTime;
};

struct GIFTCODE_GETREWARD_INFOSAVE
{
	PSBMSG_HEAD	h;
	short aIndex;
	int ID_Num;
	GiftCode_Data_Struct rew;
};

struct SDHP_GIFTCODE_INFODEL
{
	PSBMSG_HEAD h;
	int ID_Num;
};

struct GIFTCODE_COUNT
{
	PSBMSG_HEAD	h;
	int ID;
};

struct GIFTCODE_LOG
{
	PSBMSG_HEAD	h;
	char Name[11];
	int ID;
};


// -------------------------------------------------------------------------------
//**********************************************//
//**********************************************//

void DataServerProtocolCore(int index,BYTE head,BYTE* lpMsg,int size);
void GDServerInfoRecv(SDHP_SERVER_INFO_RECV* lpMsg,int index);
void GDCharacterListRecv(SDHP_CHARACTER_LIST_RECV* lpMsg,int index);
void GDCharacterListMultiRecv(SDHP_CHARACTER_LIST_MULTI_RECV* lpMsg, int index);
void GDCharacterCreateRecv(SDHP_CHARACTER_CREATE_RECV* lpMsg,int index);
void GDCharacterDeleteRecv(SDHP_CHARACTER_DELETE_RECV* lpMsg,int index);
void GDCharacterInfoRecv(SDHP_CHARACTER_INFO_RECV* lpMsg,int index);
void GDCreateItemRecv(SDHP_CREATE_ITEM_RECV* lpMsg,int index);
void GDOptionDataRecv(SDHP_OPTION_DATA_RECV* lpMsg,int index);
void GDPetItemInfoRecv(SDHP_PET_ITEM_INFO_RECV* lpMsg,int index);
void GDCharacterNameCheckRecv(SDHP_CHARACTER_NAME_CHECK_RECV* lpMsg,int index);
void GDCharacterNameChangeRecv(SDHP_CHARACTER_NAME_CHANGE_RECV* lpMsg,int index);
void GDCrywolfSyncRecv(SDHP_CRYWOLF_SYNC_RECV* lpMsg,int index);
void GDCrywolfInfoRecv(SDHP_CRYWOLF_INFO_RECV* lpMsg,int index);
void GDGlobalPostRecv(SDHP_GLOBAL_POST_RECV* lpMsg,int index);
void GDGlobalItemPostRecv(SDHP_GLOBAL_ITEM_POST_RECV* lpMsg,int index);
void GDGlobalNoticeRecv(SDHP_GLOBAL_NOTICE_RECV* lpMsg,int index);
void GDSNSDataRecv(SDHP_SNS_DATA_RECV* lpMsg,int index);
void GDCharacterInfoSaveRecv(SDHP_CHARACTER_INFO_SAVE_RECV* lpMsg);
void GDInventoryItemSaveRecv(SDHP_INVENTORY_ITEM_SAVE_RECV* lpMsg);
void GDOptionDataSaveRecv(SDHP_OPTION_DATA_SAVE_RECV* lpMsg);
void GDPetItemInfoSaveRecv(SDHP_PET_ITEM_INFO_SAVE_RECV* lpMsg);
void GDResetInfoSaveRecv(SDHP_RESET_INFO_SAVE_RECV* lpMsg);
void GDMasterResetInfoSaveRecv(SDHP_MASTER_RESET_INFO_SAVE_RECV* lpMsg);
void GDRankingDuelSaveRecv(SDHP_RANKING_DUEL_SAVE_RECV* lpMsg);
void GDRankingBloodCastleSaveRecv(SDHP_RANKING_BLOOD_CASTLE_SAVE_RECV* lpMsg);
void GDRankingChaosCastleSaveRecv(SDHP_RANKING_CHAOS_CASTLE_SAVE_RECV* lpMsg);
void GDRankingDevilSquareSaveRecv(SDHP_RANKING_DEVIL_SQUARE_SAVE_RECV* lpMsg);
void GDRankingIllusionTempleSaveRecv(SDHP_RANKING_ILLUSION_TEMPLE_SAVE_RECV* lpMsg);
void GDCreationCardSaveRecv(SDHP_CREATION_CARD_SAVE_RECV* lpMsg);
void GDCrywolfInfoSaveRecv(SDHP_CRYWOLF_INFO_SAVE_RECV* lpMsg);
void GDSNSDataSaveRecv(SDHP_SNS_DATA_SAVE_RECV* lpMsg);
void GDCustomMonsterRewardSaveRecv(SDHP_CUSTOM_MONSTER_REWARD_SAVE_RECV* lpMsg);
void GDRankingCustomArenaSaveRecv(SDHP_RANKING_CUSTOM_ARENA_SAVE_RECV* lpMsg);
void GDConnectCharacterRecv(SDHP_CONNECT_CHARACTER_RECV* lpMsg,int index);
void GDDisconnectCharacterRecv(SDHP_DISCONNECT_CHARACTER_RECV* lpMsg,int index);
void GDGlobalWhisperRecv(SDHP_GLOBAL_WHISPER_RECV* lpMsg,int index);
void DGGlobalWhisperEchoSend(WORD ServerCode,WORD index,char* account,char* name,char* SourceName,char* message);
void GDCharacterTitleRecv(DANHHIEU_GD_REQ_DATA* lpMsg,int index);
void GDCharacterTitleSaveRecv(DANHHIEU_GD_SAVE_DATA* lpMsg);
void GDSaveTheGiftRecv(THEGIFT_GD_SAVE_DATA* lpMsg);
void GDAccSecurity(ACC_SECURITY_REQ* lpMsg,int index);
void GDAccSecuritySave(ACC_SECURITY_DATA_SAVE* lpMsg);
void GDSecurityPassSaveRecv(ACCSECURITY_PASS_SAVE* lpMsg);
void BankExReq(BANKEX_GD_REQ_POINT * lpMsg,int index);
void BankExSavePoint(BANKEX_GD_SAVE_POINT * lpMsg);
void CharacterRanking(GDTop* lpMsg, int pIndex);
void FruitSystem(FRUIT_REQ_POINT * lpMsg,int index);
void FruitSavePoint(FRUIT_SAVE_POINT * lpMsg);
void DelGiftCode(SDHP_GIFTCODE_INFODEL * aRecv);
void GiftBox_Check(GiftCode_GetInfo * lpMsg,int index);
void GiftCodeCount(GIFTCODE_COUNT * lpMsg);
void GiftCode_Log(GIFTCODE_LOG * lpMsg);
//**************************************************************************//
// RAW FUNCTIONS ***********************************************************//
//**************************************************************************//

void DS_GDReqCastleTotalInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqOwnerGuildMaster(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcBuy(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcRepair(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcUpgrade(BYTE *lpRecv, int aIndex);
void DS_GDReqTaxInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqTaxRateChange(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleMoneyChange(BYTE *lpRecv, int aIndex);
void DS_GDReqSiegeDateChange(BYTE *lpRecv, int aIndex);
void DS_GDReqGuildMarkRegInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqSiegeEndedChange(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleOwnerChange(BYTE *lpRecv, int aIndex);
void DS_GDReqRegAttackGuild(BYTE *lpRecv, int aIndex);
void DS_GDReqRestartCastleState(BYTE *lpRecv, int aIndex);
void DS_GDReqMapSvrMsgMultiCast(BYTE *lpRecv, int aIndex);
void DS_GDReqRegGuildMark(BYTE *lpRecv, int aIndex);
void DS_GDReqGuildMarkReset(BYTE *lpRecv, int aIndex);
void DS_GDReqGuildSetGiveUp(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcRemove(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleStateSync(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleTributeMoney(BYTE *lpRecv, int aIndex);
void DS_GDReqResetCastleTaxInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqResetSiegeGuildInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqResetRegSiegeInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleInitData(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqAllGuildMarkRegInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqFirstCreateNPC(BYTE *lpRecv, int aIndex);
void DS_GDReqCalcRegGuildList(BYTE *lpRecv, int aIndex);
void DS_GDReqCsGuildUnionInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqCsSaveTotalGuildInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqCsLoadTotalGuildInfo(BYTE *lpRecv, int aIndex);
void DS_GDReqCastleNpcUpdate(BYTE *lpRecv, int aIndex);