#include "stdafx.h"
#include "Item.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "CustomMessage.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "Offset.h"
#include "Util.h"
#include "Import.h"
#include "Defines.h"
#include "CustomPet.h"
#include "Fenrir.h"
#include "ItemPrice.h"
#include "Protect.h"
#include "ItemOption.h"
#include "TMemory.h"
#include "CustomGloves.h"
#include "User.h"
cItem gItem;
DWORD FixWingsExcellentGlow_Buff;
DWORD FixWingsLevelGlow_Buff;
DWORD FixWingsLevelGlow_Buff2;
bool IsItem(WORD ItemID, bool Preview)
{
	
	if( Preview )
	{
		ItemID -= ITEM_BASE_MODEL;
	}

	if (ItemID >= GET_ITEM(0, 0) && ItemID <= GET_ITEM(11, 255))
	{
		return true;
	}
	
	return false;
}
/*
Naked(FixWingsExcellentGlow)
{
	_asm
	{
		mov FixWingsExcellentGlow_Buff, ecx
		mov ecx, dword ptr ds:[FixWingsExcellentGlow_Buff + 0x30]
		mov FixWingsExcellentGlow_Buff, ecx
	}
	// ----
	if(		FixWingsExcellentGlow_Buff <= ITEM2(12, 50)
		||	IsItem(FixWingsExcellentGlow_Buff, true) )
	{
		_asm
		{
			mov FixWingsExcellentGlow_Buff, 0x0060F325
			jmp FixWingsExcellentGlow_Buff
		}
	}
	// ----
	_asm
	{
		mov FixWingsExcellentGlow_Buff, 0x0060EE95
		jmp FixWingsExcellentGlow_Buff
	}
}

Naked(FixWingsLevelGlow)
{
	_asm
	{
		mov FixWingsLevelGlow_Buff, ecx
		sub ecx, 0x1C9A
		mov FixWingsLevelGlow_Buff2, ecx
		mov dword ptr ss:[ebp-0x4ec], ecx
	}
	// ----
	if( IsItem(FixWingsLevelGlow_Buff, true) )
	{
		_asm
		{
			mov dword ptr ss:[ebp-4], 0
		}
	}
	// ----
	if( FixWingsLevelGlow_Buff2 > 136 )
	{
		_asm
		{
			mov FixWingsLevelGlow_Buff, 0x0060A3B0
			jmp FixWingsLevelGlow_Buff
		}
	}
	else
	{
		_asm
		{
			mov FixWingsLevelGlow_Buff, 0x0060A06B
			jmp FixWingsLevelGlow_Buff
		}
	}
}
*/
#define sub_56F210_Addr			((void(__cdecl*)(ObjectPreview *a4, ObjectModel *a5, int a6)) 0x0056F210)
#define sub_4CD7F0_Addr			((int(__thiscall*)(ObjectModel *a5, signed int a2)) 0x004CD7F0)
#define sub_545030_Addr			((int(__thiscall*)(void *This, int a2, int a3, DWORD *a4, char a5)) 0x00545030)
void __cdecl sub_56F210(ObjectPreview *a4, ObjectModel *a5, int a6)
{
	//g_Console.AddMessage(3,"kek = %d",a6);
	//g_Console.AddMessage(5,"%d - %d",a4->aIndex, gObjUser.lpViewPlayer->aIndex);
	if (*(DWORD*)(MAIN_SCREEN_STATE) == GameProcess)
	{
		// && a4->aIndex == gObjUser.lpViewPlayer->aIndex
		if (strcmp(a4->Name,"WhiteBlood") == 0)
		//if (a4->aIndex == gObjUser.lpViewPlayer->aIndex)
		{
		
			//g_Console.AddMessage(5,"type = %d|%d [%s - %s]",a4->m_Model.ObjectType,a5->ObjectType,a4->Name,gObjUser.lpViewPlayer->Name);
			gObjUser.lpViewPlayer->m_Model.Unknown156 = 1.0;
			gObjUser.lpViewPlayer->m_Model.Unknown160 = 1.0;
			gObjUser.lpViewPlayer->m_Model.Unknown164 = 1.0;
			//a5->VecPos.X+=5;

			int v8 = sub_4CDA10_Addr();
			int v554 = sub_969C50_Addr(v8, gObjUser.lpViewPlayer->m_Model.Unknown48);

			int v276 = sub_4CD7F0_Addr(&gObjUser.lpViewPlayer->m_Model,0);

			VAngle test;
			test.X = 0.0;
			test.Y = -18.0;
			test.Z = 50;

			DWORD v556;

			//a5->Angle.X+=10;

			float R = gObjUser.lpViewPlayer->m_Model.Unknown156;
			float G = gObjUser.lpViewPlayer->m_Model.Unknown160;
			float B = gObjUser.lpViewPlayer->m_Model.Unknown164;

			//pCustomEffGet2(v554,v276)
			sub_545030_Addr((LPVOID)v554,v276,(int)&test,&v556,1);
			pPlayDynamicEffect(32002,&v556,(int)&gObjUser.lpViewPlayer->m_Model.Angle, &gObjUser.lpViewPlayer->m_Model.Unknown156, 3, 1.0, 0);
			test.X = 0.0;
			test.Y = 0.0;
			test.Z = 70.0;
			sub_545030_Addr((LPVOID)v554,v276,(int)&test,&v556,1);
			pPlayDynamicEffect(32002,&v556,(int)&gObjUser.lpViewPlayer->m_Model.Angle, &gObjUser.lpViewPlayer->m_Model.Unknown156, 3, 1.0, 0);
			test.X = 0.0;
			test.Y = 18.0;
			test.Z = 50.0;
			sub_545030_Addr((LPVOID)v554,v276,(int)&test,&v556,1);
			pPlayDynamicEffect(32002,&v556,(int)&gObjUser.lpViewPlayer->m_Model.Angle, &gObjUser.lpViewPlayer->m_Model.Unknown156, 3, 1.0, 0);

			gObjUser.lpViewPlayer->m_Model.Unknown156 = R;
			gObjUser.lpViewPlayer->m_Model.Unknown160 = G;
			gObjUser.lpViewPlayer->m_Model.Unknown164 = B;
		}
	}

	sub_56F210_Addr(a4,a5,a6);
}


