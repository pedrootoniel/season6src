#include "stdafx.h"
#include "TMemory.h"
#include "Import.h"
#include "Defines.h"
#include "Item.h"
#include "Fenrir.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"

NewPets	gNewPets;

Naked(SetNewPetSkins)
{
	DWORD Adr, Adr1, Adr2, Adr3;
	_asm
	{
		//White Tiger
		MOV ECX, DWORD PTR SS : [EBP + 8]
		MOVZX EDX, BYTE PTR DS : [ECX + 0x17]
		CMP EDX, 8		// Exc Option
		JNE HullWolf
		push 0
		push 0
		MOV EAX, DWORD PTR SS : [EBP - 4]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 4]
		ADD ECX, 0x0FC
		PUSH ECX
		PUSH PetWhiteTiger
		mov Adr, 0x00501700
		CALL Adr
		ADD ESP, 0x14
		mov Adr2, 0x008360DD
		JMP SHORT Adr2

HullWolf:
		MOV ECX, DWORD PTR SS : [EBP + 8]
		MOVZX EDX, BYTE PTR DS : [ECX + 0x17]
		CMP EDX, 16		// Exc option
		JNE Beast
		push 0
		push 0
		MOV EAX, DWORD PTR SS : [EBP - 4]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 4]
		ADD ECX, 0x0FC
		PUSH ECX
		PUSH PetHullWolf
		mov Adr, 0x00501700
		CALL Adr
		ADD ESP, 0x14
		mov Adr2, 0x008360DD
		JMP SHORT Adr2

Beast:
		MOV ECX, DWORD PTR SS : [EBP + 8]
		MOVZX EDX, BYTE PTR DS : [ECX + 0x17]
		CMP EDX, 32		// Exc option
		JNE FenrirRed
		push 0
		push 0
		MOV EAX, DWORD PTR SS : [EBP - 4]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 4]
		ADD ECX, 0x0FC
		PUSH ECX
		PUSH PetBeast
		mov Adr, 0x00501700
		CALL Adr
		ADD ESP, 0x14
		mov Adr2, 0x008360DD
		JMP SHORT Adr2
FenrirRed:
		push 0
		push 0
		MOV EAX, DWORD PTR SS : [EBP - 4]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 4]
		ADD ECX, 0x0FC
		PUSH ECX
		PUSH 0x181
		mov Adr3, 0x00501700
		CALL Adr3
		ADD ESP, 0x14
		mov Adr2, 0x008360DD
		JMP SHORT Adr2
	}
}

Naked(FixVisualBug)
{
	DWORD Adr, Adr1, Adr2, Adr3;
	_asm
	{
		//White Tiger
		MOVZX ECX, BYTE PTR SS : [EBP - 2]
		CMP ECX, 8		// Exc Option
		JNE HullWolf
		push 0
		push 0
		MOV EDX, DWORD PTR SS : [EBP - 0x14]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x14]
		ADD EAX, 0x0FC
		PUSH EAX
		PUSH PetWhiteTiger
		mov Adr, 0x00501700
		CALL Adr
		ADD ESP, 0x14
		mov Adr2, 0x00641914
		JMP SHORT Adr2

HullWolf:
		MOVZX ECX, BYTE PTR SS : [EBP - 2]
		CMP ECX, 16		// Exc Option
		JNE Beast
		push 0
		push 0
		MOV EDX, DWORD PTR SS : [EBP - 0x14]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x14]
		ADD EAX, 0x0FC
		PUSH EAX
		PUSH PetHullWolf
		mov Adr, 0x00501700
		CALL Adr
		ADD ESP, 0x14
		mov Adr2, 0x00641914
		JMP SHORT Adr2

Beast:
		MOVZX ECX, BYTE PTR SS : [EBP - 2]
		CMP ECX, 32		// Exc Option
		JNE FenrirRed
		push 0
		push 0
		MOV EDX, DWORD PTR SS : [EBP - 0x14]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x14]
		ADD EAX, 0x0FC
		PUSH EAX
		PUSH PetBeast
		mov Adr, 0x00501700
		CALL Adr
		ADD ESP, 0x14
		mov Adr2, 0x00641914
		JMP SHORT Adr2

