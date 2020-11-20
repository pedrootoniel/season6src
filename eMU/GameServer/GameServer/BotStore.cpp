#include "stdafx.h"
#include "BotStore.h"
#include "Monster.h"
#include "ItemManager.h"
#include "ObjectManager.h"
#include "SkillManager.h"
#include "EffectManager.h"
#include "MasterSkillTree.h"
#include "ServerInfo.h"
//#include "MemScript.h"
#include "Util.h"
#include "CashShop.h"
#include "JewelsBank.h"
#include "Message.h"
#include "readscript.h"
#include "Notice.h"
#include "PersonalShop.h"
ObjBotStore BotStore;

void ObjBotStore::Read(char * FilePath)
{
	if(this->Enabled == true)
	{
		for(int botNum=0;botNum<MAX_BOTSTORE;botNum++)
		{
			if(this->bot[botNum].Enabled == true)
			{
				int bIndex = this->bot[botNum].index;
				if(gObjIsConnected(bIndex) == TRUE)
				{
					gObjDel(bIndex);
				}
			}
		}
	}
	for(int i=0;i<MAX_BOTSTORE;i++)
	{
		this->bot[i].index = -1;
		this->bot[i].Enabled = false;
		this->bot[i].ItemCount=0;
		for(int j=0;j<9;j++)
			this->bot[i].body[j].num =-1;
	}

	this->Enabled = FALSE;
	int Token;
	SMDFile = fopen(FilePath, "r");

	if ( SMDFile == NULL )
	{
		MsgBox("BotStore data load error %s", FilePath);
		return;
	}

	while ( true )
	{
		int iType = GetToken();
		
		if ( iType == 1 )
		{
			while(true)
			{
				Token = GetToken();
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				int BotNum = TokenNumber;
				if(BotNum < 0 || BotNum > MAX_BOTSTORE-1)
				{
					MsgBox("BotStore error: BotPetIndex:%d out of range!", BotNum);
					return;
				}

				Token = GetToken();
				this->bot[BotNum].Class = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].OnlyVip = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].UseVipMoney = TokenNumber;

				Token = GetToken();
				strncpy(this->bot[BotNum].Name,TokenString,sizeof(this->bot[BotNum].Name));

				Token = GetToken();
				strncpy(this->bot[BotNum].StoreName,TokenString,sizeof(this->bot[BotNum].StoreName));

				Token = GetToken();
				this->bot[BotNum].Map = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].X = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].Y = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].Dir = TokenNumber;

				this->bot[BotNum].Enabled = true;
			}
		}
		
		iType = GetToken();
		iType = TokenNumber;
		if ( iType == 2 )
		{
			while(true)
			{
				Token = GetToken();
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				int BotNum = TokenNumber;
				if(BotNum < 0 || BotNum > MAX_BOTSTORE-1)
				{
					MsgBox("BotStore error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				if(this->bot[BotNum].Enabled == false)
				{	
					MsgBox("BotStore error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				Token = GetToken();
				int Slot = TokenNumber;
				
				if(Slot < 0 || Slot > 8)
				{	
					MsgBox("BotStore error: Min Slot 0 ; Max Slot 8");
					return;
				}

				Token = GetToken();
				int iType = TokenNumber;

				Token = GetToken();
				int iIndex = TokenNumber;

				this->bot[BotNum].body[Slot].num = ITEMGET(iType,iIndex);

				Token = GetToken();
				this->bot[BotNum].body[Slot].level = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].body[Slot].opt = TokenNumber;

				this->bot[BotNum].body[Slot].Enabled = true;
			}
		}
		
		iType = GetToken();
		iType = TokenNumber;
		if ( iType == 3 )
		{
			this->Enabled = TRUE;
			while(true)
			{
				Token = GetToken();
				if ( strcmp("end", TokenString) == 0 )
				{
					break;
				}

				int BotNum = TokenNumber;
				if(BotNum < 0 || BotNum > MAX_BOTSTORE-1)
				{
					MsgBox("BotStore error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				if(this->bot[BotNum].Enabled == false)
				{	
					MsgBox("BotStore error: BotPetIndex:%d doesnt exist", BotNum);
					return;
				}
				int Num = this->bot[BotNum].ItemCount;

				Token = GetToken();
				this->bot[BotNum].storeItem[Num].Value = TokenNumber;

				Token = GetToken();
				int iType = TokenNumber;

				Token = GetToken();
				int iIndex = TokenNumber;

				this->bot[BotNum].storeItem[Num].num = ITEMGET(iType,iIndex);

				Token = GetToken();
				this->bot[BotNum].storeItem[Num].Level = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].storeItem[Num].Opt = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].storeItem[Num].Luck = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].storeItem[Num].Skill = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].storeItem[Num].Dur = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].storeItem[Num].Exc = TokenNumber;

				Token = GetToken();
				this->bot[BotNum].storeItem[Num].Anc = TokenNumber;

				for(int i=0;i<5;i++)
				{
					Token = GetToken();
					this->bot[BotNum].storeItem[Num].Sock[i] = TokenNumber;
				}

				this->bot[BotNum].ItemCount++;
			}
		}
		
		break;
	}
			
	LogAdd(LOG_RED,"[BotStore] - %s file is Loaded",FilePath);
	fclose(SMDFile);
}




