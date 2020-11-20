#include "stdafx.h"
#include "ItemPrice.h"
#include "Console.h"
#include "Defines.h"
#include "Offset.h"
#include "HealthBar.h"
#include "Protect.h"
#include "Util.h"
#include "Item.h"
#include "Import.h"
#include "CustomMessage.h"
//#include "NewParty.h"

ItemPrice gItemPrice;

ItemPrice::ItemPrice()
{
	this->Init();
}

ItemPrice::~ItemPrice()
{
	
}

int StackItems[MAX_ITEMSTACK] = 
{6688, 6689, 6690, 6288, 6290, 6801, 6803, 7168, 7169, 7170, 7171, 7172, 7173, 7174, 7175, 7176, 7197, 7203, 7204, 7205, 
7206, 7207, 7008, 7214, 7215, 7216, 7217, 7218, 7238, 7239, 7253, 7254, 7255, 7256, 7257, 7258, 7268, 7269, 7278, 7301, 7389};

#define sub_4F9CB0_Addr		((char(__cdecl*)(int a1, int a2, int a3, int a4)) 0x4F9CB0)

char __cdecl sub_4F9CB0(int a1, int a2, int a3, int a4)
{
	HDC test;
	return sub_4F9CB0_Addr(a1,a2,a3,a4);
}

#define sub_9593B0_Addr		((BOOL(__stdcall*)(/*LPVOID This,*/HDC hdc, LPCSTR lpMultiByteStr, int a3, LPSIZE psizl)) 0x9593B0)

#define sub_42DE10_Addr		((int(__thiscall*)(void *This, int *a2)) 0x42DE10)//int __thiscall sub_42DE10(void *this, int a2)

#define sub_958FC0_Addr		((int(__thiscall*)(void *This, int *a2, LPCSTR lpMultiByteStr)) 0x958FC0)//int __thiscall sub_958FC0(void *this, int a2, LPCSTR lpMultiByteStr)


