#include "StdAfx.h"
#include "FakeOnline.h"
#include "User.h"
#include "readscript.h"
#ifdef NOLOAD
//========================================================================================================================
CFakeOnline s_FakeOnline;


//========================================================================================================================
void CFakeOnline::Init()
{
}
//========================================================================================================================
void CFakeOnline::LoadFileFakeOnline(char *filename)
{
	
	if((SMDFile = fopen(filename, "r")) == NULL)
	{
		MessageBoxA(0,"CGMBOT::LoadFileFakeOnline() error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	SMDToken Token;
	int iIndex;


	char Name[11];
	int aIndex;
	int Class;
	int Map;
	int MapX;
	int MapY;
	int isGM;
	int ItemType0;
	int ItemLevel0;
	int ItemType1;
	int ItemLevel1;
	int ItemType2;
	int ItemLevel2;
    int ItemType3;
	int ItemLevel3;
	int ItemType4;
	int ItemLevel4;
	int ItemType5;
	int ItemLevel5;
	int ItemType6;
	int ItemLevel6;
	int ItemType7;
	int ItemLevel7;
	int ItemType8;
	int ItemLevel8;
	int Active;


	while(true)
	{
		Token = GetToken();
		
		if(Token == END)
			break;
	
		if(Token == NUMBER)
		{
	
			
			while(true)
			{	
			
				Token = GetToken();
				
				if(strcmp("end",TokenString) == 0)
					break;

			
				aIndex = TokenNumber;
			  

				Token = GetToken();
				memcpy(Name,TokenString,sizeof(Name));


				
				Token = GetToken();
				Class = TokenNumber;

				Token = GetToken();
				Map = TokenNumber;

				Token = GetToken();
				MapX = TokenNumber;

				Token = GetToken();
				MapY = TokenNumber;

				Token = GetToken();
				isGM = TokenNumber;

				Token = GetToken();
				ItemType0 = TokenNumber;

				

				Token = GetToken();
				ItemLevel0 = TokenNumber;


				Token = GetToken();
				ItemType1 = TokenNumber;

				Token = GetToken();
				ItemLevel1 = TokenNumber;


				Token = GetToken();
				ItemType2 = TokenNumber;

				Token = GetToken();
				ItemLevel2 = TokenNumber;



				Token = GetToken();
				ItemType3 = TokenNumber;

				Token = GetToken();
				ItemLevel3 = TokenNumber;


				Token = GetToken();
				ItemType4 = TokenNumber;

				Token = GetToken();
				ItemLevel4 = TokenNumber;



				Token = GetToken();
				ItemType5 = TokenNumber;

				Token = GetToken();
				ItemLevel5 = TokenNumber;



				Token = GetToken();
				ItemType6 = TokenNumber;

				Token = GetToken();
				ItemLevel6 = TokenNumber;



				Token = GetToken();
				ItemType7 = TokenNumber;

				Token = GetToken();
				ItemLevel7 = TokenNumber;



				Token = GetToken();
				ItemType8 = TokenNumber;

				Token = GetToken();
				ItemLevel8 = TokenNumber;



				this->iCountFake++;
				this->InsertFakeOnline(aIndex,Name,1,Class,Map,MapX,MapY,isGM,ItemType0,ItemLevel0,ItemType1,ItemLevel1,ItemType2,ItemLevel2,ItemType3,ItemLevel3,ItemType4,ItemLevel4,ItemType5,ItemLevel5,ItemType6,ItemLevel6,ItemType7,ItemLevel7,ItemType8,ItemLevel8);
	
			}

			
		}
	}

	fclose(SMDFile);
	return;
}
//=====================================
//	Dark Wizard Fake Attack
//=====================================
void CFakeOnline::DarkWizardFakeAttack(LPOBJ lpObj)
{
	int Skill = 9;
	CMagicInf * lpMagic;

	//if (gObjGetMagicSearch(lpObj, 9) != NULL) SearchSkill = 9;
	//else return;

	lpMagic = gObjGetMagicSearch(lpObj, Skill);
	//if (lpMagic == NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic, lpObj->X, lpObj->Y, 0, 0, -1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n = 0; n<MAX_VIEWPORT_MONSTER; n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if (lpObj->VpPlayer2[n].state == 0) continue;
		if (tObjNum >= 0)
		{
			if (gObj[tObjNum].Type == OBJ_MONSTER)
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ((attr & 1) != 1)
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if (6 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE);
					}
				}
			}
		}
	}

	//this->UseMana(lpObj->m_Index);
}
void CFakeOnline::FakeAttackStart()
{
	for (int n = 0; n<OBJMAX; n++)
	{
		LPOBJ lpObj = &gObj[n];

		if (lpObj->FakeState == true)
		{
			if (CheckOutsideZone(lpObj))
			{
				bool Attack = false;

				if (lpObj->Dexterity > 0 && lpObj->Dexterity <= 3000)
				{
					lpObj->OffAttackSpeed++;
					if (lpObj->OffAttackSpeed == 10)
					{
						Attack = true;
						lpObj->OffAttackSpeed = 0;
					}
				}
				else if (lpObj->Dexterity > 3000 && lpObj->Dexterity <= 6000)
				{
					lpObj->OffAttackSpeed++;
					if (lpObj->OffAttackSpeed == 9)
					{
						Attack = true;
						lpObj->OffAttackSpeed = 0;
					}
				}
				else if (lpObj->Dexterity > 6000 && lpObj->Dexterity <= 9000)
				{
					lpObj->OffAttackSpeed++;
					if (lpObj->OffAttackSpeed == 8)
					{
						Attack = true;
						lpObj->OffAttackSpeed = 0;
					}
				}
				else if (lpObj->Dexterity > 9000 && lpObj->Dexterity <= 12000)
				{
					lpObj->OffAttackSpeed++;
					if (lpObj->OffAttackSpeed == 7)
					{
						Attack = true;
						lpObj->OffAttackSpeed = 0;
					}
				}
				else if (lpObj->Dexterity > 12000 && lpObj->Dexterity <= 15000)
				{
					lpObj->OffAttackSpeed++;
					if (lpObj->OffAttackSpeed == 5)
					{
						Attack = true;
						lpObj->OffAttackSpeed = 0;
					}
				}
				else if (lpObj->Dexterity > 15000 && lpObj->Dexterity <= 18000)
				{
					lpObj->OffAttackSpeed++;
					if (lpObj->OffAttackSpeed == 4)
					{
						Attack = true;
						lpObj->OffAttackSpeed = 0;
					}
				}
				else if (lpObj->Dexterity > 18000 && lpObj->Dexterity <= 21000)
				{
					lpObj->OffAttackSpeed++;
					if (lpObj->OffAttackSpeed == 3)
					{
						Attack = true;
						lpObj->OffAttackSpeed = 0;
					}
				}
				else if (lpObj->Dexterity > 21000 && lpObj->Dexterity <= 24000)
				{
					lpObj->OffAttackSpeed++;
					if (lpObj->OffAttackSpeed == 2)
					{
						Attack = true;
						lpObj->OffAttackSpeed = 0;
					}
				}
				else if (lpObj->Dexterity > 24000)
				{
					Attack = true;
				}
				else
				{
					continue;
				}

				if (Attack == false)
				{
					continue;
				}


				//if (this->KickFallen) lpObj->OffAttack = 0;



				switch (lpObj->Class)
				{
				case 0:	this->DarkWizardFakeAttack(lpObj);		break;
					//case 1:	this->DarkKnightOff(lpObj);		break;
					//case 2:	this->FairyElfOff(lpObj);		break;
					//case 3:	this->MagicGladiatorOff(lpObj);	break;
					//case 4:	this->DarkLordOff(lpObj);		break;

				}
			}
		
		}
	}


}
void CFakeOnline::InsertFakeOnline(int iIndex,char Name[11],int Active,int Class,int Map,int MapX,int MapY,int isGM,int ItemType0,int ItemLevel0,int ItemType1,int ItemLevel1,int ItemType2,int ItemLevel2,int ItemType3,int ItemLevel3,int ItemType4,int ItemLevel4,int ItemType5,int ItemLevel5,int ItemType6,int ItemLevel6,int ItemType7,int ItemLevel7,int ItemType8,int ItemLevel8)

