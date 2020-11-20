#include "stdafx.h"
#include "Item.h"
#include "BowCrossbow.h"
#include "Defines.h"
#include "Util.h"
#include "TMemory.h"
#include "User.h"
#include "Console.h"
#include "CustomWeapons.h"
#include "Offset.h"
#include "Import.h"
#include "CustomWeapons.h"
// ----------------------------------------------------------------------------------------------
DWORD IsBowItem = 0;
DWORD IsCrossItem = 0;
DWORD BowValue = 0x09C;
DWORD MaxBoneCount = 0x108;
DWORD WorldPosition = 0x0FC;

DWORD oCreateEffect = 0x006D9070; // 1.04D ENG
DWORD ReturnBowCode = 0x0074A12E; // 1.04D ENG
DWORD BowPosition = 0x005CC8ED; // 1.04D ENG
DWORD NextBowPosition = 0x005CC92E; // 1.04D ENG
DWORD BowAddPlayerDimension_Offset = 0x0056617F; // 1.04D ENG

void __declspec(naked) cBowAddSkillEffect()
{
	static DWORD v10;
	static DWORD a7;
	static DWORD a8;
	_asm
	{
		mov ecx, dword ptr ss : [ebp - 0x4]
			mov dword ptr ss : [ebp - 0x14], ecx
			mov IsBowItem, ecx
		mov cx, word ptr ss : [ebp + 0x14]
		mov a7, ecx
		mov cx, word ptr ss : [ebp + 0x18]
		mov a8, ecx
		mov ecx, dword ptr ss : [ebp - 0x0C]
		mov v10, ecx
	}
	//g_Console.AddMessage(5,"a7 = %d a8 = %d v10 = %d", a7, a8, v10);
	// ---
	if (IsBowItem >= GET_ITEM_MODEL(4, 25) && IsBowItem <= GET_ITEM_MODEL(4, 255)) // Angelic Bow
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
				push 297
				call oCreateEffect
		}
	}
	_asm
	{
		jmp ReturnBowCode
	}
}

void __declspec(naked) cBowAddPlayerDimension()
{
	_asm
	{
		cmp dword ptr ss : [ebp + 0x1c], 0x0CA7
		je ReturnLoad
		//
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,25)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,26)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,28)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,29)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,30)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,31)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,32)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,33)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,34)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,35)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,36)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,37)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,38)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,39)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,40)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,41)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,42)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,43)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,44)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,45)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,46)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,47)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,48)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,49)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,50)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,51)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,52)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,53)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,54)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,55)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,56)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,57)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,58)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,59)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,60)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,61)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,62)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,63)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,64)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,65)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,66)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,67)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,68)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,69)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,70)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,71)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,72)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,73)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,74)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,75)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,76)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,77)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,78)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,79)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,80)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,81)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,82)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,83)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,84)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,85)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,86)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,87)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,88)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,89)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,90)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,91)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,92)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,93)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,94)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,95)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,96)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,97)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,98)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4,99)
		je ReturnLoad
		//
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 100)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 101)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 102)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 103)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 104)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 105)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 106)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 107)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 108)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 109)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 110)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 111)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 112)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 113)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 114)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 115)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 116)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 117)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 118)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 119)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 120)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 121)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 122)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 123)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 124)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 125)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 126)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 127)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 128)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 129)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 130)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 131)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 132)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 133)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 134)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 135)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 136)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 137)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 138)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 139)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 140)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 141)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 142)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 143)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 144)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 145)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 146)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 147)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 148)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 149)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 150)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 151)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 152)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 153)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 154)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 155)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 156)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 157)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 158)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 159)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 160)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 161)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 162)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 163)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 164)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 165)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 166)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 167)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 168)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 169)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 170)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 171)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 172)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 173)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 174)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 175)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 176)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 177)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 178)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 179)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 180)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 181)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 182)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 183)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 184)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 185)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 186)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 187)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 188)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 189)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 190)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 191)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 192)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 193)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 194)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 195)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 196)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 197)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 198)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 199)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 200)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 201)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 202)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 203)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 204)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 205)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 206)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 207)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 208)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 209)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 210)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 211)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 212)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 213)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 214)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 215)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 216)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 217)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 218)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 219)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 220)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 221)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 222)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 223)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 224)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 225)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 226)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 227)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 228)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 229)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 230)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 231)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 232)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 233)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 234)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 235)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 236)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 237)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 238)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 239)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 240)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 241)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 242)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 243)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 244)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 245)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 246)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 247)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 248)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 249)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 250)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 251)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 252)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 253)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 254)
		je ReturnLoad
		cmp dword ptr ss : [ebp + 0x1c], GET_ITEM_MODEL(4, 255)
		je ReturnLoad
		// ---
		ReturnLoad :
		// ---
		jmp BowAddPlayerDimension_Offset
	}
}

