#pragma once

#define MAX_ITEMPRICE	1000

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
	void Load(char *path);
	void SetInfo(CUSTOM_ITEMPRICE info);
public:
	CUSTOM_ITEMPRICE m_ItemPrice[MAX_ITEMPRICE];
}; extern ItemPrice gItemPrice;