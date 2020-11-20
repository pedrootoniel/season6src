#pragma once

#define pDrawInterfaceTest		((int(__cdecl*)(DWORD ObjectID, float PosX, float PosY)) 0x790C20)
#define pDrawViewPortEffects	((int(__cdecl*)(DWORD ObjectPointer, DWORD ModelPointer, int a3)) 0x56F210)
#define sub_51EEF0				((int(__stdcall*)(float a1, float a2, float a3, float a4, int a5)) 0x51EEF0)
#define BindEffectTest			((void(__thiscall*)(DWORD, DWORD, DWORD, float, float, float, DWORD, DWORD, float, float, DWORD, DWORD, DWORD))0x60FC70)
#define pPreviewCharacter		((int(__cdecl*)(DWORD ObjectPointer, int a2, char a3, char a4, float a5)) 0x57DD40)
#define __CFADD__(X,Y)			(((unsigned int)(X)+(unsigned int)(Y)) >> 8 ? 1 : 0)
#define pDrawViewportGlow		((void(__cdecl*)(int a1, int a2, int ModelID, float a4, int a5)) 0x5FA710)
#define pRefreshCape1			((void(__stdcall*)(ObjectItem * lpItem)) 0x8363D0)
#define pRefreshViewportEffect	((void(__cdecl*)(DWORD a1, DWORD a2, int a3)) 0x558630)
#define pRefreshCapeMain		((void(__stdcall*)(int ObjItemPointer)) 0x835E40)
#define pPreviewPetThis            *(DWORD*)0x007BC4F04
#define LODWORD(h)                ((DWORD)(__int64(h) & __int64(0xffffffff)))
#define pGraphicsEnter			((int(__thiscall*)(LPVOID This, int a2)) 0x777CB0)
#define pCheckSocket			((int(__stdcall*)(int a1)) 0x968180)
#define pTextEffectUnKnow		((int(__cdecl*)(float))0x4DB0C0)
#define pIsDivineWeapon			((BOOL(__stdcall*)(DWORD a1)) 0x7E7820)
#define pDropColor				((int(__cdecl*)(int a1))0x5F3F10)
#define	pCreateBowSkillEffect		((int(__cdecl*)(DWORD a1, DWORD a2, DWORD a3, __int16 a4, __int16 a5, unsigned __int16 a6))0x749C90)
#define pObjOnViewport				((int(__cdecl*)(int Object))0x5F61C0)
//Pet
#define pMaybeDrawPetHP				((char(__stdcall*)(int a1, int a2)) 0x7DFDB0)
#define sub_50D100					((size_t(__cdecl*)(char * a1, char * a2, ...)) 0x50D100)
#define	sub_7DFA60					((int(__stdcall*)(signed int PosX, signed int PosY, int a3, signed int a4, signed int a5, char a6)) 0x7DFA60)
#define sub_501790					((char(__cdecl*)(int a1, char a2)) 0x501790)
#define sub_540C30					((int(__cdecl*)(float, float, float, float)) 0x540C30)
#define sub_540EA0					((int(__cdecl*)(float, float a2, float)) 0x540EA0)
#define sub_959CE0					((int(__cdecl*)(DWORD, DWORD)) 0x959CE0)
#define sub_95A1E0					((int(__cdecl*)(DWORD a1, DWORD a2, float *a3)) 0x95A1E0)
#define sub_541460					((void(__cdecl*)(int a1)) 0x541460)
#define sub_4CDA10					((LPVOID(*)())0x4CDA10)
#define sub_969C50					((int(__thiscall*)(LPVOID This, signed int a2)) 0x969C50)
#define sub_5D6700					((int(__cdecl*)(unsigned __int8 a1, unsigned __int8 a2)) 0x5D6700)
#define sub_5422E0					((bool(__cdecl*)(__int16 a1)) 0x5422E0)
#define sub_542310					((__int16(__cdecl*)(int a1, int a2, char a3)) 0x542310)
#define sub_545030					((int(__thiscall*)(LPVOID This, int a2, DWORD *a3, DWORD *BMD, char a5)) 0x545030)
#define sub_6D9070					((void(__cdecl*)(int a1, int a2, int a3, float * a4, int a5, int a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, float a11, __int16 a12)) 0x6D9070)
#define sub_74CD30					((int(__cdecl*)(int a1, int a2, int a3, vec3_t a4, int a5, float a6, int a7)) 0x74CD30)
#define sub_74CD30_					((int(__cdecl*)(DWORD a1, vec3_t a2, int a3, vec3_t a4, int a5, float a6, int a7)) 0x74CD30)
#define sub_4DB1C0					((bool(__cdecl*)(signed int a1))0x4DB1C0)
#define sub_4C8640					((bool(__thiscall*)(void * This,char a2)) 0x4C8640)
#define sub_4DB250					((int(__cdecl*)()) 0x4DB250)
#define sub_4E44A0					((bool(__thiscall*)(int This)) 0x4E44A0)
#define sub_7293F0					((char*(__cdecl*)(int a1, int a2, int a3, int a4, int a5, char a6, int a7)) 0x7293F0)
#define sub_5039A0					((void(__cdecl*)(int a1, int a2)) 0x5039A0)
#define sub_72D1B0					((void(__cdecl*)(int a1, int a2, int a3, int a4, int a5, int a6, float a7, __int16 a8, __int16 a9, char a10, int a11, int a12, __int16 a13)) 0x72D1B0)
#define sub_542280					((bool(__cdecl*)(__int16 a1)) 0x542280)
#define sub_545180					((char(__thiscall*)(void * This, int a2, int a3, int a4, float a5, int a6, int a7)) 0x545180)
#define sub_5CA0D0					((void(__cdecl*)( int a1,  int a2, int a3, int a4, int a5, int a6, char a7)) 0x5CA0D0)
#define sub_9250E0					((int(__thiscall*)(LPVOID This, int a1, int a2, int a3, int a4, int a5, int a6)) 0x9250E0)
#define sub_4DB230					((LPVOID(*)())0x4DB230)
#define sub_501700					((DWORD(__cdecl*)(DWORD, DWORD, DWORD, DWORD, DWORD)) 0x501700)
#define sub_57D9A0					((DWORD(__cdecl*)(DWORD)) 0x57D9A0)
#define sub_58AA80					((DWORD(__cdecl*)(DWORD)) 0x58AA80)
#define sub_4E6670					((DWORD(__cdecl*)(DWORD)) 0x4E6670)
#define sub_57F020					((DWORD(__cdecl*)(DWORD)) 0x57F020)

