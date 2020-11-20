#pragma once
// ----------------------------------------------------------------------------------------------

#define naked	__declspec(naked)

struct ItemSmokeEffect
{
public:
	void Load();
	static void SetItemEffect();
	static void SetColorEffect();
public:
	float R;
	float G;
	float B;
}; extern ItemSmokeEffect gItemSmokeEffect;
// ----------------------------------------------------------------------------------------------