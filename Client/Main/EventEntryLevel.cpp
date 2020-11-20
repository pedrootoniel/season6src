#include "StdAfx.h"
#include "EventEntryLevel.h"

#include "Util.h"

void LoadBCEntryLevel()
{
	char szTemp[128];

	FILE * hFile = fopen("Data\\Custom\\EventEntry.txt", "r"); // check if file exists

	if (hFile == NULL)
	{
		MsgBox("EventEntry.txt not found!");
	}

	fclose(hFile);

	for (int i = 0; i < 7; i++)
	{
		sprintf(szTemp, "BC%dLevelMin_Normal", i + 1);
		g_BloodCastleEnterLevel_Normal[i][0] = GetPrivateProfileInt("BloodCastle", szTemp, 0, "Data\\Custom\\EventEntry.txt");

		sprintf(szTemp, "BC%dLevelMax_Normal", i + 1);
		g_BloodCastleEnterLevel_Normal[i][1] = GetPrivateProfileInt("BloodCastle", szTemp, 0, "Data\\Custom\\EventEntry.txt");

		sprintf(szTemp, "BC%dLevelMin_MGDLRF", i + 1);
		g_BloodCastleEnterLevel_Magumsa[i][0] = GetPrivateProfileInt("BloodCastle", szTemp, 0, "Data\\Custom\\EventEntry.txt");

		sprintf(szTemp, "BC%dLevelMax_MGDLRF", i + 1);
		g_BloodCastleEnterLevel_Magumsa[i][1] = GetPrivateProfileInt("BloodCastle", szTemp, 0, "Data\\Custom\\EventEntry.txt");
	}

	//HookManager.MakeJmpHook(0x009F45E3, HookBCLevel);
	ModifyBCLevel();
}

void ModifyBCLevel()
{
	//
	/*DWORD OldProtect;
	VirtualProtect((LPVOID)(0x005D45C2), 204, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(DWORD*)(0x005D45BF + 3) = 0x3D;
	*(DWORD*)(0x005D45D1 + 3) = 0x3E;
	*(DWORD*)(0x005D4676 + 3) = 0x51;
	*(DWORD*)(0x005D4688 + 3) = 0x52;*/
	DWORD OldProtect;
	VirtualProtect((LPVOID)(0x008740FB), 381, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(DWORD*)(0x008740F5 + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[0][0];
	*(DWORD*)(0x00874102 + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[0][1];
	*(DWORD*)(0x0087410F + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[1][0];
	*(DWORD*)(0x0087411C + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[1][1];
	*(DWORD*)(0x00874129 + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[2][0];
	*(DWORD*)(0x00874136 + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[2][1];
	*(DWORD*)(0x00874143 + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[3][0];
	*(DWORD*)(0x00874150 + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[3][1];
	*(DWORD*)(0x0087415D + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[4][0];
	*(DWORD*)(0x0087416A + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[4][1];
	*(DWORD*)(0x00874177 + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[5][0];
	*(DWORD*)(0x00874184 + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[5][1];
	*(DWORD*)(0x00874191 + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[6][0];
	*(DWORD*)(0x0087419E + 6) = (DWORD)g_BloodCastleEnterLevel_Normal[6][1];



	*(DWORD*)(0x008741C5 + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[0][0];
	*(DWORD*)(0x008741D2 + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[0][1];
	*(DWORD*)(0x008741DF + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[1][0];
	*(DWORD*)(0x008741EC + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[1][1];
	*(DWORD*)(0x008741F9 + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[2][0];
	*(DWORD*)(0x00874206 + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[2][1];
	*(DWORD*)(0x00874213 + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[3][0];
	*(DWORD*)(0x00874220 + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[3][1];
	*(DWORD*)(0x0087422D + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[4][0];
	*(DWORD*)(0x0087423A + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[4][1];
	*(DWORD*)(0x00874247 + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[5][0];
	*(DWORD*)(0x00874254 + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[5][1];
	*(DWORD*)(0x00874261 + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[6][0];
	*(DWORD*)(0x0087426E + 6) = (DWORD)g_BloodCastleEnterLevel_Magumsa[6][1];
}

void LoadDSEntryLevel()
{
	char szTemp[128];

	FILE * hFile = fopen("Data\\Custom\\EventEntry.txt", "r"); // check if file exists

	if (hFile == NULL)
	{
		MsgBox("EventEntry.txt not found!");
	}

	fclose(hFile);

	for (int i = 0; i < 6; i++)
	{
		sprintf(szTemp, "DS%dLevelMin_Normal", i + 1);
		g_DevilSquareEnterLevel_Normal[i][0] = GetPrivateProfileInt("DevilSquare", szTemp, 0, "Data\\Custom\\EventEntry.txt");
		////console.Log("", "DS %d", g_DevilSquareEnterLevel_Normal[i][0]);
		sprintf(szTemp, "DS%dLevelMax_Normal", i + 1);
		g_DevilSquareEnterLevel_Normal[i][1] = GetPrivateProfileInt("DevilSquare", szTemp, 0, "Data\\Custom\\EventEntry.txt");

		sprintf(szTemp, "DS%dLevelMin_MGDLRF", i + 1);
		g_DevilSquareEnterLevel_Magumsa[i][0] = GetPrivateProfileInt("DevilSquare", szTemp, 0, "Data\\Custom\\EventEntry.txt");

		sprintf(szTemp, "DS%dLevelMax_MGDLRF", i + 1);
		g_DevilSquareEnterLevel_Magumsa[i][1] = GetPrivateProfileInt("DevilSquare", szTemp, 0, "Data\\Custom\\EventEntry.txt");
	}

	ModifyDSLevel();
}

void ModifyDSLevel()
{
	DWORD OldProtect;
	VirtualProtect((LPVOID)(0x00877C0B), 319, PAGE_EXECUTE_READWRITE, &OldProtect);

	*(DWORD*)(0x00877C05 + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[0][0];
	*(DWORD*)(0x00877C12 + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[0][1];
	*(DWORD*)(0x00877C1F + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[1][0];
	*(DWORD*)(0x00877C2C + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[1][1];
	*(DWORD*)(0x00877C39 + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[2][0];
	*(DWORD*)(0x00877C46 + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[2][1];
	*(DWORD*)(0x00877C53 + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[3][0];
	*(DWORD*)(0x00877C60 + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[3][1];
	*(DWORD*)(0x00877C6D + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[4][0];
	*(DWORD*)(0x00877C7A + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[4][1];
	*(DWORD*)(0x00877C87 + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[5][0];
	*(DWORD*)(0x00877C94 + 6) = (DWORD)g_DevilSquareEnterLevel_Normal[5][1];



	*(DWORD*)(0x00877CBB + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[0][0];
	*(DWORD*)(0x00877CC8 + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[0][1];
	*(DWORD*)(0x00877CD5 + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[1][0];
	*(DWORD*)(0x00877CE2 + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[1][1];
	*(DWORD*)(0x00877CEF + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[2][0];
	*(DWORD*)(0x00877CFC + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[2][1];
	*(DWORD*)(0x00877D09 + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[3][0];
	*(DWORD*)(0x00877D16 + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[3][1];
	*(DWORD*)(0x00877D23 + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[4][0];
	*(DWORD*)(0x00877D30 + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[4][1];
	*(DWORD*)(0x00877D3D + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[5][0];
	*(DWORD*)(0x00877D4A + 6) = (DWORD)g_DevilSquareEnterLevel_Magumsa[5][1];
}