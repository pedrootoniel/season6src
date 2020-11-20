#include "stdafx.h"
#include "CustomWeapons.h"
#include "Console.h"

cCustomWeapons gCustomWeapons;

cCustomWeapons::cCustomWeapons() // OK
{
	this->Init();
}

cCustomWeapons::~cCustomWeapons() // OK
{

}

void cCustomWeapons::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_WEAPONS;n++)
	{
		this->m_CustomWeaponsInfo[n].Index = -1;
	}
}

void cCustomWeapons::Load(CUSTOM_WEAPONS_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_WEAPONS;n++)
	{
		this->SetInfo(info[n]);
	}
}

void cCustomWeapons::SetInfo(CUSTOM_WEAPONS_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_WEAPONS)
	{
		return;
	}

	this->m_CustomWeaponsInfo[info.Index] = info;
}

bool cCustomWeapons::CheckElfBow(int ItemID)
{
	for (int i=0;i<MAX_CUSTOM_WEAPONS; i++)
	{
		if (this->m_CustomWeaponsInfo[i].Index == -1)
		{
			continue;
		}

		if (ItemID == this->m_CustomWeaponsInfo[i].ItemIndex && this->m_CustomWeaponsInfo[i].Type == CTYPE_ELF_BOW)
		{
			return true;
		}
	}

	return false;
}

bool cCustomWeapons::CheckElfCrossbow(int ItemID)
{
	for (int i=0;i<MAX_CUSTOM_WEAPONS; i++)
	{
		if (this->m_CustomWeaponsInfo[i].Index == -1)
		{
			continue;
		}

		if (ItemID == this->m_CustomWeaponsInfo[i].ItemIndex && this->m_CustomWeaponsInfo[i].Type == CTYPE_ELF_CROSSBOW)
		{
			return true;
		}
	}

	return false;
}

bool cCustomWeapons::CheckMG(int ItemID)
{
	for (int i=0;i<MAX_CUSTOM_WEAPONS; i++)
	{
		//g_Console.AddMessage(5,"Index = %d ITemID = %d Type = %d",this->m_CustomWeaponsInfo[i].Index,this->m_CustomWeaponsInfo[i].ItemIndex,this->m_CustomWeaponsInfo[i].Type);
		if (this->m_CustomWeaponsInfo[i].Index == -1)
		{
			continue;
		}

		if (ItemID == this->m_CustomWeaponsInfo[i].ItemIndex && this->m_CustomWeaponsInfo[i].Type == CTYPE_MG)
		{
			return true;
		}
	}

	return false;
}

bool cCustomWeapons::CheckRF(int ItemID)
{
	for (int i=0;i<MAX_CUSTOM_WEAPONS; i++)
	{
		if (this->m_CustomWeaponsInfo[i].Index == -1)
		{
			continue;
		}

		if (ItemID == this->m_CustomWeaponsInfo[i].ItemIndex && this->m_CustomWeaponsInfo[i].Type == CTYPE_RF)
		{
			return true;
		}
	}

	return false;
}