BYTE gObjTempPShopRectCheck(BYTE * TempMap, int sx, int sy, int width, int height)
{
	int x,y,blank = 0;

	if(sx + width > 12)
	{
		return -1;
	}
	if(sy + height > 8)
	{
		return -2;
	}

	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			if(*(BYTE*)(TempMap + (sy+y)*8 + (sx+x))!= 255)
			{
				blank += 1;
				return -1;
			}
		}
	}
	if(blank == 0)
	{
		return sx+sy*8+INVENTORY_WEAR_SIZE;
	}
	return -1;
}



BYTE ObjBotStore::CheckSpace(LPOBJ lpObj, int type, BYTE * TempMap)
{
	int w,h,iwidth,iheight;
	BYTE blank = 0;

	iwidth=gItemManager.m_ItemInfo[type].Width  ;
	iheight=gItemManager.m_ItemInfo[type].Height  ;

	for(h = 0; h < 4; h++)
	{
		for(w = 0; w < 8; w++)
		{
			if(*(BYTE*)(TempMap + h * 8 + w) == 255)
			{
				blank = gObjTempPShopRectCheck(TempMap,w,h,iwidth,iheight);

				if(blank == 254)
				{
					goto GOTO_EndFunc;
				}
				if(blank != 255)
				{
					gItemManager.gObjTempInventoryItemBoxSet(TempMap,blank,iwidth,iheight,type);
					return blank;
				}
			}
		}
	}
GOTO_EndFunc:
	return -1;
}

