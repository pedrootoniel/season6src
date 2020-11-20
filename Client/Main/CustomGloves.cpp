#include "stdafx.h"
#include "CustomGloves.h"
#include "Console.h"
#include "Item.h"

cCustomGloves gCustomGloves;

cCustomGloves::cCustomGloves() // OK
{
	this->Init();
}

cCustomGloves::~cCustomGloves() // OK
{

}

void cCustomGloves::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_GLOVES;n++)
	{
		this->m_CustomGlovesInfo[n].Index = -1;
	}
}

void cCustomGloves::Load(CUSTOM_RF_GLOVES* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_GLOVES;n++)
	{
		this->SetInfo(info[n]);
	}
}

void cCustomGloves::SetInfo(CUSTOM_RF_GLOVES info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_GLOVES)
	{
		return;
	}

	this->m_CustomGlovesInfo[info.Index] = info;
}

CUSTOM_RF_GLOVES* cCustomGloves::GetInfoByID(int index)
{
	for (int i=0;i<MAX_CUSTOM_GLOVES; i++)
	{
		if (this->m_CustomGlovesInfo[i].Index == -1)
		{
			continue;
		}

		if (i == index)
		{
			return &this->m_CustomGlovesInfo[i];
		}
	}

	return 0;
}

#define sub_50D810_Addr		((int(__thiscall*)(int a1, int a2, int a3, int a4)) 0x50D810)
#define sub_512D50_Addr		((void*(__thiscall*)(void* a1)) 0x512D50)
#define sub_513C60_Addr		((char*(__thiscall*)(char *This, void *a2, int a3)) 0x513C60)
#define sub_5135F0_Addr		((char*(__thiscall*)(DWORD *This, int a2, int a3)) 0x5135F0)
#define sub_512D60_Addr		((void(*)()) 0x512D60)

void cCustomGloves::AssocGloves(char* This)
{
	for (int i=0;i<MAX_CUSTOM_GLOVES; i++)
	{
		if (this->m_CustomGlovesInfo[i].Index == -1)
		{
			continue;
		}

		//LoadItemModel(0x4BC,"Custom\\Item\\RFGloves\\","Sword41",-1);
		//LoadItemModel(0x610,"Custom\\Item\\RFGloves\\","Sword41L",-1);
		//LoadItemModel(0x611,"Custom\\Item\\RFGloves\\","Sword41R",-1);

		//LoadItemModel(this->m_CustomGlovesInfo[i].ItemIndex+ITEM_BASE_MODEL,"Custom\\Item\\RFGloves\\",this->m_CustomGlovesInfo[i].ModelName,-1);
		//LoadItemModel(this->m_CustomGlovesInfo[i].TextureLeftIndex,"Custom\\Item\\RFGloves\\",this->m_CustomGlovesInfo[i].TextureLeftName,-1);
		//LoadItemModel(this->m_CustomGlovesInfo[i].TextureRightIndex,"Custom\\Item\\RFGloves\\",this->m_CustomGlovesInfo[i].TextureRightName,-1);

		//LoadItemTexture(this->m_CustomGlovesInfo[i].ItemIndex+ITEM_BASE_MODEL,"Custom\\Item\\RFGloves\\",this->m_CustomGlovesInfo[i].ModelName,-1);
		//LoadItemTexture(this->m_CustomGlovesInfo[i].TextureLeftIndex,"Custom\\Item\\RFGloves\\",this->m_CustomGlovesInfo[i].TextureLeftName,-1);
		//LoadItemTexture(this->m_CustomGlovesInfo[i].TextureRightIndex,"Custom\\Item\\RFGloves\\",this->m_CustomGlovesInfo[i].TextureRightName,-1);

		sub_50D810_Addr((int)(This + 92), this->m_CustomGlovesInfo[i].ItemIndex+ITEM_BASE_MODEL, this->m_CustomGlovesInfo[i].TextureLeftIndex, this->m_CustomGlovesInfo[i].TextureRightIndex);
		void* v2 = sub_512D50_Addr(This + 92);
		char* v3 = sub_513C60_Addr(This, v2, (int)(This + 92));
		sub_5135F0_Addr((DWORD *)This + 15, (int)This, (int)v3);
		sub_512D60_Addr();
	}
}


bool cCustomGloves::CheckGloves(int ItemID)
{
	for (int i=0;i<MAX_CUSTOM_GLOVES; i++)
	{
		if (this->m_CustomGlovesInfo[i].Index == -1)
		{
			continue;
		}

		if (ItemID == this->m_CustomGlovesInfo[i].ItemIndex)
		{
			return true;
		}
	}
	return false;
}
