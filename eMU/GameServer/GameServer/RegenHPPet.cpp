#include "stdafx.h"
#include "ItemManager.h"
#include "BloodCastle.h"
#include "CashShop.h"
#include "CastleSiegeSync.h"
#include "CustomJewel.h"
#include "DSProtocol.h"
#include "Duel.h"
#include "EffectManager.h"
#include "EventInventory.h"
#include "Fruit.h"
#include "IllusionTemple.h"
#include "ItemBagManager.h"
#include "ItemValue.h"
#include "ItemMove.h"
#include "ItemStack.h"
#include "JewelOfHarmonyOption.h"
#include "Kalima.h"
#include "LifeStone.h"
#include "LuckyItem.h"
#include "Map.h"
#include "MemScript.h"
#include "Mercenary.h"
#include "Message.h"
#include "MossMerchant.h"
#include "MuunSystem.h"
#include "Notice.h"
#include "ObjectManager.h"
#include "PentagramSystem.h"
#include "PersonalShop.h"
#include "Quest.h"
#include "QuestObjective.h"
#include "ServerInfo.h"
#include "ShopManager.h"
#include "SkillManager.h"
#include "SummonScroll.h"
#include "Trade.h"
#include "Util.h"
#include "Viewport.h"
#include "Warehouse.h"
#include "CustomQuest.h"
#include "RegenHPPet.h"

bool NPCRegenHPPet(LPOBJ lpObj, LPOBJ lpNpc)
{
	if(lpNpc->Class	== 381 && lpNpc->Map == 0 && lpNpc->X == 135 && lpNpc->Y == 125)
	{
		RegenHPPet(lpObj);
		return true;
	}
	// ----
	return false;
}

void RegenHPPet(LPOBJ lpObj)
{
	int BlessCount = gItemManager.GetInventoryItemCount(lpObj, GET_ITEM(14, 13), 0);
	if ( BlessCount == 0 )
	{
		gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,"Ban can 1 bless de phuc hoi hp.",BlessCount);
		return;
	}
	gItemManager.DeleteInventoryItemCount(lpObj, GET_ITEM(14, 13), 0, 1);

	if(lpObj->Inventory[8].m_Durability < 200)
	{
		lpObj->Inventory[8].m_Durability = 255;
		gItemManager.GCItemDurSend(lpObj->Index,8,(BYTE)lpObj->Inventory[8].m_Durability,0);
	}
}