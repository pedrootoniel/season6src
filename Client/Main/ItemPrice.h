#pragma once

#define MAX_ITEMPRICE	1000
#define MAX_ITEMSTACK	41
#include "Object.h"

struct CUSTOM_ITEMPRICE
{
	int Index;
	int ItemIndex;
	int Level;
	int Grade;
	int AncOption;
	int OptionEx;
	int Type;
	int BuyPrice;
	int SellPrice;
};

class ItemPrice
{
public:
	ItemPrice();
	virtual ~ItemPrice();
	void Init();
	void Load(CUSTOM_ITEMPRICE* info);
	void SetInfo(CUSTOM_ITEMPRICE info);
	bool CheckItem(ObjectItem * lpItem, __int64 * Price, int * Divisor);
	static void ShowBuyPrice(DWORD a1, const char *a2, char *Price);
	static void ShowSellPrice(DWORD a1, const char *a2, char *Price);
	static void Test(DWORD a1, const char *a2, char *Price);
	CUSTOM_ITEMPRICE m_ItemPrice[MAX_ITEMPRICE];
	int		showtype;
	int		showsellprice;
	int		showbuyprice;
}; extern ItemPrice gItemPrice;