FenrirRed:
		push 0
		push 0
		MOV EDX, DWORD PTR SS : [EBP - 0x14]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x14]
		ADD EAX, 0x0FC
		PUSH EAX
		PUSH 0x181
		mov Adr3, 0x00501700
		CALL Adr3
		ADD ESP, 0x14
		mov Adr2, 0x00641914
		JMP SHORT Adr2
	}
}

Naked(AsmTest3)
{
	DWORD Adr1, Adr2;
	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x18]
		MOVZX ECX, BYTE PTR DS : [EAX + 0x29B]
		CMP ECX, 0x8							// Excelent option for new pet
		JNE SHORT HullWolf
		PUSH 0
		PUSH 0
		MOV EDX, DWORD PTR SS : [EBP - 0x18]
		ADD EDX, 0x604
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x18]
		ADD EAX, 0x374
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x18]
		ADD ECX, 0x470
		PUSH ECX
		PUSH PetWhiteTiger						// Here is Skin Number on Hex
		mov Adr1, 0x005013B0
		CALL Adr1
		ADD ESP, 0x18
		mov Adr2, 0x0048FAAC
		JMP SHORT Adr1

HullWolf:
		MOV EAX, DWORD PTR SS : [EBP - 0x18]
		MOVZX ECX, BYTE PTR DS : [EAX + 0x29B]
		CMP ECX, 0x16							// Excelent option for new pet
		JNE SHORT Beast
		PUSH 0
		PUSH 0
		MOV EDX, DWORD PTR SS : [EBP - 0x18]
		ADD EDX, 0x604
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x18]
		ADD EAX, 0x374
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x18]
		ADD ECX, 0x470
		PUSH ECX
		PUSH PetHullWolf						// Here is Skin Number on Hex
		mov Adr1, 0x005013B0
		CALL Adr1
		ADD ESP, 0x18
		mov Adr2, 0x0048FAAC
		JMP SHORT Adr1
Beast:
		MOV EAX, DWORD PTR SS : [EBP - 0x18]
		MOVZX ECX, BYTE PTR DS : [EAX + 0x29B]
		CMP ECX, 0x32							// Excelent option for new pet
		JNE SHORT Here
		PUSH 0
		PUSH 0
		MOV EDX, DWORD PTR SS : [EBP - 0x18]
		ADD EDX, 0x604
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x18]
		ADD EAX, 0x374
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x18]
		ADD ECX, 0x470
		PUSH ECX
		PUSH PetBeast						// Here is Skin Number on Hex
		mov Adr1, 0x005013B0
		CALL Adr1
		ADD ESP, 0x18
		mov Adr2, 0x0048FAAC
		JMP SHORT Adr1

		Here:
		PUSH 0
		PUSH 0
		MOV EDX, DWORD PTR SS : [EBP - 0x18]
		ADD EDX, 0x604
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x18]
		ADD EAX, 0x374
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x18]
		ADD ECX, 0x470
		PUSH ECX
		PUSH 0x181
		mov Adr1, 0x005013B0
		CALL Adr1
		ADD ESP, 0x18
		mov Adr2, 0x0048FAAC
		JMP SHORT Adr1
	}
}

Naked(AsmTest4)
{
	DWORD Adr1, Adr2;
	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x0C]
		MOVZX EDX, BYTE PTR DS : [ECX + 0x17]
		CMP EDX, 0x8
		JNE SHORT HullWolf
		PUSH 0
		PUSH 0
		MOV EAX, DWORD PTR SS : [EBP - 0x10]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x10]
		ADD ECX, 0x0FC
		PUSH ECX
		PUSH PetWhiteTiger						// Here is Skin Number on Hex
		mov Adr1, 0x00501700
		CALL Adr1
		ADD ESP, 14
		mov Adr2, 0x005C7AD6
		JMP SHORT Adr2

HullWolf:
		MOV ECX, DWORD PTR SS : [EBP - 0x0C]
		MOVZX EDX, BYTE PTR DS : [ECX + 0x17]
		CMP EDX, 0x16
		JNE SHORT Beast
		PUSH 0
		PUSH 0
		MOV EAX, DWORD PTR SS : [EBP - 0x10]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x10]
		ADD ECX, 0x0FC
		PUSH ECX
		PUSH PetHullWolf					// Here is Skin Number on Hex
		mov Adr1, 0x00501700
		CALL Adr1
		ADD ESP, 14
		mov Adr2, 0x005C7AD6
		JMP SHORT Adr2
