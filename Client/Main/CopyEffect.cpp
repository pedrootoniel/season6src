#include "stdafx.h"
#include "CopyEffect.h"
#include "Import.h"
#include "Defines.h"
#include "Object.h"
#include "Interface.h"
#include "TMemory.h"
#include "HealthBar.h"
#include "ModelEffect.h"
#include "Offset.h"
#include "Protect.h"
#include "Config.h"
CCopyEffect gCopyEffect;

CCopyEffect::CCopyEffect()
{

}
CCopyEffect::~CCopyEffect()
{

}
DWORD WingEffectPointer;
DWORD WingEffectBuff;
DWORD CapeRegister;

__declspec(naked) void WingofStormEffect()
{
	static DWORD Address1 = 0x0060C159;
	static DWORD Address2 = 0x0060C75D;
	_asm
	{
		Mov ecx, dword ptr ss : [ebp + 0x0C]
		Mov dword ptr ss : [ebp + 0x0C] , ecx
		Mov WingEffectPointer, ecx
	}
	if (WingEffectPointer == ITEM2(12, 36)
		|| WingEffectPointer == ITEM2(12, 191)
		|| WingEffectPointer == ITEM2(12, 190)
		)
	{
		_asm {Jmp Address1}
	}
	else
	{
		_asm {Jmp Address2}
	}

}

//__declspec(naked) void WingofStormEffect2()
//{
//	static DWORD Address1 = 0x005FAA45;
//	static DWORD Address2 = 0x005FABC2;
//
//	_asm
//	{
//		Mov Ecx, Dword Ptr Ss : [Ebp + 0x10]
//		Mov Dword Ptr Ss : [Ebp + 0x10] , Ecx
//		Mov WingEffectPointer, Ecx
//	}
//	if (WingEffectPointer == ITEM2(12, 36)
//		|| WingEffectPointer == ITEM2(12, 191)
//		)
//	{
//		_asm {Jmp Address1}
//	}
//	else
//	{
//		_asm {Jmp Address2}
//	}
//
//}

__declspec(naked) void WingofSpaceTimeEffect()
{
	static DWORD Address1 = 0x0060C76A;
	static DWORD Address2 = 0x0060CB39;
	_asm
	{
		Mov Ecx, Dword Ptr Ss : [Ebp + 0x0C]
		Mov Dword Ptr Ss : [Ebp + 0x0C] , Ecx
		Mov WingEffectPointer, Ecx
	}
	if (WingEffectPointer == ITEM2(12, 37)
		|| WingEffectPointer == ITEM2(12, 192)
		)
	{
		_asm {jmp Address1}
	}
	else
	{
		_asm {jmp Address2}
	}

}

__declspec(naked) void WingofIllusionEffect()
{
	static DWORD Address1 = 0x0060CB46;
	static DWORD Address2 = 0x0060CF8E;
	_asm
	{
		Mov Ecx, Dword ptr ss : [Ebp + 0x0C]
		Mov Dword Ptr ss : [Ebp + 0x0C] , Ecx
		Mov WingEffectPointer, Ecx
	}
	if (WingEffectPointer == ITEM2(12, 38)
		//||WingEffectPointer == ITEM2(12,300)
		)
	{
		_asm {Jmp Address1}
	}
	else
	{
		_asm {Jmp Address2}
	}

}

//__declspec(naked) void WingofRuinEffect()
//{
//	static DWORD Address1 = 0x0060CF9B;
//	static DWORD Address2 = 0x0060D5C4;
//	_asm
//	{
//		Mov Ecx, dword ptr ss : [ebp + 0x0C]
//		Mov Dword ptr ss : [ebp + 0x0C] , ecx
//		Mov WingEffectPointer, ecx
//	}
//	if (WingEffectPointer == ITEM2(12, 39) ||
//		WingEffectPointer == ITEM2(12, 193)
//		)
//	{
//		_asm {Jmp Address1}
//	}
//	else
//	{
//		_asm {Jmp Address2}
//	}
//
//}

//__declspec(naked) void WingofRuinEffect2()
//{
//	static DWORD Address1 = 0x005FABCF;
//	static DWORD Address2 = 0x005FAD70;
//
//	_asm
//	{
//		Mov Ecx, Dword ptr ss : [ebp + 0x10]
//		Mov dword ptr ss : [ebp + 0x10] , ecx
//		Mov WingEffectPointer, ecx
//	}
//	if (WingEffectPointer == ITEM2(12, 39) || WingEffectPointer == ITEM2(12, 193)
//		)
//	{
//		_asm {Jmp Address1}
//	}
//	else
//	{
//		_asm {Jmp Address2}
//	}
//
//}

__declspec(naked) void WingofDimension()
{
	static DWORD Adress1 = 0x0060D5D1;
	static DWORD Adress2 = 0x0060D5CB;

	_asm
	{
		Mov Ecx, Dword ptr ss : [ebp + 0x0C]
		Mov Dword ptr ss : [ebp + 0x0C] , Ecx
		Mov WingEffectPointer, Ecx
	}
	if (WingEffectPointer == ITEM2(12, 43) || WingEffectPointer == ITEM2(12, 195))
	{
		_asm {jmp Adress1}
	}
	else
	{
		_asm {jmp Adress2}
	}

}