#define sub_4F8C30					((DWORD(__cdecl*)(DWORD)) 0x4F8C30)
#define sub_534B40					((DWORD(__cdecl*)(DWORD)) 0x534B40)
#define sub_5012D0					((DWORD(__cdecl*)(DWORD)) 0x5012D0)
#define sub_9253D0					((int(__thiscall*)(LPVOID This,int a1, short a2)) 0x9253D0)
#define sub_4F94A0					((DWORD(__cdecl*)(DWORD)) 0x4F94A0)
#define sub_57FC30					((int(__cdecl*)(BYTE CharSet)) 0x57FC30)
#define sub_587500					((DWORD(__cdecl*)(char)) 0x587500)
#define sub_402BC0					((LPVOID(*)())0x402BC0)

#define sub_405230					((int(__cdecl*)(char a1)) 0x405230)
#define sub_4F9930					((int(__cdecl*)(char *a1)) 0x4F9930)
#define sub_4F8B80					((int(__cdecl*)(int a1)) 0x4F8B80)
#define sub_4E65A0					((bool(__cdecl*)(signed int a1)) 0x4E65A0)
#define sub_4FA780					((int(__thiscall*)(int This, int a2)) 0x4FA780)
#define sub_5013B0					((char(__cdecl*)(int a1, int a2, int a3, int a4, int a5)) 0x5013B0)
#define sub_4EFF70					((void(__cdecl*)(LPVOID This,int a1)) 0x4EFF70)
#define sub_96A4C0					((int(__thiscall*)(LPVOID This, signed int a2)) 0x96A4C0)
#define sub_57FD90					((void(__cdecl*)(int a1, BYTE * a2, int a3, int a4)) 0x57FD90)
#define sub_558630					((void(__cdecl*)(int a1, int a2, int a3)) 0x558630)
#define SLODWORD(x)					(*((DWORD*)&(x)))
#define sub_771310					((int(__cdecl*)(int a1, int a2, float a3, vec3_t a4, int a5, float a6, int a7)) 0x771310)
#define sub_771310_					((int(__cdecl*)(int a1, vec3_t a2, float a3, vec3_t a4, int a5, float a6, int a7)) 0x771310)
#define sub_95A340					((int(__cdecl*)(int a1, int a2, int a3)) 0x95A340)
#define sub_5440B0					((int(__fastcall*)(int a1, int a2, int a3, float a4, float a5, __int16 a6, int a7, int a8, char a9, char a10)) 0x5440B0)
#define sub_922D50					((signed int(__thiscall*)(int This, unsigned int a2)) 0x922D50);
#define sub_580BB0					((int(__cdecl*)(DWORD, DWORD)) 0x580BB0)
#define sub_4CD7F0					((int(__stdcall*)(DWORD,DWORD)) 0x4CD7F0)
#define pDrawMonsterEffect			((char(__cdecl*)(int a1, int a2, int a3)) 0x8C7790)
#define sub_5D81B0					((int(__cdecl*)(float, float)) 0x5D81B0)
#define sub_544E60					((void(__thiscall*)(LPVOID This, vec3_t a2, int a3, signed int a4, int a5)) 0x544E60)
#define sub_9593B0					((int(__stdcall*)(HDC This, LPCSTR lpMultiByteStr, int, LPSIZE psizl)) 0x9593B0)
#define pSetTextSize				((int(__thiscall*)(LPVOID This, HFONT a2)) 0x420120)
#define pFontBold					*(DWORD*)0xE8C58C
#define sub_8CBA40					((int(__cdecl*)(int, int, float, float, float, float, GLfloat *v)) 0x8CBA40) //Effect? 32141
#define sub_5DAD80					((int(__cdecl*)(int, float, float, float, float, GLfloat *v, float, float, float, char)) 0x5DAD80) //effect ?32313
#define sub_56EFC0					((int(__cdecl*)(int, int, float, int, float, float, float)) 0x56EFC0)
#define sub_4E65C0					((bool(__cdecl*)(signed int MapNumber)) 0x4E65C0)
#define sub_89CB00					((LPVOID(*)())0x89CB00)
#define sub_89CB90					((int(__thiscall*)(LPVOID This)) 0x89CB90)

