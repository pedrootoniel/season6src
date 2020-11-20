#ifndef __ITEM_H__
#define __ITEM_H__

#define oBattleGlove_Load			0x0050DE38
#define oBattleGlove_Hook			0x0050DC31
#define oBattleGlove_Texture		0x0050E043

#define oBattleGloveProp4_Hook		0x005CD419
#define oBattleGloveProp4_Allowed	0x005CD422
#define oBattleGloveProp4_Return	0x005CD454

#define oBattleGloveProp5_Hook		0x005CEFE7
#define oBattleGloveProp5_Jump		0x005CF01C
#define oBattleGloveProp5_Return	0x005CEFFB

#define oBattleGloveGlow_Hook		0x005F91C2

class cRFItem
{
public:
	void Load();
	// ----
	static void BattleGloveLoad();
	// ---
	static void BattleGloveAssoc();
	static void BattleGloveTexture();
	// ----
	static void BattleGloveProp4(); // Inventory Position
	static void BattleGloveProp5(); // Inventory Rotation
									// ----
	static void BattleGloveGlow();
	static void AddInventoryPos();
	// ----
};

extern cRFItem gRFItem; // 

#endif