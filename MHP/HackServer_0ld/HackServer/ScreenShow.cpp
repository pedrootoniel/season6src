#include "stdafx.h"
#include "ScreenShow.h"
#include "Util.h"
#include <fstream>
#include "SocketManager.h"
#include "Resource.h"

CScreenShow gScreenShow;

CScreenShow::CScreenShow()
{
	this->Init();
	HANDLE hThread = CreateThread(NULL,NULL,LPTHREAD_START_ROUTINE(gScreenShow.DrawScreen),NULL,0,0);
	SetThreadPriority(hThread,THREAD_PRIORITY_HIGHEST);
	this->WindowOpen = false;
	this->ScreenWnd = NULL;
	this->buffer.clear();
	this->workbuffer.clear();
	this->isNeedReDraw = false;
	this->WorkIndex = -1;
	this->FPS = 0;
	this->RealFPS = 0;
	this->Tick = GetTickCount();
	this->ScreenQuality = 100;
	this->ScreenDiff = 0;
}

CScreenShow::~CScreenShow()
{
	
}

void CScreenShow::Init()
{
	this->buffer.clear();
	this->TotalAdded = 0;
}

void CScreenShow::RecvInfo(PMSG_SCREEN_RECV* lpMsg, int aIndex)
{
	if (this->WorkIndex != aIndex)
	{
		return;
	}

	static int lastindex = 0;

	//if (lpMsg->index != lastindex)
	//{
	//	//LogAdd(LOG_RED,"LastIndex != CurrentIndex [%d] [%d]",lastindex, lpMsg->index);
	//}
	//else
	//{
	//	//LogAdd(LOG_RED,"[Good] LastIndex == CurrentIndex [%d] [%d]",lastindex, lpMsg->index);
	//}

	if (lpMsg->index == 0)
	{
		lastindex=0;
		this->Init();
	}

	//LogAdd(LOG_RED,"Index = %d",lpMsg->index);

	lastindex++;

	//LogAdd(LOG_RED,"Count = %d",lpMsg->count);

	for(int n=0;n < lpMsg->count;n++)
	{
		PMSG_SCREEN* lpInfo = (PMSG_SCREEN*)(((BYTE*)lpMsg)+sizeof(PMSG_SCREEN_RECV)+(sizeof(PMSG_SCREEN)*n));
		this->buffer.push_back(lpInfo->value);
		this->TotalAdded++;

		if (this->buffer.size() == lpMsg->bufferSize)
		{
			this->workbuffer.clear();
			this->workbuffer = this->buffer;

			this->isNeedReDraw = true;

			if (GetTickCount() - this->Tick < 1000)
			{
				this->FPS++;
			}
			else
			{
				this->Tick = GetTickCount();
				this->RealFPS = FPS;
				this->FPS = 0;

				if (RealFPS<20)
				{
					if (this->ScreenQuality>30)
					{
						this->ScreenQuality-=10;
						this->SendScreenState(this->WorkIndex,1);
					}
					
				}
				else if (RealFPS > 20)
				{
					if (this->ScreenQuality < 100)
					{
						this->ScreenQuality+=10;
						this->SendScreenState(this->WorkIndex,1);
					}
				}
			}
		}
		else if (this->buffer.size() >= lpMsg->bufferSize)
		{
			LogAdd(LOG_GREEN,"ERROR! Buffer length bigger then expected size!");
		}
	}
}

bool load_img(std::vector<unsigned char> & buf, Bitmap *image)
{
    UINT len = buf.size();
    HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, len);
    BYTE *pmem = (BYTE*)GlobalLock(hMem);
    memcpy(pmem, &buf[0], len);
    IStream    *stream = NULL;
    CreateStreamOnHGlobal(hMem, FALSE, &stream);
    //image.FromStream(stream);
	//image = new Bitmap(stream);
    stream->Release();
    GlobalUnlock(hMem);
    GlobalFree(hMem);
    return true;
}  