#define sub_969CA0					((int(__thiscall*)(LPVOID This, signed int a2, int a3)) 0x969CA0) //Getpreview struct
#define sub_637A30					((void(__cdecl*)())0x637A30)
#define sub_790B10					((bool(__cdecl*)(int a1, int a2, int a3, int a4)) 0x790B10) //If Work Zone
#define sub_5878E0					((int(__cdecl*)(BYTE a1)) 0x5878E0)













//Map
#define sub_47C1A0					((int(__cdecl*)(int a1, char *a2, int a3)) 0x47C1A0)
#define sub_47C220					((int(__cdecl*)(int a1, int a2, char *a3)) 0x47C220)
#define sub_480160					((int(__stdcall*)(int a1)) 0x480160)
#define sub_409AF0					((int(__stdcall*)(int a1)) 0x409AF0)
#define sub_409AD0					((void(__thiscall*)(LPVOID This)) 0x409AD0)
/////////////////////////

#define pNewPetTest1			((int(__cdecl*)(int a1))0x6411A0)
//----
#define	pViewNPCTargetID		*(int*)0xE6172C
#define	pViewAttackTargetID		*(int*)0xE61730

#define pPreviewThis			((LPVOID(*)()) 0x402BC0)
#define pClearPreviewThis		((LPVOID(*)()) 0x82C5C80)
#define pClearPreview			((void(__thiscall*)(LPVOID This)) 0x4CC780)
#define pClearWingsPreview			((void(__thiscall*)(LPVOID This)) 0x4CC650)

#define pGetPreviewStruct		((DWORD(__thiscall*)(LPVOID This, int ViewportID)) 0x0096A4C0)
#define pPreviewCharSet			((void(__cdecl*)(int ObjectIndex, BYTE * CharSet, lpViewObj Object, int Mode)) 0x57FD90)
#define oUserPreviewStruct		*(int*)0x7BC4F04
#define oUserObjectStruct		*(int*)0x8128AC8
#define oUserObjectStruct_		*(int*)0x8128AC4
#define oUserTextObject			*(int*)0x8128AC0 //ITEM.BMD
#define pGetMapName	((char*(__cdecl*)(int MapNumber)) 0x5D2C10)