void InitItem() // OK
{
	//SetCompleteHook(0xE8,0x404570+0x30D,&sub_56F210);
	//SetCompleteHook(0xE8,0x48E120+0x44C,&sub_56F210);
	//SetCompleteHook(0xFF,0x57D260+0x29F,&sub_56F210); // Пока непонятно
	//SetCompleteHook(0xE8,0x57D260+0x2B3,&sub_56F210); // При наведении на объект

	/*
	// ----
	SetRange((LPVOID)0x0060EE88, 7, ASM::NOP);
	SetOp((LPVOID)0x0060EE88, FixWingsExcellentGlow, ASM::JMP);
	// ----
	SetRange((LPVOID)0x0060A04F, 28, ASM::NOP);
	SetOp((LPVOID)0x0060A04F, FixWingsLevelGlow, ASM::JMP);
	//gItemOption.Load(gProtect.m_MainInfo.CustomItemOption);
	*/
	gItemPrice.Load(gProtect.m_MainInfo.CustomItemPrice);

	SetCompleteHook(0xFF,0x00633FCB,&ItemModelLoad);

	SetCompleteHook(0xFF,0x00633FE3,&ItemTextureLoad);

	SetCompleteHook(0xFF,0x0057AC07,&GetItemColor);

	SetCompleteHook(0xFF,0x006083B9,&GetItemColor);

	SetCompleteHook(0xFF,0x00777FF2,&ItemTextZeroMemory);

	SetCompleteHook(0xFF,0x00778003,&ItemTextZeroMemory);

	SetCompleteHook(0xE9,0x005F7C2F,&ItemSocketName1);
	
	SetCompleteHook(0xE9,0x00968137,&ItemSocketName2);
	
	SetCompleteHook(0xE9,0x00968157,&ItemSocketName3);

	//SetCompleteHook(0xFF, 0x5087E6, &GetPrice); // Fix ChaosBox item price
	SetCompleteHook(0xFF, 0x58B78F, &GetPrice);
	SetCompleteHook(0xFF, 0x58B7A6, &GetPrice);
	SetCompleteHook(0xFF, 0x58B7FC, &GetPrice);
	SetCompleteHook(0xFF, 0x5C1A7F, &GetPrice);
	SetCompleteHook(0xFF, 0x5C2117, &GetPrice);
	SetCompleteHook(0xFF, 0x5C4268, &GetPrice);
	SetCompleteHook(0xFF, 0x7AF956, &GetPrice);
	SetCompleteHook(0xFF, 0x7E4449, &GetPrice);
	SetCompleteHook(0xFF, 0x7E4497, &GetPrice);
	SetCompleteHook(0xFF, 0x7E44EC, &GetPrice);
	SetCompleteHook(0xFF, 0x846CE9, &GetPrice);
	SetCompleteHook(0xFF, 0x846D63, &GetPrice);
	SetCompleteHook(0xFF, 0x847713, &GetPrice);
	SetCompleteHook(0xFF, 0x968550, &GetPrice);

	SetOp((LPVOID)0x4FA5E8,SetOptionText, ASM::CALL);
	SetOp((LPVOID)0x7E57DB,SetOptionText, ASM::CALL);
	/*
	// Fix Socket + joh
	SetByte(0x008385E4, 0xEB); // 
	SetByte(0x00838647, 0xEB); //
	SetByte(0x00838658, 0xEB); //
	SetByte(0x005BD939, 0xEB); // 
	SetByte(0x007E1DE1, 0xEB); // 
	SetRange(0x007E5429, 6, ASM::NOP); // fix
	//console.Log(FUNC, "Loaded");
	*/
	SetRange(0x0054F292,0x10,ASM::NOP);
	SetCompleteHook(0xE9,0x0054F292,&MGSwordPosition1);

	SetRange(0x00550187,0x11,ASM::NOP);
	SetCompleteHook(0xE9,0x00550187,&MGSwordPosition2);

	SetRange(0x00550497,0x11,ASM::NOP);
	SetCompleteHook(0xE9,0x00550497,&MGSwordPosition3);

	SetRange(0x00783DA4,0x6B,ASM::NOP);
	SetCompleteHook(0xE9,0x00783DA4,&MGSwordWizDmg);
	//SetByte(0x00783DCF+2,51);
}

void InitJewel() // OK
{
	SetCompleteHook(0xE9,0x0058E650,&JewelSetSalePrice);

	SetCompleteHook(0xE9,0x008386B5,&JewelCheckApplyItem);

	SetCompleteHook(0xE9,0x005C4025,&JewelCheckIndex1);

	SetCompleteHook(0xE9,0x005F7C3B,&JewelCheckIndex2);

	SetCompleteHook(0xE9,0x0064B701,&JewelCheckIndex3);

	SetCompleteHook(0xE9,0x008383A0,&JewelCheckIndex4);

	SetCompleteHook(0xE9,0x005F3F7E,&JewelCheckModelIndex1);

	SetCompleteHook(0xE9,0x005F4A60,&JewelCheckModelIndex2);
}

