// CustomWingEffect.h: interface for the CCustomModelEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_MODEL_EFFECT 200

struct CUSTOM_MODEL_EFFECT_INFO
{
	int		Index;
	int		ItemType;
	int		ItemIndex;
	int		MinLevel;
	int		MaxLevel;
	int		MinExcellent;
	int		MaxExcellent;
	float	Color[3];
	int		EffectIndex;
	int		EffectType;
	int		EffectCode;		
	int		EffectScale;
};

class CCustomModelEffect
{
public:
	CCustomModelEffect();
	virtual ~CCustomModelEffect();
	void Init();
	void Load(CUSTOM_MODEL_EFFECT_INFO* info);
	void SetInfo(CUSTOM_MODEL_EFFECT_INFO info);
public:
	CUSTOM_MODEL_EFFECT_INFO m_CustomModelEffectInfo[MAX_MODEL_EFFECT];
};

extern CCustomModelEffect gCustomModelEffect;
