#include "StdAfx.h"
#include "LuckySpin.h"
#include "GameMain.h"
#include "DSProtocol.h"
#include "Log.h"
#include "Notice.h"
#include "MemScript.h"
#include "Util.h"
#include "ItemManager.h"
#include "SetItemType.h"
#include "CashShop.h"
#include "SocketItemType.h"
#include "User.h"
#include "Path.h"

CLuckySpin gLuckySpin;

CLuckySpin::CLuckySpin()
{
	this->Init();
}

CLuckySpin::~CLuckySpin()
{
}

void CLuckySpin::Init()
{
	this->itemdata.clear();
	this->TicketType = 0;
	this->TicketIndex = 0;
	this->number = -1;
}

void CLuckySpin::Load()
{
	this->Init();
	this->Read(gPath.GetFullPath("Custom\\LuckySpin.txt"));
}

void CLuckySpin::Read(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}
		
			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->TicketType = lpMemScript->GetNumber();
					this->TicketIndex = lpMemScript->GetAsNumber();
				}
				else if (section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					LuckySpin_Data info;

					info.ItemType = lpMemScript->GetNumber();

					info.ItemIndex = lpMemScript->GetAsNumber();

					info.ItemLevel = lpMemScript->GetAsNumber();

					info.ItemSkill = lpMemScript->GetAsNumber();

					info.ItemLuck = lpMemScript->GetAsNumber();

					info.ItemOption = lpMemScript->GetAsNumber();

					info.ItemExc = lpMemScript->GetAsNumber();

					info.ItemTime = lpMemScript->GetAsNumber();

					this->itemdata.push_back(info);
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CLuckySpin::GCInitItem(int aIndex)
{
	if(gObjIsConnected(aIndex) == 0)
	{
		return;
	}

	GC_LuckySpinInit pMsg;
	pMsg.h.set(0xFB, 0x34,  sizeof(pMsg));
	pMsg.result = true;
	DataSend(aIndex,(LPBYTE)&pMsg,sizeof(pMsg));
}

void CLuckySpin::GCItemSend(int aIndex)
{
	if(gObjIsConnected(aIndex) == 0)
	{
		return;
	}

	GC_LuckySpin_Data pMsg;
	pMsg.h.set(0xFB, 0x33, sizeof(pMsg));
	for(int i = 0; i < itemdata.size(); i++)
	{
		pMsg.ItemType = itemdata[i].ItemType;
		pMsg.ItemIndex = itemdata[i].ItemIndex;
		pMsg.ItemLevel = itemdata[i].ItemLevel;
		pMsg.ItemExc = itemdata[i].ItemExc;
		DataSend(aIndex,(BYTE*)&pMsg,sizeof(pMsg));
	}

	this->GCInitItem(aIndex);
}


void CLuckySpin::StartRoll(LPOBJ lpObj)
{
	int TicketCount = gItemManager.GetInventoryItemCount(lpObj, GET_ITEM(this->TicketType, this->TicketIndex), 0);
	if ( TicketCount <= 0 )
		{
			return;
		}
	gItemManager.DeleteInventoryItemCount(lpObj, GET_ITEM(this->TicketType, this->TicketIndex), 0, 1);
	
	lpObj->LuckySpinTime = GetTickCount();

	GC_LuckySpinRoll pMsg;
	pMsg.header.set(0xFB,0x26,sizeof(pMsg));
	DataSend(lpObj->Index,(BYTE*)&pMsg,pMsg.header.size);

}

void CLuckySpin::MakeItem(int aIndex)
{
	srand(time(NULL));
	number = rand() % 11;
	time_t t = time(NULL);
	localtime(&t);
	DWORD iTime = (DWORD)t + this->itemdata[number].ItemTime * 86400;
	if(this->itemdata[number].ItemTime >= 1)
	{
		GDCreateItemSend(aIndex,0xEB,0,0,GET_ITEM(this->itemdata[number].ItemType,this->itemdata[number].ItemIndex),this->itemdata[number].ItemLevel,0,this->itemdata[number].ItemSkill,this->itemdata[number].ItemLuck,this->itemdata[number].ItemOption,-1,this->itemdata[number].ItemExc,0,0,0,0,0xFF,iTime);
	}
	else
	{
		GDCreateItemSend(aIndex,0xEB,0,0,GET_ITEM(this->itemdata[number].ItemType,this->itemdata[number].ItemIndex),this->itemdata[number].ItemLevel,0,this->itemdata[number].ItemSkill,this->itemdata[number].ItemLuck,this->itemdata[number].ItemOption,-1,this->itemdata[number].ItemExc,0,0,0,0,0xFF,0);
	}
}