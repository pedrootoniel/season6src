#include "StdAfx.h"
#include "Console.h"
#include <stdio.h>
#include "tchar.h"
#include "Monster.h"
#include "Offset.h"
//#include "Util.h"
#pragma warning (disable : 4482 4996)

Console1 g_Console;

Console1::Console1()
{
	
}
 
Console1::~Console1()
{
}

void Console1::Load()
{
	/*
	DWORD size=1024;
	char buf[1024];
	GetComputerName(buf, &size);
	//MsgBox(buf);
	
	//DESKTOP-9POA6CH
	if (!strcmp(buf,"mrHOANG"))
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)this->SetSettings, 0, 0, &this->PiD);
	}*/
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)this->SetSettings, 0, 0, &this->PiD);
}


#include "Other.h"

void Console1::SetComands(char * szBuffer)
{
	if (this->CommandsStatus(szBuffer, "/test", 5))
	{	
		this->AddMessage(5,"Focus");
		BringWindowToTop(*(HWND*)(MAIN_WINDOW));
		SetFocus(*(HWND*)(MAIN_WINDOW));
	}
}

void Console1::SetSettings(PVOID lpVOID)
{
	char szBuffer[2048] = { 0 };

	AllocConsole();

	while (true)
	{
		Sleep(100);

		g_Console.WriteMessage(szBuffer);

		g_Console.SetComands(szBuffer);
	}
}

bool Console1::CommandsStatus(char * szBuffer, char * szCmdName, int Size)
{
	bool bResult	= false;

	if (!strncmp(szBuffer, szCmdName, Size))
	{
		bResult		= true;
	}

	return bResult;
}

void Console1::AddMessage(int Color, const char * Format, ...)
{
	SYSTEMTIME Time;

	GetLocalTime(&Time);

	char szMessage[2048]	= { 0 };

	char szBuffer[2048]		= { 0 };

	DWORD dwBytes			= 0;

	char szTime[11]			= { 0 };

	HANDLE g_Handle			= GetStdHandle(STD_OUTPUT_HANDLE);

	va_list pArguments;

	va_start(pArguments, Format);

	vsprintf_s(szMessage, Format, pArguments);

	va_end(pArguments);

	sprintf_s(szTime, "[%02d:%02d:%02d]", Time.wHour, Time.wMinute, Time.wSecond);

	sprintf_s(szBuffer, "%s %s\n", szTime, szMessage);

	switch (Color)
	{
		case CNSL_E::CONSOLE_RED:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		}break;

		case CNSL_E::CONSOLE_GREEN:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}break;

		case CNSL_E::CONSOLE_BLUE:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}break;

		case CNSL_E::CONSOLE_CYAN:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}break;

		case CNSL_E::CONSOLE_YELLOW:
		{
			SetConsoleTextAttribute(this->g_Handle(FALSE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}break;

		default: break;
	}

	WriteFile(g_Handle, szBuffer, strlen(szBuffer), &dwBytes, NULL);

	//this->WriteInFile(szMessage);
}

bool Console1::WriteInFile(LPCTSTR szBuffer)
{
	bool bResult				= true;

	SYSTEMTIME Time;

	GetLocalTime(&Time);

	FILE * loc_FileStream		= NULL;

	DWORD dwWrite;

	char szServerName[1000]		= { "Console" };

	char szBuff[100]			= { 0 };

	char szMessageNewLine[500]	= { 0 };

	char szTime[11]				= { 0 };

	WORD wDay					= Time.wDay;

	sprintf_s(szTime, "[%02d:%02d:%02d]", Time.wHour, Time.wMinute, Time.wSecond);

	sprintf_s(szBuff, "./%s_%02d-%02d-%02d.log", &szServerName, wDay, Time.wMonth, Time.wYear);

	fopen_s(&loc_FileStream, szBuff, "a+");

	if (wDay != Time.wDay)
	{
		sprintf_s(szBuff, "./%s_%02d-%02d-%02d.log", &szServerName, Time.wDay, Time.wMonth, Time.wYear);
	}

	if (loc_FileStream != NULL)
	{
		fclose(loc_FileStream);
	}

	HANDLE szHandle = CreateFile(szBuff, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	if (szHandle == INVALID_HANDLE_VALUE)
	{
		bResult = false;
	}

	SetFilePointer(szHandle, 0, 0, FILE_END);

	sprintf_s(szMessageNewLine, "%s%s\r\n", szTime, szBuffer);

	WriteFile(szHandle, szMessageNewLine, _tcslen(szMessageNewLine) * sizeof(TCHAR), &dwWrite, NULL);

	CloseHandle(szHandle);

	return bResult;
}

int Console1::WriteMessage(char * szBuffer)
{
	char szBuff[2048] = { 0 };

	DWORD dwBytes;

	memset(szBuff, 0x00, 2048);

	memset(szBuffer, 0x00, 2048);

	ReadFile(g_Handle(TRUE), szBuff, 2048, &dwBytes, NULL);

	strncpy(szBuffer, szBuff, strlen(szBuff) - 2);

	return dwBytes;
}

HANDLE Console1::g_Handle(BOOL bImput)
{
	if (bImput)
	{
		return GetStdHandle(STD_INPUT_HANDLE);
	}
	else
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
}
