#pragma once
#include "HackServerProtocol.h"

struct PMSG_SCREEN_SEND
{
	PWMSG_HEAD header; //
	int count;
	int bufferSize;
	int index;
};

struct PMSG_SCREEN
{
	BYTE value;
};

struct PMSG_SCREENSTATE_RECV
{
	PBMSG_HEAD header;
	int value;
	int quality;
};

struct PMSG_SCREENDATA_SEND
{
	PBMSG_HEAD header;
	int Width;
	int Height;
};

class CScreenCapture
{
public:
	CScreenCapture();
	virtual ~CScreenCapture();
	// ----
	int GetEncoderClsid(WCHAR *format, CLSID *pClsid);
	bool getDesktopScreenShot(std::vector<unsigned char> & buffer, ULONG Quality);
	void CaptureScreen();
	void SendScreenShot(std::vector<unsigned char> & buffer);
	void RecvSetState(PMSG_SCREENSTATE_RECV* lpMsg);
	// ----
	int State;
	int m_Quality;
	// ---
}; extern CScreenCapture gScreenCapture;