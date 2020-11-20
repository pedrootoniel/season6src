#pragma once
// ----------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------
#define PARTY_MOVE		FALSE
#define ADD_PARTY_LEADER		FALSE
#define _NEW_PARTY_SYSTEM_		FALSE
#define	_ELF_BUFF_SHOW_			FALSE
#define MAX_BUFF				300
#define BUFF_PARTY				1
// ----------------------------------------------------------------------------------------------

#define ex_PM_FLAGNEW_LEADER 0x789A

#if _NEW_PARTY_SYSTEM_ == TRUE
#define MAX_USER_IN_PARTY	7
#else
#define MAX_USER_IN_PARTY	5
#endif
// ----------------------------------------------------------------------------------------------

#define oUserPreviewStruct  *(int*)0x7BC4F04

#define ADD_EAX				0x05
#define ADD_EDX_1			0x81
#define ADD_EDX_2			0xC2
#define ADD_ECX_1			0x81
#define ADD_ECX_2			0xC1
#define PUSH_OFFSET			0x68
// -----------------------------------------------------------------------------------------------

#define sub_9CEFB0        ((int(__thiscall*)(int a1)) 0x009CF130) //1
#define sub_4200B0        ((int(__thiscall*)(LPVOID This, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 a4, unsigned __int8 a5)) 0x4200B0)
#define sub_4C8640        ((char(__thiscall*)(LPVOID This, char a2)) 0x4C8640)
#define sub_637A30        ((void(__cdecl*)()) 0x637A30)
#define sub_420080        ((int(__thiscall*)(LPVOID This, int a2)) 0x420080)
#define sub_5996A0        ((int(__cdecl*)(int a1, const CHAR *a2, int a3, int a4, int a5)) 0x5996A0)
#define sub_84C760        ((char(__stdcall*)(int a1)) 0x0084C8B0) //1
#define sub_5B7900        ((int(__cdecl*)(unsigned __int8 a1)) 0x5B7900 )
// -----------------------------------------------------------------------------------------------

struct PMSG_PARTYDELUSER
{
	PBMSG_HEAD h;
	BYTE Number;	// 3
};
// ----------------------------------------------------------------------------------------------

struct PMSG_PARTYLIST
{
	char szId[10];
	BYTE Number;
	BYTE MapNumber;
	BYTE X;
	BYTE Y;
	int Life;
	int MaxLife;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_PARTYLISTCOUNT
{
	PBMSG_HEAD h;
	BYTE Result;
	BYTE Count;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_DEFAULT_COUNT
{
	PBMSG_HEAD h;
	BYTE Count;	// 3
};
// ----------------------------------------------------------------------------------------------

struct PMSG_PARTYLIFEALL
{
	BYTE Number;	// 0
};
// ----------------------------------------------------------------------------------------------

struct PartyUser //-> Complete (size: 32)
{
	/*+0*/	char	Name[10];
	/*+10*/	BYTE	Unknown10;
	/*+11*/	BYTE	Unknown11;
	/*+12*/	BYTE	MapNumber;
	/*+13*/	BYTE	PosX;
	/*+14*/	BYTE	PosY;
	/*+15*/ char 	gap01;
	/*+16*/	int		Life;
	/*+20*/	int		MaxLife;
	/*+24*/	BYTE	LifePercent;
	/*+25*/ BYTE	gap02[3];
	/*+28*/	int		ViewportID;	
};
// ----------------------------------------------------------------------------------------------

#if(ADD_PARTY_LEADER==1)
struct GC_PARTYNEWLEADER
{
	PSBMSG_HEAD h;
	BYTE id;
};
#endif

class NewParty
{
public:
		 NewParty();
		~NewParty();

	void Init();
	void Load();
#if(ADD_PARTY_LEADER==1)
	void LoadIMG();
#endif
	DWORD TestOPEx(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);
	DWORD TestOPEx(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2);
	DWORD TestOPEx(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2, const BYTE cmd3);

	static void DrawBarForm(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6);
	static char TargetPartyMember(LPVOID This);
	static void GCPartyListAll(LPBYTE aRecv);
	static int MainPartyVieweID();
	static int MainVieweID(unsigned __int8 a1);
	static void GetCoordPanelD(int a1, float a2, float a3, float a4, float a5);
	static void DrawPanelD();
	static int PartyMemberLifeRecv(LPBYTE aRecv);

	int PartyVieweID();
	void DrawPartyUser();
	float CoordX(int PartySlot);
	float CoordY(int PartySlot);
	bool CursorUser(int PartySlot);
	int CursorPartyMember();
	void MouseController(int Click);
	void MouseControllerD(int Click);
	void MouseControllerPage(int Click);
	void PartyPanelBlock(signed int a1, signed int a2, float a3, float a4, float a5, signed int a6);
	void DrawPanelPartyMember(int a1, int a2);
	int FilterPartyNumber(int a1, int a2, unsigned int a3);
#if(ADD_PARTY_LEADER==1)
	void MouseControllerLeader(int Click);
	int pmID;
	void MouseControllerMove(int Click);
	int pmID2;
#endif
	int PartyMemberCount;
	float StartX;
	float StartY;
	float PanelDX;
	float PanelDY;
	DWORD ClickTick;
	int OnClick;
	int OnClickD;
	int Page;
	bool PartyShow;

	PartyUser PartyData[MAX_USER_IN_PARTY];
	BYTE LifePercent[MAX_USER_IN_PARTY * 32];
	int ViewportID[MAX_USER_IN_PARTY * 8];

};
extern NewParty g_Party;
// ----------------------------------------------------------------------------------------------