#define pPlayerState			*(int*)0x0E609E8
#define oCharColor_Loot			(0x0064B6AB + 1) 
#define oCharColor_Exp			(0x0064C9A0 + 1)
#define pGetMoneyFormat			((int(__cdecl*)(double Value, char * Buff, int Arg3)) 0x5C1170)
#define pPlayEffectAnimation	((int(__cdecl*)(int EffectIndex, int PreviewStruct)) 0x00667130)
#define pPlayEffectAnimation2	((bool(__cdecl*)(int a1, int a2)) 0x667F70)
#define pTexEffect                      ((int(__thiscall*)(int This, signed int a2, int a3, float a4, signed int a5, float a6, float a7, float a8, int a9)) 0x005468A0) //0x004E2E70
#define pCustomEffGet                   ((int(__thiscall*)(LPVOID This, int a2, vec3_t a3, vec3_t a4, char a5)) 0x00545030) //0x004E171E
#define pCustomEffect                   ((int(__cdecl*)(int a1, vec3_t a2, float a3,vec3_t Color, int a5, int a6, int a7)) 0x771310) //0x006EC452
#define pCustomEffGet2                  ((int(__thiscall*)(LPVOID This, int a2, float a3,int a4,float a5,float a6, float a7, int a8,int a9)) 0x005494C0) //0x004E597C
#define pCustomEffGet2_                  ((int(__thiscall*)(int This, int a2, float a3,int a4,float a5,float a6, float a7, int a8,int a9)) 0x005494C0) //0x004E597C

// ----------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------

//-> Interface
#define pDrawInterfaceS			((char(__cdecl*)()) 0x004D7970)
#define oDrawInterfaceS_Call	0x004DA2AC
#define pDrawInterface			((void(__cdecl*)()) 0x0080F8E0)
#define oDrawInterface_Call		0x0080F7FE
#define pDrawGUI				((void(__cdecl*)(DWORD, float, float, float, float)) 0x00790B50)
#define pDrawToolTip			((int(__cdecl*)(int X, int Y, LPCSTR Text)) 0x00597220)
#define pDrawButton				((void(__cdecl*)(DWORD, float PosX, float Posy, float Width, float Height, float ButtonPosX, float ButtonPosY)) 0x00790E40)
#define pDrawSelectButton		((int(__stdcall*)(DWORD ID, int PosX, int PosY))0x779440)
#define pDrawColorButton		((void(__cdecl*)(DWORD, float, float, float, float, float, float, DWORD)) 0x00790F20)
#define pDrawExtraColor			((void(__cdecl*)(DWORD, float, float, float, float, float, float, float, float, DWORD)) 0x637A60)
#define pDrawMapObject			((void(__cdecl*)(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11, float a12, float a13, int a14)) 0x638400)
#define pDrawInfoBox			((char(__cdecl*)(char Text, int Arg2)) 0x00738200)
#define pDrawMessage			((int(__cdecl*)(LPCSTR Text, int Mode)) 0x00597630)
#define pMakeColor				((DWORD(__cdecl*)(BYTE, BYTE, BYTE, BYTE)) 0x00412D20)
#define pTextFormat				((int(__cdecl*)(char * Buffer, int Arg2, int LineSize, LPCTSTR Text, int LineWidth, bool Arg6, BYTE Arg7)) 0x540880)
#define pDrawColorText			((int(__cdecl*)(LPCTSTR Text, int PosX, int PosY, int Width, int Arg5, int Color, int Arg7, int Align)) 0x7D04D0)
#define pLoadImage				((int(__cdecl*)(char * Folder, DWORD Code, int Arg3, int Arg4, int Arg5, int Arg6)) 0x00772330)
#define pDrawImage              ((void(__cdecl*)(int ImageID, float PosX, float PosY, float Width, float Height, int Arg6, int Arg7, float ScaleX, float ScaleY, int FillCenter, int FillBolder, int Arg13)) 0x637C60)
#define pLoadModel				((void(__cdecl*)(int ResourceID, char * Path, char * File, int Arg4)) 0x614D10)
#define pLoadTexture			((void(__cdecl*)(int TextureID, char * Folder, int GLREPEAT, int GLNEAREST, int GLTRUE)) 0x614710)
#define pInitModelData			((void(__cdecl*)()) 0x00617D30)
#define pInitModelData2			((void(__cdecl*)()) 0x00626190)
#define pInitTextureData		((void(__cdecl*)()) 0x0061AED0)
#define pLoadSomeForm			((void(__cdecl*)()) 0x007C2050)
#define oLoadSomeForm_Call		0x007C1D7E
#define pWindowThis				((LPVOID(*)()) 0x861110)
#define pCheckWindow			((bool(__thiscall*)(LPVOID This, int Code)) 0x0085EC20)
#define pCloseWindow			((int(__thiscall*)(LPVOID This, int Code)) 0x0085F9A0)
#define pOpenWindow				((int(__thiscall*)(LPVOID This, int Code)) 0x0085EC50)
//#define pOpenInfoBox			((bool(__cdecl*)(LPVOID This, int Arg2, float Arg3)) 0x00790A10)
#define pOpenInfoBox			((bool(__cdecl*)(LPVOID This, int Arg2/*, float Arg3*/)) 0x790A10)
#define pTextLineThis			((LPVOID(*)()) 0x8128ADC)
#define pGetMapName				((char*(__cdecl*)(int MapNumber)) 0x5D2C10)
//#define pGetTextLine			((LPCSTR(__thiscall*)(LPVOID This, int LineNumber)) 0x402320)
#define pGetTextLine			((char*(__thiscall*)(LPVOID This, int LineNumber)) 0x402320)
#define pGetTextLineint			((int(__thiscall*)(LPVOID This, int LineNumber)) 0x402320)
#define pGetTextLine_			((char*(__thiscall*)(LPVOID This, int LineNumber)) 0x402320)
#define pMapName				((char*(__cdecl*)(signed int mapNumber)) 0x5D2C10)
#define pDrawItemModel			((int(__cdecl*)(float PosX, float PosY, float Width, float Height, int ItemID, int a6, int a7, float a8, char a9)) 0x5CF310)
#define pSetCursorFocus			*(DWORD*)0x00E8CB3C
#define pAllowGUI				((bool(__cdecl*)()) 0x007D4250)
#define oAllowGUI_Call1			0x007D378E
#define oAllowGUI_Call2			0x00811C42
#define pDrawBarForm			((void(__cdecl*)(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)) 0x6378A0)
#define pSetBlend				((void(__cdecl*)(BYTE Mode)) 0x635FD0)
#define pGLSwitchBlend			((void(__cdecl*)()) 0x00636070)
#define pGLSwitch				((void(__cdecl*)()) 0x00635F50)
#define pCharacterBuf			((int(__thiscall*)(void *This, int a2)) 0x0040FCA0)
#define pMapNumber				*(int*)0x0E61E18

