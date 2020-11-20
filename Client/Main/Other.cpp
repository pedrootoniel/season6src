#include "stdafx.h"
#include "Other.h"
#include "CustomFog.h"
#include "Offset.h"
#include "Object.h"
#include "Import.h"
#include "Defines.h"
#include "Protocol.h"
#include "TMemory.h"
#include "CustomMessage.h"
#include "LicenseInfo.h"
#include "HealthBar.h"
#include "Interface.h"
#include "Protect.h"
#include "MemScript.h"
#include "Config.h"
#include "zCustomJewel.h"
#include "CharacterList.h"
#include "Protect.h"
#include "Util.h"
Other gOther;

int InGameEffects		= GetPrivateProfileInt("Graphics","FixGraphics",0,".\\Settings.ini");
int Anisotropy			= GetPrivateProfileInt("Graphics","Anisotropy",0,".\\Settings.ini");
int MaxAnisotropy		= GetPrivateProfileInt("Graphics","MaxAnisotropy",0,".\\Settings.ini");
int Linear				= GetPrivateProfileInt("Graphics","Linear",0,".\\Settings.ini");
// ----------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------
//OGL Function Prototypes
void (WINAPI *glEnable_original)(GLenum cap) = glEnable;
void (WINAPI *glClearColor_original)(GLclampf r,GLclampf g,GLclampf b,GLclampf a) = glClearColor;
int g_nMaxAnisotropy = MaxAnisotropy;
// ----------------------------------------------------------------------------------------------

void WINAPI glEnable_hook(GLenum mode)
{
	// ---
	if(InGameEffects != 0)
	{
		if(Anisotropy != 0)
		{
			glGetIntegerv(0x84FF,&g_nMaxAnisotropy);
			glTexParameteri(GL_TEXTURE_2D,0x84FE,g_nMaxAnisotropy-(GLint)0.1);
		}
		if(Linear != 0)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
	else
	{
		if(Anisotropy != 0)
		{
			glGetIntegerv(0x84FF,&g_nMaxAnisotropy);
			glTexParameteri(GL_TEXTURE_2D,0x84FE,g_nMaxAnisotropy-(GLint)0.1);
		}
		if(Linear != 0)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	if (gConfig.m_Fog == 1)
	{
		CUSTOM_FOG* lpFog = gFog.GetFogByMap(pMapNumber);

		if (lpFog != 0)
		{
			float rgba[4] = {lpFog->Red, lpFog->Green, lpFog->Blue, 1.0f}; gFog.toRGB(rgba);
					
			if (mode == GL_BLEND || mode == GL_TEXTURE_2D || mode == GL_DEPTH_TEST)
				glDisable(GL_FOG);

			glFogi(GL_FOG_MODE, GL_LINEAR);
			glFogf(GL_FOG_DENSITY, 0.25f);
			glFogfv(GL_FOG_COLOR, rgba);
			if(pMapNumber==74)
			{
				glFogf(GL_FOG_START, 4050);
				glFogf(GL_FOG_END, 4850);
			}
			else
			{
				glFogf(GL_FOG_START, 1650.0f);
				glFogf(GL_FOG_END, 2100.0f);
			}
			glHint(GL_FOG_HINT, GL_NICEST);
			 
			glEnable_original(GL_FOG);

			if (mode == GL_BLEND || mode == GL_TEXTURE_2D || mode == GL_DEPTH_TEST) 
				glDisable(GL_FOG); 

			if(!gFog.EnableFog)
			{
				glDisable(GL_FOG);
			}
		}
	}
	glEnable_original(mode);
}

void WINAPI glClearColor_hook(GLclampf r,GLclampf g,GLclampf b,GLclampf a)
{
	if(gFog.EnableFog == true && gConfig.m_Fog && *(DWORD*)(MAIN_SCREEN_STATE) == GameProcess)
	{
		CUSTOM_FOG* lpFog = gFog.GetFogByMap(pMapNumber);
		if (lpFog != 0)
		{

			float rgba[4];
			rgba[0] = lpFog->Red;
			rgba[1] = lpFog->Green;
			rgba[2] = lpFog->Blue;
			rgba[3] = 1.0;	
			gFog.toRGB(rgba);

			glClearColor_original(rgba[0],rgba[1],rgba[2],rgba[3]);
		}
	}
}

void Other::InitOGLHook()
{	
	//---- glEnable
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID &)glEnable_original,glEnable_hook);
	DetourTransactionCommit();

	//---- glClearColor
	//DetourTransactionBegin();
	//DetourUpdateThread(GetCurrentThread());
	//DetourAttach(&(PVOID &)glClearColor_original,glClearColor_hook);
	//DetourTransactionCommit();

}

