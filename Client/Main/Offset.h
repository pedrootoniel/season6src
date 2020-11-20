#pragma once
#include <gl\GL.h>
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "Ws2_32.lib")

#define MAIN_WINDOW 0x00E8C578

#define MAIN_LANGUAGE 0x00E8C5C4
#define MAIN_CONNECTION_STATUS 0x08793704
#define MAIN_SCREEN_STATE 0x00E609E8
#define MAIN_CHARACTER_STRUCT 0x08128AC8
#define MAIN_PREVIEW_STRUCT	0x7BC4F04
#define MAIN_VIEWPORT_STRUCT 0x07BC4F04
#define MAIN_PACKET_SERIAL 0x08793700
#define MAIN_HELPER_STRUCT 0x00E8CB7C
#define MAIN_FONT_SIZE 0x081C0380
#define MAIN_RESOLUTION 0x00E8C240
#define MAIN_RESOLUTION_X 0x00E61E58
#define MAIN_RESOLUTION_Y 0x00E61E5C
#define MAIN_PARTY_MEMBER_COUNT 0x081F6B6C

#define ProtocolCore ((BOOL(*)(DWORD,BYTE*,DWORD,DWORD))0x00663B20)
#define DrawInterface ((void(*)(DWORD,float,float,float,float))0x00790B50)
#define DrawInterfaceText ((void(*)(char*,int,int,int,int,int,int,int))0x007D04D0)

//LTP
#define pDrawCircle  ((void(__cdecl*)(DWORD ModelID, float StartX, float StartY, float StartWidth, float StartHeight, float SourceX, float SourceY, float SourceWidth, float SourceHeight, bool Arg10, bool Arg11, float Arg12)) 0x637C60)
#define pSetFont				((int(__thiscall*)(LPVOID This, int a2)) 0x420120)
#define pSetBkColor				((int(__thiscall*)(LPVOID This, BYTE red, BYTE green, BYTE blue, BYTE alpha)) 0x4200B0)
#define pSetTexture				((void(__cdecl*)(int a1)) 0x00635CF0)//sub_635CF0(a1)

#define	pFontNormal				*(HGDIOBJ*)0x00E8C588
#define pFontBold				*(HGDIOBJ*)0x00E8C58C
#define pFontBigBold			*(HGDIOBJ*)0x00E8C590
#define pFontNormal2			*(HGDIOBJ*)0x00E8C594

#define pShowPrice				((int(*)(int a1, const char *a2, ...)) 0x9CF6AA)
#define pGetMoneyFormat			((int(__cdecl*)(double Value, char * Buff, int Arg3)) 0x5C1170)

#define pItemBmdStruct			*(ItemBmdStruct*)0x8128AC0
#define pGetItemBmdStruct(ItemId)	(ItemBmdStruct*)(*(DWORD*)0x8128AC0 + sizeof(ItemBmdStruct) * ItemId)

#define sub_41FFE0_Addr		((int(__thiscall*)(LPVOID a1)) 0x41FFE0)
#define sub_420010_Addr		((int(__thiscall*)(LPVOID a1)) 0x420010)
#define SetTextColorByHDC		((int(__thiscall*)(LPVOID a1, int color)) 0x420080)
#define sub_4200F0_Addr		((int(__thiscall*)(LPVOID a1, int a2)) 0x4200F0)

#define oShowChatMessage_Call	0x0078B0BC
#define pShowChatMessage		((bool(__thiscall*)(LPVOID This)) 0x00788A80)
#define pSetChatMessageType		((int(__thiscall*)(LPVOID This, int Type)) 0x0078B870)
#define pChatThis				((LPVOID(__thiscall*)(LPVOID This)) 0x861220)
#define pChatIsClosed			((bool(__thiscall*)(LPVOID This)) 0x786110)
#define pChatCheckLevel			((bool(__cdecl*)(int MinLevel, char * Name)) 0x597E10)
#define pChatWhisperThis		((LPVOID(__thiscall*)(LPVOID This)) 0x861620)
#define pChatWhisperActive		((bool(__thiscall*)(LPVOID This)) 0x849E00)
#define pChatReserveLine		((DWORD(__cdecl*)(DWORD Arg1, DWORD Arg2, DWORD Arg3)) 0x6D6C20)
#define pChatBoxThis			((DWORD(__thiscall*)(LPVOID This)) 0x861180)
#define pChatOutput				((void(__thiscall*)(DWORD This, char * Name, char * Message, DWORD Type, DWORD Arg4)) 0x007894E0)

#define pMessageRecv		((int(__cdecl*)(PMSG_CHAT_SEND* lpMsg)) 0x63F850)
#define pWhisperMessageRecv		((int(__cdecl*)(PMSG_CHAT_SEND* lpMsg)) 0x6400C0)

#define pPkLevelRecv		((int(__cdecl*)(PMSG_PK_LEVEL_SEND* lpMsg)) 0x64D090)
#define pGetViewportByIndex		((signed int(__cdecl*)(int a1)) 0x57D9A0)

#define sub_4CDA10_Addr		((int(*)()) 0x4CDA10)
#define sub_969C50_Addr		((int(__thiscall*)(int This, signed int a2)) 0x969C50)
#define sub_409A50_addr     ((void(__thiscall*)(void *This, int a2)) 0x409A50)
#define sub_7894E0_Addr		((void(__thiscall*)(char* This, int Name, int Message, DWORD Type, DWORD Arg4)) 0x007894E0)
#define sub_409AD0_Addr		((int(__thiscall*)(LPVOID a1)) 0x00409AD0)