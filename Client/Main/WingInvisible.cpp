#include "stdafx.h"
#include "WingInvisible.h"
#include "TMemory.h"
#include "Defines.h"
#include "Protect.h"
WingInvisible gWingInvisible;

DWORD	WingsSetInvisibleEffect_Pointer;
DWORD	WingsSetInvisibleEffect_Buff;


Naked(WingsSetInvisibleEffect) // -> 12 -> 005EC31D
{
	_asm
	{
		mov WingsSetInvisibleEffect_Buff, edx
			// ----
			mov ecx, dword ptr ss : [ebp + 8]
			mov edx, dword ptr ds : [ecx + 0x30]
			mov WingsSetInvisibleEffect_Pointer, edx
			// ----
			mov edx, WingsSetInvisibleEffect_Buff
	}
	// ---- wing an hien
	if (WingsSetInvisibleEffect_Pointer == 0x1EA5
		//|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 193)
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 202)
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 207)
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 208)
		)

	{
		_asm
		{
			mov WingsSetInvisibleEffect_Buff, 0x0060B37A
				jmp WingsSetInvisibleEffect_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsSetInvisibleEffect_Buff, 0x0060B41D
				jmp WingsSetInvisibleEffect_Buff
		}
	}
}

Naked(WingsSetInvisibleEffect2) // -> 12 -> 005EC31D
{
	_asm
	{
		mov WingsSetInvisibleEffect_Buff, edx
			// ----
			mov ecx, dword ptr ss : [ebp + 8]
			mov edx, dword ptr ds : [ecx + 0x30]
			mov WingsSetInvisibleEffect_Pointer, edx
			// ----
			mov edx, WingsSetInvisibleEffect_Buff
	}
	// ---- wing an hien
	if (WingsSetInvisibleEffect_Pointer == 0x1EA5
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 182)
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 185)
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 203)
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 204)
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 208)
		)

	{
		_asm
		{
			mov WingsSetInvisibleEffect_Buff, 0x0060B37A
				jmp WingsSetInvisibleEffect_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsSetInvisibleEffect_Buff, 0x0060B41D
				jmp WingsSetInvisibleEffect_Buff
		}
	}
}


void WingInvisible::Load()
{
	SetRange((LPVOID)0x0060B36A,12,ASM::NOP);
	if (gProtect.m_MainInfo.CustomItemPack == 0)
	{
		SetOp((LPVOID)0x0060B36A, (LPVOID)WingsSetInvisibleEffect, ASM::JMP);
	}
	else
	{
		SetOp((LPVOID)0x0060B36A, (LPVOID)WingsSetInvisibleEffect2, ASM::JMP);
	}
}