{
	this->m_FakeOnline[iIndex].Active = Active;
	this->m_FakeOnline[iIndex].Class = Class;
	this->m_FakeOnline[iIndex].Map= Map;
	this->m_FakeOnline[iIndex].MapX= MapX;
	this->m_FakeOnline[iIndex].MapY= MapY;
	this->m_FakeOnline[iIndex].isGM = isGM;
	this->m_FakeOnline[iIndex].ItemType0 = ItemType0;
	this->m_FakeOnline[iIndex].ItemLevel0= ItemLevel0;
	this->m_FakeOnline[iIndex].ItemType1 = ItemType1;
	this->m_FakeOnline[iIndex].ItemLevel1= ItemLevel1;
	this->m_FakeOnline[iIndex].ItemType2 = ItemType2;
	this->m_FakeOnline[iIndex].ItemLevel2= ItemLevel2;
	this->m_FakeOnline[iIndex].ItemType3 = ItemType3;
	this->m_FakeOnline[iIndex].ItemLevel3= ItemLevel3;
	this->m_FakeOnline[iIndex].ItemType4 = ItemType4;
	this->m_FakeOnline[iIndex].ItemLevel4= ItemLevel4;
	this->m_FakeOnline[iIndex].ItemType5 = ItemType5;
	this->m_FakeOnline[iIndex].ItemLevel5= ItemLevel5;
	this->m_FakeOnline[iIndex].ItemType6 = ItemType6;
	this->m_FakeOnline[iIndex].ItemLevel6= ItemLevel6;
	this->m_FakeOnline[iIndex].ItemType7 = ItemType7;
	this->m_FakeOnline[iIndex].ItemLevel7= ItemLevel7;
	this->m_FakeOnline[iIndex].ItemType8 = ItemType8;
	this->m_FakeOnline[iIndex].ItemLevel8= ItemLevel8;

	strcpy(this->m_FakeOnline[iIndex].Name,Name);
}

