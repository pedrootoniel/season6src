#include "stdafx.h"
#include "ChatWindow.h"
#include "Defines.h"
#include "offset.h"
#include "Config.h"
#include "Util.h"
#include "InfoLog.h"
#include "Object.h"
#include "User.h"
#include "Interface.h"
#include "HealthBar.h"
#include "TMemory.h"
#include "TrayMode.h"
#include "Protect.h"
// ----------------------------------------------------------------------------------------------

ChatExpanded	gChatExpanded;
// ----------------------------------------------------------------------------------------------

Naked(FixSysMsg1)
{
	__asm
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg1_FALSE
		_true:
		pop eax
		jmp FixSysMsg1_TRUE
	}
}
// ----------------------------------------------------------------------------------------------

Naked(FixSysMsg2)
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg2_FALSE
		_true:
		pop eax
		jmp FixSysMsg2_TRUE
	}
}
// ----------------------------------------------------------------------------------------------

Naked(FixSysMsg3)
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg3_FALSE
		_true:
		pop eax
		jmp FixSysMsg3_TRUE
	}
}
// ----------------------------------------------------------------------------------------------
//
//Naked(Test00)
//{
//	static DWORD Jump = 0x00788B97;
//	static MUChat* Pointer;
//
//	__asm
//	{
//		MOVZX ECX,BYTE PTR DS:[EAX+0x158];
//		MOV Pointer, EAX;
//	}
//
//	////console.Log("","PosY = %d | %d",Pointer->WindowPosY, Pointer->WindowPosX);
//	////console.Log("","Type = %d|%d|%d|%d", Pointer->Unknown0,Pointer->Unknown1,Pointer->Unknown2,Pointer->Unknown3);
//
//	__asm
//	{
//		JMP Jump;
//	}
//}
//
//DWORD Buff3 = 0;
//DWORD Bufff = 0x00788BDD;
////char* Pointer[352];
////DWORD Pointer;
//char * text;
//Naked(Test0)
//{
//	__asm
//	{
//		MOV EDX,DWORD PTR SS:[EBP-0x24];
//		ADD EDX,1;
//		MOV DWORD PTR SS:[EBP-0x24],EDX;
//		MOV EAX,DWORD PTR SS:[EBP-0x28];
//		ADD EAX,1;
//		MOV DWORD PTR SS:[EBP-0x28],EAX;
//		MOV Buff3, EDX;
//		//MOV Pointer, [EAX+0x13C];
//		//MOVZX Pointer,BYTE PTR DS:[EAX+0x140]
//	//	MOV Pointer, EAX;
//	}
//
//	/*for (int i=0;i<10;i++)
//	{
//		////console.Log("","IsActive [%d] = %d",i,*(bool*)(Pointer+256));
//	}*/
//	//MUChat* chat;
//
//	//memcpy(&chat,Pointer,sizeof(Pointer));
//	////console.Log("","linecount = %d",(DWORD)Pointer[320]);
//	//for (int i=0;i<+10;i++)
//	//{
//	//	//console.Log("","[%d] = %d size = %d",i, Pointer.IsActiveChatType[i],sizeof(Pointer));
//	//}
//
//	////console.Log("","%d",Pointer.MessageType);
//	////console.Log("","i = %d length = %d", Buff3,ChatBoxMuObjectChatDataPtrArrayLength);
//	/*text = ChatBoxMuObjectChatDataPtrArray[0]->message();
//	//console.Log("",text);*/
//
//	__asm
//	{
//		JMP Bufff;
//	}
//}
//DWORD Buff = 0;
//DWORD Buff1 = 0x00788F25;
//DWORD Buff2 = 0x00788F29;
//
//
//int lol = 0;
//
//Naked(Test)
//{
//	/*__asm
//	{
//		MOV ECX,DWORD PTR SS:[EBP-0x2C];
//		MOV Buff, 0x0078C050;
//		CALL Buff;
//		MOV Buff3, EAX;
//	}*/
//
//	/*__asm
//	{
//		MOV Buff3, [EBP-0x24];
//	}*/
//
//	////console.Log("","i = %d", Buff3);
//
//	////console.Log("","THIS IS CHAT TEXT!1 [%d]",Buff3);
//
//	//for (int i=0;i<ChatBoxMuObjectChatDataPtrArrayLength;i++)
//	//{
//	//	char * text = ChatBoxMuObjectChatDataPtrArray[i]->message();
//	//	if (text[0] == '[' && text[1] == 'P' && text[2] == 'O' && text[3] == 'S' && text[4] == 'T' && text[5] == ']')
//	//	{
//	//		lol = 1;
//	//		
//	//	}
//	//	////console.Log("",text);
//	//}
//
//	if (lol == 0)
//	{
//		__asm
//		{
//			MOV ECX,DWORD PTR SS:[EBP-0x2C];
//			MOV Buff, 0x0078C050;
//			CALL Buff;
//			CMP EAX,0x9;
//			JNZ SHORT Buff1;
//			PUSH 0x0FF;
//			PUSH 0;
//			PUSH 0;
//			PUSH 0;
//			MOV Buff, 0x0041FE10;
//			CALL Buff;
//			MOV ECX,EAX;
//			MOV Buff, 0x00420040;
//			CALL Buff;
//			PUSH 0x0C8;
//			PUSH 0x0E9;
//			PUSH 0x0E6;
//			PUSH 0x0E6;
//			MOV Buff, 0x0041FE10;
//			CALL Buff;
//			MOV ECX,EAX;
//			MOV Buff, 0x004200B0;
//			CALL Buff;
//			JMP Buff2;
//		}
//	}
//	else
//	{
//		__asm
//		{
//			MOV ECX,DWORD PTR SS:[EBP-0x2C];
//			MOV Buff, 0x0078C050;
//			CALL Buff;
//			CMP EAX,0x9;
//			JNZ SHORT Buff1;
//			PUSH 0x0FF;
//			PUSH 0;
//			PUSH 0;
//			PUSH 0;
//			MOV Buff, 0x0041FE10;
//			CALL Buff;
//			MOV ECX,EAX;
//			MOV Buff, 0x00420040;
//			CALL Buff;
//			PUSH 0x0FF;
//			PUSH 0x000;
//			PUSH 0x000;
//			PUSH 0x0FF;
//			MOV Buff, 0x0041FE10;
//			CALL Buff;
//			MOV ECX,EAX;
//			MOV Buff, 0x004200B0;
//			CALL Buff;
//			JMP Buff2;
//		}
//	}
//
//	/*__asm
//	{
//		MOV ECX,DWORD PTR SS:[EBP-0x2C];
//		MOV Buff, 0x0078C050;
//		CALL Buff;
//		CMP EAX,0xA;
//		JNZ SHORT Buff1;
//		PUSH 0x0FF;
//		PUSH 0;
//		PUSH 0;
//		PUSH 0;
//		MOV Buff, 0x0041FE10;
//		CALL Buff;
//		MOV ECX,EAX;
//		MOV Buff, 0x00420040;
//		CALL Buff;
//		PUSH 0x0C8;
//		PUSH 0x0E9;
//		PUSH 0x0E6;
//		PUSH 0x0E6;
//		MOV Buff, 0x0041FE10;
//		CALL Buff;
//		MOV ECX,EAX;
//		MOV Buff, 0x004200B0;
//		CALL Buff;
//		JMP Buff2;
//
//		TESTES:
//		MOV ECX,DWORD PTR SS:[EBP-0x2C];
//		MOV Buff, 0x0078C050;
//		CALL Buff;
//		CMP EAX,0x9;
//		JNZ SHORT Buff1;
//		PUSH 0x0FF;
//		PUSH 0;
//		PUSH 0;
//		PUSH 0;
//		MOV Buff, 0x0041FE10;
//		CALL Buff;
//		MOV ECX,EAX;
//		MOV Buff, 0x00420040;
//		CALL Buff;
//		PUSH 0x0FF;
//		PUSH 0x000;
//		PUSH 0x000;
//		PUSH 0x0FF;
//		MOV Buff, 0x0041FE10;
//		CALL Buff;
//		MOV ECX,EAX;
//		MOV Buff, 0x004200B0;
//		CALL Buff;
//		JMP Buff2;
//	}*/
//
//	/*__asm
//	{
//		JMP Buff2;
//	}*/
//}
//
//DWORD RetOffset = 0x0078B83B;
//Naked(Test1)
//{
//	__asm
//	{
//		MOV EAX,DWORD PTR SS:[EBP-0x4]
//		ADD EAX,0x0E8
//		JMP RetOffset
//		MOV EAX,DWORD PTR SS:[EBP-0x4]
//		ADD EAX,0x0E8
//		JMP RetOffset
//	}
//}
//
//MUChatType ChatExpanded::Test2(MUChat* This, int a2)
//{
//	  MUChatType* result; // eax@2
//	////console.Log("","a2 = %d",This->MessageType);
//
//	if (This->MessageType >= 0 && This->MessageType <=9)
//	{
//		return This->ChatType[4];
//	}
//	
//  //switch ( a2 )
//  //{
//  //  case 0:
//	 // result = &This->ChatType[0];
//  //    //result = (char *)This + 16;
//  //    break;
//  //  case 1:
//	 // result = &This->ChatType[1];
//  //    //result = (char *)This + 40;
//  //    break;
//  //  case 2:
//	 // result = &This->ChatType[2];
//  //    //result = (char *)This + 64;
//  //    break;
//  //  case 3:
//	 // result = &This->ChatType[6];
//  //    //result = (char *)This + 160;
//  //    break;
//  //  case 4:
//	 //  result = &This->ChatType[7];
//  //    //result = (char *)This + 184;
//  //    break;
//  //  case 5:
//	 // result = &This->ChatType[3];
//  //    //result = (char *)This + 88;
//  //    break;
//  //  case 6:
//	 // result = &This->ChatType[4];
//  //    //result = (char *)This + 112;
//  //    break;
//  //  case 7:
//	 // result = &This->ChatType[5];
//  //    //result = (char *)This + 136;
//  //    break;
//  //  case 8:
//	 //  result = &This->ChatType[8];
//  //    //result = (char *)This + 208;
//  //    break;
//  //  case 9:
//	 //  result = &This->ChatType[9];
//  //    //result = (char *)This + 232;
//  //    break;
//  //  default:
//  //    result = 0;
//  //    break;
//  //}
//  //return result;
////	return 0;
//}
//
//



