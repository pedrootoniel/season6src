// TrayMode.cpp: implementation of the CTrayMode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <ShellAPI.h>
#include "resource.h"
#include "TrayMode.h"
#include "Offset.h"
#include "User.h"
#include "Import.h"
#include "Protect.h"
CTrayMode gTrayMode;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrayMode::CTrayMode() // OK
{
}

void CTrayMode::Init(HINSTANCE Instance) // OK
{
	this->m_TrayIcon = (HICON)LoadImage(Instance,MAKEINTRESOURCE(IDI_ICON2),IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),LR_DEFAULTCOLOR);

	this->m_MainWndProc = 0;

	this->InTray = false;
}

void CTrayMode::Toggle() // OK
{
	if(this->GetMainWndProc() != 0)
	{
		if(IsWindowVisible(*(HWND*)(MAIN_WINDOW)) == 0)
		{
			ShowWindow(*(HWND*)(MAIN_WINDOW),SW_SHOW);

			this->ShowNotify(0);
		}
		else
		{
			ShowWindow(*(HWND*)(MAIN_WINDOW),SW_HIDE);

			this->ShowNotify(1);

			this->ShowMessage(NIIF_INFO, gProtect.m_MainInfo.WindowName, "Mu window was minimized.");
		}
	}
}

LONG CTrayMode::GetMainWndProc() // OK
{
	return ((this->m_MainWndProc==0)?((LONG)(this->m_MainWndProc=(WNDPROC)SetWindowLong(*(HWND*)(MAIN_WINDOW),GWL_WNDPROC,(LONG)CTrayMode::TrayModeWndProc))):((LONG)this->m_MainWndProc));
}

void CTrayMode::ShowNotify(bool mode) // OK
{
	this->InTray = mode;
	NOTIFYICONDATA nid;

	memset(&nid,0,sizeof(nid));

	nid.cbSize = sizeof(NOTIFYICONDATA);

	nid.hWnd = *(HWND*)(MAIN_WINDOW);

	nid.uID = WM_TRAY_MODE_ICON;

	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;

	nid.uCallbackMessage = WM_TRAY_MODE_MESSAGE;

	nid.hIcon = this->m_TrayIcon;

	if(*(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		char Text[120];
		sprintf(Text, "[%s]\n=====================\nCharacter: %s\nLevel: %d \nMap: %s (%d:%d)",gProtect.m_MainInfo.WindowName,
				gObjUser.lpPlayer->Name, gObjUser.lpPlayer->Level,
				gObjUser.GetMapName(gObjUser.m_MapNumber), gObjUser.lpViewPlayer->MapPosX, gObjUser.lpViewPlayer->MapPosY);
		strcat_s(nid.szTip, Text);
	}
	else
	{
		wsprintf(nid.szTip,"Mu Online");
	}

	Shell_NotifyIcon(((mode==0)?NIM_DELETE:NIM_ADD),&nid);
}

void CTrayMode::ShowMessage(DWORD Type, char * Title, char * Message)
{
	NOTIFYICONDATA Icon		= { 0 };
	
	Icon.cbSize				= sizeof(NOTIFYICONDATA);
	Icon.uID				= WM_TRAY_MODE_ICON;
	Icon.hWnd				= *(HWND*)MAIN_WINDOW;
	Icon.uFlags				= NIF_ICON | NIF_MESSAGE | NIF_INFO;
	Icon.hIcon				= this->m_TrayIcon;
	Icon.uCallbackMessage	= WM_TRAY_MODE_MESSAGE;
	Icon.dwInfoFlags		= Type;
	Icon.uTimeout			= 5000;
	
	strcpy(Icon.szInfo, Message);
	strcpy(Icon.szInfoTitle, Title);
	
	Shell_NotifyIcon(NIM_MODIFY, &Icon);
}


LRESULT CALLBACK CTrayMode::TrayModeWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) // OK
{
	switch(message)
	{
		case WM_TRAY_MODE_MESSAGE:
			switch(lParam)
			{
				case WM_LBUTTONDBLCLK:
					gTrayMode.Toggle();
					break;
				default:
					break;
			}
		default:
			break;
	}

	return CallWindowProc((WNDPROC)gTrayMode.GetMainWndProc(),hWnd,message,wParam,lParam);
}