static int pDrawText1(int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
{
	//g_Console.AddMessage(5,"%d %d %d %d",nCount,nTabPositions,lpnTabStopPositions,nTabOrigin);
	//static int lol = 0;
	//g_Console.AddMessage(5,"[%d] %s (%d %d %d %d)",lol++,Text,nCount,nTabPositions,lpnTabStopPositions,nTabOrigin);
	//nCount*=2;
	//nTabPositions*=2;
	//lpnTabStopPositions+=1;
	//nTabOrigin-=1;
	//HGDIOBJ ho = *(HGDIOBJ*)0x00E8C58C;
	//FW_BOLD
	pSetFont(pTextThis(), int(pFontNormal2));
	return pDrawText(pTextThis(),PosX,PosY,Text,nCount,nTabPositions,lpnTabStopPositions,nTabOrigin);
	//return 0;
}

#define sub_5BF700_Addr		((int(__cdecl*)(int a1, int count, signed int a3, signed int a4, int a5, signed int a6, int a7, int a8, int a9)) 0x5BF700)

int __cdecl sub_5BF700(int a1, int count, signed int a3, signed int a4, int a5, signed int a6, int a7, int a8, int a9)
{
	//SetFloat(0xD22BB8,2.0); // отступ
	/*for	(int i=0;i<count;i++)
	{
		char *test = *(char**)(0x81C0AE0 + (100 * i));
		g_Console.AddMessage(5,test);
	}*/
	return sub_5BF700_Addr(a1,count,a3,a4,a5,a6,a7,a8,a9);
	//return 0;
}

void ItemPrice::Init()
{
	for (int n = 0; n < MAX_ITEMPRICE; n++)
	{
		this->m_ItemPrice[n].Index = -1;
		this->m_ItemPrice[n].ItemIndex = -1;
	}
	this->showtype = 0;
	this->showbuyprice = 0;
	this->showsellprice = 0;
	SetCompleteHook(0xFF, 0x007E44D3, &this->ShowBuyPrice);
	SetCompleteHook(0xFF, 0x007E452F, &this->ShowSellPrice);
	//SetCompleteHook(0xFF, 0x7E3E30+0x581, &sub_4F9CB0);

	//0x5BF700+0x983
	//SetCompleteHook(0xE8,0x5BF700+0x983,&pDrawText1);

    //005BFD78      
	//SetCompleteHook(0xE8,0x5BF700+0x106,&sub_9593B0);

//SetCompleteHook(0xE8,0x4900B0+0x4D3 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x4EB910+0x3E6 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x4EBE70+0x334 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x4F91F0+0x287 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x4F9CB0+0xABB ,&sub_5BF700);
//SetCompleteHook(0xE8,0x5C05B0+0xC6  ,&sub_5BF700);
//SetCompleteHook(0xE8,0x5C0740+0x18B ,&sub_5BF700);
//SetCompleteHook(0xE8,0x5C3D70+0xABC ,&sub_5BF700);
//SetCompleteHook(0xE8,0x5C4BA0+0x1AE0,&sub_5BF700);
//SetCompleteHook(0xE8,0x777FB0+0x1F8 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x7D1D70+0x1DB ,&sub_5BF700);
//SetCompleteHook(0xE8,0x7D1D70+0x37D ,&sub_5BF700);
//SetCompleteHook(0xE8,0x7D1D70+0x4A6 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x7D1D70+0x60E ,&sub_5BF700);
//SetCompleteHook(0xE8,0x7E0EA0+0x720 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x7E3E30+0x1E68,&sub_5BF700);
//SetCompleteHook(0xE8,0x7E3E30+0x1E86,&sub_5BF700);
//SetCompleteHook(0xE8,0x81A5B0+0xA7  ,&sub_5BF700);
//SetCompleteHook(0xE8,0x81B2D0+0x987 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x86DEE0+0x4CD ,&sub_5BF700);
//SetCompleteHook(0xE8,0x86DEE0+0x5F4 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x86DEE0+0x719 ,&sub_5BF700);
//SetCompleteHook(0xE8,0x969030+0x293 ,&sub_5BF700);

	//sub_7E3E30+581
	//SetCompleteHook(0xFF, 0x007E4575, &this->Test);
	
}

void ItemPrice::Load(CUSTOM_ITEMPRICE* info)
{
	for(int n=0;n < MAX_ITEMPRICE;n++)
	{
		this->SetInfo(info[n]);
	}
}

void ItemPrice::SetInfo(CUSTOM_ITEMPRICE info)
{
	if(info.Index < 0 || info.Index >= MAX_ITEMPRICE)
	{
		return;
	}
	//g_Console.AddMessage(5,"[Load] %d %d %d %d",info.Index, info.ItemIndex, info.Level, info.Grade);
	this->m_ItemPrice[info.Index] = info;
}

bool ItemPrice::CheckItem(ObjectItem * lpItem, __int64 * Price, int * Divisor)
{
	for (int i=0; i < MAX_ITEMPRICE; i++)
	{
		if (this->m_ItemPrice[i].Index == -1 || this->m_ItemPrice[i].ItemIndex == -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		if (lpItem->ItemID != this->m_ItemPrice[i].ItemIndex)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		if (GET_ITEMOPT_LEVEL(lpItem->Level) != this->m_ItemPrice[i].Level && this->m_ItemPrice[i].Level != -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		int ExcellentOpt = lpItem->ExcellentOption;

		if (ExcellentOpt > 63)
		{
			ExcellentOpt -= 64;
		}

		if (ExcellentOpt != this->m_ItemPrice[i].Grade && this->m_ItemPrice[i].Grade != -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		//console.Log("", "Anc [%d %d] OptionEx [%d %d] Grade [%d]", this->m_ItemPrice[i].AncOption, lpItem->AncientOption, this->m_ItemPrice[i].OptionEx, lpItem->Is380Item, this->m_ItemPrice[i].Grade);
		//g_Console.AddMessage(5,"Anc [%d %d] OptionEx [%d %d] Grade [%d]", this->m_ItemPrice[i].AncOption, lpItem->AncientOption, this->m_ItemPrice[i].OptionEx, lpItem->Is380Item, this->m_ItemPrice[i].Grade);
		if (this->m_ItemPrice[i].AncOption != lpItem->AncientOption && this->m_ItemPrice[i].AncOption != -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		if (this->m_ItemPrice[i].OptionEx != lpItem->Is380Item && this->m_ItemPrice[i].OptionEx != -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		for (int n=0; n<MAX_ITEMSTACK; n++)
		{
			if (lpItem->ItemID == StackItems[n])
			{
				int SellPrice = 0;

				if (this->m_ItemPrice[i].SellPrice == -1)
				{
					SellPrice = (this->m_ItemPrice[i].BuyPrice*lpItem->Durability) / 3;
				}
				else
				{
					SellPrice = (this->m_ItemPrice[i].SellPrice*lpItem->Durability);
				}	
				//console.Log(FUNC, "%d durability [%d] total price [%d]", lpItem->ItemID, lpItem->Durability, this->m_ItemPrice[i].Value*lpItem->Durability);
				*Price		= this->m_ItemPrice[i].BuyPrice*lpItem->Durability;
				*Divisor	= SellPrice;
				this->showtype		=	this->m_ItemPrice[i].Type;
				this->showbuyprice = this->m_ItemPrice[i].BuyPrice*lpItem->Durability;
				this->showsellprice = SellPrice;
				return true;
			}
		}
		int SellPrice = 0;

		if (this->m_ItemPrice[i].SellPrice == -1)
		{
			SellPrice = this->m_ItemPrice[i].BuyPrice / 3;
		}
		else
		{
			SellPrice = this->m_ItemPrice[i].SellPrice;
		}

		*Price		= this->m_ItemPrice[i].BuyPrice;
		*Divisor	= SellPrice;
		this->showtype		=	this->m_ItemPrice[i].Type;
		this->showbuyprice = this->m_ItemPrice[i].BuyPrice;
		this->showsellprice = SellPrice;
		return true;
	}
	return false;
}

void ItemPrice::Test(DWORD a1, const char *a2, char *Price)
{
	//g_Console.AddMessage(5,"%s",(char*)0x81C0AE0);
	
	pShowPrice(a1,a2,Price);
}

void ItemPrice::ShowBuyPrice(DWORD a1, const char *a2, char *Price)
{
	if(gItemPrice.showbuyprice > 0)
	{
		if (gItemPrice.showtype == 0)
		{
			pShowPrice(a1,gCustomMessage.GetMessage(211),Price);
		}
		else if (gItemPrice.showtype == 1)
		{
			pShowPrice(a1,gCustomMessage.GetMessage(212),Price);
		}
		else if (gItemPrice.showtype == 2)
		{
			pShowPrice(a1,gCustomMessage.GetMessage(213),Price);
		}
		else if (gItemPrice.showtype == 3)
		{
			pShowPrice(a1,gCustomMessage.GetMessage(214),Price);
		}
		else
		{
			pShowPrice(a1,gCustomMessage.GetMessage(211),Price);
		}
	}
	else
	{
		pShowPrice(a1,gCustomMessage.GetMessage(211),Price);
	}
}

void ItemPrice::ShowSellPrice(DWORD a1, const char *a2, char *Price)
{
	if(gItemPrice.showsellprice > 0)
	{
		if (gItemPrice.showtype == 0)
		{
			pShowPrice(a1,gCustomMessage.GetMessage(207),Price);
		}
		else if (gItemPrice.showtype == 1)
		{
			pShowPrice(a1,gCustomMessage.GetMessage(208),Price);
		}
		else if (gItemPrice.showtype == 2)
		{
			pShowPrice(a1,gCustomMessage.GetMessage(209),Price);
		}
		else if (gItemPrice.showtype == 3)
		{
			pShowPrice(a1,gCustomMessage.GetMessage(210),Price);
		}
		else
		{
			pShowPrice(a1,gCustomMessage.GetMessage(207),Price);
		}
	}
	else
	{
		pShowPrice(a1,gCustomMessage.GetMessage(207),Price);
	}
}