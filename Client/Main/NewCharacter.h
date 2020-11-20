#pragma once

#define sub_402F20_Addr		((void *(__thiscall*)(char *This)) 0x402F20)
#define sub_9CF630_Addr		((BYTE *(__cdecl*)(int a1, int a2, unsigned int a3)) 0x9CF630)
#pragma pack(push, 1)
struct sub_402F20_STRUCT1
{
	BYTE field_0[8];
	DWORD field_8;
	DWORD field_C;
	int field_10;
	DWORD field_14;
	DWORD field_18;
	BYTE field_1C;
	BYTE field_1D;
	BYTE field_1E;
	BYTE field_1F;
	BYTE field_20;
	BYTE field_21;
	BYTE field_22;
	BYTE field_23;
	BYTE field_24;
	BYTE field_25;
	BYTE field_26;
	BYTE field_27;
	DWORD field_28;
	DWORD field_2C;
	BYTE field_30;
	BYTE field_31;
	BYTE gap_32[2];
	DWORD field_34;
	int field_38;
	BYTE gap_3C[4];
	double field_40;
	double field_48;
	double field_50;
	double field_58;
	BYTE field_60;
	BYTE field_61;
	BYTE field_62;
};
#pragma pack(pop)

class NewCharacter
{
public:
	NewCharacter();
	~NewCharacter() {};

	static void __fastcall sub_402F20(char *This, void *EDX);
};

extern NewCharacter c_NewCharacter;