__declspec(naked) void DeathCape2()
{
	_asm
	{
		PUSH iCapeDeath1
		PUSH iCapeDeath1
		mov CapeRegister, 0x00574924
		Jmp CapeRegister
	}
}
__declspec(naked) void DeathCape3()
{
	_asm
	{
		PUSH iCapeDeath2
		PUSH iCapeDeath2
		mov CapeRegister, 0x00574F38
		jmp CapeRegister
	}
}
__declspec(naked) void DeathCape3_2()
{
	_asm
	{
		PUSH iCapeDeath2
		PUSH iCapeDeath2
		mov CapeRegister, 0x00575006
		jmp CapeRegister
	}
}


__declspec(naked) void CapeLvl4DL1()
{
	_asm
	{
		Push iCapeLvl4DL2
		Push iCapeLvl4DL2
		Mov CapeRegister, 0x00574924
		Jmp CapeRegister
	}
}
__declspec(naked) void CapeLvl4DL2()
{
	_asm
	{
		PUSH iCapeLvl4DL
		PUSH iCapeLvl4DL
		mov CapeRegister, 0x00574F38
		jmp CapeRegister
	}
}
__declspec(naked) void CapeLvl4DL3()
{
	_asm
	{
		PUSH iCapeLvl4DL
		PUSH iCapeLvl4DL
		mov CapeRegister, 0x00575006
		jmp CapeRegister
	}
}