Beast:
		MOV ECX, DWORD PTR SS : [EBP - 0x0C]
		MOVZX EDX, BYTE PTR DS : [ECX + 0x17]
		CMP EDX, 0x32
		JNE SHORT Here
		PUSH 0
		PUSH 0
		MOV EAX, DWORD PTR SS : [EBP - 0x10]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x10]
		ADD ECX, 0x0FC
		PUSH ECX
		PUSH PetBeast					// Here is Skin Number on Hex
		mov Adr1, 0x00501700
		CALL Adr1
		ADD ESP, 14
		mov Adr2, 0x005C7AD6
		JMP SHORT Adr2

Here:
		PUSH 0
		PUSH 0
		MOV EAX, DWORD PTR SS : [EBP - 0x10]
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x10]
		ADD ECX, 0x0FC
		PUSH ECX
		PUSH 0x181							// Here is Skin Number on Hex
		mov Adr1, 0x00501700
		CALL Adr1
		ADD ESP, 14
		mov Adr2, 0x005C7AD6
		JMP SHORT Adr2
	}
}

Naked(AsmTest5)
{
	DWORD Adr1, Adr2;
	_asm
	{
		MOVZX ECX, BYTE PTR SS : [EBP - 0x2]
		CMP ECX, 0x8
		JNE SHORT HullWolf
		PUSH 0
		PUSH 0
		MOV EDX, DWORD PTR SS : [EBP - 0x14]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x14]
		ADD EAX, 0x0FC
		PUSH EAX
		PUSH PetWhiteTiger						// Here is Skin Number on Hex
		mov Adr1, 0x00501700
		CALL Adr1
		ADD ESP, 14
		mov Adr2, 0x00641914
		JMP SHORT Adr2
		//
HullWolf:
		MOVZX ECX, BYTE PTR SS : [EBP - 0x2]
		CMP ECX, 0x16
		JNE SHORT Beast
		PUSH 0
		PUSH 0
		MOV EDX, DWORD PTR SS : [EBP - 0x14]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x14]
		ADD EAX, 0x0FC
		PUSH EAX
		PUSH PetHullWolf						// Here is Skin Number on Hex
		mov Adr1, 0x00501700
		CALL Adr1
		ADD ESP, 14
		mov Adr2, 0x00641914
		JMP SHORT Adr2
		//
Beast:
		MOVZX ECX, BYTE PTR SS : [EBP - 0x2]
		CMP ECX, 0x32
		JNE SHORT Here
		PUSH 0
		PUSH 0
		MOV EDX, DWORD PTR SS : [EBP - 0x14]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x14]
		ADD EAX, 0x0FC
		PUSH EAX
		PUSH PetBeast						// Here is Skin Number on Hex
		mov Adr1, 0x00501700
		CALL Adr1
		ADD ESP, 14
		mov Adr2, 0x00641914
		JMP SHORT Adr2
		//
		Here :
		PUSH 0
		PUSH 0
		MOV EDX, DWORD PTR SS : [EBP - 0x14]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x14]
		ADD EAX, 0x0FC
		PUSH EAX
		PUSH 0x181
		mov Adr1, 0x00501700
		CALL Adr1
		ADD ESP, 14
		mov Adr2, 0x00641914
		JMP SHORT Adr2
	}
}

Naked(AsmTest6)
{
	DWORD Adr1, Adr2;
	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP + 0x8]
		CMP DWORD PTR DS : [ECX + 0x30], 0x183
		JE SHORT Here
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		CMP DWORD PTR DS : [EDX + 0x30], PetWhiteTiger
		JE SHORT Here
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		CMP DWORD PTR DS : [EDX + 0x30], PetHullWolf
		JE SHORT Here
		MOV EDX, DWORD PTR SS : [EBP + 0x8]
		CMP DWORD PTR DS : [EDX + 0x30], PetBeast
		JE SHORT Here
		Here :
		mov Adr1, 0x0050387C
		JMP Adr1
	}
}