void CFakeOnline::FakeOnlineSet(char Name[11],int Active,int Class,int Map,int MapX,int MapY,int isGM,int ItemType0,int ItemLevel0,int ItemType1,int ItemLevel1,int ItemType2,int ItemLevel2,int ItemType3,int ItemLevel3,int ItemType4,int ItemLevel4,int ItemType5,int ItemLevel5,int ItemType6,int ItemLevel6,int ItemType7,int ItemLevel7,int ItemType8,int ItemLevel8)
{

	if (Active == NULL)
	{
		return;
	}
	 int iIndex = gObjAddUser();
	 
	 gObjCharZeroSet(iIndex);
	 gObjSetMonster(iIndex,0);
	 LPOBJ m_gObj = &gObj[iIndex];
	 m_gObj->FakeState = true;
	 m_gObj->m_Index = iIndex;
	// g_OfflineState[m_gObj->m_Index].IsOffState = 1;
	 //NEED TO FIX IT
	memcpy(m_gObj->AccountID, "FakeSystem", MAX_ACCOUNT_LEN);
	memcpy(m_gObj->Name, Name, MAX_ACCOUNT_LEN);
	m_gObj->X = MapX; m_gObj->TX = m_gObj->X; m_gObj->MTX = m_gObj->X; m_gObj->m_OldX = m_gObj->X; m_gObj->StartX = m_gObj->X;
	m_gObj->Y = MapY; m_gObj->TY = m_gObj->Y; m_gObj->MTY = m_gObj->Y; m_gObj->m_OldY = m_gObj->Y; m_gObj->StartY = m_gObj->Y;
	m_gObj->MapNumber = Map;
	m_gObj->Dir = rand()%8;	
	m_gObj->Level = 200;
	m_gObj->Type = OBJ_USER;

//	lpObj->MapNumber = MAP_INDEX_RORENCIA;
	//MapC[m_gObj->MapNumber].GetMapPos(m_gObj->MapNumber, m_gObj->X, m_gObj->Y);
	//gObjMoveGate(
	if(Class == 0 ||Class == 1 || Class == 3 )
	{
	m_gObj->Class = CLASS_WIZARD;
	}
	else if (Class == 16 || Class == 17 || Class == 19)
	{
	m_gObj->Class = CLASS_KNIGHT;
	}

	else if (Class == 32 || Class == 33 || Class == 35)
	{
	  m_gObj->Class = CLASS_ELF;
	}
	else if (Class == 48 || Class == 50)
	{
	 m_gObj->Class = CLASS_MAGUMSA;
	}
	else if (Class == 64 || Class == 66)
	{
    m_gObj->Class = CLASS_DARKLORD;
	}
	else
	{
    m_gObj->Class = CLASS_KNIGHT;
	}

    if(Class == 1 ||Class == 17 || Class == 33 )
	{
	m_gObj->ChangeUP = 1;
	}
	if(Class == 3 ||Class == 19 || Class == 35 || Class == 50 || Class == 66 )
	{
	m_gObj->ChangeUP = 1;
	m_gObj->ChangeUP3rd = true;
	}
	
	m_gObj->Life = 500;
	m_gObj->MaxLife = 500;
	m_gObj->RegenTime = 0;
	m_gObj->DieRegen = 0;
	m_gObj->m_MoveRange = 10;
	m_gObj->DbClass |= Class;
	m_gObj->Live = TRUE;
    m_gObj->Type = OBJ_USER;
    m_gObj->TargetNumber = -1;
	m_gObj->Connected = PLAYER_PLAYING;

	if(ItemType0 != 0)
	m_gObj->pInventory[0].m_Type = ItemType0;
	m_gObj->pInventory[0].m_Level = ItemLevel0;

	if(ItemType1 != 0)
	m_gObj->pInventory[1].m_Type = ItemType1;
	m_gObj->pInventory[1].m_Level = ItemLevel1;


	if(ItemType2 != 0)
	m_gObj->pInventory[2].m_Type = ItemType2;
	m_gObj->pInventory[2].m_Level = ItemLevel2;

	if(ItemType3 != 0)
	m_gObj->pInventory[3].m_Type = ItemType3;
	m_gObj->pInventory[3].m_Level = ItemLevel3;

	if(ItemType4 != 0)
	m_gObj->pInventory[4].m_Type = ItemType4;
	m_gObj->pInventory[4].m_Level = ItemLevel4;

	if(ItemType5 != 0)
	m_gObj->pInventory[5].m_Type = ItemType5;
	m_gObj->pInventory[5].m_Level = ItemLevel5;

	if(ItemType6 != 0)
	m_gObj->pInventory[6].m_Type = ItemType6;
	m_gObj->pInventory[6].m_Level = ItemLevel6;

	if(ItemType7 != 0)
	m_gObj->pInventory[7].m_Type = ItemType7;
	m_gObj->pInventory[7].m_Level = ItemLevel7;

	if(ItemType8 != 0)
    m_gObj->pInventory[8].m_Type = ItemType8;
	m_gObj->pInventory[8].m_Level = ItemLevel8;


	if(isGM == 1)
	{
	m_gObj->Authority = 32;
	m_gObj->AuthorityCode |= 32;
	m_gObj->m_ViewSkillState |= 0x1000000; 
	}
	 ::gObjMakePreviewCharSet(iIndex);

	 LogAdd("[FakeOnline]Name - %s , Active %d,Class %d/%d,Map %d,MapX %d,MapY %d",Name,Active,Class, m_gObj->Class,Map,MapX,MapY);
	
}
void CFakeOnline::CreateFakeOnline()
{
	for(int i=OBJ_STARTUSERINDEX;i<OBJMAX;i++)
	{
		if(gObj[i].FakeState == true)
		{
		 gObjCharZeroSet(i);
		 gObj[i].Type = OBJ_EMPTY;
		 gObj[i].Connected = PLAYER_EMPTY;
		}
	
	}
	
	for(int i=-1;i<this->iCountFake;i++)
	{	
		//if(m_FakeOnline[i].Active == 1)
		//{
		FakeOnlineSet(m_FakeOnline[i].Name,m_FakeOnline[i].Active,m_FakeOnline[i].Class,m_FakeOnline[i].Map,m_FakeOnline[i].MapX,m_FakeOnline[i].MapY,m_FakeOnline[i].isGM,
			m_FakeOnline[i].ItemType0,m_FakeOnline[i].ItemLevel0,
			m_FakeOnline[i].ItemType1,m_FakeOnline[i].ItemLevel1,
			m_FakeOnline[i].ItemType2,m_FakeOnline[i].ItemLevel2,
			m_FakeOnline[i].ItemType3,m_FakeOnline[i].ItemLevel3,
			m_FakeOnline[i].ItemType4,m_FakeOnline[i].ItemLevel4,
			m_FakeOnline[i].ItemType5,m_FakeOnline[i].ItemLevel5,
			m_FakeOnline[i].ItemType6,m_FakeOnline[i].ItemLevel6,
			m_FakeOnline[i].ItemType7,m_FakeOnline[i].ItemLevel7,
			m_FakeOnline[i].ItemType8,m_FakeOnline[i].ItemLevel8);
	   // }
	}



}
void CFakeOnline::SetZenoStruct()
{
	for(int i=0;i<512;i++)
	{
	this->m_FakeOnline[i].Active;
	this->m_FakeOnline[i].Class;
	this->m_FakeOnline[i].Map;
	this->m_FakeOnline[i].MapX;
	this->m_FakeOnline[i].MapY;
	this->m_FakeOnline[i].isGM;
	this->m_FakeOnline[i].ItemType0;
	this->m_FakeOnline[i].ItemLevel0;
	this->m_FakeOnline[i].ItemType1;
	this->m_FakeOnline[i].ItemLevel1;
	this->m_FakeOnline[i].ItemType2;
	this->m_FakeOnline[i].ItemLevel2;
	this->m_FakeOnline[i].ItemType3;
	this->m_FakeOnline[i].ItemLevel3;
	this->m_FakeOnline[i].ItemType4;
	this->m_FakeOnline[i].ItemLevel4;
	this->m_FakeOnline[i].ItemType5;
	this->m_FakeOnline[i].ItemLevel5;
	this->m_FakeOnline[i].ItemType6;
	this->m_FakeOnline[i].ItemLevel6;
	this->m_FakeOnline[i].ItemType7;
	this->m_FakeOnline[i].ItemLevel7;
	this->m_FakeOnline[i].ItemType8;
	this->m_FakeOnline[i].ItemLevel8;
	this->m_FakeOnline[i].Name;
	this->iCountFake = 0;
	}
}
void CFakeOnline::ReloadFakeOnline()
{
	this->SetZenoStruct();
	this->DeleteFakeOnline();
	this->LoadFileFakeOnline(gDirPath.GetNewPath("FakeOnline.txt"));
	this->CreateFakeOnline();
}
void CFakeOnline::DeleteFakeOnline()
{
	for(int i=OBJ_STARTUSERINDEX;i<OBJMAX;i++)
	{
		if(gObj[i].FakeState == true)
		{
		 gObjCharZeroSet(i);
		 gObj[i].Type = OBJ_EMPTY;
		 gObj[i].Connected = PLAYER_EMPTY;
		}
	
	}
}

