#include "Stdafx.h"
#include "BattleGloves.h"
//#include "TMemory.h"
//#include "ItemAsm.h"
//#include "Import.h"
#include "Util.h"
#include "Defines.h"
#include "Item.h"
#include "CustomWeapons.h"
#include "CustomGloves.h"
#include "TMemory.h"

cRFItem gRFItem;

void __declspec ( naked ) cRFItem::BattleGloveLoad() {
    static DWORD BattleGloveModel   = 0x00614D10;
    static DWORD BattleGloveReturn  = 0x0050DE83;
    // ----
    static PCHAR DragonRoarModel    = "Sword45";
    static PCHAR DragonRoarLeft     = "Sword45L";
    static PCHAR DragonRoarRight    = "Sword45R";
    // ----
	LoadItemModel(GET_ITEM_MODEL ( 0, 41 ),"Custom\\Item\\RFGloves\\","Sword41",-1);
	LoadItemModel(0x610,"Custom\\Item\\RFGloves\\","Sword41L",-1);
	LoadItemModel(0x611,"Custom\\Item\\RFGloves\\","Sword41R",-1);
    _asm {
        PUSH -1
        PUSH 0x00D28B88
        PUSH 0x00D28B90
        PUSH 0x4B6
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH 0x00D28B9C
        PUSH 0x00D28BA8
        PUSH 0x268
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH 0x00D28BB4
        PUSH 0x00D28BC0
        PUSH 0x269
        CALL BattleGloveModel
        ADD ESP, 0x10
        // ----
        JMP BattleGloveReturn
    }

	
	
}

#define sub_50D810_Addr		((int(__thiscall*)(int a1, int a2, int a3, int a4)) 0x50D810)
#define sub_512D50_Addr		((void*(__thiscall*)(void* a1)) 0x512D50)
#define sub_513C60_Addr		((char*(__thiscall*)(char *This, void *a2, int a3)) 0x513C60)
#define sub_5135F0_Addr		((char*(__thiscall*)(DWORD *This, int a2, int a3)) 0x5135F0)
#define sub_512D60_Addr		((void(*)()) 0x512D60)


void GlovesAssoc(char *This)
{
	sub_50D810_Addr((int)(This + 92), 1203, 610, 611);
	void* v2 = sub_512D50_Addr(This + 92);
	char* v3 = sub_513C60_Addr(This, v2, (int)(This + 92));
	sub_5135F0_Addr((DWORD *)This + 15, (int)This, (int)v3);
	sub_512D60_Addr();
	// ----
	sub_50D810_Addr((int)(This + 92), 1204, 612, 613);
	v2 = sub_512D50_Addr(This + 92);
	v3 = sub_513C60_Addr(This, v2, (int)(This + 92));
	sub_5135F0_Addr((DWORD *)This + 15, (int)This, (int)v3);
	sub_512D60_Addr();
	// ----
	sub_50D810_Addr((int)(This + 92), 1205, 614, 615);
	v2 = sub_512D50_Addr(This + 92);
	v3 = sub_513C60_Addr(This, v2, (int)(This + 92));
	sub_5135F0_Addr((DWORD *)This + 15, (int)This, (int)v3);
	sub_512D60_Addr();
	// ----
	sub_50D810_Addr((int)(This + 92), 1206, 616, 617);
	v2 = sub_512D50_Addr(This + 92);
	v3 = sub_513C60_Addr(This, v2, (int)(This + 92));
	sub_5135F0_Addr((DWORD *)This + 15, (int)This, (int)v3);
	sub_512D60_Addr();
	// ----
	sub_50D810_Addr((int)(This + 92), 1211, 610, 611);
	v2 = sub_512D50_Addr(This + 92);
	v3 = sub_513C60_Addr(This, v2, (int)(This + 92));
	sub_5135F0_Addr((DWORD *)This + 15, (int)This, (int)v3);
	sub_512D60_Addr();
	// ----
	gCustomGloves.AssocGloves(This);
}