Naked(SetNewPetMovement) 
{
	DWORD Adr1,Adr2;
	_asm
	{
		CMP DWORD PTR SS:[EBP-0x124],0x180 //Golden Fenrir
		JLE SHORT Here
		CMP DWORD PTR SS:[EBP-0x124],0x181 //Golden Fenrir
		JLE SHORT Here
		CMP DWORD PTR SS:[EBP-0x124],0x182 //Golden Fenrir
		JLE SHORT Here
		CMP DWORD PTR SS:[EBP-0x124],0x183 //Golden Fenrir
		JLE SHORT Here
		CMP DWORD PTR SS:[EBP-0x124], PetWhiteTiger
		JE SHORT Here
		CMP DWORD PTR SS:[EBP-0x124], PetHullWolf
		JE SHORT Here
		CMP DWORD PTR SS:[EBP-0x124], PetBeast
		JE SHORT Here
		MOV Adr2, 0x0050339A
		JMP Adr2
Here:
		MOV Adr1, 0x0050190F
		JMP Adr1
	}
}

Naked(SetNewPetScale)
{
	DWORD Adr1,Adr2,Adr3;
	_asm
	{
		MOV DWORD PTR SS:[EBP-0x04],EAX
		CMP DWORD PTR SS:[EBP-0x04],0x0E9
		JE ScaleItNow
		MOV DWORD PTR SS:[EBP-0x04],EAX
		CMP DWORD PTR SS:[EBP-0x04],0x143
		JE ScaleItNow
		MOV DWORD PTR SS:[EBP-0x04],EAX
		CMP DWORD PTR SS:[EBP-0x04],0x0E2
		JE ScaleItNow
		MOV DWORD PTR SS:[EBP-0x04],EAX
		CMP DWORD PTR SS:[EBP-0x04],PetWhiteTiger
		JE ScaleItNow
		MOV DWORD PTR SS:[EBP-0x04],EAX
		CMP DWORD PTR SS:[EBP-0x04],PetHullWolf
		JE ScaleItNow
		MOV DWORD PTR SS:[EBP-0x04],EAX
		CMP DWORD PTR SS:[EBP-0x04],PetBeast
		JE ScaleItNow
		CMP DWORD PTR SS:[EBP-0x04],0x183 //Golden fenrir
		JG DontScale		
		CMP DWORD PTR SS:[EBP-0x04],0x180 //Red Fenrir
		JGE ScaleItNow
		MOV Adr3,0x0050153E
		JMP Adr3
DontScale:
		MOV Adr1,0x0050155E
		JMP SHORT Adr1
ScaleItNow:
		MOV Adr2,0x00501579
		JMP SHORT Adr2
	}
}

struct TestStruct
{
	byte Gap[8];
	int Texture;
	int EffectID;
	byte Gap2[56];
	float R;
	float G;
	float B;
};
TestStruct *Temp1;

