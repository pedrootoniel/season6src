#include "stdafx.h"
#include "Inter3.h"
#include "Defines.h"
#include "TMemory.h"
#include "LicenseInfo.h"
#include "Interface.h"
__declspec(naked) void AGPosition()
{
	static float AGPositionW = 13.0f;
	static float AGPositionH = 39.0f;
	static float AGPositionX = 552.0f;
	static float AGPositionY = 435.0f;
	static DWORD AGPosition_buff = 0x008102AD;
	_asm
	{
	FLD DWORD PTR DS : [AGPositionW]
	FSTP DWORD PTR SS : [EBP - 0x18]
	FLD DWORD PTR DS : [AGPositionH]
	FSTP DWORD PTR SS : [EBP - 0x14]
	FLD DWORD PTR DS : [AGPositionX]
	FSTP DWORD PTR SS : [EBP - 0x10]
	FLD DWORD PTR DS : [AGPositionY]
	FSTP DWORD PTR SS : [EBP - 0x0C]
	jmp[AGPosition_buff]
	}
}
__declspec(naked) void SDPosition()
{
	static float SDPositionW = 14.0f;
	static float SDPositionH = 39.0f;
	static float SDPositionX = 73.0f;
	static float SDPositionY = 435.0f;
	static DWORD SDPosition_buff = 0x0081057D;
	_asm
	{	
	FLD DWORD PTR DS:[SDPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[SDPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	FLD DWORD PTR DS:[SDPositionX]
	FSTP DWORD PTR SS:[EBP-0x10]
	FLD DWORD PTR DS:[SDPositionY]
	FSTP DWORD PTR SS:[EBP-0x0C] 
	jmp [SDPosition_buff]
	}
}
__declspec(naked) void MANAPosition()
{
	static float MANAPositionW = 52.0f;
	static float MANAPositionX = 489.0f;
	static float MANAPositionH = 48.0f;
	static float MANAPositionY = 429.0f;
	static DWORD MANAPosition_buff = 0x0080FFD0;
	_asm
	{	
	FLD DWORD PTR DS:[MANAPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[MANAPositionX]
	FSTP DWORD PTR SS:[EBP-0x0C]
	FLD DWORD PTR DS:[MANAPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	FLD DWORD PTR DS:[MANAPositionY]
	FSTP DWORD PTR SS:[EBP-0x8]
	jmp [MANAPosition_buff]
	}
}
__declspec(naked) void HPPosition()
{
	static float HPPositionW = 52.0f;
	static float HPPositionX = 98.0f;
	static float HPPositionH = 48.0f;
	static float HPPositionY = 429.0f;
	static DWORD HPPosition_buff = 0x0080FD7C;
	_asm
	{             
	FLD DWORD PTR DS:[HPPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[HPPositionX]
	FSTP DWORD PTR SS:[EBP-0x0C]
	FLD DWORD PTR DS:[HPPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	FLD DWORD PTR DS:[HPPositionY]
	FSTP DWORD PTR SS:[EBP-0x8]
	jmp [HPPosition_buff]
	}
}

__declspec(naked) void UsingSkillPosition()
{
	static float UsingSkillPositionX = 311.0f;
	static float UsingSkillPositionY = 448.0f;
	static float UsingSkillPositionW = 20.0f;
	static float UsingSkillPositionH = 28.0f;
	static DWORD UsingSkillPosition_buff = 0x00813900;
	_asm
	{
	FLD DWORD PTR DS:[UsingSkillPositionX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[UsingSkillPositionY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[UsingSkillPositionW]
	FSTP DWORD PTR SS:[EBP-0x18]
	FLD DWORD PTR DS:[UsingSkillPositionH]
	FSTP DWORD PTR SS:[EBP-0x14]
	jmp [UsingSkillPosition_buff]
	}
}
__declspec(naked) void SkillClickPosition()
{
	static float SkillClickPositionX = 310.0f;
	static float SkillClickPositionY = 431.0f;
	static float SkillClickPositionW = 32.0f;
	static float SkillClickPositionH = 38.0f;
	static DWORD SkillClickPosition_buff = 0x00812734;
	_asm
	{
	FLD DWORD PTR DS:[SkillClickPositionX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[SkillClickPositionY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[SkillClickPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[SkillClickPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	jmp [SkillClickPosition_buff]
	}
}
__declspec(naked) void SkillBarDrawPosition()
{
	static float SkillBarDrawPositionX = 222.0f;
	static float SkillBarDrawPositionY = 480.0f;
	static float SkillBarDrawPositionW = 160.0f;
	static float SkillBarDrawPositionH = 38.0f;
	static DWORD SkillBarDrawPosition_buff = 0x00812968;
	_asm
	{	
	FLD DWORD PTR DS:[SkillBarDrawPositionX]
	FSTP DWORD PTR SS:[EBP-0x8]
	FLD DWORD PTR DS:[SkillBarDrawPositionY]
	FSTP DWORD PTR SS:[EBP-0x4]
	FLD DWORD PTR DS:[SkillBarDrawPositionW]
	FSTP DWORD PTR SS:[EBP-0x20]
	FLD DWORD PTR DS:[SkillBarDrawPositionH]
	FSTP DWORD PTR SS:[EBP-0x1C]
	jmp [SkillBarDrawPosition_buff]
	}
}

__declspec(naked) void SkillSwitchDraw()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchDraw_buff = 0x008139CA;
	_asm
	{
		FLD DWORD PTR DS:[SkillSwitchDrawX]
		FSTP DWORD PTR SS:[EBP-0x8]
		FLD DWORD PTR DS:[SkillSwitchDrawY]
		FSTP DWORD PTR SS:[EBP-0x4]	
		FLD DWORD PTR DS:[SkillSwitchDrawW]
		FSTP DWORD PTR SS:[EBP-0x18]
		FLD DWORD PTR DS:[SkillSwitchDrawH]
		FSTP DWORD PTR SS:[EBP-0x14]
		FLD DWORD PTR DS:[SkillSwitchDrawMW]
		FSTP DWORD PTR SS:[EBP-0x24]
		jmp [SkillSwitchDraw_buff]
	}
}
/*
_declspec(naked) void SkillSwitchDraw()
{
 static float SkillSwitchDrawX = 385.0f;
 static float SkillSwitchDrawY = 380.0f;
 static float SkillSwitchDrawW = 32.0f;
 static float SkillSwitchDrawH = 38.0f;
 static float SkillSwitchDrawMW = 385.0f;
 static DWORD SkillSwitchDraw_buff = 0x008139CA;
 static DWORD SkillJumpOut = 0x00813BB7;
 _asm
 {
  MOV EAX, DWORD PTR SS : [EBP - 0x34]
  MOVZX ECX, BYTE PTR DS : [EAX + 0x40]
  MOV gInterface.IsSkillDrawn, ECX
  CMP ECX, 1
  JNE fail
  FLD DWORD PTR DS:[SkillSwitchDrawX]
  FSTP DWORD PTR SS:[EBP-0x8]
  FLD DWORD PTR DS:[SkillSwitchDrawY]
  FSTP DWORD PTR SS:[EBP-0x4] 
  FLD DWORD PTR DS:[SkillSwitchDrawW]
  FSTP DWORD PTR SS:[EBP-0x18]
  FLD DWORD PTR DS:[SkillSwitchDrawH]
  FSTP DWORD PTR SS:[EBP-0x14]
  FLD DWORD PTR DS:[SkillSwitchDrawMW]
  FSTP DWORD PTR SS:[EBP-0x24]
  jmp [SkillSwitchDraw_buff]
 fail :
  jmp [SkillJumpOut]
 }
}
*/
__declspec(naked) void SkillSwitchClick()
{
	static float SkillSwitchDrawX = 385.0f;
	static float SkillSwitchDrawY = 380.0f;
	static float SkillSwitchDrawW = 32.0f;
	static float SkillSwitchDrawH = 38.0f;
	static float SkillSwitchDrawMW = 385.0f;
	static DWORD SkillSwitchClick_buff = 0x00812D69;
	_asm
	{
		FLD DWORD PTR DS:[SkillSwitchDrawX]
		FSTP DWORD PTR SS:[EBP-0x8]
		FLD DWORD PTR DS:[SkillSwitchDrawY]
		FSTP DWORD PTR SS:[EBP-0x4]
		FLD DWORD PTR DS:[SkillSwitchDrawW]
		FSTP DWORD PTR SS:[EBP-0x20]
		FLD DWORD PTR DS:[SkillSwitchDrawH]
		FSTP DWORD PTR SS:[EBP-0x1C]
		FLD DWORD PTR DS:[SkillSwitchDrawMW]
		FSTP DWORD PTR SS:[EBP-0x14]
		jmp [SkillSwitchClick_buff]
	}
}
__declspec(naked) void QPosition1()
{
	static float BarNumberY = 445.0f;
	static DWORD QPosition1_buff = 0x00895A4F;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition1_buff]
	}
}
__declspec(naked) void QPosition2()
{
	static float QPosition2X = 227.0f;
	static DWORD QPosition2_buff = 0x00895A59;
	_asm
	{
	FLD DWORD PTR DS:[QPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition2_buff]
	}
}
__declspec(naked) void QPosition3()
{
	static float BarPotionY = 453.0f;
	static DWORD QPosition3_buff = 0x00895A63;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition3_buff]
	}
}
__declspec(naked) void QPosition4()
{
	static float QPosition4X = 210.0f;
	static DWORD QPosition4_buff = 0x00895A6D;
	_asm
	{
	FLD DWORD PTR DS:[QPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [QPosition4_buff]
	}
}
__declspec(naked) void WPosition1()
{
	static float BarNumberY = 445.0f;
	static DWORD WPosition1_buff = 0x00895AC4;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition1_buff]
	}
}
__declspec(naked) void WPosition2()
{
	static float WPosition2X = 257.0f;
	static DWORD WPosition2_buff = 0x00895ACE;
	_asm
	{
	FLD DWORD PTR DS:[WPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition2_buff]
	}
}
__declspec(naked) void WPosition3()
{
	static float BarPotionY = 453.0f;
	static DWORD WPosition3_buff = 0x00895AD8;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition3_buff]
	}
}
__declspec(naked) void WPosition4()
{
	static float WPosition4X = 240.0f;
	static DWORD WPosition4_buff = 0x00895AE2;
	_asm
	{
	FLD DWORD PTR DS:[WPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [WPosition4_buff]
	}
}
__declspec(naked) void EPosition1()
{
	static float BarNumberY = 445.0f;
	static DWORD EPosition1_buff = 0x00895B39;
	_asm
	{
	FLD DWORD PTR DS:[BarNumberY]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition1_buff]
	}
}
__declspec(naked) void EPosition2()
{
	static float EPosition2X = 287.0f;
	static DWORD EPosition2_buff = 0x00895B43;
	_asm
	{
	FLD DWORD PTR DS:[EPosition2X]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition2_buff]
	}
}
__declspec(naked) void EPosition3()
{
	static float BarPotionY = 453.0f;
	static DWORD EPosition3_buff = 0x00895B4D;
	_asm
	{
	FLD DWORD PTR DS:[BarPotionY]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition3_buff]
	}
}
__declspec(naked) void EPosition4()
{
	static float EPosition4X = 270.0f;
	static DWORD EPosition4_buff = 0x00895B57;
	_asm
	{
	FLD DWORD PTR DS:[EPosition4X]
	FSTP DWORD PTR SS:[ESP]
	jmp [EPosition4_buff]
	}
}
__declspec(naked) void NopRShortKey()
{
	static DWORD RButtonAddress = 0x00895C0C;
	_asm{jmp RButtonAddress}
}
__declspec(naked) void HPNumberPosition()
{
	static float HPNumberPositionX = 45.0f;
	static DWORD HPNumberPosition_buff = 0x0080FF1E;
	_asm
	{
	FADD DWORD PTR DS:[HPNumberPositionX]
	FSTP DWORD PTR SS:[EBP-0x19C]
	FLD DWORD PTR SS:[EBP-0x19C]
	jmp [HPNumberPosition_buff]
	}
}
__declspec(naked) void MasterButton()
{
	static DWORD MasterButtonAddress1 = 0x0077ED20;
	_asm
	{
		jmp [MasterButtonAddress1]
	}
}
__declspec(naked) void HelperAll()
{
	static DWORD HelperStopAddress1 = 0x007D28B4;
	_asm
	{
		jmp [HelperStopAddress1]
	}
}
void InitInter3()
{

	SetRange((LPVOID)0x0080F270, 0x4D1, ASM::NOP);//-> Interface -> Draw Button
	//-
	SetByte((PVOID)(0x008137AF + 3), 0); //->skill Draw loop 5
	SetByte((PVOID)(0x008119A7), 0xEB); //-> Quest Interface First Login
	SetRange((LPVOID)0x00811AC0, 0xAC, ASM::NOP); //-> Friend message 
	//-
	SetRange((LPVOID)0x0081028C, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081028C, (LPVOID)AGPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0081055C, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081055C, (LPVOID)SDPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FFAF, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FFAF, (LPVOID)MANAPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FD5B, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FD5B, (LPVOID)HPPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x008138DF, 0x24, ASM::NOP);
	SetOp((LPVOID)0x008138DF, (LPVOID)UsingSkillPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x00812713, 0x24, ASM::NOP);
	SetOp((LPVOID)0x00812713, (LPVOID)SkillClickPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x00812947, 0x24, ASM::NOP);
	SetOp((LPVOID)0x00812947, (LPVOID)SkillBarDrawPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x008139A0, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x008139A0, (LPVOID)SkillSwitchDraw, ASM::JMP);
	//-
	SetRange((LPVOID)0x00812D3F, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x00812D3F, (LPVOID)SkillSwitchClick, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FF12, 0x12, ASM::NOP);
	SetOp((LPVOID)0x0080FF12, (LPVOID)HPNumberPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0077EC97, 0x88, ASM::NOP); //Remove Master Button (C)
	SetOp((LPVOID)0x0077EC97, (LPVOID)MasterButton, ASM::JMP); //Remove Master Button (C)
	//-
	//SetNop(0x008193F0,0xC8); //->Disable Master Window Skill (A)
	//-
	//MemorySet(0x00842DD0,0x90,0x1D7); //Remove NPC Gens window
	//MemorySet(0x007C4430,0x90,0x159); //Remove Gens Window(Hotkey B)
	//->Q
	SetRange((LPVOID)0x00895A49, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A49, (LPVOID)QPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895A53, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A53, (LPVOID)QPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895A5D, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A5D, (LPVOID)QPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895A67, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A67, (LPVOID)QPosition4, ASM::JMP);
	//->W
	SetRange((LPVOID)0x00895ABE, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895ABE, (LPVOID)WPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895AC8, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895AC8, (LPVOID)WPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895AD2, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895AD2, (LPVOID)WPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895ADC, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895ADC, (LPVOID)WPosition4, ASM::JMP);
	//-
	//->E
	SetRange((LPVOID)0x00895B33, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895B33, (LPVOID)EPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895B3D, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895B3D, (LPVOID)EPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895B47, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895B47, (LPVOID)EPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895B51, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895B51, (LPVOID)EPosition4, ASM::JMP);
	//-
	//->R
	SetRange((LPVOID)0x00895B8D, 0x7E, ASM::NOP);
	SetOp((LPVOID)0x00895B8D, (LPVOID)NopRShortKey, ASM::JMP);
}

void InitInter1()
{

	SetRange((LPVOID)0x0080F270, 0x4D1, ASM::NOP);//-> Interface -> Draw Button
	//-
	SetByte((PVOID)(0x008137AF + 3), 0); //->skill Draw loop 5
	SetByte((PVOID)(0x008119A7), 0xEB); //-> Quest Interface First Login
	SetRange((LPVOID)0x00811AC0, 0xAC, ASM::NOP); //-> Friend message 
	//-
	SetRange((LPVOID)0x0081028C, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0081028C, (LPVOID)AGPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0081055C, 0x24, ASM::NOP); //Disable SD Texture
	SetRange((LPVOID)0x00810631, 0x24, ASM::NOP); //Disable SD Number
	//SetOp((LPVOID)0x0081055C, (LPVOID)SDPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FFAF, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FFAF, (LPVOID)MANAPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FD5B, 0x24, ASM::NOP);
	SetOp((LPVOID)0x0080FD5B, (LPVOID)HPPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x008138DF, 0x24, ASM::NOP);
	SetOp((LPVOID)0x008138DF, (LPVOID)UsingSkillPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x00812713, 0x24, ASM::NOP);
	SetOp((LPVOID)0x00812713, (LPVOID)SkillClickPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x00812947, 0x24, ASM::NOP);
	SetOp((LPVOID)0x00812947, (LPVOID)SkillBarDrawPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x008139A0, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x008139A0, (LPVOID)SkillSwitchDraw, ASM::JMP);
	//-
	SetRange((LPVOID)0x00812D3F, 0x2D, ASM::NOP);
	SetOp((LPVOID)0x00812D3F, (LPVOID)SkillSwitchClick, ASM::JMP);
	//-
	SetRange((LPVOID)0x0080FF12, 0x12, ASM::NOP);
	SetOp((LPVOID)0x0080FF12, (LPVOID)HPNumberPosition, ASM::JMP);
	//-
	SetRange((LPVOID)0x0077EC97, 0x88, ASM::NOP); //Remove Master Button (C)
	SetOp((LPVOID)0x0077EC97, (LPVOID)MasterButton, ASM::JMP); //Remove Master Button (C)
	//-
	//SetNop(0x008193F0,0xC8); //->Disable Master Window Skill (A)
	//-
	//MemorySet(0x00842DD0,0x90,0x1D7); //Remove NPC Gens window
	//MemorySet(0x007C4430,0x90,0x159); //Remove Gens Window(Hotkey B)
	//->Q
	SetRange((LPVOID)0x00895A49, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A49, (LPVOID)QPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895A53, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A53, (LPVOID)QPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895A5D, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A5D, (LPVOID)QPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895A67, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895A67, (LPVOID)QPosition4, ASM::JMP);
	//->W
	SetRange((LPVOID)0x00895ABE, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895ABE, (LPVOID)WPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895AC8, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895AC8, (LPVOID)WPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895AD2, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895AD2, (LPVOID)WPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895ADC, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895ADC, (LPVOID)WPosition4, ASM::JMP);
	//-
	//->E
	SetRange((LPVOID)0x00895B33, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895B33, (LPVOID)EPosition1, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895B3D, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895B3D, (LPVOID)EPosition2, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895B47, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895B47, (LPVOID)EPosition3, ASM::JMP);
	//-
	SetRange((LPVOID)0x00895B51, 0x9, ASM::NOP);
	SetOp((LPVOID)0x00895B51, (LPVOID)EPosition4, ASM::JMP);
	//-
	//->R
	SetRange((LPVOID)0x00895B8D, 0x7E, ASM::NOP);
	SetOp((LPVOID)0x00895B8D, (LPVOID)NopRShortKey, ASM::JMP);

	SetRange((LPVOID)0x007D25C3, 0x2F0, ASM::NOP);
	SetOp((LPVOID)0x007D25C3, (LPVOID)HelperAll, ASM::JMP);
}