__declspec(naked) void RemoveDLHair()
{
	_asm
	{
		Mov CapeRegister, 0x005748FF
		Jmp CapeRegister
	}
}
__declspec(naked) void AllowDLHair()
{
	_asm
	{
		Push 0xC0000205
		mov CapeRegister, 0x00574755
		jmp CapeRegister
	}
}
#include "CustomMessage.h"
void CCopyEffect::DrawViewPortEffects(DWORD ObjectPointer, DWORD ObjectModel, DWORD a3)
{
	lpViewObj Object = &*(ObjectPreview*)(ObjectPointer);
	if (gProtect.m_MainInfo.CustomItemPack == 0)
	{
		switch (Object->WingsSlot)
		{
		case ITEM2(12, 189):
		case ITEM2(12, 220):
			Object->WingsSlot = ITEM2(12, 220);
			//
			SetDword((PVOID)(0x0057491A + 1), iCapeDeath1);
			SetDword((PVOID)(0x0057491F + 1), iCapeDeath1);
			//
			SetDword((PVOID)(0x00574F2E + 1), iCapeDeath2);
			SetDword((PVOID)(0x00574F33 + 1), iCapeDeath2);
			//
			SetDword((PVOID)(0x00574FFC + 1), iCapeDeath2);
			SetDword((PVOID)(0x00575001 + 1), iCapeDeath2);
			//-
			break;

		case ITEM2(12, 194):
		case ITEM2(12, 221):
			Object->WingsSlot = ITEM2(12, 221);
			SetDword((PVOID)(0x0057491A + 1), iCapeLvl4DL2);
			SetDword((PVOID)(0x0057491F + 1), iCapeLvl4DL2);
			//
			SetDword((PVOID)(0x00574F2E + 1), iCapeLvl4DL);
			SetDword((PVOID)(0x00574F33 + 1), iCapeLvl4DL);
			//
			SetDword((PVOID)(0x00574FFC + 1), iCapeLvl4DL);
			SetDword((PVOID)(0x00575001 + 1), iCapeLvl4DL);
			break;
		case ITEM2(12, 40):
			SetDword((PVOID)(0x0057491A + 1), iDLRedwing02);
			SetDword((PVOID)(0x0057491F + 1), iDLRedwing02);
			//
			SetDword((PVOID)(0x00574F2E + 1), iDLRedwing03);
			SetDword((PVOID)(0x00574F33 + 1), iDLRedwing03);
			//
			SetDword((PVOID)(0x00574FFC + 1), iDLRedwing03);
			SetDword((PVOID)(0x00575001 + 1), iDLRedwing03);
			//-
			break;
			/*
	   case ITEM2(12,50):
		   SetDword((PVOID)(0x005751EB + 1), 0x7EE2);
		   SetDword((PVOID)(0x005751F0 + 1), 0x7EE2);
		   //
		   SetDword((PVOID)(0x0057562C + 1), 0x7EE1);
		   SetDword((PVOID)(0x00575631 + 1), 0x7EE1);
		   //
		   SetDword((PVOID)(0x005756EE + 1), 0x7EE1);
		   SetDword((PVOID)(0x005756F3 + 1), 0x7EE1);
		   //-
			break;
	   case ITEM2(12, 196):
	   case ITEM2(12, 222):
		   Object->WingsSlot = ITEM2(12, 222);
		   SetDword((PVOID)(0x005751EB + 1), iCapeLvl4RF);
		   SetDword((PVOID)(0x005751F0 + 1), iCapeLvl4RF);
		   //
		   SetDword((PVOID)(0x0057562C + 1), 0x7EE1);
		   SetDword((PVOID)(0x00575631 + 1), 0x7EE1);
		   //
		   SetDword((PVOID)(0x005756EE + 1), 0x7EE1);
		   SetDword((PVOID)(0x005756F3 + 1), 0x7EE1);
		   //-
		   break;
		   */
		}
	}
	if (Object->HelmSlot >= ITEM2(7, 0) && Object->HelmSlot <= ITEM2(7, 255)
		|| Object->ArmorSlot >= ITEM2(8, 0) && Object->ArmorSlot <= ITEM2(8, 255)
		|| Object->PantsSlot >= ITEM2(9, 0) && Object->PantsSlot <= ITEM2(9, 255)
		|| Object->GlovesSlot >= ITEM2(10, 0) && Object->GlovesSlot <= ITEM2(10, 255)
		|| Object->BootsSlot >= ITEM2(11, 0) && Object->BootsSlot <= ITEM2(11, 255))
	{
		if (gConfig.EffectLevel15 == 0)
		{
			if (Object->HelmLevel == 15)
			{
				Object->HelmLevel = 14;
			}
			if (Object->ArmorLevel == 15)
			{
				Object->ArmorLevel = 14;
			}
			if (Object->PantsLevel == 15)
			{
				Object->PantsLevel = 14;
			}
			if (Object->GlovesLevel == 15)
			{
				Object->GlovesLevel = 14;
			}
			if (Object->BootsLevel == 15)
			{
				Object->BootsLevel = 14;
			}
		}
	}

	/*
	switch(Object->Class)
	{
		case 0:case 8:case 24:
			SetByte((PVOID)(0x0057236B + 2),0);
			SetByte((PVOID)(0x0057465E + 2),0);
			SetOp((LPVOID)0x00574750,(LPVOID)RemoveDLHair,ASM::JMP);
			break;
		case 1:case 9:case 25:
			SetByte((PVOID)(0x0057236B + 2),1);
			SetByte((PVOID)(0x0057465E + 2),1);
			SetOp((LPVOID)0x00574750,(LPVOID)RemoveDLHair,ASM::JMP);
			break;
		case 2:case 10:case 26:
			SetByte((PVOID)(0x0057236B + 2),2);
			SetByte((PVOID)(0x0057465E + 2),2);
			SetOp((LPVOID)0x00574750,(LPVOID)RemoveDLHair,ASM::JMP);
			break;
		case 3:case 27:case 11:
			SetByte((PVOID)(0x0057236B + 2),3);
			SetByte((PVOID)(0x0057465E + 2),3);
			SetOp((LPVOID)0x00574750,(LPVOID)RemoveDLHair,ASM::JMP);
			break;
		case 4:case 28:
			SetByte((PVOID)(0x00572356 + 2),4);
			SetByte((PVOID)(0x0057465E + 2),4);
			SetOp((LPVOID)0x00574750,(LPVOID)AllowDLHair,ASM::JMP);
			break;
		case 5:case 13:case 29:
			SetByte((PVOID)(0x0057236B + 2),5);
			SetByte((PVOID)(0x0057465E + 2),5);
			SetOp((LPVOID)0x00574750,(LPVOID)RemoveDLHair,ASM::JMP);
			break;

		case 6:case 30:
			SetByte((PVOID)(0x0057236B + 2),6);
			SetByte((PVOID)(0x0057465E + 2),6);
			SetOp((LPVOID)0x00574750,(LPVOID)RemoveDLHair,ASM::JMP);
			break;
	}
	*/
	MU3Float lBone[MAX_MODEL_EFFECT];
	MU3Float lBone2[MAX_MODEL_EFFECT];
	vec3_t Color;
	vec3_t ColorRandom;
	//
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	{
		lBone[i].X = *(float*)(ObjectModel + 252);
		lBone[i].Y = *(float*)(ObjectModel + 256);
		lBone[i].Z = *(float*)(ObjectModel + 260);
		lBone2[i].X = *(float*)(ObjectModel + 264);
		lBone2[i].Y = *(float*)(ObjectModel + 268);
		lBone2[i].Z = *(float*)(ObjectModel + 272);
	}
	//
	Vector(1.0, 1.0, 1.0, Color);
	Vector(((float)(rand() % 100) / 100), ((float)(rand() % 100) / 100), ((float)(rand() % 100) / 100), ColorRandom);
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	{
		if (Object->HelmSlot == ITEM2(gCustomModelEffect.m_CustomModelEffectInfo[i].ItemType, gCustomModelEffect.m_CustomModelEffectInfo[i].ItemIndex) &&
			Object->HelmLevel >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinLevel && Object->HelmLevel <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxLevel &&
			Object->HelmExcellent >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinExcellent && Object->HelmExcellent <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxExcellent)
		{
			lBone[i].Z = lBone[i].Z + (float)(150);
			lBone2[i].Z = lBone2[i].Z + (float)(150);
			Vector(gCustomModelEffect.m_CustomModelEffectInfo[i].Color[0], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[1], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[2], Color);
			if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 1)
			{
				sub_74CD30(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, 0);
			} // 3}
			else if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 2)
			{
				sub_6D9070(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
			}
			else
				pPlayStaticEffect(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (DWORD*)&lBone[i], gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
		}
	}
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	{
		if (Object->ArmorSlot == ITEM2(gCustomModelEffect.m_CustomModelEffectInfo[i].ItemType, gCustomModelEffect.m_CustomModelEffectInfo[i].ItemIndex) &&
			Object->ArmorLevel >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinLevel && Object->ArmorLevel <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxLevel &&
			Object->ArmorExcellent >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinExcellent && Object->ArmorExcellent <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxExcellent)
		{
			lBone[i].Z = lBone[i].Z + (float)(120);
			lBone2[i].Z = lBone2[i].Z + (float)(120);
			Vector(gCustomModelEffect.m_CustomModelEffectInfo[i].Color[0], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[1], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[2], Color);
			if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 1)
			{
				sub_74CD30(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, 0);
			} // 3}
			else if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 2)
			{
				sub_6D9070(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
			}
			else
				pPlayStaticEffect(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (DWORD*)&lBone[i], gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
		}
	}
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	{

		if (Object->PantsSlot == ITEM2(gCustomModelEffect.m_CustomModelEffectInfo[i].ItemType, gCustomModelEffect.m_CustomModelEffectInfo[i].ItemIndex) &&
			Object->PantsLevel >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinLevel && Object->PantsLevel <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxLevel &&
			Object->PantsExcellent >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinExcellent && Object->PantsExcellent <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxExcellent)
		{
			lBone[i].Z = lBone[i].Z + (float)(60);
			lBone2[i].Z = lBone2[i].Z + (float)(60);
			Vector(gCustomModelEffect.m_CustomModelEffectInfo[i].Color[0], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[1], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[2], Color);
			if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 1)
			{
				sub_74CD30(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, 0);
			} // 3}
			else if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 2)
			{
				sub_6D9070(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
			}
			else
				pPlayStaticEffect(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (DWORD*)&lBone[i], gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
		}
	}
	for (int i = 0; i < MAX_MODEL_EFFECT; i++)
	{
		if (Object->BootsSlot == ITEM2(gCustomModelEffect.m_CustomModelEffectInfo[i].ItemType, gCustomModelEffect.m_CustomModelEffectInfo[i].ItemIndex) &&
			Object->BootsLevel >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinLevel && Object->BootsLevel <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxLevel &&
			Object->BootsExcellent >= gCustomModelEffect.m_CustomModelEffectInfo[i].MinExcellent && Object->BootsExcellent <= gCustomModelEffect.m_CustomModelEffectInfo[i].MaxExcellent)
		{
			if (Object->WingsSlot >= 1)
			{
				if (Object->InSafeZone)
				{
					lBone[i].Z = lBone[i].Z + (float)(20);
					lBone2[i].Z = lBone2[i].Z + (float)(20);
				}
				else
					lBone[i].Z = lBone[i].Z + (float)(80);
				lBone2[i].Z = lBone2[i].Z + (float)(80);
			}
			else
			{
				lBone[i].Z = lBone[i].Z + (float)(20);
				lBone2[i].Z = lBone2[i].Z + (float)(20);
			}
			Vector(gCustomModelEffect.m_CustomModelEffectInfo[i].Color[0], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[1], gCustomModelEffect.m_CustomModelEffectInfo[i].Color[2], Color);
			if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 1)
			{
				sub_74CD30(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, 0);
			} // 3}
			else if (gCustomModelEffect.m_CustomModelEffectInfo[i].EffectIndex == 2)
			{
				sub_6D9070(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (int)&lBone[i], (int)&lBone2[i], Color, gCustomModelEffect.m_CustomModelEffectInfo[i].EffectType, 0, 0, 0, 0, 0, 0.0, -1);
			}
			else
				pPlayStaticEffect(gCustomModelEffect.m_CustomModelEffectInfo[i].EffectCode, (DWORD*)&lBone[i], gCustomModelEffect.m_CustomModelEffectInfo[i].EffectScale, Color, (int)&lBone2[i], 0, 0);
		}
	}
	/*
	switch(Object->ID)
	{
	case 0:
		memcpy(Object->Name, "Bull Fighter", sizeof(Object->Name));
		break;

	case 658:
		Bone.Z = Bone.Z + 30.0f;
		if (Object->m_Model.AnimationID != 6)
		{
			pPlayStaticEffect(32002, (DWORD*)&Bone, 2.0, Color, (int)&Bone2, 0, 0);
			Vector(0.3f, 0.3f, 1.0f, Color);
			pPlayStaticEffect(32002, (DWORD*)&Bone, 3.0, Color, (int)&Bone2, 0, 0);
		}
		else
		{
			//pCreateEffect 550 ?: //229 id 7-> Decay
			//Bone.Z = Bone.Z + 200.0;
			sub_6D9070(550, (int)&Bone, (int)&Bone2, Color, 0, 0, -1, 0, 0, 0, 0.0, -1);
			Bone.Z = Bone.Z + 300.0f;
			Bone2.Z = Bone2.Z + 300.0f;
			sub_6D9070(32407, (int)&Bone, (int)&Bone2, Color, 0, 0, 0, 0, 0, 0, 0.0, -1);//FireWork
		}
		break;
	case 657:
		Object->WeaponFirstSlot = ITEM2(5, 200);
		Object->WeaponFirstExcellent = 1;
		Object->WeaponFirstLevel = 15;
		if (Object->m_Model.AnimationID == 6) {
			sub_6D9070(337, (int)&Bone, (int)&Bone2, Color, 3, 0, -130, 5, 0, 0, 0.0, -1);
			//sub_72D1B0(322, (int)&Bone, (int)&Bone, (int)&Bone2, 6, SLODWORD(Object->m_Model), 170.0, -1, 0, 0, -1, 0, -1); //WTF
			Bone.X = Bone.X + (float)(rand() % 1024 - 480);
			Bone.Y = Bone.Y + (float)(rand() % 1024 - 480);
			Bone.Z = Bone.Z + (float)(rand() % 1024 - 480);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 0, 0, 0, 0, 0, 0, 0.0, -1);
		}
		else if (Object->m_Model.AnimationID == 4) {
			sub_6D9070(336, (int)&Bone, (int)&Bone2, Color, 3, 0, -130, 4, 0, 0, 0.0, -1);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 2, 0, 0, 0, 0, 0, 0.0, -1);
			Bone.X = Bone.X + (float)(rand() % 1024 - 480);
			Bone.Y = Bone.Y + (float)(rand() % 1024 - 480);
			Bone.Z = Bone.Z + (float)(rand() % 1024 - 480);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 0, 0, 0, 0, 0, 0, 0.0, -1);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 0, 0, 0, 0, 0, 0, 0.0, -1);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 0, 0, 0, 0, 0, 0, 0.0, -1);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 0, 0, 0, 0, 0, 0, 0.0, -1);
		}
		else if (Object->m_Model.AnimationID == 3)
		{
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 2, 0, 0, 0, 0, 0, 0.0, -1);
			Bone.X = Bone.X + (float)(rand() % 1024 - 480);
			Bone.Y = Bone.Y + (float)(rand() % 1024 - 480);
			Bone.Z = Bone.Z + (float)(rand() % 1024 - 480);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 6, 0, 0, 0, 0, 0, 0.0, -1);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 6, 0, 0, 0, 0, 0, 0.0, -1);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 6, 0, 0, 0, 0, 0, 0.0, -1);
			sub_6D9070(229, (int)&Bone, (int)&Bone2, Color, 6, 0, 0, 0, 0, 0, 0.0, -1);
		}
		sub_72D1B0(322, (int)&Bone, (int)&Bone, (int)&Bone2, 6, SLODWORD(ObjectModel), 170.0, -1, 0, 0, -1, 0, -1); //WTF
		Bone.Z = Bone.Z + 250.0f;
		sub_74CD30(0x7D83, (int)&Bone, (int)&Bone2, ColorRandom, 3, 2.0f, 0);
		break;
	case 604:
		*(BYTE*)(ObjectModel + 24) = 4;
		break;
	}


	if (!strncmp(Object->Name, "WhiteBlood", 11))
	{
		Vector(0.1f, 0.8f, 1.0f, Color);
		Bone.Z = Bone.Z + (float)(200);
		Bone2.Z = Bone2.Z + (float)(200);
		sub_74CD30(0x7D65, (int)&Bone, (int)&Bone2, Color, 17,0.1f, 56);
	}
	*/
	pDrawViewPortEffects(ObjectPointer, ObjectModel, a3);
}
DWORD CapeEffectPointer;
DWORD CapeEffectBuff;