bool __fastcall ShowChatMessage(MUChat* This)
{

	return pShowChatMessage(This);
}

int __cdecl PkLevelRecv(PMSG_PK_LEVEL_SEND *lpMsg)
{
	lpViewObj lpObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(),  pGetViewportByIndex(lpMsg->index[1] + (lpMsg->index[0] << 8)));
	//g_Console.AddMessage(5,"%s",lpObj->Name);
	if (strcmp(lpObj->Name,gObjUser.lpPlayer->Name) != 0)
	{
		gInfoLog.Output(LOG_KILLERS, "[KILL] [%s] %s",gObjUser.lpPlayer->Name,lpObj->Name);
	}
	return pPkLevelRecv(lpMsg);
}

int __cdecl WhisperMessageRecv(PMSG_CHAT_SEND* lpMsg)
{
	if( gTrayMode.InTray )
	{
		char Text[200];
		sprintf(Text,"[%s] %s",lpMsg->name,lpMsg->message);
		gTrayMode.ShowMessage(NIIF_INFO, gProtect.m_MainInfo.WindowName, Text);
	}
	if (lpMsg->message[0] == '[' && lpMsg->message[1] == 'P' && lpMsg->message[2] == 'O' && lpMsg->message[3] == 'S' && 
		lpMsg->message[4] == 'T' && lpMsg->message[5] == ']')
	{
		gInfoLog.Output(LOG_CHAT, "[POST] [%s] %s",lpMsg->name,lpMsg->message+5);
	}
	else
	{
		gInfoLog.Output(LOG_CHAT, "[PRIVATE] [%s] %s",lpMsg->name,lpMsg->message);
	}

	return pWhisperMessageRecv(lpMsg);
}