void InitWing() // OK
{
	SetCompleteHook(0xE9,0x00580047,&WingMakePreviewCharSet);

	SetCompleteHook(0xE9,0x00609FDF,&WingDisableLevelGlow);

	SetCompleteHook(0xE9,0x007E67FC,&WingSetIncDamage);
	
	SetCompleteHook(0xE9,0x007E687B,&WingSetDecDamage);

	SetCompleteHook(0xE9,0x0058C1E7,&WingSetDefense);

	SetCompleteHook(0xE9,0x0058C273,&WingSetExtraDefense);

	SetCompleteHook(0xE9,0x0058DBDF,&WingSetOption);

	SetCompleteHook(0xE9,0x0058CCE9,&WingSetNewOption);

	SetCompleteHook(0xE9,0x005885AA,&WingSetModelType);

	SetCompleteHook(0xE9,0x005666F7,&WingSetEffect);

	SetCompleteHook(0xE9,0x0050848B,&WingCheckIndex1);

	SetCompleteHook(0xE9,0x00587C3A,&WingCheckIndex2);

	SetCompleteHook(0xE9,0x0058B996,&WingCheckIndex3);

	SetCompleteHook(0xE9,0x0058C520,&WingCheckIndex4);

	SetCompleteHook(0xE9,0x0058CF4A,&WingCheckIndex5);

	SetCompleteHook(0xE9,0x0058F451,&WingCheckIndex6);

	SetCompleteHook(0xE9,0x0058F613,&WingCheckIndex7);

	SetCompleteHook(0xE9,0x0058F7D6,&WingCheckIndex8);

	SetCompleteHook(0xE9,0x005B5ADD,&WingCheckIndex9);

	SetCompleteHook(0xE9,0x005C23B1,&WingCheckIndex10);

	SetCompleteHook(0xE9,0x005C2DB7,&WingCheckIndex11);

	SetCompleteHook(0xE9,0x005C4191,&WingCheckIndex12);

	SetCompleteHook(0xE9,0x005C4504,&WingCheckIndex13);

	SetCompleteHook(0xE9,0x005C8304,&WingCheckIndex14);

	SetCompleteHook(0xE9,0x007DDB34,&WingCheckIndex15);

	SetCompleteHook(0xE9,0x007E78F7,&WingCheckIndex16);

	SetCompleteHook(0xE9,0x00831A79,&WingCheckIndex17);

	SetCompleteHook(0xE9,0x0083847B,&WingCheckIndex18);

	SetCompleteHook(0xE9,0x00866112,&WingCheckIndex19);

	SetCompleteHook(0xE9,0x00876F13,&WingCheckIndex20);

	SetCompleteHook(0xE9,0x005C9DA4,&WingCheckIndex21);

	SetCompleteHook(0xE9,0x0056562C,&WingCheckModelIndex1); 
	
	SetCompleteHook(0xE9,0x005F497A,&WingCheckModelIndex2); 
	
	SetCompleteHook(0xE9,0x0060EE4D,&WingCheckModelIndex3); //Exc Glow
}

