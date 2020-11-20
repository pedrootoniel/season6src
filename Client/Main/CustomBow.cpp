#include "stdafx.h"
#include "Item.h"
#include "Import.h"
#include "TMemory.h"
#include "CustomBow.h"
#include "Defines.h"
#ifdef NOLOAD
CCustomBow gCustomBow;

CCustomBow::CCustomBow() //ok
{

}

CCustomBow::~CCustomBow() //ok
{

}

DWORD IsBowItem = 0;
DWORD IsCrossItem = 0;
DWORD BowValue = 0x09C;
DWORD MaxBoneCount = 0x108;
DWORD WorldPosition = 0x0FC;

DWORD oCreateEffect = 0x006D9070; // 1.04E ENG
DWORD ReturnBowCode = 0x0074A12E; // 1.04E ENG
DWORD ReturnCrossCode = 0x00749DD2; // 1.04E ENG
DWORD BowPosition = 0x005CC8ED; // 1.04E ENG
DWORD NextBowPosition = 0x005CC92E; // 1.04E ENG
DWORD BowAddPlayerDimension_Offset = 0x0056617F; // 1.04E ENG
DWORD CrossPosition = 0x00565994;
DWORD NextCrossPosition = 0x005659E7;

void __declspec(naked) cBowAddSkillEffect()
{
	_asm
	{
			Mov ecx, dword ptr ss : [ebp - 0x4]
			Mov dword ptr ss : [ebp - 0x14], ecx
			Mov IsBowItem, ecx
	}
	// ---
	if (IsBowItem == ITEM2(4, 25)) // Angelic Bow
	{
		_asm
		{
				push - 1
				push 0
				push 0
				mov dx, word ptr ss : [ebp + 0x18]
				push edx
				mov ax, word ptr ss : [ebp + 0x14]
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				mov dx, word ptr ds : [ecx + 0x2C]
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				push eax
				mov ecx, dword ptr ss : [ebp - 0x0C]
				push ecx
				mov edx, dword ptr ss : [ebp + 0x0C]
				add edx, BowValue
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				add eax, MaxBoneCount
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				add ecx, WorldPosition
				push ecx
				push 509
				call oCreateEffect
		}
	}
	if (IsBowItem == ITEM2(4, 28)) // bloobangel
	{
		_asm
		{
				push - 1
				push 0
				push 0
				mov dx, word ptr ss : [ebp + 0x18]
				push edx
				mov ax, word ptr ss : [ebp + 0x14]
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				mov dx, word ptr ds : [ecx + 0x2C]
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				push eax
				mov ecx, dword ptr ss : [ebp - 0x0C]
				push ecx
				mov edx, dword ptr ss : [ebp + 0x0C]
				add edx, BowValue
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				add eax, MaxBoneCount
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				add ecx, WorldPosition
				push ecx
				push 321
				call oCreateEffect
		}
	}
	if (IsBowItem == ITEM2(4, 29)) // darkangel
	{
		_asm
		{
				push - 1
				push 0
				push 0
				mov dx, word ptr ss : [ebp + 0x18]
				push edx
				mov ax, word ptr ss : [ebp + 0x14]
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				mov dx, word ptr ds : [ecx + 0x2C]
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				push eax
				mov ecx, dword ptr ss : [ebp - 0x0C]
				push ecx
				mov edx, dword ptr ss : [ebp + 0x0C]
				add edx, BowValue
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				add eax, MaxBoneCount
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				add ecx, WorldPosition
				push ecx
				push 321
				call oCreateEffect
		}
	}
	if (IsBowItem == ITEM2(4, 31)) // holyangel
	{
		_asm
		{
				push -1
				push 0
				push 0
				mov dx, word ptr ss : [ebp + 0x18]
				push edx
				mov ax, word ptr ss : [ebp + 0x14]
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				mov dx, word ptr ds : [ecx + 0x2C]
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				push eax
				mov ecx, dword ptr ss : [ebp - 0x0C]
				push ecx
				mov edx, dword ptr ss : [ebp + 0x0C]
				add edx, BowValue
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				add eax, MaxBoneCount
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				add ecx, WorldPosition
				push ecx
				push 294
				call oCreateEffect
		}
	}
	 _asm
    {
        jmp ReturnBowCode
    }
}
void __declspec(naked) cCrossAddSkillEffect()
{
   _asm
    {
        mov ecx,dword ptr ss:[ebp-0x0C]
        mov dword ptr ss:[ebp-0x10],ecx
        mov IsCrossItem,ecx
    }
    // ---
    if(IsCrossItem == ITEM2(4,26)) // Devil Crossbow
    {
        _asm
        {
				push - 1
				push 0
				push 0
				mov dx, word ptr ss : [ebp + 0x18]
				push edx
				mov ax, word ptr ss : [ebp + 0x14]
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				mov dx, word ptr ds : [ecx + 0x2C]
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				push eax
				mov ecx, dword ptr ss : [ebp - 0x10]
				push ecx
				mov edx, dword ptr ss : [ebp + 0x0C]
				add edx, BowValue
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				add eax, MaxBoneCount
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				add ecx, WorldPosition
				push ecx
				push 296
				call oCreateEffect
        }
    }
    if(IsCrossItem == ITEM2(4,30)) // Blessed Divine Crossbow of Archangel
    {
        _asm
        {
				push - 1
				push 0
				push 0
				mov dx, word ptr ss : [ebp + 0x18]
				push edx
				mov ax, word ptr ss : [ebp + 0x14]
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				mov dx, word ptr ds : [ecx + 0x2C]
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				push eax
				mov ecx, dword ptr ss : [ebp - 0x10]
				push ecx
				mov edx, dword ptr ss : [ebp + 0x0C]
				add edx, BowValue
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				add eax, MaxBoneCount
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				add ecx, WorldPosition
				push ecx
				push 296
				call oCreateEffect
        }
    }
	 if(IsCrossItem == ITEM2(4,8)) 
    {
        _asm
        {
				push - 1
				push 0
				push 0
				mov dx, word ptr ss : [ebp + 0x18]
				push edx
				mov ax, word ptr ss : [ebp + 0x14]
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				mov dx, word ptr ds : [ecx + 0x2C]
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				push eax
				mov ecx, dword ptr ss : [ebp - 0x10]
				push ecx
				mov edx, dword ptr ss : [ebp + 0x0C]
				add edx, BowValue
				push edx
				mov eax, dword ptr ss : [ebp + 0x0C]
				add eax, MaxBoneCount
				push eax
				mov ecx, dword ptr ss : [ebp + 0x0C]
				add ecx, WorldPosition
				push ecx
            push 296
            call oCreateEffect
        }
    }

    _asm
    {
		jmp ReturnCrossCode				
    }
}