//-> User
#define pLastSkillIndex			*(DWORD*)0x81C039C
#define	pViewUnknownTargetID	*(int*)0xE61728		//item target
#define pPartyListStruct		*(PartyList*)0x81CB4E8
#define pGetPartyStruct(Slot)	((Slot * sizeof(PartyList)) + (*(char**)pPartyListStruct))
#define pPartyMemberCount		*(DWORD*)0x81F6B6C
#define pGetPosFromAngle		((void(__cdecl*)(VAngle * Angle, int * PosX, int * PosY)) 0x635B00)
#define pCursorX				*(int*)0x879340C
#define pCursorY				*(int*)0x8793410
#define pTextThis				((LPVOID(*)()) 0x0041FE10)
#define pSetTextColor			((void(__thiscall*)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h)) 0x420040)
#define pSetTextBGColor			((void(__thiscall*)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h)) 0x4200B0)
#define pDrawText_				((int(__thiscall*)(LPVOID This, int PosX, int PosY, char * Text, int Arg4, int Arg5, int * Arg6, int Arg7)) 0x420150)
#define pDrawText				((int(__thiscall*)(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)) 0x00420150)
#define pMasterLevel			*(short*)0x87935D8
#define pMasterPoint			*(short*)0x87935F2
#define pMasterExp				*(__int64*)0x87935E0
#define pMasterNextExp			*(__int64*)0x87935E8
#define pFrameValue1			*(BYTE*)(0x004D9F02 + 2)
#define pFrameValue2			*(DWORD*)(0x004DA3B2 + 1)
#define pFrameValue3			*(DWORD*)(0x004DA3DD + 3)
#define pFrameValue4			*(BYTE*)(0x004DA3AC + 3)
#define pPlayerState			*(int*)0x0E609E8
#define pFrameLimit				0//need check value inside struct
#define pFrameSpeed1			*(double*)0x0D27C88
#define	pFrameSpeed2			*(double*)0x0D281C0
// ----------------------------------------------------------------------------------------------
#define pWinWidthReal			*(float*)0xE7C3D4
#define pWinHeightReal			*(float*)0xE7C3D8
#define pWinFontHeight			*(int*)0x81C0380
#define pWinWidth				*(GLsizei*)0x0E61E58
#define pWinHeight				*(GLsizei*)0x0E61E5C
#define pInitGraphics			((void(__cdecl*)()) 0x00777590)
#define oInitGraphics_Call		0x00776EAE
#define pIsButtonPressed		((int(__thiscall*)(int ButtonNumber)) 0x791070)
#define pGetMapName				((char*(__cdecl*)(int MapNumber)) 0x5D2C10)
#define pMoveListInit			((void(__thiscall*)(LPVOID This, int Arg1, int Arg2)) 0x00830C10)

