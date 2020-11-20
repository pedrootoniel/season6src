#pragma once
#define TEMP_S TRUE

//#include "stdafx.h"
#include "Protocol.h"
#include <vector>
#define SMITHY_CLASS	0
#define SMITHY_CATEGORY	1
#define SMITHY_ITEM		2
#define SMITHY_OPTION	3

#define ex_SMITHY_TEXT 0x789B

static char* Menu1[7] = 
{
	"Dark Wizard",
	"Dark Knight",
	"Elf",
	"Magic Gladiator",
	"Dark Lord",
	"Summoner",
	"Rage Fighter"
};

static char* Menu2[] = 
{
	"Weapon",
	"Shield",
	"Helm",
	"Armor",
	"Pants",
	"Gloves",
	"Boots",
	"Wings",
	"Ring & Pendant",
};

struct GC_SmithyInit
{
	PSBMSG_HEAD h;
	bool result;
};

struct GC_SmithySettings
{
	PSBMSG_HEAD h;
	unsigned char MaxLevel;
	unsigned short LevelPrice;
	unsigned char MaxDays;
	unsigned short DaysPrice;
	unsigned short LuckPrice;
	unsigned short AddPrice;
	unsigned short Opt1Price;
	unsigned short Opt2Price;
	unsigned short Opt3Price;
	unsigned short Opt4Price;
	unsigned short Opt5Price;
	unsigned short Opt6Price;
	unsigned short AncientPrice;
	unsigned short SocketPrice;
};

struct CG_SmithyCreateItem
{
	PSBMSG_HEAD h;
	unsigned short Item;
	unsigned char ItemLevel;
	unsigned char ItemTime;
	unsigned char ItemAdd;
	bool ItemLuck;
	bool ItemOpt1;
	bool ItemOpt2;
	bool ItemOpt3;
	bool ItemOpt4;
	bool ItemOpt5;
	bool ItemOpt6;
	BYTE ItemAncient;
	bool ItemSocket;
};

struct CG_SMITHY_REQ
{
	PSBMSG_HEAD	h;
};

struct GC_SmithyDATA
{
	PSBMSG_HEAD h;
	unsigned char Class;
	unsigned char Type;
	unsigned char Index;
	unsigned int  Price;
	unsigned int  Time;
};

struct SmithyDATA
{
	unsigned char Class;
	unsigned char Type;
	unsigned char Index;
	unsigned int  Price;
	unsigned int  Time;
};

struct SmithyAncDATA
{
	int Index;
	BYTE AncCount[2];
};

struct SmithySocketDATA
{
	int Index;
};

class CSmithy
{
public:
	CSmithy();
	~CSmithy();
	void Init();
	void Load();
	void LoadImg();
	void BindImg();
	void Draw();
	bool DrawCheckBuy();
	void Button(DWORD Event);
	void GCItemInit(GC_SmithyInit* aRecv);
	void GCItemSend(GC_SmithyDATA* aRecv);
	void GCSettingsRecv(GC_SmithySettings* aRecv);
	void GCAncientRecv(int Index, BYTE count[2]);
	void GCSocketRecv(int Index);
	void ClearAncientList();
	void ClearSocketList();
	void CGCreateItem();
	int GetCategory(int Type);
	int GetMaxItemCategory();
	int GetItemPrice();
	void CloseWindow();
	bool CheckRing();
	bool CheckPend();
	bool CheckAnc();
	BYTE GetCountOfAnc();
	BYTE GetAncientOption();
	bool CheckSocket();
	bool CheckFenrir();
	bool CheckOther();
	bool CheckExc();
	void SwitchSmithyWindowState();
	void CGSmithySend();
	unsigned char CheckWingLevel();
	unsigned char MainPage;
	unsigned char Class;
	unsigned char Category;
	unsigned char CategoryPage;
	unsigned short Item;
	unsigned char ItemLevel;
	unsigned char ItemTime;
	unsigned char ItemAdd;
	unsigned char ItemAnc;
	bool ItemLuck;
	bool ItemOpt1;
	bool ItemOpt2;
	bool ItemOpt3;
	bool ItemOpt4;
	bool ItemOpt5;
	bool ItemOpt6;
	bool ItemSocket;
	//bool ItemAncient;
	unsigned short CheckOpt;
	unsigned char MaxLevel;
	unsigned char MaxDays;
	unsigned short LevelPrice;
	unsigned short DaysPrice;
	unsigned short LuckPrice;
	unsigned short AddPrice;
	unsigned short Opt1Price;
	unsigned short Opt2Price;
	unsigned short Opt3Price;
	unsigned short Opt4Price;
	unsigned short Opt5Price;
	unsigned short Opt6Price;
	unsigned short AncientPrice;
	unsigned short SocketPrice;
	std::vector<SmithyDATA> itemdata;
	std::vector<SmithyAncDATA> m_AncData;
	std::vector<SmithySocketDATA> m_SocketData;
};
extern CSmithy gSmithy;

/*
2 wing:
	2 -- Increase Attackin(Wizardy) speed +5
	3 - Max Ag + 50 Increased
	4 - Ignor Optionent's defensive power by 3%%
	5 - Mana + 50 Increased
	6 - HP + 50 Increased

3 wing:
	3 - Complete reco of Mana in 5%% rate
	4 - Complete recoy of Life in 5%% rate
	5 - Return the enemy attack power in 5%%
	6 - Ignor openent defensive power by 5%%
*/