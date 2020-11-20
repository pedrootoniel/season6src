#pragma once

#include "StdAfx.h"
#include "Protocol.h"
#include "SetItemType.h"

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
	BYTE Ancient;
	bool ItemSocket;
};

struct GC_SmithyInit
{
	PSBMSG_HEAD h;
	bool result;
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

struct PMSG_SMITHY_ANCIENT_SEND
{
	PSWMSG_HEAD header;
	BYTE count;
};

struct PMSG_SMITHY_ANCIENT
{
	int index;
	BYTE options[MAX_SET_ITEM_OPTION_INDEX];
};

struct PMSG_SMITHY_SOCKET_SEND
{
	PSWMSG_HEAD header;
	BYTE count;
};

struct PMSG_SMITHY_SOCKET
{
	int index;
};

class CSmithy
{
public:
	CSmithy();
	~CSmithy();
	void Init();
	void Load();
	void Read(char* filename);
	void GCInitItem(int aIndex);
	void GCItemSend(int aIndex);
	void GCSettingsSend(int aIndex);
	void GCSendAncientList(int aIndex);
	void GCSendSocketList(int aIndex);
	void CGCreateItem(CG_SmithyCreateItem* aRecv, int aIndex);
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
};
extern CSmithy gSmithy;