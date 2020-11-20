#pragma once

#define MAX_FOG 150

struct CUSTOM_FOG
{
	int Index;
	int MapNumber;
	float Red;
	float Green;
	float Blue;
};

class cFog
{
public:
	cFog();
	virtual ~cFog();
	void Init();
	void Load(CUSTOM_FOG* info);
	void SetInfo(CUSTOM_FOG info);
	CUSTOM_FOG* GetFogByMap(int MapNumber);
	CUSTOM_FOG* GetFogByIndex(int Index);
	float		*toRGB(float *rgba);
	// ----
public:
	CUSTOM_FOG m_CustomFog[MAX_FOG];
	bool EnableFog;
}; extern cFog gFog;