void __declspec(naked) cBowAddInventoryPos()
{
	_asm
	{
		Mov ecx, dword ptr ss : [ebp + 0x8]
		Mov dword ptr ss : [ebp + 0x8], ecx
		Mov IsBowItem, ecx
	}
	// ---
	if (IsBowItem == 0x0CAB
		||IsBowItem == ITEM2(4,25)
		||IsBowItem == ITEM2(4,28)
		||IsBowItem == ITEM2(4,29)
		||IsBowItem == ITEM2(4,31)
		)
	{
		_asm{jmp BowPosition}
	}
	else if(IsBowItem >= ITEM2(13,147) && IsBowItem <= ITEM2(13, 410))
	{
		  _asm
		  {
			  Mov Ecx,0x005CC597
			  Jmp Ecx
		  }
	}
	else
	{
		_asm
		{
			Jmp NextBowPosition
		}
	}
}
__declspec(naked) void cCrossPos()
{
	static DWORD Address1 = 0x00565994;
	static DWORD Address2 = 0x005659E7;
		_asm
		{
			Mov ecx, dword ptr ss : [ebp + 0x1C]
			Mov dword ptr ss : [ebp + 0x1C], ecx
			Mov IsCrossItem, ecx
		}
		if (IsCrossItem >= ITEM2(4,8) && IsCrossItem <= ITEM2(4,14)||
			IsCrossItem >= ITEM2(4,18) && IsCrossItem <= ITEM2(4,19)
			||IsCrossItem == ITEM2(4,26)||IsCrossItem == ITEM2(4,30)
			||IsCrossItem == ITEM2(4,16))
		{
			_asm
			{
				Jmp Address1
			}
		}
		else
		{
			_asm
			{
				Jmp Address2
			}
		}
	
}
void __declspec(naked) cBowAddPlayerDimension()
{
	_asm
	{
		cmp dword ptr ss : [ebp + 0x1c], 0x0CA7
			je ReturnLoad
			cmp dword ptr ss : [ebp + 0x1c], ITEM2(4,25)
			je ReturnLoad
			cmp dword ptr ss : [ebp + 0x1c], ITEM2(4,26)
			je ReturnLoad
			cmp dword ptr ss : [ebp + 0x1c], ITEM2(4,28)
			je ReturnLoad
			cmp dword ptr ss : [ebp + 0x1c], ITEM2(4,29)
			je ReturnLoad
			cmp dword ptr ss : [ebp + 0x1c], ITEM2(4,30)
			je ReturnLoad
			cmp dword ptr ss : [ebp + 0x1c], ITEM2(4,31)
			je ReturnLoad
			// ---
		ReturnLoad :
		// ---
		jmp BowAddPlayerDimension_Offset
	}
}


void CCustomBow::Load()
{
	SetRange((LPVOID)iBowAddSkillEffect,6,ASM::NOP);
	SetOp((LPVOID)iBowAddSkillEffect,(LPVOID)cBowAddSkillEffect,ASM::JMP);
	//--
	SetRange((LPVOID)iBowAddInventoryPos,6,ASM::NOP);
	SetOp((LPVOID)iBowAddInventoryPos,(LPVOID)cBowAddInventoryPos,ASM::JMP);
	//--
	SetRange((LPVOID)0x0056595E,6,ASM::NOP);
	SetOp((LPVOID)0x0056595E,(LPVOID)cCrossPos,ASM::JMP);
	//--
	SetRange((LPVOID)iBowAddPlayerDimension,7,ASM::NOP);
	SetOp((LPVOID)iBowAddPlayerDimension,(LPVOID)cBowAddPlayerDimension,ASM::JMP);
	//--
	SetRange((LPVOID)iCrossAddSkillEffect,6,ASM::NOP);
	SetOp((LPVOID)iCrossAddSkillEffect,(LPVOID)cCrossAddSkillEffect,ASM::JMP);
}
#endif