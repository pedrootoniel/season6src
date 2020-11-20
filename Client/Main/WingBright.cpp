#include "stdafx.h"
#include "WingBright.h"
#include "Offset.h"
#include "TMemory.h"
#include "Import.h"
#include "Defines.h"
#include "Protect.h"
WingsBright gWingsBright;
DWORD dwItemId;
DWORD dwWingThis;
DWORD dwWingStyle;
DWORD dwWingEff;
// ----
DWORD mdTmpEax;
DWORD mdTmpEsi;
DWORD mdTmpEdi;
DWORD mdTmpEcx;
DWORD mdTmpEdx;
DWORD mdTmpEbx;
DWORD mdTmpEbp;
DWORD mdTmpEsp;
// ----
DWORD dwCustomItemGlowJmp00		= 0x005FAA3F; //0x005E04E6 1.03Y
DWORD dwCustomItemGlowJmp01		= 0x005FAA33; //0x005E5375 1.03Y

__declspec(naked) void HieuUngBufferGlow()
{
	DWORD dwItem;
	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0x10]
			MOV dwItem, EAX
			// ----
			CMP dwItem, 0x4AA
			JE Return
			CMP dwItem, ITEM2(5, 200)
			JE Return
			CMP dwItem, ITEM2(2, 24)
			JE Return
			CMP dwItem, ITEM2(5, 44)
			JE Return
			CMP dwItem, ITEM2(5, 45)
			JE Return
			CMP dwItem, ITEM2(0, 47)
			JE Return
			CMP dwItem, ITEM2(12, 180)
			JE Return
			CMP dwItem, ITEM2(12, 191)
			JE Return
			CMP dwItem, ITEM2(12, 200)
			JE Return
			CMP dwItem, ITEM2(12, 201)
			JE Return
			CMP dwItem, ITEM2(12, 203)
			JE Return
			CMP dwItem, ITEM2(12, 204)
			JE Return
			CMP dwItem, ITEM2(12, 205)
			JE Return
			CMP dwItem, ITEM2(12, 206)
			JE Return
			CMP dwItem, ITEM2(12, 209)
			JE Return
			CMP dwItem, ITEM2(12, 212)
			JE Return
		Return :
		MOV EAX, 0x005FF983
			JMP EAX
	}
}

__declspec(naked) void HieuUngBufferGlow2()
{
	DWORD dwItem;
	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0x10]
			MOV dwItem, EAX
			// ----
			CMP dwItem, 0x4AA
			JE Return
			CMP dwItem, ITEM2(12, 180)
			JE Return
			CMP dwItem, ITEM2(12, 183)
			JE Return
			CMP dwItem, ITEM2(12, 184)
			JE Return
			CMP dwItem, ITEM2(12, 186)
			JE Return
			CMP dwItem, ITEM2(12, 187)
			JE Return
			CMP dwItem, ITEM2(12, 188)
			JE Return
			CMP dwItem, ITEM2(12, 189)
			JE Return
			CMP dwItem, ITEM2(12, 190)
			JE Return
			CMP dwItem, ITEM2(12, 191)
			JE Return
			CMP dwItem, ITEM2(12, 192)
			JE Return
			CMP dwItem, ITEM2(12, 193)
			JE Return
			CMP dwItem, ITEM2(12, 194)
			JE Return
			CMP dwItem, ITEM2(12, 195)
			JE Return
			//CMP dwItem, ITEM2(12, 196)
			//JE Return
			CMP dwItem, ITEM2(12, 197)
			JE Return
			CMP dwItem, ITEM2(12, 200)
			JE Return
			CMP dwItem, ITEM2(12, 201)
			JE Return
			CMP dwItem, ITEM2(12, 209)
			JE Return
			CMP dwItem, ITEM2(12, 226)
			JE Return
			CMP dwItem, ITEM2(12, 231)
			JE Return
		Return :
		MOV EAX, 0x005FF983
			JMP EAX
	}
}

void __declspec(naked) SwordTex()
{
	DWORD dwItem;
	_asm
	{
		Mov Ecx,DWORD PTR SS:[EBP+0x10]
		Mov dwItem, Ecx
		//-
		cmp dwItem,ITEM2(0,28)
		Je EXIT
		//cmp dwItem,ITEM2(0,47)
		//Je EXIT
		EXIT:
		Mov Ecx,0x005FC17C
		Jmp Ecx
	}
}
void __declspec(naked) SwordTex2()
{
	DWORD dwItem;
	_asm
	{
		Mov Ecx,DWORD PTR SS:[EBP+0x10]
		Mov dwItem, Ecx
		//-
		Cmp dwItem,ITEM2(0,28)
		Je EXIT
		//Cmp dwItem,ITEM2(0,47)
		//Je EXIT
		EXIT:
		mov Ecx,0x00608628
		Jmp Ecx
	}
}

