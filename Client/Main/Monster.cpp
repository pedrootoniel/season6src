#include "stdafx.h"
#include "Monster.h"
#include "CustomMonster.h"
#include "TMemory.h"
#include "Import.h"
#include "Defines.h"
#include "Config.h"
Monster gMonster;

Monster::Monster() //ok
{

}

Monster::~Monster() //ok
{

}

#define pGetViewStruct			((lpViewObj(__cdecl*)(int a1, signed int a2, unsigned __int8 a3, unsigned __int8 a4, float a5)) 0x57EEC0)
#define	pOpenMonsterModel		((void(__cdecl*)(int MonsterID)) 0x61FDE0)

void Monster::Load()
{
	SetOp((LPVOID)0x0061FE3F, (LPVOID)Monster::LoadMonsterBMD, ASM::CALL);
	SetOp((LPVOID)0x0061FEEA, (LPVOID)Monster::LoadMonsterTexture, ASM::CALL);

	SetOp((LPVOID)0x004E199D, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00587049, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00587049, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00590CCC, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x005BBEE6, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0064229D, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00642D51, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00643229, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x0065EA86, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911A53, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911A6D, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911A87, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911AA1, (LPVOID)Monster::ShowMonster, ASM::CALL);
	SetOp((LPVOID)0x00911ABB, (LPVOID)Monster::ShowMonster, ASM::CALL);

	SetOp((LPVOID)0x0058101A, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058105B, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058109C, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005810DD, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058111E, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058115F, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005811A0, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005811E1, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00581222, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00581263, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005812A8, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005812ED, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058132E, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x0058136F, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005813B4, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x005813F9, (LPVOID)Monster::SetMainAttribute, ASM::CALL);
	SetOp((LPVOID)0x00586859, (LPVOID)Monster::SetMainAttribute, ASM::CALL);

	SetOp((LPVOID)0x0055A2DD, (LPVOID)Monster::NPCChat, ASM::CALL);

	SetByte((PVOID)(0x00559B82 + 3), 0xFF); //Limit kill
	SetByte((PVOID)(0x00559B82 + 4), 0xFF); //Limit kill
}

void Monster::LoadMonsterBMD(signed int ModelID, char* a2, char* a3, signed int a4)
{
	int MonsterID = ModelID - MONSTER_MODEL;

	for (int n = 0; n < MAX_CUSTOM_MONSTER; n++)
	{
		if (MonsterID == gCustomMonster.m_CustomMonsterInfo[n].ID)
		{
			pLoadMonsterBMD(ModelID, gCustomMonster.m_CustomMonsterInfo[n].Dir, gCustomMonster.m_CustomMonsterInfo[n].BMDFile, -1);
			return;
		}
	}

	pLoadMonsterBMD(ModelID, a2, a3, a4);
}

void Monster::LoadMonsterTexture(signed int ModelID, char* a2, int a3, int a4)
{
	int MonsterID = ModelID - MONSTER_MODEL;

	for (int n = 0; n < MAX_CUSTOM_MONSTER; n++)
	{
		if (MonsterID == gCustomMonster.m_CustomMonsterInfo[n].ID)
		{
			pLoadMonsterTexture(ModelID, gCustomMonster.m_CustomMonsterInfo[n].Folder, a3, a4);
			return;
		}
	}

	pLoadMonsterTexture(ModelID, a2, a3, a4);
}

int Monster::LoadNpcModel(int a1)
{
	pLoadNpcModel(a1);

	int result = sub_969C50(sub_4CDA10, a1);
	if (result && *(signed __int16 *)(result + 38) <= 0)
	{
		switch (a1)
		{
		case 1162:
			pLoadModel(1162, "Data\\Npc\\", "jinn", -1);
			pLoadTexture(1162, "Npc\\", 10497, 9728, 0);
			break;
		}
	}

	return result;
}

int Monster::ShowMonster(int MonsterID, int a2, int a3, int a4)
{
	for (int n = 0; n < MAX_CUSTOM_MONSTER; n++)
	{
		if (MonsterID == gCustomMonster.m_CustomMonsterInfo[n].ID)
		{
			pLoadMonsterID(MonsterID);

			DWORD ObjectStruct = pViewObject(a4, MonsterID + MONSTER_MODEL, a2, a3, 0.0); //665?

			lpViewObj Object = &*(ObjectPreview*)ObjectStruct;

			//memcpy(Object->Name, gCustomMonster.m_CustomMonsterInfo[n].Name, sizeof(Object->Name));
			strcpy((char *)(ObjectStruct + 56), gCustomMonster.m_CustomMonsterInfo[n].Name);
			//wsprintf(Object->Name, gCustomMonster.m_CustomMonsterInfo[n].Name);

			if (gCustomMonster.m_CustomMonsterInfo[n].Type == 4)
			{
				*(BYTE*)(ObjectStruct + 800) = emNPC;
			}
			else
			{
				*(BYTE*)(ObjectStruct + 800) = emMonster;
			}

			*(float *)(ObjectStruct + 872) = gCustomMonster.m_CustomMonsterInfo[n].Size;

			//Object->ID = MonsterID;
			//*(BYTE*)(ObjectStruct + 798) = 0;
			//Object->Unknown128 = *(WORD*)0x879343C;
			//sub_580BB0(ObjectStruct, MonsterID);
			//Monster::SetMainAttribute(ObjectStruct, MonsterID);
			//return sub_580BB0(ObjectStruct, MonsterID);

			sub_580BB0(ObjectStruct, MonsterID);
			return ObjectStruct;
		}
	}

	return pShowMonster(MonsterID, a2, a3, a4);
}