Naked(SetNewPetSkillEffect)
{
	DWORD Adr1,Adr2;
	_asm
	{
		mov Adr1, EDX
	}

	Temp1 = (TestStruct*) Adr1;

	if (&Temp1->EffectID)
	{
		switch (Temp1->EffectID)
		{
		
		case 1:
			Temp1->Texture = 0x7D86u;
			Temp1->R = 1.0;
			Temp1->G = 0.6;
			Temp1->B = 0.6;
			break;
		case 2:
			Temp1->Texture = 0x7D86u;
			Temp1->R = 0.7;
			Temp1->G = 0.7;
			Temp1->B = 1.0;
			break;
		case 3:
			Temp1->Texture = 0x7D86u;
			Temp1->R = 0.9;
			Temp1->G = 0.9;
			Temp1->B = 0.3;
			break;
		case 4:
			Temp1->Texture = 0x7DECu;
			Temp1->R = 0.1;
			Temp1->G = 0.8;
			Temp1->B = 0.1;
			break;
		case 5:
			Temp1->Texture = 0x7DECu;
			Temp1->R = 1.0;
			Temp1->G = 0.3;
			Temp1->B = 0.2;
			break;
		case 6:
			Temp1->Texture = 0x7DECu;
			Temp1->R = 0.2;
			Temp1->G = 0.3;
			Temp1->B = 1.0;
			break;
		case 7:
			Temp1->Texture = 0x7DECu;
			Temp1->R = 0.8;
			Temp1->G = 0.8;
			Temp1->B = 0.1;
			break;

	//WHITE TIGER
		case 8:
			Temp1->Texture = 0x7D1Au;
			Temp1->R = 0.5;
			Temp1->G = 0.01;
			Temp1->B = 0.01;
			break;
		case 11:
			Temp1->Texture = 0x7D1Au;
			Temp1->R = 0.5;
			Temp1->G = 0.01;
			Temp1->B = 0.01;
			break;
		case 12:
			Temp1->Texture = 0x7D1Au;
			Temp1->R = 0.3;
			Temp1->G = 0.01;
			Temp1->B = 0.4;
			break;

	//HULL WOLF (Ice Effect)
		case 13:
			Temp1->Texture = 0x7E35;
			Temp1->R = 0.1;
			Temp1->G = 0.1;
			Temp1->B = 1.0;
			break;
		case 16:
			Temp1->Texture = 0x7E36;
			Temp1->R = 0.1;
			Temp1->G = 0.1;
			Temp1->B = 1.0;
			break;
		case 17:
			Temp1->Texture = 0x7E36;
			Temp1->R = 0.1;
			Temp1->G = 0.1;
			Temp1->B = 1.0;
			break;

	//BEAST
		case 18:
			Temp1->Texture = 0x7D1E;
			Temp1->R = 1.0;
			Temp1->G = 0.35;
			Temp1->B = 0.0;
			break;
		case 21:
			Temp1->Texture = 0x7D1F;
			Temp1->R = 1.0;
			Temp1->G = 0.35;
			Temp1->B = 0.0;
			break;
		case 22:
			Temp1->Texture = 0x7D1C;
			Temp1->R = 1.0;
			Temp1->G = 0.35;
			Temp1->B = 0.0;
			break;

		default:
			Temp1->Texture = 0x7D86u;
			Temp1->R = 0.7;
			Temp1->G = 1.0;
			Temp1->B = 0.7;
		}
	}

	_asm
	{
		MOV Adr2, 0x00730079
		JMP Adr2
	}

}

Naked(SetNewPetItemLevelTooltipLines)
{
	DWORD Addr1, Addr2;

	_asm
	{
		MOV Addr1, 0x007E3FC3
		MOV Addr2, 0x007E3FDE

		MOV EDX,DWORD PTR SS:[EBP+0x10]
		MOVZX EAX,BYTE PTR DS:[EDX+0x17]
		CMP EAX, 4 //Golden Fenrir
		JNZ SHORT WhiteTiger
		MOV ECX,DWORD PTR SS:[EBP-0x13C8]
		MOV DWORD PTR DS:[ECX+0x11BB64],0x03 //Add 3

WhiteTiger:
		MOV EDX,DWORD PTR SS:[EBP+0x10]
		MOVZX EAX,BYTE PTR DS:[EDX+0x17]
		CMP EAX, 8 //Exc Option
		JNZ SHORT HullWolf
		MOV ECX,DWORD PTR SS:[EBP-0x13C8]
		MOV DWORD PTR DS:[ECX+0x11BB64],0x03 //Add 17

HullWolf:
		MOV EDX,DWORD PTR SS:[EBP+0x10]
		MOVZX EAX,BYTE PTR DS:[EDX+0x17]
		CMP EAX, 16 //Exc Option
		JNZ SHORT Beast
		MOV ECX,DWORD PTR SS:[EBP-0x13C8]
		MOV DWORD PTR DS:[ECX+0x11BB64],0x03 //Add 18

Beast:
		MOV EDX,DWORD PTR SS:[EBP+0x10]
		MOVZX EAX,BYTE PTR DS:[EDX+0x17]
		CMP EAX, 32 //Exc Option
		JNZ SHORT TheExit
		MOV ECX,DWORD PTR SS:[EBP-0x13C8]
		MOV DWORD PTR DS:[ECX+0x11BB64],0x03 //Add 19

TheExit:
		JMP SHORT Addr1
	}
}

