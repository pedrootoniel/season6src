#include "stdafx.h"
#include "LoadMap.h"
#include "Defines.h"
#include "Import.h"
#include "TMemory.h"

// ----------------------------------------------------------------------------------------------

LoadMap gLoadMap;

LoadMap::LoadMap() //ok
{

}

LoadMap::~LoadMap() //ok
{

}
// ----------------------------------------------------------------------------------------------

DWORD MapTextOffset		= 0x00402320;
DWORD MapJumpOffset		= 0x005D3027;
DWORD MapJumpOffset2	= 0x005D2D19;
DWORD MapReturnOffset	= 0x005D2C32;
// ----
char * arkania_map = "Arkania.tga";
char * acheron_map = "Acheron.tga";
char * deventer_map = "Deventer.tga";
char * uruk_map = "Uruk.tga";
char * ferea_map = "Ferea.tga";
char * teamvsteam = "TeamvsTeam.tga";
// ----------------------------------------------------------------------------------------------
int LoadMap::Mapname(signed int a1)
{
	int result; // eax@2

	switch (a1)
	{
	case 34:
		result = pGetTextLineint(pTextLineThis, 1851);
		break;
	case 33:
		result = pGetTextLineint(pTextLineThis, 1850);
		break;
	case 37:
		result = pGetTextLineint(pTextLineThis, 2177);
		break;
	case 38:
		result = pGetTextLineint(pTextLineThis, 2178);
		break;
	case 39:
		result = pGetTextLineint(pTextLineThis, 2179);
		break;
	case 40:
		result = pGetTextLineint(pTextLineThis, 2324);
		break;
	case 51:
		result = pGetTextLineint(pTextLineThis, 1853);
		break;
	case 57:
		result = pGetTextLineint(pTextLineThis, 1855);
		break;
	case 58:
		result = pGetTextLineint(pTextLineThis, 1856);
		break;
	default:
		if (a1 == 30)
		{
			result = pGetTextLineint(pTextLineThis, 669);
		}
		else if (a1 == 31)
		{
			result = pGetTextLineint(pTextLineThis, 59);
		}
		else if (sub_4E65A0(a1) == 1)
		{
			result = pGetTextLineint(pTextLineThis, 57);
		}
		else if (sub_4DB1C0(a1) == 1)
		{
			if (a1 == 36)
				result = pGetTextLineint(pTextLineThis, 1852);
			else
				result = pGetTextLineint(pTextLineThis, 58);
		}
		else if ((unsigned __int8)sub_4E65C0(a1) == 1)
		{
			result = pGetTextLineint(pTextLineThis, 56);
		}
		else if (a1 == 10)
		{
			result = pGetTextLineint(pTextLineThis, 55);
		}
		else if (a1 == 32)
		{
			result = pGetTextLineint(pTextLineThis, 39);
		}
		else
		{
			//v2 = sub_89CB00();
			if (pMapNumber == 41)
			{
				result = pGetTextLineint(pTextLineThis, 1678);
			}
			else
			{
				//v3 = sub_89CB00();
				if (pMapNumber == 42)
				{
					result = pGetTextLineint(pTextLineThis, 1679);
				}
				else
				{
					//v4 = sub_91C9D0();
					if (pMapNumber >= 45 && pMapNumber <= 50)
					{
						result = pGetTextLineint(pTextLineThis, 2369);
					}
					else
					{
						switch (a1)
						{
						case 51:
							result = pGetTextLineint(pTextLineThis, 1853);
							break;
						case 56:
							result = pGetTextLineint(pTextLineThis, 1854);
							break;
						case 62:
							result = pGetTextLineint(pTextLineThis, 2611);
							break;
						case 64:
							result = pGetTextLineint(pTextLineThis, 2703);
							break;
						case 63:
							result = pGetTextLineint(pTextLineThis, 2686);
							break;
						case 65:
							result = pGetTextLineint(pTextLineThis, 3057);
							break;
						case 66:
							result = pGetTextLineint(pTextLineThis, 3057);
							break;
						case 67:
							result = pGetTextLineint(pTextLineThis, 3057);
							break;
						case 68:
							result = pGetTextLineint(pTextLineThis, 3057);
							break;
						case 69:
							result = pGetTextLineint(pTextLineThis, 2806);
							break;
						case 70:
							result = pGetTextLineint(pTextLineThis, 2806);
							break;
						case 71:
							result = pGetTextLineint(pTextLineThis, 2806);
							break;
						case 72:
							result = pGetTextLineint(pTextLineThis, 2806);
							break;
						case 79:
							result = pGetTextLineint(pTextLineThis, 3017);
							break;
						case 82: //Arkania
							result = pGetTextLineint(pTextLineThis, 3170);
							break;
						case 83: //Acheron
							result = pGetTextLineint(pTextLineThis, 3171);
							break;
						case 84: //Deventer
							result = pGetTextLineint(pTextLineThis, 3172);
							break;
						case 85: //Uruk
							result = pGetTextLineint(pTextLineThis, 3173);
							break;
						case 86: //Ferea
							result = pGetTextLineint(pTextLineThis, 3174);
							break;
						case 87: //TvsT
							result = pGetTextLineint(pTextLineThis, 3175);
							break;
						default:
							if (a1 != 80 && a1 != 81)
								result = pGetTextLineint(pTextLineThis, a1 + 30);
							else
								result = pGetTextLineint(pTextLineThis, 3285);
							break;
						}
					}
				}
			}
		}
		break;
	}

	return result;
}

