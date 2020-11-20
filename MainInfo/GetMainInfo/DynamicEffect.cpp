// CustomWingEffect.cpp: implementation of the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DynamicEffect.h"
#include "MemScript.h"

CDynamicWingEffect gDynamicWingEffect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDynamicWingEffect::CDynamicWingEffect() // OK
{
	this->Init();
}

CDynamicWingEffect::~CDynamicWingEffect() // OK
{

}

void CDynamicWingEffect::Init() // OK
{
	for(int n=0;n < MAX_DYNAMIC_WING_EFFECT;n++)
	{
		this->m_DynamicWingEffectInfo[n].Index = -1;
	}
}

void CDynamicWingEffect::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->Init();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			DYNAMIC_WING_EFFECT_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomWingEffectIndexCount = 0;

			info.Index = CustomWingEffectIndexCount++;

			info.ItemType = lpMemScript->GetNumber();

			info.ItemIndex = lpMemScript->GetAsNumber();

			info.EffectIndex = lpMemScript->GetAsNumber();

			info.EffectValue = lpMemScript->GetAsNumber();

			info.EffectLevel = lpMemScript->GetAsNumber();

			info.ColorR = lpMemScript->GetAsFloatNumber();

			info.ColorG = lpMemScript->GetAsFloatNumber();

			info.ColorB = lpMemScript->GetAsFloatNumber();

			info.Effect1 = lpMemScript->GetAsFloatNumber();

			info.Effect2 = lpMemScript->GetAsFloatNumber();

			info.Effect = lpMemScript->GetAsFloatNumber();

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CDynamicWingEffect::SetInfo(DYNAMIC_WING_EFFECT_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_DYNAMIC_WING_EFFECT)
	{
		return;
	}

	this->m_DynamicWingEffectInfo[info.Index] = info;
}
