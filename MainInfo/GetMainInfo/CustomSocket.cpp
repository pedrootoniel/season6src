#include "stdafx.h"
#include "CustomSocket.h"
#include "MemScript.h"

CCustomSocket gCustomSocket;

CCustomSocket::CCustomSocket() //ok
{
	this->Init();
}
CCustomSocket::~CCustomSocket() //ok
{

}
void CCustomSocket::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_SOCKET;n++)
	{
		this->m_CustomSocketInfo[n].Index = -1;
	}
}
void CCustomSocket::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			CUSTOM_SOCKET_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomItemIndexCount = 0;

			info.Index = CustomItemIndexCount++;

			info.SocketType = lpMemScript->GetNumber();

			info.SocketIndex = lpMemScript->GetAsNumber();

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomSocket::SetInfo(CUSTOM_SOCKET_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_SOCKET)
	{
		return;
	}

	this->m_CustomSocketInfo[info.Index] = info;
}