void ObjBotStore::AddItem(int bIndex,int botNum)
{
	int S6E2 = 1;
	for(int i=0;i<this->bot[botNum].ItemCount;i++)
	{
		int blank = this->CheckSpace(&gObj[bIndex],this->bot[botNum].storeItem[i].num,&gObj[bIndex].InventoryMap[gServerInfo.MAIN_INVENTORY_SIZE(bIndex,false)]);
		//int blank = this->CheckSpace(&gObj[bIndex],this->bot[botNum].storeItem[i].num,&gObj[bIndex].InventoryMap[MAIN_INVENTORY_NORMAL_SIZE]);
		if(blank != 255)
		{
			
			if(S6E2 == FALSE)
			{
				blank += gServerInfo.MAIN_INVENTORY_SIZE(bIndex,false) - INVENTORY_WEAR_SIZE;
			}
			else
			{
				blank += gServerInfo.MAIN_INVENTORY_SIZE(bIndex,true) - INVENTORY_WEAR_SIZE;
			}
			//blank += MAIN_INVENTORY_NORMAL_SIZE - INVENTORY_WEAR_SIZE -1;
			CItem item;
			item.m_Level = this->bot[botNum].storeItem[i].Level;
			item.m_Option1 = this->bot[botNum].storeItem[i].Skill;
			item.m_Option2 = this->bot[botNum].storeItem[i].Luck;
			item.m_Option3 = this->bot[botNum].storeItem[i].Opt;
			item.m_Durability = this->bot[botNum].storeItem[i].Dur;
			item.m_JewelOfHarmonyOption = 0;
			item.m_NewOption = this->bot[botNum].storeItem[i].Exc;
			item.m_ItemOptionEx = 0;
			item.m_SetOption = this->bot[botNum].storeItem[i].Anc;
			item.m_SocketOption[0] = this->bot[botNum].storeItem[i].Sock[0];
			item.m_SocketOption[1] = this->bot[botNum].storeItem[i].Sock[1];
			item.m_SocketOption[2] = this->bot[botNum].storeItem[i].Sock[2];
			item.m_SocketOption[3] = this->bot[botNum].storeItem[i].Sock[3];
			item.m_SocketOption[4] = this->bot[botNum].storeItem[i].Sock[4];
			item.m_PShopValue = this->bot[botNum].storeItem[i].Value;
			item.Convert(this->bot[botNum].storeItem[i].num,item.m_Option1,item.m_Option2,item.m_Option3,item.m_NewOption,item.m_SetOption,item.m_JewelOfHarmonyOption,item.m_ItemOptionEx,item.m_SocketOption,item.m_SocketOptionBonus);

			gObj[bIndex].Inventory[blank].m_Option1 = item.m_Option1;
			gObj[bIndex].Inventory[blank].m_Option2 = item.m_Option2;
			gObj[bIndex].Inventory[blank].m_Option3 = item.m_Option3;
			gObj[bIndex].Inventory[blank].m_JewelOfHarmonyOption = item.m_JewelOfHarmonyOption;
			gObj[bIndex].Inventory[blank].m_ItemOptionEx = item.m_ItemOptionEx;
			//item.m_Number = 0;
			gObj[bIndex].Inventory[blank] = item;
		}
	}	
}

