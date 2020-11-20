#include "stdafx.h"
#include "NewParty.h"
#include "Object.h"
#include "User.h"
#include "Interface.h"
#include "Protocol.h"
#include "PartyBuffs.h"
#include "Util.h"
#include "HealthBar.h"
#include "Offset.h"
#include "Console.h"
#include "TMemory.h"
// ----------------------------------------------------------------------------------------------

NewParty g_Party;
// ----------------------------------------------------------------------------------------------

NewParty::NewParty()
{
	//this->Init();
	//this->Load();
}
// ----------------------------------------------------------------------------------------------

NewParty::~NewParty()
{
}
// ----------------------------------------------------------------------------------------------

void NewParty::Init()
{
	this->PartyMemberCount = 0;

	this->ClickTick = 0;
	this->OnClick = -1;
	this->OnClickD = -1;
	this->Page = 0;
	this->StartX = 0;
	this->StartY = 0;
	this->PanelDX = 0;
	this->PanelDY = 0;
	this->PartyShow = true;
#if(ADD_PARTY_LEADER==1)
	this->pmID = -1;
	this->pmID2 = -1;
#endif

	ZeroMemory(&this->PartyData, sizeof(PartyData));
	ZeroMemory(&this->LifePercent, sizeof(LifePercent));
	ZeroMemory(&this->ViewportID, sizeof(ViewportID));
}
// ----------------------------------------------------------------------------------------------

#if(ADD_PARTY_LEADER==1)
void NewParty::LoadIMG()
{
	//gInterface.ImageLoad("Custom\\Interface\\pm_flag.tga", ex_PM_FLAGNEW_LEADER, 0x2601, 0x2900, 1, 0);
}
#endif

void NewParty::Load()
{
#if(ADD_PARTY_LEADER==1)
	this->LoadIMG();
#endif
#if _NEW_PARTY_SYSTEM_ == FALSE
	return;
#endif
	this->Init();
	BYTE bPartyD[] = { 0x83, 0x3D, 0x6C, 0x6B, 0x1F, 0x08, 0x00, 0x0F, 0x8E, 0x8E, 0x00, 0x00, 0x00, 0x90, 0x90 };
	WriteMemory((LPVOID)0x0084A6C8/*0x0084A578*/, bPartyD, sizeof(bPartyD));
	DWORD AdressNewParty = (DWORD)&this->PartyData;
	TestOPEx((LPVOID)0x0051C629, &AdressNewParty, ADD_EDX_1, ADD_EDX_2);
	TestOPEx((LPVOID)0x0078F28A/*0x0078F13A*/, &AdressNewParty, PUSH_OFFSET);	//прием в парт
	TestOPEx((LPVOID)0x0084A6FA/*0x0084A5AA*/, &AdressNewParty, ADD_EAX);//original 
	TestOPEx((LPVOID)0x0084A710/*0x0084A5C0*/, &AdressNewParty, PUSH_OFFSET);//original 
	TestOPEx((LPVOID)0x0084A731/*0x0084A5E1*/, &AdressNewParty, ADD_EAX);	//original
	DWORD AddressLifePercent = (DWORD)&this->LifePercent;
	TestOPEx((LPVOID)0x0095FED9/*0x0095FD59*/, &AddressLifePercent, 0x0F, 0xB6, 0x89);//+ 
	DWORD AddressViewportID = (DWORD)&this->ViewportID;
	TestOPEx((LPVOID)0x0095FF91/*0x0095FE11*/, &AddressViewportID, 0x8B, 0x91);//+
	DWORD AddressPartyMemberCount = (DWORD)&this->PartyMemberCount;
	TestOPEx((LPVOID)0x0095E6B7/*0x0095E537*/, &AddressPartyMemberCount, 0x83, 0x3D);//+
	TestOPEx((LPVOID)0x0095FE98/*0x0095FD18*/, &AddressPartyMemberCount, 0x3B, 0x05);//+ ??
	TestOPEx((LPVOID)0x0095E70D/*0x0095E58D*/, &AddressPartyMemberCount, 0x83, 0x05);//+  
	TestOPEx((LPVOID)0x0095FF7F/*0x0095FDFF*/, &AddressPartyMemberCount, 0x3B, 0x05);//+ 
	TestOPEx((LPVOID)0x0051C61B, &AddressPartyMemberCount, 0x3B, 0x0D);//+
	TestOPEx((LPVOID)0x0064E2CC, &AddressPartyMemberCount, 0xC7, 0x05);//+ при разрыве партии
	TestOPEx((LPVOID)0x0084A6EC/*0x0084A59C*/, &AddressPartyMemberCount, 0x3B, 0x15);//+ 
	TestOPEx((LPVOID)0x0084A6C8/*0x0084A578*/, &AddressPartyMemberCount, 0x83, 0x3D);//+ My Hook  
	TestOPEx((LPVOID)0x005C60CB, &AddressPartyMemberCount, 0x83, 0x3D);	//DL Summon
	TestOPEx((LPVOID)0x00814033/*0x00813EE3*/, &AddressPartyMemberCount, 0x83, 0x3D);	//DL Summon 
	TestOPEx((LPVOID)0x005AD1B2, &AddressPartyMemberCount, 0x83, 0x3D);	//DL Summon
	TestOPEx((LPVOID)0x0078F274/*0x0078F124*/, &AddressPartyMemberCount, 0x83, 0x3D);	//Принимает в пт любой фикс 
	TestOPEx((LPVOID)0x0084BA51/*0x0084B901*/, &AddressPartyMemberCount, 0x0F, 0xAF, 0x0D);
	BYTE NoLimitPartyMember[] = { 0xEB, 0x07 };
	WriteMemory((LPVOID)0x0084BDC5/*0x0084BC75*/, NoLimitPartyMember, sizeof(NoLimitPartyMember));
	BYTE LimitPtMemberFix2[] = { 0xEB, 0x04 };
	WriteMemory((LPVOID)0x0084BCC5/*0x0084BB75*/, LimitPtMemberFix2, sizeof(LimitPtMemberFix2));
	BYTE NoAddedPartyMember[] = { 0x83, 0xC0, 0x00 };
	WriteMemory((LPVOID)0x0084BE45/*0x0084BCF5*/, NoAddedPartyMember, sizeof(NoAddedPartyMember));
	BYTE OnlyOnePartyCord[] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	WriteMemory((LPVOID)0x0084BE54/*0x0084BD04*/, OnlyOnePartyCord, sizeof(OnlyOnePartyCord));
	BYTE OriginalPartyBlock[] = { 0xE9, 0x3C, 0x05, 0x00, 0x00, 0x90 };
	WriteMemory((LPVOID)0x0084BEEE/*0x0084BD9E*/, OriginalPartyBlock, sizeof(OriginalPartyBlock));
	SetOp3(0x005B83EE, this->MainPartyVieweID, 0xE8);
	SetOp3(0x005B84D3, this->MainPartyVieweID, 0xE8);
	SetOp3(0x005B856C, this->MainPartyVieweID, 0xE8);
	SetOp3(0x005B857A, this->MainPartyVieweID, 0xE8);
	SetOp3(0x005B8395, this->MainVieweID, 0xE8);
	SetOp3(0x005B83AD, this->MainVieweID, 0xE8);
	SetOp3(0x005B83C5, this->MainVieweID, 0xE8);
	SetOp3(0x005B84EB, this->MainVieweID, 0xE8);
	SetOp3(0x005B8506, this->MainVieweID, 0xE8);
	SetOp3(0x005B851E, this->MainVieweID, 0xE8);
	SetOp3(0x0084BEDF/*0x0084BD8F*/, this->DrawBarForm, 0xE8);
	SetOp3(0x0084BCCE/*0x0084BB7E*/, this->TargetPartyMember, 0xE8);
	SetOp3(0x0084A546/*0x0084A3F6*/, this->GetCoordPanelD, 0xE8);
	SetOp3(0x0084A6D5/*0x0084A585*/, this->DrawPanelD, 0xE8);
	SetOp3(0x00664568/*0x00664418*/, this->GCPartyListAll, 0xE8);
	SetOp3(0x0066458A/*0x0066443A*/, this->PartyMemberLifeRecv, 0xE8);
	BYTE bHookPtD[] = { 0xE9, 0x2B, 0x02, 0x00, 0x00 };
	WriteMemory((LPVOID)0x0084A6DA/*0x0084A58A*/, bHookPtD, sizeof(bHookPtD));
}
// ----------------------------------------------------------------------------------------------