void __declspec ( naked ) cRFItem::BattleGloveAssoc() {
    static DWORD BattleGloveCall1   = 0x0050D810;
    static DWORD BattleGloveCall2   = 0x00512D50;
    static DWORD BattleGloveCall3   = 0x00513C60;
    static DWORD BattleGloveCall4   = 0x005135F0;
    static DWORD BattleGloveCall5   = 0x00512D60;
    // ----
    static DWORD BattleGloveJump    = 0x0050DCB0;
    // ----
    _asm {
        PUSH 0x269                                        //; /Arg3 = 269
        PUSH 0x268                                        //; |Arg2 = 268
        PUSH 0x4B6                                        //; |Arg1 = 4B6
        MOV ECX, DWORD PTR SS:[EBP-0x9C]                  //; |
        ADD ECX, 0x5C                                     //; |
        CALL BattleGloveCall1                             //; \Main.0050D810
        MOV EAX, DWORD PTR SS:[EBP-0x9C]
        ADD EAX, 0x5C
        PUSH EAX                                          //; /Arg2 => ARG.ECX+5C
        MOV ECX, DWORD PTR SS:[EBP-0x9C]                  //; |
        ADD ECX, 0x5C                                     //; |
        CALL BattleGloveCall2                             //; |
        PUSH EAX                                          //; |Arg1
        LEA ECX, [EBP-0x70]                               //; |
        CALL BattleGloveCall3                             //; \Main.00513C60
        MOV DWORD PTR SS:[EBP-0xB8], EAX
        MOV ECX, DWORD PTR SS:[EBP-0xB8]
        MOV DWORD PTR SS:[EBP-0xBC], ECX
        MOV DWORD PTR SS:[EBP-0x4], 3   // -> Battle Glove Number
        MOV EDX, DWORD PTR SS:[EBP-0xBC]
        PUSH EDX                                          //; /Arg2 => [LOCAL.46]
        LEA EAX, [EBP-0x7C]                               //; |
        PUSH EAX                                          //; |Arg1 => OFFSET LOCAL.31
        MOV ECX, DWORD PTR SS:[EBP-0x9C]                  //; |
        ADD ECX, 0x3C                                     //; |
        CALL BattleGloveCall4                             //; \Main.005135F0
        MOV DWORD PTR SS:[EBP-0x4], -1
        LEA ECX, [EBP-0x70]
        CALL BattleGloveCall5                             //; [Main.00512D60
        // ----
        PUSH 0x611                                        //; /Arg3 = 611 -> Right
        PUSH 0x610                                        //; |Arg2 = 610 -> Left
        PUSH 0x4BC                                        //; |Arg1 = 4BF -> ITEM2(0,41)
        MOV ECX, DWORD PTR SS:[EBP-0x9C]                  //; |
        ADD ECX, 0x5C                                     //; |
        CALL BattleGloveCall1                             //; \Main.0050D810
        MOV EAX, DWORD PTR SS:[EBP-0x9C]
        ADD EAX, 0x5C
        PUSH EAX
        MOV ECX, DWORD PTR SS:[EBP-0x9C]
        ADD ECX, 0x5C
        CALL BattleGloveCall2
        PUSH EAX
        LEA ECX, [EBP-0x70]
        CALL BattleGloveCall3
        MOV DWORD PTR SS:[EBP-0xB8], EAX
        MOV ECX, DWORD PTR SS:[EBP-0xB8]
        MOV DWORD PTR SS:[EBP-0xBC], ECX
        MOV DWORD PTR SS:[EBP-0x4], 5   // -> Battle Glove Number
        MOV EDX, DWORD PTR SS:[EBP-0xBC]
        PUSH EDX
        LEA EAX, [EBP-0x7C]
        PUSH EAX
        MOV ECX, DWORD PTR SS:[EBP-0x9C]
        ADD ECX, 0x3C
        CALL BattleGloveCall4
        MOV DWORD PTR SS:[EBP-0x4], -1
        LEA ECX, [EBP-0x70]
        CALL BattleGloveCall5
        // ----
        JMP BattleGloveJump
    }
}

void __declspec ( naked ) cRFItem::BattleGloveTexture() {
    static DWORD BattleGloveTexCall = 0x00614710;
    static DWORD BattleGloveTexJump = 0x0050E09D;
    // ----
	LoadItemTexture(GET_ITEM_MODEL ( 0, 41 ),"Custom\\Item\\RFGloves\\","Sword41",-1);
	LoadItemTexture(0x610,"Custom\\Item\\RFGloves\\","Sword41L",-1);
	LoadItemTexture(0x611,"Custom\\Item\\RFGloves\\","Sword41R",-1);
    _asm {
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CC8
        PUSH 0x4B6
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CD0
        PUSH 0x268
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CD8
        PUSH 0x269
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        // ----
        JMP BattleGloveTexJump
    }
}

