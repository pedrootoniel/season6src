#include "stdafx.h"
#include "Controller.h"
#include "Offset.h"
#include "LicenseInfo.h"
#include "Interface.h"
#include "TrayMode.h"
//#include "ServerInfo.h"
#include "Camera.h"
#include "NewParty.h"
#include "Smithy.h"
#include "UserPanel.h"
#include "NewInterface.h"
#include "ShopSearch.h"
#include "Ranking.h"
#include "NewsBoard.h"
#include "LuckySpin.h"
#ifdef NOLOAD
// ----------------------------------------------------------------------------------------------

Controller	gController;
// ----------------------------------------------------------------------------------------------
HHOOK HookKB;
HHOOK HookMS;
BOOL VKF9_State = 0;
BOOL VKF8_State = 0;

LONG WINAPI CheckMacroThread() // OK
{
	while(!SleepEx(400,0))
	{
		if(VKF9_State != 0)
		{
			SendMessage(*(HWND*)(MAIN_WINDOW),WM_RBUTTONDOWN,VK_F9,MK_RBUTTON);
			gInterface.ShowAutoInfo = true;
		}
	}

	return 0;
}

LONG WINAPI CheckMacroThreadMouse() // OK
{
	while(!SleepEx(10,0))
	{
		if(VKF8_State != 0)
		{
			if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					pCursorX = 320;
					pCursorY = 240;
				}
		}
	}

	return 0;
}
bool Controller::Load()
{
	CreateThread(0,0,(LPTHREAD_START_ROUTINE)CheckMacroThread,0,0,0);

	CreateThread(0,0,(LPTHREAD_START_ROUTINE)CheckMacroThreadMouse,0,0,0);

	if( !this->MouseHook )
	{
		this->MouseHook = SetWindowsHookEx(WH_MOUSE, this->Mouse, gController.Instance, GetCurrentThreadId());
		// ----
		if( !this->MouseHook )
		{
			return false;
		}
	}
	
	// ----
	if( !this->KeyboardHook )
	{
		this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, this->Keyboard, gController.Instance, NULL);
		// ----
		if( !this->KeyboardHook )
		{
			return false;
		}
	}
	
	// ----
	////console.Log(FUNC, "[Controller]\t\tSuccessfully Loaded");
	return true;
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Mouse(int Code, WPARAM wParam, LPARAM lParam)
{
	if( GetForegroundWindow() != *(HWND*)(MAIN_WINDOW) )
	{
		return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
	}
	gController.wMouse = wParam;
	// ----
	MOUSEHOOKSTRUCTEX * Mouse	= (MOUSEHOOKSTRUCTEX*)lParam;
	// ----
	//gCamera.Run(Mouse, wParam);
	// ----
	//g_Console.AddMessage(5,"Event = %d",wParam);
	switch(wParam)
	{
		case WM_MOUSEMOVE:
			if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
			{
				gCamera.Move(Mouse);
			}
			break;
		case WM_MBUTTONDOWN:
			if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
			{
				gCamera.SetIsMove(1);
				gCamera.SetCursorX(Mouse->pt.x);
				gCamera.SetCursorY(Mouse->pt.y);
			}
			break;
		case WM_MBUTTONUP:
			if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
			{
				gCamera.SetIsMove(0);
				//gController.ProcInterface(wParam);
			}
			break;
		case WM_MOUSEWHEEL:
			if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
			{
				gCamera.Zoom(Mouse);
				if (gUserPanel.EventUserPanel(wParam,Mouse) == true)
				{
					return 1;
				}
			}
			break;
		case WM_LBUTTONUP:
		case WM_LBUTTONDOWN:
		{
			if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
			{
				gController.ProcInterface(wParam);
				if (gNewInterface.EventAllWindow(wParam,Mouse) == true)
				{
					return 1;
				}
			}
		}
		break;
	}
	// ----
	return CallNextHookEx(gController.MouseHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Keyboard(int Code, WPARAM wParam, LPARAM lParam)
{
	if( (Code == HC_ACTION) && (wParam == WM_KEYDOWN))
	{
		KBDLLHOOKSTRUCT Hook = *((KBDLLHOOKSTRUCT*)lParam);
		// ----
		if( GetForegroundWindow() == *(HWND*)(MAIN_WINDOW) )
		{
			if (gInterface.ControlTextBox(Hook))
			{
				return 1;
			}
		}
		// ----

	} 
	return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Window(HWND Window, DWORD Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	/*case WM_CLOSE:
		{
			int Key= MessageBox(*(HWND*)(MAIN_WINDOW), "You realy want to close MuOnline ? =(", "MuOnline", MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2);
			if (Key!=6)
			{
				return 0;
			}
		}
		break;*/
	case TRAYMODE_ICON_MESSAGE:
		{
			switch(lParam)
			{
			case WM_LBUTTONDBLCLK:
				{
					gTrayMode.SwitchState();
				}
				break;
			}
		}
		break;
	}
	// ----
	return CallWindowProc((WNDPROC)gTrayMode.TempWindowProc, Window, Message, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------

void Controller::ProcInterface(WPARAM wParam)
{
	if(strcmp(gLicenseInfo.RFbt,"2") == 0)
	{			
		gInterface.EventMenuButton(wParam);
	}
	if(strcmp(gLicenseInfo.RFbt,"1") == 0)
	{			
		gInterface.EventMenuButton1(wParam);
	}
	gInterface.EventUserPanel(wParam);
	gInterface.EventRolltheDice_Main(wParam);
	gInterface.EventTitleSystem_Main(wParam);
	gInterface.EventHeadsTails_Main(wParam);
	gInterface.EventLuckyNumber_Main(wParam);
	//gInterface.EventGamblingPanel(wParam);
	gInterface.EventTitleManagerButton_Main(wParam);
	//gInterface.EventSmithItem_Main(wParam);
	gInterface.EventPartySearchWindow_All(wParam);
	gInterface.EventPartySettingsWindow_Main(wParam);
	gSmithy.Button(wParam);
	g_PersonalShopEx.Button(wParam);
	g_Party.MouseController(wParam);
	g_Party.MouseControllerD(wParam);
	g_Party.MouseControllerPage(wParam);
#if(ADD_PARTY_LEADER==1)
	g_Party.MouseControllerLeader(wParam);
#endif
	gInterface.EventStatsAddWindow(wParam);
	gInterface.EventResetStatsWindow(wParam);
	//gInterface.EventCharacterWindow(wParam);
	gInterface.EventOffExpWindow_Main(wParam);
	gInterface.EventAccountSecurityPW_Main(wParam);
	gInterface.EventAccountSecurity_Main(wParam);
	gInterface.EventSelectChar(wParam);
	gInterface.EventChangingClassWindow_Main(wParam);
	gInterface.EventVipWindow_Main(wParam);
	gInterface.EventRename_Main(wParam);
	gInterface.EventPSHOP_Main(wParam);
	gInterface.EventPSHOP_OFFMODE(wParam);
	gInterface.EventJewelsBank(wParam);
	gInterface.EventRPS_Main(wParam);
	gInterface.EventNewsWindow_Main(wParam);
	gLuckySpin.EventWindow_Main(wParam);
	gInterface.EventFruitWindow_Main(wParam);
	gInterface.EventGiftCode_Main(wParam);
	gInterface.EventUsersPanel(wParam);
	/*
	if (wParam == WM_LBUTTONUP)
	{
		for (int i=0; i<eMAX_VALUE;i++)
		{
			gInterface.Data[i].OnClick = false;
		}
	}
	*/
}
#endif