int GetEncoderClsid(WCHAR *format, CLSID *pClsid) {
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

IStream* CreateStreamOnResource(LPCTSTR lpName, LPCTSTR lpType)
{
    IStream * ipStream = NULL;

    HRSRC hrsrc = FindResource(NULL, lpName, lpType);
    if (hrsrc == NULL)
        goto Return;

    DWORD dwResourceSize = SizeofResource(NULL, hrsrc);
    HGLOBAL hglbImage = LoadResource(NULL, hrsrc);
    if (hglbImage == NULL)
        goto Return;

    LPVOID pvSourceResourceData = LockResource(hglbImage);
    if (pvSourceResourceData == NULL)
        goto Return;

    HGLOBAL hgblResourceData = GlobalAlloc(GMEM_MOVEABLE, dwResourceSize);
    if (hgblResourceData == NULL)
        goto Return;

    LPVOID pvResourceData = GlobalLock(hgblResourceData);

    if (pvResourceData == NULL)
        goto FreeData;

    CopyMemory(pvResourceData, pvSourceResourceData, dwResourceSize);

    GlobalUnlock(hgblResourceData);

    if (SUCCEEDED(CreateStreamOnHGlobal(hgblResourceData, TRUE, &ipStream)))
        goto Return;

FreeData:
    GlobalFree(hgblResourceData);

Return:
    return ipStream;
}

void CScreenShow::DrawScreen(HWND hWnd, HDC hdc)
{
	if (!gScreenShow.WindowOpen)
	{
		return;
	}

	if (gScreenShow.TotalAdded==0)
	{
		return;
	}

	if (gScreenShow.workbuffer.size() == 0)
	{
		return;
	}

	if (gScreenShow.isNeedReDraw == false)
	{
		return;
	}

	gScreenShow.ScreenWnd = hWnd;
	gScreenShow.ScreenDC = hdc;

	UINT len = gScreenShow.workbuffer.size();
	HGLOBAL hMem = GlobalAlloc(GMEM_FIXED, len);
	BYTE *pmem = (BYTE*)GlobalLock(hMem);
	memcpy(pmem, &gScreenShow.workbuffer[0], len);
	IStream    *stream = NULL;
	CreateStreamOnHGlobal(hMem, FALSE, &stream);
	CImage image;
	image.Load(stream);
	stream->Release();
	GlobalUnlock(hMem);
	GlobalFree(hMem);

	CImage LogoImage;
	LogoImage.Load("logo.png");

	wchar_t text[50];
	wchar_t text1[50];

	swprintf(text,L"FPS: %d",gScreenShow.RealFPS);
	swprintf(text1,L"Picture Quality: %d",gScreenShow.ScreenQuality);

	Gdiplus::Graphics graphics ( image.GetDC () );
	Gdiplus::Font font ( &FontFamily ( L"Arial" ), 16 );
	Gdiplus::SolidBrush brush ( Color ( 255, 0, 0, 255 ) );
	graphics.DrawString ( text, -1, &font, PointF(0.0f, 0.0f), &brush );
	graphics.DrawString ( text1, -1, &font, PointF(0.0f, 19.0f), &brush );
	image.ReleaseDC();

	image.Draw(hdc,0,0,gScreenShow.ScreenWidth,gScreenShow.ScreenHeight,0,0,gScreenShow.ScreenWidth,gScreenShow.ScreenHeight+gScreenShow.ScreenDiff);
	//image.StretchBlt(hdc,0,0,gScreenShow.ScreenWidth,gScreenShow.ScreenHeight/*-30*//*image.GetWidth(),image.GetHeight()*/,SRCCOPY);
	LogoImage.StretchBlt(hdc,gScreenShow.ScreenWidth - LogoImage.GetWidth()-6-10,10,LogoImage.GetWidth(),LogoImage.GetHeight()/*image.GetWidth(),image.GetHeight()*/,SRCCOPY);

	

	image.Destroy();
	LogoImage.Destroy();

	gScreenShow.isNeedReDraw = false;
}

void CScreenShow::SendScreenState(int aIndex, int state)
{
	if (state == 1)
	{
		this->WorkIndex = aIndex;
	}
	else
	{
		this->WorkIndex = -1;
		this->ScreenQuality = 100;
		this->ScreenDiff = 0;
	}

	PMSG_SCREENSTATE_SEND pMsg;

	pMsg.header.set(0x10,sizeof(pMsg));

	pMsg.value = state;

	pMsg.quality = this->ScreenQuality;

	gSocketManager.DataSend(aIndex,(BYTE*)&pMsg,pMsg.header.size);
}

void CScreenShow::RecvScreenData(PMSG_SCREENDATA_RECV* lpMsg, int aIndex)
{
	if (aIndex != this->WorkIndex)
	{
		return;
	}

	HDC hDCScreen =  GetDC(NULL);
	int Horres = GetDeviceCaps(hDCScreen,  HORZRES);
	int Vertres = GetDeviceCaps(hDCScreen,  VERTRES);
	ReleaseDC(NULL, hDCScreen);

	if (Horres > lpMsg->Width && Vertres > lpMsg->Height)
	{
		this->ScreenWidth = lpMsg->Width;
		this->ScreenHeight = lpMsg->Height;
	}
	else
	{
		this->ScreenWidth = Horres-(Horres/100*10);
		this->ScreenHeight = Vertres-(Vertres/100*10);
		this->ScreenDiff = 100;
	}

	this->WindowOpen = true;
	MoveWindow(this->ScreenWnd,0,0,this->ScreenWidth,this->ScreenHeight+30,1);
	ShowWindow(ScreenWnd, SW_SHOWNORMAL);
}