void __declspec ( naked ) cRFItem::BattleGloveProp4() {
    static DWORD BattleGloveProp4_Return    = 0x005CD454;
    static DWORD BattleGloveProp4_Jump      = 0x005CD491;
    // ----
    _asm {
        CMP DWORD PTR SS:[EBP+0x8], GET_ITEM_MODEL ( 0, 41 )
        JNZ BattleGloveProp4_Label1
        FLD DWORD PTR SS:[EBP-0x4C]
        FSUB QWORD PTR DS:[0x0D27CA8]                     //FLOAT 0.004999999888241291
        FSTP DWORD PTR SS:[EBP-0x4C]
        FLD DWORD PTR SS:[EBP-0x48]
        FADD QWORD PTR DS:[0x0D254B8]                     //FLOAT 0.01499999966472387
        FSTP DWORD PTR SS:[EBP-0x48]
        FLDZ
        FSTP DWORD PTR DS:[0x82C6320]                     //FLOAT 0.0
        FLDZ
        FSTP DWORD PTR DS:[0x82C6324]                     //FLOAT 0.0
        FLDZ
        FSTP DWORD PTR DS:[0x82C6328]                     //FLOAT 0.0
        JMP BattleGloveProp4_Jump
        // ----
        BattleGloveProp4_Label1:
        // ----
        CMP DWORD PTR SS : [EBP + 0x8], GET_ITEM_MODEL ( 0, 41 )
        JNZ BattleGloveProp4_LabelReturn
        FLD DWORD PTR SS: [EBP - 0x4C]
        FSUB QWORD PTR DS: [0x0D27CA8]                    //FLOAT 0.004999999888241291
        FSTP DWORD PTR SS: [EBP - 0x4C]
        FLD DWORD PTR SS: [EBP - 0x48]
        FADD QWORD PTR DS: [0x0D254B8]                    //FLOAT 0.01499999966472387
        FSTP DWORD PTR SS: [EBP - 0x48]
        FLDZ
        FSTP DWORD PTR DS: [0x82C6320]                    //FLOAT 0.0
        FLDZ
        FSTP DWORD PTR DS: [0x82C6324]                    //FLOAT 0.0
        FLDZ
        FSTP DWORD PTR DS: [0x82C6328]                    //FLOAT 0.0
        JMP BattleGloveProp4_Jump
        // ----
        BattleGloveProp4_LabelReturn:
        // ----
        JMP BattleGloveProp4_Return
    }
}

DWORD IsGlovesItem = 0;
DWORD GlovesPosition = 0x005CD422; // 1.04D ENG
DWORD NextGlovesPosition = 0x005CD454; // 1.04D ENG

void __declspec(naked) cGlovesAddInventoryPos()
{
	_asm
	{

		mov ecx, dword ptr ss : [ebp + 0x8]
			mov dword ptr ss : [ebp + 0x8], ecx
			mov IsGlovesItem, ecx
	}
	// ---
	//console.Log("","FUCK [%x]",IsGlovesItem);
	if (IsGlovesItem == 0x04B6)
	{
		_asm{jmp GlovesPosition}
	}
	else if (IsGlovesItem >= GET_ITEM_MODEL(0, 41) && IsGlovesItem <= GET_ITEM_MODEL(0, 50))
	{
		_asm{jmp GlovesPosition}
	}
	else
	{
		_asm{jmp NextGlovesPosition}
	}
}

void __declspec ( naked ) cRFItem::BattleGloveProp5() { // Масштаб
    static DWORD BattleGloveProp5_Return    = 0x005CEFFB;
    static DWORD BattleGloveProp5_Jump      = 0x005CF01C;
    // ----
	static float a1 = 0.00480000;
	//a1 = GetPrivateProfileFloat("Custom", "a1", 0, "./Settings.ini");
    _asm {
        CMP DWORD PTR SS:[EBP+0x8], GET_ITEM_MODEL ( 0, 35 )
        JNZ NextBattleGlove1
        FLD DWORD PTR DS: [0x0D2C618]                       //FLOAT 0.003000000
        FSTP DWORD PTR SS: [EBP - 0x2C]
        JMP BattleGloveProp5_Jump
        // ----
        NextBattleGlove1:
        // ----
        CMP DWORD PTR SS: [EBP + 0x8], GET_ITEM_MODEL ( 0, 41 )
        JNZ ReturnBattleGlove_Load
        FLD DWORD PTR DS:[a1]                       //FLOAT 0.003800000
        FSTP DWORD PTR SS: [EBP - 0x2C]
        JMP BattleGloveProp5_Jump
        // ----
        ReturnBattleGlove_Load:
        // ----
        JMP BattleGloveProp5_Return
    }
}

static BOOL bBattleGlovesGlow_Switcher;

