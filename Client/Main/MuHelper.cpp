#include "stdafx.h"
#include "MuHelper.h"
#include "Offset.h"
#include "Protocol.h"
#include "User.h"
#include "Util.h"
#include "Item.h"
#include "Console.h"
#include "Interface.h"
#include "PrintPlayer.h"
#include "NewParty.h"
#include "PrintPlayer.h"

CMuHelper gMuHelper;
 
void CMuHelper::Load()
{
    SetCompleteHook(0xE8, 0x4D8FD0+0x312,&this->Work);                
    SetCompleteHook(0xE8, 0x95DE10+0x500,&this->PartyUseBuff);
    SetCompleteHook(0xE8, 0x95DE10+0x8DB,&this->PartyUseBuff);
}
 
void CMuHelper::Work(MUHelper* pHelper)
{
    DWORD Time = NULL;
    LPCSTR pText = NULL;
    CharTest v15;
 
    int v4 = NULL;
 
    *(BYTE*)0x8793381 = 0;
 
 
    if ( pHelper->lpTarget && (!pHelper->lpTarget->m_Model.Unknown4 || pHelper->lpTarget->m_Model.AnimationID == 6) )
    {
        pHelper->lpTarget = 0;
        pViewAttackTargetID = -1;
    }
 
    Time = GetTickCount();
 
    if ( (Time - pHelper->Time01) >= pHelper->Time02 )
    {
        pHelper->Time01 = Time;
        pHelper->Time02 = 200;
 
        if ( pHelper->lpPlayer->InSafeZone )
        {
            /*pText = pGetTextLine((LPVOID)0x8128ADC, 3581);
            sub_409A50_addr(&v15, (int)pText);
            sub_409A50_addr(&v15, (int)0xD4F917);
            sub_7894E0_Addr((char *)v4, (int)&v15, (int)&v15, 3, 0);
            sub_409AD0_Addr((LPVOID)&v15);*/
            //NEED CHECK UP

			pText = pGetTextLine((LPVOID)0x8128ADC, 3581);
            sub_409A50_addr(&v15, (int)pText);
            //sub_409A50_addr(&v15, (int)0xD4F917);
            //sub_7894E0_Addr((char *)v4, (int)&v15, (int)&v15, 3, 0);
			pOpenInfoBox(&v15,-1);
            sub_409AD0_Addr((LPVOID)&v15);
 
            PMSG_HELPER_START_SEND pMsg;
 
            pMsg.header.set(0xBF, 0x51, sizeof(pMsg));
            pMsg.type = 1;
            DataSend((LPBYTE)&pMsg, sizeof(pMsg));
            return;
        }
 
        if (/*pCheckWindow(pWindowThis(),Inventory) || */pCheckWindow(pWindowThis(),MuHelper))
        {
            PMSG_HELPER_START_SEND pMsg;
 
            pMsg.header.set(0xBF,0x51,sizeof(pMsg));
            pMsg.type = 1;
 
            DataSend((BYTE*)&pMsg,pMsg.header.size);
 
            return;
        }
 
        if ( LOBYTE(pHelper->DarkSpiritOn) && !pHelper->Unknown160 )
        {
             PMSG_PET_ITEM_COMMAND_SEND pMsg;
 
             pMsg.header.set(0xA7, sizeof(pMsg));
             pMsg.type = 0;
             pMsg.command = pHelper->DarkSpiritMode;
             pMsg.index[0] = SET_NUMBERHB(-1);
             pMsg.index[1] = SET_NUMBERLB(-1);
 
             DataSend((BYTE*)&pMsg,pMsg.header.size);
 
             pHelper->Unknown160 = 1;
        }
 
        if ( pHelper->RecoveryPotionOn )
        {
            //DWORD MaxLife = pIs3rdClass(pHelper->lpPlayer->Class) ? *(WORD*)0x87935F8 : gObjUser.lpPlayer->MaxLife;
 
            //if ( gObjUser.lpPlayer->Life < (MaxLife * pHelper->RecoveryPotionPercent / 100) )
 
            if ( ViewCurHP < (ViewMaxHP * pHelper->RecoveryPotionPercent / 100) )
            {
                if ( pHelper->lpPlayer->m_Model.Unknown4 == 1 )
                {
                    //if ( gObjUser.lpPlayer->Life > 0 )
                    if ( ViewCurHP > 0 )
                    {
                        pHelperUsePotion(pHelper);
                    }
                }
            }
        }
 
        /*if ( !pHelper->RecoveryHealOn || (pGetSkillPos(26) < 0 && pGetSkillPos(413) < 0) ||
            (!pIs3rdClass(pHelper->lpPlayer->Class) ? v11 = gObjUser.lpPlayer->MaxLife : (v11 = *(WORD*)0x87935F8),
            (v17 = v11, gObjUser.lpPlayer->Life >= (unsigned __int16)v11 * pHelper->RecoveryHealPercent / 100) ||
            pHelper->lpPlayer->m_Model.Unknown4 != 1 || gObjUser.lpPlayer->MaxLife <= 0 || !pHelperUseBuff(pHelper,pHelper->lpPlayer)) )*/
        if ( !pHelper->RecoveryHealOn || (pGetSkillPos(26) < 0 && pGetSkillPos(413) < 0) || (ViewCurHP >= (ViewMaxHP * pHelper->RecoveryHealPercent / 100) || pHelper->lpPlayer->m_Model.Unknown4 != 1 || ViewCurHP <= 0 || !pHelperUseBuff(pHelper,pHelper->lpPlayer)) )
        {
            if ( !pHelper->PartyModeOn || !pHelper->PartyModeHealOn || pPartyMemberCount <= 0 || (pGetSkillPos(26) < 0 && pGetSkillPos(413) < 0) || !gMuHelper.PartyUseBuff(pHelper) )
            {
                /*if ( !pHelper->RecoveryDrainOn || (pGetSkillPos(214) < 0 && pGetSkillPos(458) < 0) ||
                    (!pIs3rdClass(pHelper->lpPlayer->Class) ? (v10 = gObjUser.lpPlayer->MaxLife) : (v10 = *(WORD*)0x87935F8),
                    (v16 = (unsigned __int16)v10, gObjUser.lpPlayer->Life >= (unsigned __int16)v10 * pHelper->RecoveryDrainPercent / 100)
                    || pHelper->lpPlayer->m_Model.Unknown4 != 1 || gObjUser.lpPlayer->Life <= 0 || !sub_95EC00_Addr(pHelper) ||
                    (pGetSkillPos(214) < 0 || !(unsigned __int8)pHelperUseSkill(pHelper, 214, pHelper->lpTarget, 1)) &&
                    (pGetSkillPos(458) < 0 || !(unsigned __int8)pHelperUseSkill(pHelper, 458, pHelper->lpTarget, 1))) )*/
                if ( !pHelper->RecoveryDrainOn || (pGetSkillPos(214) < 0 && pGetSkillPos(458) < 0) ||
                    ( ViewCurHP >= (ViewMaxHP * pHelper->RecoveryHealPercent / 100)
                    || pHelper->lpPlayer->m_Model.Unknown4 != 1
                    || ViewCurHP <= 0 || !sub_95EC00_Addr(pHelper)
                    || (pGetSkillPos(214) < 0 || !pHelperUseSkill(pHelper, 214, pHelper->lpTarget, 1)) && (pGetSkillPos(458) < 0 || !pHelperUseSkill(pHelper, 458, pHelper->lpTarget, 1)))  )
                {
                    if ( !LOBYTE(pHelper->BuffOn) || !sub_95FCD0_Addr(pHelper) )
                    {
                        if ( sub_95F0D0_Addr(pHelper) )
                        {
                            sub_95F490_Addr(pHelper, pHelper->Unknown20);
                            return;
                        }
 
                        if ( pHelper->ObtainRepairOn )
                        {
                            HelperRepairItems();
                        }
 
                        if ( pHelper->lpPlayer->Unknown120 == 1 )
                        {
                            if ( pHelper->Unknown168 == 1 && sub_95EFA0_Addr(pHelper) == 1 )
                            {
                                sub_59B2B0_Addr(pHelper->lpPlayer, 1);
                                sub_54EA80_Addr(pHelper->lpPlayer);
                            }
                        }
                        else
                        {
                            if ( pHelper->ComboOn && pHelper->Unknown80 > 0 && pHelper->lpIDontKnow
                                && pHelper->lpIDontKnow->m_Model.Unknown4 == 1 && pHelper->lpIDontKnow->m_Model.AnimationID != 6 )
                            {
                                if ( pHelper->lpPlayer->m_Model.AnimationID > 14 && (pHelper->lpPlayer->m_Model.AnimationID < 122 || pHelper->lpPlayer->m_Model.AnimationID > 129) )
                                {
                                    return;
                                }
 
                                if ( pHelper->Unknown80 == 1 )
                                {
                                    if ( pHelperUseSkill(pHelper, pHelper->SkillSecond1.SkillSecondID, pHelper->lpIDontKnow, 1) )
                                    {
                                        ++pHelper->Unknown80;
                                        return;
                                    }
                                }
                                else if ( pHelper->Unknown80 == 2 && pHelperUseSkill(pHelper, pHelper->SkillSecond2.SkillSecondID, pHelper->lpIDontKnow, 1) )
                                {
                                    pHelper->Unknown80 = 0;
                                    return;
                                }
                            }
                        }
 
                        if ( (!pHelper->PartyModeOn || pPartyMemberCount <= 0 || (pGetSkillPos(26) < 0 && pGetSkillPos(413) < 0)
                            || !pHelperPartyUseBaff(pHelper)) && (!pHelper->PartyModeOn || pPartyMemberCount <= 0 || !LOBYTE(pHelper->PartyModeBuffOn)
                            || !sub_95FF40_Addr(pHelper)) )
                        {
                            if ( pHelper->DistanceReturnOn )
                            {
                                if ( sub_960140_Addr(pHelper, pHelper->MapPosX, pHelper->MapPosY) )
                                {
                                    if ( pHelper->Unknown168 == 1 )
                                    {
                                        pHelper->Unknown168 = 0;
                                        pHelper->lpTarget = 0;
                                        pViewAttackTargetID = -1;
                                    }
                                    pHelper->Time03 = Time;
                                }
                                else if ( Time - pHelper->Time03 > 1000 * pHelper->DistanceMin )
                                {
                                    pHelper->Time03 += 5000;
                                    pHelper->lpIDontKnow = 0;
                                    pHelper->lpTarget = 0;
                                    sub_9600A0_Addr(pHelper, pHelper->MapPosX, pHelper->MapPosY);
                                    pHelper->Unknown168 = 1;
                                    return;
                                }
                            }
                            if ( (pHelper->ComboOn
                                || !sub_95FAE0_Addr(pHelper, &pHelper->SkillSecond2, (int)&pHelper->Unknown44)
                                && !sub_95FAE0_Addr(pHelper, &pHelper->SkillSecond1, (int)&pHelper->Unknown40))
                                && pHelper->SkillBasicID
                                && sub_95EC00_Addr(pHelper)
                                && (!pHelper->ComboOn
                                || pHelper->Unknown80
                                || (signed int)pHelper->lpPlayer->m_Model.AnimationID <= 14
                                || (signed int)pHelper->lpPlayer->m_Model.AnimationID >= 122
                                && (signed int)pHelper->lpPlayer->m_Model.AnimationID <= 129)
                                && pHelperUseSkill(pHelper, pHelper->SkillBasicID, pHelper->lpTarget, 1) )
                            {
                                pHelper->Unknown80 = 1;
                            }
                        }
                    }
                }
 
            }
        }
    }
}
 
