#include "stdafx.h"
#include "ItemPrice.h"
#include "MemScript.h"

ItemPrice gItemPrice;

ItemPrice::ItemPrice()
{
	this->Init();
}

ItemPrice::~ItemPrice()
{
	
}

void ItemPrice::Init()
{
	for (int n = 0; n < MAX_ITEMPRICE; n++)
	{
		this->m_ItemPrice[n].Index = -1;
	}
}

void ItemPrice::Load(char * path)
{
	CMemScript* lpMemScript = new CMemScript;

	int Index = 0;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			CUSTOM_ITEMPRICE info;

			info.Index = Index++;

			info.ItemIndex = lpMemScript->GetNumber();

			info.Level = lpMemScript->GetAsNumber();

			info.Grade = lpMemScript->GetAsNumber();

			info.AncOption = lpMemScript->GetAsNumber();

			info.OptionEx = lpMemScript->GetAsNumber();

			info.Type = lpMemScript->GetAsNumber();

			info.BuyPrice = lpMemScript->GetAsNumber();

			info.SellPrice = lpMemScript->GetAsNumber();

			

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void ItemPrice::SetInfo(CUSTOM_ITEMPRICE info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_ITEMPRICE)
	{
		return;
	}

	this->m_ItemPrice[info.Index] = info;
}