void Other::UnlockCastleSkills()
{
	if(gProtect.m_MainInfo.CastleSiegeSkill == 1)
	{
		// 
		SetByte((PVOID)(0x005B89C3+3), 0x00);
		SetByte((PVOID)(0x005B89C9+3), 0x00);
		SetByte((PVOID)(0x005B89CF+3), 0x00);
		SetByte((PVOID)(0x005B89D5+3), 0x00);
		SetByte((PVOID)(0x005B89DB+3), 0x00);
		SetByte((PVOID)(0x005B89E1+3), 0x00);
		SetWord((PVOID)(0x005B89E7+3), 0x00);
		//
		SetByte((PVOID)(0x005C6314+2), 0x00);
		SetByte((PVOID)(0x005C6327+2), 0x00);
		SetByte((PVOID)(0x005C633A+2), 0x00);
		SetByte((PVOID)(0x005C634D+2), 0x00);
		SetByte((PVOID)(0x005C6360+2), 0x00);
		SetByte((PVOID)(0x005C6373+2), 0x00);
		SetWord((PVOID)(0x005C6386+2), 0x00);
	}

}

int gMakePreviewSoldierElf(ObjectPreview * gPreview) 
{
		gPreview->WingsSlot					= ITEM2(12,gConfig.Wings);
		gPreview->HelmSlot					= ITEM2(7,gConfig.SetID[0]);
		gPreview->HelmLevel					= 13;
		gPreview->HelmExcellent				= 1;
		gPreview->ArmorSlot					= ITEM2(8,gConfig.SetID[0]);
		gPreview->ArmorLevel				= 13;
		gPreview->ArmorExcellent			= 1;
		gPreview->PantsSlot					= ITEM2(9,gConfig.SetID[0]);
		gPreview->PantsLevel				= 13;
		gPreview->PantsExcellent			= 1;
		gPreview->GlovesSlot				= ITEM2(10,gConfig.SetID[0]);
		gPreview->GlovesLevel				= 13;
		gPreview->GlovesExcellent			= 1;
		gPreview->BootsSlot					= ITEM2(11,gConfig.SetID[0]);
		gPreview->BootsLevel				= 13;
		gPreview->BootsExcellent			= 1;
		gPreview->WeaponFirstSlot			= ITEM2(gConfig.FirstWeaponType[0],gConfig.FirstWeaponIndex[0]);
		gPreview->WeaponFirstLevel			= 15;
		gPreview->WeaponFirstExcellent		= 1;
		gPreview->WeaponSecondSlot			= ITEM2(gConfig.SecondWeaponType[0],gConfig.SecondWeaponIndex[0]);
		gPreview->WeaponSecondLevel			= 15;
		gPreview->WeaponSecondExcellent		= 1;
		//// ----
		gPreview->Class						= 18;
		return gPreview->m_Model.Prev;
}

DWORD	WingPercentID;
DWORD	WingPecent_buff;
Naked(NewWingPercents)// -> 6 -> 007E4C5D
{
	_asm
	{
		mov WingPercentID, edx
	}
	// ----
	if ( WingPercentID == ITEM(12,180))
	{
		SetByte((PVOID)(0x007E681E + 3), 62); //-> Wings s8
		
	}
	else if (WingPercentID == ITEM(12, 181))
	{
		SetByte((PVOID)(0x007E681E + 3), 56); //-> Wings s8
	}
	else if (WingPercentID == ITEM(12, 190)
		|| WingPercentID == ITEM(12, 191)
		|| WingPercentID == ITEM(12, 192)
		|| WingPercentID == ITEM(12, 193)
		|| WingPercentID == ITEM(12, 194)
		|| WingPercentID == ITEM(12, 195)
		|| WingPercentID == ITEM(12, 196))
	{
		SetByte((PVOID)(0x007E681E + 3), 55); //-> //Wings 4
		
	}
	
	else if(WingPercentID == ITEM(12, 200)||WingPercentID == ITEM(12, 201)
		||WingPercentID == ITEM(12, 202)||WingPercentID == ITEM(12, 203)
		||WingPercentID == ITEM(12, 204)|| WingPercentID == ITEM(12, 205)
		||WingPercentID == ITEM(12, 206)
		)
	{
		SetByte((PVOID)(0x007E681E + 3), 44); //-> Wings Custom
	}
	
	else if ( WingPercentID == ITEM(12,185) || WingPercentID == ITEM(12,186) 
			|| WingPercentID == ITEM(12,187) || WingPercentID == ITEM(12,188) 
			|| WingPercentID == ITEM(12,189))
	{
		SetByte((PVOID)(0x007E681E + 3), 26); //-> Wings 2.5
	}
	else
	{
		SetByte((PVOID)(0x007E681E + 3), 39); //-> Default percent
	}
	// ----
	if ( WingPercentID == 0x1A46 )
	{
		_asm
		{
			mov WingPecent_buff, 0x007E4DB9
			jmp WingPecent_buff
		}
	}
	// ----
	_asm
	{
		mov WingPecent_buff, 0x007E4EB9
		jmp WingPecent_buff
	}
}