__declspec(naked) void CapeD() //allow play
{
	static DWORD Address1 = 0x00574683;
	static DWORD Address2 = 0x0057468F;
	_asm {
		Mov CapeEffectBuff, Ecx
		MOV DWORD PTR SS : [EBP - 0x2D8] , 4
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		MOVSX ECX, WORD PTR DS : [EAX + 0x208]
		mov CapeEffectPointer, ecx
		mov ecx, CapeEffectBuff
	}
	if (CapeEffectPointer == ITEM2(12, 40)
		|| CapeEffectPointer == ITEM2(12, 189)
		|| CapeEffectPointer == ITEM2(12, 194)
		//||CapeEffectPointer == ITEM2(12,196)
		|| CapeEffectPointer == ITEM2(12, 220)
		|| CapeEffectPointer == ITEM2(12, 221)
		//||CapeEffectPointer == ITEM2(12,222)
		)
	{
		_asm {jmp Address1}
	}
	else
	{
		_asm {jmp Address2}
	}

}

__declspec(naked) void CapeA() // 0x7759 //-> 03 Main
{
	static DWORD Address1 = 0x00574F29;
	static DWORD Address2 = 0x005750C5;

	_asm {
		Mov CapeEffectBuff, ecx
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		MOVSX ECX, WORD PTR DS : [EAX + 0x208]
		Mov CapeEffectPointer, ecx
		Mov ecx, CapeEffectBuff
	}
	if (CapeEffectPointer == ITEM2(12, 40)
		|| CapeEffectPointer == ITEM2(12, 189)
		|| CapeEffectPointer == ITEM2(12, 194)
		//||CapeEffectPointer == ITEM2(12,196)
		|| CapeEffectPointer == ITEM2(12, 220)
		|| CapeEffectPointer == ITEM2(12, 221)
		//||CapeEffectPointer == ITEM2(12,222)
		)
	{
		_asm {Jmp Address1}
	}
	else
	{
		_asm {Jmp Address2}
	}
}

