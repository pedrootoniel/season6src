#include "stdafx.h"
#include "BuffIcon.h"
#include "Interface.h"
#include "Defines.h"
#include <process.h>
//include "Util.h"
#include "Offset.h"
#include "Interface.h"
#include <time.h>
//#include "HealthBar.h"
#include "User.h"
//#include "PrintPlayer.h"
#include "Util.h"
#include "TMemory.h"
#include "PartyBuffs.h"
#include "HealthBar.h"
// ------------------------------------------------------------------------------
//#if(USER_BUFF_ICON_EX==TRUE)

BuffIcon g_BuffIcon;
// ------------------------------------------------------------------------------

BuffIcon::BuffIcon()
{
	this->Init();

	this->hThread = (HANDLE)_beginthreadex(NULL, 0, this->Timer, 0, 0, NULL);

	this->Load();
}
// ------------------------------------------------------------------------------

BuffIcon::~BuffIcon()
{
	CloseHandle(this->hThread);
}
// ------------------------------------------------------------------------------
void BuffIcon::Init()
{
	this->LoadBuffCount = 0;
	this->UserBuffCount = 0;
	ZeroMemory(&DataBuff, sizeof(DataBuff));
	ZeroMemory(&UserBuff, sizeof(UserBuff));
}
// ------------------------------------------------------------------------------

void __fastcall BuffIcon::GetCoord(struct_v15* This, int a2)
{
	//g_Console.AddMessage(5,"a2 = %d",a2);
	if (This->Pos_X == 220)
	{
		//if (a2 == 1)
		//{
			gPartyBuffs.DrawPartyBuffs();
		//}
	}


	//if (gConfig.GetCustomState(CUSTOM_BUFFICON) == true)
	//{
			g_BuffIcon.Draw((float)This->Pos_X, (float)This->Pos_Y);
	//}
	/*
	else
	{
		DWORD addr = 0x00777CB0;
		__asm
		{
			PUSH 0                        
			MOV ECX,This
			CALL addr           
			PUSH 1                        
			MOV ECX,This 
			CALL addr          
		}
	}*/
}

// ------------------------------------------------------------------------------

//void __declspec ( naked ) TestBuff() 
//{
//	static DWORD X = 0;
//	static DWORD Y = 0;
//
//	__asm
//	{
//		MOV EAX,DWORD PTR SS:[EBP-0x6C]
//		MOV ECX, DWORD PTR DS:[EAX+0x10]
//		MOV X, ECX
//		MOV ECX, DWORD PTR DS:[EAX+0x14]
//		MOV Y, ECX
//	}
//
//	if (X == 220)
//	{
//		gPartyBuffs.DrawPartyBuffs();
//	}
//
//	//g_Console.AddMessage(5,"X = %f Y = %f",(float)X,(float)Y);
//	g_BuffIcon.Draw((float)X, (float)Y);
//
//	__asm
//	{
//		MOV ECX,DWORD PTR SS:[EBP-0xC]
//		MOV DWORD PTR FS:[0x0],ECX
//		MOV ESP,EBP
//		POP EBP
//		RETN 0x4
//	}
//}