void __declspec ( naked ) cRFItem::BattleGloveGlow() {
    static DWORD dwBattleGlovesGlow_Pointer;
    static DWORD dwBattleGlovesGlow_Buffer;
    static DWORD dwBattleGlovesNewGlow_Buffer;
    static DWORD dwBattleGlovesGlow_Jump = 0x005F94E8;
    // ----
    bBattleGlovesGlow_Switcher = FALSE;
    // ----
    _asm {
        MOV dwBattleGlovesGlow_Pointer, EAX
    }

    // ----
    if ( dwBattleGlovesGlow_Pointer == GET_ITEM_MODEL ( 0, 35 ) ) {
        bBattleGlovesGlow_Switcher = TRUE;
    }
    else if ( gCustomGloves.CheckGloves(dwBattleGlovesGlow_Pointer-ITEM_BASE_MODEL)/*dwBattleGlovesGlow_Pointer == GET_ITEM_MODEL ( 0, 41 )*/ ) {
        bBattleGlovesGlow_Switcher = FALSE;
        // ----
        _asm {
            MOV DWORD PTR SS:[EBP-0x4], 0x2C
            JMP dwBattleGlovesGlow_Jump
        }
    }

    // ----
    if ( bBattleGlovesGlow_Switcher == TRUE ) {
        _asm {
            MOV dwBattleGlovesGlow_Buffer, 0x005F91C9
            JMP dwBattleGlovesGlow_Buffer
        }
    }
    else {
        _asm {
            MOV dwBattleGlovesGlow_Buffer, 0x005F91D5
            JMP dwBattleGlovesGlow_Buffer
        }
    }
}

__declspec(naked) void cRFItem::AddInventoryPos() // OK
{
	static DWORD IsRFItem = 0;
    static DWORD RFPosition = 0x005CD084; // 1.04D ENG
    static DWORD NextRFPosition = 0x005CD086; // 1.04D ENG
    //
    _asm {
        mov ecx, dword ptr ss : [ebp + 0x8]
        mov dword ptr ss : [ebp + 0x8], ecx
        mov IsRFItem, ecx
    }

    // ---
    if ( IsRFItem == 0x04B3 ) {
        _asm {jmp RFPosition}
    }
    else if ( IsRFItem == GET_ITEM_MODEL ( 0, 41 ) ) {
        _asm {jmp RFPosition}
    }
    else {
        _asm {jmp NextRFPosition}
    }
}

void cRFItem::Load() {

    //SetRange (oBattleGlove_Load, 75, ASM::NOP );
	//SetOp(oBattleGlove_Load, &this->BattleGloveLoad, ASM::JMP);
    // ----


   // SetRange (oBattleGlove_Hook, 127, ASM::NOP );
	//SetOp(oBattleGlove_Hook, &this->BattleGloveAssoc, ASM::JMP);
	SetCompleteHook(0xE8,0x50D840+0xC5,&GlovesAssoc);

 //   // ----
   // SetRange (oBattleGlove_Texture, 90, ASM::NOP );
	//SetOp(oBattleGlove_Texture, &this->BattleGloveTexture, ASM::JMP);
 //   // ----
    //SetRange (oBattleGloveProp4_Hook, 59, ASM::NOP );
	//SetOp(oBattleGloveProp4_Hook, &this->BattleGloveProp4, ASM::JMP);// -> Inventory Position
	//SetRange(oBattleGloveProp4_Hook, 6, ASM::NOP);
	//SetJmp((LPVOID)iBowAddInventoryPos, cBowAddInventoryPos);
	//SetOp(oBattleGloveProp4_Hook, &cGlovesAddInventoryPos, ASM::JMP);
 //   // ----
   // SetRange (oBattleGloveProp5_Hook, 20, ASM::NOP );
	//SetOp(oBattleGloveProp5_Hook, &this->BattleGloveProp5, ASM::JMP); // -> Inventory Rotation
 //   // ----
    SetRange(oBattleGloveGlow_Hook, 7, ASM::NOP );
	SetOp3(oBattleGloveGlow_Hook, &this->BattleGloveGlow, ASM::JMP);

	/*SetDword(0x005765B4+1,0x4BC);
	SetDword(0x00576B69+2,0x4BC);
	SetDword(0x00578A46+1,0x4BC);
	SetDword(0x005CD419+3,0x4BC);
	SetDword(0x005CEFE7+3,0x4BC);
	SetDword(0x005F91C2+1,0x4BC);
	SetDword(0x00607503+1,0x4BC);
	SetDword(0x00608D4C+3,0x4BC);
	SetDword(0x006095ED+3,0x4BC);
	SetDword(0x006105D6+1,0x4BC);*/

	//SetRange (0x005CD07D, 7, ASM::NOP );
	//SetOp(0x005CD07D, &this->AddInventoryPos, ASM::JMP);
    //SetRange ( ( LPVOID ) 0x005CD07D, 7, ASM::NOP );
    //SetJmp ( ( LPVOID ) 0x005CD07D, &this->AddInventoryPos );
}