__declspec(naked) void CapeB() //7758
{
	static DWORD Address1 = 0x00574915;
	static DWORD Address2 = 0x00574A6A;

	_asm {
		mov CapeEffectBuff, ecx
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		MOVSX ECX, WORD PTR DS : [EAX + 0x208]
		mov CapeEffectPointer, ecx
		mov ecx, CapeEffectBuff
	}
	if (CapeEffectPointer == ITEM2(12, 40)
		|| CapeEffectPointer == ITEM2(12, 189)
		|| CapeEffectPointer == ITEM2(12, 194)
		//||CapeEffectPointer == ITEM2(12,196)
		|| CapeEffectPointer == ITEM2(12, 220)
		|| CapeEffectPointer == ITEM2(12, 221)
		//||CapeEffectPointer == ITEM2(12,222)
		)
	{
		_asm {Jmp Address1}
	}
	else
	{
		_asm {Jmp Address2}
	}
}

__declspec(naked) void CapeE() //main allow
{
	static DWORD Address1 = 0x005760C2;
	static DWORD Address2 = 0x00576014;

	_asm {
		Mov CapeEffectBuff, ecx
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		MOVSX ECX, WORD PTR DS : [EAX + 0x208]
		Mov CapeEffectPointer, Ecx
		Mov Ecx, CapeEffectBuff
	}
	if (CapeEffectPointer == 0x1CBB || CapeEffectPointer == 0x1D15 || CapeEffectPointer == 0x1EB1
		|| CapeEffectPointer == ITEM2(12, 189)
		|| CapeEffectPointer == ITEM2(12, 194)
		//||CapeEffectPointer == ITEM2(12,196)
		|| CapeEffectPointer == ITEM2(12, 220)
		|| CapeEffectPointer == ITEM2(12, 221)
		//||CapeEffectPointer == ITEM2(12,222)
		)
	{
		_asm {jmp Address1}
	}
	else
	{
		_asm {jmp Address2}
	}
}