void BuffIcon::Load()
{
	this->Init();
	//SetRange((LPVOID)0x00777C78, 5, ASM::NOP); //Icon Disable , Need Info DIsable


	SetRange(0x00777C90, 5, ASM::NOP);


	//SetCompleteHook(0xE8, 0x00777C90, &this->GetCoord);

	SetCompleteHook(0xE8, 0x00777C9A, &this->GetCoord);

	//SetCompleteHook(0xE9,0x00777CCE,&TestBuff);
	
	this->BindIcon(AT_INCREASE_ATTACK, "Increase Attack Power", "Attack power increases.");
	this->BindIcon(AT_INCREASE_DEFENSE, "Increase Defense", "Defensibility increases.");
	this->BindIcon(AT_NPC_HELP, "Shadow Phantom effect", "Attack power and Defensibility increases");
	this->BindIcon(AT_ICE, "Ice", "Mobility speed decreases.");
	this->BindIcon(AT_WIZARD_DEFENSE, "Soul Barrier", "Manna absorbs the damage.");
	this->BindIcon(AT_INCREASE_CRITICAL_DMG, "Critical Damage increase", "Critical damage increases.");
	this->BindIcon(AT_INFINITY_ARROW, "Infinity Arrow", "Arrows do not become consumed.");
	this->BindIcon(AT_INCREASE_AG_SPEED, "AG recovery speed increase", "");
	this->BindIcon(AT_SWELL_LIFE, "Swell Life", "Health stat increases to maximum.");
	this->BindIcon(AT_SWELL_MANA, "Swell Mana", "Mana stat increases to maximum.");
	this->BindIcon(AT_POTION_OF_BLESS, "Potion of Blessing", "Attack power +20%% increase");

	this->BindIcon(AT_POTION_OF_SOUL, "Potion of Soul", "AG recovery speed increase +8/Lightning and Ice resistance increase/attack speed increase +20");
	this->BindIcon(12, "Abolish Magic", "");
	this->BindIcon(13, "Gate Open/Close Status", "");
	this->BindIcon(14, "Watchtower", "");
	this->BindIcon(15, "Besiegement Guild1", "");
	this->BindIcon(16, "Besiegement Guild2", "");
	this->BindIcon(17, "Besiegement Guild3", "");
	this->BindIcon(18, "Invisibility", "");
	this->BindIcon(19, "Dark Rod Battle Skill", "");
	this->BindIcon(20, "Crown Registration Status", "");//

	this->BindIcon(21, "Altar of Wolf contract enabled", "");//Altar of Wolf contract enabled
	this->BindIcon(22, "Altar of Wolf contract enabled", "");//Altar of Wolf contract disabled
	this->BindIcon(23, "Altar of Wolf contract enabled", "");//Altar of Wolf contract Status
	this->BindIcon(24, "Altar of Wolf contract enabled", "");//Altar of Wolf contract attempt
	this->BindIcon(25, "Altar of Wolf contract enabled", "");//Altar of Wolf besiegement Status
	this->BindIcon(26, "Altar of Wolf contract enabled", "");//Altar of Wolf hero contract Status
	this->BindIcon(27, "Altar of Wolf contract enabled", "");//Cry Wolf NPC transparency
	this->BindIcon(28, "GM", "You are GameMaster");
	this->BindIcon(29, "Seal of Ascension", "EXP gain increase 150%%");
	this->BindIcon(30, "Seal of Wealth", "EXP gain increase 150%%/item gain increase 200%%");//

	this->BindIcon(31, "Seal of Wealth", "EXP gain disabled");//
	this->BindIcon(32, "Temple - Spell of Quickness", "");//Temple - Spell of Quickness
	this->BindIcon(33, "Temple - Spell of Sublimation", "");//Temple - Spell of Sublimation
	this->BindIcon(34, "Spell of Protection", "Damage absorbed at 100%%.");//Spell of Protection
	this->BindIcon(35, "Jack O'Lantern Blessings", "Attack speed increase +10");//Jack O'Lantern Blessings
	this->BindIcon(36, "Jack O'Lantern Wrath", "Attack power increase +25");//Jack O'Lantern Wrath
	this->BindIcon(37, "Jack O'Lantern Cry", "Defensibility increase +100");//Jack O'Lantern Cry
	this->BindIcon(38, "Jack O'Lantern Food", "Maximum Life increase +500");//Jack O'Lantern Food
	this->BindIcon(39, "Jack O'Lantern Drink", "Maximum Mana increase +500");//Jack O'Lantern Drink
	this->BindIcon(40, "Seal of Ascension", "EXP gain increase 150%%");//Seal of Ascension

	this->BindIcon(41, "Seal of Wealth", "EXP gain increase 200%%/Item gain increase 150%%"); //Seal of Wealth	0	0	1	EXP gain increase 200%%/Item gain increase 150%%
	this->BindIcon(42, "Seal of Sustenance", "EXP gain disabled"); //Seal of Sustenance	0	0	1	EXP gain disabled
	this->BindIcon(43, "Seal of Mobility", "Mobility enabled"); //Seal of Mobility	0	0	1	Mobility enabled
	this->BindIcon(44, "Scroll of Quickness", "Attack speed increase +15"); //Scroll of Quickness	0	1	1	Attack speed increase +15
	this->BindIcon(45, "Scroll of Defense", "Defensibility increase +60"); //Scroll of Defense	0	1	1	Defensibility increase +60
	this->BindIcon(46, "Scroll of Wrath", "Attack power increase +30"); //Scroll of Wrath	0	1	1	Attack power increase +30
	this->BindIcon(47, "Scroll of Wizardry", "Wizardry increase +30"); //Scroll of Wizardry	0	1	1	Wizardry increase +30
	this->BindIcon(48, "Scroll of Health", " increase +200"); //Scroll of Health	0	1	1	HP
	this->BindIcon(49, "Scroll of Mana", "Mana increase +300"); //	0	1	1	
	this->BindIcon(50, "Elixir of Strength", "Strength Status +50"); //	0	1	1	

	this->BindIcon(51, "Elixir of Agility", "Agility Status +50"); //	0	1	1	
	this->BindIcon(52, "Elixir of Health", "Health Status +50"); //	0	1	1	
	this->BindIcon(53, "Elixir of Energy", "Energy Status +50"); //	0	1	1	
	this->BindIcon(54, "Elixir of Control", "Control Status +50"); //	0	1	1	
	this->BindIcon(AT_POISON, "Poison", "Poisoned status of condition"); //	1	1	1	
	this->BindIcon(AT_ICE, "Ice", "Mobility speed decreases.");
	this->BindIcon(AT_ICE_ARROW, "Iced Arrow", "Mobility disabled"); //Iced Arrow	1	1	1	Mobility disabled
	this->BindIcon(58, "Defensibility reduction", "Random defensibility decreases at 10%%."); //	1	1	1	
	this->BindIcon(59, "Attack power reduction", ""); //	1	0	1	
	this->BindIcon(60, "Wizardry increase reduction", ""); //	1	0	1	


	this->BindIcon(61, "Stun", "Mobility disabled"); //	1	1	1	
	this->BindIcon(62, "Magic Defense", ""); //	1	0	1	
	this->BindIcon(63, "Monster Magic Attack Resistance", ""); //	1	1	1	
	this->BindIcon(64, "Monster Chemistry Attack Resistance", ""); //	1	1	1	
	this->BindIcon(65, "Spell of Restriction", "Mobility disabled"); //	1	1	1	
	this->BindIcon(66, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(67, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(68, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(69, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(70, "Cry Wolf Divine Protection Status", "Cry Wolf Divine Protection Status"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	

	this->BindIcon(AT_DAMAGE_REFLECTION, "Damage Reflection", "Partial damage reflected out."); //	0	1	1	
	this->BindIcon(AT_SLEEP, "Sleep", "Short period of nap"); //	1	1	1	
	this->BindIcon(AT_BLIND, "Blind", "Shortened view and the attack accuracy decreases."); //	1	1	1	
	this->BindIcon(AT_REQUIEM, "Requiem", "Summoner Neil attack"); //	1	1	1	
	this->BindIcon(AT_EXPLOSION, "Explosion", "Summoner Shamut attack"); //	1	1	1	
	this->BindIcon(AT_WEAKNESS, "Weakness", "Attack power reduction"); //	1	1	1	
	this->BindIcon(AT_INNOVATION, "Innovation", "Defensibility reduction"); //	1	1	1	
	this->BindIcon(78, "Cherry Blossom Wine", "Maximum Mana increase +700"); //	0	0	1	
	this->BindIcon(79, "Cherry Blossom Rice Cake", "Maximum Life increase +700"); //	0	0	1	
	this->BindIcon(80, "Cherry Blossom Flower Petal", "Cherry Blossom Flower Petal"); //	0	0	1	x
	//char Buff[150] = {0};
	//sprintf_s(Buff, "Add stats. / Strength / Agility / Vitlity / Enery / Command ", c_GuildBuff.Strength, c_GuildBuff.Agility, c_GuildBuff.Vitality, c_GuildBuff.Energy, c_GuildBuff.Command);
	//this->BindIcon(84, "Guild Buff", Buff); //	1	1	1
	this->BindIcon(AT_BERSERKER, "Berserker", "Curse spell, Wizardry/Attack power and Maximum Mana increases/Defense and Maximum Life decreases"); //	0	1	1	
	this->BindIcon(AT_EXPANSION_WIZARDRY, "Expansion of Wizardry", "Minimum Wizardry increases."); //Expansion of Wizardry	0	1	1	
	this->BindIcon(83, "Flame Strike", ""); //	1	1	1	
	this->BindIcon(85, "Lightning Shock", ""); //	1	1	1	
	this->BindIcon(86, "Cold", "Detrimental cold reduces /the mobility speed."); //Cold	1	1	1	
	this->BindIcon(87, "Seal of Healing", "EXP gain increase 150%%/Automatic Life recovery at 5%%"); //	0	0	1	
	this->BindIcon(88, "Seal of Divinity", "Item gain increase at 150%%/Automatic Mana recovery at 5%%"); //	0	0	1	
	this->BindIcon(89, "Scroll of Battle", "Critical damage increase at 20%%"); //	0	1	1	
	this->BindIcon(90, "Scroll of Strength", "Excellent damage increase at 20%%"); //	0	1	1	

	this->BindIcon(91, "Blessing of Christmas", ""); //	0	1	1	Attack power and Defensibility increases
	this->BindIcon(92, "Santa Healing", "Maximum Life increase +500"); //	0	1	1	
	this->BindIcon(93, "Santa Protection", "Maximum Mana increase +500"); //	0	1	1	
	this->BindIcon(94, "Santa Strengthener", "Attack power +30"); //	0	1	1	
	this->BindIcon(95, "Santa Defense", "Defensibility +100"); //	0	1	1	
	this->BindIcon(96, "Santa Quickness", "Attack speed +15"); //	0	1	1	
	this->BindIcon(97, "Santa Fortune", "AG recovery speed increase +10"); //	0	1	1	
	this->BindIcon(98, "Watch", "You may enter and watch a duel in Arena."); //	0	0	1	
	this->BindIcon(99, "Talisman of Guardian", "No penalty for dying."); //	0	0	1	
	this->BindIcon(AT_CSHOP_MASTER_SEAL_OF_WEALTH, "Master Seal of Wealth", "No penalty for dying.");
	this->BindIcon(EFFECT_FITNESS, "Increases Health", "Increase Health stat.");
	this->BindIcon(EFFECT_GREATER_DEFENSE_SUCCESS_RATE, "Increase Defence Rate", "Increases maximum defend rate.");
	this->BindIcon(EFFECT_MAGIC_CIRCLE_IMPROVED, "Expansion of Wizardry", "Increases min Wizardry and max Wizardry.");
	this->BindIcon(EFFECT_MAGIC_CIRCLE_ENHANCED, "Expansion of Wizardry", "Increases min Wizardry and max Wizardry/and critical damage rate.");
	this->BindIcon(EFFECT_GREATER_CRITICAL_DAMAGE_MASTERED, "Critical Damage Increase", "Increases critical damage and critical damage rate.");
	this->BindIcon(EFFECT_SWORD_POWER_IMPROVED, "Berserker", "Curse spell, Wizardry/Attack power and Maximum Mana increases/Defense and Maximum Life decreases");
	this->BindIcon(EFFECT_SWORD_POWER_ENHANCED, "Berserker", "Curse spell, Wizardry/Attack power and Maximum Mana increases/Defense and Maximum Life decreases");
	this->BindIcon(EFFECT_SWORD_POWER_MASTERED, "Berserker", "Curse spell, Wizardry/Attack power and Maximum Mana increases/Defense and Maximum Life decreases");
	this->BindIcon(EFFECT_FITNESS_IMPROVED, "Increases Health", "Increase Health stat.");
	
/*
	this->BindIcon(AT_INCREASE_ATTACK, "战神之力", "提升攻击力");
	this->BindIcon(AT_INCREASE_DEFENSE, "守护之光", "提升防御力");
	this->BindIcon(AT_NPC_HELP, "幻影导师效果", "提升攻击力与防御力");
	this->BindIcon(AT_ICE, "冰", "移动速度变慢");
	this->BindIcon(AT_WIZARD_DEFENSE, "守护之魂", "吸收伤害");
	this->BindIcon(AT_INCREASE_CRITICAL_DMG, "致命圣印", "增加会心一击伤害");
	this->BindIcon(AT_INFINITY_ARROW, "无影箭", "不消耗弓箭");
	this->BindIcon(AT_INCREASE_AG_SPEED, "AG恢复速度增加", "");
	this->BindIcon(AT_SWELL_LIFE, "生命之光", "提升最大体力");
	this->BindIcon(AT_SWELL_MANA, "增益魔法", "提升最大魔力");
	this->BindIcon(AT_POTION_OF_BLESS, "祝福药水", "攻击力提升为 20%%");

	this->BindIcon(AT_POTION_OF_SOUL, "灵魂药水", "AG恢复速度 +8/雷,冰抵抗力提升 /攻及速度增加+20");
	this->BindIcon(12, "解除魔法", "");
	this->BindIcon(13, "城门开/关状态", "");
	this->BindIcon(14, "守城", "目前正在守城");
	this->BindIcon(15, "攻城战盟1", "目前正在攻城");
	this->BindIcon(16, "攻城战盟2", "目前正在攻城");
	this->BindIcon(17, "攻城战盟3", "目前正在攻城");
	this->BindIcon(18, "透明术", "隐身状态");
	this->BindIcon(19, "圣导师攻城技能", "");
	this->BindIcon(20, "皇冠登录状态", "");//

	this->BindIcon(21, "可绑定神狼护台", "");//Altar of Wolf contract enabled
	this->BindIcon(22, "无法绑定神狼护台", "");//Altar of Wolf contract disabled
	this->BindIcon(23, "神狼护台绑定状态", "");//Altar of Wolf contract Status
	this->BindIcon(24, "试图绑定神狼护台", "");//Altar of Wolf contract attempt
	this->BindIcon(25, "已占领神狼护台", "");//Altar of Wolf besiegement Status
	this->BindIcon(26, "神狼护台英雄绑定状态", "");//Altar of Wolf hero contract Status
	this->BindIcon(27, "狼魂要塞NPC隐身", "");//Cry Wolf NPC transparency
	this->BindIcon(28, "GM", "游戏管理员");
	this->BindIcon(29, "经验印章", "经验值获得提升为 150%%");
	this->BindIcon(30, "神圣印章", "经验值获得提升为 200%% /道具获得提升150%%");//

	this->BindIcon(31, "贡献印章", "无法获得经验值");//
	this->BindIcon(32, "寺院 - 迅速咒语", "");//Temple - Spell of Quickness
	this->BindIcon(33, "寺院– 升化咒语", "");//Temple - Spell of Sublimation
	this->BindIcon(34, "保护咒语", "伤害吸收100%%");//Spell of Protection
	this->BindIcon(35, "南瓜灯的祝福", "攻击速度上升 +10");//Jack O'Lantern Blessings
	this->BindIcon(36, "南瓜灯的愤怒", "攻击力上升 +25");//Jack O'Lantern Wrath
	this->BindIcon(37, "南瓜灯的呐喊", "防御力上升 +100");//Jack O'Lantern Cry
	this->BindIcon(38, "南瓜灯的食物", "最大生命力增加 +500");//Jack O'Lantern Food
	this->BindIcon(39, "南瓜灯的饮料", "最大魔法值增加 +500");//Jack O'Lantern Drink
	this->BindIcon(40, "经验印章", "经验值获得提升为 150%%");//Seal of Ascension

	this->BindIcon(41, "神圣印章", "经验值获得提升为 200%% /道具获得提升150%%"); //Seal of Wealth	0	0	1	EXP gain increase 200%%/Item gain increase 150%%
	this->BindIcon(42, "贡献印章", "无法获得经验值"); //Seal of Sustenance	0	0	1	EXP gain disabled
	this->BindIcon(43, "移动印章", "可移动"); //Seal of Mobility	0	0	1	Mobility enabled
	this->BindIcon(44, "加速卷轴", "攻击速度提升 +15"); //Scroll of Quickness	0	1	1	Attack speed increase +15
	this->BindIcon(45, "防御卷轴", "防御力提升 +60"); //Scroll of Defense	0	1	1	Defensibility increase +60
	this->BindIcon(46, "愤怒卷轴", "攻击力提升 +30"); //Scroll of Wrath	0	1	1	Attack power increase +30
	this->BindIcon(47, "魔力卷轴", "魔法攻击力提升 +30"); //Scroll of Wizardry	0	1	1	Wizardry increase +30
	this->BindIcon(48, "体力卷轴", "体力值增加 +200"); //Scroll of Health	0	1	1	HP
	this->BindIcon(49, "魔法卷轴", "魔法值增加 +300"); //	0	1	1	
	this->BindIcon(50, "力量圣水", "力量值 +50"); //	0	1	1	

	this->BindIcon(51, "敏捷圣水", "敏捷值 +50"); //	0	1	1	
	this->BindIcon(52, "体力圣水", "体力值 +50"); //	0	1	1	
	this->BindIcon(53, "智力圣水", "智力值 +50"); //	0	1	1	
	this->BindIcon(54, "统率圣水", "统率值+50"); //	0	1	1	
	this->BindIcon(AT_POISON, "毒", "中毒状态"); //	1	1	1	
	this->BindIcon(AT_ICE, "冰", "移动速度变慢");
	this->BindIcon(AT_ICE_ARROW, "冰封箭", "无法移动"); //Iced Arrow	1	1	1	Mobility disabled
	this->BindIcon(58, "防御力减少", "防御力随机降低10%%"); //	1	1	1	
	this->BindIcon(59, "攻击力减少", ""); //	1	0	1	
	this->BindIcon(60, "魔法攻击力减少", ""); //	1	0	1	


	this->BindIcon(61, "束缚", "无法移动"); //	1	1	1	
	this->BindIcon(62, "魔法防御", ""); //	1	0	1	
	this->BindIcon(63, "怪物魔法攻击抵抗效果", ""); //	1	1	1	
	this->BindIcon(64, "怪物物理攻击抵抗效果", ""); //	1	1	1	
	this->BindIcon(65, "束缚咒语", "无法移动"); //	1	1	1	
	this->BindIcon(66, "狼魂要塞神座保护状态", "狼魂要塞神座保护状态"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(67, "狼魂要塞神座保护状态", "狼魂要塞神座保护状态"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(68, "狼魂要塞神座保护状态", "狼魂要塞神座保护状态"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(69, "狼魂要塞神座保护状态", "狼魂要塞神座保护状态"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	this->BindIcon(70, "狼魂要塞神座保护状态", "狼魂要塞神座保护状态"); //Cry Wolf Divine Protection Status	0	1	1	Cry Wolf Divine Protection Status
	

	this->BindIcon(AT_DAMAGE_REFLECTION, "反射之镜", "反射伤害的部份"); //	0	1	1	
	this->BindIcon(AT_SLEEP, "催眠术", "暂时睡觉"); //	1	1	1	
	this->BindIcon(AT_BLIND, "致盲", "视力模糊降低攻击成功率"); //	1	1	1	
	this->BindIcon(AT_REQUIEM, "刺袭", "幻兽异灵的攻击"); //	1	1	1	
	this->BindIcon(AT_EXPLOSION, "爆裂", "幻兽火龙兽的攻击"); //	1	1	1	
	this->BindIcon(AT_WEAKNESS, "虚弱术", "攻击力降低"); //	1	1	1	
	this->BindIcon(AT_INNOVATION, "精神术", "防御力降低"); //	1	1	1	
	this->BindIcon(78, "樱花酒", "最大魔法值增加 +700"); //	0	0	1	
	this->BindIcon(79, "樱花饼", "最大生命力增加 +700"); //	0	0	1	
	this->BindIcon(80, "樱花花瓣", "攻击力提升 +40"); //	0	0	1	x
	//char Buff[150] = {0};
	//sprintf_s(Buff, "Add stats. / Strength / Agility / Vitlity / Enery / Command ", c_GuildBuff.Strength, c_GuildBuff.Agility, c_GuildBuff.Vitality, c_GuildBuff.Energy, c_GuildBuff.Command);
	//this->BindIcon(84, "Guild Buff", Buff); //	1	1	1
	this->BindIcon(AT_BERSERKER, "狂暴战士", "提升诅咒能力,魔法攻击力/提升攻击力,增加最大魔法值/降低防御，最高生命值"); //	0	1	1	
	this->BindIcon(AT_EXPANSION_WIZARDRY, "法神附体", "提升最小魔法攻击力"); //Expansion of Wizardry	0	1	1	
	this->BindIcon(83, "火剑袭", ""); //	1	1	1	
	this->BindIcon(85, "烈光闪", ""); //	1	1	1	
	this->BindIcon(86, "严寒", "因残酷的寒冷/移动速度降低"); //Cold	1	1	1	
	this->BindIcon(87, "大师经验印章", "经验值获得提升为 150%%/生命值自动恢复提升为 5%%"); //	0	0	1	
	this->BindIcon(88, "大师神圣印章", "物品掉落提升为 150%%/魔法值自动恢复提升为 5%%"); //	0	0	1	
	this->BindIcon(89, "幸运一击卷轴", "提升会心一击攻击力 20%%"); //	0	1	1	
	this->BindIcon(90, "卓越一击卷轴", "提升卓越一击攻击力 20%%"); //	0	1	1	

	this->BindIcon(91, "雪之祝福", "提升攻击力与防御力"); //	0	1	1	Attack power and Defensibility increases
	this->BindIcon(92, "雪之治疗", "提升最大生命值 500"); //	0	1	1	
	this->BindIcon(93, "雪之保护", "提升最大魔法值 500"); //	0	1	1	
	this->BindIcon(94, "雪之强化", "攻击力  +30"); //	0	1	1	
	this->BindIcon(95, "雪之防御", "防御力  +100"); //	0	1	1	
	this->BindIcon(96, "雪之加速", "攻击速度  +15"); //	0	1	1	
	this->BindIcon(97, "雪之幸运", "提升AG恢复速度 10"); //	0	1	1	
	this->BindIcon(98, "观战", "可进入角斗场观战"); //	0	0	1	
	this->BindIcon(99, "守护符咒", "角色死亡时无惩罚"); //	0	0	1	
	this->BindIcon(AT_CSHOP_MASTER_SEAL_OF_WEALTH, "Master Seal of Wealth", "角色死亡时无惩罚");
	this->BindIcon(EFFECT_FITNESS, "体力提高", "体力增加");
	this->BindIcon(EFFECT_GREATER_DEFENSE_SUCCESS_RATE, "防御率提高", "提高最大防御率");
	this->BindIcon(EFFECT_MAGIC_CIRCLE_IMPROVED, "法神附体", "提高最小魔法攻击力与最大魔法攻击力");
	this->BindIcon(EFFECT_MAGIC_CIRCLE_ENHANCED, "法神附体", "提高最小魔法攻击力与最大魔法攻击力，/提高会心一击几率");
	this->BindIcon(EFFECT_GREATER_CRITICAL_DAMAGE_MASTERED, "提高会心一击伤害", "提高会心一击伤害与几率");
	this->BindIcon(EFFECT_SWORD_POWER_IMPROVED, "狂暴", "提高诅咒能力与魔法攻击力，/提高攻击力与最大魔法攻击力，/降低防御力与最大生命值");
	this->BindIcon(EFFECT_SWORD_POWER_ENHANCED, "狂暴", "提高诅咒能力与魔法攻击力，/提高攻击力与最大魔法攻击力，/降低防御力与最大生命值");
	this->BindIcon(EFFECT_SWORD_POWER_MASTERED, "狂暴", "提高诅咒能力与魔法攻击力，/提高攻击力与最大魔法攻击力，/降低防御力与最大生命值");
	this->BindIcon(EFFECT_FITNESS_IMPROVED, "体力提高", "体力增加");
	*/
	// -> ExTeam Buff

	this->BindIcon(112, "Platinum Party", "Exp: +10%% / DropZen: +10%% / Damage: +3%% / Defence: +3%% / Wizard Damage: +3%%" ); 

	this->BindIcon(129, "Ignore Enemy's Defense", "Increases 5%% chance to ignore enemy's defense and inflict damage." ); 

	this->BindIcon(171, "Bronze Vip", "Exp: +15%% / DropZen: +5%% / Damage: +5%% / Defence: +5%% / Wizard Damage: +5%%"); //
	this->BindIcon(172, "Silver Vip", "Exp: +25%% / DropZen: +10%% / Damage: +10%% / Defence: +10%% / Wizard Damage: +10%%"); //
	this->BindIcon(173, "Gold Vip", "Exp: +35%% / DropZen: +15%% / Damage: +15%% / Defence: +15%% / Wizard Damage: +15%%"); //

	this->BindIcon(AT_GUILD_BUFF, "Guild Buff", "Description new buff");

	this->BindIcon(AT_NPC_BUFF_EXP, "Experience Buff", "Experience: + 15%%");
	this->BindIcon(AT_NPC_BUFF_DAMAGE, "Damage Buff", "Damage: +10%%/Wizard Damage: +10%%");
	this->BindIcon(AT_NPC_BUFF_DEFENCE, "Defence Buff", "Defence: +10%%");
	this->BindIcon(AT_NPC_BUFF_EXL_CRIT, "Battle Buff", "Exellent Damage Rate: +5%%/Critical Damage Rate: +5%%");
	this->BindIcon(AT_NPC_BUFF_DROP, "Drop Buff", "Zen Drop: +50%%/Jewel Drop: +150%%");
	this->BindIcon(AT_NPC_BUFF_DOUBLE, "Double Buff", "Double Damage: +5%%");

	this->BindIcon(AT_NOOB_BUFF, "NooB Buff", "Experience: + 30%% / Damage: +15%% / Defence: +15%% / Wizard Damage: +15%% /  Defence: +15%%");
	this->BindIcon(AT_QUEST_BUFF, "Quest Buff", "Description new buff");
	//this->BindIcon(NULL, "", ""); //
}
// ------------------------------------------------------------------------------

void BuffIcon::BindIcon(BYTE Index, char* Name, char* Text)
{
	this->DataBuff[this->LoadBuffCount].Index = Index;
	strncpy(this->DataBuff[this->LoadBuffCount].Name, Name, 50);
	strncpy(this->DataBuff[this->LoadBuffCount].Text, Text, 200);

	this->LoadBuffCount++;
}
// ------------------------------------------------------------------------------
void BuffIcon::Draw(float StartX, float StartY)
{
	//g_Console.AddMessage(5,"%f - %f [%d %d]",StartX,StartY,pCursorX,pCursorY);

	//if (gInterface.CheckWindow(57) || gInterface.CheckWindow(2))
	//{
	//	return;
	//}

	const float High	= 28.0; //28
	const float Whith	= 20.0; //20

	int DataIndex = 0;
	int InfoIndex = 0;
	float InfoX = 0;
	float InfoY = 0;

	int BuffDraw = 0;

	int line = 0;

	for(int i = 0; i < MAX_STATE_COUNT; i++)	
	{
		if(this->UserBuff[i].Index == NULL)
		{
			continue;
		}

		float X = 0;
		float Y = StartY;

		/*if(pGameResolutionMode > 1)
		{
			X = GAME_X_IN_FULL_X(250) + ( (Whith + 2) * BuffDraw);	// pWinWidth * 250 / 640.0  + ( (Whith + 2) * BuffDraw);
		}
		else
		{
			X = GAME_X_IN_FULL_X(200) + ( (Whith + 2) * BuffDraw);	//X = pWinWidth * 200 / 640.0  + ( (Whith + 2) * BuffDraw);
		}*/

		//X = pWinWidth / 2 + ( (Whith + 5) * BuffDraw) ;

		//X -= this->UserBuffCount * Whith / 2 - 1;

		/*int test = 0;
		if (BuffDraw>8)
		{
			test = 8;
			Y+=High+10;
		}*/

		//X = WIN_DRAW_CORD(StartX) + ( (Whith + 5) * (BuffDraw- test));

		//X = StartX + ( (Whith + 5.5) * (BuffDraw- test));
		X = StartX + BuffDraw * (20.0 + 5.0);
		Y = StartY + line * (28.0 + 5.0);

		//X -= this->UserBuffCount * Whith / 2 - 1;

		

		int BuffIndex = this->UserBuff[i].Index;

		int Model = 0;
		int v6 = 0;

		if( BuffIndex > 0 && BuffIndex <= 80)
		{
			Model = 0x7BED;
			v6 = (BuffIndex - 1) % 80;
		}
		else if (BuffIndex > 80 && BuffIndex <= 160)
		{
			Model = 0x7BEE;
			v6 = (BuffIndex - 81) % 80;
		}
		else
		{
			Model = 0x7BEF;
			v6 = (BuffIndex - 161) % 80;
		}
    
		float CritX = (double)(v6 % 10) * (Whith) / 256;
		float CritY = (double)(v6 / 10) * (High) / 256;

		float standartWhith = Whith / 256;
		float standartHight = High / 256;

		//pDrawCircle(Model, X, Y, Whith, High, CritX, CritY, standartWhith, standartHight, 1, 1, 0.0);

		int EffectValue = (BuffIndex - 1) % 80;
		float SourceX = (double)(EffectValue % 10) * Whith / 256.0;
		float SourceY = (double)(EffectValue / 10) * High / 256.0;
		float SourceWidth = Whith / 256.0;
		float SourceHeight = High / 256.0;
		pDrawCircle((BuffIndex - 1) / 80 + 31725, X, Y, Whith, High, SourceX, SourceY, SourceWidth, SourceHeight, 1, 1, 0);

		// ----

		float LineX = X; // 640 * X / pWinWidth;
		float LineY =  Y+High;	/* 480 * (Y + High) / pWinHeight;*/

		float LineWind = Whith;// 640 * Whith / pWinWidth ;

		int pBuffHp = 100;
	
		if(this->UserBuff[i].MaxTime > 0 && this->UserBuff[i].Time > 0)
		{
			pBuffHp = (this->UserBuff[i].Time * 100) / this->UserBuff[i].MaxTime;
		}

		//LineX +=1; my

		//g_Console.AddMessage(5,"HP = %d",pBuffHp);

		//pDrawColorButton(0x7880, LineX, LineY, LineWind, 1.0, 0, 0,  Color4f(0, 0, 0, 255));	
		//pDrawExtraColor(0x7880, LineX, LineY, LineWind * pBuffHp / 100, 0.5, 0, 0, 0, 0, Color4f(0, 255, 0, 255));	//(Wind * pHP) / 100
		pSetBlend(1);
		glColor4f(0.0, 1.0, 0.0, 1.0);
		pDrawBarForm(LineX, LineY, LineWind * pBuffHp / 100.0f, 2.0f, 0.0f, 0);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		//pGLSwitchBlend();

		//g_Console.AddMessage(3,"X = %d Y = %d X2 = %f Y2 = %f [%d|%d]",X, Y, X+Whith,Y+High,WIN_DRAW_CORD(pCursorX),WIN_DRAW_CORDY(pCursorY));
		// ----
		if(gInterface.IsWorkZone(X, Y, X + Whith, Y + High-6))
		{
			DataIndex = this->UserBuff[i].Index;
			InfoIndex = i;
			InfoX = X;
			InfoY = Y;
			//g_Console.AddMessage(1, "[InfoX %d][InfoY %d][InfoX + Whith %d][InfoY + High %d]",InfoX, InfoY, InfoX + Whith, InfoY + High);
		}

		BuffDraw++;
		if (BuffDraw>=8)
			{
				line=1;
				BuffDraw=0;
			}

		//g_Console.AddMessage(2, "[InfoX %d][InfoY %d][InfoX + Whith %d][InfoY + High %d]",InfoX, InfoY, InfoX + Whith, InfoY + High);
	}

	// ----



	//g_Console.AddMessage(3, "[InfoX %d][InfoY %d][InfoX + Whith %d][InfoY + High %d]",InfoX, InfoY, InfoX + Whith, InfoY + High);
	//gInterface.IsWorkFullZone(InfoX, InfoY, InfoX + Whith, InfoY + High)
	if(gInterface.IsWorkZone(InfoX, InfoY, InfoX + Whith, InfoY + High))
	{
		pSetBlend(true);

		int DrawInfoX = InfoX; // 640 * InfoX / pWinWidth;
		int DrawInfoY = InfoY + 33;

		//g_Console.AddMessage(5,"DataIndex = %d, InfoIndex = %d",DataIndex,InfoIndex);
		this->DrawBuffInfo(DataIndex, InfoIndex, DrawInfoX, DrawInfoY,line);
	}

	pSetBlend(false);
}
// ------------------------------------------------------------------------------
void BuffIcon::DrawBuffInfo(int BuffIndex, int InfoIndex, float iX, float iY, int line)
{
	int posYEx = iY;
	int Wind =  100;

	int DrawBuffIndexData = -1;

	for(int b = 0; b < this->LoadBuffCount; b++)
	{
		if( this->DataBuff[b].Index == BuffIndex)
		{
			DrawBuffIndexData = b;
			break;
		}
	}

	if(DrawBuffIndexData == -1)
	{
		return;
	}

	// ----

	int Br = 0;

	int LenBuff = 0;
	int LenName = 0;
	int LenText = 0;
	int LenData = 0;

	char Buff[256] = { 0 };
	char BuffName[256] = { 0 };
	char BuffText[256] = { 0 };
	char BuffDate[256] = { 0 };

	strncpy(BuffName, this->DataBuff[DrawBuffIndexData].Name, 50);
	strncpy(BuffText, this->DataBuff[DrawBuffIndexData].Text, 200);

	strncpy(Buff, this->DataBuff[DrawBuffIndexData].Text, 200);

	char * Line = strtok(Buff, "/");

	while( Line != NULL )
	{
		LenText = strlen(Line);

		if(LenText > LenBuff)
		{
			LenBuff = LenText;
		}
		Br += 1;
		Line = strtok(NULL, "/");
	}
	// --
	if(this->UserBuff[InfoIndex].Time > 0)
	{
		time_t t = UserBuff[InfoIndex].Time;
		tm* m = gmtime(&t);

		if(m->tm_yday > 0)
		{
			sprintf(BuffDate, "%2d Day %2d Hour %2d Minutes %2d Seconds",m->tm_yday,m->tm_hour,m->tm_min,m->tm_sec);
		}
		else if(m->tm_hour > 0)
		{
			sprintf(BuffDate, "%2d Hour %2d Minutes %2d Seconds",m->tm_hour,m->tm_min,m->tm_sec);
		}
		else if(m->tm_min > 0)
		{
			sprintf(BuffDate, "%2d Minutes %2d Seconds",m->tm_min,m->tm_sec);
		}
		else if(m->tm_sec > 0)
		{
			sprintf(BuffDate, "%2d Seconds",m->tm_sec);
		}

		LenData = strlen(BuffDate);
	}

	LenName = strlen(BuffName);
	LenText = LenBuff;

	//g_Console.Output(cGREEN, "LenData: %d | LenText: %d", LenData, LenText );

	if(LenText == NULL || LenName > LenText)
	{
		LenText = LenName;
	}
	if( LenData > LenText )
	{
		LenText = LenData;
	}

	Wind = LenText * 4;

	if(*(DWORD*)MAIN_RESOLUTION > 5)
	{
		Wind = LenText * 3;
	}

	// -----

	if(DrawBuffIndexData >= 0 && DrawBuffIndexData < MAX_BUFF_INDEX)
	{

		int _20 = 20;

		if(this->UserBuff[InfoIndex].Time <= 0)
		{
			//g_Console.AddMessage(5,"Time <= 0");
			_20 = 10;
		}

		float TextCoord = iX-(Wind/2)+10;

		//pDrawColorButton(0x7880, iX, iY, Wind, _20 + Br * 10,
		//	0, 0, Color4f(0, 0, 0, 150));	
		pSetBlend(1);
		glColor4f(0.0, 0.0, 0.0, 1.0);
		pDrawBarForm(iX-(Wind/2)+10, iY, Wind, _20 + Br * 10, 0.0f, 0);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		gInterface.DrawFormatEx(eBlue, TextCoord, iY+1, Wind, 3, BuffName);

		posYEx	+=	10;

		posYEx = gInterface.DrawFormat_Ex(eWhite, TextCoord, posYEx, Wind, 3, BuffText);
		//gInterface.DrawFormatEx(eWhite, TextCoord, posYEx, Wind, 3, BuffText);
		//posYEx += 10 * Br;
		if(this->UserBuff[InfoIndex].Time > 0)
		{
			gInterface.DrawFormatEx(eSocket, TextCoord, posYEx, Wind, 3, BuffDate);
		}
	}
}
// ------------------------------------------------------------------------------
unsigned int BuffIcon::Timer(void *Args)
{
	while(true)
	{
		for(int i = 0; i < MAX_STATE_COUNT; i++)
		{
			if(g_BuffIcon.UserBuff[i].Index != NULL)
			{
				if(g_BuffIcon.UserBuff[i].Time > 0)
				{
					g_BuffIcon.UserBuff[i].Time--;
					if(g_BuffIcon.UserBuff[i].Time <= 0)
					{
						g_BuffIcon.UserBuff[i].Index = NULL;
						g_BuffIcon.UserBuff[i].Time = 0;

						g_BuffIcon.UserBuffCount--;
					}
				}
			}

			Sleep(1);
		}

		Sleep(999);
	}	

	return 0;
}
// ------------------------------------------------------------------------------
void BuffIcon::Recv(PMSG_SEND_BUFF_ICON* DataRecv)
{
	if(DataRecv->byEffectOption == 0)
	{
		for( int i = 0; i < MAX_STATE_COUNT; i++ )
		{
			if(this->UserBuff[i].Index == NULL || this->UserBuff[i].Index == DataRecv->btEffectIndex)
			{
				if(this->UserBuff[i].Index == NULL)
				{
					this->UserBuffCount++;
				}
				this->UserBuff[i].Index = DataRecv->btEffectIndex;
				this->UserBuff[i].Time = DataRecv->iLeftTime;
				this->UserBuff[i].MaxTime = DataRecv->iLeftTime;
				return;
			}
		}
	}
	else
	{
		for( int i = 0; i < MAX_STATE_COUNT; i++ )
		{
			if(this->UserBuff[i].Index == DataRecv->btEffectIndex)
			{
				this->UserBuff[i].Index = NULL;
				this->UserBuff[i].Time = 0;
				this->UserBuff[i].MaxTime = 0;

				this->UserBuffCount--;
				return;
			}
		}
	}
}
// ------------------------------------------------------------------------------
void BuffIcon::DeleteAllBuff()
{
	this->UserBuffCount = 0;
	for( int i = 0; i < MAX_STATE_COUNT; i++ )
	{
		this->UserBuff[i].Index = NULL;
		this->UserBuff[i].Time = 0;
		this->UserBuff[i].MaxTime = 0;
	}
}
// ------------------------------------------------------------------------------
void BuffIcon::DrawBuffInfoEx(int BuffIndex, float iX, float iY, int iTime)
{
	if (gInterface.CheckWindow(57) || gInterface.CheckWindow(2))
	{
		return;
	}

	int posYEx = iY;
	int Wind =  100;

	int DrawBuffIndexData = -1;

	for(int b = 0; b < this->LoadBuffCount; b++)
	{
		if( this->DataBuff[b].Index == BuffIndex)
		{
			DrawBuffIndexData = b;
			break;
		}
	}

	// ----

	int Br = 0;

	int LenBuff = 0;
	int LenName = 0;
	int LenText = 0;
	int LenData = 0;

	char Buff[256] = { 0 };
	char BuffName[256] = { 0 };
	char BuffText[256] = { 0 };
	char BuffDate[256] = { 0 };

	strncpy(BuffName, this->DataBuff[DrawBuffIndexData].Name, 50);
	strncpy(BuffText, this->DataBuff[DrawBuffIndexData].Text, 200);

	strncpy(Buff, this->DataBuff[DrawBuffIndexData].Text, 200);

	char * Line = strtok(Buff, "/");

	while( Line != NULL )
	{
		LenText = strlen(Line);

		if(LenText > LenBuff)
		{
			LenBuff = LenText;
		}
		Br += 1;
		Line = strtok(NULL, "/");
	}
	// --
	if(iTime > 0)
	{
		time_t t = iTime;
		tm* m = gmtime(&t);

		if(m->tm_yday > 0)
		{
			sprintf(BuffDate, "%2d Day %2d Hour %2d Minutes %2d Seconds",m->tm_yday,m->tm_hour,m->tm_min,m->tm_sec);
		}
		else if(m->tm_hour > 0)
		{
			sprintf(BuffDate, "%2d Hour %2d Minutes %2d Seconds",m->tm_hour,m->tm_min,m->tm_sec);
		}
		else if(m->tm_min > 0)
		{
			sprintf(BuffDate, "%2d Minutes %2d Seconds",m->tm_min,m->tm_sec);
		}
		else if(m->tm_sec > 0)
		{
			sprintf(BuffDate, "%2d Seconds",m->tm_sec);
		}

		LenData = strlen(BuffDate);
	}

	LenName = strlen(BuffName);
	LenText = LenBuff;

	//g_Console.Output(cGREEN, "LenData: %d | LenText: %d", LenData, LenText );

	if(LenText == NULL || LenName > LenText)
	{
		LenText = LenName;
	}
	if( LenData > LenText )
	{
		LenText = LenData;
	}

	Wind = LenText * 4;

	if(*(DWORD*)MAIN_RESOLUTION > 5)
	{
		Wind = LenText * 3;
	}

	// -----

	if(DrawBuffIndexData >= 0 && DrawBuffIndexData < MAX_BUFF_INDEX)
	{
		int _20 = 20;

		if(iTime < 0)
		{
			_20 = 10;
		}

		pDrawColorButton(0x7880, iX, iY, Wind, _20 + Br * 10, NULL, NULL, Color4f(0, 0, 0, 255));	

		gInterface.DrawFormatEx(eBlue, iX, iY, Wind, 3, BuffName);

		posYEx+=10;

		posYEx = gInterface.DrawFormat_Ex(eWhite, iX, posYEx, Wind, 3, BuffText);
		//posYEx += 10 * Br;
		if(iTime > 0)
		{
			gInterface.DrawFormatEx(eSocket, iX, posYEx, Wind, 3, BuffDate);
		}
	}
}
// ------------------------------------------------------------------------------
char* BuffIcon::GetBuffName(int ID)
{
	int BuffIndexData = -1;

	for(int i = 0; i < this->LoadBuffCount; i++)
	{
		if( this->DataBuff[i].Index == ID)
		{
			return this->DataBuff[i].Name;
		}
	}

	return NULL;
}
// ------------------------------------------------------------------------------
char* BuffIcon::GetAddedBuffName(int buff)
{
	if(buff == eAddExp)
	{
		return this->GetBuffName(AT_NPC_BUFF_EXP);
	}
	else if(buff == eAddDamage)
	{
		return this->GetBuffName(AT_NPC_BUFF_DAMAGE);
	}
	else if(buff == eAddDefence)
	{
		return this->GetBuffName(AT_NPC_BUFF_DEFENCE);
	}
	else if(buff == eAddBattle)
	{
		return this->GetBuffName(AT_NPC_BUFF_EXL_CRIT);
	}
	else if(buff == eAddDrop)
	{
		return this->GetBuffName(AT_NPC_BUFF_DROP);
	}
	else if(buff == eAddDouble)
	{
		return this->GetBuffName(AT_NPC_BUFF_DOUBLE);
	}

	return NULL;
}
// ------------------------------------------------------------------------------
void BuffIcon::GC_BuffInfo(PMSG_SEND_BUFF_ICON_EX* aRecv)
{
	//g_Console.AddMessage(5,"RECV buffs Index = %d [%s]",aRecv->btEffectIndex,aRecv->szBuffName);
	int BuffIndex = aRecv->btEffectIndex;
	int DataIndex = -1;

	for(int b = 0; b < this->LoadBuffCount; b++)
	{
		if( this->DataBuff[b].Index == BuffIndex)
		{
			DataIndex = b;
			break;
		}
	}

	if(DataIndex == -1)
	{
		return;
	}

	bool bDraw = false;
	char szName[20];
	char szInfo[5][200];

	ZeroMemory(&szName, sizeof(szName));
	ZeroMemory(&szInfo, sizeof(szInfo));

	memcpy(szName,	aRecv->szBuffName, sizeof(aRecv->szBuffName));

	//g_Console.AddMessage(5,"Buff = %d",BuffIndex);
	if( BuffIndex == AT_VIP_SILVER )
	{
		// --
	}
	else if( BuffIndex == AT_VIP_GOLD )
	{
		// --
	}
	else if( BuffIndex == AT_VIP_PLATINUM )
	{
		// --
	}
	else if( BuffIndex == AT_PARTY_EXP_BONUS_EX )
	{
		// --
	}
	else if( BuffIndex == AT_GUILD_BUFF )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_EXP )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_DAMAGE )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_DEFENCE )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_EXL_CRIT )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_DROP )
	{
		// --
	}
	else if( BuffIndex == AT_NPC_BUFF_DOUBLE )
	{
		// --
	}
	else if( BuffIndex == AT_NOOB_BUFF )
	{
		// --
	}
	else if( BuffIndex == AT_QUEST_BUFF )
	{
		// --
	}
	else
	{
		switch(BuffIndex)
		{
		case EFFECT_GREATER_DAMAGE:
			{
				sprintf(szInfo[0], "Damage : +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[1], "Magic damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[2], "Curse damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_DEFENSE:
			{
				sprintf(szInfo[0], "Defence: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELF_BUFFER:
			{
				sprintf(szInfo[0], "Damage : +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[1], "Magic damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[2], "Curse damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[3], "Defence: +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_MANA_SHIELD:
			{
				sprintf(szInfo[0], "Damage reduction: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_CRITICAL_DAMAGE:
			{
				sprintf(szInfo[0], "Critical damage : +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_LIFE:
			{
				sprintf(szInfo[0], "Add Life : +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_MANA:
			sprintf(szInfo[0], "Add Mana : +%d", aRecv->iValue[0]);
			break;
		case EFFECT_SOUL_POTION:
			{
				sprintf(szInfo[0], "Damage : +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Add magic speed: +%d", aRecv->iValue[0]);
				sprintf(szInfo[2], "Add BP recovery: +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_SEAL_OF_ASCENSION1:
			{
				sprintf(szInfo[0], "Experience Rate : +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_SEAL_OF_WEALTH1:
			{
				sprintf(szInfo[0], "Experience rate : +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Item drop rate : +%d%%%%", aRecv->iValue[1]);
			}
			break;
		case EFFECT_ORDER_OF_PROTECTION:
			{
				sprintf(szInfo[0], "Damage reduction: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN1:
			{
				sprintf(szInfo[0], "Magic Speed: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Attack Speed: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN2:
			{
				sprintf(szInfo[0], "Magic Speed: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Attack Speed: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN3:
			{
				sprintf(szInfo[0], "Defence: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN4:
			{
				sprintf(szInfo[0], "Max HP: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN5:
			{
				sprintf(szInfo[0], "Max Mana: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_SEAL_OF_ASCENSION2:
			{
				sprintf(szInfo[0], "Experience Rate: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_SEAL_OF_WEALTH2:
			{
				sprintf(szInfo[0], "Experience rate : +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Item drop rate : +%d%%%%", aRecv->iValue[1]);
			}
			break;
		case EFFECT_SCROLL_OF_QUICK:
			{
				sprintf(szInfo[0], "Magic Speed: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Attack Speed: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_DEFENSE:
			{
				sprintf(szInfo[0], "Defence: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_DAMAGE:
			{
				sprintf(szInfo[0], "Physi Damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_MAGIC_DAMAGE:
			{
				sprintf(szInfo[0], "Magic Damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_LIFE:
			{
				sprintf(szInfo[0], "Max HP: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_MANA:
			{
				sprintf(szInfo[0], "Max Mana: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_STRENGTH:
			{
				sprintf(szInfo[0], "Strength: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_DEXTERITY:
			{
				sprintf(szInfo[0], "Agility: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_VITALITY:
			{
				sprintf(szInfo[0], "Vitality: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_ENERGY:
			{
				sprintf(szInfo[0], "Energy: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_LEADERSHIP:
			{
				sprintf(szInfo[0], "Command: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_FIRE_SLASH:
			{
				sprintf(szInfo[0], "Defense: -%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_DAMAGE_REFLECT:
			{
				sprintf(szInfo[0], "Reflect Damage: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_BLIND:
			{
				sprintf(szInfo[0], "Attack Success Rate: -%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_LESSER_DAMAGE:
			{
				sprintf(szInfo[0], "Physi Damage: -%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Magic Damage: -%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[2], "Curse Damage: -%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_LESSER_DEFENSE:
			{
				sprintf(szInfo[0], "Defense: -%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHERRY_BLOSSOM1:
			{
				sprintf(szInfo[0], "Max Mana: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHERRY_BLOSSOM2:
			{
				sprintf(szInfo[0], "Max HP: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHERRY_BLOSSOM3:
			{
				sprintf(szInfo[0], "Damage : +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[1], "Magic damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_SWORD_POWER:
			{
				sprintf(szInfo[0], "Physi Damage: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Mana: +%d%%%%", aRecv->iValue[1]);
				sprintf(szInfo[2], "Defense: +%d%%%%", aRecv->iValue[2]);
				sprintf(szInfo[3], "MaxHP: -%d%%%%", aRecv->iValue[3]);
			}
			break;
		case EFFECT_MAGIC_CIRCLE:
			{
				sprintf(szInfo[0], "Min Magic Damage: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_SEAL_OF_LIFE:
			{
				sprintf(szInfo[0], "Experience Rate: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "HP Recovery Rate: +%d%%%%", aRecv->iValue[1]); //check me
			}
			break;
		case EFFECT_SEAL_OF_MANA:
			{
				sprintf(szInfo[0], "Item gain increase at: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "MP Recovery Rate: +%d%%%%", aRecv->iValue[1]); //check me
			}
			break;
		case EFFECT_SCROLL_OF_BATTLE:
			{
				sprintf(szInfo[0], "Critical Damage Rate: +%d", aRecv->iValue[0]); //Need check
			}
			break;
		case EFFECT_SCROLL_OF_STRENGTH:
			{
				sprintf(szInfo[0], "Excellent Damage Rate: +%d", aRecv->iValue[0]); //Need check
			}
			break;
		case EFFECT_CHRISTMAS1:
			{
				sprintf(szInfo[0], "Damage : +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[1], "Magic damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[2], "Curse damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[3], "Defence: +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_CHRISTMAS2:
			{
				sprintf(szInfo[0], "Max HP : +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS3:
			{
				sprintf(szInfo[0], "Max MP : +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS4:
			{
				sprintf(szInfo[0], "Damage : +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[1], "Magic damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
				sprintf(szInfo[2], "Curse damage: +%d~%d", aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS5:
			{
				sprintf(szInfo[0], "Defence: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS6:
			{
				sprintf(szInfo[0], "Physi Speed: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Magic Speed: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS7:
			{
				sprintf(szInfo[0], "BP Recovery: +%d", aRecv->iValue[0]); //need check
			}
			break;
		case EFFECT_MASTER_SEAL_OF_ASCENSION:
			{
				sprintf(szInfo[0], "Master Experience Rate: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SEAL_OF_WEALTH:
			{
				sprintf(szInfo[0], "Master Experience Rate: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Item Drop Rate: +%d%%%%", aRecv->iValue[1]);
			}
			break;
		case EFFECT_GLADIATORS_GLORY:
			{
				sprintf(szInfo[0], "Experience Rate: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_PARTY_EXPERIENCE_BONUS:
			{
				sprintf(szInfo[0], "Experience Rate: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Master Experience Rate: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[2], "Party Bonus Experience Rate: +%d%%%%", aRecv->iValue[1]);
			}
			break;
		case EFFECT_MAX_AG_BOOST_AURA:
			{
				sprintf(szInfo[0], "Max BP: +%d", aRecv->iValue[0]*gObjUser.lpPlayer->Level); //Need check
			}
			break;
		case EFFECT_MAX_SD_BOOST_AURA:
			{
				sprintf(szInfo[0], "Max SD: +%d", aRecv->iValue[0]*gObjUser.lpPlayer->Level); //Need check
			}
			break;
		case EFFECT_SCROLL_OF_HEALING:
			{
				sprintf(szInfo[0], "HP Recovery Rate: +%d", aRecv->iValue[0]); //Need check
				sprintf(szInfo[1], "Max HP: +%d", aRecv->iValue[1]); //Need check
			}
			break;
		case EFFECT_HAWK_FIGURINE:
			{
				sprintf(szInfo[0], "Critical Damage Rate: +%d", aRecv->iValue[0]); //need check
			}
			break;
		case EFFECT_GOAT_FIGURINE:
			{
				sprintf(szInfo[0], "Excellent Damage Rate: +%d", aRecv->iValue[0]); //need check
			}
			break;
		case EFFECT_OAK_CHARM:
			{
				sprintf(szInfo[0], "Max HP: +%d", aRecv->iValue[0]); //Need check
			}
			break;
		case EFFECT_MAPLE_CHARM:
			{
				sprintf(szInfo[0], "Max MP: +%d", aRecv->iValue[0]); //Need check
			}
			break;
		case EFFECT_GOLDEN_OAK_CHARM:
			{
				sprintf(szInfo[0], "Max HP: +%d", aRecv->iValue[0]); //Need check
				sprintf(szInfo[1], "Max SD: +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_GOLDEN_MAPLE_CHARM:
			{
				sprintf(szInfo[0], "Max MP: +%d", aRecv->iValue[0]); //Need check
				sprintf(szInfo[1], "Max BP: +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_WORN_HORSESHOE:
			{
				sprintf(szInfo[0], "Item Drop Rate: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_IGNORE_DEFENSE_RATE:
			{
				sprintf(szInfo[0], "Ignore Defense Rate: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_FITNESS:
			{
				sprintf(szInfo[0], "Vitality: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_DEFENSE_SUCCESS_RATE:
			{
				sprintf(szInfo[0], "Defense Success Rate: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_IRON_DEFENSE:
			{
				sprintf(szInfo[0], "Max HP: +%d", aRecv->iValue[0]); //need check mybe S7
				sprintf(szInfo[1], "Defense: +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_GREATER_LIFE_ENHANCED:
			{
				sprintf(szInfo[0], "Max HP: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Max MP: +%d%%%%", aRecv->iValue[1]);
			}
			break;
		case EFFECT_GREATER_LIFE_MASTERED:
			{
				sprintf(szInfo[0], "Max HP: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Max MP: +%d%%%%", aRecv->iValue[1]);
				sprintf(szInfo[2], "Max BP: +%d%%%%", aRecv->iValue[2]);
			}
			break;
		case EFFECT_MAGIC_CIRCLE_IMPROVED:
			{
				sprintf(szInfo[0], "Min Magic Damage: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Max Magic Damage: +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_MAGIC_CIRCLE_ENHANCED:
			{
				sprintf(szInfo[0], "Min Magic Damage: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Max Magic Damage: +%d", aRecv->iValue[1]);
				sprintf(szInfo[2], "Critical Damage Rate: +%d%%%%", aRecv->iValue[2]);
			}
			break;
		case EFFECT_MANA_SHIELD_MASTERED:
			{
				sprintf(szInfo[0], "Damage Reduction: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Max MP: +%d%%%%", aRecv->iValue[1]);
			}
			break;
		case EFFECT_BLESS:
			{
				sprintf(szInfo[0], "Strength: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Agility: +%d", aRecv->iValue[0]);
				sprintf(szInfo[2], "Vitality: +%d", aRecv->iValue[0]);
				sprintf(szInfo[3], "Energy: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_INFINITY_ARROW_IMPROVED:
			{
				sprintf(szInfo[0], "Physi Damage: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_BLIND_IMPROVED:
			{
				sprintf(szInfo[0], "Attack Success Rate: -%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_CRITICAL_DAMAGE_MASTERED:
			{
				sprintf(szInfo[0], "Critical Damage: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Critical Damage Rate: +%d%%%%", aRecv->iValue[1]);
			}
			break;
		case EFFECT_GREATER_CRITICAL_DAMAGE_EXTENDED:
			{
				sprintf(szInfo[0], "Critical Damage: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Critical Damage Rate: +%d%%%%", aRecv->iValue[1]);
				sprintf(szInfo[2], "Excellent Critical Damage: +%d%%%%", aRecv->iValue[2]);
			}
			break;
		case EFFECT_SWORD_POWER_IMPROVED:
			{
				sprintf(szInfo[0], "Physi Damage: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Mana: +%d%%%%", aRecv->iValue[1]);
				sprintf(szInfo[2], "Defense: +%d%%%%", aRecv->iValue[2]);
				sprintf(szInfo[3], "MaxHP: -%d%%%%", aRecv->iValue[3]);
			}
			break;
		case EFFECT_SWORD_POWER_ENHANCED:
			{
				sprintf(szInfo[0], "Physi Damage: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Mana: +%d%%%%", aRecv->iValue[1]);
				sprintf(szInfo[2], "Defense: +%d%%%%", aRecv->iValue[2]);
				sprintf(szInfo[3], "MaxHP: -%d%%%%", aRecv->iValue[3]);
			}
			break;
		case EFFECT_SWORD_POWER_MASTERED:
			{
				sprintf(szInfo[0], "Physi Damage: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Mana: +%d%%%%", aRecv->iValue[1]);
				sprintf(szInfo[2], "Defense: +%d%%%%", aRecv->iValue[2]);
				sprintf(szInfo[3], "MaxHP: -%d%%%%", aRecv->iValue[3]);
			}
			break;
		case EFFECT_GREATER_DEFENSE_SUCCESS_RATE_IMPROVED:
			{
				sprintf(szInfo[0], "Defense Success Rate : +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_DEFENSE_SUCCESS_RATE_ENHANCED:
			{
				sprintf(szInfo[0], "Defense Success Rate : +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Defense : +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_FITNESS_IMPROVED:
			{
				sprintf(szInfo[0], "Vitality : +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_BLESS_IMPROVED:
			{
				sprintf(szInfo[0], "Strength: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Agility: +%d", aRecv->iValue[0]);
				sprintf(szInfo[2], "Vitality: +%d", aRecv->iValue[0]);
				sprintf(szInfo[3], "Energy: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_LESSER_DAMAGE_IMPROVED:
			{
				//lpObj->EffectOption.DivPhysiDamage += lpEffect->m_value[0];
				//lpObj->EffectOption.DivMagicDamage += lpEffect->m_value[0];
				//lpObj->EffectOption.DivCurseDamage += lpEffect->m_value[0];
			}
			break;
		//case EFFECT_LESSER_DEFENSE_IMPROVED:
		//	lpObj->EffectOption.DivDefense += lpEffect->m_value[0];
		//	break;
		//case EFFECT_FIRE_SLASH_ENHANCED:
		//	lpObj->EffectOption.DivDefense += lpEffect->m_value[0];
		//	break;
		case EFFECT_IRON_DEFENSE_IMPROVED:
			{
				sprintf(szInfo[0], "Max HP: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Defense: +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_TALISMAN_OF_ASCENSION1:
			{
				sprintf(szInfo[0], "Experience Rate: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Master Experience Rate : +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_TALISMAN_OF_ASCENSION2:
			{
				sprintf(szInfo[0], "Experience Rate: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Master Experience Rate : +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_TALISMAN_OF_ASCENSION3:
			{
				sprintf(szInfo[0], "Experience Rate: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Master Experience Rate : +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_SEAL_OF_ASCENSION3:
			{
				sprintf(szInfo[0], "Experience Rate: +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SEAL_OF_ASCENSION2:
			{
				sprintf(szInfo[0], "Master Experience Rate : +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_BLESSING_OF_LIGHT:
			{
				sprintf(szInfo[0], "Experience Rate: +%d%%%%", aRecv->iValue[0]);
				sprintf(szInfo[1], "Master Experience Rate : +%d%%%%", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SCROLL_OF_DEFENSE:
			{
				sprintf(szInfo[0], "Defense: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SCROLL_OF_MAGIC_DAMAGE: // íàäî òåñòàíóò üè òå ÷òî íèæå
			{
				sprintf(szInfo[0], "Magic Damage: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SCROLL_OF_LIFE:
			{
				sprintf(szInfo[0], "Max HP: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SCROLL_OF_MANA:
			{
				sprintf(szInfo[0], "Max MP: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SCROLL_OF_DAMAGE:
			{
				sprintf(szInfo[0], "Physi Damage: +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SCROLL_OF_HEALING:
			{
				sprintf(szInfo[0], "HP Recovery Rate: +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Max HP: +%d", aRecv->iValue[1]);
			}
			break;
		case EFFECT_MASTER_SCROLL_OF_BATTLE:
			{
				sprintf(szInfo[0], "Critical Damage Rate +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SCROLL_OF_STRENGTH:
			{
				sprintf(szInfo[0], "Excellent Damage Rate +%d", aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SCROLL_OF_QUICK:
			{
				sprintf(szInfo[0], "Physi Speed +%d", aRecv->iValue[0]);
				sprintf(szInfo[1], "Magic Speed +%d", aRecv->iValue[0]);
			}
			break;
		}

		for(int i = 0; i < 5; i++)
		{
			if(szInfo[i][0] != 0)
			{
				bDraw = true;
			}
		}

		if(bDraw == true)
		{
			ZeroMemory(&this->DataBuff[DataIndex].Text, sizeof(this->DataBuff[DataIndex].Text));

			for(int i = 0; i < 5; i++)
			{
				if(szInfo[i][0] != 0)
				{
					strcat(szInfo[i], "/");
					strcat(this->DataBuff[DataIndex].Text, szInfo[i]);
				}
			}	
		}
	}
}
// ------------------------------------------------------------------------------
//#endif