void ItemModelLoad() // OK
{
	((void(*)())0x00617D30)();

	//pLoadModel(ITEM2 (12, 220), "Data\\Item", "FWing214", -1 );
    //pLoadModel(ITEM2 (12, 221), "Data\\Item", "FWing405", -1 );
	pLoadModel(PetWhiteTiger, "Data\\Skill\\", "fenril_5", -1);
	pLoadModel(PetHullWolf, "Data\\Skill\\", "fenril_6", -1);
	pLoadModel(PetBeast, "Data\\Skill\\", "fenril_7", -1);

	for (int i=0;i<MAX_CUSTOM_GLOVES; i++)
	{
		if (gCustomGloves.m_CustomGlovesInfo[i].Index == -1)
		{
			continue;
		}

		LoadItemModel(gCustomGloves.m_CustomGlovesInfo[i].ItemIndex+ITEM_BASE_MODEL,"Item\\",gCustomGloves.m_CustomGlovesInfo[i].ModelName,-1);
		LoadItemModel(gCustomGloves.m_CustomGlovesInfo[i].TextureLeftIndex,"Item\\",gCustomGloves.m_CustomGlovesInfo[i].TextureLeftName,-1);
		LoadItemModel(gCustomGloves.m_CustomGlovesInfo[i].TextureRightIndex,"Item\\",gCustomGloves.m_CustomGlovesInfo[i].TextureRightName,-1);
	}

	for(int n=0;n < MAX_CUSTOM_JEWEL;n++)
	{
		if(gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemModel((gCustomJewel.m_CustomJewelInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomJewel.m_CustomJewelInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemModel((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomWing.m_CustomWingInfo[n].ModelName,-1);
			
		}
	}

	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		int ModelID = ITEM2(gCustomItem.m_CustomItemInfo[n].ItemType, gCustomItem.m_CustomItemInfo[n].ItemIndex);
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemModel((ModelID),((gCustomItem.m_CustomItemInfo[n].ItemType >=7 && gCustomItem.m_CustomItemInfo[n].ItemType < 12)?"Player\\":"Item\\"),gCustomItem.m_CustomItemInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_PET_ITEM;n++)
	{
		int ModelID = ITEM2(gCustomPet2.m_CustomPetInfo[n].ItemType, gCustomPet2.m_CustomPetInfo[n].ItemIndex);
		if(gCustomPet2.m_CustomPetInfo[n].Index != -1)
		{
			LoadItemModel((ModelID),"Item\\",gCustomPet2.m_CustomPetInfo[n].ModelName,-1);		
		}
	}
}

void ItemTextureLoad() // OK
{
	((void(*)())0x0061AED0)();
    //pLoadTexture ( ITEM2 ( 12, 220 ), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE );
    //pLoadTexture ( ITEM2 ( 12, 221 ), "Item\\", GL_REPEAT, GL_NEAREST, GL_TRUE );
	pLoadTexture(PetWhiteTiger, "Skill\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(PetHullWolf, "Skill\\", GL_REPEAT, GL_NEAREST, GL_TRUE);
	pLoadTexture(PetBeast, "Skill\\", GL_REPEAT, GL_NEAREST, GL_TRUE);

	for (int i=0;i<MAX_CUSTOM_GLOVES; i++)
	{
		if (gCustomGloves.m_CustomGlovesInfo[i].Index == -1)
		{
			continue;
		}
		LoadItemTexture(gCustomGloves.m_CustomGlovesInfo[i].ItemIndex+ITEM_BASE_MODEL,"Item\\",gCustomGloves.m_CustomGlovesInfo[i].ModelName,-1);
		LoadItemTexture(gCustomGloves.m_CustomGlovesInfo[i].TextureLeftIndex,"Item\\",gCustomGloves.m_CustomGlovesInfo[i].TextureLeftName,-1);
		LoadItemTexture(gCustomGloves.m_CustomGlovesInfo[i].TextureRightIndex,"Item\\",gCustomGloves.m_CustomGlovesInfo[i].TextureRightName,-1);
	}

	for(int n=0;n < MAX_CUSTOM_JEWEL;n++)
	{
		if(gCustomJewel.m_CustomJewelInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomJewel.m_CustomJewelInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomJewel.m_CustomJewelInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_WING;n++)
	{
		if(gCustomWing.m_CustomWingInfo[n].Index != -1)
		{
			LoadItemTexture((gCustomWing.m_CustomWingInfo[n].ItemIndex+ITEM_BASE_MODEL),"Item\\",gCustomWing.m_CustomWingInfo[n].ModelName,-1);
		}
	}

	for(int n=0;n < MAX_CUSTOM_ITEM;n++)
	{
		int ModelID = ITEM2(gCustomItem.m_CustomItemInfo[n].ItemType, gCustomItem.m_CustomItemInfo[n].ItemIndex);
		if(gCustomItem.m_CustomItemInfo[n].Index != -1)
		{
			LoadItemTexture((ModelID),((gCustomItem.m_CustomItemInfo[n].ItemType >= 7 && gCustomItem.m_CustomItemInfo[n].ItemType < 12 )?"Player\\":"Item\\"),gCustomItem.m_CustomItemInfo[n].ModelName,-1);
		}
	}
	for(int n=0;n < MAX_PET_ITEM;n++)
	{
		int ModelID = ITEM2(gCustomPet2.m_CustomPetInfo[n].ItemType, gCustomPet2.m_CustomPetInfo[n].ItemIndex);
		if(gCustomPet2.m_CustomPetInfo[n].Index != -1)
		{
			LoadItemTexture((ModelID),"Item\\",gCustomPet2.m_CustomPetInfo[n].ModelName,-1);		
		}
	}
}

void LoadItemModel(int index,char* folder,char* name,int value) // OK
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,char*,int))0x00614D10)(index,path,name,value);
}

void LoadItemTexture(int index,char* folder,char* name,int value) // OK
{
	if(name[0] == 0)
	{
		return;
	}

	char path[MAX_PATH] = {0};

	wsprintf(path,"Data\\%s",folder);

	((void(*)(int,char*,int,int,int))0x00614710)(index,folder,0x2901,0x2600,0x01);
}

void GetItemColor(DWORD a,DWORD b,DWORD c,DWORD d,DWORD e) // OK
{
	if(gCustomItem.GetCustomItemColor(a,(float*)d) == 0)
	{
		((void(*)(DWORD,DWORD,DWORD,DWORD,DWORD))0x005F8C50)(a,b,c,d,e);
	}
}

BOOL CheckSocketItem(DWORD address,DWORD this_pointer) // OK
{
	for(int n=0;n < 5;n++)
	{
		if(*(BYTE*)(address+(0x4A+n)) != 0xFF)
		{
			return 1;
		}
	}

	return ((BOOL(__thiscall*)(void*,WORD))0x00968180)((void*)this_pointer,(*(WORD*)(address+0x00)));
}

__declspec(naked) void ItemTextZeroMemory() // OK
{
	static DWORD ItemTextAddress1 = 0x009CF630;

	__asm
	{
		Mov Dword Ptr Ss:[Esp+0x0C],0xF0
		Jmp [ItemTextAddress1]
	}
}

__declspec(naked) void ItemSocketName1() // OK
{
	static DWORD ItemSocketNameAddress1 = 0x005F7C35;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Mov Byte Ptr Ds:[Ecx+0x49],Al
		Push 0x05
		Mov Edx,Dword Ptr Ss:[Ebp+0x0C]
		Add Edx,0x07
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x04]
		Add Eax,0x4A
		Push Eax
		Call [MemoryCpy]
		Add Esp,0x0C
		Jmp [ItemSocketNameAddress1]
	}
}

__declspec(naked) void ItemSocketName2() // OK
{
	static DWORD ItemSocketNameAddress1 = 0x00968146;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x04]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Push Ecx
		Call [CheckSocketItem]
		Add Esp,0x08
		Jmp [ItemSocketNameAddress1]
	}
}

__declspec(naked) void ItemSocketName3() // OK
{
	static DWORD ItemSocketNameAddress1 = 0x0096816C;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x04]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Sub Ecx,0x6E
		Push Ecx
		Call [CheckSocketItem]
		Add Esp,0x08
		Jmp [ItemSocketNameAddress1]
	}
}

__declspec(naked) void JewelSetSalePrice() // OK
{
	static DWORD JewelSetSalePriceAddress1 = 0x0058FB4B;
	static DWORD JewelSetSalePriceAddress2 = 0x0058E656;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::GetCustomJewelSalePrice]
		Mov Dword Ptr Ss:[Ebp-0x10],Eax
		Mov Dword Ptr Ss:[Ebp-0x0C],0x00
		Jmp [JewelSetSalePriceAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [JewelSetSalePriceAddress2]
	}
}

__declspec(naked) void JewelCheckApplyItem() // OK
{
	static DWORD JewelCheckApplyItemAddress1 = 0x008386C1;
	static DWORD JewelCheckApplyItemAddress2 = 0x008386BB;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp-0x20]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Mov Ecx,Dword Ptr Ss:[Ebp-0x20]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Mov Eax,Dword Ptr Ss:[Ebp-0x2C]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Push Edx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelApplyItem]
		Test Eax,Eax
		Je EXIT
		Mov Byte Ptr Ss:[Ebp-0x35],0x01
		Jmp [JewelCheckApplyItemAddress1]
		EXIT:
		Movzx Eax,Byte Ptr Ss:[Ebp-0x35]
		Test Eax,Eax
		Jmp [JewelCheckApplyItemAddress2]
	}
}