__declspec(naked) void HideCape()
{
	static DWORD Address1 = 0x005FAD7D;
	static DWORD Address2 = 0x005FAE90;
	_asm
	{
		Mov Ecx, dword ptr ss : [ebp + 0x10]
		Mov Dword ptr ss : [ebp + 0x10] , Ecx
		Mov CapeEffectPointer, Ecx
	}
	if (CapeEffectPointer == ITEM2(12, 40) ||
		CapeEffectPointer == ITEM2(12, 189) ||
		CapeEffectPointer == ITEM2(12, 194)
		)
	{
		_asm {jmp Address1}
	}
	else
	{
		_asm {jmp Address2}
	}
}
void RefreshCapeUnEquip(ObjectItem* lpItem)
{

	switch (lpItem->ItemID)
	{
	case ITEM2(12, 189):
	case ITEM2(12, 194):
		//case ITEM2(12,196):
	case ITEM2(12, 220):
	case ITEM2(12, 221):
		//case ITEM2(12,222):
		pRefreshViewportEffect(oUserPreviewStruct, oUserPreviewStruct + 776, 0);
		break;
	}

	pRefreshCape1(lpItem);
}

__declspec(naked) void AllowMGCape() //?
{
	static DWORD Address1 = 0x00574D4C;
	static DWORD Address2 = 0x00574DAC;
	_asm
	{
		Mov CapeEffectBuff, Ecx
		Mov Eax, Dword Ptr Ss : [Ebp + 0x8]
		MOVZX ECX, BYTE Ptr Ds : [Eax + 0x13]
		Mov CapeEffectPointer, Ecx
		Mov Ecx, CapeEffectBuff
	}
	if (CapeEffectPointer == 3)
	{
		_asm {jmp Address1}
	}
	else
	{
		_asm {jmp Address2}
	}

}
void __declspec(naked) CapeInventoryPos()
{
	DWORD dwItem;
	_asm
	{
		Mov Ecx, DWORD PTR SS : [EBP + 0x8]
		Mov dwItem, Ecx
		CMP dwItem, ITEM2(12, 40)
		Je Exit
		CMP dwItem, ITEM2(12, 189)
		Je Exit
		CMP dwItem, ITEM2(12, 194)
		Je Exit
		//CMP dwItem,ITEM2(12,196)
		//Je Exit
		Exit :
		Mov Ecx, 0x005CAFD2
			Jmp Ecx
	}
}
DWORD DivineWeapon_Buff = 0;
DWORD DivineWeapon_Pointer = 0;
__declspec(naked) void DivineWeapon()
{
	static DWORD Address1 = 0x007E785F;
	static DWORD Address2 = 0x007E7866;
	_asm
	{
		Mov DivineWeapon_Buff, Edx
		MOVSX EDX, WORD PTR SS : [EBP + 0x8]
		mov DWORD PTR SS : [EBP + 0x8] , Edx
		mov DivineWeapon_Pointer, Edx
		Mov Edx, DivineWeapon_Buff
	}
	if (DivineWeapon_Pointer == 0x13
		|| DivineWeapon_Pointer == 0x812
		|| DivineWeapon_Pointer == 0x0A0A
		|| DivineWeapon_Pointer == 0x40D
		|| DivineWeapon_Pointer == 0x0A24
		|| DivineWeapon_Pointer == ITEM(0, 47) || DivineWeapon_Pointer == ITEM(2, 24)
		|| DivineWeapon_Pointer == ITEM(4, 30) || DivineWeapon_Pointer == ITEM(5, 44)
		|| DivineWeapon_Pointer == ITEM(5, 45) || DivineWeapon_Pointer == ITEM(0, 42)
		|| DivineWeapon_Pointer == ITEM(0, 44) || DivineWeapon_Pointer == ITEM(2, 23)
		|| DivineWeapon_Pointer == ITEM(4, 30) || DivineWeapon_Pointer == ITEM(5, 41)
		|| DivineWeapon_Pointer == ITEM(0, 57) || DivineWeapon_Pointer == ITEM(0, 58)
		|| DivineWeapon_Pointer == ITEM(2, 27) || DivineWeapon_Pointer == ITEM(4, 36)
		|| DivineWeapon_Pointer == ITEM(5, 53) || DivineWeapon_Pointer == ITEM(5, 54)
		|| (DivineWeapon_Pointer >= ITEM(7, 100) && DivineWeapon_Pointer <= ITEM(7, 117))
		|| (DivineWeapon_Pointer >= ITEM(8, 100) && DivineWeapon_Pointer <= ITEM(8, 117))
		|| (DivineWeapon_Pointer >= ITEM(9, 100) && DivineWeapon_Pointer <= ITEM(9, 117))
		|| (DivineWeapon_Pointer >= ITEM(10, 100) && DivineWeapon_Pointer <= ITEM(10, 117))
		|| (DivineWeapon_Pointer >= ITEM(11, 100) && DivineWeapon_Pointer <= ITEM(11, 117))
		|| (DivineWeapon_Pointer >= ITEM(7, 164) && DivineWeapon_Pointer <= ITEM(7, 169))
		|| (DivineWeapon_Pointer >= ITEM(8, 164) && DivineWeapon_Pointer <= ITEM(8, 169))
		|| (DivineWeapon_Pointer >= ITEM(9, 164) && DivineWeapon_Pointer <= ITEM(9, 169))
		|| (DivineWeapon_Pointer >= ITEM(10, 164) && DivineWeapon_Pointer <= ITEM(10, 169))
		|| (DivineWeapon_Pointer >= ITEM(11, 164) && DivineWeapon_Pointer <= ITEM(11, 169))
		)
	{
		_asm {Jmp Address1}
	}
	else
	{
		_asm {Jmp Address2}
	}

}