// ----------------------------------------------------------------------------------------------

Naked(LoadInterfaceMapName)
{
	_asm
	{
		MOV DWORD PTR SS : [EBP - 0x848], 0x51
		PUSH 0x00D25498							// Karutan
		LEA EAX, DWORD PTR SS : [EBP - 0x28]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP, 0x0C
		MOV DWORD PTR SS : [EBP - 0xA74], EAX
		MOV EDX, DWORD PTR SS : [EBP - 0xA74]
		MOV DWORD PTR SS : [EBP - 0xA78], EDX
		MOV BYTE PTR SS : [EBP - 0x4], 0x43
		MOV EAX, DWORD PTR SS : [EBP - 0xA78]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x848]
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x868]
		ADD ECX, 0x4
		CALL InterfaceLoad2
		MOV ECX, EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS : [EBP - 0x4], 0x2
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS : [EBP - 0x4], -0x1
		LEA ECX, DWORD PTR SS : [EBP - 0x28]

		MOV DWORD PTR SS : [EBP - 0x848], 0x52	// 82 Arkania Custom Map
		PUSH arkania_map						// Arkania
		LEA EAX, DWORD PTR SS : [EBP - 0x28]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP, 0x0C
		MOV DWORD PTR SS : [EBP - 0xA74], EAX
		MOV EDX, DWORD PTR SS : [EBP - 0xA74]
		MOV DWORD PTR SS : [EBP - 0xA78], EDX
		MOV BYTE PTR SS : [EBP - 0x4], 0x43
		MOV EAX, DWORD PTR SS : [EBP - 0xA78]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x848]
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x868]
		ADD ECX, 0x4
		CALL InterfaceLoad2
		MOV ECX, EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS : [EBP - 0x4], 0x2
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS : [EBP - 0x4], -0x1
		LEA ECX, DWORD PTR SS : [EBP - 0x28]

		MOV DWORD PTR SS : [EBP - 0x848], 0x53	// 83 Acheron
		PUSH acheron_map						// Acheron
		LEA EAX, DWORD PTR SS : [EBP - 0x28]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP, 0x0C
		MOV DWORD PTR SS : [EBP - 0xA74], EAX
		MOV EDX, DWORD PTR SS : [EBP - 0xA74]
		MOV DWORD PTR SS : [EBP - 0xA78], EDX
		MOV BYTE PTR SS : [EBP - 0x4], 0x43
		MOV EAX, DWORD PTR SS : [EBP - 0xA78]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x848]
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x868]
		ADD ECX, 0x4
		CALL InterfaceLoad2
		MOV ECX, EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS : [EBP - 0x4], 0x2
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS : [EBP - 0x4], -0x1
		LEA ECX, DWORD PTR SS : [EBP - 0x28]

		MOV DWORD PTR SS : [EBP - 0x848], 0x54	// 84 Map Deventer
		PUSH deventer_map						// Deventer
		LEA EAX, DWORD PTR SS : [EBP - 0x28]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP, 0x0C
		MOV DWORD PTR SS : [EBP - 0xA74], EAX
		MOV EDX, DWORD PTR SS : [EBP - 0xA74]
		MOV DWORD PTR SS : [EBP - 0xA78], EDX
		MOV BYTE PTR SS : [EBP - 0x4], 0x43
		MOV EAX, DWORD PTR SS : [EBP - 0xA78]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x848]
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x868]
		ADD ECX, 0x4
		CALL InterfaceLoad2
		MOV ECX, EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS : [EBP - 0x4], 0x2
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS : [EBP - 0x4], -0x1
		LEA ECX, DWORD PTR SS : [EBP - 0x28]

		MOV DWORD PTR SS : [EBP - 0x848], 0x55	// 85 Map Uruk
		PUSH uruk_map						// Uruk
		LEA EAX, DWORD PTR SS : [EBP - 0x28]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP, 0x0C
		MOV DWORD PTR SS : [EBP - 0xA74], EAX
		MOV EDX, DWORD PTR SS : [EBP - 0xA74]
		MOV DWORD PTR SS : [EBP - 0xA78], EDX
		MOV BYTE PTR SS : [EBP - 0x4], 0x43
		MOV EAX, DWORD PTR SS : [EBP - 0xA78]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x848]
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x868]
		ADD ECX, 0x4
		CALL InterfaceLoad2
		MOV ECX, EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS : [EBP - 0x4], 0x2
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS : [EBP - 0x4], -0x1
		LEA ECX, DWORD PTR SS : [EBP - 0x28]

		MOV DWORD PTR SS : [EBP - 0x848], 0x56	// 86 Map Ferea
		PUSH ferea_map						// Ferea
		LEA EAX, DWORD PTR SS : [EBP - 0x28]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP, 0x0C
		MOV DWORD PTR SS : [EBP - 0xA74], EAX
		MOV EDX, DWORD PTR SS : [EBP - 0xA74]
		MOV DWORD PTR SS : [EBP - 0xA78], EDX
		MOV BYTE PTR SS : [EBP - 0x4], 0x43
		MOV EAX, DWORD PTR SS : [EBP - 0xA78]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x848]
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x868]
		ADD ECX, 0x4
		CALL InterfaceLoad2
		MOV ECX, EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS : [EBP - 0x4], 0x2
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS : [EBP - 0x4], -0x1
		LEA ECX, DWORD PTR SS : [EBP - 0x28]
		// ----

		MOV DWORD PTR SS : [EBP - 0x848], 0x57	// 87 Map TvT
		PUSH teamvsteam						// TvT
		LEA EAX, DWORD PTR SS : [EBP - 0x28]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		PUSH ECX
		CALL InterfaceLoad1
		ADD ESP, 0x0C
		MOV DWORD PTR SS : [EBP - 0xA74], EAX
		MOV EDX, DWORD PTR SS : [EBP - 0xA74]
		MOV DWORD PTR SS : [EBP - 0xA78], EDX
		MOV BYTE PTR SS : [EBP - 0x4], 0x43
		MOV EAX, DWORD PTR SS : [EBP - 0xA78]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0x848]
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x868]
		ADD ECX, 0x4
		CALL InterfaceLoad2
		MOV ECX, EAX
		CALL InterfaceLoad3
		MOV BYTE PTR SS : [EBP - 0x4], 0x2
		LEA ECX, DWORD PTR SS : [EBP - 0x864]
		CALL InterfaceLoad4
		MOV DWORD PTR SS : [EBP - 0x4], -0x1
		LEA ECX, DWORD PTR SS : [EBP - 0x28]

		// ----
		CALL InterfaceLoad4
		MOV ECX, DWORD PTR SS : [EBP - 0xC]
		MOV DWORD PTR FS : [0x1], ECX
		// ----
		MOV EDI, 0x0047FD08
		JMP EDI
		// ----
		InterfaceLoad1 :
		MOV EDI, 0x0047C220
		JMP EDI
		// ----
		InterfaceLoad2 :
		MOV EDI, 0x00480160
		JMP EDI
		// ----
		InterfaceLoad3 :
		MOV EDI, 0x00409AF0
		JMP EDI
		// ----
		InterfaceLoad4 :
		MOV EDI, 0x00409AD0
		JMP EDI
		// ----
		MOV ESP, EBP
		POP EBP
		RETN
	}
}