//-> Item
#define pDrawModel				((int(__cdecl*)(float PosX, float PosY, float Width, float Height, int ItemID, int a6, int a7, float a8, char a9)) 0x5CF310)
#define pDrawNumber				((bool(__cdecl*)(int pObj))0x004E1230)
#define pGetItemColor			((void(__cdecl*)(int ModelID, float Arg2, float Arg3, VAngle * Color, bool BalrogMode)) 0x5F8C50)
#define pGetItemColor2			((void(__cdecl*)(int ModelID, float Arg2, float Arg3, VAngle * Color, bool BalrogMode)) 0x5FA4A0)
#define pSetItemPrice           ((__int64(__cdecl*)(ObjectItem * lpItem, int Mode)) 0x58E3B0)
#define pIsExpensiveItem		((bool(__cdecl*)(ObjectItem * lpItem)) 0x5C81F0)
#define pIsUpgradeItem			((bool(__thiscall*)(LPVOID This, ObjectItem * lpSource, ObjectItem * lpTarget)) 0x7DDC10)
#define pAllowRepairWings		((bool(__cdecl*)(ObjectItem * lpItem)) 0x5C9DA0)
#define pSetItemOption			((void(__cdecl*)(ObjectItem * lpItem, BYTE Option, BYTE Special, BYTE Value)) 0x58B910)
#define pSetItemOptionText		((void(__cdecl*)(int ItemID, int Line, WORD OptionID, bool Arg4, int Arg5)) 0x5C2F70)
#define pSetItemTextLine		((void(__cdecl*)(int Line, LPSTR Text, ...)) 0x9CF6AA)
#define pIsWings				((int(__thiscall*)(LPVOID This, DWORD ItemID)) 0x7E7870)
#define pSetItemEffect			((void(__cdecl*)(int Arg1, int ModelID, vec3_t Angle, int Arg4, int ItemLevel, char Arg6, int Arg7, int Arg8, int Arg9)) 0x609E70)
#define pSetItemEffect2			((void(__cdecl*)(float a4, float a5, float a6, int Object, float a8, DWORD ModelID, int a10, char a11, char a12, char a13, signed int a14, char a15)) 0x5655C0)
#define pGetMaxDurability		((short(__cdecl*)(ObjectItem * lpItem, int ScriptStruct, int Level)) 0x5C2170)
#define pIsFlyingMauntToMove	((bool(__thiscall*)(LPVOID This, WORD ItemID1, WORD ItemID2)) 0x831B09)
#define pAllowStaticEffect		((void(__thiscall*)(LPVOID This, DWORD * Arg1, DWORD Arg2, int Arg3, int Arg4)) 0x544E60)
#define pAllowStaticEffectSS	((void(__thiscall*)(LPVOID This, DWORD * Arg1, DWORD Arg2, int * Arg3, int Arg4)) 0x544E60)
#define pPlayStaticEffect		((int(__cdecl*)(DWORD ModelID, DWORD * Arg1, float Scale, float * Color, int Model, float a6, int a7)) 0x771310)
#define pPlayDynamicEffect		((int(__cdecl*)(DWORD ModelID, DWORD * Arg1, int Arg2, float * Color, int EffectID, float Arg5, int Arg6)) 0x74CD30)
#define pPlaySkillEffect		((int(__cdecl*)(DWORD ModelID, DWORD * Arg1, DWORD * Arg2, int EffectPos, int EffectID, float speed, float, __int16, __int16, char, int, int, __int16)) 0x72D1B0)