bool Other::IsExpensiveItem(ObjectItem * lpItem)
{
	if( lpItem->ItemID == ITEM(13, 20) && lpItem->Level == 0 )	//-> Wizards Ring
	{
		return false;
	}
	
    if ( gJewel.IsCustomJewels ( lpItem->ItemID, false ) ) {
        return true;
    }

	if( (lpItem->ItemID >= ITEM(14,176) && lpItem->ItemID <= ITEM(14,179))
		//||lpItem->ItemID == ITEM(0,47)||lpItem->ItemID == ITEM(2,24)
		||lpItem->ItemID == ITEM(4,30)||lpItem->ItemID == ITEM(5,44)
		||lpItem->ItemID == ITEM(14, 213)|| lpItem->ItemID == ITEM(14, 214)
		||lpItem->ItemID == ITEM(5,45)
		||lpItem->ItemID == ITEM(14,211) ||lpItem->ItemID == ITEM(14,212)
		||lpItem->ExcellentOption > 0 || lpItem->AncientOption > 0
		||(lpItem->ItemID >= ITEM(14,240) && lpItem->ItemID <= ITEM(14,247))
		)
	{
		return true;
	}
	
	return pIsExpensiveItem(lpItem);
}
//BOOL Other::DrawItemNumber(int pObj) // -> 004E1230 //-> 1.04D
//{
//    int pObject = *(WORD*)pObj; // -> Here I make a: 'pointer' to: Inventory Class Method.
//    // ----
//    switch(pObject)
//    {
//        case ITEM(12,30):
//        case ITEM(12,31):
//		case ITEM(12,136):
//		case ITEM(12,137):
//		case ITEM(12,138):
//		case ITEM(12,139):
//		case ITEM(12,140):
//		case ITEM(12,141):
//		case ITEM(12,142):
//		case ITEM(12,143):
//            return TRUE;
//        default:
//			// return FALSE;
//            return pDrawNumber(pObj);
//        break;
//    }
//}
void Other::MoveListInit(LPVOID This, LPVOID EDX, int Arg1, int Arg2)
{
	GLsizei TempWidth = pWinWidth;
	pWinWidth = 1280;
	pMoveListInit(This, Arg1, Arg2);
	pWinWidth = TempWidth;
}

DWORD SocketPointer = 0;
__declspec(naked) void RemoveSocket()
{
	static DWORD RemoveSocketAdress1 = 0x0096826E;
	static DWORD RemoveSocketAdress2 = 0x00968275;
	_asm
	{
		mov ecx, dword ptr ss : [ebp - 0x8]
			mov dword ptr ss : [ebp - 0x8], ecx
			mov SocketPointer, ecx
	}
	if(SocketPointer == ITEM(14,191)
		||SocketPointer == ITEM(14,192)
		||SocketPointer == ITEM(14,193)
		||SocketPointer == ITEM(14,194)
		||SocketPointer == ITEM(14,195)
		||SocketPointer == ITEM(14,196)
		||SocketPointer == ITEM(14,197)
		||SocketPointer == ITEM(14,198)
		||SocketPointer == ITEM(14,199)
		||SocketPointer == ITEM(14,200)
		||SocketPointer == ITEM(14,201)
		||SocketPointer == ITEM(14,202)
		)
	{
		_asm
		{
			jmp[RemoveSocketAdress1]
		}
	}
	else
	{
		_asm
		{
			jmp [RemoveSocketAdress2]
		}
	}
}
DWORD ExcellentGlow_Pointer = 0;
DWORD ExcellentGlow_Buff = 0;

