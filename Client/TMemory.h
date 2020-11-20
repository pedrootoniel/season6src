#pragma once
// ----------------------------------------------------------------------------------------------

#include <windows.h>

#define MEMORY4(value) *(unsigned int*)(value)
#define MEMORY2(value) *(unsigned short*)(value)
#define MEMORY1(value) *(unsigned char*)(value)

class TMemory
{
// ----------------------------------------------------------------------------------------------
public:
	TMemory();
	virtual ~TMemory();
bool FileExists(char * name);
void CommandLineToArg(char* Command, char*** argv);
DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
DWORD ReadMemory(const LPVOID lpAddress, LPVOID lpBuf, const UINT uSize);
DWORD SetByte(const LPVOID dwOffset, const BYTE btValue);
DWORD GetByte(const LPVOID dwOffset, BYTE & btValue);
DWORD SetWord(const LPVOID dwOffset, const WORD wValue);
DWORD GetWord(const LPVOID dwOffset, WORD & wValue);
DWORD SetDword(const LPVOID dwOffset, const DWORD dwValue);
DWORD GetDword(const LPVOID dwOffset, DWORD & dwValue);
DWORD SetFloat(const LPVOID dwOffset, const float fValue);
DWORD GetFloat(const LPVOID dwOffset, float & fValue);
DWORD SetDouble(const LPVOID dwOffset, double dValue);
DWORD SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
DWORD SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, BYTE cmd);
void SetNop(DWORD dwSrcOffset, int Size);
DWORD SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
DWORD SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue);
DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd);
void SetByteU(DWORD dwOffset, BYTE btValue);
// ----------------------------------------------------------------------------------------------
void HookOffset(DWORD my, DWORD tohook, BYTE type);
void HookThis(DWORD dwMyFuncOffset,DWORD dwJmpOffset);
void Protect(const LPVOID dwSrcOffset, int Size, DWORD dwNewProtect);
DWORD UnProtect(const LPVOID dwSrcOffset, int Size);

//
void Access(DWORD dwOffset, int t_size);
void HookAddress(DWORD dwAddrOffst, DWORD dwNewOffst, BYTE new_Cmd);
//
}; extern TMemory gTMemory;