#define pDrawInterfaceNumBer   ((double(__stdcall*)(float X, float Y, int num, float size)) 0x854FE0)
#define pDrawInterfaceNumBer2   ((void(__cdecl*)(float X, float Y, int num, float size)) 0x791000)
#define pCreateEffect			((int(__cdecl*)(DWORD ModelID, DWORD * Position, int Angle, float * Color, int SubType, int Owner, short PKKey, BYTE Skill, float Scale, BYTE SkillSerial, float SkillAngle, BYTE SkillHotKey)) 0x006D9070)
#define pCreateEffect3			((int(__cdecl*)(DWORD ModelID, vec3_t Position, int Angle, vec3_t Color, int SubType, int Owner, short PKKey, BYTE Skill, float Scale, BYTE SkillSerial, float SkillAngle, BYTE SkillHotKey)) 0x006D9070)
#define pCreateEffect2			((int(__cdecl*)(int Type, vec3_t Position, vec3_t Angle, vec3_t Light, int SubType, OBJECT *Owner, short PKKey, BYTE Skill, float Scale, BYTE SkillSerial, vec3_t SkillAngle, BYTE SkillHotKey)) 0x006D9070)
#define pGetAttackSpeed			((void(__thiscall*)()) 0x593B20)
#define pPetCall1				((LPVOID(__cdecl*)(int ID, int PetStruct, int PetObjectView, int Mode, int arg5)) 0x5013B0)
#define pPetCall2				((LPVOID(__cdecl*)(int ID, int PetStruct, int PetObjectView, int Mode, int arg5)) 0x501700)
#define oItemText_Color			0x81C0A68
#define oItemText_Weight		0x81C09F0
#define oItemText_Line			0x81C0AE0
#define oItemText_Index			0x81F6BF0
#define	oItemText_Add			0x9CF6AA
#define oItemTitleColor			0x005C8261
#define oItemTitleColor_Next	(oItemTitleColor+8)
#define oItemTitleColor_Set		0x005A9C00
#define oItemDescriptionText		0x005AE921
#define oItemDescriptionText_Next	0x005AE96C						

#define pChatStructure			0x8129540
#define pFpsTime				0x0E8CB30
#define Main_PrintGlobal		00597630H

//-> Monster
#define oNpcName				0x8119F68
#define pSendChatSay			((int(__cdecl*)(char * Name, char * Text, int a1, int a4, int a5)) 0x5996A0)
#define pShowMonster			((int(__cdecl*)(int MonsterID, int a2, int a3, int a4)) 0x580FC0)
#define pLoadMonsterBMD			((void(__cdecl*)(signed int a1, char* a2, char* a3, signed int a4)) 0x614D10)
#define pLoadMonsterTexture		((void(__cdecl*)(int a1, char* a2, int a3, signed int a4)) 0x614710)
//#define pShowMonster			((double(__cdecl*)(int a1, int a2, int a3, int a4)) 0x580FC0)
#define pViewObject				((int(__cdecl*)(int a1, int a2, char a3, char a4, float a5)) 0x57EEC0)
#define pLoadMonsterID			((int(__cdecl*)(signed int a1)) 0x61FDE0)
#define pMonsterAttribute		((int(__cdecl*)(int ObjectPointer, signed int MonsterID)) 0x580BB0)
#define pNpcChat				((char*(__cdecl*)(int a1, int a2)) 0x559540)
#define pLoadNpcModel			((int(__cdecl*)(int a1)) 0x61E060)

//-> Other
#define oCam_Zoom				0x0D27BFC	//1037DB0
#define oCam_PosZDef			0x0D255AC	// Restore PosZ
#define oCam_PosZ				0x0D255A0	// PosZ
#define oCam_RotZ				0x87933D8	//8B4ACC8
#define oCam_RotZDef			0x0D27B78	//1033AB0
#define oCam_RotY				0x0D27B88	//1033AC0
#define oCam_ClipX				0x0D2C848	//1038D28
#define oCam_ClipY				0x0D2C894	//1033A78
#define oCam_ClipZ				0x0D2C8B8	//1038D78
#define oCam_ClipXCS			0x0D2C898	//1038D58
#define oCam_ClipYCS			0x0D2C8A8	//1038D68
#define oCam_ClipX2				0x0D2C878	//1038D38
#define oCam_ClipY2				0x0D2C880	//1038D40
#define oCam_ClipZ2				0x0D2B94C	//1037DA4
#define oCam_ClipGL				0x0D2570C	//1031BCC

//POSTITEM
//#include "mu_object_chat_data.h"
#include "mu_object_chat_data.h"
// ----------------------------------------------------------------------------------------------

#define oXORFilterStart         0x00404C99
#define pActiveSocket           *(SOCKET*)(*(DWORD*)0x0E61F84 + 0x0c)
//#define oDataRecv_Call          0x0065FD79
//#define pDataRecv               ((void(*)(DWORD Type, LPBYTE Data, int Len, int aIndex))0x00663B20) //1.04D-> 0x006639D0
//#define pWindowThis             ((LPVOID(*)())0x00861110)//1.04D-> 0x860FC0
//#define pCheckWindow            ((bool(__thiscall*)(LPVOID This, int Code))0x0085EC20)//1.04D-> 0x0085EAD0
//#define oUserObjectStruct       *(int*)0x8128AC8
//#define oUserObjectStruct_      *(int*)0x8128AC4

