#include "stdafx.h"
#include "HealthBar2.h"
#include "Util.h"
#include "Defines.h"
#include "Offset.h"
#include "Import.h"
#include "Object.h"
#include "array.h"
#include "TMemory.h"
#include "CustomTitle.h"
#include "MemScript.h"
#include "PrintPlayer.h"
#include "DanhHieu.h"
#include "Font.h"
#include "User.h"
#ifdef NOLOAD
struct sMonsterBar
{
	DWORD GetTime;
    int aIndex;
    int Life;
    int MaxLife;
    short Level;
	int ViewID;
};

array<sMonsterBar> MonsterBar;

struct sPlayerBar : sMonsterBar
{
    int SD;
    int MaxSD;
	int	RankTitle;
	bool ChatShowed;
};

array<sPlayerBar> PlayerBar;
bool lifebar = true;

cHPBar	gHPBar;

DWORD LastTime = 0;


void cHPBar::Load()
{
	SetOp((LPVOID)0x005B96E8, (LPVOID)this->DrawHP, ASM::CALL);
	this->TitleBar				= true;
	this->LifeBar				= true;
	this->PlayerHPBar			= true;
	this->LoadRankTitle();
}

void cHPBar::SetTargetData(PMSG_TARGETDATA_ANS * lpMsg)
{
    if(lpMsg->isMonster)
    {
        sMonsterBar *tempBar = NULL;
        for (int i = 0; i < MonsterBar.size(); ++i)
        {
            if (MonsterBar[i].aIndex == lpMsg->aIndex)
            {
                tempBar = &MonsterBar[i];
                break;
            }
        }

        if(tempBar == NULL)
        {
            sMonsterBar Temp;
			int ID = MonsterBar.add(Temp);
			tempBar = &MonsterBar[ID];
            tempBar->aIndex = lpMsg->aIndex;
        }

        PMSG_TARGET_MONSTER_DATA *pRecv = (PMSG_TARGET_MONSTER_DATA*)lpMsg;

        tempBar->Level = pRecv->Level;
        tempBar->Life = pRecv->Life;
        tempBar->MaxLife = pRecv->MaxLife;

		if (tempBar->Life > tempBar->MaxLife)
			tempBar->Life = tempBar->MaxLife;

		tempBar->ViewID = -1;
		tempBar->GetTime = GetTickCount();
    }
    else
    {
        sPlayerBar *tempBar = NULL;
        for (int i = 0; i < PlayerBar.size(); ++i)
        {
            if (PlayerBar[i].aIndex == lpMsg->aIndex)
            {
                tempBar = &PlayerBar[i];
                break;
            }
        }

        if(tempBar == NULL)
        {
            sPlayerBar Temp;
            int ID = PlayerBar.add(Temp);
			tempBar = &PlayerBar[ID];
            tempBar->aIndex = lpMsg->aIndex;
        }

        PMSG_TARGET_PLAYER_DATA *pRecv = (PMSG_TARGET_PLAYER_DATA*)lpMsg;

        tempBar->Level = pRecv->Level;
        tempBar->Life = pRecv->Life;
        tempBar->MaxLife = pRecv->MaxLife;
        tempBar->SD = pRecv->SD;
        tempBar->MaxSD = pRecv->MaxSD;
		tempBar->RankTitle	= pRecv->RankTitle;
		this->SurvivorKill	=	0;
		this->SurvivorKill	=	pRecv->SurvivorKill;
		this->SurvivorDie	=	0;
		this->SurvivorDie	=	pRecv->SurvivorDie;

		if (tempBar->Life > tempBar->MaxLife)
			tempBar->Life = tempBar->MaxLife;
		if (tempBar->SD > tempBar->MaxSD)
			tempBar->SD = tempBar->MaxSD;

		tempBar->ViewID = -1;
		tempBar->ChatShowed = false;
		tempBar->GetTime = GetTickCount();
    }
}

char* cHPBar::ParsingHP(DWORD Num)
{
	char Text[50];
	if (Num >= 10000000000)
		sprintf(Text, "%ldkkk", Num / 1000000000);
	else if (Num >= 10000000)
		sprintf(Text, "%ldkk", Num / 1000000);
	else if (Num >= 10000)
		sprintf(Text, "%ldk", Num / 1000);
	else
		sprintf(Text, "%ld", Num);

	return strdup(Text);
}

