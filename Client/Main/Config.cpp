#include "StdAfx.h"
#include "Config.h"
#include "HealthBar.h"
#include "Console.h"
cConfig gConfig;

void cConfig::Load()
{
	this->SetID[0] = GetPrivateProfileInt("NPC1","SetID",0,MAIN_FILE);
	this->Wings = GetPrivateProfileInt("NPC1","WingID",0,MAIN_FILE);
	this->FirstWeaponType[0] = GetPrivateProfileInt("NPC1","FirstWeaponType",0,MAIN_FILE);
	this->FirstWeaponIndex[0] = GetPrivateProfileInt("NPC1","FirstWeaponIndex",0,MAIN_FILE);
	this->SecondWeaponType[0] = GetPrivateProfileInt("NPC1","SecondWeaponType",0,MAIN_FILE);
	this->SecondWeaponIndex[0] = GetPrivateProfileInt("NPC1","SecondWeaponIndex",0,MAIN_FILE);
	//
	this->SetID[1] = GetPrivateProfileInt("NPC2","SetID",0,MAIN_FILE);
	this->FirstWeaponType[1] = GetPrivateProfileInt("NPC2","WeaponType",0,MAIN_FILE);
	this->FirstWeaponIndex[1] = GetPrivateProfileInt("NPC2","WeaponIndex",0,MAIN_FILE);
	//
	this->SetID[2] = GetPrivateProfileInt("NPC3","SetID",0,MAIN_FILE);
	this->FirstWeaponType[2] = GetPrivateProfileInt("NPC3","247WeaponType",0,MAIN_FILE);
	this->FirstWeaponIndex[2] = GetPrivateProfileInt("NPC3","247WeaponIndex",0,MAIN_FILE);
	this->SecondWeaponType[2] = GetPrivateProfileInt("NPC3","249WeaponType",0,MAIN_FILE);
	this->SecondWeaponIndex[2] = GetPrivateProfileInt("NPC3","249WeaponIndex",0,MAIN_FILE);
	//
	this->m_Fog = GetPrivateProfileIntA("Game","Fog",0,SETTINGS);
	this->m_SeparateChat = GetPrivateProfileIntA("Game","SeparateChat",0,SETTINGS);
	this->m_LoginTheme = GetPrivateProfileIntA("Game","LoginTheme",0,SETTINGS);
	//
	this->EffectStatic = GetPrivateProfileIntA("Game","EffectStatic",1,SETTINGS);
	this->EffectDynamic = GetPrivateProfileIntA("Game","EffectDynamic",1,SETTINGS);
	this->EffectSkill = GetPrivateProfileIntA("Game","EffectSkill",1,SETTINGS);
	this->EffectSkill2 = GetPrivateProfileIntA("Game","EffectSkill2",1,SETTINGS);
	this->EffectLevelGlow = GetPrivateProfileIntA("Game","EffectLevelGlow",1,SETTINGS);
	this->EffectExcellent = GetPrivateProfileIntA("Game","EffectExcellent",1,SETTINGS);
	this->EffectLevel15	= GetPrivateProfileIntA("Game","EffectLevel15",1,SETTINGS);
	//
	this->MenuBackground.Red = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBG_Red",FLOATTORGB(0.0),SETTINGS));
	this->MenuBackground.Green = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBG_Green",FLOATTORGB(0.0),SETTINGS));
	this->MenuBackground.Blue = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBG_Blue",FLOATTORGB(0.0),SETTINGS));
	this->MenuBackground.Alpha = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBG_Alpha",FLOATTORGB(0.5),SETTINGS));

	this->MenuButton.Red = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtn_Red",FLOATTORGB(0.6),SETTINGS));
	this->MenuButton.Green = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtn_Green",FLOATTORGB(0.6),SETTINGS));
	this->MenuButton.Blue = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtn_Blue",FLOATTORGB(0.6),SETTINGS));
	this->MenuButton.Alpha = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtn_Alpha",FLOATTORGB(1.0),SETTINGS));

	this->MenuButtonHover.Red = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtnHover_Red",FLOATTORGB(0.0),SETTINGS));
	this->MenuButtonHover.Green = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtnHover_Green",FLOATTORGB(0.0),SETTINGS));
	this->MenuButtonHover.Blue = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtnHover_Blue",FLOATTORGB(0.8),SETTINGS));
	this->MenuButtonHover.Alpha = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtnHover_Alpha",FLOATTORGB(1.0),SETTINGS));

	this->MenuButtonClick.Red = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtnMouse_Red",FLOATTORGB(0.8),SETTINGS));
	this->MenuButtonClick.Green = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtnMouse_Green",FLOATTORGB(0.0),SETTINGS));
	this->MenuButtonClick.Blue = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtnMouse_Blue",FLOATTORGB(0.0),SETTINGS));
	this->MenuButtonClick.Alpha = RGBTOGLFLOAT(GetPrivateProfileInt("Menu","MenuBtnMouse_Alpha",FLOATTORGB(1.0),SETTINGS));

	this->CustomerName	= GetPrivateProfileIntA("Game","CustomerName",1996,SETTINGS);

}