__declspec(naked) void FixWingsExcellentGlow()
{
	static DWORD ExcellentGlowJmp = 0x0060EEA5;
	static DWORD ExcellentGlowJmpNext = 0x0060F325;
	_asm
	{
		Mov ExcellentGlow_Buff,Eax
		MOV EDX,DWORD PTR SS:[EBP+0x8]
		Mov Eax,DWORD PTR DS:[EDX+0x30]
		Mov ExcellentGlow_Pointer,Eax
		Mov Eax,ExcellentGlow_Buff	
	}
	/*
	if(ExcellentGlow_Pointer == 0x1D1A
	 ||(ExcellentGlow_Pointer >= ITEM2(12,180) && ExcellentGlow_Pointer <= ITEM2(12,199))
	 ||ExcellentGlow_Pointer == ITEM2(12,202) || ExcellentGlow_Pointer == ITEM2(12,204)
	 ||ExcellentGlow_Pointer == ITEM2(12,207) || ExcellentGlow_Pointer == ITEM2(12,208)
	 ||ExcellentGlow_Pointer == ITEM2(12,210))
	 */
	if(ExcellentGlow_Pointer == 0x1D1A
	 ||(ExcellentGlow_Pointer >= ITEM2(0,0) && ExcellentGlow_Pointer <= ITEM2(11,255)))
	{
		_asm
		{
			Jmp [ExcellentGlowJmpNext]
		}
	}
	else
	{
		_asm
		{
			Jmp [ExcellentGlowJmp]
		}
	}
}

DWORD DropColorProtect;
DWORD DropColorPointer;
__declspec(naked) void DropColor()
{
	_asm
	{
		Mov DropColorProtect,Eax
		MOV EDX,DWORD PTR SS:[EBP-0x18]
		Mov Eax,DWORD PTR DS:[EDX+0x30]
		Mov DropColorPointer,Eax
		Mov Eax,DropColorProtect
	}
	if(DropColorPointer == 0x253B
		||(DropColorPointer >= ITEM2(7,100) && DropColorPointer <= ITEM2(7,114))
		||(DropColorPointer >= ITEM2(8,100) && DropColorPointer <= ITEM2(8,114))
		||(DropColorPointer >= ITEM2(9,100) && DropColorPointer <= ITEM2(9,114))
		||(DropColorPointer >= ITEM2(10,100)&& DropColorPointer <= ITEM2(10,114))
		||(DropColorPointer >= ITEM2(11,100)&& DropColorPointer <= ITEM2(11,114))
		||(DropColorPointer >= ITEM2(7,164) && DropColorPointer <= ITEM2(7,169))
		||(DropColorPointer >= ITEM2(8,164) && DropColorPointer <= ITEM2(8,169))
		||(DropColorPointer >= ITEM2(9,164) && DropColorPointer <= ITEM2(9,169))
		||(DropColorPointer >= ITEM2(10,164)&& DropColorPointer <= ITEM2(10,169))
		||(DropColorPointer >= ITEM2(11,164)&& DropColorPointer <= ITEM2(11,169))
		||DropColorPointer == ITEM2(0,42)||DropColorPointer == ITEM2(0,44)
		||DropColorPointer == ITEM2(0,57)||DropColorPointer == ITEM2(0,58)
		||DropColorPointer == ITEM2(2,22)||DropColorPointer == ITEM2(4,28)
		||DropColorPointer == ITEM2(2,27)||DropColorPointer == ITEM2(4,36)
		||DropColorPointer == ITEM2(5,53)||DropColorPointer == ITEM2(5,54)
		||DropColorPointer == ITEM2(5,41)
		||(DropColorPointer >= ITEM2(13,147) && DropColorPointer <= ITEM2(13, 410))
		)
	{
		_asm{
			Mov DropColorPointer,0x005F47AA //Orange
				Jmp DropColorPointer
		}
	}
	else if(DropColorPointer == ITEM2(0,50)
		||DropColorPointer == ITEM2(2,24)
		||DropColorPointer == ITEM2(4,30)
		||DropColorPointer == ITEM2(5,44)
		||DropColorPointer == ITEM2(5,45)
		||DropColorPointer == ITEM2(14,213)
		||DropColorPointer == ITEM2(14,214))
	{
		_asm
		{
			Mov DropColorPointer,0x005F4918 //Divine
			Jmp DropColorPointer
		}
	}
	else if(DropColorPointer == ITEM2(14, 14)
		||DropColorPointer == ITEM2(14, 176)
		||DropColorPointer == ITEM2(14, 177)
		||DropColorPointer == ITEM2(14, 178)
		||DropColorPointer == ITEM2(14, 179)
		||DropColorPointer == ITEM2(14, 211)
		||DropColorPointer == ITEM2(14, 212)
		||DropColorPointer == ITEM2(14, 180)
		||DropColorPointer == ITEM2(14, 181)
		||DropColorPointer == ITEM2(14, 182)
		||DropColorPointer == ITEM2(14, 183)
		||DropColorPointer == ITEM2(14, 184)
		||DropColorPointer == ITEM2(14, 185)
		||DropColorPointer == ITEM2(14, 186)
		||DropColorPointer == ITEM2(14, 187)
		||DropColorPointer == ITEM2(14, 188)
		||DropColorPointer == ITEM2(14, 210)
		)
	{
		_asm
		{
			mov DropColorPointer, 0x005F439E	//yellow
			jmp DropColorPointer
		}
	}
	else
		{
		_asm{
			Mov DropColorPointer,0x005F47BC //next
			Jmp DropColorPointer
		}
	}

}

