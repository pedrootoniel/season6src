#include "stdafx.h"
#include "TMemory.h"
#include "Import.h"
#include "Defines.h"
#include "zCustomJewel.h"

// ----------------------------------------------------------------------------------------------

Jewel    gJewel;
// ----------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------

bool Jewel::IsCustomWings ( WORD ItemID, bool Preview ) {
    // ----
    if ( Preview ) {
        ItemID -= ITEM_INTER;
    }

    // ----
    if ( ItemID >= ITEM ( 13, 150 ) && ItemID <= ITEM ( 13, 410 ) ) {
        return true;
    }

    // ----
    return false;
}
// ----------------------------------------------------------------------------------------------

bool Jewel::IsCustomJewels ( WORD ItemID, bool Preview ) {
    if ( Preview ) {
        ItemID -= ITEM_INTER;
    }

    // ----
    if ( ItemID == ITEM ( 14, 13 )) {
        return true;
    }

    // ----
    return false;
}
// ----------------------------------------------------------------------------------------------

bool Jewel::GetUpgradeFlag ( LPVOID This, LPVOID EDX, ObjectItem * lpSource, ObjectItem * lpTarget ) {
    BYTE TargetLevel = ( lpTarget->Level >> 3 ) & 0xF;

    // ----
    if ( gJewel.IsCustomJewels ( lpSource->ItemID, false ) ) {
        return true;
    }

    // ----
    if ( gJewel.IsCustomWings ( lpTarget->ItemID, false ) ) {
        if ( lpSource->ItemID == ITEM ( 14, 13 ) ) {
            if ( TargetLevel >= 0 && TargetLevel <= 5 ) {
                return true;
            }
        }
        else if ( lpSource->ItemID == ITEM ( 14, 14 ) ) {
            if ( TargetLevel >= 0 && TargetLevel <= 8 ) {
                return true;
            }
        }
    }

    // ----
    return pIsUpgradeItem ( This, lpSource, lpTarget );
}
// ----------------------------------------------------------------------------------------------
Naked ( AllowJewelsInsert ) {
    static DWORD AllowJewelsInsert_Buff;
    static DWORD AllowJewelsInsert_Buff2;
    static DWORD AllowJewelsInsert_Buff3;
    _asm {
        mov AllowJewelsInsert_Buff, edx
    }

    // ----
    if ( AllowJewelsInsert_Buff == ITEM ( 14, 14 )
            || gJewel.IsCustomJewels ( AllowJewelsInsert_Buff, false ) ) {
        _asm {
            mov AllowJewelsInsert_Buff, 0x00838411
            jmp AllowJewelsInsert_Buff
        }
    }

    // ----
    _asm {
        mov AllowJewelsInsert_Buff, 0x008383BB
        jmp AllowJewelsInsert_Buff
    }
}

void Jewel::Load() {
    // ----
    SetOp ( ( LPVOID ) 0x7DBEBB, this->GetUpgradeFlag, ASM::CALL );
    // ----
    SetRange ( ( LPVOID ) 0x008383B3, 8, ASM::NOP );
    SetOp ( ( LPVOID ) 0x008383B3, AllowJewelsInsert, ASM::JMP );
}