bool CMuHelper::PartyUseBuff(MUHelper* pHelper)
{
    signed int v4;
 
    if ( timeGetTime() - pHelper->Unknown60 < 500 )
    {
        return 0;
    }
 
    if ( pGetSkillPos(26) == -1 && pGetSkillPos(413) == -1 )
    {
        return 0;
    }
 
    int BuffsCount = 0;
 
    for (int  i = 0; i < pPartyMemberCount; i++ )
    {
        PartyList PartyMember   = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * i);
 
        lpViewObj lpPartyObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), PartyMember.ViewportID);
 
        if (!lpPartyObj || lpPartyObj == gObjUser.lpViewPlayer)
        {
            continue;
        }
 
        if (lpPartyObj->m_Model.Unknown4 != 1)
        {
            continue;
        }
 
        if (PartyMember.LifePercent < pHelper->PartyModeHealPercent / 10 && pHelperUseBuff(pHelper, lpPartyObj) == 1 )
        {
            //g_Console.AddMessage(5,"[%s] Buffed", lpPartyObj->Name);
 
            BuffsCount++;
        }
    }
 
    if (BuffsCount > 0)
    {
        pHelper->Unknown60 = timeGetTime();
        //g_Console.AddMessage(3,"BuffsCount = %d", BuffsCount);
        return 1;
    }
 
    return 0;
}

