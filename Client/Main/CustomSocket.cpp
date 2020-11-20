#include "stdafx.h"
#include "CustomSocket.h"

CCustomSocket gCustomSocket;

CCustomSocket::CCustomSocket()
{
	this->Init();
}
CCustomSocket::~CCustomSocket()
{

}
void CCustomSocket::Init()
{
	for(int n=0;n < MAX_CUSTOM_SOCKET;n++)
	{
		this->m_CustomSocketInfo[n].Index = -1;
	}
}
void CCustomSocket::Load(CUSTOM_SOCKET_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_SOCKET;n++)
	{
		this->SetInfo(info[n]);
	}
}
void CCustomSocket::SetInfo(CUSTOM_SOCKET_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_SOCKET)
	{
		return;
	}

	this->m_CustomSocketInfo[info.Index] = info;
}
CUSTOM_SOCKET_INFO* CCustomSocket::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_SOCKET)
	{
		return 0;
	}

	if(this->m_CustomSocketInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomSocketInfo[index];
}
CUSTOM_SOCKET_INFO* CCustomSocket::GetInfoByType(short SocketType)
{
	for(int n=0;n < MAX_CUSTOM_SOCKET;n++)
	{
		CUSTOM_SOCKET_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->SocketType == SocketType)
		{
			return lpInfo;
		}
	}

	return 0;
}
BOOL CCustomSocket::GetCustomSocketInfo(short SocketType,short SocketIndex)
{
	CUSTOM_SOCKET_INFO* lpInfo = this->GetInfoByType(SocketType);
	if(lpInfo == 0)
	{
		return 0;
	}

	SocketIndex = (short)(lpInfo->SocketIndex);
	return 1;
}