void DrawViewportGlow(int a1, int a2, int ModelID, float a4, int a5)
{
	pDrawViewportGlow(a1, a2, ModelID, a4, a5);
	DWORD Model = sub_969C50(sub_4CDA10(), ModelID);

	float v20;
	float v21;
	float v403;
	switch (ModelID)
	{
#ifdef SaveCodeUseLater
	case ITEM2(12, 180):
		if (*(float *)(a1 + 72) != 1.0 || *(float *)(a1 + 76) != 1.0 || *(float *)(a1 + 80) != 1.0)
		{

			*(float *)(a1 + 72) = 1.0;
			*(float *)(a1 + 76) = 1.0;
			*(float *)(a1 + 80) = 1.0;
			glColor3fv((const GLfloat *)(a1 + 72));
			pTexEffect(
				a1,
				0,
				2,
				*(float *)(a2 + 152),
				*(DWORD *)(a2 + 68),
				*(float *)(a2 + 100),
				*(float *)(a2 + 104),
				*(float *)(a2 + 108),
				-1);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
		}
		else
		{
			*(float *)(a1 + 72) = 1.0;
			*(float *)(a1 + 76) = 1.0;
			*(float *)(a1 + 80) = 1.0;
			glColor3fv((const GLfloat *)(a1 + 72));
			pCustomEffGet2_(a1,
				2,
				*(float *)(a2 + 152),
				*(DWORD *)(a2 + 68),
				*(float *)(a2 + 100),
				*(float *)(a2 + 104),
				*(float *)(a2 + 108),
				*(DWORD *)(a2 + 60),
				-1);
		}
		break;
#endif
	//case ITEM2(12, 180):
	//case ITEM2(12, 181):
	//case ITEM2(12, 185):
	//case ITEM2(12, 186):
	//case ITEM2(12, 187):
	//case ITEM2(12, 188):
	//case ITEM2(12, 189):
	//case ITEM2(12, 190):
	//case ITEM2(12, 191):
	//case ITEM2(12, 192):
	//case ITEM2(12, 193):
	//case ITEM2(12, 194):
	//case ITEM2(12, 195):
	//case ITEM2(12, 196):
	//case ITEM2(12, 200):
	//case ITEM2(12, 201):
	//case ITEM2(12, 202):
	//case ITEM2(12, 203):
	//case ITEM2(12, 204):
	//case ITEM2(12, 205):
	//case ITEM2(12, 206):
	//case ITEM2(12, 207):
	//case ITEM2(12, 208):
	//case ITEM2(12, 209):
	//case ITEM2(12, 210):
	//case ITEM2(12, 211):
		*(float *)(a1 + 72) = 1.0;
		*(float *)(a1 + 76) = 1.0;
		*(float *)(a1 + 80) = 1.0;
		glColor3fv((const GLfloat *)(a1 + 72));
		pCustomEffGet2_(a1,
			2,
			*(float *)(a2 + 152),
			*(DWORD *)(a2 + 68),
			*(float *)(a2 + 100),
			*(float *)(a2 + 104),
			*(float *)(a2 + 108),
			*(DWORD *)(a2 + 60),
			-1);
		break;
	case ITEM2(0, 47):
		*(float *)(a1 + 72) = 0.8f;
		*(float *)(a1 + 76) = 0.8f;
		*(float *)(a1 + 80) = 0.8f;
		v20 = *(float*)0x5EF5A1C * 0.002000000094994903f;
		v21 = sin(v20) * 0.300000011920929f;
		v403 = v21 + 0.699999988079071f;
		pCustomEffGet2_(a1, 66, 1.0, 0, v403, *(float *)(a1 + 104), *(float *)(a1 + 108), *(DWORD *)(a1 + 60), -1);
		break;
	}
}