//#include "stdafx.h"
//#include "MuHelper.h"
//#include "Offset.h"
//#include "Defines.h"
//#include "Protocol.h"
//#include "User.h"
//#include "Util.h"
//#include "NEWConsole.h"
//#include "Item.h"
//
//CMuHelper gMuHelper;
//
//void CMuHelper::Load()
//{
//	SetCompleteHook(0xE8, 0x4D8FD0+0x312,&this->Work);                
//	SetCompleteHook(0xE8, 0x95DE10+0x500,&this->PartyUseBuff);
//	SetCompleteHook(0xE8, 0x95DE10+0x8DB,&this->PartyUseBuff);
//}
//
//void CMuHelper::Work(MUHelper* pHelper)
//{
//	g_Console.AddMessage(5,"Model = %d",gObjUser.lpViewPlayer->m_Model.Unknown48);
//	DWORD Time; // [sp+186Ah] [bp-10h]@5
//
//	*(BYTE*)0x8793381 = 0;
//
//	if ( pHelper->lpTarget && (!pHelper->lpTarget->m_Model.Unknown4 || pHelper->lpTarget->m_Model.AnimationID == 6) )
//	{
//		pHelper->lpTarget = 0;
//		pViewAttackTargetID = -1;
//	}
//
//	Time = timeGetTime();
//
//	if ( Time - pHelper->Time01 >= pHelper->Time02 )
//	{
//		if (pHelper->DarkSpiritOn && !pHelper->Unknown160)
//		{
//			sub_95DE10_Addr(pHelper);
//			return;
//		}
//
//		if (pHelper->lpPlayer->InSafeZone)
//		{
//			sub_95DE10_Addr(pHelper);
//			return;
//		}
//
//		pHelper->Time01 = Time;
//		pHelper->Time02 = 200;
//
//		if (pCheckWindow(pWindowThis(),Inventory) || pCheckWindow(pWindowThis(),MuHelper))
//		{
//			/* ... */
//			PMSG_HELPER_START_SEND pMsg;
//
//			pMsg.header.set(0xBF,0x51,sizeof(pMsg));
//
//			pMsg.type = 1;
//
//			DataSend((BYTE*)&pMsg,pMsg.header.size);
//
//			return;
//		}
//
//		if ( pHelper->RecoveryPotionOn )
//		{
//			int MaxLife = pIs3rdClass(pHelper->lpPlayer->Class) ? pMaxLife : gObjUser.lpPlayer->MaxLife;
//
//			if ((gObjUser.lpPlayer->Life < MaxLife/100*pHelper->RecoveryPotionPercent) 
//				&& pHelper->lpPlayer->m_Model.Unknown4 == 1 && gObjUser.lpPlayer->Life > 0)
//			{
//				//g_Console.AddMessage(2,"Heal!!!1");
//				pHelperUsePotion(pHelper);
//			}
//		}
//
//		int v15,v21,v14,v20;
//
//		//(pGetSkillPos(26) < 0 && pGetSkillPos(413) < 0) //скиллы хила
//		if (!pHelper->RecoveryHealOn || (pGetSkillPos(26) < 0 && pGetSkillPos(413) < 0) || 
//			(!pIs3rdClass(pHelper->lpPlayer->Class) ? (v15 = gObjUser.lpPlayer->MaxLife) : (v15 = pMaxLife),
//			(v21 = v15,  gObjUser.lpPlayer->Life >= v15 * pHelper->RecoveryHealPercent / 100) || 
//			pHelper->lpPlayer->m_Model.Unknown4 != 1 || gObjUser.lpPlayer->Life <= 0 || 
//			!pHelperUseBuff(pHelper,pHelper->lpPlayer)) )
//		{
//			if ( !pHelper->PartyModeOn
//				|| !pHelper->PartyModeHealOn
//				|| pPartyMemberCount <= 0
//				|| (pGetSkillPos(26) < 0 && pGetSkillPos(413)) < 0
//				|| !gMuHelper.PartyUseBuff(pHelper) ) 
//				//|| !pHelperPartyUseBaff(pHelper) )
//			{
//				 if ( !pHelper->RecoveryDrainOn || pGetSkillPos(214) < 0 && pGetSkillPos(458) < 0 ||
//					(!pIs3rdClass(pHelper->lpPlayer->Class) ? (v14 = gObjUser.lpPlayer->MaxLife) : (v14 = pMaxLife),
//					(v20 = v14, gObjUser.lpPlayer->Life >= v14 * pHelper->RecoveryDrainPercent / 100) ||
//					pHelper->lpPlayer->m_Model.Unknown4 != 1 || gObjUser.lpPlayer->Life <= 0 || 
//					!sub_95EC00_Addr(pHelper) ||
//					((pGetSkillPos(214) < 0 || !pHelperUseSkill(pHelper, 214, pHelper->lpTarget, 1)) && 
//					(pGetSkillPos(458) < 0 || !pHelperUseSkill(pHelper, 458, pHelper->lpTarget, 1))) ))
//				{
//					if (!pHelper->BuffOn || !sub_95FCD0_Addr(pHelper))
//					{
//						if (sub_95F0D0_Addr(pHelper))
//						{
//							sub_95F490_Addr(pHelper,pHelper->Unknown20);
//							return;
//						}
//
//						if ( pHelper->ObtainRepairOn )
//							HelperRepairItems();
//
//						if ( pHelper->lpPlayer->Unknown120 == 1 )
//						{
//							if (pHelper->Unknown168 == 1 && sub_95EFA0_Addr(pHelper) == 1)
//							{
//								g_Console.AddMessage(2,"IF");
//								sub_59B2B0_Addr(pHelper->lpPlayer, 1);
//								sub_54EA80_Addr(pHelper->lpPlayer);
//							}
//							
//						}
//						else
//						{
//							if ( pHelper->ComboOn
//								&& pHelper->Unknown80 > 0
//								&& pHelper->lpIDontKnow
//								&& pHelper->lpIDontKnow->m_Model.Unknown4 == 1
//								&& pHelper->lpIDontKnow->m_Model.AnimationID != 6 )
//							{
//								if ( pHelper->lpPlayer->m_Model.AnimationID > 14 && 
//									(pHelper->lpPlayer->m_Model.AnimationID < 122 || 
//									pHelper->lpPlayer->m_Model.AnimationID > 129) )
//										return;
//
//								if (pHelper->Unknown80 == 1 && pHelperUseSkill(pHelper, pHelper->SkillSecond1.SkillSecondID, pHelper->lpIDontKnow, 1))
//								{
//									++pHelper->Unknown80;
//									return;
//								}
//								else if (pHelper->Unknown80 == 2 && pHelperUseSkill(pHelper, pHelper->SkillSecond2.SkillSecondID, pHelper->lpIDontKnow, 1))
//								{
//									pHelper->Unknown80 = 0;
//								}
//							}
//
//							if ( (!pHelper->PartyModeOn
//								|| pPartyMemberCount <= 0
//								|| pGetSkillPos(26) < 0 && pGetSkillPos(413) < 0
//								|| !gMuHelper.PartyUseBuff(pHelper))
//								//|| !pHelperPartyUseBaff(pHelper))
//								&& (!pHelper->PartyModeOn
//								|| pPartyMemberCount <= 0
//								|| !pHelper->PartyModeBuffOn
//								|| !sub_95FF40_Addr(pHelper)) )
//							{
//								if (pHelper->DistanceReturnOn)
//								{
//									if (sub_960140_Addr(pHelper, pHelper->MapPosX, pHelper->MapPosY))
//									{
//										if (pHelper->Unknown168 == 1)
//										{
//											pHelper->Unknown168 = 0;
//											pHelper->lpTarget = 0;
//											pViewAttackTargetID = -1;
//										}
//										pHelper->Time03 = Time;
//									}
//									else if( Time - pHelper->Time03 > 1000 * pHelper->DistanceMin )
//									{
//										pHelper->Time03 += 5000;
//										pHelper->lpIDontKnow = 0;
//										pHelper->lpTarget = 0;
//										sub_9600A0_Addr(pHelper, pHelper->MapPosX, pHelper->MapPosY);
//										pHelper->Unknown168 = 1;
//										return;
//									}
//								}
//
//								if ( pHelper->ComboOn
//									|| !sub_95FAE0_Addr(pHelper, &pHelper->SkillSecond2, pHelper->Unknown44)
//									&& !sub_95FAE0_Addr(pHelper, &pHelper->SkillSecond1, pHelper->Unknown40)
//									&& pHelper->SkillBasicID
//									&& sub_95EC00_Addr(pHelper)
//									&& (!pHelper->ComboOn
//									|| pHelper->Unknown80
//									|| pHelper->lpPlayer->m_Model.AnimationID <= 14
//									|| pHelper->lpPlayer->m_Model.AnimationID >= 122
//									&& pHelper->lpPlayer->m_Model.AnimationID <= 129)
//									&& pHelperUseSkill(pHelper, pHelper->SkillBasicID, pHelper->lpTarget, 1) )
//								{
//										pHelper->Unknown80 = 1;
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//	//g_Console.AddMessage(2,"X = %d Y = %d", pHelper->MapPosX, pHelper->MapPosY);
//	//g_Console.AddMessage(2,"Time01 = %d Time02 = %d",v26 - pHelper->Time01,pHelper->Time02);
//	//g_Console.AddMessage(4,"Range = %d", pHelper->HuntingRange);
//	//g_Console.AddMessage(2,"Test = %d", *(WORD*)0x87935F8);
//	//g_Console.AddMessage(2,"Skill = %d", pGetSkillPos(41));
//	//sub_95DE10_Addr(pHelper);
//}
//
//bool CMuHelper::PartyUseBuff(MUHelper* pHelper)
//{
//	signed int v4; // ST00_4@9
//
//	//DWORD Time = timeGetTime();
//
//	if ( timeGetTime() - pHelper->Unknown60 < 500 )
//	{
//		return 0;
//	}
//
//	if ( pGetSkillPos(26) == -1 && pGetSkillPos(413) == -1 )
//	{
//		return 0;
//	}
//
//	int BuffsCount = 0;
//
//	for (int  i = 0; i < pPartyMemberCount; i++ )
//	{
//		PartyList PartyMember	= *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * i);
//
//		lpViewObj lpPartyObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), PartyMember.ViewportID);
//
//		//g_Console.AddMessage(5, "%s %d %d",PartyMember.Name, PartyMember.LifePercent,pHelper->PartyModeHealPercent / 10 );
//
//		if (!lpPartyObj || lpPartyObj == gObjUser.lpViewPlayer)
//		{
//			continue;
//		}
//
//		if (lpPartyObj->m_Model.Unknown4 != 1)
//		{
//			continue;
//		}
//
//		if (PartyMember.LifePercent < pHelper->PartyModeHealPercent / 10 && pHelperUseBuff(pHelper, lpPartyObj) == 1 )
//		{
//			/*if (pHelperUseBuff(pHelper, lpPartyObj) == 1)
//			{
//
//				pHelper->Unknown60 = timeGetTime();
//				return 1;
//			}*/
//			g_Console.AddMessage(5,"[%s] Buffed", lpPartyObj->Name);
//			BuffsCount++;
//		}
//		//DWORD * v4Mass = (DWORD *)0x81CB504;
//		
//		//v4 = v4Mass[8 * i];
//
//		//BYTE * TEST = (BYTE *)0x81CB500;
//
//		//ObjectPreview * lpPrev = (ObjectPreview *)pGetPreviewStruct(pPreviewThis(), v4);
//
//		//if ( lpPrev /*&& lpPrev != (ObjectPreview *)MAIN_VIEWPORT_STRUCT*/ && (unsigned __int8)TEST[32 * i] < pHelper->PartyModeHealPercent / 10 /*&& lpPrev->m_Model.Unknown4 == 1 */&& pHelperUseBuff(pHelper, lpPrev) )
//		//{
//		//	*(DWORD *)&pHelper->gap06[12] = timeGetTime();
//
//			//return 1;
//		//}
//	}
//
//	if (BuffsCount > 0)
//	{
//		pHelper->Unknown60 = timeGetTime();
//		g_Console.AddMessage(3,"BuffsCount = %d", BuffsCount);
//		return 1;
//	}
//
//	return 0;
//}