char* cHPBar::del_char(char* s, char c)
{
    char * buf = strchr(s, c);
    while( buf )
    {
        if(buf + 1)
            strcpy(buf, buf + 1);
        else
            buf[0] = '\0';
        buf = strchr(buf, c);
    }
    return s;
}
// ----------------------------------------------------------------------------------------------
void cHPBar::DrawHP()
{
	//gHPBar.DrawTitle();
	VAngle Angle;
	int PosX, PosY;
	bool MonsterTarget = false;
	bool PlayerTarget = false;

	// first of all we check all Viewport and if server send monster/player HP it insert ViewPortID to our structure
	for (int ViewPortID = 0; ViewPortID < 120; ViewPortID++)
	{
		lpViewObj lpObj = (ObjectPreview*)pGetPreviewStruct(pPreviewThis(), ViewPortID);

		// check if it exist and it is player or monster
		if (!lpObj || (lpObj->m_Model.ObjectType != emMonster && lpObj->m_Model.ObjectType != emPlayer) || !lpObj->m_Model.Unknown4)
		{
			// check if we have same ViewportID monster in our array and delete it
			for (int i = 0; i < MonsterBar.size(); i++)
			{
				if (ViewPortID == MonsterBar[i].ViewID)
				{
					MonsterBar.remove_index_fast(i);
					break;
				}
			}
			// check if we have same ViewportID Player in our array and delete it
			for (int i = 0; i < PlayerBar.size(); i++)
			{
				if (ViewPortID == PlayerBar[i].ViewID)
				{
					PlayerBar.remove_index_fast(i);
					break;
				}
			}
			continue;
		}

		if (lpObj->m_Model.ObjectType == emMonster)
		{
			// goes throw all monsterbars (that server send to us)
			for (int i = 0; i < MonsterBar.size(); ++i)
			{
				// check if it needs to be deleted by life decrees or lifetime (too old)
				if (MonsterBar[i].Life <= 0 || GetTickCount() - MonsterBar[i].GetTime > 10000)
				{
					MonsterBar.remove_index_fast(i--);	// i--, so we could parse new item by same index in array
					continue;
				}

				// if monster exist in array, add ViewID so we could render it later
				if (MonsterBar[i].aIndex == lpObj->aIndex)
				{
					MonsterBar[i].ViewID = ViewPortID;

					// if monster is targeted by user, make it latest in array (so it would be rendered latest and on the top of all)
					if (gObjUser.m_TargetType > 0 && gObjUser.lpViewTarget != NULL && gObjUser.lpViewTarget->aIndex == lpObj->aIndex)
					{
						MonsterBar.make_latest(i);
						MonsterTarget = true;
					}
					break;
				}
			}
		}
		else
		{
			// goes  throw all playerbars (that server send to us)
			for (int i = 0; i < PlayerBar.size(); ++i)
			{
				// check if it needs to be deleted by life decrees or lifetime (too old)
				if (PlayerBar[i].Life <= 0 || GetTickCount() - PlayerBar[i].GetTime > 10000)
				{
					PlayerBar.remove_index_fast(i--);	// i--, so we could parse new item by same index in array
					continue;
				}

				// check if it is our player with hpbar
				if (PlayerBar[i].aIndex == lpObj->aIndex)
				{
					PlayerBar[i].ViewID = ViewPortID;

					// check player for chat window and player target
					for (int j = 0; j < 120; j++)
					{
						// search throw all structure of chat messages (or something)
						BYTE *pChatMember = (BYTE*)(pChatStructure + 700 * j);

						char TName[10];
						strncpy(TName, (char*)pChatMember, 10);

						// if it's not our player, goes next
						if (strcmp(TName, lpObj->Name))
							continue;

						// Check if guys is chating
						if (*(DWORD*)(pChatMember + 660) > 0)
						{
							PlayerBar[i].ChatShowed = true;
							break;							// break to prevent targeting
						}
						else
						{
							PlayerBar[i].ChatShowed = false;
						}

						// if player target him, make it latest so we could render it on top later
						if (*(DWORD*)(pChatMember + 144) > 0)
						{
							PlayerTarget = true;
							PlayerBar.make_latest(i);
						}

						break;
					}

					break;
				}
			}
		}
	}

	// Render time !!!
	// Take real line height for using it later
	//float lineHeight = 20.0f;

	// monsters, so players would be always on top
	if(gHPBar.LifeBar == TRUE)
	{
	for (int i = 0; i < MonsterBar.size(); ++i)
	{
		// check if it's not an error
		if (MonsterBar[i].ViewID == -1)
			continue;
		
		// taking it's structure
		lpViewObj lpObj = (ObjectPreview*)pGetPreviewStruct(pPreviewThis(), MonsterBar[i].ViewID);
		// to prevent that player doesn't exist
		if (!lpObj || (lpObj->m_Model.ObjectType != emMonster && lpObj->m_Model.ObjectType != emPlayer) || !lpObj->m_Model.Unknown4)
		{
			MonsterBar.remove_index(i--);	// i--, so we could parse new item by same index in array
			continue;
		}

		// taking it's coordinates
		Angle.X = lpObj->m_Model.VecPos.X;
		Angle.Y = lpObj->m_Model.VecPos.Y;
		Angle.Z = lpObj->m_Model.VecPos.Z + lpObj->m_Model.Unknown216.Z + 100.0;

		pGetPosFromAngle(&Angle, &PosX, &PosY);

		// calculating some width and pos shit
		float BarWidth = 78.1f * (MonsterBar[i].Life / (MonsterBar[i].MaxLife * 1.0f));
		PosX -= 40;

		// taking this bool for more easier way to use it
		bool MouseOver = MonsterTarget && (i == MonsterBar.size() - 1);

		// For blend fix
		pSetBlend(true);

		// making needed color (if it is targeting, make it fully visible, others = 100/255 blank)
		DWORD Color = Color4f(255, 255, 255, 100);
		if (MouseOver)
			Color = Color4f(255, 255, 255, 255);

		// render this background and life meter
        glColor4f(0.0, 0.0, 0.0, 0.7);
        pDrawBarForm((float)PosX, (float)PosY, 80, 4.5, 0, 0);
		glColor3f(2.0, 0.0, 0.2);
        pDrawBarForm((float)PosX + 1, (float)PosY + 1.4f, BarWidth, 2.0, 0, 0);
		// if targeting, show more info about monster
		if (MouseOver)
		{
			// draw background
			glColor4f(0.0f, 0.0f, 0.0f, 0.30f);
			pDrawBarForm((float)PosX -15, (float)PosY - 17, 110, 25.0f, 0.0, 0);

			// draw first line - Name
			pDrawColorText(lpObj->Name, PosX -7.5, PosY - 18, 100, 1, Color, 9, 3);

			// draw second line - other stuff
			char Text[50];
			sprintf(Text, "Lvl %d, HP %s/%s", MonsterBar[i].Level, ParsingHP(MonsterBar[i].Life), ParsingHP(MonsterBar[i].MaxLife));
			pDrawColorText(Text, PosX, PosY - 9, 80, 1, Color, 9, 3);
		}
		else
		{
			// draw background
			glColor4f(0.0f, 0.0f, 0.0f, 0.3f);
			pDrawBarForm((float)PosX, (float)PosY - 13, 80, 10.0f, 0.0, 0);
			// draw name
			pDrawColorText(lpObj->Name, PosX -7.5, PosY -12.5, 100, 1, eWhite, 9, 3);
		}
		pGLSwitchBlend();
	}
	}
    // the sweetest part about players :DD
    for ( int i = 0; i < PlayerBar.size(); ++i ) {
        // check if it's not an error or chat showed
        if ( PlayerBar[i].ViewID == -1 || PlayerBar[i].ChatShowed ) {
            continue;
        }

        // taking it's structure
        lpViewObj lpObj = ( ObjectPreview* ) pGetPreviewStruct ( pPreviewThis(), PlayerBar[i].ViewID );

        // to prevent that player doesn't exist
        if ( !lpObj || ( lpObj->m_Model.ObjectType != emMonster && lpObj->m_Model.ObjectType != emPlayer ) || !lpObj->m_Model.Unknown4 ) {
            PlayerBar.remove_index ( i-- ); // i--, so we could parse new item by same index in array
            continue;
        }

        // taking it's coordinates
        Angle.X = lpObj->m_Model.VecPos.X;
        Angle.Y = lpObj->m_Model.VecPos.Y;
        Angle.Z = lpObj->m_Model.VecPos.Z + lpObj->m_Model.Unknown216.Z + 100.0;
        pGetPosFromAngle ( &Angle, &PosX, &PosY );
        // calculating some width and pos shit
        float LifeBarWidth = 45.1f * ( PlayerBar[i].Life / ( PlayerBar[i].MaxLife * 1.0f ) );
		float SDBarWidth = 45.1f * ( PlayerBar[i].SD / ( PlayerBar[i].MaxSD * 1.0f ) );
		PosX -= 40.0f;
		PosY += 25.0f;
        // taking this bool for more easier way to use it 
        // For blend fix
		if(gObjUser.TitleBarSwitch == 1)
		{
			if(gHPBar.TitleBar == TRUE)
			{
            gHPBar.DrawRankTitle_1 ( PlayerBar[i].RankTitle, PosX + 47.0f, PosY - 60.0f );
            gHPBar.DrawRankTitle_2 ( PlayerBar[i].RankTitle, PosX + 47.0f, PosY - 60.0f );
			}
		}

		if(gObjUser.PlayerHPBarSwitch == 1)
		{
			if(gHPBar.PlayerHPBar == TRUE)
			{
			pSetBlend ( true );
            // draw background and name
			glColor4f(0.0f, 0.0f, 0.0f, 0.58f);
			pDrawBarForm((float)PosX + 17.0f, (float)PosY - 48.0f, 50, 10.0f, 0.0, 0);
			// draw hp
        	glColor4f(0.0, 0.0, 0.0, 0.7);
        	pDrawBarForm((float)PosX + 18.0f, (float)PosY - 48.0f, 47, 4.0, 0, 0);
			glColor3f(2.0, 0.0, 0.0);
        	pDrawBarForm((float)PosX + 19.0f, (float)PosY - 47.3f, LifeBarWidth, 2, 0, 0);
			// draw sd
        	glColor4f(0.0, 0.0, 0.0, 0.7);
        	pDrawBarForm((float)PosX + 18.0f, (float)PosY - 43.5f, 47, 4.0, 0, 0);
			glColor3f(2.0, 2.0, 0.0);
        	pDrawBarForm((float)PosX + 19.0f, (float)PosY - 42.5f, SDBarWidth, 2, 0, 0);
			pGLSwitchBlend();   // for blend objects
			glColor3f(1.0, 1.0, 1.0);
			}
		}
	}
			lpViewObj lpObj = gObjUser.lpViewPlayer;
			DWORD CurrentTick = GetTickCount();
			DWORD Delay = (CurrentTick - gHPBar.m_TargetUpdateTick);
			// ----
			if (!lpObj || lpObj->m_Model.ObjectType != emPlayer || !lpObj->m_Model.Unknown4)
			{
				return;
			}
			// ----
			
			Angle.X = lpObj->m_Model.VecPos.X;
			Angle.Y = lpObj->m_Model.VecPos.Y;
			Angle.Z = lpObj->m_Model.VecPos.Z + lpObj->m_Model.Unknown216.Z + 100.0;
			pGetPosFromAngle(&Angle, &PosX, &PosY);
			PosX -= 40.0f;
			PosY += 25.0f;
			//
			if(gObjUser.TitleBarSwitch == 1)
			{
				gHPBar.DrawRankTitle_1 ( gDanhHieu.m_RankSlot, PosX + 47.0f, PosY - 60.0f );
				gHPBar.DrawRankTitle_2 ( gDanhHieu.m_RankSlot, PosX + 47.0f, PosY - 60.0f );
			}
			if(gObjUser.PlayerHPBarSwitch == 1)
			{
				pSetBlend(true);
				// For blend fix
				float BarWidth = 45.1f * (ViewCurHP / (ViewMaxHP * 1.0f));
				float SDBarWidth = 45.1f * (ViewCurSD / (ViewMaxSD * 1.0f));
				float lineHeight1 = 25.0f * (pWinHeightReal - 0.6f);
				glColor4f(0.0f, 0.0f, 0.0f, 0.58f);
				//pDrawBarForm((float)PosX + 17.0f, (float)PosY - 48.0f, 0, lineHeight1, 0.0, 0);
				// draw hp
        		glColor4f(0.0, 0.0, 0.0, 0.7);
        		pDrawBarForm((float)PosX + 18.0f, (float)PosY - 48.0f, 47, 4.0, 0, 0);
				glColor3f(2.0, 0.0, 0.0);
        		pDrawBarForm((float)PosX + 19.0f, (float)PosY - 47.3f, BarWidth, 2, 0, 0);
				// draw sd
        		glColor4f(0.0, 0.0, 0.0, 0.7);
        		pDrawBarForm((float)PosX + 18.0f, (float)PosY - 43.5f, 47, 4.0, 0, 0);
				glColor3f(2.0, 2.0, 0.0);
        		pDrawBarForm((float)PosX + 19.0f, (float)PosY - 42.5f, SDBarWidth, 2, 0, 0);
				//
				pGLSwitchBlend();	// for blend objects	
				glColor3f(1.0, 1.0, 1.0);
			}
}
// ----------------------------------------------------------------------------------------------
void cHPBar::LoadRankTitle() {

    this->RankTextColor[0] = Color4f ( 172, 255, 56, 255 );
    this->RankTextColor[1] = Color4f ( 255, 189, 25, 255 );
    this->RankTextColor[2] = Color4f ( 255, 255, 255, 255 );
    this->RankTextColor[3] = Color4f ( 255, 255, 255, 180 );
    this->RankTextColor[4] = Color4f ( 255, 105, 25, 255 );
    this->RankTextColor[5] = Color4f ( 50, 50, 50, 100 );
    this->RankTextColor[6] = Color4f ( 50, 50, 50, 150 );
    this->RankTextColor[7] = Color4f ( 220, 20, 60, 255 );
    this->RankTextColor[8] = Color4f ( 225, 0, 0, 255 );
    this->RankTextColor[9] = Color4f ( 0, 225, 139, 255 );
    this->RankTextColor[10] = Color4f ( 1, 223, 119, 255 );
    this->RankTextColor[11] = Color4f ( 153, 102, 204, 255 );
    this->RankTextColor[12] = Color4f ( 36, 242, 252, 255 );
    this->RankTextColor[13] = Color4f ( 255, 255, 0, 255 );
    this->RankTextColor[14] = Color4f ( 69, 39, 18, 255 );
}
// ----------------------------------------------------------------------------------------------
void cHPBar::DrawRankTitle_1 ( int lpTitle, int PosX, int PosY ) {
    int TitleCode = lpTitle -1;

    if ( gCustomTitle.m_CustomTitle[TitleCode].ImgCode == 0 ) { return; }

    pSetBlend ( true );
    float Hornor_Width = gCustomTitle.m_CustomTitle[TitleCode].width;
    float Hornor_Height = gCustomTitle.m_CustomTitle[TitleCode].height;
    //PosX -= Hornor_Width - 25.0f;
	PosX -= ( int ) floor ( Hornor_Width / 1.7f );
    PosY -= Hornor_Height;
    pDrawGUI ( gCustomTitle.m_CustomTitle[TitleCode].ImgCode, PosX, PosY, Hornor_Width, Hornor_Height );
    pGLSwitchBlend();   // for blend objects
	glColor3f(1.0, 1.0, 1.0);
}
// ----------------------------------------------------------------------------------------------
void cHPBar::DrawRankTitle_2 ( int Title, int PosX, int PosY ) {
    int TitleCode = Title -1;
    int color = gCustomTitle.m_CustomTitle[TitleCode].color;
    float Hornor_Width = 150.0f;

    if ( gCustomTitle.m_CustomTitle[TitleCode].TitleText[0] == '\0' ) { return; }

    pSetBlend ( true );
    glColor4f ( 0.0f, 0.0f, 0.0f, 0.40f );
    pDrawBarForm ( ( float ) PosX - 55.0f, ( float ) PosY - 4.0f, 100.0f, 12.0f, 0.0f, 0 );
    PosX -= ( int ) floor ( Hornor_Width / 1.88f );
    PosY -= 3.0f;
    pDrawColorText ( gCustomTitle.m_CustomTitle[TitleCode].TitleText, PosX, PosY, Hornor_Width, 1.5, gHPBar.RankTextColor[color], 32, 3 );
    pGLSwitchBlend();
	glColor3f(1.0, 1.0, 1.0);
}
// ----------------------------------------------------------------------------------------------
#endif