int __cdecl MessageRecv(PMSG_CHAT_SEND* lpMsg)
{
	if (*(DWORD*)(MAIN_SCREEN_STATE) != ObjState::SelectServer)
	{
		if (strlen(lpMsg->name) != 0)
		{
			if (lpMsg->message[0] == '[' && lpMsg->message[1] == 'P' && lpMsg->message[2] == 'O' && lpMsg->message[3] == 'S' && 
				lpMsg->message[4] == 'T' && lpMsg->message[5] == ']')
			{
				gInfoLog.Output(LOG_CHAT, "[POST] [%s] %s",lpMsg->name,lpMsg->message);
			}
			else if (lpMsg->message[0] == '~') // Party
			{
				gInfoLog.Output(LOG_CHAT, "[PARTY] [%s] %s",lpMsg->name,lpMsg->message);
			}
			else if (lpMsg->message[0] == '@') // Guild
			{
				if (lpMsg->message[1] == '@') // Alliance
				{
					gInfoLog.Output(LOG_CHAT, "[ALLIANCE] [%s] %s",lpMsg->name,lpMsg->message);
				}
				else
				{
					gInfoLog.Output(LOG_CHAT, "[GUILD] [%s] %s",lpMsg->name,lpMsg->message);
				}
			}
			else if (lpMsg->message[0] == '&') // Gens
			{
				gInfoLog.Output(LOG_CHAT, "[Gens] [%s] %s",lpMsg->name,lpMsg->message);
			}
			else
			{
				gInfoLog.Output(LOG_CHAT, "[STANDART] [%s] %s",lpMsg->name,lpMsg->message);
			}
		}
	}
	return pMessageRecv(lpMsg);
}

