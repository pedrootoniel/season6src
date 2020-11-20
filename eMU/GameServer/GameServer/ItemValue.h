// ItemValue.h: interface for the CItemValue class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Item.h"

struct ITEM_VALUE_INFO
{
	int Index;
	int Level;
	int Grade;
	int AncOption;
	int OptionEx;
	int Type;
	int BuyPrice;
	int SellPrice;
};

enum ItemPriceType
{
	ZEN = 0,
	WCOINC = 1,
	WCOINP = 2,
	WCOING = 3,
};

class CItemValue
{
public:
	CItemValue();
	virtual ~CItemValue();
	void Load(char* path);
	bool GetItemValue(CItem* lpItem, int* type, int* BuyPrice, int* SellPrice);
private:
	std::vector<ITEM_VALUE_INFO> m_ItemValueInfo;
};

extern CItemValue gItemValue;