void ObjBotStore::MakeBot()
{
	if(this->Enabled == true)
	{
		for(int botNum=0;botNum<MAX_BOTSTORE;botNum++)
		{
			if(this->bot[botNum].Enabled == true)
			{
				int aIndex = gObjAddMonster(bot[botNum].Map);

				if(aIndex >= 0)
				{
					LPOBJ lpObj = &gObj[aIndex];
					this->bot[botNum].index = aIndex;
					lpObj->PosNum = (WORD)-1;
					lpObj->X = this->bot[botNum].X;
					lpObj->Y = this->bot[botNum].Y;
					lpObj->OldX = this->bot[botNum].X;
					lpObj->OldY = this->bot[botNum].Y;
					lpObj->TX = this->bot[botNum].X;
					lpObj->TY = this->bot[botNum].Y;
					lpObj->MTX = this->bot[botNum].X;
					lpObj->MTY = this->bot[botNum].Y;
					lpObj->Dir = this->bot[botNum].Dir;
					lpObj->Map = this->bot[botNum].Map;
					lpObj->Live = TRUE;
					lpObj->PathCount = 0;
					lpObj->IsBot = 4;
					lpObj->Type = OBJECT_USER;
					//gObjSetMonsterTest(aIndex,this->bot[botNum].Class, "BotBuffer");
					gObjSetMonster(aIndex,this->bot[botNum].Class);

					lpObj->ChangeUp = this->bot[botNum].Class % 16;	// Set Second Type of Character
					lpObj->Class = this->bot[botNum].Class / 16;
					lpObj->Level = 400;
					lpObj->Life = 1;
					lpObj->MaxLife = 2;
					lpObj->Mana = 1;
					lpObj->MaxMana = 2;
					lpObj->Experience = 0;
					//lpObj->DBClass = this->bot[botNum].Class;
					
					lpObj->Inventory = new CItem[MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE];					
					lpObj->Inventory1 = new CItem[MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE];
					lpObj->InventoryMap1 = new BYTE[MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE];
					lpObj->InventoryMap = new BYTE[MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE];

					for (int i=0;i<(MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE);i++)
					{
						lpObj->Inventory[i].Clear();
						lpObj->Inventory1[i].Clear();
					}

					memset(&lpObj->InventoryMap[0], (BYTE)-1, (MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE));	//108+64+64
					memset(&lpObj->InventoryMap1[0], (BYTE)-1, (MAIN_INVENTORY_NORMAL_SIZE + (MAX_EXTENDED_INV*EXTENDED_INV_SIZE) + PSHOP_SIZE));	//108+64+64

					strncpy(lpObj->Name,this->bot[botNum].Name,sizeof(lpObj->Name));


					for(int i=0;i<9;i++)
					{
						if(this->bot[botNum].body[i].num >= 0 && this->bot[botNum].body[i].Enabled == true)
						{
							CItem lpItem;

							lpObj->Inventory[i].Clear();

							lpItem.Clear();

							lpItem.m_Index = this->bot[botNum].body[i].num;

							lpItem.m_Option1 = 0;

							lpItem.m_Option2 = 1;

							lpItem.m_Option3 = this->bot[botNum].body[i].opt;

							lpItem.m_Level = this->bot[botNum].body[i].level;

							lpItem.m_Durability = 255.0f;

							lpItem.m_Serial = 0;

							lpItem.m_NewOption = 0;

							lpItem.m_SetOption = 0;

							lpItem.m_ItemOptionEx = 0;

							lpItem.m_IsPeriodicItem = 0;

							lpItem.m_IsExpiredItem = 0;

							memset(lpItem.m_SocketOption,0xFF,MAX_SOCKET_OPTION);

							lpItem.m_JewelOfHarmonyOption = 0;

							lpItem.m_SocketOptionBonus = 0xFF;

							lpItem.Convert(lpItem.m_Index,lpItem.m_Option1,lpItem.m_Option2,lpItem.m_Option3,lpItem.m_NewOption,lpItem.m_SetOption,lpItem.m_JewelOfHarmonyOption,lpItem.m_ItemOptionEx,lpItem.m_SocketOption,lpItem.m_SocketOptionBonus);

							gItemManager.InventoryAddItem(aIndex,lpItem,i);
						}
					}	
					this->AddItem(aIndex,botNum);

					lpObj->Inventory1 = lpObj->Inventory;
					lpObj->InventoryMap1 = lpObj->InventoryMap;
					gObjectManager.CharacterMakePreviewCharSet(aIndex);

					lpObj->AttackType = 0;
					lpObj->BotSkillAttack = 0;					

					lpObj->Attribute = 100;
					lpObj->TargetNumber = (WORD)-1;
					lpObj->ActionState.Emotion = 0;
					lpObj->ActionState.Attack = 0;
					lpObj->ActionState.EmotionCount = 0;
					lpObj->PathCount = 0;
					lpObj->BotPower = this->bot[botNum].UseVipMoney;
					lpObj->BotDefense = this->bot[botNum].OnlyVip;
					lpObj->BotLife = 1;
					lpObj->BotMaxLife = 1;
					
					lpObj->BotLvlUpDefense = 1;
					lpObj->BotLvlUpPower = 1;
					lpObj->BotLvlUpLife = 1;
					lpObj->BotLvlUpMana = 1;
					lpObj->BotLvlUpExp = 1;
					lpObj->BotLvlUpMaxLevel = 1;

					lpObj->MoveRange = 1;
					lpObj->BotFollowMe = 0;
					lpObj->NextExperience = gLevelExperience[lpObj->Level];
					
					lpObj->PShopOpen = 1;
					memcpy(lpObj->PShopText, this->bot[botNum].StoreName, sizeof(lpObj->PShopText));
					gPersonalShop.GCPShopTextChangeSend(aIndex);
					gPersonalShop.GCPShopOpenSend(aIndex,1);
				}
			}
		}
	}
}
