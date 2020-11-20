#include "StdAfx.h"
#include "ItemSmoke.h"
#include "CustomSmoke.h"
#include "Defines.h"
#include "Object.h"
#include "Import.h"
#include "ReadScript.h"
#include "TMemory.h"
// ----------------------------------------------------------------------------------------------

ItemSmokeEffect gItemSmokeEffect;
// ----------------------------------------------------------------------------------------------

DWORD dwProtect;
DWORD pItemType = 0;
// ----------------------------------------------------------------------------------------------

void naked ItemSmokeEffect::SetItemEffect()
{
	__asm
	{
		Mov pItemType, Eax
	}
	// ----
	for (int i = 0; i < MAX_ITEM_SMOKER; i++)
	{	
		if (pItemType == ITEM2(11, gCustomSmoker.m_ItemSmokerInfo[i].ID))
		{
			__asm
			{
				Mov Esi, 0x0057AD8D
				JMP Esi
			}
		}
	}
	// ----
	if (pItemType >= ITEM2(11, 29) && pItemType <= ITEM2(11, 33)) //-> Default 380lvl sets allow
	{
		__asm
		{
			Mov Esi, 0x0057AD8D
			JMP Esi
		}
	}
	// ----
	__asm
	{
		Mov Esi, 0x0057B73B
		JMP Esi
	}
}
// ----------------------------------------------------------------------------------------------

void naked ItemSmokeEffect::SetColorEffect()
{
	__asm
	{
		Mov pItemType, Ecx
	}
	// ----
	for (int i = 0; i < MAX_ITEM_SMOKER; i++)
	{
		if (pItemType == ITEM2(11, gCustomSmoker.m_ItemSmokerInfo[i].ID))
		{	
			gItemSmokeEffect.R = gCustomSmoker.m_ItemSmokerInfo[i].R;
			gItemSmokeEffect.G = gCustomSmoker.m_ItemSmokerInfo[i].G;
			gItemSmokeEffect.B = gCustomSmoker.m_ItemSmokerInfo[i].B;
			// ----
			__asm
			{
				MOV EDX, DWORD PTR SS : [EBP + 0xC]
				MOV EAX, gItemSmokeEffect.R
				MOV DWORD PTR DS : [EDX + 0x9C], EAX
				// ----
				MOV EAX, DWORD PTR SS : [EBP + 0xC]
				MOV ECX, gItemSmokeEffect.G
				MOV DWORD PTR DS : [EAX + 0xA0], ECX
				// ----
				MOV ECX, DWORD PTR SS : [EBP + 0xC]
				MOV EDX, gItemSmokeEffect.B
				MOV DWORD PTR DS : [ECX + 0xA4], EDX
			}
		}
	}
	// ----
	__asm
	{
		Mov Esi, 0x0057AF2E
		JMP Esi
	}
}
// ----------------------------------------------------------------------------------------------

void ItemSmokeEffect::Load()
{
	// ----
	UnProtect((LPVOID)0x0057AD82, 11);
	SetRange((LPVOID)0x0057AD82, 11, ASM::NOP);
	SetOp((LPVOID)0x0057AD82, this->SetItemEffect, ASM::JMP);
	Protect((LPVOID)0x0057AD82, 21, dwProtect);
	// ----
	UnProtect((LPVOID)0x0057AEFA, 47);
	SetRange((LPVOID)0x0057AEFA, 47, ASM::NOP);
	SetOp((LPVOID)0x0057AEFA, this->SetColorEffect, ASM::JMP);
	Protect((LPVOID)0x0057AEFA, 63, dwProtect);
}
// ----------------------------------------------------------------------------------------------