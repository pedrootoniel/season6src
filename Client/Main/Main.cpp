#include "stdafx.h"
#include "resource.h"
#include "Main.h"
#include "..\\..\\Util\\CCRC32.H"
#include "Common.h"
#include "CustomItem.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "HackCheck.h"
#include "HealthBar.h"
#include "Item.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Protocol.h"
#include "Reconnect.h"
#include "Resolution.h"
#include "Util.h"
#include "WingEffect.h"
#include "WingBright.h"
#include "NewFont.h"
#include "CustomBow.h"
#include "Interface.h"
#include "CustomFog.h"
#include "Other.h"
#include "WingInvisible.h"
#include "Camera.h"
#include "ChatWindow.h"
#include "LoadMap.h"
#include "Monster.h"
#include "CustomMonster.h"
#include "Offset.h"
#include "CopyEffect.h"
#include "PetHook.h"
#include "Inter3.h"
#include "Controller.h"
#include "Pet.h"
#include "Fenrir.h"
#include "Font.h"
#include "RFGloves.h"
#include "CustomSmoke.h"
#include "ItemSmoke.h"
#include "CustomTitle.h"
#include "CustomPet.h"
#include "SmithItem.h"
#include "LicenseInfo.h"
#include "ModelEffect.h"
#include "Config.h"
#include "zCustomJewel.h"
#include "SocketItem.h"
#include "InfoLog.h"
#include "User.h"
#include "Console.h"
#include "SpeedFix.h"
#include "EventEntryLevel.h"
#include "MuHelper.h"
#include "MonsterNameColor.h"
#include "ItemOption.h"
#include "ItemPosition.h"
#include "BowCrossbow.h"
#include "CustomWeapons.h"
#include "CustomGloves.h"
#include "BattleGloves.h"
#include "EventTimer.h"
#include "CreateEffect.h"

HINSTANCE hins;
void RefreshRam()
{
	HANDLE v1;
	HANDLE v2;

	while ( true )
	{
		Sleep(5000);
		v1 = GetCurrentProcess();
		SetProcessWorkingSetSize(v1, 0xFFFFFFFF, 0xFFFFFFFF); 
		v2 = GetCurrentProcess();
		SetThreadPriority(v2, THREAD_PRIORITY_LOWEST);
	}
}