void Monster::SetMainAttribute(int ObjectPointer, signed int MonsterID)
{
	lpViewObj Object = &*(ObjectPreview*)(ObjectPointer);

	if (ObjectPointer)
	{
		switch (MonsterID)
		{
		case 229:
			*(short*)(ObjectPointer + 268) = ITEM2(7, gConfig.SetID[1]);
			*(BYTE*)(ObjectPointer + 270) = 13;
			*(BYTE*)(ObjectPointer + 271) = 1;
			*(short*)(ObjectPointer + 304) = ITEM2(8, gConfig.SetID[1]);
			*(BYTE*)(ObjectPointer + 306) = 13;
			*(BYTE*)(ObjectPointer + 307) = 1;
			*(short*)(ObjectPointer + 340) = ITEM2(9, gConfig.SetID[1]);
			*(BYTE*)(ObjectPointer + 342) = 13;
			*(BYTE*)(ObjectPointer + 343) = 1;
			*(short*)(ObjectPointer + 376) = ITEM2(10, gConfig.SetID[1]);
			*(BYTE*)(ObjectPointer + 378) = 13;
			*(BYTE*)(ObjectPointer + 379) = 1;
			*(short*)(ObjectPointer + 412) = ITEM2(11, gConfig.SetID[1]);
			*(BYTE*)(ObjectPointer + 414) = 13;
			*(BYTE*)(ObjectPointer + 415) = 1;
			*(short*)(ObjectPointer + 448) = ITEM2(gConfig.FirstWeaponType[1],gConfig.FirstWeaponIndex[1]);
			*(BYTE*)(ObjectPointer + 450) = 15;
			*(BYTE*)(ObjectPointer + 451) = 1;
			*(DWORD *)(ObjectPointer + 1300) = 1;
			break;
		case 247:
		case 249:
			*(short*)(ObjectPointer + 268) = ITEM2(7, gConfig.SetID[2]);
			*(BYTE*)(ObjectPointer + 270) = 13;
			*(BYTE*)(ObjectPointer + 271) = 1;
			*(short*)(ObjectPointer + 304) = ITEM2(8, gConfig.SetID[2]);
			*(BYTE*)(ObjectPointer + 306) = 13;
			*(BYTE*)(ObjectPointer + 307) = 1;
			*(short*)(ObjectPointer + 340) = ITEM2(9, gConfig.SetID[2]);
			*(BYTE*)(ObjectPointer + 342) = 13;
			*(BYTE*)(ObjectPointer + 343) = 1;
			*(short*)(ObjectPointer + 376) = ITEM2(10, gConfig.SetID[2]);
			*(BYTE*)(ObjectPointer + 378) = 13;
			*(BYTE*)(ObjectPointer + 379) = 1;
			*(short*)(ObjectPointer + 412) = ITEM2(11, gConfig.SetID[2]);
			*(BYTE*)(ObjectPointer + 414) = 13;
			*(BYTE*)(ObjectPointer + 415) = 1;
			if (MonsterID == 247)
			{
				*(short*)(ObjectPointer + 448) = ITEM2(gConfig.FirstWeaponType[2],gConfig.FirstWeaponIndex[2]);
			}
			else if (MonsterID == 249)
			{
				*(short*)(ObjectPointer + 448) = ITEM2(gConfig.SecondWeaponType[2],gConfig.SecondWeaponIndex[2]);
			}
			*(BYTE*)(ObjectPointer + 450) = 15;
			*(BYTE*)(ObjectPointer + 451) = 1;
			*(DWORD *)(ObjectPointer + 1300) = 1;
			break;
		case 58:
			*(short*)(ObjectPointer + 448) = ITEM2(0, 28);
			*(BYTE*)(ObjectPointer + 450) = 0;
			*(BYTE*)(ObjectPointer + 451) = 0;
			break;
		}
		//if ( MonsterID == 451 )
		//  *(BYTE*)(ObjectPointer + 800) = -128;
	}

	pMonsterAttribute(ObjectPointer, MonsterID);
}

void Monster::NPCChat(int a1, int a2)
{
	//switch (*(WORD *)(a1 + 132))
	//{
	//case 651: //651+794: //794???
	//	pSendChatSay((char *)(a1 + 56), "I Wish You !", a1, 0, -1);
	//	break;
	//}

	pNpcChat(a1, a2);
}