__declspec(naked) void JewelCheckIndex1() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x005C404E;
	static DWORD JewelCheckIndexAddress2 = 0x005C402B;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x10]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x10]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex2() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x005F7C71;
	static DWORD JewelCheckIndexAddress2 = 0x005F7C42;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x08]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x08],0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex3() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x0064B749;
	static DWORD JewelCheckIndexAddress2 = 0x0064B708;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x14]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x14],0x1C0D
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckIndex4() // OK
{
	static DWORD JewelCheckIndexAddress1 = 0x00838411;
	static DWORD JewelCheckIndexAddress2 = 0x008383A6;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp-0x20]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp-0x20]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [JewelCheckIndexAddress2]
	}
}

__declspec(naked) void JewelCheckModelIndex1() // OK
{
	static DWORD JewelCheckModelIndexAddress1 = 0x005F439E;
	static DWORD JewelCheckModelIndexAddress2 = 0x005F3F88;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x18]
		Mov Ecx,Dword Ptr Ds:[Eax+0x30]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckModelIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp-0x18]
		Cmp Dword Ptr Ds:[Eax+0x30],0x20A0
		Jmp [JewelCheckModelIndexAddress2]
	}
}

__declspec(naked) void JewelCheckModelIndex2() // OK
{
	static DWORD JewelCheckModelIndexAddress1 = 0x005F4B52;
	static DWORD JewelCheckModelIndexAddress2 = 0x005F4A6A;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x18]
		Mov Ecx,Dword Ptr Ds:[Eax+0x30]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomJewel
		Call [CCustomJewel::CheckCustomJewelByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [JewelCheckModelIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp-0x18]
		Cmp Dword Ptr Ds:[Eax+0x30],0x20A0
		Jmp [JewelCheckModelIndexAddress2]
	}
}

__declspec(naked) void WingMakePreviewCharSet() // OK
{
	static DWORD WingMakePreviewCharSetAddress1 = 0x0058009E;
	static DWORD WingMakePreviewCharSetAddress2 = 0x0058004E;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x10]
		Sar Edx,0x01
		And Edx,0x0FF
		Test Edx,Edx
		Je EXIT
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Ecx,Byte Ptr Ds:[Eax+0x10]
		Sar Ecx,0x01
		And Ecx,0x0FF
		Sub Ecx,0x01
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWing]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Eax,Byte Ptr Ds:[Edx+0x10]
		Sar Eax,0x01
		And Eax,0x0FF
		Sub Eax,0x01
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingItem]
		Add Eax,ITEM_BASE_MODEL
		Mov Ecx,Dword Ptr Ss:[Ebp-0x10]
		Mov Word Ptr Ds:[Ecx+0x208],Ax
		Jmp [WingMakePreviewCharSetAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x0C]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x10]
		Jmp [WingMakePreviewCharSetAddress2]
	}
}

__declspec(naked) void WingDisableLevelGlow() // OK
{
	static DWORD WingDisableLevelGlowAddress1 = 0x0060A3B0;
	static DWORD WingDisableLevelGlowAddress2 = 0x00609FE8;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x0C]
		Mov Dword Ptr Ss:[Ebp-0x4EC],Eax
		Sub Eax,ITEM_BASE_MODEL
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Dword Ptr Ss:[Ebp-0x04],0x00
		Jmp [WingDisableLevelGlowAddress1]
		EXIT:
		Jmp [WingDisableLevelGlowAddress2]
	}
}

__declspec(naked) void WingSetIncDamage() // OK
{
	static DWORD WingSetIncDamageAddress1 = 0x007E6803;
	static DWORD WingSetIncDamageAddress2 = 0x007E6803;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x1C]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp+0x1C]
		Movsx Eax,Word Ptr Ds:[Edx]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x24]
		Push Ecx
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingIncDamage]
		Mov Edx,Eax
		Push Edx
		Jmp [WingSetIncDamageAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x24]
		Add Edx,0x20
		Push Edx
		Jmp [WingSetIncDamageAddress2]
	}
}

__declspec(naked) void WingSetDecDamage() // OK
{
	static DWORD WingSetDecDamageAddress1 = 0x007E6883;
	static DWORD WingSetDecDamageAddress2 = 0x007E6883;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x1C]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp+0x1C]
		Movsx Eax,Word Ptr Ds:[Edx]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x24]
		Push Ecx
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingDecDamage]
		Push Eax
		Jmp [WingSetDecDamageAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x24]
		Lea Eax,Dword Ptr Ds:[Edx+Edx+0x19]
		Push Eax
		Jmp [WingSetDecDamageAddress2]
	}
}

__declspec(naked) void WingSetDefense() // OK
{
	static DWORD WingSetDefenseAddress1 = 0x0058C22B;
	static DWORD WingSetDefenseAddress2 = 0x0058C1ED;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Mov Eax,Dword Ptr Ss:[Ebp-0x08]
		Push Eax
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingDefense]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Word Ptr Ds:[Ecx+0x0E]
		Add Edx,Eax
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Eax+0x0E],Dx
		Jmp [WingSetDefenseAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [WingSetDefenseAddress2]
	}
}

__declspec(naked) void WingSetExtraDefense() // OK
{
	static DWORD WingSetExtraDefenseAddress1 = 0x0058C31A;
	static DWORD WingSetExtraDefenseAddress2 = 0x0058C279;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Cmp Edx,0x0A
		Jnz NEXT1
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x01
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT1:
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Cmp Edx,0x0B
		Jnz NEXT2
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x03
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT2:
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Cmp Edx,0x0C
		Jnz NEXT3
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x06
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT3:
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Cmp Edx,0x0D
		Jnz NEXT4
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x0A
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT4:
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Cmp Edx,0x0E
		Jnz NEXT5
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x0F
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		Jmp [WingSetExtraDefenseAddress1]
		NEXT5:
		Mov Edx,Dword Ptr Ss:[Ebp-0x08]
		Cmp Edx,0x0F
		Jnz NEXT6
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Word Ptr Ds:[Eax+0x0E]
		Add Ecx,0x15
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Word Ptr Ds:[Edx+0x0E],Cx
		NEXT6:
		Jmp [WingSetExtraDefenseAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingSetExtraDefenseAddress2]
	}
}

