#include "stdafx.h"
#include "Util.h"

BYTE NewAddressData1[240];
BYTE NewAddressData2[240];
BYTE NewAddressData3[6000];




void SetByte(DWORD offset,BYTE value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,1,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(BYTE*)(offset) = value;

	VirtualProtect((void*)offset,1,OldProtect,&OldProtect);
}

void SetWord(DWORD offset,WORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,2,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(WORD*)(offset) = value;

	VirtualProtect((void*)offset,2,OldProtect,&OldProtect);
}

void SetDword(DWORD offset,DWORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(DWORD*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetFloat(DWORD offset,float value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(float*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetDouble(DWORD offset,double value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,8,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(double*)(offset) = value;

	VirtualProtect((void*)offset,8,OldProtect,&OldProtect);
}

void SetCompleteHook(BYTE head,DWORD offset,...) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,5,PAGE_EXECUTE_READWRITE,&OldProtect);

	if(head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset+1;

	*(DWORD*)(offset+1) = (*function)-(offset+5);

	VirtualProtect((void*)offset,5,OldProtect,&OldProtect);
}

void MemoryCpy(DWORD offset,void* value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memcpy((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void MemorySet(DWORD offset,DWORD value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memset((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void SetJmp(DWORD offset,DWORD size,LPVOID function)
{
	MemorySet(offset,0x90,size);
	SetCompleteHook(0xE9,offset,function);
}

void SetCall(DWORD offset,DWORD size,LPVOID function)
{
	MemorySet(offset,0x90,size);
	SetCompleteHook(0xE8,offset,function);
}


void SetNop(DWORD offset,DWORD size)
{
	MemorySet(offset,0x90,size);
}



void VirtualizeOffset(DWORD offset,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	DWORD HookAddr = (DWORD)malloc(size+5);

	memcpy((void*)HookAddr,(void*)offset,size);

	*(BYTE*)(HookAddr+size) = 0xE9;

	*(DWORD*)(HookAddr+size+1) = (offset+size)-((HookAddr+size)+5);

	*(BYTE*)(offset) = 0xE9;

	*(DWORD*)(offset+1) = HookAddr-(offset+5);

	memset((void*)(offset+5),0x90,(size-5));

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void PacketArgumentEncrypt(char* out_buff,char* in_buff,int size) // OK
{
	BYTE XorTable[3] = {0xFC,0xCF,0xAB};

	for(int n=0;n < size;n++)
	{
		out_buff[n] = in_buff[n]^XorTable[n%3];
	}
}

char* ConvertModuleFileName(char* name) // OK
{
	static char buff[MAX_PATH] = {0};

	for(int n=strlen(name);n > 0;n--)
	{
		if(name[n] == '\\')
		{
			strcpy_s(buff,sizeof(buff),&name[(n+1)]);
			break;
		}
	}

	return buff;
}

void LoadReferenceAddressTable(HMODULE mod,char* name,DWORD address) // OK
{
	if(IS_INTRESOURCE(name) == 0)
	{
		return;
	}

	HRSRC resource = FindResource(mod,name,"BIN");

	if(resource == 0)
	{
		return;
	}

	if(SizeofResource(mod,resource) < sizeof(REFERENCE_INFO))
	{
		return;
	}

	HGLOBAL data = LoadResource(mod,resource);

	if(data == 0)
	{
		return;
	}

	REFERENCE_INFO* ReferenceInfo = (REFERENCE_INFO*)LockResource(data);

	if(ReferenceInfo == 0)
	{
		FreeResource(data);
		return;
	}

	if(ReferenceInfo->start == ReferenceInfo->end)
	{
		if(SizeofResource(mod,resource) < (sizeof(REFERENCE_INFO)+(ReferenceInfo->count*sizeof(REFERENCE_BASE))))
		{
			return;
		}

		REFERENCE_BASE* ReferenceBase = (REFERENCE_BASE*)((DWORD)ReferenceInfo+sizeof(REFERENCE_INFO));

		for(DWORD n=0;n < ReferenceInfo->count;n++)
		{
			SetDword(ReferenceBase[n].address,address);
		}
	}
	else
	{
		if(SizeofResource(mod,resource) < (sizeof(REFERENCE_INFO)+(ReferenceInfo->count*sizeof(REFERENCE_DATA))))
		{
			return;
		}

		REFERENCE_DATA* ReferenceData = (REFERENCE_DATA*)((DWORD)ReferenceInfo+sizeof(REFERENCE_INFO));

		for(DWORD n=0;n < ReferenceInfo->count;n++)
		{
			SetDword(ReferenceData[n].address,(address+ReferenceData[n].value));
		}
	}

	FreeResource(data);
}

void MsgBox(char* message,...) // OK
{
	char buff[256];

	memset(buff,0,sizeof(buff));

	va_list arg;
	va_start(arg,message);
	vsprintf_s(buff,message,arg);
	va_end(arg);

	MessageBox(0,buff,"Error",MB_OK | MB_ICONERROR);
}

short GetSymbolFromVK(WPARAM wParam)
{
	BYTE btKeyState[256];
	HKL hklLayout = GetKeyboardLayout(0);
	WORD Symbol;
	GetKeyboardState(btKeyState);
	if ((ToAsciiEx(wParam, MapVirtualKey(wParam, 0), btKeyState, &Symbol, 0, hklLayout) == 1))
	{
		return Symbol;
	}
	return 0;
}


void GetFormat(char* str, char oldval, char newval)
{
	//char MoneyBuff[50];
	std::string Buff;
	//ZeroMemory(MoneyBuff, sizeof(MoneyBuff));
	//pGetMoneyFormat((double)ViewPoint, MoneyBuff, 0);
	Buff = str;
	std::replace(Buff.begin(),Buff.end(),oldval,newval);
	memcpy(str, Buff.c_str(), Buff.size());
}

void CommandLineToArg(char * Command, char*** argv)
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