#pragma once

struct REFERENCE_INFO
{
	DWORD count;
	DWORD start;
	DWORD end;
};

struct REFERENCE_BASE
{
	DWORD address;
};

struct REFERENCE_DATA
{
	DWORD address;
	DWORD value;
};


void SetByte(DWORD offset,BYTE value);
void SetWord(DWORD offset,WORD value);
void SetDword(DWORD offset,DWORD value);
void SetFloat(DWORD offset,float value);
void SetDouble(DWORD offset,double value);
void SetCompleteHook(BYTE head,DWORD offset,...);
void MemoryCpy(DWORD offset,void* value,DWORD size);
void MemorySet(DWORD offset,DWORD value,DWORD size);
void VirtualizeOffset(DWORD offset,DWORD size);
void PacketArgumentEncrypt(char* out_buff,char* in_buff,int size);
char* ConvertModuleFileName(char* name);
void LoadReferenceAddressTable(HMODULE mod,char* name,DWORD address);
void SetJmp(DWORD offset,DWORD size,LPVOID function);
void SetCall(DWORD offset,DWORD size,LPVOID function);
void SetNop(DWORD offset,DWORD size);

void MsgBox(char* message,...);
void GetFormat(char* str, char oldval, char newval);
short GetSymbolFromVK(WPARAM wParam);
void CommandLineToArg(char * Command, char*** argv);
extern DWORD FrameValue;
extern DWORD MainTickCount;
extern BYTE NewAddressData1[240];
extern BYTE NewAddressData2[240];
extern BYTE NewAddressData3[6000];