__declspec(naked) void WingSetOption() // OK
{
	static DWORD WingSetOptionAddress1 = 0x0058DCAD;
	static DWORD WingSetOptionAddress2 = 0x0058DBE5;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Eax,Dword Ptr Ss:[Ebp-0x14]
		Sar Eax,0x04
		And Eax,0x01
		Je NEXT1
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push 1
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionValue]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x1C]
		Imul Eax,Ecx
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr DS:[Edx+Ecx+0x36],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 1
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Word Ptr Ds:[Ecx+Edx*0x02+0x26],Ax
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		Jmp [WingSetOptionAddress1]
		NEXT1:
		Mov Eax,Dword Ptr Ss:[Ebp-0x14]
		Sar Eax,0x05
		And Eax,0x01
		Je NEXT2
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push 2
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionValue]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x1C]
		Imul Eax,Ecx
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr DS:[Edx+Ecx+0x36],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 2
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Word Ptr Ds:[Ecx+Edx*0x02+0x26],Ax
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		Jmp [WingSetOptionAddress1]
		NEXT2:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push 0
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionValue]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x1C]
		Imul Eax,Ecx
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr DS:[Edx+Ecx+0x36],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 0
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Word Ptr Ds:[Ecx+Edx*0x02+0x26],Ax
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		Jmp [WingSetOptionAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingSetOptionAddress2]
	}
}

__declspec(naked) void WingSetNewOption() // OK
{
	static DWORD WingSetNewOptionAddress1 = 0x0058CDF7;
	static DWORD WingSetNewOptionAddress2 = 0x0058CCEF;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Mov Edx,Dword Ptr Ss:[Ebp-0x14]
		And Edx,1
		Je NEXT1
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push 0
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr Ds:[Edx+Ecx+0x36],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 0
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Word Ptr Ds:[Ecx+Edx*0x02+0x26],Ax
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		NEXT1:
		Mov Edx,Dword Ptr Ss:[Ebp-0x14]
		Sar Edx,1
		And Edx,1
		Je NEXT2
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push 1
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr Ds:[Edx+Ecx+0x36],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 1
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Word Ptr Ds:[Ecx+Edx*0x02+0x26],Ax
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		NEXT2:
		Mov Edx,Dword Ptr Ss:[Ebp-0x14]
		Sar Edx,2
		And Edx,1
		Je NEXT3
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push 2
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr Ds:[Edx+Ecx+0x36],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 2
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Word Ptr Ds:[Ecx+Edx*0x02+0x26],Ax
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		NEXT3:
		Mov Edx,Dword Ptr Ss:[Ebp-0x14]
		Sar Edx,3
		And Edx,1
		Je NEXT4
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push 3
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionValue]
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Ecx,Byte Ptr Ds:[Edx+0x25]
		Mov Byte Ptr Ds:[Edx+Ecx+0x36],Al
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push 3
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::GetCustomWingNewOptionIndex]
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movzx Edx,Byte Ptr Ds:[Ecx+0x25]
		Mov Word Ptr Ds:[Ecx+Edx*0x02+0x26],Ax
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Cl,Byte Ptr Ds:[Eax+0x25]
		Add Cl,1
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Mov Byte Ptr Ds:[Edx+0x25],Cl
		NEXT4:
		Jmp [WingSetNewOptionAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingSetNewOptionAddress2]
	}
}

__declspec(naked) void WingSetModelType() // OK
{
	static DWORD WingSetModelTypeAddress1 = 0x005885D0;
	static DWORD WingSetModelTypeAddress2 = 0x005885B6;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x6C]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Mov Dword Ptr Ss:[Ebp-0xB0],Ecx
		Mov Edx,Dword Ptr Ss:[Ebp-0xB0]
		Sub Edx,ITEM_BASE_MODEL
		Push 1
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByModelType]
		Test Eax,Eax
		Je EXIT
		Jmp [WingSetModelTypeAddress1]
		EXIT:
		Jmp [WingSetModelTypeAddress2]
	}
}

__declspec(naked) void WingSetEffect() // OK
{
	static DWORD WingSetColorAddress1 = 0x0056EECF;
	static DWORD WingSetColorAddress2 = 0x00566701;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x70]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x6C]
		Push Ecx
		Lea Edx,Dword Ptr Ss:[Ebp-0x18]
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x68]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x530]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomWingEffect
		Call [CCustomWingEffect::SetWingEffect]
		Test Eax,Eax	
		Mov Eax,Dword Ptr Ss:[Ebp-0x70]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x6C]
		Push Ecx
		Lea Edx,Dword Ptr Ss:[Ebp-0x18]
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x68]
		Push Eax
		Mov Ecx,Dword Ptr Ss:[Ebp-0x530]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gDynamicWingEffect
		Call [CDynamicWingEffect::DynamicWingEffect]
		Je EXIT
		Jmp [WingSetColorAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x530],0xA9D
		Jmp [WingSetColorAddress2]
	}
}

