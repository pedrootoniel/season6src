#include "Stdafx.h"
#include "RFGloves.h"
#include "TMemory.h"
#include "Import.h"
#include "Defines.h"
#ifdef NOLOAD
cRFItem RFItem;

void __declspec ( naked ) cRFItem::BattleGloveLoad() {
    static DWORD BattleGloveModel   = 0x00614D10;
    static DWORD BattleGloveReturn  = 0x0050DE83;
    // ----
    static PCHAR PhoenixSoulModel   = "Sword36";
    static PCHAR PhoenixSoulLeft    = "Sword36L";
    static PCHAR PhoenixSoulRight   = "Sword36R";
    static PCHAR DragonRoarModel    = "GloveMaleBloodyDragon";
    static PCHAR DragonRoarLeft     = "GloveMaleBloodyDragonL";
    static PCHAR DragonRoarRight    = "GloveMaleBloodyDragonR";
    static PCHAR GloveTigris    = "GloveMaleTigris";
    static PCHAR GloveTigrisLeft     = "GloveMaleTigrisL";
    static PCHAR GloveTigrisRight    = "GloveMaleTigrisR";
    static PCHAR GloveCrimson    = "GloveMaleCrimson";
    static PCHAR GloveCrimsonLeft     = "GloveMaleCrimsonL";
    static PCHAR GloveCrimsonRight    = "GloveMaleCrimsonR";
    static PCHAR GloveBloodAngel    = "GloveBloodAngel";
    static PCHAR GloveBloodAngelLeft     = "GloveBloodAngelL";
    static PCHAR GloveBloodAngelRight    = "GloveBloodAngelR";
    static PCHAR GloveDarkAngel    = "GloveDarkAngel";
    static PCHAR GloveDarkAngelLeft     = "GloveDarkAngelL";
    static PCHAR GloveDarkAngelRight    = "GloveDarkAngelR";
    static PCHAR GloveHolyAngel    = "HolyAngelClaw";
    static PCHAR GloveHolyAngelLeft     = "HolyAngelClawL";
    static PCHAR GloveHolyAngelRight    = "HolyAngelClawR";
    // ----
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
        PUSH -1
        PUSH DragonRoarModel
        PUSH 0x00D28B90
        PUSH 0x4BC
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH DragonRoarLeft
        PUSH 0x00D28BA8
        PUSH 0x610
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH DragonRoarRight
        PUSH 0x00D28BC0
        PUSH 0x611
        CALL BattleGloveModel
        ADD ESP, 0x10
        // ----
        PUSH -1
        PUSH GloveTigris
        PUSH 0x00D28B90
        PUSH 0x4BD
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveTigrisLeft
        PUSH 0x00D28BA8
        PUSH 0x612
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveTigrisRight
        PUSH 0x00D28BC0
        PUSH 0x613
        CALL BattleGloveModel
        ADD ESP, 0x10
        // ----
        PUSH -1
        PUSH GloveCrimson
        PUSH 0x00D28B90
        PUSH 0x4BE
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveCrimsonLeft
        PUSH 0x00D28BA8
        PUSH 0x614
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveCrimsonRight
        PUSH 0x00D28BC0
        PUSH 0x615
        CALL BattleGloveModel
        ADD ESP, 0x10
        // ----
        PUSH -1
        PUSH GloveBloodAngel
        PUSH 0x00D28B90
        PUSH 0x4C1
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveBloodAngelLeft
        PUSH 0x00D28BA8
        PUSH 0x616
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveBloodAngelRight
        PUSH 0x00D28BC0
        PUSH 0x617
        CALL BattleGloveModel
        ADD ESP, 0x10
        // ----
        PUSH -1
        PUSH GloveDarkAngel
        PUSH 0x00D28B90
        PUSH 0x4C5
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveDarkAngelLeft
        PUSH 0x00D28BA8
        PUSH 0x618
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveDarkAngelRight
        PUSH 0x00D28BC0
        PUSH 0x619
        CALL BattleGloveModel
        ADD ESP, 0x10
        // ----
        PUSH -1
        PUSH GloveHolyAngel
        PUSH 0x00D28B90
        PUSH 0x4C8
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveHolyAngelLeft
        PUSH 0x00D28BA8
        PUSH 0x620
        CALL BattleGloveModel
        ADD ESP, 0x10
        PUSH -1
        PUSH GloveHolyAngelRight
        PUSH 0x00D28BC0
        PUSH 0x621
        CALL BattleGloveModel
        ADD ESP, 0x10
        // ----
        JMP BattleGloveReturn
    }
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
        PUSH 0x613                                        //; /Arg3 = 613 -> Right
        PUSH 0x612                                        //; |Arg2 = 612 -> Left
        PUSH 0x4BD                                        //; |Arg1 = 4BD -> ITEM2(0,42)
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
        PUSH 0x615                                        //; /Arg3 = 615 -> Right
        PUSH 0x614                                        //; |Arg2 = 614 -> Left
        PUSH 0x4BE                                        //; |Arg1 = 4BE -> ITEM2(0,43)
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
        PUSH 0x617                                        //; /Arg3 = 617 -> Right
        PUSH 0x616                                        //; |Arg2 = 616 -> Left
        PUSH 0x4C1                                        //; |Arg1 = 4C1 -> ITEM2(0,46)
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
        PUSH 0x619                                        //; /Arg3 = 619 -> Right
        PUSH 0x618                                        //; |Arg2 = 618 -> Left
        PUSH 0x4C5                                        //; |Arg1 = 4C6 -> ITEM2(0,50)
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
        PUSH 0x621                                        //; /Arg3 = 621 -> Right
        PUSH 0x620                                        //; |Arg2 = 620 -> Left
        PUSH 0x4C8                                        //; |Arg1 = 4C8 -> ITEM2(0,50)
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
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CC8
        PUSH 0x4BC
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CD0
        PUSH 0x610
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CD8
        PUSH 0x611
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        // ----
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CC8
        PUSH 0x4BD
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CD0
        PUSH 0x612
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CD8
        PUSH 0x613
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        // ----
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CC8
        PUSH 0x4BE
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CD0
        PUSH 0x614
        CALL BattleGloveTexCall
        ADD ESP, 0x14
        PUSH 1
        PUSH GL_NEAREST
        PUSH GL_REPEAT
        PUSH 0x00D28CD8
        PUSH 0x615
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
        CMP DWORD PTR SS:[EBP+0x8], 0x4B6
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
        CMP DWORD PTR SS : [EBP + 0x8], 0x4BC
        JNZ BattleGloveProp4_Label2
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
        BattleGloveProp4_Label2:
        // ----
        CMP DWORD PTR SS : [EBP + 0x8], 0x4BD
        JNZ BattleGloveProp4_Label3
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
        BattleGloveProp4_Label3:
        // ----
        CMP DWORD PTR SS : [EBP + 0x8], 0x4BE
        JNZ BattleGloveProp4_Label4
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
		BattleGloveProp4_Label4:
        // ----
        CMP DWORD PTR SS : [EBP + 0x8], 0x4C1
        JNZ BattleGloveProp4_Label5
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
		BattleGloveProp4_Label5:
        // ----
        CMP DWORD PTR SS : [EBP + 0x8], 0x4C5
        JNZ BattleGloveProp4_Label6
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
		BattleGloveProp4_Label6:
        // ----
        CMP DWORD PTR SS : [EBP + 0x8], 0x4C8
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

