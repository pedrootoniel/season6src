#include "stdafx.h"
#include "TMemory.h"
//---------------------------------------------------------------------------
TMemory gTMemory;

TMemory::TMemory() //ok
{

}

TMemory::~TMemory() //ok
{

}

void TMemory::CommandLineToArg(char * Command, char*** argv)
{
	if (!Command) { return; }

	bool	Quote			=	false;
	bool	Content			=	false;
	size_t	CommandLen		=	strlen(Command);
	int		NumCommands		=	1;
	size_t	I				=	0;

	for (I=0; I < CommandLen; I++)
	{
		if (Command[I] == '"')
		{
			Quote			=	!Quote;
			Content			=	true;
		}
		else if (Command[I] == ' ')
		{
			if (!Quote&&Content)
			{
				Content		=	false;

				NumCommands++;
			}
		}
		else
		{
			Content			=	true;
		}
	}

	*argv = new char*[NumCommands];

	size_t StrBegin		=	0;
	size_t StrLen		=	0;
	size_t CommandNum	=	0;

	for (I=0; I < CommandLen; I++)
	{
		if (Command[I] == '"')
		{
			Quote = !Quote;
			Content			=	true;
		}
		else if (Command[I] == ' ')
		{
			if ( !Quote && Content)
			{
				Content		=	false;

				StrLen = I - StrBegin;
				if (Command[StrBegin] == '"')
				{
					StrBegin++;
					StrLen--;
				}
				if (Command[StrBegin+StrLen-1] == '"')
				{
					StrLen-=1;
				}
				char* Argument = 0;
				Argument = new char[StrLen+1];
				memcpy(Argument,Command + StrBegin,StrLen);
				memset(Argument+StrLen,0,1);

				(*argv)[CommandNum] = Argument;		

				CommandNum++;
				StrBegin = I+1;
			}
			else if ( !Quote )
			{
				StrBegin++;
			}
		}
		else
		{
			Content			=	true;
		}
	}
	StrLen = I - StrBegin;
	if (Command[StrBegin] == '"')
	{
		StrBegin++;
		StrLen--;
	}
	if (Command[StrBegin+StrLen-1] == '"')
	{
		StrLen-=1;
	}
	char* Argument = 0;
	Argument = new char[StrLen+1];
	memcpy(Argument,Command + StrBegin,StrLen);
	memset(Argument+StrLen,0,1);

	(*argv)[CommandNum] = Argument;
}
//---------------------------------------------------------------------------

DWORD TMemory::WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
    DWORD dwErrorCode   = 0;
    DWORD dwOldProtect  = 0;
	// ----
    int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);
	// ----
    if( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
	// ----
    memcpy(lpAddress, lpBuf, uSize);
	// ----
    DWORD dwBytes   = 0;
	// ----
    iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);
	// ----
    if ( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
	// ----
    return 0x00;
}
//---------------------------------------------------------------------------

void TMemory::SetNop(DWORD dwSrcOffset, int Size)
{
	for (int i = 0; i < Size; i++) 
		*(BYTE*)(dwSrcOffset + i) = 0x90;
};
//---------------------------------------------------------------------------
DWORD TMemory::ReadMemory(const LPVOID lpAddress, LPVOID lpBuf, const UINT uSize)
{
    DWORD dwErrorCode   = 0;
    DWORD dwOldProtect  = 0;
	// ----
    int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);
	// ----
    if ( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
	// ----
    memcpy(lpBuf, lpAddress, uSize);
	// ----
    DWORD dwBytes   = 0;
	// ----
    iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);
	// ----
    if ( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
	// ----
    return 0x00;
}
//---------------------------------------------------------------------------

DWORD TMemory::SetByte(const LPVOID dwOffset, const BYTE btValue)
{
	return WriteMemory(dwOffset, (LPVOID) & btValue, sizeof(BYTE));
}

void TMemory::SetByteU(DWORD dwOffset, BYTE btValue)
{
	*(BYTE*) (dwOffset) = btValue;
};
//---------------------------------------------------------------------------