__declspec(naked) void WingCheckIndex1() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005084C2;
	static DWORD WingCheckIndexAddress2 = 0x00508492;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x14]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x14],0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex2() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00587C9A;
	static DWORD WingCheckIndexAddress2 = 0x00587C40;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex3() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058BA40;
	static DWORD WingCheckIndexAddress2 = 0x0058B99C;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex4() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058C549;
	static DWORD WingCheckIndexAddress2 = 0x0058C526;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex5() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058CF65;
	static DWORD WingCheckIndexAddress2 = 0x0058CF50;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex6() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058F46D;
	static DWORD WingCheckIndexAddress2 = 0x0058F457;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex7() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058F62E;
	static DWORD WingCheckIndexAddress2 = 0x0058F619;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex8() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x0058F807;
	static DWORD WingCheckIndexAddress2 = 0x0058F7DC;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex9() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005B5C91;
	static DWORD WingCheckIndexAddress2 = 0x005B5AE9;

	_asm
	{
		Mov Eax,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Movsx Ecx,Word Ptr Ds:[Eax+0x152D]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ds:[MAIN_CHARACTER_STRUCT]
		Movsx Ecx,Word Ptr Ds:[Eax+0x152D]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex10() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005C2400;
	static DWORD WingCheckIndexAddress2 = 0x005C23B7;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex11() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005C2DC9;
	static DWORD WingCheckIndexAddress2 = 0x005C2DBE;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp+0x08],0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex12() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005C41BA;
	static DWORD WingCheckIndexAddress2 = 0x005C4197;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x10]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x10]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex13() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005C452D;
	static DWORD WingCheckIndexAddress2 = 0x005C450A;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x10]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x10]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex14() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005C86BB;
	static DWORD WingCheckIndexAddress2 = 0x005C830A;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex15() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x007DDB6B;
	static DWORD WingCheckIndexAddress2 = 0x007DDB3A;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x0C]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x0C]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex16() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x007E7926;
	static DWORD WingCheckIndexAddress2 = 0x007E7901;

	_asm
	{
		Movsx Ecx,Word Ptr Ss:[Ebp+0x08]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Movsx Ecx,Word Ptr Ss:[Ebp+0x08]
		Cmp Ecx,0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex17() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00831AE6;
	static DWORD WingCheckIndexAddress2 = 0x00831A7F;

	_asm
	{
		Mov Edx,Dword Ptr Ss:[Ebp-0x28]
		Movsx Eax,Word Ptr Ds:[Edx]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Edx,Dword Ptr Ss:[Ebp-0x28]
		Movsx Eax,Word Ptr Ds:[Edx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex18() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x008384B5;
	static DWORD WingCheckIndexAddress2 = 0x00838482;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x3C]
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp-0x3C],0x182B
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex19() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00866177;
	static DWORD WingCheckIndexAddress2 = 0x00866118;

	_asm
	{
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Push Edx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Ecx,Dword Ptr Ss:[Ebp+0x08]
		Movsx Edx,Word Ptr Ds:[Ecx]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex20() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x00876FAE;
	static DWORD WingCheckIndexAddress2 = 0x00876F19;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp-0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckIndex21() // OK
{
	static DWORD WingCheckIndexAddress1 = 0x005C9DFF;
	static DWORD WingCheckIndexAddress2 = 0x005C9DAD;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Movsx Ecx,Word Ptr Ds:[Eax]
		Mov Dword Ptr Ss:[Ebp-0x04],Ecx
		Jmp [WingCheckIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex1() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x00565635;
	static DWORD WingCheckModelIndexAddress2 = 0x00565633;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x1C]
		Sub Eax,ITEM_BASE_MODEL
		Push Eax
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		Cmp Dword Ptr Ss:[Ebp+0x1C],0x1CBE
		Jmp [WingCheckModelIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex2() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x005F49B0;
	static DWORD WingCheckModelIndexAddress2 = 0x005F4984;

	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp-0x18]
		Mov Ecx,Dword Ptr Ds:[Eax+0x30]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp-0x18]
		Cmp Dword Ptr Ds:[Eax+0x30],0x1CBE
		Jmp [WingCheckModelIndexAddress2]
	}
}

__declspec(naked) void WingCheckModelIndex3() // OK
{
	static DWORD WingCheckModelIndexAddress1 = 0x0060F325;
	static DWORD WingCheckModelIndexAddress2 = 0x0060EE57;
	//SetCompleteHook(0xE9,0x0060EE4D,&WingCheckModelIndex3); //Exc Glow
	_asm
	{
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Mov Ecx,Dword Ptr Ds:[Eax+0x30]
		Sub Ecx,ITEM_BASE_MODEL
		Push Ecx
		Lea Ecx,gCustomWing
		Call [CCustomWing::CheckCustomWingByItem]
		Test Eax,Eax
		Je EXIT
		Jmp [WingCheckModelIndexAddress1]
		EXIT:
		Mov Eax,Dword Ptr Ss:[Ebp+0x08]
		Cmp Dword Ptr Ds:[Eax+0x30],0x1CBE
		Jmp [WingCheckModelIndexAddress2]
	}
}
bool IsCustomWings(WORD ItemID, bool Preview)
{
	
	if( Preview )
	{
		ItemID -= ITEM_BASE_MODEL;
	}

	if (ItemID >= GET_ITEM(12, 180) && ItemID <= GET_ITEM(12, 231))
	{
		return true;
	}
	
	return false;
}
bool IsCustomItem(WORD ItemID, bool Preview)
{
	
	if( Preview )
	{
		ItemID -= ITEM_BASE_MODEL;
	}

	if (ItemID >= GET_ITEM(0, 1) && ItemID <= GET_ITEM(11, 200))
	{
		return true;
	}
	
	return false;
}

static __int64	GetPrice(ObjectItem * lpItem, int Mode)
{
	__int64 Money				= -1;
	__int64 StartMoney			= pSetItemPrice(lpItem, Mode);
	__int64 NewOptionAddMoney	= 0;
	int Divisor					= 3;
	// ----
	/*
	CUSTOM_DONATEITEM info;
	;

	////console.Log("","%d",info.ItemIndex);
	if (gDonateShop.GetItemInfo(lpItem,&info) != NULL)
	{
		if (Mode == 1) 
		{
			Money = info.SellPrice;
		}
		else
		{
			Money = info.BuyPrice;
		}
		gItemPrice.showtype = info.Type;
		gItemPrice.showbuyprice = info.BuyPrice;
		gItemPrice.showsellprice = info.SellPrice;
		return Money;
	}
	*/
	if(gItemPrice.CheckItem(lpItem, &Money, &Divisor))
	{
		////console.Log("ItemPrice", "[ItemCheck] IsItemPrice [%d]", lpItem->ItemID);
		if( Money != -1 )
		{
			if( Mode == 1 )
			{
				Money = Divisor;
			}

			// ----
			//console.Log("", "return Item = %d Price = %d", lpItem->ItemID, Money);
			return Money;
		}
	}

	return pSetItemPrice(lpItem, Mode);
}

