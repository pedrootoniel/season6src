#ifdef NOLOAD
#ifndef __ITEM_H__
#define __ITEM_H__

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
	static void cRFAddInventoryPos();
	// ----
};

extern cRFItem RFItem; // 

#endif
#endif