#define ChatBoxMuObjectChatDataPtrArray        ((MuObjectChatData **) (*(DWORD *) ((*(DWORD *) (0x09867090 + 0x10)) + 0x1C)))
#define ChatBoxMuObjectChatDataPtrFreeSlot     ((MuObjectChatData *)  (*(DWORD *) ((*(DWORD *) (0x09867090 + 0x10)) + 0x20)))
#define ChatBoxMuObjectChatDataPtrLastSlot     ((MuObjectChatData *)  (*(DWORD *) ((*(DWORD *) (0x09867090 + 0x10)) + 0x24)))
#define ChatBoxMuObjectChatDataPtrArrayLength  ((DWORD) (((DWORD) ChatBoxMuObjectChatDataPtrFreeSlot - (DWORD) ChatBoxMuObjectChatDataPtrArray) / sizeof(DWORD)))
#define ChatBoxMuObjectChatDataPtrArraySize    ((DWORD) ((((DWORD) ChatBoxMuObjectChatDataPtrLastSlot - (DWORD) ChatBoxMuObjectChatDataPtrArray) / sizeof(DWORD)) + 1))
#define pHandlePacketChatData ((void(__cdecl*)(const void * chat_msg)) 0x0063F850)
#define pDrawInterface2         ((void(__cdecl*)()) 0x00861110) //1.04D -> 0x00860FC0
#define oDrawInterface2_Call    0x0080F9AB //1.04D -> 0x0080F85B
#define pCurrentViewingItemName (*(DWORD *) (0x007E4528 + 2)) //1.04D-> (0x007E43D8 + 2))
#define CharacterHeadChatTextFirst(x) ((char *) ((x) + 0x194))
#define CharacterHeadChatTextLast(x) ((char *) ((x) + 0x194 - 0x100))

#define sub_636720_Addr ((int(*)())0x636720)
#define sub_6363D0_Addr ((void(__cdecl*)(GLint x, int a2, GLsizei width, GLsizei height)) 0x6363D0)
#define sub_6358A0_Addr ((int(__cdecl*)(float a1, float a2, float a3, float a4)) 0x6358A0)
#define sub_635830_Addr ((void(__cdecl*)(LPVOID a1)) 0x635830)
#define sub_635DE0_Addr ((void(*)()) 0x635DE0)
#define sub_635E40_Addr ((void(*)()) 0x635E40)
#define sub_637770_Addr ((void(*)()) 0x637770)

#define sub_959A60_Addr		((int(__cdecl*)(int a1, float a2, int a3, int a4)) 0x959A60)
#define sub_4E1250_Addr		((int(__cdecl*)(int a1, char a2)) 0x4E1250)
#define sub_4CDA10_Addr		((int(*)()) 0x4CDA10)
#define sub_969C50_Addr		((int(__thiscall*)(int This, signed int a2)) 0x969C50)
#define sub_5C9370_Addr		((bool(__cdecl*)(signed int a1, int a2)) 0x5C9370)
#define sub_5440B0_Addr		((int(__fastcall*)(int a1, int a2, int a3, float a4, float a5, __int16 a6, int a7, int a8, char a9, char a10)) 0x5440B0)
#define sub_4CC650_Addr		((char *(__thiscall*)(int This)) 0x4CC650)
#define sub_5F58E0_Addr		((int(__cdecl*)(ObjectModel * a1)) 0x5F58E0)
#define sub_635B00_Addr		((int(__cdecl*)(int a1, int a2, int a3)) 0x635B00)
#define sub_861110_Addr		((void *(*)()) 0x861110)
#define sub_861900_Addr		((int(__thiscall*)(int This)) 0x861900)
#define sub_943A20_Addr		((int(__stdcall*)(float a1, float a2)) 0x943A20)
#define sub_5D65E0_Addr		((double(__thiscall*)(int This)) 0x5D65E0)
#define sub_4CC720_Addr		((int(__thiscall*)(int This)) 0x4CC720)
#define sub_5CA0D0_Addr		((void(__cdecl*)(signed int a1, signed int a2, int a3, int a4, int a5, int a6, char a7)) 0x5CA0D0)
#define sub_60FC70_Addr				((void (__cdecl*)(int a1, int a2, int a3, int a4, float a5, int a6, int a7, int a8, char a9, char a10, char a11, int a12, int a13)) 0x60FC70)

#define sub_6D9070_Addr		((int(__cdecl*)(int Type, vec3_t Position, vec3_t Angle, vec3_t Light, int SubType, Object* Owner, __int16 PKKey, __int16 Skill, __int16 Scale, __int16 SkillSerial, float SkillAngle, __int16 SkillHotKey)) 0x6D9070)