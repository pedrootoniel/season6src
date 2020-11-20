#include "stdafx.h"
#include "ShopSearch.h"
#include "Interface.h"
#include "Protocol.h"
#include "Console.h"
//#include "TMemory.h"
#include "Object.h"
#include "Offset.h"
#include "Util.h"
#include "Console.h"
#include "CustomMessage.h"
#include "TMemory.h"

#if(SHOPSEARCH==TRUE)

PersonalShopEx g_PersonalShopEx;
// ----------------------------------------------------------------------------------------------
void PersonalShopEx::BindImages()
{
	gInterface.BindObject(ePT_PERSONAL_SEARCH_MAIN, 0x7A5A, 222, 345.0, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_TITLE, 0x7A63, 230, 67, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_FRAME, 0x7A58, 230, 15, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_FOOTER, 0x7A59, 230, 50, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_DIV, 0x7A62, 223, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_CLOSE, 0x7EC5, 36, 29, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_L, 0x7BAA, 17, 17, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_R, 0x7BAB, 17, 17, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP1, 0x7E98, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP2, 0x7E98, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP3, 0x7E98, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP4, 0x7E98, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP5, 0x7E98, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP6, 0x7E98, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP7, 0x7E98, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP8, 0x7E98, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP9, 0x7E98, 170, 21, -1, -1);
	gInterface.BindObject(ePT_PERSONAL_SEARCH_PAGEUP10, 0x7E98, 170, 21, -1, -1);
}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Draw()
{
	if( gInterface.CheckWindow(Store) )
	{
		g_PersonalShopEx.aTargetIndex = pGameIndex;
		return;
	}

	if( gInterface.CheckWindow(OtherStore) )
	{
		return;
	}

	if(!gInterface.CheckWindowEx(ePT_PERSONAL_SEARCH_MAIN))
	{
		return;
	}

	pSetCursorFocus = true;

	// ----
	DWORD ItemNameColor		= eWhite;
	float MainWidth			= 230.0;
	float MainHeight		= 350.0;
	float StartY			= 50;	100;
	float StartX			= (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter		= StartX + (MainWidth / 3);
	float ButtonX			= MainCenter - (29.0 / 2);

	float ContentX          = StartX;
	float ContentY			= StartY;

	// ----
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_MAIN, StartX+4, StartY + 4);
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(ePT_PERSONAL_SEARCH_FRAME, StartX, StartY + 67.0, 16);
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_FOOTER, StartX, StartY);
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_CLOSE, StartX + MainWidth - gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].Width, ContentY);
	// ----
	if( gInterface.IsWorkZone2(ePT_PERSONAL_SEARCH_CLOSE) )
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_PERSONAL_SEARCH_CLOSE, gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].X, gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].Y, Color);
		gInterface.DrawToolTip(gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].X + 5, gInterface.Data[ePT_PERSONAL_SEARCH_CLOSE].Y + 25, gCustomMessage.GetMessage(14));
	}
	// ----

	gInterface.DrawFormat(eGold, ContentX + 10, ContentY + 8, 210, 3, gCustomMessage.GetMessage(116));

	// -> Content

	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_DIV, ContentX, ContentY + 40);

	float ListDrawX = ContentX + 20 + 15;
	float ListDrawY = ContentY + 10 + 25;

	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, gCustomMessage.GetMessage(117));

	ListDrawX += 50;
	gInterface.DrawFormat(eGold, ListDrawX, ListDrawY + 20, 100, 1, gCustomMessage.GetMessage(118));

	ListDrawX += 50;

	ListDrawX += 15;

	ListDrawX += 20;

	ListDrawX += 35;

	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_DIV, ContentX, ListDrawY + 23);

	// ----------

	// -> Draw Listing

	for(int i = 0; i < 10; i++)
	{

		if(this->PShop[i].Name[0] == NULL) continue;

		gInterface.DrawGUI(ePT_PERSONAL_SEARCH_PAGEUP1 + i, ContentX + 10 + 18, ContentY + 77 + i * 22);

		ListDrawX = ContentX + 20 + 18;
		ListDrawY = ContentY + 60 + i * 22;

		gInterface.DrawFormat(eYellow, ListDrawX - 7, ListDrawY + 21, 100, 1, this->PShop[i].Name);

		ListDrawX += 50;
		gInterface.DrawFormat(eWhite, ListDrawX, ListDrawY + 21, 100, 1, "%s", this->PShop[i].PersonalText);

		ListDrawX += 50;

		ListDrawX += 15;

		ListDrawX += 20;

		ListDrawX += 27;

		ListDrawX += 10;

		if(gInterface.IsWorkZone2(ePT_PERSONAL_SEARCH_PAGEUP1 + i))
		{
			DWORD Color = eGray100;
			// ----
			if( gInterface.Data[ePT_PERSONAL_SEARCH_PAGEUP1 + i].OnClick )
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(ePT_PERSONAL_SEARCH_PAGEUP1 + i, gInterface.Data[ePT_PERSONAL_SEARCH_PAGEUP1 + i].X, gInterface.Data[ePT_PERSONAL_SEARCH_PAGEUP1 + i].Y, Color);
		}

	}

	// -----------

	//-> Page Draw

	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_DIV, ContentX, gInterface.Data[ePT_PERSONAL_SEARCH_FOOTER].Y - 10);

	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_L, ContentX + 80, ContentY + 325);
	gInterface.DrawGUI(ePT_PERSONAL_SEARCH_R, ContentX + 130, ContentY + 325);

	if(gInterface.IsWorkZone2(ePT_PERSONAL_SEARCH_L))
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_PERSONAL_SEARCH_L].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_PERSONAL_SEARCH_L, gInterface.Data[ePT_PERSONAL_SEARCH_L].X, gInterface.Data[ePT_PERSONAL_SEARCH_L].Y, Color);
	}

	if(gInterface.IsWorkZone2(ePT_PERSONAL_SEARCH_R))
	{
		DWORD Color = eGray100;
		// ----
		if( gInterface.Data[ePT_PERSONAL_SEARCH_R].OnClick )
		{
			Color = eGray150;
		}
		// ----
		gInterface.DrawColoredGUI(ePT_PERSONAL_SEARCH_R, gInterface.Data[ePT_PERSONAL_SEARCH_R].X, gInterface.Data[ePT_PERSONAL_SEARCH_R].Y, Color);
	}

	gInterface.DrawFormat(eGold, ContentX+97, ContentY + 329, 100, 1, "Page: %d/%d", this->Page+1,(this->TotalShop-1)/10+1);
}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::Button(DWORD Event)
{
	if( gInterface.CheckWindow(Store) || gInterface.CheckWindow(OtherStore) )
	{
		return;
	}

	if(!gInterface.CheckWindowEx(ePT_PERSONAL_SEARCH_MAIN))
	{
		return;
	}

	if(gInterface.ButtonEx(Event, ePT_PERSONAL_SEARCH_CLOSE, 0))
	{
		gInterface.CloseWindowEx(ePT_PERSONAL_SEARCH_MAIN);
	}

	if( gInterface.ButtonEx(Event, ePT_PERSONAL_SEARCH_L, false ) )
	{
		if(this->Page != 0)
		{
			this->Page--;
			this->CG_Send();
		}
		return;
	}
	else if( gInterface.ButtonEx(Event, ePT_PERSONAL_SEARCH_R, false ) )
	{
		if(this->Page != (this->TotalShop-1)/10)
		{
			 this->Page++;
			 this->CG_Send();
		}
		return;
	}

	// --------

	if(gInterface.CheckWindowEx(ePT_PERSONAL_SEARCH_MAIN))
	{
		for(int i = 0; i < 10; i++)
		{
			if(gInterface.ButtonEx(Event, ePT_PERSONAL_SEARCH_PAGEUP1 + i, false))
			{
				PMSG_REQ_BUYLIST_FROM_PSHOP pReq;
				pReq.header.set(0xFF, 0x20, sizeof(pReq));

				//pReq.index[0] = SET_NUMBERHW(this->PShop[i].aIndex);
				//pReq.index[1] = SET_NUMBERLW(this->PShop[i].aIndex);
				pReq.index[0] = SET_NUMBERHB(this->PShop[i].aIndex);
				pReq.index[1] = SET_NUMBERLB(this->PShop[i].aIndex);

				memcpy(pReq.name, this->PShop[i].Name, 10);

				DataSend((BYTE*)&pReq, pReq.header.size);
			}
		}
	}
}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::GC_Recv(LPBYTE aRecv)
{
	ZeroMemory(&this->PShop,sizeof(this->PShop));
	int datasize = 8;
	int excount = MAKE_NUMBERW(aRecv[datasize-3], aRecv[datasize-2]);
	this->TotalShop = excount;

	int SendCount = aRecv[datasize-1];

	for (int n = 0; n < SendCount; n++)
	{
		GC_PersonalShopInfo ap;
		memcpy(&ap,&aRecv[datasize],sizeof(ap));

		this->PShop[n].aIndex = ap.aIndex;
		strncpy(this->PShop[n].Name, ap.Name, 10);
		strncpy(this->PShop[n].PersonalText, ap.PersonalText, 36);
		this->PShop[n].Value = ap.Value;

		datasize += sizeof(ap);
		//g_Console.AddMessage(1,"%d",datasize);
	}

	if(!gInterface.CheckWindowEx(ePT_PERSONAL_SEARCH_MAIN))
	{
		gInterface.OpenWindowEx(ePT_PERSONAL_SEARCH_MAIN);
	}
}
// ----------------------------------------------------------------------------------------------

void PersonalShopEx::CG_Send()
{
	CG_PersonalPage pRequest;
	pRequest.h.set(0xFF, 0x22, sizeof(pRequest));
	pRequest.Page = this->Page;
	DataSend((BYTE*)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------
#endif