#include "stdafx.h"
#include "CustomFog.h"


cFog gFog;

cFog::cFog()
{
	this->Init();
}

cFog::~cFog()
{
	
}

void cFog::Init()
{
	for (int n = 0; n < MAX_FOG; n++)
	{
		this->m_CustomFog[n].Index = -1;
	}
}

void cFog::Load(CUSTOM_FOG* info)
{
	for(int n=0;n < MAX_FOG;n++)
	{
		this->SetInfo(info[n]);
	}
}

void cFog::SetInfo(CUSTOM_FOG info)
{
	if(info.Index < 0 || info.Index >= MAX_FOG)
	{
		return;
	}
	////console.Log("Fog", "[Load] %d [R:%f|G:%f|B:%f]", info.MapNumber, info.Red, info.Green, info.Blue);
	this->m_CustomFog[info.Index] = info;
}

CUSTOM_FOG* cFog::GetFogByMap(int MapNumber)
{
	for(int n=0;n < MAX_FOG;n++)
	{
		CUSTOM_FOG* lpInfo = this->GetFogByIndex(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->MapNumber == MapNumber)
		{
			return lpInfo;
		}
	}

	return 0;
}

CUSTOM_FOG* cFog::GetFogByIndex(int index)
{
	if(index < 0 || index >= MAX_FOG)
	{
		return 0;
	}

	if(this->m_CustomFog[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomFog[index];
}

float *cFog::toRGB(float *rgba)
{
	rgba[0] /= 255.0;
	rgba[1] /= 255.0;
	rgba[2] /= 255.0;

	return rgba;
}