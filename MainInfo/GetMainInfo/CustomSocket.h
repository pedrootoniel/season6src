
#pragma once

#define MAX_CUSTOM_SOCKET 100

struct CUSTOM_SOCKET_INFO
{
	int Index;
	short SocketType;
	short SocketIndex;
};
class CCustomSocket
{
public:
	CCustomSocket();
	virtual ~CCustomSocket();
	void Init();
	void Load(char* path);
	void SetInfo(CUSTOM_SOCKET_INFO info);
public:
	CUSTOM_SOCKET_INFO m_CustomSocketInfo[MAX_CUSTOM_SOCKET];
};
extern CCustomSocket gCustomSocket;