void __declspec ( naked ) cRFItem::BattleGloveProp5() {
    static DWORD BattleGloveProp5_Return    = 0x005CEFFB;
    static DWORD BattleGloveProp5_Jump      = 0x005CF01C;
    // ----
    _asm {
        CMP DWORD PTR SS:[EBP+0x8], ITEM2 ( 0, 35 )
        JNZ NextBattleGlove1
        FLD DWORD PTR DS: [0x0D2C618]                       //FLOAT 0.003000000
        FSTP DWORD PTR SS: [EBP - 0x2C]
        JMP BattleGloveProp5_Jump
        // ----
        NextBattleGlove1:
        // ----
        CMP DWORD PTR SS: [EBP + 0x8], ITEM2 ( 0, 41 )
        JNZ NextBattleGlove2
        FLD DWORD PTR DS: [0x0D2C630]                       //FLOAT 0.003800000
        FSTP DWORD PTR SS: [EBP - 0x2C]
        JMP BattleGloveProp5_Jump
		// ----
        NextBattleGlove2:
        // ----
        CMP DWORD PTR SS: [EBP + 0x8], ITEM2 ( 0, 42 )
        JNZ NextBattleGlove3
        FLD DWORD PTR DS: [0x0D2C630]                       //FLOAT 0.003800000
        FSTP DWORD PTR SS: [EBP - 0x2C]
        JMP BattleGloveProp5_Jump
		// ----
        NextBattleGlove3:
        // ----
        CMP DWORD PTR SS: [EBP + 0x8], ITEM2 ( 0, 43 )
        JNZ NextBattleGlove4
        FLD DWORD PTR DS: [0x0D2C630]                       //FLOAT 0.003800000
        FSTP DWORD PTR SS: [EBP - 0x2C]
        JMP BattleGloveProp5_Jump
		// ----
		NextBattleGlove4:
        // ----
        CMP DWORD PTR SS: [EBP + 0x8], ITEM2 ( 0, 46 )
        JNZ ReturnBattleGlove_Load
        FLD DWORD PTR DS: [0x0D2C630]                       //FLOAT 0.003800000
        FSTP DWORD PTR SS: [EBP - 0x2C]
        JMP BattleGloveProp5_Jump
		// ----
		NextBattleGlove5:
        // ----
        CMP DWORD PTR SS: [EBP + 0x8], ITEM2 ( 0, 50 )
        JNZ NextBattleGlove6
        FLD DWORD PTR DS: [0x0D2C630]                       //FLOAT 0.003800000
        FSTP DWORD PTR SS: [EBP - 0x2C]
        JMP BattleGloveProp5_Jump
		// ----
		NextBattleGlove6:
        // ----
        CMP DWORD PTR SS: [EBP + 0x8], ITEM2 ( 0, 53 )
        JNZ ReturnBattleGlove_Load
        FLD DWORD PTR DS: [0x0D2C630]                       //FLOAT 0.003800000
        FSTP DWORD PTR SS: [EBP - 0x2C]
        JMP BattleGloveProp5_Jump
		//
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
    if ( dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 35 ) ) {
        bBattleGlovesGlow_Switcher = TRUE;
    }
    else if ( dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 41 ) ) {
        bBattleGlovesGlow_Switcher = FALSE;

        // ----
        _asm {
            MOV DWORD PTR SS:[EBP-0x4], 0x2C
            JMP dwBattleGlovesGlow_Jump
        }
    }
    else if ( dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 42 ) ) {
        bBattleGlovesGlow_Switcher = FALSE;

        // ----
        _asm {
            MOV DWORD PTR SS:[EBP-0x4], 0x2C
            JMP dwBattleGlovesGlow_Jump
        }
    }
    else if ( dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 43 ) ) {
        bBattleGlovesGlow_Switcher = FALSE;

        // ----
        _asm {
            MOV DWORD PTR SS:[EBP-0x4], 0x2C
            JMP dwBattleGlovesGlow_Jump
        }
    }
    else if ( dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 46 ) ) {
        bBattleGlovesGlow_Switcher = FALSE;

        // ----
        _asm {
            MOV DWORD PTR SS:[EBP-0x4], 0x2C
            JMP dwBattleGlovesGlow_Jump
        }
    }
    else if ( dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 50 ) ) {
        bBattleGlovesGlow_Switcher = FALSE;

        // ----
        _asm {
            MOV DWORD PTR SS:[EBP-0x4], 0x2C
            JMP dwBattleGlovesGlow_Jump
        }
    }
    else if ( dwBattleGlovesGlow_Pointer == ITEM2 ( 0, 53 ) ) {
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

void __declspec ( naked ) cRFItem::cRFAddInventoryPos() {
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
    else if ( IsRFItem == ITEM2 ( 0, 41 ) ) {
        _asm {jmp RFPosition}
    }
    else if ( IsRFItem == ITEM2 ( 0, 42 ) ) {
        _asm {jmp RFPosition}
    }
    else if ( IsRFItem == ITEM2 ( 0, 43 ) ) {
        _asm {jmp RFPosition}
    }
    else if ( IsRFItem == ITEM2 ( 0, 46 ) ) {
        _asm {jmp RFPosition}
    }
    else if ( IsRFItem == ITEM2 ( 0, 50 ) ) {
        _asm {jmp RFPosition}
    }
    else if ( IsRFItem == ITEM2 ( 0, 53 ) ) {
        _asm {jmp RFPosition}
    }
    else {
        _asm {jmp NextRFPosition}
    }
}

void cRFItem::Load() {
    SetRange ( ( LPVOID ) 0x0050DE38, 75, ASM::NOP );
    SetJmp ( ( LPVOID ) 0x0050DE38, this->BattleGloveLoad );
    // ----
    SetRange ( ( LPVOID ) 0x0050DC31, 127, ASM::NOP );
    SetJmp ( ( LPVOID ) 0x0050DC31, this->BattleGloveAssoc );
    // ----
   // SetRange ( ( LPVOID ) 0x0050E043, 90, ASM::NOP );
   // SetJmp ( ( LPVOID ) 0x0050E043, this->BattleGloveTexture );
    // ----
    SetRange ( ( LPVOID ) 0x005CD419, 59, ASM::NOP );
    SetJmp ( ( LPVOID ) 0x005CD419, this->BattleGloveProp4 ); // -> Inventory Position
    // ----
    SetRange ( ( LPVOID ) 0x005CEFE7, 20, ASM::NOP );
    SetJmp ( ( LPVOID ) 0x005CEFE7, this->BattleGloveProp5 ); // -> Inventory Rotation
    // ----
    SetRange ( ( LPVOID ) 0x005F91C2, 7, ASM::NOP );
    SetJmp ( ( LPVOID ) 0x005F91C2, this->BattleGloveGlow );

    SetRange ( ( LPVOID ) 0x005CD07D, 7, ASM::NOP );
    SetJmp ( ( LPVOID ) 0x005CD07D, this->cRFAddInventoryPos );
}
#endif