__declspec(naked) void CheckLol() // OK
{
	static DWORD mem = 0x00788C9F;
	static DWORD mem1 = 0x00788C66;
	static DWORD ItemID;

	__asm
	{
		MOV ItemID, EAX
	}

	//g_Console.AddMessage(5,"Type = %d",ItemID);

	__asm
	{
		CMP EAX,2
		JMP mem
		JMP mem1
	}
}

__declspec(naked) void SetChatTextType()
{
	static DWORD ret = 0x00788F29;
	static int textType;

	__asm
	{
		mov textType, EAX
	}

	gChatExpanded.m_Lua.Generic_Call("MakeText","i",textType);

	__asm
	{
		JMP ret;
	}
}

#define sub_7865E0_Addr		((int(__thiscall*)(int This)) 0x7865E0)

char sub_7865E0(int This, LPVOID EDX)
{
	//, LPVOID EDX
	return sub_7865E0_Addr(This);
}


std::string quest;
size_t pos;
std::string s;
__declspec(naked) void ChangeSystemColor()
{
	static DWORD ret = 0x007890F2;
	static DWORD addr0 = 0x0078C030;
	static DWORD addr1 = 0x00402880;

	static DWORD text;
	static DWORD X;
	static DWORD Y;

	__asm
	{
		MOV ECX,DWORD PTR SS:[EBP-0x2C]
		CALL addr0
		MOV ECX,EAX
		CALL addr1
		MOV text,EAX
		MOV ECX,DWORD PTR SS:[EBP-0x34]
		MOV Y, ECX
		MOV EDX,DWORD PTR SS:[EBP-0x38]
		MOV X, EDX
	}

	quest = "[Quest]";
	s = (char*)text;
	pos = s.find(quest);
	if (pos != std::string::npos)
	{
		gChatExpanded.m_Lua.Generic_Call("MakeText","i",11);
	}

	pDrawText(pTextThis(), (int)X, (int)Y, /*s.c_str()*/(char*)text, 0, 0, (LPINT)1, 0);
	s.clear();
	__asm
	{
		jmp ret
	}
}

std::string post;

__declspec(naked) void ChangePostColor()
{
	static DWORD ret = 0x007890A9;
	static DWORD addr1 = 0x00402880;
	static DWORD addr2 = 0x0041FE10;
	static DWORD addr3 = 0x00420150;

	static DWORD text;
	static DWORD X;
	static DWORD Y;

	__asm
	{
		LEA ECX,DWORD PTR SS:[EBP-0x54]
		CALL addr1
		MOV text,EAX
		MOV EDX,DWORD PTR SS:[EBP-0x34]
		MOV Y, EDX
		MOV EAX,DWORD PTR SS:[EBP-0x38]
		MOV X, EAX
	}

	post = "[POST]";
	s = (char*)text;
	pos = s.find(post);
	if (pos != std::string::npos)
	{
		
		gChatExpanded.m_Lua.Generic_Call("MakeText","i",10);
		/*std::string::size_type i = s.find(post);
		if (i != std::string::npos)
		{
			s.erase(i, post.length()+1);
		}*/
	}	

	pDrawText(pTextThis(), (int)X, (int)Y, /*s.c_str()*/(char*)text, 0, 0, (LPINT)1, 0);
	s.clear();
	__asm
	{
		jmp ret
	}
}