DWORD TMemory::GetByte(const LPVOID dwOffset, BYTE & btValue)
{
	return ReadMemory(dwOffset, (LPVOID) btValue, sizeof(BYTE));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetWord(const LPVOID dwOffset, const WORD wValue)
{
	return WriteMemory(dwOffset, (LPVOID) & wValue, sizeof(WORD));
}
//---------------------------------------------------------------------------

DWORD TMemory::GetWord(const LPVOID dwOffset, WORD & wValue)
{
	return ReadMemory(dwOffset, (LPVOID) wValue, sizeof(WORD));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetDword(const LPVOID dwOffset, const DWORD dwValue)
{
	return WriteMemory(dwOffset, (LPVOID) & dwValue, sizeof(DWORD));
}
//---------------------------------------------------------------------------

DWORD TMemory::GetDword(const LPVOID dwOffset, DWORD & dwValue)
{
	return ReadMemory(dwOffset, (LPVOID) dwValue, sizeof(DWORD));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetFloat(const LPVOID dwOffset, float fValue)
{
	return WriteMemory(dwOffset, & fValue, sizeof(float));
}
//---------------------------------------------------------------------------

DWORD TMemory::GetFloat(const LPVOID dwOffset, float & fValue)
{
	return ReadMemory(dwOffset, & fValue, sizeof(float));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetDouble(const LPVOID dwOffset, double dValue)
{
	return WriteMemory(dwOffset, & dValue, sizeof(double));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[5];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ----
	btBuf[0]	= 0xE9;
	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
	// ----
	btBuf[0]	= 0x0F;
	btBuf[1]	= 0x8F;
	memcpy( (LPVOID) & btBuf[2], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;
	// ----
	btBuf[0]	= 0x0F;
	btBuf[1]	= 0x87;
	memcpy( (LPVOID) & btBuf[2], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
	// ----
	btBuf[0]		= cmd;
	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

DWORD TMemory::SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue)
{
	BYTE * lpBuf	= new BYTE[wCount];
	// ----
	memset(lpBuf, btValue, wCount);
	// ----
	return WriteMemory( dwAddress, (LPVOID) lpBuf, wCount);
}
//---------------------------------------------------------------------------

DWORD TMemory::SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd)
{
	BYTE btBuf[5];
	// ----
	DWORD dwShift	= (ULONG_PTR)dwMyFuncOffset - ( (ULONG_PTR)dwJmpOffset + 5 );
	// ----
	btBuf[0] = cmd;
	// ----
	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwJmpOffset, (LPVOID) btBuf, sizeof(btBuf));
}
//---------------------------------------------------------------------------

void TMemory::HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset)
{
	*(DWORD*)(dwJmpOffset+1) = dwMyFuncOffset-(dwJmpOffset+5);
}
//---------------------------------------------------------------------------

bool TMemory::FileExists(char * name)
{
	if (CreateFile(name, 0, 0, 0, OPEN_EXISTING, 0, 0) == INVALID_HANDLE_VALUE)
		return false;
	return true;
};

void TMemory::HookOffset(DWORD my, DWORD tohook, BYTE type)
{
	*(BYTE*)tohook = type;
	*(DWORD*)(tohook + 1) = my - (tohook + 5);
};

void TMemory::Protect(const LPVOID dwSrcOffset, int Size, DWORD dwNewProtect)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, dwNewProtect, &OldProtect);
}

DWORD TMemory::UnProtect(const LPVOID dwSrcOffset, int Size)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, PAGE_EXECUTE_READWRITE, &OldProtect);
	return OldProtect;
}

void TMemory::Access(DWORD dwOffset, int t_size)
{
	DWORD OldProtect;
	VirtualProtect((LPVOID)dwOffset, t_size, PAGE_EXECUTE_READWRITE, &OldProtect);
}

void TMemory::HookAddress(DWORD dwAddrOffst, DWORD dwNewOffst, BYTE new_Cmd)
{
	Access(dwAddrOffst, 5);

	if (new_Cmd)
		memset((void*)dwAddrOffst, new_Cmd, 1);

	*(DWORD*)(dwAddrOffst + 1) = dwNewOffst - (dwAddrOffst + 5);
}