extern "C" _declspec(dllexport) void EntryProc() // OK
{
	
	if(!gLicenseInfo.CheckSumLoad("license.info"))
	{
		ExitProcess(0);
	}
	
	if(gProtect.ReadMainFile("main.supremo") == 0)
	{
		ExitProcess(0);
	}

	if(gProtect.m_MainInfo.Instances == 0)
	{
		CreateMutexA(0, 1, "MuOnline");
		if( GetLastError() == 183 )
			ExitProcess(0);
	}
	
	DWORD OldProtect;
	if(VirtualProtect(LPVOID(0x401000),0xD21FFF,PAGE_EXECUTE_READWRITE,&OldProtect ) ) 
	{
		SetByte(0x00E61144, 0xA0); // Accent
		SetByte(0x004D1E69, 0xEB); // Crack (mu.exe)
		SetByte(0x004D228D, 0xE9); // Crack (GameGuard)
		SetByte(0x004D228E, 0x8B); // Crack (GameGuard)
		SetByte(0x004D228F, 0x00); // Crack (GameGuard)
		SetByte(0x004D2290, 0x00); // Crack (GameGuard)
		SetByte(0x004D2291, 0x00); // Crack (GameGuard)
		SetByte(0x004D559C, 0xEB); // Crack (ResourceGuard)
		SetByte(0x00633F7A, 0xEB); // Crack (ResourceGuard)
		SetByte(0x00634403, 0xEB); // Crack (ResourceGuard)
		SetByte(0x0063E6C4, 0xEB); // Crack (ResourceGuard)
		SetByte(0x004D2246, 0xEB); // Crack (ResourceGuard)
		SetByte(0x00501163, 0xEB); // Crack (ResourceGuard)
		SetByte(0x0040AF0A, 0x00); // Crack (ResourceGuard)
		SetByte(0x0040B4BC, 0x50); // Login Screen
		SetByte(0x0040B4C5, 0x50); // Login Screen
		SetByte(0x0040B4CF, 0x18); // Login Screen
		SetByte(0x0040AF0A, 0x00); // Login Screen
		SetByte(0x0040AFD5, 0xEB); // Login Screen
		SetByte(0x00777FD6, 0x70); // Item Text Limit
		SetByte(0x00777FD7, 0x17); // Item Text Limit
		SetByte(0x004EBEC7, 0x3C); // Item Text Limit
		SetByte(0x005C4004, 0x3C); // Item Text Limit
		SetByte(0x007E40BB, 0x3C); // Item Text Limit
		SetByte(0x0081B546, 0x3C); // Item Text Limit
		SetByte(0x0081B58D, 0x3C); // Item Text Limit
		SetByte(0x0086E284, 0x3C); // Item Text Limit
		SetByte(0x0086E44C, 0x3C); // Item Text Limit
		SetByte(0x0086E573, 0x3C); // Item Text Limit
		SetByte(0x0086F8FC, 0x3C); // Item Text Limit
		SetByte(0x007DA373, 0xB7); // Item Type Limit
		SetByte(0x007E1C44, 0xB7); // Item Type Limit
		SetByte(0x0052100D, 0xEB); // Ctrl Fix
		SetByte(0x009543C4, 0x00); // Move Vulcanus
		SetByte(0x0064CBD1, ((gProtect.m_MainInfo.HelperActiveAlert == 0) ? 0xEB : 0x75)); // Helper Message Box
		SetByte(0x0064CBD0, (BYTE)gProtect.m_MainInfo.HelperActiveLevel); // Helper Active Level
		SetByte(0x0095CEEF, (BYTE)gProtect.m_MainInfo.HelperActiveLevel); // Helper Active Level
		SetByte(0x0095CF14, (BYTE)gProtect.m_MainInfo.HelperActiveLevel); // Helper Active Level
		
		/*
		MemoryCpy(0x00E611B2, gProtect.m_MainInfo.IpAddress, sizeof(gProtect.m_MainInfo.IpAddress)); // IpAddress		
		MemoryCpy(0x00E61F70, gProtect.m_MainInfo.ClientSerial, sizeof(gProtect.m_MainInfo.ClientSerial)); // ClientSerial
		SetByte(0x00E61F68, (gProtect.m_MainInfo.ClientVersion[0] + 1)); // Version
		SetByte(0x00E61F69, (gProtect.m_MainInfo.ClientVersion[2] + 2)); // Version
		SetByte(0x00E61F6A, (gProtect.m_MainInfo.ClientVersion[3] + 3)); // Version
		SetByte(0x00E61F6B, (gProtect.m_MainInfo.ClientVersion[5] + 4)); // Version
		SetByte(0x00E61F6C, (gProtect.m_MainInfo.ClientVersion[6] + 5)); // Version
		SetWord(0x00E609E4, (gProtect.m_MainInfo.IpAddressPort)); // IpAddressPort
		SetDword(0x004D0E09, (DWORD)gProtect.m_MainInfo.WindowName);
		SetDword(0x004D9F55, (DWORD)gProtect.m_MainInfo.ScreenShotPath);
		*/
		
		MemoryCpy(0x00E611B2, gLicenseInfo.ServerIP, sizeof(gLicenseInfo.ServerIP)); // IpAddress
		MemoryCpy(0x00E61F70, gLicenseInfo.Serial, sizeof(gLicenseInfo.Serial)); // ClientSerial
		SetWord(0x00E609E4, (gLicenseInfo.CSPort)); // IpAddressPort
		SetByte(0x00E61F68, (gLicenseInfo.MainCRCchar[0] + 1)); // Version
		SetByte(0x00E61F69, (gLicenseInfo.MainCRCchar[2] + 2)); // Version
		SetByte(0x00E61F6A, (gLicenseInfo.MainCRCchar[3] + 3)); // Version
		SetByte(0x00E61F6B, (gLicenseInfo.MainCRCchar[5] + 4)); // Version
		SetByte(0x00E61F6C, (gLicenseInfo.MainCRCchar[6] + 5)); // Version
		SetDword(0x004D0E09, (DWORD)gLicenseInfo.WindowName); //Window Name
		SetDword(0x004D9F55, (DWORD)gLicenseInfo.ScreenShot); // Screenshots path
		
		SetDword(0x004D9D3B, (DWORD)&FrameValue);
		SetDword(0x004DAC60, (DWORD)&FrameValue);
		//SetDword(0x004D597B, (DWORD)&MainTickCount);
		//SetDword(0x004DA289, (DWORD)&MainTickCount);
		//SetDword(0x004DA297, (DWORD)&MainTickCount);
		//SetDword(0x004DA3A2, (DWORD)&MainTickCount);
		//SetDword(0x004DA3CE, (DWORD)&MainTickCount);
		//SetDword(0x004DA3D9, (DWORD)&MainTickCount);
		//SetDword(0x0063D326, (DWORD)&MainTickCount);
		//SetDword(0x00642112, (DWORD)&MainTickCount);

		MemorySet(0x0063E908, 0x90, 20); // C1:F3:04

		SetByte(0x004D7D18 + 4, 0xEB);	  //Webzen Copyright
		SetByte(0x004D7DAD + 4, 0xEB);	  //Webzen Copyright

		SetCompleteHook(0xFF, 0x0065FD79, &ProtocolCoreEx);

		//SetCompleteHook(0xE9, 0x004DA280, &CheckTickCount1);

		//SetCompleteHook(0xE9, 0x004DA3A1, &CheckTickCount2);

		//SetCompleteHook(0xE8, 0x005B96E8, &gHPBar.DrawHealthBar);

		VirtualizeOffset(0x004D9D39, 12);

		VirtualizeOffset(0x004D9D45, 7);

		VirtualizeOffset(0x004D9EFC, 15);

		VirtualizeOffset(0x004DAC5C, 8);

		VirtualizeOffset(0x005451F7, 5);

		VirtualizeOffset(0x00545230, 8);

		VirtualizeOffset(0x005A52E9, 8);

		LoadReferenceAddressTable((HMODULE)hins,MAKEINTRESOURCE(IDR_BIN1),(DWORD)&NewAddressData1);

		LoadReferenceAddressTable((HMODULE)hins,MAKEINTRESOURCE(IDR_BIN2),(DWORD)&NewAddressData2);

		LoadReferenceAddressTable((HMODULE)hins,MAKEINTRESOURCE(IDR_BIN3),(DWORD)&NewAddressData3);

		gCustomMessage.LoadEng(gProtect.m_MainInfo.EngCustomMessageInfo);

		gCustomMessage.LoadPor(gProtect.m_MainInfo.PorCustomMessageInfo);

		gCustomMessage.LoadSpn(gProtect.m_MainInfo.SpnCustomMessageInfo);

		gCustomMessage.LoadVtm(gProtect.m_MainInfo.VtmCustomMessageInfo);

		gCustomJewel.Load(gProtect.m_MainInfo.CustomJewelInfo);

		gCustomWing.Load(gProtect.m_MainInfo.CustomWingInfo);

		gCustomItem.Load(gProtect.m_MainInfo.CustomItemInfo);

		gCustomMonster.Load(gProtect.m_MainInfo.CustomMonsterInfo);

		gCustomWingEffect.Load(gProtect.m_MainInfo.CustomWingEffectInfo);

		gDynamicWingEffect.Load(gProtect.m_MainInfo.DynamicWingEffectInfo);

		gCustomSmoker.Load(gProtect.m_MainInfo.CustomSmokerInfo);

		gCustomTitle.Load(gProtect.m_MainInfo.CustomTitleInfo);

		gFog.Load(gProtect.m_MainInfo.CustomFog);

		gCustomPet2.Load(gProtect.m_MainInfo.CustomPetInfo);

		gEventTimer.Load(gProtect.m_MainInfo.CustomEventTime);

		gPacketManager.LoadEncryptionKey("Data\\Enc1.dat");

		gPacketManager.LoadDecryptionKey("Data\\Dec2.dat");

		//gHPBar.Load();
		
		if(gProtect.m_MainInfo.HealthBar == 1)
		{
			SetCompleteHook(0xE8,0x005B96E8,&gHPBar.DrawAllHPBars);
		}
		gConfig.Load();
	
		gHPBar.LoadRankTitle();

		InitCommon();

		gObjUser.Load();

		InitHackCheck();

		InitItem();

		InitJewel();

		InitPrintPlayer();

		InitReconnect();

		InitResolution();

		InitWing();

		gProtect.CheckLauncher();

		gProtect.CheckInstance();

		gProtect.CheckClientFile();

		gProtect.CheckPlugin1File();

		gProtect.CheckPlugin2File();

		gProtect.CheckPlugin3File();

		gProtect.CheckPlugin4File();

		gProtect.CheckPlugin5File();

		gProtect.CheckCameraFile();

		Fcolor->LoadResource();

		gLoadMap.Load();

		gOther.Load();

		//gWingEffect.Load();

		gWingsBright.Load();

		int FontSwitch = GetPrivateProfileInt("Font", "EnableNewFont", 0, ".\\Settings.ini");
		if (FontSwitch == 1) { gFont.Load(); }

		//gSocketItem.Load();

		gCopyEffect.Load();   // esse e o efeito na wings

		gCreateEffect.Load(); // esse e o brilho ok (ajustar efeito sword 0 47)

		gMonster.Load();

		gController.Load(hins);

		gObjCreatePetExHook();

		gCustomModelEffect.Load(gProtect.m_MainInfo.ModelEffectInfo);

		gCustomMonsterNameColor.Load(gProtect.m_MainInfo.CustomMonsterNameColor);

		if(strcmp(gLicenseInfo.RFbt,"2") == 0)
		{
			InitInter3();
		}
		if(strcmp(gLicenseInfo.RFbt,"1") == 0)
		{
			InitInter1();
		}
		
		gInterface.Load();
		
		gCustomPet.Load();

		gNewPets.Load();

		gItemPosition.Load();

		InitBows();

		gRFItem.Load();

		//gCustomBow.Load();

		gWingInvisible.Load();

		gItemSmokeEffect.Load();

		gInfoLog.Load();

		gChatExpanded.Load();
		
		InitAttackSpeed();

		gMuHelper.Load();

		//gJewel.Load();

		if(gProtect.m_MainInfo.MasterSkillTree == 0)
		{
			SetNop(0x008193F0,0xC8); //->Master skill tree
		}
		
		//LoadDSEntryLevel();
		//LoadBCEntryLevel();

		gItemOption.Load(gProtect.m_MainInfo.CustomItemOption);

		gCustomWeapons.Load(gProtect.m_MainInfo.CustomWeapons);

		gCustomGloves.Load(gProtect.m_MainInfo.CustomGloves);

		if(gConfig.m_Fog == 1)
		{
			gFog.EnableFog = true;
		}
		/*
		gCustomSmith.LoadSword(gProtect.m_MainInfo.SmithSwordInfo);
		gCustomSmith.LoadAxe(gProtect.m_MainInfo.SmithAxeInfo);
		gCustomSmith.LoadMace(gProtect.m_MainInfo.SmithMaceInfo);
		gCustomSmith.LoadSpear(gProtect.m_MainInfo.SmithSpearInfo);
		gCustomSmith.LoadBow(gProtect.m_MainInfo.SmithBowInfo);
		gCustomSmith.LoadStaff(gProtect.m_MainInfo.SmithStaffInfo);
		gCustomSmith.LoadShield(gProtect.m_MainInfo.SmithShieldInfo);
		gCustomSmith.LoadHelm(gProtect.m_MainInfo.SmithHelmInfo);
		gCustomSmith.LoadArmor(gProtect.m_MainInfo.SmithArmorInfo);
		gCustomSmith.LoadPant(gProtect.m_MainInfo.SmithPantInfo);
		gCustomSmith.LoadGlove(gProtect.m_MainInfo.SmithGloveInfo);
		gCustomSmith.LoadBoot(gProtect.m_MainInfo.SmithBootInfo);
		*/
		
	}
}

BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			hins = (HINSTANCE)hModule;
			CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)RefreshRam,NULL,0,0);
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
	}

	return 1;
}