void ChatExpanded::Load()
{
	//Убераем эффект при нажатии на карту
	//SetDword(0x005B768A+1,0x0);
	//SetDword(0x005B7707+1,0x0);
	this->isFirstLoad = true;
	this->m_Lua.DoFile("Data\\Custom\\Scripts\\ChatWindow.lua");

	MemorySet(0x007890C6,0x90,0x2C);
	SetCompleteHook(0xE9,0x007890C6,&ChangeSystemColor);

	MemorySet(0x00789084,0x90,0x25);
	SetCompleteHook(0xE9,0x00789084,&ChangePostColor);

	MemorySet(0x00788C66,0x90,0x33);
	SetCompleteHook(0xE9,0x00788C66,&SetChatTextType);

	MemorySet(0x00788CAC,0x90,0x33);
	SetCompleteHook(0xE9,0x00788CAC,&SetChatTextType);

	MemorySet(0x00788CF2,0x90,0x30);
	SetCompleteHook(0xE9,0x00788CF2,&SetChatTextType);

	MemorySet(0x00788D35,0x90,0x36);
	SetCompleteHook(0xE9,0x00788D35,&SetChatTextType);

	MemorySet(0x00788D7E,0x90,0x33);
	SetCompleteHook(0xE9,0x00788D7E,&SetChatTextType);

	MemorySet(0x00788DC4,0x90,0x33);
	SetCompleteHook(0xE9,0x00788DC4,&SetChatTextType);

	MemorySet(0x00788E0A,0x90,0x33);
	SetCompleteHook(0xE9,0x00788E0A,&SetChatTextType);

	MemorySet(0x00788E50,0x90,0x33);
	SetCompleteHook(0xE9,0x00788E50,&SetChatTextType);

	MemorySet(0x00788E96,0x90,0x46);
	SetCompleteHook(0xE9,0x00788E96,&SetChatTextType);

	MemorySet(0x00788EEC,0x90,0x36);
	SetCompleteHook(0xE9,0x00788EEC,&SetChatTextType);

	//this->IsActive = true;
	SetOp3(oShowChatMessage_Call, (LPVOID)this->ShowChatMessage, ASM::CALL);

	SetCompleteHook(0xE8,0x663B20+0x5AC,&MessageRecv);

	SetCompleteHook(0xE8,0x663B20+0x5CE,&WhisperMessageRecv);

	SetCompleteHook(0xE8,0x663B20+0x423,&PkLevelRecv);	

	if (gConfig.m_SeparateChat)
	{
		SetOp3(FixSysMsg1_Hook, FixSysMsg1, ASM::JMP);
		SetOp3(FixSysMsg2_Hook, FixSysMsg2, ASM::JMP);
		SetOp3(FixSysMsg3_Hook, FixSysMsg3, ASM::JMP);

		/*SetOp3(0x00788AEF,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078963E,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078984C,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x00789B82,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x00789E97,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x00789FA3,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078A040,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078A110,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078A1D0,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078A226,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078A94E,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078B13E,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078B891,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078B8FF,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078B97A,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078BA45,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078BAF5,(LPVOID)this->Test2,ASM::CALL);
		SetOp3(0x0078BAF5,(LPVOID)this->Test2,ASM::CALL);*/

		/*Local calls from 00788AEF, 0078963E, 0078984C, 00789B82, 00789E97, 00789FA3, 0078A040, 0078A110,
		 * 0078A1D0, 0078A226, 0078A94E, 0078B13E, 0078B891, 0078B8FF, 0078B97A, 0078BA45, 0078BAF5
*/
		//SetOp3(0x00788B90, Test00, ASM::JMP); // цвет текста
		// SetOp3(0x00788BCB, Test0, ASM::JMP); // цвет текста (основа, выбор цвета для 9 типа)
		//SetOp3(0x00788EDF, Test, ASM::JMP);
		//SetByte(0x0078B7CF+3,10);
		//SetOp3(0x0078B82F, Test1, ASM::JMP);
	}
}
// ----------------------------------------------------------------------------------------------