void SetItemEffect(int a1, int ModelID, vec3_t Angle, int Arg4, int ItemLevel, char Arg6, int Arg7, int Arg8, int Arg9)
{
	pSetItemEffect(a1, ModelID, Angle, Arg4, ItemLevel, Arg6, Arg7, Arg8, Arg9);
	DWORD Model = sub_969C50(sub_4CDA10(), ModelID);

	float v20;
	float v21;
	float v403;


	switch (*(DWORD *)(a1 + 48))
	{
	case ITEM2(0, 47):
		*(float *)(Model + 72) = 0.80000001f;
		*(float *)(Model + 76) = 0.80000001f;
		*(float *)(Model + 80) = 0.80000001f;
		v20 = *(float*)0x5EF5A1C * 0.002000000094994903f;
		v21 = sin(v20) * 0.300000011920929f;
		v403 = v21 + 0.699999988079071f;
		pCustomEffGet2((LPVOID)Model, 66, 1.0, 0, v403, *(float *)(a1 + 104), *(float *)(a1 + 108), *(DWORD *)(a1 + 60), -1);
		break;
	/*case ITEM2(12, 180):
		*(float *)(Model + 72) = 1.0;
		*(float *)(Model + 76) = 1.0;
		*(float *)(Model + 80) = 1.0;
		glColor3fv((const GLfloat *)(a1 + 72));
		pCustomEffGet2((LPVOID)Model, 2, *(float *)(a1 + 152), *(DWORD *)(a1 + 68), *(float *)(a1 + 100), *(float *)(a1 + 104), *(float *)(a1 + 108), *(DWORD *)(a1 + 60), -1);
	
		*(float *)(Model + 72) = 0.40000001f;
		*(float *)(Model + 76) = 0.10000001f;
		*(float *)(Model + 80) = 0.10000001f;
		v20 = *(float*)0x5EF5A1C * 0.002000000094994903f;
		v21 = sin(v20) * 0.300000011920929f;
		v403 = v21 + 0.699999988079071f;
		pCustomEffGet2((LPVOID)Model, 66, 1.0, 0, v403, *(float *)(a1 + 104), *(float *)(a1 + 108), *(DWORD *)(a1 + 60), -1);
		break;*/
	case ITEM2(12, 180):
	case ITEM2(12, 187):
	case ITEM2(12, 192):
	case ITEM2(12, 181):
	case ITEM2(12, 182):
	case ITEM2(12, 183):
	case ITEM2(12, 194):
	case ITEM2(12, 196):
	case ITEM2(12, 204):
	case ITEM2(12, 220):
	case ITEM2(12, 221):
	case ITEM2(12, 222):
	case ITEM2(12, 223):
	case ITEM2(12, 224):
	case ITEM2(12, 225):
	case ITEM2(12, 226):
	case ITEM2(12, 227):
		*(float *)(Model + 72) = 1.0;
		*(float *)(Model + 76) = 1.0;
		*(float *)(Model + 80) = 1.0;
		glColor3fv((const GLfloat *)(a1 + 72));
		pCustomEffGet2((LPVOID)Model, 2, *(float *)(a1 + 152), *(DWORD *)(a1 + 68), *(float *)(a1 + 100), *(float *)(a1 + 104), *(float *)(a1 + 108), *(DWORD *)(a1 + 60), -1);
		break;
	}
}

void WingsBright::Load()
{

	SetRange((LPVOID)0x005FC175, 7, ASM::NOP);
	SetOp((LPVOID)0x005FC175, (LPVOID)SwordTex, ASM::JMP);
	//--
	SetRange((LPVOID)0x00608621, 7, ASM::NOP);
	SetOp((LPVOID)0x00608621, (LPVOID)SwordTex2, ASM::JMP);
	//--
	SetRange((LPVOID)0x005FF97C, 7, ASM::NOP);
	if (gProtect.m_MainInfo.CustomItemPack == 0)
		SetOp((LPVOID)0x005FF97C, (LPVOID)HieuUngBufferGlow, ASM::JMP);
	else	
		SetOp((LPVOID)0x005FF97C, (LPVOID)HieuUngBufferGlow2, ASM::JMP);
	//SetOp((LPVOID)0x005666C1, (LPVOID)SetItemEffect, ASM::CALL);
	//SetOp((LPVOID)0x0061041C, (LPVOID)SetItemEffect, ASM::CALL);
	//SetOp((LPVOID)0x00610466, (LPVOID)SetItemEffect, ASM::CALL);

	SetOp((LPVOID)0x0060D9C9, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060DB79, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060DBEA, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060DC5B, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060DD1D, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060DD8E, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060DDFF, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060DE70, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060DEBA, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060DF78, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E045, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E124, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E211, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E2E6, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E394, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E408, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E47C, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E516, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E5BC, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E662, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E745, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E828, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060E93C, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060EA50, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060EB63, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060EC77, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060ED50, (LPVOID)DrawViewportGlow, ASM::CALL);
	SetOp((LPVOID)0x0060ED94, (LPVOID)DrawViewportGlow, ASM::CALL);
}