void Other::CalculateAttackSpeed(lpCharObj lpUser, LPVOID EDX)
{
	pGetAttackSpeed();
	switch(lpUser->Class)
	{ 
		case eClassCode::DarkWizard:
		case eClassCode::SoulMaster: 
		case eClassCode::GrandMaster: 
			{ 
				if( lpUser->AttackSpeed >= 455 && lpUser->AttackSpeed <= 479 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0024700); 
					} 
				else if( lpUser->AttackSpeed >= 605 && lpUser->AttackSpeed <= 636 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0019000); 
					} 
				else if( lpUser->AttackSpeed >= 637 && lpUser->AttackSpeed <= 668 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0018000); 
					} 
				else if( lpUser->AttackSpeed >= 669 && lpUser->AttackSpeed <= 688 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0017000); 
					} 
				else if( lpUser->AttackSpeed >= 855 && lpUser->AttackSpeed <= 1040 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0016300); 
					} 
				else if( lpUser->AttackSpeed >= 1041 && lpUser->AttackSpeed <= 1104 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0015500); 
					} 
				else if( lpUser->AttackSpeed >= 1301 && lpUser->AttackSpeed <= 1500 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0017500); 
					} 
				else if( lpUser->AttackSpeed >= 1501 && lpUser->AttackSpeed <= 1524 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0015000); 
					} 
				else if( lpUser->AttackSpeed >= 1525 && lpUser->AttackSpeed <= 1800 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0014500); 
					} 
				else if( lpUser->AttackSpeed >= 1801 && lpUser->AttackSpeed <= 1999 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0013000); 
					} 
				else if( lpUser->AttackSpeed >= 2000 && lpUser->AttackSpeed <= 2167 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0012500); 
					} 
				else if( lpUser->AttackSpeed >= 2168 && lpUser->AttackSpeed <= 2354 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0011500); 
					} 
				else if( lpUser->AttackSpeed >= 2855 && lpUser->AttackSpeed <= 3011 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0009000); 
					} 
				else if( lpUser->AttackSpeed >= 3011 ) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0008000); 
					} 
				else
					{
						SetDouble(&pFrameSpeed2, 0.0020000); 
					} 
			} 
		break; 
		// ---- 
		case eClassCode::DarkKnight: 
		case eClassCode::BladeKnight: 
		case eClassCode::BladeMaster: 
			{ 
				SetDouble(&pFrameSpeed1, 0.0040000); 
				SetDouble(&pFrameSpeed2, 0.0020000); 
			} 
		break; 
		// ---- 
		case eClassCode::Elf:
		case eClassCode::MuseElf: 
		case eClassCode::HightElf: 
			{ 
				if( lpUser->AttackSpeed >= 509 && lpUser->AttackSpeed <= 549 ) 
					{ 
						SetDouble(&pFrameSpeed1, 0.0037000); 
					} 
				else
					{ 
						SetDouble(&pFrameSpeed1, 0.0040000); 
					} 
			} 
		break; 
		// ---- 
		case eClassCode::MagicGladiator: 
		case eClassCode::DuelMaster: 
			{ 
				if(lpUser->Dexterity >= 5700 && lpUser->Dexterity <= 6550) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0020000); 
					} 
				else if(lpUser->Dexterity >= 8200 && lpUser->Dexterity <= 10700) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0020000); 
					} 
				else if(lpUser->Dexterity >= 13250 && lpUser->Dexterity <= 23250) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0020000); 
					} 
				else if(lpUser->Dexterity >= 28250) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0006000); 
					} 
				else
					{ 
						SetDouble(&pFrameSpeed2, 0.0020000); 
					} 
			} 
		break; 
		// ---- 
		case eClassCode::DarkLord: 
		case eClassCode::LordEmperor: 
			{ 
				if(lpUser->Dexterity >= 2000 && lpUser->Dexterity < 4900) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0038000); 
					} 
				else if(lpUser->Dexterity >= 4900 && lpUser->Dexterity < 5050) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0037000); 
					} 
				else if(lpUser->Dexterity >= 5050 && lpUser->Dexterity < 5200) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0036000); 
					} 
				else if(lpUser->Dexterity >= 5200 && lpUser->Dexterity < 5350) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0035000); 
					} 
				else if(lpUser->Dexterity >= 5350 && lpUser->Dexterity < 5550) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0034000); 
					} 
				else if(lpUser->Dexterity >= 5550 && lpUser->Dexterity < 5700) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0033000); 
					} 
				else if(lpUser->Dexterity >= 5700 && lpUser->Dexterity < 5900) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0032000); 
					} 
				else if(lpUser->Dexterity >= 5900 && lpUser->Dexterity < 6100) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0031000); 
					} 
				else if(lpUser->Dexterity >= 6100 && lpUser->Dexterity < 6300) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0030000); 
					} 
				else if(lpUser->Dexterity >= 6300 && lpUser->Dexterity < 6500) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0029000); 
					} 
				else if(lpUser->Dexterity >= 6500 && lpUser->Dexterity < 6750) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0028000); 
					} 
				else if(lpUser->Dexterity >= 6750 && lpUser->Dexterity < 7000) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0027000); 
					} 
				else if(lpUser->Dexterity >= 7000 && lpUser->Dexterity < 7300) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0026000); 
					} 
				else if(lpUser->Dexterity >= 7300 && lpUser->Dexterity < 7600) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0025000); 
					} 
				else if(lpUser->Dexterity >= 7600 && lpUser->Dexterity < 7900) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0024000); 
					} 
				else if(lpUser->Dexterity >= 7900 && lpUser->Dexterity < 8250) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0023000); 
					} 
				else if(lpUser->Dexterity >= 8250 && lpUser->Dexterity < 8650) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0022000); 
					} 
				else if(lpUser->Dexterity >= 8650 && lpUser->Dexterity < 9050) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0021000); 
					} 
				else if(lpUser->Dexterity >= 9050 && lpUser->Dexterity < 9500) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0020000); 
					} 
				else if(lpUser->Dexterity >= 9500 && lpUser->Dexterity < 10000) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0019000); 
					} 
				else if(lpUser->Dexterity >= 10000 && lpUser->Dexterity < 10550) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0018000); 
					} 
				else if(lpUser->Dexterity >= 10550 && lpUser->Dexterity < 11150) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0017000); 
					} 
				else if(lpUser->Dexterity >= 11150 && lpUser->Dexterity < 11850) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0016000); 
					} 
				else if(lpUser->Dexterity >= 11850 && lpUser->Dexterity < 12600) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0015000); 
					} 
				else if(lpUser->Dexterity >= 12600 && lpUser->Dexterity < 13450) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0014000); 
					} 
				else if(lpUser->Dexterity >= 13450 && lpUser->Dexterity < 16600) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0010000); 
					} 
				else if(lpUser->Dexterity >= 16600) 
					{ 
						SetDouble(&pFrameSpeed2, 0.0008000); 
					} 
				else
					{ 
						SetDouble(&pFrameSpeed2, 0.0040000); 
					} 
			} 
		break; 
	} 