void ChatExpanded::SetInstance(LPVOID Instance)
{
	this->Instance			= Instance;
	this->PosYBuff			= this->GetPosY();
	this->HeightBuff		= this->GetHeight();
	this->MessageCountBuff	= this->GetMessageCount();
	this->MessageTypeBuff	= this->GetMessageType();
	this->ScrollPosBuff		= this->GetScrollPos();
	//this->LineCountBuff		= this->GetLineCount();

	//g_Console.AddMessage(5,"ScrollPos = %d",this->ScrollPosBuff);
	//g_Console.AddMessage(5,"LineCount = %d",this->LineCountBuff);

	//if (this->LineCountBuff == 3)
	//{
	//	this->LineCountBuff=4;
	//}
	//else if (this->LineCountBuff == 6)
	//{
	//	this->LineCountBuff=8;
	//}
	//else if (this->LineCountBuff == 9)
	//{
	//	this->LineCountBuff=13;
	//}
	//else if (this->LineCountBuff == 15)
	//{
	//	this->LineCountBuff=22;
	//}

	//if (this->isFirstLoad==true)
	//{
	//	this->LineCountBuff=22;
	//	//this->LineCountBuff+=7;
	//	//this->PosYBuff+=60;
	//	this->isFirstLoad = false;
	//}
	/*else
	{
		if (this->LineCountBuff==3)
		{
			this->LineCountBuff = 5;
		}
		else if (this->LineCountBuff == 6)
		{
			this->LineCountBuff = 10;
		}
		else if (this->LineCountBuff == 9)
		{
			this->LineCountBuff = 14;
		}
		else if (this->LineCountBuff == 12)
		{
			this->LineCountBuff = 20;
		}
		else if (this->LineCountBuff == 15)
		{
			this->LineCountBuff = 22;
		}
		else
		{
			this->LineCountBuff = 5;
		}
	}*/
}
// ----------------------------------------------------------------------------------------------

void ChatExpanded::Restore()
{
	this->SetPosY(this->PosYBuff);
	this->SetHeight(this->HeightBuff);
	this->SetMessageCount(this->MessageCountBuff);
	this->SetMessageType(this->MessageTypeBuff);
	this->SetScrollPos(this->ScrollPosBuff);
	//this->SetLineCount(this->LineCountBuff);
}
// ----------------------------------------------------------------------------------------------

void ChatExpanded::Switch()
{
	if( gConfig.m_SeparateChat )
	{
		SetOp3(FixSysMsg1_Hook, FixSysMsg1, ASM::JMP);
		SetOp3(FixSysMsg2_Hook, FixSysMsg2, ASM::JMP);
		SetOp3(FixSysMsg3_Hook, FixSysMsg3, ASM::JMP);
		//gChatExpanded.IsActive = true;
	}
	else
	{
		SetOp3(FixSysMsg1_Hook, (LPVOID)oNewCall, ASM::CALL);
		SetOp3(FixSysMsg2_Hook, (LPVOID)oNewCall, ASM::CALL);
		SetOp3(FixSysMsg3_Hook, (LPVOID)oNewCall, ASM::CALL);
		//gChatExpanded.IsActive = false;
	}
}
// ----------------------------------------------------------------------------------------------

bool ChatExpanded::ShowChatMessage(LPVOID This, LPVOID EDX)
{
	if( !gConfig.m_SeparateChat )
	{
		return pShowChatMessage(This);
	}
	////console.Log("","ShowChatMessge");
	// ----
	gChatExpanded.SetInstance(This);
	gChatExpanded.SetPosY(172);
	gChatExpanded.SetHeight(100);
	gChatExpanded.SetMessageCount(4);
	pSetChatMessageType(This, 3);
	pShowChatMessage(This);
	gChatExpanded.Restore();
	return pShowChatMessage(This);
}
//// ----------------------------------------------------------------------------------------------

//#include "Util.h"

//