void DrawObjectDropOnViewport(int a1)
{
	pObjOnViewport(a1);

	switch (*(DWORD*)(a1 + 48))
	{
	case ITEM2(13, 64):
		*(float*)(a1 + 264) = 0.0f;
		*(float*)(a1 + 96) = 0.2f;
		*(float*)(a1 + 272) = 70.0f;
		break;
	}
}

char DrawDarkRavenHP(int a1, int a2)
{
	char result; // al@2
	char* v3; // eax@3
	char PetName[255]; // [sp+4h] [bp-108h]@3
	//char v5; // [sp+5h] [bp-107h]@3
	int HP; // [sp+108h] [bp-4h]@3

	if (*(DWORD*)(*(DWORD*)0x7BC4F04 + 676))
	{
		PetName[0] = 0;
		memset(&HP, 0, 0xFF);
		v3 = pGetTextLine_(pTextLineThis, 1214);
		sub_50D100((char*)&PetName, "%s", v3);
		HP = *((BYTE*)(*(DWORD*)0x8128AC4 + 4801));
		sub_7DFA60(60, 50, (int)&PetName, HP, 255, 0);
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}
#include "Util.h"
void CCopyEffect::Load()
{
	SetOp((LPVOID)0x0040487D, &this->DrawViewPortEffects, ASM::CALL);
	SetOp((LPVOID)0x0048E56C, &this->DrawViewPortEffects, ASM::CALL);
	SetOp((LPVOID)0x0057D4FF, &this->DrawViewPortEffects, ASM::CALL);
	SetOp((LPVOID)0x0057D513, &this->DrawViewPortEffects, ASM::CALL);

	SetCompleteHook(0xFF, 0x0040487D, &this->DrawViewPortEffects);
	SetCompleteHook(0xFF, 0x0048E56C, &this->DrawViewPortEffects);
	SetCompleteHook(0xFF, 0x0057D4FF, &this->DrawViewPortEffects);
	SetCompleteHook(0xFF, 0x0057D513, &this->DrawViewPortEffects);

	SetCompleteHook(0xE8, 0x007DF8F6, &DrawDarkRavenHP);

	SetCompleteHook(0xE8, 0x005F820C, &DrawObjectDropOnViewport);
	SetCompleteHook(0xE8, 0x005F847D, &DrawObjectDropOnViewport);

	//---------------
	SetRange((LPVOID)0x0060C14C, 7, ASM::NOP);
	SetOp((LPVOID)0x0060C14C, (LPVOID)WingofStormEffect, ASM::JMP);
	//-
	//SetRange((LPVOID)0x005FAA38, 7, ASM::NOP);
	//SetOp((LPVOID)0x005FAA38, (LPVOID)WingofStormEffect2, ASM::JMP);
	//-

	SetRange((LPVOID)0x0060C75D, 7, ASM::NOP);
	SetOp((LPVOID)0x0060C75D, (LPVOID)WingofSpaceTimeEffect, ASM::JMP);
	//-
	SetRange((LPVOID)0x0060CB39, 7, ASM::NOP);
	SetOp((LPVOID)0x0060CB39, (LPVOID)WingofIllusionEffect, ASM::JMP);
	//-
	SetRange((LPVOID)0x0060D5C4, 7, ASM::NOP);
	SetOp((LPVOID)0x0060D5C4, (LPVOID)WingofDimension, ASM::JMP);
	//--
	SetRange((LPVOID)0x0060CF8E, 7, ASM::NOP);
	//SetOp((LPVOID)0x0060CF8E, (LPVOID)WingofRuinEffect, ASM::JMP);
	//-
	SetRange((LPVOID)0x005FABC2, 7, ASM::NOP);
	//SetOp((LPVOID)0x005FABC2, (LPVOID)WingofRuinEffect2, ASM::JMP);

	//-
	if (gProtect.m_MainInfo.CustomItemPack == 0)
	{
		SetRange((LPVOID)0x00574667, 20, ASM::NOP);
		SetOp((LPVOID)0x00574667, (LPVOID)CapeD, ASM::JMP);
		//-
		SetRange((LPVOID)0x005748FF, 10, ASM::NOP);
		SetOp((LPVOID)0x005748FF, (LPVOID)CapeB, ASM::JMP);
		//-
		SetRange((LPVOID)0x00574F13, 10, ASM::NOP);
		SetOp((LPVOID)0x00574F13, (LPVOID)CapeA, ASM::JMP);
		//-
		SetRange((LPVOID)0x00576058, 10, ASM::NOP);
		SetOp((LPVOID)0x00576058, (LPVOID)CapeE, ASM::JMP);
		//-
		SetRange((LPVOID)0x005FAD70, 7, ASM::NOP);
		SetOp((LPVOID)0x005FAD70, (LPVOID)HideCape, ASM::JMP);
		//-
		SetRange((LPVOID)0x00574D3D, 13, ASM::NOP);
		SetOp((LPVOID)0x00574D3D, (LPVOID)AllowMGCape, ASM::JMP);
		//-
		//SetRange((LPVOID)0x0064160E,10,ASM::NOP);											//-> Pet.cpp
		//SetOp((LPVOID)0x0064160E,(LPVOID)CapeOtherPlayerRefreshUnEquip,ASM::JMP);			//-> Pet.cpp
		////-																				//-> Pet.cpp
		//SetRange((LPVOID)0x006416CA,10,ASM::NOP);											//-> Pet.cpp
		//SetOp((LPVOID)0x006416CA,(LPVOID)CapeOtherPlayerRefreshEquip,ASM::JMP);			//-> Pet.cpp
		//-
	//	SetOp((LPVOID)0x007DD304,(LPVOID)RefreshCapeMain,ASM::CALL);	   //PetHook.cpp
	//	SetOp((LPVOID)0x00833B08,(LPVOID)RefreshCapeMain,ASM::CALL);	   //PetHook.cpp
		SetOp((LPVOID)0x00833BE7, (LPVOID)RefreshCapeUnEquip, ASM::CALL);
		//-
		SetRange((LPVOID)0x005CAFCB, 7, ASM::NOP);
		SetOp((LPVOID)0x005CAFCB, (LPVOID)CapeInventoryPos, ASM::JMP);
		//-
		SetRange((LPVOID)0x007E7827, 4, ASM::NOP);
		SetOp((LPVOID)0x007E7827, (LPVOID)DivineWeapon, ASM::JMP);
		//SetByte((0x00830B8E+1),78); MKey *aqui tira o M DA INTERFACE CLIENTE 97D ATIVAR)
	}

}