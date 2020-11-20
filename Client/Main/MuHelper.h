#pragma once

#include "Object.h"

#define sub_95DE10_Addr		((void(__thiscall*)(MUHelper *This)) 0x95DE10)
#define pHelperUsePotion		((char(__thiscall*)(MUHelper *pHelper)) 0x95E980)
#define pGetSkillPos			((int(__stdcall*)(int SkillID)) 0x95F8D0)
#define pHelperUseBuff			((bool(__thiscall*)(MUHelper *pHelper, lpViewObj lpPlayer)) 0x95FDA0)
#define sub_95EC00_Addr			((int(__thiscall*)(MUHelper *pHelper)) 0x95EC00)
#define pHelperUseSkill			((char(__thiscall*)(MUHelper *pHelper, int SkillID, lpViewObj lpTarget, int Type)) 0x95F930)
#define sub_95FCD0_Addr			((char(__thiscall*)(MUHelper *pHelper)) 0x95FCD0)
#define sub_95F0D0_Addr			((char(__thiscall*)(MUHelper *pHelper)) 0x95F0D0)
#define sub_95F490_Addr			((char(__thiscall*)(MUHelper *pHelper, int a1)) 0x95F490)
#define HelperRepairItems		((void(__thiscall*)()) 0x95F6B0)//sub_95F6B0
#define sub_95EFA0_Addr			((char(__thiscall*)(MUHelper *pHelper)) 0x95EFA0)
#define sub_59B2B0_Addr			((void(__cdecl*)(lpViewObj lpPlayer, int a2)) 0x59B2B0)
#define sub_54EA80_Addr			((void(__cdecl*)(lpViewObj lpPlayer)) 0x54EA80)
#define pHelperPartyUseBaff		((char(__thiscall*)(MUHelper *pHelper)) 0x95FE30)
#define sub_95FF40_Addr			((char(__thiscall*)(MUHelper *pHelper)) 0x95FF40)
#define sub_960140_Addr			((bool(__thiscall*)(MUHelper *pHelper, int a1,  int a2)) 0x960140)
#define sub_9600A0_Addr			((char(__thiscall*)(MUHelper *pHelper, int a1, int a2)) 0x9600A0)
#define sub_95FAE0_Addr			((char(__thiscall*)(MUHelper *pHelper, SkillData *a1, int a2)) 0x95FAE0)
class CMuHelper
{
public:
	void Load();
	static void __fastcall Work(MUHelper * pHelper);
	static bool PartyUseBuff(MUHelper * pHelper);
}; extern CMuHelper gMuHelper;