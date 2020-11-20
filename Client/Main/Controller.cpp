#include "stdafx.h"
#include "Controller.h"
#include "Offset.h"
#include "LicenseInfo.h"
#include "Interface.h"
#include "TrayMode.h"
#include "Camera.h"
#include "NewParty.h"
#include "Smithy.h"
#include "UserPanel.h"
#include "NewInterface.h"
#include "ShopSearch.h"
#include "Ranking.h"
#include "NewsBoard.h"
#include "LuckySpin.h"
#include "EventTimer.h"
Controller gController;

HHOOK HookKB;
HHOOK HookMS;
BOOL VKF9_State = 0;
BOOL VKF8_State = 0;

LRESULT CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam) // OK
{
	if(nCode == HC_ACTION)
	{
		// ----
		if(((DWORD)lParam & (1 << 30)) != 0 && ((DWORD)lParam & (1 << 31)) != 0)
		{
			if( GetForegroundWindow() == *(HWND*)(MAIN_WINDOW) )
			{
				gInterface.ControlTextBox(wParam);
			}
			switch(wParam)
			{
				case VK_F8:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						if(VKF9_State == 1){
							VKF8_State ^= 1;
						}
						else{
							VKF8_State = 0;
						}
					}
				break;
				case VK_F9:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						VKF9_State ^= 1;
						VKF8_State = 0;
						SendMessage(*(HWND*)(MAIN_WINDOW),WM_RBUTTONUP,VK_F9,MK_RBUTTON);
						gInterface.ShowAutoInfo = false;
					}
				break;
				case VK_F10:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						gCamera.Toggle();
					}
					break;
				case VK_F11:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						gCamera.Restore();
					}
					break;
				case VK_F12:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						gUserPanel.UserPanelSwitchState();
					}
					break;
				case VK_ESCAPE:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						gInterface.CloseUserPanel();
						gInterface.CloseRolltheDiceWindow();
						gInterface.CloseTitleSystemWindow();
						gInterface.CloseHeadsTailsWindow();
						gInterface.CloseLuckyNumberWindow();
						gInterface.ClosePartySettingsWindow();
						gInterface.ClosePartySearchWindow();
						gInterface.CloseStatsAddWindow();
						gInterface.CloseResetStatsWindow();
						gInterface.CloseOffExpWindow();
						gInterface.CloseAccountSecurityPWWindow();
						gInterface.CloseAccountSecurityWindow();
						gInterface.CloseChangingClassWindow();
						gInterface.CloseBuyVipWindow();
						gInterface.CloseRenameWindow();
						gInterface.ClosePShopWindow();
						gInterface.CloseJewelsBankWindow();
						gInterface.CloseNewsWindow();
						gInterface.CloseFruitWindow();
						gInterface.CloseGiftCodeWindow();
						gInterface.CloseEventTableWindow();
						gInterface.CloseWarehouseWindow();
						pSetCursorFocus = false;
					}
					break;
				case VK_END:
					if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
					{
						gTrayMode.Toggle();
					}
					break;
				default:
					break;
			}
		}

	
	}
	
	return CallNextHookEx(HookKB,nCode,wParam,lParam);
}

LRESULT CALLBACK MouseProc(int nCode,WPARAM wParam,LPARAM lParam) // OK
{
	if(nCode == HC_ACTION)
	{
		MOUSEHOOKSTRUCTEX* HookStruct = (MOUSEHOOKSTRUCTEX*)lParam;
		gController.wMouse = wParam;
		switch(wParam)
		{
			case WM_MOUSEMOVE:
				if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					gCamera.Move(HookStruct);
				}
				break;
			case WM_MBUTTONDOWN:
				if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					gCamera.SetIsMove(1);
					gCamera.SetCursorX(HookStruct->pt.x);
					gCamera.SetCursorY(HookStruct->pt.y);
				}
				break;
			case WM_MBUTTONUP:
				if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					gCamera.SetIsMove(0);
				}
				break;
			case WM_MOUSEWHEEL:
				if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					gCamera.Zoom(HookStruct);
					gUserPanel.EventUserPanel(wParam,HookStruct);
				}
				break;
			case WM_LBUTTONUP:
			case WM_LBUTTONDOWN:
				if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
				{
					if (gNewInterface.EventAllWindow(wParam,HookStruct) == true)
					{
						return 1;
					}
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
					//g_Party.MouseControllerMove(wParam);
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
					gInterface.EventEventTableWindow(wParam);
					gInterface.EventWarehouseUI(wParam);
					gInterface.EventPartyInterface(wParam);
				}
				break;
			default:
				break;
		}
	}

	return CallNextHookEx(HookMS,nCode,wParam,lParam);
}
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

void Controller::Load(HINSTANCE Instance)
{

		HookKB = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,Instance,GetCurrentThreadId());

		HookMS = SetWindowsHookEx(WH_MOUSE,MouseProc,Instance,GetCurrentThreadId());

		CreateThread(0,0,(LPTHREAD_START_ROUTINE)CheckMacroThread,0,0,0);

		CreateThread(0,0,(LPTHREAD_START_ROUTINE)CheckMacroThreadMouse,0,0,0);

		gTrayMode.Init(Instance);
}