char* cItem::getItemName(int ItemID)
{
	ItemBmdStruct* ItemInfo = pGetItemBmdStruct(ItemID);

	return ItemInfo->Name;
}

void SetOptionText(int ItemID, int Line, WORD OptionID, bool Arg4, int Arg5)
{
	pSetItemOptionText(ItemID, Line, OptionID, Arg4, Arg5);

	if(ItemID == ITEM(13,150))
	{
		pSetItemTextLine(0,"asddsa");
	}
	// ----
	if(!gItemOption.GetInfoByItem(ItemID) )
	{
		return;
	}
	// ----
	switch(OptionID)
	{
	case eItemOption::LifeIncrease:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(215),
			gItemOption.GetCustomItemOption(ItemID, 0));
		break;
	case eItemOption::ExcellentDamage:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(216),
			gItemOption.GetCustomItemOption(ItemID, 0));
		break;
	case eItemOption::ManaIncrease:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(217),
			gItemOption.GetCustomItemOption(ItemID, 1));
		break;
	case eItemOption::DamageByLevel	:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(218),
			gItemOption.GetCustomItemOption(ItemID, 1));
		break;
	case eItemOption::IncreaseWizardry:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(219),
			gItemOption.GetCustomItemOption(ItemID, 1));
		break;
	case eItemOption::DamageDecrease:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(220),
			gItemOption.GetCustomItemOption(ItemID, 2));
		break;
	case eItemOption::IncreaseDamage:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(221),
			gItemOption.GetCustomItemOption(ItemID, 2));
		break;
	case eItemOption::IncreaseWizardryDmg:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(222),
			gItemOption.GetCustomItemOption(ItemID, 2));
		break;
	case eItemOption::Reflect:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(223),
			gItemOption.GetCustomItemOption(ItemID, 3));
		break;
	case eItemOption::IncreaseSpeed:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(224),
			gItemOption.GetCustomItemOption(ItemID, 3));
		break;
	case eItemOption::DefenseSuccess:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(225),
			gItemOption.GetCustomItemOption(ItemID, 4));
		break;
	case eItemOption::LifePerMob:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(226),
			gItemOption.GetCustomItemOption(ItemID, 4));
		break;
	case eItemOption::IncreaseZen:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(227),
			gItemOption.GetCustomItemOption(ItemID, 5));
		break;
	case eItemOption::ManaPerMob:
		pSetItemTextLine(Line, gCustomMessage.GetMessage(228),
			gItemOption.GetCustomItemOption(ItemID, 5));
		break;
	}
}

__declspec(naked) void MGSwordPosition1() // OK
{
	static DWORD Effect = 0x0054F2D8;
	static DWORD ReturnPos = 0x0054F2F3;

	static DWORD ItemID;

	__asm
	{
		MOV EDX,DWORD PTR SS:[EBP+0x8]
		MOVSX EAX,WORD PTR DS:[EDX+0x1C0]
		MOV ItemID, EAX
	}

	if (ItemID == 1192 || ItemID == 1194 || ItemID == 1196 || ItemID == 1202 || gCustomWeapons.CheckMG(ItemID-ITEM_BASE_MODEL))
		__asm {	JMP Effect }
	else
		__asm { jmp ReturnPos }	
}

__declspec(naked) void MGSwordPosition2() // OK
{
	static DWORD Effect = 0x005501CE;
	static DWORD ReturnPos = 0x005501E8;

	static DWORD ItemID;

	__asm
	{
		MOV ECX,DWORD PTR SS:[EBP+0x8]
		MOVSX EDX,WORD PTR DS:[ECX+0x1C0]
		MOV ItemID, EDX
	}

	if (ItemID == 1192 || ItemID == 1194 || ItemID == 1196 || ItemID == 1202 || gCustomWeapons.CheckMG(ItemID-ITEM_BASE_MODEL))
		__asm {	JMP Effect }
	else
		__asm { jmp ReturnPos }	
}

__declspec(naked) void MGSwordPosition3() // OK
{
	static DWORD Effect = 0x005504DE;
	static DWORD ReturnPos = 0x005504F8;

	static DWORD ItemID;

	__asm
	{
		MOV ECX,DWORD PTR SS:[EBP+0x8]
		MOVSX EDX,WORD PTR DS:[ECX+0x1C0]
		MOV ItemID, EDX
	}

	if (ItemID == 1192 || ItemID == 1194 || ItemID == 1196 || ItemID == 1202 || gCustomWeapons.CheckMG(ItemID-ITEM_BASE_MODEL))
		__asm {	JMP Effect }
	else
		__asm { jmp ReturnPos }	
}

__declspec(naked) void MGSwordWizDmg() // OK
{
	static DWORD Done = 0x00783E10;
	static DWORD ReturnPos = 0x00783F05;
	static DWORD ItemID;

	__asm
	{
		MOV EDX,DWORD PTR SS:[EBP-0x314]
		MOVSX EAX,WORD PTR DS:[EDX]
		MOV ItemID, EAX
	}

	if ((ItemID >= GET_ITEM(5,0) && ItemID < GET_ITEM(6,0)) || ItemID == 21 || ItemID == 23 || ItemID == 25 || 
		ItemID == 28 || ItemID == 31 || gCustomWeapons.CheckMG(ItemID))
	{
		__asm {	JMP Done }
	}
	else
	{
		__asm { jmp ReturnPos }	
	}
}