//
//DWORD ChatValueMessageType;
//DWORD ChatValueMessagePosition;
//DWORD ChatValueMessageHeight;
//DWORD ChatValueMessageCount;
//DWORD ChatValueMessageScroll;
//
//void InitChatWindow() // OK
//{
//	SetCompleteHook(0xE9,0x0078B0BC,&ChatWindowDisplay);
//
//	SetCompleteHook(0xE9,0x00789765,&ChatWindowMessage1);
//
//	SetCompleteHook(0xE9,0x00789A61,&ChatWindowMessage2);
//
//	SetCompleteHook(0xE9,0x00789DAA,&ChatWindowMessage3);
//
//	SetCompleteHook(0xE8,0x663B20+0x5AC,&MessageRecv);
//
//	SetCompleteHook(0xE8,0x663B20+0x5CE,&WhisperMessageRecv);
//
//	SetCompleteHook(0xE8,0x663B20+0x423,&PkLevelRecv);
//
//	//SetOp3(oShowChatMessage_Call, (LPVOID)ShowChatMessage, ASM::CALL);
//}
//
//__declspec(naked) void ChatWindowDisplay() // OK
//{
//	static DWORD ChatWindowDisplayAddress1 = 0x0078B8C0;
//	static DWORD ChatWindowDisplayAddress2 = 0x0078B870;
//	static DWORD ChatWindowDisplayAddress3 = 0x00788A80;
//	static DWORD ChatWindowDisplayAddress4 = 0x0078B0C1;
//
//	__asm
//	{
//		Call [ChatWindowDisplayAddress1]
//		Mov ChatValueMessageType,Eax
//		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
//		Mov Eax,Dword Ptr Ds:[Ecx+0x128]
//		Mov ChatValueMessagePosition,Eax
//		Mov Eax,Dword Ptr Ds:[Ecx+0x138]
//		Mov ChatValueMessageHeight,Eax
//		Mov Eax,Dword Ptr Ds:[Ecx+0x13C]
//		Mov ChatValueMessageCount,Eax
//		Mov Eax,Dword Ptr Ds:[Ecx+0x148]
//		Mov ChatValueMessageScroll,Eax
//		Mov Dword Ptr Ds:[Ecx+0x128],0xBA
//		Mov Dword Ptr Ds:[Ecx+0x138],0x64
//		Mov Dword Ptr Ds:[Ecx+0x13C],0x04
//		Push 0x03
//		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
//		Call [ChatWindowDisplayAddress2]
//		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
//		Call [ChatWindowDisplayAddress3]
//		Push ChatValueMessageType
//		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
//		Call [ChatWindowDisplayAddress2]
//		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
//		Mov Eax,ChatValueMessagePosition
//		Mov Dword Ptr Ds:[Ecx+0x128],Eax
//		Mov Eax,ChatValueMessageHeight
//		Mov Dword Ptr Ds:[Ecx+0x138],Eax
//		Mov Eax,ChatValueMessageCount
//		Mov Dword Ptr Ds:[Ecx+0x13C],Eax
//		Mov Eax,ChatValueMessageScroll
//		Mov Dword Ptr Ds:[Ecx+0x148],Eax
//		Mov Ecx,Dword Ptr Ss:[Ebp-0x04]
//		Call [ChatWindowDisplayAddress3]
//		Jmp [ChatWindowDisplayAddress4]
//	}
//}
//
//__declspec(naked) void ChatWindowMessage1() // OK
//{
//	static DWORD ChatWindowMessageAddress1 = 0x00789824;
//	static DWORD ChatWindowMessageAddress2 = 0x009D00C5;
//	static DWORD ChatWindowMessageAddress3 = 0x0078976C;
//
//	__asm
//	{
//		Cmp Dword Ptr Ss:[Ebp+0x10],0x03
//		Jnz EXIT
//		Mov Dword Ptr Ss:[Ebp-0x94],0x00
//		Jmp [ChatWindowMessageAddress1]
//		EXIT:
//		Push 0x40
//		Call [ChatWindowMessageAddress2]
//		Jmp [ChatWindowMessageAddress3]
//	}
//}
//
//__declspec(naked) void ChatWindowMessage2() // OK
//{
//	static DWORD ChatWindowMessageAddress1 = 0x00789B5A;
//	static DWORD ChatWindowMessageAddress2 = 0x009D00C5;
//	static DWORD ChatWindowMessageAddress3 = 0x00789A68;
//
//	__asm
//	{
//		Cmp Dword Ptr Ss:[Ebp+0x10],0x03
//		Jnz EXIT
//		Mov Dword Ptr Ss:[Ebp-0xE4],0x00
//		Jmp [ChatWindowMessageAddress1]
//		EXIT:
//		Push 0x40
//		Call [ChatWindowMessageAddress2]
//		Jmp [ChatWindowMessageAddress3]
//	}
//}
//
//__declspec(naked) void ChatWindowMessage3() // OK
//{
//	static DWORD ChatWindowMessageAddress1 = 0x00789E6F;
//	static DWORD ChatWindowMessageAddress2 = 0x009D00C5;
//	static DWORD ChatWindowMessageAddress3 = 0x00789DB1;
//
//	__asm
//	{
//		Cmp Dword Ptr Ss:[Ebp+0x10],0x03
//		Jnz EXIT
//		Mov Dword Ptr Ss:[Ebp-0x154],0x00
//		Jmp [ChatWindowMessageAddress1]
//		EXIT:
//		Push 0x40
//		Call [ChatWindowMessageAddress2]
//		Jmp [ChatWindowMessageAddress3]
//	}
//}