void LoadMap::Load()
{
	SetOp((LPVOID)0x00520ECF, LoadMap::Mapname, ASM::CALL);
	SetOp((LPVOID)0x00520F1F, LoadMap::Mapname, ASM::CALL);
	SetOp((LPVOID)0x0063E743, LoadMap::Mapname, ASM::CALL);
	SetOp((LPVOID)0x00640EB2, LoadMap::Mapname, ASM::CALL);
	SetOp((LPVOID)0x007D2DD9, LoadMap::Mapname, ASM::CALL);
	SetOp((LPVOID)0x007E6C0F, LoadMap::Mapname, ASM::CALL);
	SetOp((LPVOID)0x0084AEF7, LoadMap::Mapname, ASM::CALL);

	//--
	SetRange((LPVOID)0x0047FC85, 131, ASM::NOP);
	SetOp((LPVOID)0x0047FC85, (LPVOID)LoadInterfaceMapName, ASM::JMP);
	// Fix Check .map files
	SetByte((PVOID)0x0062EBF8, 0xEB);
	SetByte((PVOID)0x0062EBFE, 0xEB);
	// Fix Check .att files
	SetByte((PVOID)0x0062EE42, 0xEB);
	SetByte((PVOID)0x0062EE48, 0xEB);
	// Fix Check .obj files
	SetByte((PVOID)0x0062EEE5, 0xEB);
	SetByte((PVOID)0x0062EEEB, 0xEB);
	//increase terrain
	SetByte((PVOID)0x0062EBF7,0x69);
	SetByte((PVOID)0x0062EE41,0x69);
	SetByte((PVOID)0x0062EEE4,0x69);
}
// ----------------------------------------------------------------------------------------------