DWORD NewParty::TestOPEx(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	// ----
	btBuf[0] = cmd;
	memcpy((LPVOID)& btBuf[1], (LPVOID)dwJMPAddress, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}
// ----------------------------------------------------------------------------------------------

DWORD NewParty::TestOPEx(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2)
{
	BYTE btBuf[6];
	// ----
	btBuf[0] = cmd;
	btBuf[1] = cmd2;
	memcpy((LPVOID)& btBuf[2], (LPVOID)dwJMPAddress, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}
// ----------------------------------------------------------------------------------------------

DWORD NewParty::TestOPEx(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2, const BYTE cmd3)
{
	BYTE btBuf[7];
	// ----
	btBuf[0] = cmd;
	btBuf[1] = cmd2;
	btBuf[2] = cmd3;
	memcpy((LPVOID)& btBuf[3], (LPVOID)dwJMPAddress, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}
// ---------------------------------------------------------------------------------------------

int NewParty::PartyVieweID()
{
#if _NEW_PARTY_SYSTEM_ == FALSE
	return false;
#endif

	for (int i = 0; i < this->PartyMemberCount; i++)
	{
		this->LifePercent[32 * i] = this->PartyData[i].LifePercent;
		this->ViewportID[8 * i] = this->PartyData[i].ViewportID;
		this->PartyData[i].ViewportID = -2;
	}

	int result;
	signed int v2;
	signed int v3;
	signed int v4;
	int v6;

	for (int i = 0; i < 400; ++i)
	{
		int v12 = pGetPreviewStruct(pPreviewThis(), i);
		if (*(DWORD *)(v12 + 824) == 1163
			&& *(BYTE *)(v12 + 800) == 1
			&& *(BYTE *)(v12 + 780)
			&& *(BYTE *)(v12 + 788)
			&& *(float *)(v12 + 928) > 0.0
			&& !*(BYTE *)(v12 + 36))
		{
			for (int j = 0; j < this->PartyMemberCount; j++)
			{
				int v10 = (int)&this->PartyData[j];
				if (this->PartyData[j].ViewportID == -2 && this->PartyData[j].ViewportID <= -1)
				{
					unsigned int v7 = sub_9CEFB0(v12 + 56) >= 1 ? sub_9CEFB0(v12 + 56) : 1;
					if (sub_9CEFB0(v10) <= v7)
					{
						int v5 = sub_9CEFB0(v12 + 56) >= 1 ? sub_9CEFB0(v12 + 56) : 1;
						v6 = v5;
					}
					else
					{
						v6 = sub_9CEFB0(v10);
					}
					if (!this->FilterPartyNumber(v10, v12 + 56, v6))
					{
						this->PartyData[j].ViewportID = i;
						break;
					}
				}
			}
		}
		result = i + 1;
	}

	for (int k = 0; k < this->PartyMemberCount; k++)
	{
		int v8 = (int)&this->PartyData[k];
		if (this->PartyData[k].ViewportID < 0)
		{
			if (sub_9CEFB0(LODWORD(oUserPreviewStruct) + 56) >= 1)
				v4 = sub_9CEFB0(LODWORD(oUserPreviewStruct) + 56);
			else
				v4 = 1;
			if (sub_9CEFB0(v8) <= (unsigned int)v4)
			{
				if (sub_9CEFB0(LODWORD(oUserPreviewStruct) + 56) >= 1)
					v2 = sub_9CEFB0(LODWORD(oUserPreviewStruct) + 56);
				else
					v2 = 1;
				v3 = v2;
			}
			else
			{
				v3 = sub_9CEFB0(v8);
			}
			result = this->FilterPartyNumber(v8, LODWORD(oUserPreviewStruct) + 56, v3);
			if (result)
				this->PartyData[k].ViewportID = -1;
			else
				this->PartyData[k].ViewportID = -3;
		}
	}

	return result;
}
// ----------------------------------------------------------------------------------------------

void NewParty::DrawBarForm(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)
{
	g_Party.StartX = PosX - 2;
	g_Party.StartY = PosY - 2;
	g_Party.DrawPartyUser();
	//#if(BUFF_PARTY==0)
	//	g_NewPartyBuff.DrawBuff();
	//#endif
}
// ----------------------------------------------------------------------------------------------

float NewParty::CoordX(int PartySlot)
{
	return this->StartX;
}
// ----------------------------------------------------------------------------------------------

float NewParty::CoordY(int PartySlot)
{
	return this->StartY + PartySlot * 24.0;
}
// ----------------------------------------------------------------------------------------------

bool NewParty::CursorUser(int PartySlot)
{
	float MaxX = this->StartX + 77.0;
	float MinY = this->StartY + PartySlot * 23.0;
	float MaxY = this->StartY + 23.0 + PartySlot * 23.0;
	// ----
	if ((pCursorX < this->StartX || pCursorX > MaxX) ||
		(pCursorY < this->StartY || pCursorY > MaxY))
	{
		return false;
	}
	// ----
	return true;
}
// ----------------------------------------------------------------------------------------------

int NewParty::CursorPartyMember()
{
	for (int n = 0; n < this->PartyMemberCount; n++)
	{
		if (this->CursorUser(n))
		{
			return n;
		}
	}
	return -1;
}
// ----------------------------------------------------------------------------------------------


void NewParty::DrawPartyUser()
{
#if _NEW_PARTY_SYSTEM_ == FALSE
	return;
#endif

	if (this->PartyMemberCount <= 0)
	{
		return;
	}

	if (!this->PartyShow)
	{
		return;
	}

	lpCharObj lpPlayer = gObjUser.lpPlayer;

	float X = StartX;
	float Y = StartY;

	float pmMaxX = 0;
	float pmMaxY = 0;

	pSetBlend(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	HGDIOBJ h = *(HGDIOBJ*)0x00E8C588;
	pSetFont(pTextThis(), int(h));
	pSetTextColor(pTextThis(), 0xFF, 0xFF, 0xFF, 0xFF);
	sub_4200B0(pTextThis(), 0, 0, 0, 0);

	for (int p = 0; p < this->PartyMemberCount; p++)
	{
		glColor4f(0.0, 0.0, 0.0, 0.89999998);
		X = this->CoordX(p) + 2;
		Y = this->CoordY(p) + 2;
		pDrawBarForm(X, Y, 74.0, 17.0, 0.0, 0);
		pSetBlend(1);

		if (this->PartyData[p].ViewportID == -1)
		{
			glColor4f(0.30000001, 0.0, 0.0, 0.5);
			X = this->CoordX(p) + 2;
			Y = this->CoordY(p) + 2;
			pDrawBarForm(X, Y, 74.0, 17.0, 0.0, 0);
			pSetBlend(1);
		}
		else
		{
			DWORD Object = pGetPreviewStruct(pPreviewThis(), this->PartyData[p].ViewportID);

			//#if _ELF_BUFF_SHOW_ == TRUE
						/*if(!gPARTY_SYSTEM)
						{*/
			if (Object && sub_4C8640((LPVOID)(Object + 1260), 2) == 1)
			{
				glColor4f(0.2, 1.0, 0.2, 0.2);
				X = this->CoordX(p) + 2;
				Y = this->CoordY(p) + 2;
				pDrawBarForm(X, Y, 74.0, 17.0, 0.0, 0);
				pSetBlend(1);
			}
			/*}*/
//#endif

			if (this->CursorPartyMember() != -1 && this->CursorPartyMember() == p)
			{
				glColor4f(0.40000001, 0.40000001, 0.40000001, 0.69999999);
				X = this->CoordX(p) + 2;
				Y = this->CoordY(p) + 2;
				pDrawBarForm(X, Y, 74.0, 17.0, 0.0, 0);
				pSetBlend(1);
			}
		}

		sub_637A30();
		X = this->CoordX(p);
		Y = this->CoordY(p);
		pDrawGUI(31557, X, Y, 77.0, 23.0);

		if (p)
		{
			if (this->PartyData[p].ViewportID == -1)
			{
				sub_420080(pTextThis(), pMakeColor(-128, -128, -128, -1));
			}
			else
			{
				sub_420080(pTextThis(), pMakeColor(-1, -1, -1, -1));
			}
#if(ADD_PARTY_LEADER==1)
			if(gInterface.m_PartyLeader == 1)
			{
				if (!strcmp(this->PartyData[0].Name, lpPlayer->Name))
				{
					X = this->CoordX(p) + 53;
					Y = this->CoordY(p) + 3;

					pmMaxX = X + 9;
					pmMaxY = Y + 10;

					pDrawGUI(ex_PM_FLAGNEW_LEADER, X, Y, 9.0, 10.0);

					if (gInterface.IsWorkZone(X, Y, pmMaxX, pmMaxY))
					{
						if (this->pmID > 0)
						{
							pDrawColorButton(ex_PM_FLAGNEW_LEADER, X, Y, 9, 10, NULL, NULL, eRed);
						}
						else
						{
							pDrawColorButton(ex_PM_FLAGNEW_LEADER, X, Y, 9, 10, NULL, NULL, eBlue);
						}
					}
				}
			}
#endif
			X = this->CoordX(p) + 4;
			Y = this->CoordY(p) + 4;
			pDrawText(pTextThis(), X, Y, this->PartyData[p].Name, 74.0, 0, (int*)1, 0);

		}
		else
		{
			if (this->PartyData[0].ViewportID == -1)
			{
				sub_420080(pTextThis(), pMakeColor(-128, 75, 11, -1));
			}
			else
			{
				sub_420080(pTextThis(), pMakeColor(-1, -108, 22, -1));
			}
			X = this->CoordX(p) + 53;
			Y = this->CoordY(p) + 3;
			pDrawGUI(31553, X, Y, 9.0, 10.0);
			X = this->CoordX(p) + 4;
			Y = this->CoordY(p) + 4;
			pDrawText(pTextThis(), X, Y, this->PartyData[p].Name, 74.0, 0, (int*)1, 0);
		}

		int HPLine = 0;
		if (this->PartyData[p].LifePercent <= 10)
		{
			HPLine = this->PartyData[p].LifePercent;
		}
		else
		{
			HPLine = 10;
		}

		float DrawHpLine = (double)HPLine / 10.0 * 69.0;

		X = this->CoordX(p) + 4;
		Y = this->CoordY(p) + 16;
		pDrawGUI(31558, X, Y, DrawHpLine, 3.0);

		if (!strcmp(this->PartyData[0].Name, lpPlayer->Name) || !strcmp(this->PartyData[p].Name, lpPlayer->Name))
		{
			X = this->CoordX(p) + 53 + 10;
			Y = this->CoordY(p) + 2;

			float Whith = 12;
			float High = 12;

			float standartWhith = Whith / ((Whith * 2) / 1.5);
			float standartHight = High / ((High * 4) / 1.5);

			int DrawSwitch = 1;

			if (this->OnClick == this->PartyData[p].Unknown11 && this->OnClick != -1)
			{
				DrawSwitch = 2;
			}

			float CritY = (double)(DrawSwitch / 2) * High / ((High * 4) / 1.5);

			pDrawCircle(0x7B42, X, Y, Whith, High, 0.0, CritY, standartWhith, standartHight, 1, 1, 0.0);
		}
#if(PARTY_MOVE==1)
			if(gInterface.m_PartyTrace == 1)
			{
				if (strcmp(this->PartyData[p].Name, lpPlayer->Name))
				{
					X = this->CoordX(p) + 33;
					Y = this->CoordY(p) + 3;

					pmMaxX = X + 9;
					pmMaxY = Y + 10;

					pDrawGUI(0x79E1, X, Y, 13, 13);

					if (gInterface.IsWorkZone(X, Y, pmMaxX, pmMaxY))
					{
						if (this->pmID2 > 0)
						{
							pDrawColorButton(0x79E1, X, Y, 13, 13, NULL, NULL, eRed);
						}
						else
						{
							pDrawColorButton(0x79E1, X, Y, 13, 13, NULL, NULL, eBlue);
						}
					}
				}
			}
#endif
		//перенести отрисовку баффов
#if(BUFF_PARTY==1)
		//if(gPARTY_SYSTEM /*|| g_ExLicense.CheckUser(eExUB::MedoniAndrei)*/)
		//{
		//	//float Buff_Y = Y;// 15 + ( 24 * p );
		//	//float Buff_X = X - 70.0;

		//	X = this->CoordX(p) - g_NewPartyBuff.Whith;
		//	Y = this->CoordY(p);

		//	int pb = 0;

		//	for(int n = 0; n <  g_NewPartyBuff.PartyUser[p].btBuffCount; n++)
		//	{
		//		int BuffIndex =	g_NewPartyBuff.PartyUser[p].iBuffList[n];

		//		if(g_NewPartyBuff.AllBuff[BuffIndex] == true)
		//		{
		//			g_NewPartyBuff.DrawBuffParty(BuffIndex, X, Y);

		//			if(pb == 0 || pb == 2 || pb == 4 || pb == 6 || pb == 8)
		//			{
		//				Y += g_NewPartyBuff.High;	
		//			}
		//			else
		//			{
		//				X -= g_NewPartyBuff.Whith;	
		//				Y -= g_NewPartyBuff.High;
		//			}		

		//			pb++;
		//		}
		//	}
		//}
#endif
	}

	pGLSwitch();
}
// ----------------------------------------------------------------------------------------------

void NewParty::MouseController(int Click)
{
	if (this->PartyMemberCount <= 0)
	{
		return;
	}

	if (!g_Party.PartyShow)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->ClickTick);
	// ----
	int ClickMember = -1;

	lpCharObj lpPlayer = gObjUser.lpPlayer;

	for (int p = 0; p < this->PartyMemberCount; p++)
	{
		if (!strcmp(this->PartyData[0].Name, lpPlayer->Name) || !strcmp(this->PartyData[p].Name, lpPlayer->Name))
		{
			float X = this->CoordX(p) + 53 + 10;
			float Y = this->CoordY(p) + 2;

			float MaxX = X + 12;
			float MaxY = Y + 12;

			if ((pCursorX < X || pCursorX > MaxX) ||
				(pCursorY < Y || pCursorY > MaxY))
			{
				continue;
			}
			// ----
			ClickMember = this->PartyData[p].Unknown11;
			break;
		}
	}

	if (ClickMember == -1)
	{
		this->OnClick = -1;
		return;
	}

	if (Click == WM_LBUTTONDOWN)
	{
		//g_Console.AddMessage(5,"LOL");
		this->OnClick = ClickMember;
		return;
	}
	// ----
	this->OnClick = -1;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->ClickTick = GetTickCount();
	// ----
	PMSG_PARTYDELUSER pRequest;
	pRequest.h.set(0x43, sizeof(pRequest));
	pRequest.Number = (BYTE)ClickMember;
	//g_Console.AddMessage(5,"Index = %d",ClickMember);
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

char NewParty::TargetPartyMember(LPVOID This)
{
	if (!g_Party.PartyShow)
	{
		return 0;
	}

	for (int i = 0; i < g_Party.PartyMemberCount; i++)
	{
		if (g_Party.CursorPartyMember() != -1 && g_Party.CursorPartyMember() == i)
		{
			if (pViewAttackTargetID == -1)
			{
				DWORD ObjectID = pGetPreviewStruct(pPreviewThis(), g_Party.PartyData[i].ViewportID);
				if (ObjectID)
				{
					if (ObjectID != LODWORD(*(DWORD*)0x7BC4F04))
						sub_5996A0(ObjectID + 56, (const CHAR *)&*(DWORD*)0x0D47C9C, ObjectID, 0, -1); //??
				}
			}
			sub_84C760((int)&g_Party.PartyData[i]);
			return 1;
		}
	}

	return 0;
}
// ----------------------------------------------------------------------------------------------

void NewParty::GCPartyListAll(LPBYTE aRecv)
{
	int datasize = 0;
	PMSG_PARTYLISTCOUNT pCount;
	memcpy(&pCount, &aRecv[datasize], sizeof(pCount));

	g_Party.PartyMemberCount = pCount.Count;

	datasize = 5;

	for (int i = 0; i < g_Party.PartyMemberCount; ++i)
	{
		PMSG_PARTYLIST pList;
		memcpy(&pList, &aRecv[datasize], sizeof(pList));

		strncpy(g_Party.PartyData[i].Name, pList.szId, 10);
		g_Party.PartyData[i].Unknown10 = 0;
		g_Party.PartyData[i].Unknown11 = pList.Number;
		g_Party.PartyData[i].MapNumber = pList.MapNumber;
		g_Party.PartyData[i].PosX = pList.X;
		g_Party.PartyData[i].PosY = pList.Y;
		g_Party.PartyData[i].Life = pList.Life;
		g_Party.PartyData[i].MaxLife = pList.MaxLife;

		datasize += 24;
	}
}
// ----------------------------------------------------------------------------------------------

int NewParty::MainPartyVieweID()
{
	return g_Party.PartyVieweID();
}
// ----------------------------------------------------------------------------------------------

int NewParty::MainVieweID(unsigned __int8 a1)
{
	int result = sub_5B7900(a1);

	g_Party.PartyVieweID();

	return result;
}
// ----------------------------------------------------------------------------------------------

void NewParty::GetCoordPanelD(int a1, float a2, float a3, float a4, float a5)
{
	pDrawGUI(a1, a2, a3, a4, a5);

	g_Party.PanelDX = a2;
	g_Party.PanelDY = a3;

	float pX = g_Party.PanelDX - 10;
	float pY = g_Party.PanelDY + 123;

	//if(g_Party.PartyMemberCount <= 5)
	//{
	//	return;
	//}

	gInterface.DrawFormat(eGold, pX + 95, pY + 279, 100, 1, "Page: %d/%d", g_Party.Page + 1, 2);

	pDrawGUI(0x7BAA, pX + 70, pY + 275, 20, 20);

	if (gInterface.IsWorkZone(pX + 70.0f, pY + 275.0f, pX + 70.0f + 20.0f, pY + 275.0f + 20.0f))
	{
		pDrawColorButton(0x7BAA, pX + 70, pY + 275, 20, 20, 0, 0, pMakeColor(255, 204, 20, 130));
	}

	pDrawGUI(0x7BAB, pX + 133, pY + 275, 20, 20);

	if (gInterface.IsWorkZone(pX + 133, pY + 275, pX + 133 + 20, pY + 275 + 20))
	{
		pDrawColorButton(0x7BAB, pX + 133, pY + 275, 20, 20, 0, 0, pMakeColor(255, 204, 20, 130));
	}
}
// ----------------------------------------------------------------------------------------------

void NewParty::PartyPanelBlock(signed int a1, signed int a2, float a3, float a4, float a5, signed int a6)
{
	pSetBlend(1);
	glColor4f(0.0, 0.0, 0.0, 0.89999998);
	float v6 = (double)a6;
	float v7 = (double)(LODWORD(a5) - 8);
	float v8 = (double)(a2 + 2);
	float v9 = (double)(a1 + 3);
	pDrawBarForm(v9, v8, v7, v6, 0.0, 0);
	glColor4f(0.0, 0.0, 0.0, 0.60000002);
	float v10 = (double)(LODWORD(a4) - a6 - 7);
	float v11 = (double)(LODWORD(a3) - 7);
	float v12 = (double)(a2 + a6 + 2);
	float v13 = (double)(a1 + 3);
	pDrawBarForm(v13, v12, v11, v10, 0.0, 0);
	sub_637A30();
	float v14 = (double)a2;
	float v15 = (double)a1;
	pDrawGUI(31340, v15, v14, 14.0, 14.0);
	float v16 = (double)a2;
	float v17 = (double)(a1 + LODWORD(a5) - 14);
	pDrawGUI(31341, v17, v16, 14.0, 14.0);
	float v18 = (double)(a6 + a2);
	float v19 = (double)(a1 + LODWORD(a3) - 14);
	pDrawGUI(31341, v19, v18, 14.0, 14.0);
	float v20 = (double)(a2 + LODWORD(a4) - 14);
	float v21 = (double)a1;
	pDrawGUI(31342, v21, v20, 14.0, 14.0);
	float v22 = (double)(a2 + LODWORD(a4) - 14);
	float v23 = (double)(a1 + LODWORD(a3) - 14);
	pDrawGUI(31343, v23, v22, 14.0, 14.0);
	float v24 = (double)(LODWORD(a5) - 12);
	float v25 = (double)a2;
	float v26 = (double)(a1 + 6);
	pDrawGUI(31344, v26, v25, v24, 14.0);
	float v27 = (double)(a6 - 6);
	float v28 = (double)(a2 + 6);
	float v29 = (double)(a1 + LODWORD(a5) - 14);
	pDrawGUI(31347, v29, v28, 14.0, v27);
	float v30 = (double)(LODWORD(a3) - LODWORD(a5) - 6);
	float v31 = (double)(a6 + a2);
	float v32 = (double)(a1 + LODWORD(a5) - 5);
	pDrawGUI(31344, v32, v31, v30, 14.0);
	float v33 = (double)(LODWORD(a4) - a6 - 14);
	float v34 = (double)(a2 + a6 + 6);
	float v35 = (double)(a1 + LODWORD(a3) - 14);
	pDrawGUI(31347, v35, v34, 14.0, v33);
	float v36 = (double)(LODWORD(a3) - 12);
	float v37 = (double)(a2 + LODWORD(a4) - 14);
	float v38 = (double)(a1 + 6);
	pDrawGUI(31345, v38, v37, v36, 14.0);
	float v39 = (double)(LODWORD(a4) - 14);
	float v40 = (double)(a2 + 6);
	float v41 = (double)a1;
	pDrawGUI(31346, v41, v40, 14.0, v39);
}
// ----------------------------------------------------------------------------------------------

void NewParty::DrawPanelPartyMember(int a1, int a2)
{
	int p = a1;

	if (a1 >= 5)
	{
		a1 -= 5;
	}

	HGDIOBJ ho = *(HGDIOBJ*)0x00E8C588;

	float staticX = g_Party.PanelDX + 10;
	float staticY = g_Party.PanelDY + 71 * a1 + 40;

	float X = staticX;
	float Y = staticY;

	X = staticX;
	Y = staticY;

	this->PartyPanelBlock(X, Y, 170, 70, 70, 20);

	pSetFont(pTextThis(), int(ho));

	if (p)
	{
		pSetFont(pTextThis(), int(ho));
		pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
		Y = staticY + 8;
		X = staticX;
		pDrawText(pTextThis(), X, Y, g_Party.PartyData[p].Name, 70, 0, (int*)3, 0);
	}
	else
	{
		pSetFont(pTextThis(), int(ho));
		pSetTextColor(pTextThis(), 0, 0xFFu, 0, 0xFFu);
		Y = staticY + 8;
		pDrawText(pTextThis(), X, Y, g_Party.PartyData[p].Name, 70, 0, (int*)3, 0);
		Y = staticY + 23;
		X = staticX + 136;
		pDrawGUI(31553, X, Y, 10.0, 12.0);
	}

	pSetFont(pTextThis(), int(ho));
	sub_420080(pTextThis(), pMakeColor(-62, -62, -62, -1));

	Y = staticY + 26;
	X = staticX + 10;
	pDrawText(pTextThis(), X, Y, pGetMapName(g_Party.PartyData[p].MapNumber), 70, 0, (int*)1, 0);

	char Buffer[100];
	ZeroMemory(Buffer, sizeof(Buffer));
	sprintf(Buffer, "(%d,%d)", g_Party.PartyData[p].PosX, g_Party.PartyData[p].PosY);
	Y = staticY + 26;
	X = staticX + 85;
	pDrawText(pTextThis(), X, Y, Buffer, 60, 0, (int*)1, 0);

	Y = staticY + 39;
	X = staticX + 8;
	pDrawGUI(31551, X, Y, 151.0, 8.0);

	if (g_Party.PartyData[p].Life > g_Party.PartyData[p].MaxLife)
	{
		g_Party.PartyData[p].Life = g_Party.PartyData[p].MaxLife;
	}

	double v433 = (147 * g_Party.PartyData[p].Life) / g_Party.PartyData[p].MaxLife;
	Y = staticY + 41;
	X = staticX + 10;
	pDrawGUI(31552, X, Y, v433, 4.0);

	ZeroMemory(Buffer, sizeof(Buffer));
	sprintf(Buffer, "%d / %d", g_Party.PartyData[p].Life, g_Party.PartyData[p].MaxLife);
	Y = staticY + 51;
	X = staticX + 88;
	pDrawText(pTextThis(), X, Y, Buffer, 70, 0, (int*)4, 0);

	lpCharObj lpPlayer = gObjUser.lpPlayer;

	if (!strcmp(g_Party.PartyData[0].Name, lpPlayer->Name) || !strcmp(g_Party.PartyData[p].Name, lpPlayer->Name))
	{
		X = staticX + 140 + 9;
		Y = staticY + 24;

		float Whith = 12;
		float High = 12;

		float standartWhith = Whith / ((Whith * 2) / 1.5);
		float standartHight = High / ((High * 4) / 1.5);

		int DrawSwitch = 1;

		if (g_Party.OnClickD == this->PartyData[p].Unknown11 && g_Party.OnClickD != -1)
		{
			DrawSwitch = 2;
		}

		float CritY = (double)(DrawSwitch / 2) * High / ((High * 4) / 1.5);

		pDrawCircle(0x7B42, X, Y, Whith, High, 0.0, CritY, standartWhith, standartHight, 1, 1, 0.0);
	}

}
// ----------------------------------------------------------------------------------------------

void NewParty::DrawPanelD()
{
	for (int i = 0; i < g_Party.PartyMemberCount; i++)
	{
		if (i < 5 && g_Party.Page == 0)
		{
			g_Party.DrawPanelPartyMember(i, (int)((char *)&g_Party.PartyData[i]));
		}
		else if (i >= 5 && g_Party.Page == 1)
		{
			g_Party.DrawPanelPartyMember(i, (int)((char *)&g_Party.PartyData[i]));
		}
	}
}
// ----------------------------------------------------------------------------------------------

void NewParty::MouseControllerD(int Click)
{
	if (this->PartyMemberCount <= 0 || !gInterface.CheckWindow(3))
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->ClickTick);
	// ----
	int ClickMember = -1;
	int a1 = 0;

	lpCharObj lpPlayer = gObjUser.lpPlayer;

	for (int p = 0; p < this->PartyMemberCount; p++)
	{
		if (p < 5 && Page == 0)
		{
			a1 = p;
			if (!strcmp(this->PartyData[0].Name, lpPlayer->Name) || !strcmp(this->PartyData[p].Name, lpPlayer->Name))
			{
				float staticX = g_Party.PanelDX + 10;
				float staticY = g_Party.PanelDY + 71 * a1 + 40;

				float X = staticX + 140 + 9;
				float Y = staticY + 24;

				float MaxX = X + 12;
				float MaxY = Y + 12;

				if ((pCursorX < X || pCursorX > MaxX) ||
					(pCursorY < Y || pCursorY > MaxY))
				{
					continue;
				}
				// ----
				ClickMember = this->PartyData[p].Unknown11;
				break;
			}
		}
		else if (p >= 5 && Page == 1)
		{
			a1 = p - 5;

			if (!strcmp(this->PartyData[0].Name, lpPlayer->Name) || !strcmp(this->PartyData[p].Name, lpPlayer->Name))
			{
				float staticX = g_Party.PanelDX + 10;
				float staticY = g_Party.PanelDY + 71 * a1 + 40;

				float X = staticX + 140 + 9;
				float Y = staticY + 24;

				float MaxX = X + 12;
				float MaxY = Y + 12;

				if ((pCursorX < X || pCursorX > MaxX) ||
					(pCursorY < Y || pCursorY > MaxY))
				{
					continue;
				}
				// ----
				ClickMember = this->PartyData[p].Unknown11;
				break;
			}
		}
	}

	if (ClickMember == -1)
	{
		this->OnClickD = -1;
		return;
	}

	if (Click == WM_LBUTTONDOWN)
	{
		this->OnClickD = ClickMember;
		return;
	}
	// ----
	this->OnClickD = -1;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->ClickTick = GetTickCount();
	// ----
	PMSG_PARTYDELUSER pRequest;
	pRequest.h.set(0x43, sizeof(pRequest));
	pRequest.Number = (BYTE)ClickMember;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

void NewParty::MouseControllerPage(int Click)
{
	if (/*this->PartyMemberCount <= 5 ||*/ !gInterface.CheckWindow(3))
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->ClickTick);
	// ----

	int ClickPage = -1;

	float pX = g_Party.PanelDX - 10;
	float pY = g_Party.PanelDY + 123;

	if (gInterface.IsWorkZone(pX + 70, pY + 275, pX + 70 + 20, pY + 275 + 20))
	{
		ClickPage = 0;
	}
	else if (gInterface.IsWorkZone(pX + 133, pY + 275, pX + 133 + 20, pY + 275 + 20))
	{
		ClickPage = 1;
	}

	if (ClickPage == -1)
	{
		return;
	}

	if (Click == WM_LBUTTONDOWN)
	{
		return;
	}
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->ClickTick = GetTickCount();
	// ----
	this->Page = ClickPage;
}
// ----------------------------------------------------------------------------------------------

int NewParty::PartyMemberLifeRecv(LPBYTE aRecv)
{
	int datasize = 0;
	char v2;
	char v3;
	signed int v4;
	char v5;
	PMSG_DEFAULT_COUNT pCount;
	memcpy(&pCount, &aRecv[datasize], sizeof(pCount));
	datasize = 4;
	int result = pCount.Count;

	for (int i = 0; i < result; ++i)
	{
		PMSG_PARTYLIFEALL pList;
		memcpy(&pList, &aRecv[datasize], sizeof(pList));

		v5 = pList.Number & 0xF;
		if (v5 >= 0)
			v4 = v5;
		else
			v4 = 0;
		if (v4 <= 10)
		{
			if (v5 >= 0)
				v2 = pList.Number & 0xF;
			else
				v2 = 0;
			v3 = v2;
		}
		else
		{
			v3 = 10;
		}

		g_Party.PartyData[i].LifePercent = v3;
		++datasize;
	}
	return result;
}
// ----------------------------------------------------------------------------------------------

int NewParty::FilterPartyNumber(int a1, int a2, unsigned int a3)
{
	int result;
	int v4;
	int v5;
	char v6;
	char v7;
	char v8;
	char v9;
	int v10;
	int v11;
	unsigned int v12;

	char v13;
	char v14;
	char v15;
	char v16;
	char v17;

	v12 = 0;
	if (a3)
	{
		if (a3 < 9 || a3 == 9)
		{
			v4 = a2;
			v5 = a1;
			goto LABEL_24;
		}
		v4 = a2;
		v5 = a1;
		do
		{
			v13 = *(BYTE *)v5;
			//v5 += 4;
			//v4 += 4;
			v5 += 9;
			v4 += 9;
			//---
			int  mins = 9;
			if (!v13 || v13 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v14 = *(BYTE *)(v5 - mins - 1);
			// ---
			mins = 8;
			if (!v14 || v14 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v15 = *(BYTE *)(v5 - mins - 1);
			// ---
			mins = 7;
			if (!v15 || v15 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v16 = *(BYTE *)(v5 - mins - 1);
			// ---
			mins = 6;
			if (!v16 || v16 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v7 = *(BYTE *)(v5 - mins - 1);
			// ---
			mins = 5;
			if (!v13 || v13 != *(BYTE *)(v4 - mins))
			{
				v10 = *(BYTE *)(v5 - mins);
				v11 = *(BYTE *)(v4 - mins);
				goto LABEL_28;
			}
			v13 = *(BYTE *)(v5 - mins - 1);
			// ---
			if (!v6 || v6 != *(BYTE *)(v4 - 4))
			{
				v10 = *(BYTE *)(v5 - 4);
				v11 = *(BYTE *)(v4 - 4);
				goto LABEL_28;
			}
			v17 = *(BYTE *)(v5 - 3);
			if (!v17 || v17 != *(BYTE *)(v4 - 3))
			{
				v10 = *(BYTE *)(v5 - 3);
				v11 = *(BYTE *)(v4 - 3);
				goto LABEL_28;
			}
			v8 = *(BYTE *)(v5 - 2);
			if (!v8 || v8 != *(BYTE *)(v4 - 2))
			{
				v10 = *(BYTE *)(v5 - 2);
				v11 = *(BYTE *)(v4 - 2);
				goto LABEL_28;
			}
			v9 = *(BYTE *)(v5 - 1);
			if (!v9 || v9 != *(BYTE *)(v4 - 1))
			{
				v10 = *(BYTE *)(v5 - 1);
				v11 = *(BYTE *)(v4 - 1);
				goto LABEL_28;
			}
			v12 += 4;
		} while (v12 < a3 - 9);
		while (1)
		{
		LABEL_24:
			if (v12 >= a3)
				return 0;
			if (!*(BYTE *)v5 || *(BYTE *)v5 != *(BYTE *)v4)
				break;
			++v5;
			++v4;
			++v12;
		}
		v10 = *(BYTE *)v5;
		v11 = *(BYTE *)v4;
	LABEL_28:
		result = v10 - v11;
	}
	else
	{
		result = 0;
	}
	return result;
}
// ----------------------------------------------------------------------------------------------

#if(ADD_PARTY_LEADER==1)
void NewParty::MouseControllerLeader(int Click)
{
	if(gInterface.m_PartyLeader == 0)
	{
		return;
	}
	if (!g_Party.PartyShow)
	{
		return;
	}

	/*if(!g_Settings.ShowParty)
	{
		return;
	}*/

	if (this->PartyMemberCount <= 0)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->ClickTick);
	// ----
	int ClickMember = -1;
	int pmNumCkick = 0;

	lpCharObj lpPlayer = gObjUser.lpPlayer;

	for (int p = 1; p < this->PartyMemberCount; p++)
	{
		if (!strcmp(this->PartyData[0].Name, lpPlayer->Name) || !strcmp(this->PartyData[p].Name, lpPlayer->Name))
		{
			float X = this->CoordX(p) + 53;
			float Y = this->CoordY(p) + 3;

			float MaxX = X + 9;
			float MaxY = Y + 10;

			if ((pCursorX < X || pCursorX > MaxX) ||
				(pCursorY < Y || pCursorY > MaxY))
			{
				continue;
			}
			// ----


			// ----
			ClickMember = this->PartyData[p].Unknown11;
			pmNumCkick = p;
			break;
		}
	}

	if (ClickMember == -1)
	{
		this->pmID = -1;
		return;
	}

	if (Click == WM_LBUTTONDOWN)
	{
		this->pmID = pmNumCkick;
		return;
	}
	// ----
	this->pmID = -1;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->ClickTick = GetTickCount();
	// ----
	GC_PARTYNEWLEADER pRequest;

	pRequest.h.set(0xFF,0x15,sizeof(pRequest));

	//pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x42, sizeof(pRequest));
	pRequest.id = (BYTE)ClickMember;
	//DataSend((LPBYTE)&pRequest, pRequest.h.size);

	DataSend((BYTE*)&pRequest,pRequest.h.size);
	//g_Console.AddMessage(5,"SEND");
}
#endif

#if(PARTY_MOVE==1)
void NewParty::MouseControllerMove(int Click)
{
	if(gInterface.m_PartyTrace == 0)
	{
		return;
	}
	if (this->PartyMemberCount <= 0)
	{
		return;
	}

	if (!g_Party.PartyShow)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->ClickTick);
	// ----
	int ClickMember = -1;
	int pmNumCkick = 0;

	lpCharObj lpPlayer = gObjUser.lpPlayer;

	for (int p = 0; p < this->PartyMemberCount; p++)
	{
		if (strcmp(this->PartyData[p].Name, lpPlayer->Name))
		{
			float X = this->CoordX(p) + 33;
			float Y = this->CoordY(p) + 3;

			float MaxX = X + 9;
			float MaxY = Y + 10;

			if ((pCursorX < X || pCursorX > MaxX) ||
				(pCursorY < Y || pCursorY > MaxY))
			{
				continue;
			}		
			// ----
			ClickMember = this->PartyData[p].Unknown11;\
			pmNumCkick = p;
			break;
		}
	}

	if (ClickMember == -1)
	{
		this->pmID2 = -1;
		return;
	}

	if (Click == WM_LBUTTONDOWN)
	{
		this->pmID2 = pmNumCkick;
		return;
	}
	// ----
	this->pmID2 = -1;
	// ----
	if (Delay < 500)
	{
		return;
	}
	// ----
	this->ClickTick = GetTickCount();
	// ----
	GC_PARTYNEWLEADER pRequest;
	pRequest.h.set(0xFF,0x26,sizeof(pRequest));
	pRequest.id = (BYTE)ClickMember;
	DataSend((BYTE*)&pRequest,pRequest.h.size);
}
#endif