//---------------------------------------------------------------------------
}

std::string lol;
__declspec(naked) void TestRes()
{
	static DWORD a1 = 0x00401C60;
	static DWORD a2 = 0x009CEBF0;
	static DWORD a3 = 0x00401C40;
	static DWORD a4 = 0x0041FE10;

	static DWORD ret = 0x00401FC9;

	static DWORD X;
	static DWORD Y;
	static DWORD nCount;
	static DWORD Text;
	static DWORD Name;

	_asm
	{
		MOV ECX,DWORD PTR SS:[EBP-0x20]
		CALL a1
		ADD EAX,0x1E
		MOV DWORD PTR SS:[EBP-0x38],EAX
		FILD DWORD PTR SS:[EBP-0x38]
		FDIV DWORD PTR DS:[0xE7C3D4]
		CALL a2
		MOv nCount,EAX
		MOV ECX,DWORD PTR SS:[EBP-0x20]
		ADD ECX,0x130
		MOV Text, ECX
		MOV ECX,DWORD PTR SS:[EBP-0x20]
		ADD ECX,0xB0
		MOV Name, ECX
		MOV ECX,DWORD PTR SS:[EBP-0x20]
		CALL a3
		ADD EAX,0x27
		MOV DWORD PTR SS:[EBP-0x3C],EAX
		FILD DWORD PTR SS:[EBP-0x3C]
		FDIV DWORD PTR DS:[0xE7C3D8]
		CALL a2
		MOV Y, EAX
		MOV EDX,DWORD PTR SS:[EBP-0x18]
		SUB EDX,0x0A
		MOV X, EDX
		CALL a4
		MOV ECX,EAX
	}

	int Reset;
	int GReset;

	gCharacterList.GetInfo((char*)Name,&Reset);

	static char test[30];
	sprintf_s(test,sizeof(test),"Reset: %d",Reset);

	lol = (char*)Text;

	pDrawText(pTextThis(),X+5,Y,lol.c_str(),nCount,0,(LPINT)3,0);
	pDrawText(pTextThis(),X+5,Y+7,test,nCount,0,(LPINT)3,0);
	lol.clear();
	_asm{jmp ret}
}