ObjectItem *TheItem;
Naked(SetNewPetItemNameColor)
{
	DWORD Adr1,Adr2;
	_asm
	{
		MOV EBX, DWORD PTR SS:[EBP+0x10]
		MOV Adr1, EBX
	}

	TheItem = (ObjectItem*) Adr1;

	if(TheItem->ItemID == ITEM(13,37) && TheItem->ExcellentOption == 1)
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x6C],0x2 //My New Item Name Color
		}
	}

	else if(TheItem->ItemID == ITEM(13,37) && TheItem->ExcellentOption == 2)
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x6C],0x3 //My New Item Name Color
		}
	}

	else if(TheItem->ItemID == ITEM(13,37) && TheItem->ExcellentOption == 4)
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x6C],0x4 //My New Item Name Color
		}
	}

	else if(TheItem->ItemID == ITEM(13,37) && TheItem->ExcellentOption == 8)
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x6C],0x5 //My New Item Name Color
		}
	}

	else if(TheItem->ItemID == ITEM(13,37) && TheItem->ExcellentOption == 16)
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x6C],0x8 //My New Item Name Color
		}
	}

	else if(TheItem->ItemID == ITEM(13,37) && TheItem->ExcellentOption == 32)
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x6C],0x7 //My New Item Name Color
		}
	}

	else
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x6C],0x1 //
		}
	}

	_asm
	{
		MOV Adr2, 0x007E48FA
		JMP Adr2
	}
}

void NewPets::Load()
{

	SetOp((LPVOID)0x005803E5, (LPVOID)0x0058056F, ASM::JMP); // New Pets fix
	SetByte((LPVOID)0x005803EA, 0x90); // New Pets fix

	// Set New Pets Skins
	SetRange((LPVOID)0x008360BF, 27, ASM::NOP);
	SetOp((LPVOID)0x008360BF, SetNewPetSkins, ASM::CALL);

	SetRange((LPVOID)0x006418F5, 28, ASM::NOP);
	SetOp((LPVOID)0x006418F5, FixVisualBug, ASM::CALL);
	
	SetRange((LPVOID)0x0048FA7E, 42, ASM::NOP);
	SetOp((LPVOID)0x0048FA7E, AsmTest3, ASM::CALL);

	SetRange((LPVOID)0x005C7AB8, 26, ASM::NOP);
	SetOp((LPVOID)0x005C7AB8, AsmTest4, ASM::CALL);

	SetRange((LPVOID)0x006418F5, 27, ASM::NOP);
	SetOp((LPVOID)0x006418F5, AsmTest5, ASM::CALL);
	
	SetRange((LPVOID)0x00503868, 11, ASM::NOP);
	SetOp((LPVOID)0x00503868, AsmTest6, ASM::CALL);

	SetRange((LPVOID)0x005018E9, 16, ASM::NOP);
	SetOp((LPVOID)0x005018E9, SetNewPetMovement, ASM::CALL);

	SetRange((LPVOID)0x00501529, 20, ASM::NOP);
	SetOp((LPVOID)0x00501529, SetNewPetScale, ASM::CALL);

	SetRange((LPVOID)0x0054E8A0, 76, ASM::NOP);
	SetOp((LPVOID)0x0054E8A0, this->GetFenrirSkillColor, ASM::JMP);

	SetRange((LPVOID)0x0072FEBB, 54, ASM::NOP);
	SetOp((LPVOID)0x0072FEBB, SetNewPetSkillEffect, ASM::JMP);

	SetRange((LPVOID)0x007E3FA5, 29, ASM::NOP);
	SetOp((LPVOID)0x007E3FA5, SetNewPetItemLevelTooltipLines, ASM::JMP);
	
	SetRange((LPVOID)0x007E48F3, 7, ASM::NOP);
	SetOp((LPVOID)0x007E48F3, SetNewPetItemNameColor, ASM::JMP);
}

int NewPets::GetFenrirSkillColor(ObjectPreview * gPreview)
{
	int result = 1;

	switch ( gPreview->PetExcellent )
	{
	case 1:
		result = 0;
		break;
	case 2:
		result = 2;
		break;
	case 4:
		result = 3;
		break;
	case 8:
		result = 8;
		break;
	case 16:
		result = 13;
		break;
	case 32:
		result = 18;
		break;
	default:
		result = 1;
		break;
	}
	return result;
}