void CFakeOnline::FakeBaseAct(LPOBJ lpObj)
{
	LPOBJ lpTargetObj = NULL;





	if (lpObj->TargetNumber >= 0)
		lpTargetObj = &gObj[lpObj->TargetNumber];
	else
		lpObj->m_ActState.Emotion = 0;

	if (lpObj->m_ActState.Emotion == 0)
	{
		if (lpObj->m_Attribute)
		{
			if (lpObj->m_ActState.Attack)
			{
				lpObj->m_ActState.Attack = 0;
				lpObj->TargetNumber = -1;
				lpObj->NextActionTime = 500;
			}

			int actcode1 = rand() % 2;

			if (lpObj->m_Attribute == 100)
				actcode1 = 1;

			if (actcode1 == 0)
			{
				lpObj->m_ActState.Rest = 1;
				lpObj->NextActionTime = 500;
			}
			else if (lpObj->m_MoveRange > 0 && !lpObj->m_SkillHarden && !lpObj->m_iSkillStunTime)
			{
				if (lpObj->m_Attribute != 100)
				{
					gObjMonsterMoveAction(lpObj);
				}
				else
				{
					int tx = 0;
					int ty = 0;

					if (lpObj->m_RecallMon >= 0)
					{
						if (gObj[lpObj->m_RecallMon].Connected > PLAYER_LOGGED)
						{
							LPOBJ lpRecallObj = &gObj[lpObj->m_RecallMon];

							if (lpRecallObj->m_Rest == FALSE)
							{
								if (gObjGetTargetPos(lpObj, lpRecallObj->X, lpRecallObj->Y, tx, ty) == TRUE)
								{
									lpObj->MTX = tx;
									lpObj->MTY = ty;
									lpObj->m_ActState.Move = 1;
									lpObj->NextActionTime = 1000;
								}
							}
						}
					}
				}
			}

				if (lpObj->m_Attribute == 100)
				{
					lpObj->TargetNumber = gObjMonsterSearchEnemy(lpObj, OBJ_MONSTER);
				}
				else
				{

					lpObj->TargetNumber = gObjMonsterSearchEnemy(lpObj, OBJ_USER);
				}
			

			if (lpObj->TargetNumber >= 0)
			{
				lpObj->m_ActState.EmotionCount = 30;
				lpObj->m_ActState.Emotion = 1;
			}
		}
	}
	else if (lpObj->m_ActState.Emotion == 1)
	{
		if (lpObj->m_ActState.EmotionCount > 0)
		{
			lpObj->m_ActState.EmotionCount--;
		}
		else
		{
			lpObj->m_ActState.Emotion = 0;
		}

		if (lpTargetObj != NULL && lpObj->TargetNumber >= 0 && lpObj->PathStartEnd == 0) //??
		{
			if (BC_MAP_RANGE(lpObj->MapNumber))
			{
				int iRAND_CHANGE_TARGET = rand() % 10;

				if (iRAND_CHANGE_TARGET == 3)
					lpObj->LastAttackerID = -1;

				if (iRAND_CHANGE_TARGET == 1)
				{
					if (lpObj->LastAttackerID != -1 && lpObj->LastAttackerID != lpObj->TargetNumber)
					{
						if (gObj[lpObj->LastAttackerID].Connected > PLAYER_LOGGED &&
							lpObj->MapNumber == gObj[lpObj->LastAttackerID].MapNumber)
						{
							lpObj->TargetNumber = lpObj->LastAttackerID;
							lpTargetObj = &gObj[lpObj->LastAttackerID];
						}
					}
				}
			}

			int dis = gObjCalDistance(lpObj, lpTargetObj);
			int attackrange;


			if (lpObj->m_AttackType >= 100)	// #warning Change this To Level
				attackrange = lpObj->m_AttackRange + 2;
			else
				attackrange = lpObj->m_AttackRange;

			if (dis <= attackrange)
			{
				int tuser = lpObj->TargetNumber;
				int map = gObj[tuser].MapNumber;
				BYTE attr;

				if (MapC[map].CheckWall(lpObj->X, lpObj->Y, gObj[tuser].X, gObj[tuser].Y) == TRUE)
				{
					attr = MapC[map].GetAttr(gObj[tuser].X, gObj[tuser].Y);

					lpObj->m_ActState.Attack = 1;
					/*if ( (attr&1) != 1 )
					{
					lpObj->m_ActState.Attack = 1;
					}
					else
					{
					lpObj->TargetNumber = -1;
					lpObj->m_ActState.EmotionCount = 30;
					lpObj->m_ActState.Emotion = 1;
					}*/ //???

					lpObj->Dir = GetPathPacketDirPos(lpTargetObj->X - lpObj->X, lpTargetObj->Y - lpObj->Y);
					lpObj->NextActionTime = lpObj->m_AttackSpeed;
				}
				else
				{
					//if( lpObj->Class == 275 )
					//{
					lpObj->TargetNumber = -1;
					lpObj->m_ActState.Attack = 0;
					lpObj->NextActionTime = 500;
					lpObj->m_ActState.Emotion = 2;
					lpObj->m_ActState.EmotionCount = 2;
					lpObj->m_ActState.Move = 1;
					//}*/

					//gObjMonsterMoveAction(lpObj);
					//lpObj->m_ActState.Emotion = 3;
					//lpObj->m_ActState.EmotionCount = 10;
				}
			}
			else
			{
				if (gObjMonsterGetTargetPos(lpObj) == TRUE)
				{
					if (MapC[lpObj->MapNumber].CheckWall(lpObj->X, lpObj->Y, lpObj->MTX, lpObj->MTY) == TRUE)
					{
						lpObj->m_ActState.Move = 1;
						lpObj->NextActionTime = 400;
						lpObj->Dir = GetPathPacketDirPos(lpTargetObj->X - lpObj->X, lpTargetObj->Y - lpObj->Y);
					}
					else
					{
						gObjMonsterMoveAction(lpObj);
						lpObj->m_ActState.Emotion = 3;
						lpObj->m_ActState.EmotionCount = 10;

					}
				}
				else
				{
					gObjMonsterMoveAction(lpObj);
				}
			}
		}
	}
	else if (lpObj->m_ActState.Emotion == 2)
	{
		if (lpObj->m_ActState.EmotionCount > 0)
		{
			lpObj->m_ActState.EmotionCount--;
		}
		else
		{
			lpObj->m_ActState.Emotion = 0;
		}

		lpObj->m_ActState.Move = 1;
		lpObj->NextActionTime = 800;

		if (lpTargetObj)
		{
			int tdir = GetPathPacketDirPos(lpTargetObj->X - lpObj->X, lpTargetObj->Y - lpObj->Y) * 2;
			lpObj->MTX += RoadPathTable[tdir] * (-3);
			lpObj->MTY += RoadPathTable[tdir + 1] * (-3);
		}
	}
	else if (lpObj->m_ActState.Emotion == 3)
	{
		if (lpObj->m_ActState.EmotionCount > 0)
		{
			lpObj->m_ActState.EmotionCount--;
		}
		else
		{
			lpObj->m_ActState.Emotion = 0;
		}

		lpObj->m_ActState.Move = 0;
		lpObj->m_ActState.Attack = 0;
		lpObj->NextActionTime = 400;
	}

}
#endif