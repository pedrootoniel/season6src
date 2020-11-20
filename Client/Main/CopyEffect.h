#pragma once

class CCopyEffect
{
public:
	CCopyEffect();
	virtual ~CCopyEffect();
	void Load();
	static void DrawViewPortEffects(DWORD ObjectPointer, DWORD ModelPointer, DWORD a3);
};

extern CCopyEffect gCopyEffect;