//Mov DropColorPointer,0x005F4918 //Divine
void Other::Load()
{
	//Bypass in terrains files
	SetByte(0x0062EBF8,0xEB);
	SetByte(0x0062EBFE,0xEB);
	SetByte(0x0062EE42,0xEB);
	SetByte(0x0062EE48,0xEB);
	SetByte(0x0062EEEB,0xEB);
	SetByte(0x0062EEE5,0xEB);
	//Bypass in .bmd files
	SetByte(0x007E363F,0xEB);
	SetByte(0x004AD9D9,0xEB);
	SetByte(0x004E8A36,0xEB);
	SetByte(0x004E8C26,0xEB);
	SetByte(0x00589650,0xEB);
	SetByte(0x00589A00,0xEB);
	SetByte(0x0058A499,0xEB);
	SetByte(0x0058B2A0,0xEB);
	SetByte(0x0062EBFE,0xEB);
	SetByte(0x0062EE48,0xEB);
	SetByte(0x0062EEEB,0xEB);
	SetByte(0x007E3851,0xEB);
	SetByte(0x007E3A71,0xEB);
	SetByte(0x0081960A,0xEB);
	SetByte(0x0081981A,0xEB);
	SetByte(0x0082B5CC,0xEB);
	//SetOp((LPVOID)0x00559539, (LPVOID)this->CalculateAttackSpeed, ASM::CALL);

	//SetOp((LPVOID)0x008337B0, (LPVOID)pSub_836510, ASM::CALL);
	//SetOp((LPVOID)0x0083443C, (LPVOID)pSub_836510, ASM::CALL);

	//SetRange((LPVOID)0x005F479E, 10, ASM::NOP);
	//SetOp((LPVOID)0x005F479E, (LPVOID)DropColor, ASM::JMP);

	//SetRange((LPVOID)0x0060EE95, 10, ASM::NOP);
	//SetOp((LPVOID)0x0060EE95, (LPVOID)FixWingsExcellentGlow, ASM::JMP);
	SetByte((PVOID)(0x004030D1 + 3),gProtect.m_MainInfo.CharacterCount); // Create character max chars (default: 7)
	SetRange((LPVOID)0x0096818F,7,ASM::NOP);
	SetOp((LPVOID)0x0096818F,(LPVOID)RemoveSocket,ASM::JMP);
	//0x005BF700 //-> Item tool tip
	static char* LogName	= "Logs\\Error.log";
	static char* LogName2	= "Logs\\Error_%d.log";
	static char* DumpName	= "Logs\\Error.dmp";
	SetDword((PVOID)(0x0096AA48+1), (DWORD)LogName);
	SetDword((PVOID)(0x0096AACF+1), (DWORD)LogName);
	SetDword((PVOID)(0x0096AB5B+1), (DWORD)LogName2);
	SetDword((PVOID)(0x004D1D0B+1), (DWORD)DumpName);
	SetByte((PVOID)(0x007AF175 + 1),9); //-> max zen length
	SetByte((PVOID)(0x007AF415 + 1),9); //-> max zen length
	SetByte((PVOID)(0x007AF795 + 1),9); //-> max zen length
	SetByte((PVOID)(0x007B0315 + 1),9); //-> max zen length
	SetOp((LPVOID)0x005847FE,(LPVOID)gMakePreviewSoldierElf,ASM::CALL);
//	SetWord((PVOID)(0x0057FCCF+1),0x1D47);
	//SetByte(oCharColor_Loot, 8);
	//SetFloat(0x0D27B1C,500.000); //-> Camera Range
	//SetByte((PVOID)(0x00649E24 + 3), 14);	//-> 1 Method //-> Speed bug fix
	//SetByte((PVOID)(0x00556C32 + 6), 2);	//-> 2 Method //-> Speed bug fix
	//SetRange((LPVOID)0x006505FB,0x4,ASM::NOP); //-> Siege minimap fix
	//-
	//SetRange((LPVOID)0x007E4DAD,6,ASM::NOP);
	//SetOp((LPVOID)0x007E4DAD,(LPVOID)NewWingPercents,ASM::JMP);
	if(gConfig.m_LoginTheme == 1)
	{
		SetByte((LPVOID)(0x004D75EA + 6), 62); //-> select server
	}
	//SetNop(0x005C8411,0x10);	//-> Disable ResourceGuard Call
	//SetByte(0x007E363F,0xEB);   //-> Bypass in Local folder text .bmd files
	SetOp((LPVOID)0x008348BC,this->IsExpensiveItem,ASM::CALL);
	SetOp((LPVOID)0x0084790C,this->IsExpensiveItem,ASM::CALL);
	//SetCompleteHook(0xE8,0x004E0728,&this->DrawItemNumber);
	//SetCompleteHook(0xE8,0x004E0B4B,&this->DrawItemNumber);
	//SetCompleteHook(0xE8,0x0058E629,&this->DrawItemNumber);
	//SetCompleteHook(0xE8,0x005C405E,&this->DrawItemNumber);
	//SetCompleteHook(0xE8,0x005C867F,&this->DrawItemNumber);
	//SetCompleteHook(0xE8,0x007DCE64,&this->DrawItemNumber);
	//SetCompleteHook(0xE8,0x008660C5,&this->DrawItemNumber);

	SetOp((LPVOID)0x00830BA6,this->MoveListInit,ASM::CALL);
	SetOp((LPVOID)0x00832ED8,this->MoveListInit,ASM::CALL);

	//SetByte((PVOID)(0x004E8CA4+6),76);
	//SetByte((PVOID)(0x00599238 + 3), 0x28); //Chat Long

	//Remove Effect Static
	if(gConfig.EffectStatic == 0)
	{
		MemorySet(0x00771310,0x90,0x11E);
	}
	//Remove Effect Dynamic
	if(gConfig.EffectDynamic == 0)
	{
		MemorySet(0x0074CD30,0x90,0x10C50);
	}
	//Remove Effect Skill
	if(gConfig.EffectSkill == 0)
	{
		MemorySet(0x00626190,0x90,0x2FE2);
	}
	//Remove Efeect Skill 2
	if(gConfig.EffectSkill2 == 0)
	{
		MemorySet(0x0072D1B0,0x90,0x87A2);
	}

	this->InitOGLHook();
	this->UnlockCastleSkills();
}
#ifdef OldFix
void Other::RamFix(LPVOID lpThreadParameter)
{
	HANDLE v1;
	HANDLE v2;
	while ( 1 )
	{
		Sleep(5000);
		v1 = GetCurrentProcess();
		SetProcessWorkingSetSize(v1, 0xFFFFFFFF, 0xFFFFFFFF);
		v2 = GetCurrentProcess();
		SetThreadPriority(v2, -2);
	}
}
#endif