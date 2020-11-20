// CustomWingEffect.cpp: implementation of the CCustomModelEffect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModelEffect.h"
#include "Defines.h"
CCustomModelEffect gCustomModelEffect;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomModelEffect::CCustomModelEffect() // OK
{
	this->Init();
}

CCustomModelEffect::~CCustomModelEffect() // OK
{

}

void CCustomModelEffect::Init() // OK
{
	for(int n=0;n < MAX_MODEL_EFFECT;n++)
	{
		this->m_CustomModelEffectInfo[n].Index = -1;
	}
}

void CCustomModelEffect::Load(CUSTOM_MODEL_EFFECT_INFO* info) // OK
{
	for(int n=0;n < MAX_MODEL_EFFECT;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomModelEffect::SetInfo(CUSTOM_MODEL_EFFECT_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_MODEL_EFFECT)
	{
		return;
	}

	this->m_CustomModelEffectInfo[info.Index] = info;
}