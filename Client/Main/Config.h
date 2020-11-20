#pragma once
#include "NewInterface.h"

class cConfig
{
public:
	void Load();
	int	SetID[5];
	int	Wings;
	int	FirstWeaponType[5];
	int	FirstWeaponIndex[5];
	int	SecondWeaponType[5];
	int	SecondWeaponIndex[5];
	//
	int	m_Fog;
	int	m_SeparateChat;
	int m_LoginTheme;
	// ----
	MU_4float MenuBackground;
	MU_4float MenuButton;
	MU_4float MenuButtonHover;
	MU_4float MenuButtonClick;
	// ----
	int EffectStatic;
	int EffectDynamic;
	int EffectSkill;
	int EffectSkill2;
	//
	int	EffectLevelGlow;
	int	EffectExcellent;
	int	EffectLevel15;
	char BuffText[100][255];
	//
	int CustomerName;
};

// Arquivo de configuracao
// "./" Indica que o arquivo e na mesa pasta do main.exe
#define MAIN_FILE "./Data/Custom/NPCModel.txt"
#define SETTINGS ".\\Settings.ini"
#define BUFFICONTEXT "./Data/Custom/BuffIconText.txt"
extern cConfig gConfig;