#define sub_6D6C20_Addr		((signed int(__cdecl*)(int a1, Object* a2, int a3)) 0x6D6C20)
//#define sub_6D9070_Addr		((int(__cdecl*)(int Type, vec3_t Position, vec3_t Angle, vec3_t Light, int SubType, Object* Owner, short PKKey, BYTE Skill, float Scale, BYTE SkillSerial, vec3_t SkillAngle, BYTE SkillHotKey)) 0x6D9070)
#define sub_749C90_Addr		((int(__cdecl*)(ObjectPreview *a4, Object*/*int*/ a5,Object*/*int*/ a6, __int16 a7, __int16 a8, unsigned __int16 SkillID)) 0x749C90)

/*
 
DWORD test1 = (DWORD)a5->Position;
				DWORD test2 = (DWORD)a5->Angle;
				DWORD test3 = (DWORD)a5->Light;
				DWORD test4 = (DWORD)v10;
				DWORD test5 = (DWORD)a5;
				DWORD test6 = (DWORD)a5->Unknown44;
				DWORD test7 = (DWORD)a7;
				DWORD test8 = (DWORD)a8;
				

				_asm
				{
						push - 1
						push 0
						push 0
						push test8
						push test7
						push test6
						push test5
						push test4
						push test3
						push test2
						push test1
						push 335
						call oCreateEffect
				}
 
 */

