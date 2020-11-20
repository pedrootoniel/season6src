#include "stdafx.h"
#include "NewCharacter.h"
#include "Util.h"
#include "Offset.h"

NewCharacter c_NewCharacter;

NewCharacter::NewCharacter()
{
	//SetCompleteHook(0xE8, 0x4837D0+0x1BC , this->sub_402F20);
}

#define sub_402F20_Addr		((void *(__thiscall*)(char *This)) 0x402F20)
#define sub_407B20_Addr		((void *(__thiscall*)()) 0x407B20)
#define sub_404920_Addr		((void (__thiscall*)(sub_402F20_STRUCT1 *Åhis, int a2)) 0x404920)
#define sub_401210_Addr		((int(__thiscall*)(int This)) 0x401210)
#define sub_4011F0_Addr		((int(__thiscall*)(int This)) 0x4011F0)
#define sub_4ABE90_Addr		((void(__thiscall*)(void *This, int a2, int a3, signed int a4, char a5)) 0x4ABE90)
#define sub_416210_Addr		((float *(__thiscall*)(void *This, int a2, int a3, int a4, int a5, int a6, int a7, int a8, char a9, int a10, float a11, float a12)) 0x416210)
#define sub_401270_Addr		((int(__thiscall*)(int This, char a2)) 0x401270)
#define sub_405240_Addr		((int(__thiscall*)(int This, char a2, char a3, char a4)) 0x405240)
#define sub_401370_Addr		((void *(__thiscall*)(int This, int a2, int a3, int a4, int a5, signed int a6, signed int a7, int a8, int a9, signed int a10, signed int a11, int a12)) 0x401370)
#define sub_4AC500_Addr		((int(__stdcall*)(int a1)) 0x4AC500)
#define sub_404900_Addr		((int(__thiscall*)(int This, char a2)) 0x404900)
#define sub_403700_Addr		((int(__thiscall*)(int This)) 0x403700)
#define sub_407B00_Addr		((void *(__thiscall*)(int This)) 0x407B00)
#define sub_402320_Addr		((int(__thiscall*)(int This, int a1)) 0x402320)
#define sub_401AE0_Addr		((char *(__thiscall*)(int This, int a1, int a3)) 0x401AE0)

void __fastcall NewCharacter::sub_402F20(char *This, void *EDX)
{
	LPVOID v1 = sub_407B20_Addr();
	int v2;
	int v3;
	int v4;

	sub_402F20_STRUCT1 v14;

	sub_404920_Addr(&v14, (int)v1);

	v2 = sub_401210_Addr((int)&v14);
	v3 = sub_4011F0_Addr((int)&v14);

	sub_4ABE90_Addr(This, v3, v2, -1, 0);
	sub_4ABE90_Addr(This + 60, 454, 406, -2, 0);
	sub_416210_Addr(This + 120, 346, 38, 0x791A, 0, 0, 0, 0, 0, 0, 1.0, 1.0);
	sub_416210_Addr(This + 288, 108, 80, -1, 0, 0, 0, 0, 0, 0, 1.0, 1.0);
	sub_416210_Addr(This + 456, 454, 51, -1, 0, 0, 0, 0, 0, 0, 1.0, 1.0);

	for ( int i = 1; i < 3; ++i )
	{
		sub_401270_Addr((int)&This[168 * i + 120], -113);
		sub_405240_Addr((int)&This[168 * i + 120], 0, 0, 0);
	}
	
	unsigned int mInt1[8] = {0xFFE2E2E2, 0xFFE2E2E2, -1, 0xFF777777, 0xFFE2E2E2, 0xFFE2E2E2, -1, 0xFF777777};

	int mInt[7] = {20,21,22,23,24,1687,3150};

	for ( int i = 0; i < 7; ++i )
	{
		sub_401370_Addr((int)&This[224 * i + 624], 108, 26, 31003, 4, 2, 1, 0, 3, 3, 3, 0);
		v4 = sub_402320_Addr(0x8128ADC, (int)mInt[i]);
		sub_401AE0_Addr((int)&This[224 * i + 624], v4, (int)mInt1);
		sub_4AC500_Addr((int)&This[224 * i + 624]);
	}

	for ( int i = 0; i < 2; ++i )
	{
		sub_401370_Addr((int)&This[224 * i + 2192], 54, 30, i + 31132, 3, 2, 1, -1, -1, -1, -1, -1);
		sub_4AC500_Addr((int)&This[224 * i + 2192]);
	}

	sub_9CF630_Addr((int)This + 2644, 0, 0x96u);
	*((DWORD *)This + 699) = 0;
	*((DWORD *)This + 660) = 1;
	sub_404900_Addr((int)&This[224 * *((DWORD*)This + 660) + 624], 1);
	sub_403700_Addr((int)This);
	sub_407B00_Addr((int)&v14);
}