void SkillEffect(ObjectPreview *a4, Object*/*int*/ a5,Object*/*int*/ a6, __int16 a7, __int16 a8, unsigned __int16 SkillID)
{
	//g_Console.AddMessage(5,"a8 = %d",a8);
	int v10 = 0;
	int FirstIndex = a4->WeaponFirstSlot;
	int SecondIndex = a4->WeaponSecondSlot;

	lpCharObj Character = &*(ObjectCharacter*)*(int*)(0x8128AC4);

	if (a4 == gObjUser.lpViewPlayer)
	{
		FirstIndex = Character->pEquipment[0].ItemID;
		SecondIndex = Character->pEquipment[1].ItemID;
		//g_Console.AddMessage(5,"Name = %s - %s",a4->Name,Character->Name);

		if ( FirstIndex != -1 )
			FirstIndex += 1171;
		if ( SecondIndex != -1 )
			SecondIndex += 1171;
	}

	//g_Console.AddMessage(5,"%d %d %d",a7,a8,SkillID);

	if (SkillID == 52 || SkillID == 416)
	{
		v10 = 2;
		sub_6D6C20_Addr(85, a5, 0);
	}

	*(DWORD*)0x8793730 = SkillID;

	if ( SkillID == 51 || SkillID == 424 )
	{
		sub_6D6C20_Addr(130, a5, 0);
	}

	if ( a8 == 2 )
	{
		v10 = 99;
	}

	if (SkillID == 46)
	{
		//sub_6D9070_Addr(365, *(vec3_t*)a5 + 252, *(vec3_t*)a5+264, *(vec3_t*)a5+156,0,a6,*(WORD*)a5+44,a7,a8,0,0,-1);
		sub_6D9070_Addr(365, a5->Position, a5->Angle, a5->Light,0,a6,a5->Unknown44,a7,a8,0,0,-1);
	}
	else
	{
		switch(FirstIndex)
		{
			case GET_ITEM_MODEL(4,8):
				sub_6D9070_Addr(267, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,9):
				sub_6D9070_Addr(267, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,10):
				sub_6D9070_Addr(271, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,11):
				sub_6D9070_Addr(269, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,12):
				sub_6D9070_Addr(268, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,13):
				sub_6D9070_Addr(274, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,14):
				sub_6D9070_Addr(273, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,16):
				sub_6D9070_Addr(294, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,18):
				sub_6D9070_Addr(321, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,19):
				sub_6D9070_Addr(324, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
		}

		switch (SecondIndex)
		{
			case GET_ITEM_MODEL(4,0):
				sub_6D9070_Addr(266, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,1):
				sub_6D9070_Addr(266, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,2):
				sub_6D9070_Addr(270, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,3):
				sub_6D9070_Addr(266, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,4):
				sub_6D9070_Addr(266, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,5):
				sub_6D9070_Addr(266, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,6):
				sub_6D9070_Addr(272, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,17):
				sub_6D9070_Addr(295, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,20):
				sub_6D9070_Addr(335, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,21):
				sub_6D9070_Addr(296, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,22):
				sub_6D9070_Addr(297, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,23):
				sub_6D9070_Addr(298, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,24):
				sub_6D9070_Addr(509, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
			case GET_ITEM_MODEL(4,27):
				sub_6D9070_Addr(266, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
			break;
		}

		if (gCustomWeapons.CheckElfBow(SecondIndex-ITEM_BASE_MODEL))
		{
			sub_6D9070_Addr(297, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
		}

		if (gCustomWeapons.CheckElfCrossbow(FirstIndex-ITEM_BASE_MODEL))
		{
			sub_6D9070_Addr(297, a5->Position, a5->Angle, a5->Light,v10,a5,a5->Unknown44,a7,a8,0,0,-1);
		}
	}
}

void __declspec(naked) cBowCheckPositionOnMap()
{
	static DWORD ret_continue = 0x005659EE;
	static DWORD ret_succes = 0x00565994;

	static DWORD ItemId;

	__asm
	{
		mov EAX, DWORD PTR SS:[EBP+0x1C]
		mov ItemId, EAX
	}

	if (gCustomWeapons.CheckElfCrossbow(ItemId-ITEM_BASE_MODEL))
	{
		__asm
		{
			jmp ret_succes
		}
	}
	else
	{
		__asm
		{
			CMP DWORD PTR SS:[EBP+0x1C],0x22C
			jmp ret_continue;
		}
	}
}

#define sub_599F10_Addr			((signed int(*)()) 0x599F10)

signed int __cdecl FixBowArrow(WORD *a1)
{
	signed int result; // eax@8
	if ((int)(*a1/512) != 4 || *a1 == 2055 || *a1 == 2063)
	{
		return 0;
	}
	ItemBmdStruct* ItemInfo = pGetItemBmdStruct(*a1);
	if (ItemInfo == 0 || (*a1/512) != 4)
	{
		return 0;
	}
	if (ItemInfo->Slot == 0)
	{
		return 2;
	}
	if (ItemInfo->Slot == 1)
	{
		return 1;
	}
	return 0;
}

ItemBmdStruct* ItemBmdInfo;

void __declspec(naked) cAddMGSetDefense()
{
	static DWORD ret_addr = 0x00781B86;
	static DWORD success_addr = 0x00781B7F;

	static DWORD itemId;

	ItemBmdInfo = 0;

	__asm
	{
		mov itemId,eax
	}

	ItemBmdInfo = pGetItemBmdStruct(itemId);
	
	if (ItemBmdInfo != NULL)
	{
		if (ItemBmdInfo->DW == 0 && ItemBmdInfo->DK == 0 && ItemBmdInfo->ELF == 0 && ItemBmdInfo->DL == 0 && ItemBmdInfo->Sum == 0 && ItemBmdInfo->RF == 0 && ItemBmdInfo->MG != 0 )
		{
			__asm
			{
				jmp ret_addr
			}
		}
	}

	__asm
	{
		MOV BYTE PTR SS:[EBP-0x441],0x0
		jmp ret_addr
	}
}

void InitBows()
{      
	MemorySet(0x00781B2B,0x90,0x5B);
	SetCompleteHook(0xE9,0x00781B2B,&cAddMGSetDefense);



	SetCompleteHook(0xE8,0x5913D0+0xDB ,&FixBowArrow);
	SetCompleteHook(0xE8,0x5913D0+0xF7 ,&FixBowArrow);
	SetCompleteHook(0xE8,0x5A05C0+0x92 ,&FixBowArrow);
	SetCompleteHook(0xE8,0x5A05C0+0x1B5,&FixBowArrow);
	SetCompleteHook(0xE8,0x5B5FC0+0xD34,&FixBowArrow);
	SetCompleteHook(0xE8,0x7E04B0+0xF8 ,&FixBowArrow);

	//SetDword(0x00781B2B+6,0);
	//SetDword(0x0056116F+2,0);
	//0056116F

	//SetCompleteHook(0xE8,0x5A05C0+0x1E,&sub_599F10);


	//SetCompleteHook(0xE8,0x0059438D,&sub_5A09A0);
	//SetCompleteHook(0xE8,0x00599F34,&sub_5A09A0);


	/*SetCompleteHook(0xE8,0x00599F47,&sub_5A09A0);
	SetCompleteHook(0xE8,0x00599FBB,&sub_5A09A0);
	SetCompleteHook(0xE8,0x00599FCE,&sub_5A09A0);
	SetCompleteHook(0xE8,0x005A09C5,&sub_5A09A0);*/

	/*SetCompleteHook(0xE8,0x005A09F4,&sub_5A09A0);
	SetCompleteHook(0xE8,0x005A144D,&sub_5A09A0);
	SetCompleteHook(0xE8,0x005B6E6F,&sub_5A09A0);
	SetCompleteHook(0xE8,0x005C489F,&sub_5A09A0);
	SetCompleteHook(0xE8,0x005C48C7,&sub_5A09A0);
	SetCompleteHook(0xE8,0x007807DD,&sub_5A09A0);
	SetCompleteHook(0xE8,0x0078080C,&sub_5A09A0);
	SetCompleteHook(0xE8,0x007DF787,&sub_5A09A0);
	SetCompleteHook(0xE8,0x007DF79D,&sub_5A09A0);*/


	SetCompleteHook(0xE8,0x6F1100+0x1CDC,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x53  ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x121 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x15C ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x197 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x1D2 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x20D ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x267 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x2A2 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x2DD ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x318 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x395 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x3D0 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x40B ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x446 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x488 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x4C3 ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x4FE ,&SkillEffect);
	SetCompleteHook(0xE8,0x74A670+0x53D ,&SkillEffect);


	MemorySet(0x005659E7,0x90,7);
	SetCompleteHook(0xE9,0x005659E7,&cBowCheckPositionOnMap);

	//SetRange(iBowAddSkillEffect, 6, ASM::NOP);
	//SetJmp((LPVOID)iBowAddSkillEffect, cBowAddSkillEffect);
	//SetOp(iBowAddSkillEffect, &cBowAddSkillEffect, ASM::JMP);
	// ----
	//SetRange(iBowAddInventoryPos, 6, ASM::NOP);
	//SetJmp((LPVOID)iBowAddInventoryPos, cBowAddInventoryPos);
	//SetOp(iBowAddInventoryPos, &cBowAddInventoryPos, ASM::JMP);
	// ----
	SetRange(iBowAddPlayerDimension, 7, ASM::NOP);
	//SetJmp((LPVOID)iBowAddPlayerDimension, cBowAddPlayerDimension);
	SetOp3(iBowAddPlayerDimension, &cBowAddPlayerDimension, ASM::JMP);
	// ----
}
