#include "stdafx.h"
#include "HealthBar.h"
#include "Util.h"
#include "Offset.h"
#include "Camera.h"
#include "Interface.h"
#include "Object.h"
#include "User.h"
//#include "Monster.h"
#include "MonsterBar.h"
#include "Defines.h"
#include "CustomTitle.h"
//#include "ServerInfo.h"
#include "Console.h"
#include "DanhHieu.h"
#include "PrintPlayer.h"
//#include "Protocol.h"
#include "MonsterNameColor.h"
#include "Font.h"
#include "Config.h"
#include "NewParty.h"
CHPBar gHPBar;

NEW_HEALTH_BAR gNewHealthBar[MAX_MAIN_VIEWPORT];

CHPBar::CHPBar()
{

}

CHPBar::~CHPBar()
{

}

void CHPBar::ClearNewHealthBar() // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		gNewHealthBar[n].index = 0xFFFF;
		gNewHealthBar[n].type = 0;
		gNewHealthBar[n].rate = 0;
		gNewHealthBar[n].monsterid = 0;
		gNewHealthBar[n].Life = 0;
		gNewHealthBar[n].MaxLife = 0;
		gNewHealthBar[n].Level = 0;
		gNewHealthBar[n].Shield = 0;
		gNewHealthBar[n].MaxShield = 0;
		gNewHealthBar[n].SDrate = 0;
		gNewHealthBar[n].isSameGuild = false;
		gNewHealthBar[n].RankTitle = false;
		/*
		gNewHealthBar[n].HaveGuild = false;
		for	(int i=0;i<64;i++)
		{
			gNewHealthBar[n].Mark[i] = 0;
		}
		*/
	}
}

void CHPBar::InsertNewHealthBar(PMSG_NEW_HEALTH_RECV* lpInfo) // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		if(gNewHealthBar[n].index == 0xFFFF)
		{
			gNewHealthBar[n].index = lpInfo->index;
			gNewHealthBar[n].type = lpInfo->type;
			gNewHealthBar[n].rate = lpInfo->rate;
			gNewHealthBar[n].monsterid = lpInfo->monsterid;
			gNewHealthBar[n].Life = lpInfo->Life;
			gNewHealthBar[n].MaxLife = lpInfo->MaxLife;
			gNewHealthBar[n].Level = lpInfo->Level;
			gNewHealthBar[n].Shield = lpInfo->Shield;
			gNewHealthBar[n].MaxShield = lpInfo->MaxShield;
			gNewHealthBar[n].SDrate = lpInfo->SDrate;
			gNewHealthBar[n].isSameGuild = lpInfo->isSameGuild;
			gNewHealthBar[n].RankTitle = lpInfo->RankTitle;
			/*
			gNewHealthBar[n].HaveGuild = lpInfo->HaveGuild;
			if (lpInfo->type == emPlayer && lpInfo->HaveGuild)
			{
				memcpy(gNewHealthBar[n].GuildName,lpInfo->GuildName,sizeof(gNewHealthBar[n].GuildName));
				char kek[65];

				for	(int i=0;i<32;i++)
				{
					sprintf(&kek[i * 2], "%02x", lpInfo->Mark[i]);
				}
				kek[64] = '\0';

				for	(int i=0;i<64;i++)
				{
					if (kek[i]>=97)
					{
						gNewHealthBar[n].Mark[i] = (int)kek[i] - 87;
					}
					else
					{
						gNewHealthBar[n].Mark[i] = (int)kek[i] - 48;
					}
				}
			}
			*/
			return;
		}
	}
}

NEW_HEALTH_BAR* CHPBar::GetNewHealthBar(WORD index,BYTE type) // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		if(gNewHealthBar[n].index != 0xFFFF)
		{
			if(gNewHealthBar[n].index == index && gNewHealthBar[n].type == type)
			{
				return &gNewHealthBar[n];
			}
		}
	}

	return 0;
}

void getColor(int type,int &red,int &green,int &blue, int &alpha)
{
	switch(type)
	{
		case 0x0:
			alpha = 0;
		break;
		case 0x1:
			red = 0;
			green = 0;
			blue = 0;
			alpha = 0xFF;
		break;
		case 0x2:
			red = 0x80;
			green = 0x80;
			blue = 0x80;
			alpha = 0xFF;
		break;
		case 0x3:
			red = 0xFF;
			green = 0xFF;
			blue = 0xFF;
			alpha = 0xFF;
		break;
		case 0x4:
			red = 0xFF;
			green = 0;
			blue = 0;
			alpha = 0xFF;
		break;
		case 0x5:
			red = 0xFF;
			green = 0x80;
			blue = 0;
			alpha = 0xFF;
		break;
		case 0x6:
			red = 0xFF;
			green = 0xFF;
			blue = 0;
			alpha = 0xFF;
		break;
		case 0x7:
			red = 0x80;
			green = 0xFF;
			blue = 0;
			alpha = 0xFF;
		break;
		case 0x8:
			red = 0;
			green = 0xFF;
			blue = 0;
			alpha = 0xFF;
		break;
		case 0x9:
			red = 0;
			green = 0xFF;
			blue = 0x80;
			alpha = 0xFF;
		break;
		case 0xA:
			red = 0;
			green = 0xFF;
			blue = 0xFF;
			alpha = 0xFF;
		break;
		case 0xB:
			red = 0;
			green = 0x80;
			blue = 0xFF;
			alpha = 0xFF;
		break;
		case 0xC:
			red = 0;
			green = 0;
			blue = 0xFF;
			alpha = 0xFF;
		break;
		case 0xD:
			red = 0x80;
			green = 0;
			blue = 0xFF;
			alpha = 0xFF;
		break;
		case 0xE:
			red = 0xFF;
			green = 0;
			blue = 0xFF;
			alpha = 0xFF;
		break;
		case 0xF:
			red = 0xFF;
			green = 0;
			blue = 0x80;
			alpha = 0xFF;
		break;
	}
}

void DrawGuildLogo(BYTE* Mark, float startX, float startY)
{
	glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.7);
	pDrawBarForm(startX-1,startY,10,10,0.0,0);
	int line = 0;
	for	(int i=0;i<64;i++)
	{
		if (i%8==0)
		{
			line++;
		}
		int red=0;
		int green=0;
		int blue = 0;
		int alpha = 0;
		getColor(Mark[i],red,green,blue,alpha);
		pSetBlend(true);
		glColor4f(RGBTOGLFLOAT(red), RGBTOGLFLOAT(green), RGBTOGLFLOAT(blue), RGBTOGLFLOAT(alpha));
		pDrawBarForm(startX+((i%8)),startY+line,1,1,0.0f, 0);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);

	}
}


void CHPBar::DrawHealthBar()
{
	/*if (!gConfig.m_HPBar)
	{
		return;
	}
*/
	//((void(*)())0x005BA770)();

	//ItemEquip();

	int PosX, PosY;
	float LifeBarWidth = 66.95;
	char LifeDisplay[20];
	VAngle Angle;

	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		lpViewObj lpObj		= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), n);
		lpViewObj lpTarget	= gObjUser.lpViewTarget;

		bool istarget = 1;

		if( !lpTarget || (lpTarget->m_Model.ObjectType != emMonster && lpTarget->m_Model.ObjectType != emPlayer) || !lpTarget->m_Model.Unknown4 || lpTarget->aIndex != lpObj->aIndex )
		{
			istarget = 0;
		}

		if(!lpObj)
		{
			continue;
		}

		if(lpObj->m_Model.Unknown4 == 0)
		{
			continue;
		}

		NEW_HEALTH_BAR* lpNewHealthBar = this->GetNewHealthBar(lpObj->aIndex,lpObj->m_Model.ObjectType);

		if(lpNewHealthBar == 0)
		{
			continue;
		}

		int LifePercent = lpNewHealthBar->rate/10;
		float BarWidth = (((35.95 - 1) / 100.0f) * lpNewHealthBar->rate) - 1;
		float BarWidth2 = (((66.95 - 1) / 100.0f) * lpNewHealthBar->rate) - 1;
		float SDBarWidth = (((35.95 - 1) / 100.0f) * lpNewHealthBar->SDrate) - 1;

		Angle.X = lpObj->m_Model.VecPos.X;
		Angle.Y = lpObj->m_Model.VecPos.Y;
		Angle.Z = lpObj->m_Model.VecPos.Z + lpObj->m_Model.Unknown216.Z + 100.0;

		pGetPosFromAngle(&Angle, &PosX, &PosY);
		PosX -= (int)floor(LifeBarWidth / (double)2.0);

		pSetBlend(true);

		if (lpNewHealthBar->type == emPlayer)
		{
			if(gObjUser.PlayerHPBarSwitch == 1)
			{
				if(gHPBar.PlayerHPBar == TRUE)
				{

					if (this->IsPartyMember(n))
					{
						glColor4f(RGBTOGLFLOAT(63), RGBTOGLFLOAT(124), RGBTOGLFLOAT(204), 0.9); // Öâåò ôîíà äëÿ èìåíè
					}
					else if (lpNewHealthBar->isSameGuild == true)
					{
						glColor4f(RGBTOGLFLOAT(18), RGBTOGLFLOAT(226), RGBTOGLFLOAT(131), 0.9); // Öâåò ôîíà äëÿ èìåíè
					}
					else
					{
						glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Öâåò ôîíà äëÿ èìåíè
					}

					if (istarget)
					{					
					//
					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Öâåò ôîíà äëÿ õïáàðà
					pDrawBarForm((float)(PosX + 15), (float)(PosY - 9.5), 35.95, 4, 0.0, 0); // Ôîí õïáàðà

					if(gObjUser.SDByPass == 0)
					{
						pDrawBarForm((float)(PosX + 15), (float)(PosY - 6.5), 35.95, 4, 0.0, 0); // Ôîí SD
					}
					//
			
					glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT(ABS(((255.0f/100.0f)*lpNewHealthBar->rate)-255.0f)), RGBTOGLFLOAT(0), 0.8); // Öâåò ÕÏ Áàðà
					pDrawBarForm((float)(PosX + 16), (float)(PosY - 8.5), BarWidth, 1.5, 0.0, 0); // ÕïÁàð

					if(gObjUser.SDByPass == 0)
					{
						glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT((255.0f/100.0f)*lpNewHealthBar->SDrate), RGBTOGLFLOAT(0), 0.8); // Öâåò SD Áàðà
						pDrawBarForm((float)(PosX + 16), (float)(PosY - 5.5), SDBarWidth, 1.5, 0.0, 0); // SD Áàð
					}
					}
					if(!istarget)
					{
						/*
						if (this->IsPartyMember(n))
						{
							pDrawBarForm((float)(PosX + 16), (float)(PosY), BarWidth, 1.5, 0.0, 0); // ÕïÁàð
						}
						*/
						pDrawBarForm((float)(PosX + 8), (float)(PosY - 12), 45.95, 10, 0.0, 0); // Ôîí äëÿ èìåíè
						pDrawColorText(lpObj->Name, PosX -1, PosY - 10.5, 66.95, 1, eWhite, 9, 3); // Äðàâ èìåíè
						/*
						if (lpNewHealthBar->HaveGuild)
						{
							DrawGuildLogo(lpNewHealthBar->Mark,(float)(PosX + 9), (float)(PosY - 12));
							pDrawColorText(lpObj->Name, PosX -1, PosY - 10.5, 73, 1, eWhite, 9, 3); // Äðàâ èìåíè
						}
						else
						{
							pDrawColorText(lpObj->Name, PosX -1, PosY - 10.5, 66.95, 1, eWhite, 9, 3); // Äðàâ èìåíè
						}
						*/
					}
					if(!istarget)
					{
						if(gObjUser.TitleBarSwitch == 1)
						{
							if(gHPBar.TitleBar == TRUE)
							{
							gHPBar.DrawRankTitle_1 ( lpNewHealthBar->RankTitle, PosX + 38.0f, PosY - 30.0f );
							gHPBar.DrawRankTitle_2 ( lpNewHealthBar->RankTitle, PosX + 38.0f, PosY - 25.0f );
							}
						}
					}
				}
			}
		}
		else
		{
			MONSTERBAR_DATA* HpBarEx = gMonsterBar.GetHPBar(lpNewHealthBar->monsterid);
			if(gHPBar.LifeBar == TRUE)
			{				
				if(HpBarEx == 0)
				{
					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Öâåò ôîíà äëÿ èìåíè

					if (!istarget)
					{
						pDrawBarForm((float)(PosX - 1), (float)(PosY - 12), 66.95, 10, 0.0, 0); // Ôîí äëÿ èìåíè
					}
					else
					{
						pDrawBarForm((float)(PosX - 1), (float)(PosY - 22), 66.95, 20, 0.0, 0); // Ôîí äëÿ èìåíè
					}

					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Öâåò ôîíà äëÿ õïáàðà
					pDrawBarForm((float)(PosX - 1), (float)(PosY - 1.5), 66.95, 6, 0.0, 0); // Ôîí õïáàðà

					glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT(ABS(((255.0f/100.0f)*lpNewHealthBar->rate)-255.0f)), RGBTOGLFLOAT(0), 0.8); // Öâåò ÕÏ Áàðà

					pDrawBarForm((float)(PosX), (float)(PosY), BarWidth2, 3, 0.0, 0); // ÕïÁàð
							if(!istarget)
							{
								
								pDrawColorText(lpObj->Name, PosX -1, PosY - 11, 66.95, 1, eWhite, 9, 3); // Äðàâ èìåíè

								for (int h = 0; h < MAX_NAME_COLOR; h++)
								{
									int color[MAX_NAME_COLOR];
									color[h] = Color4f ( gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Red, gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Green, gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Blue, gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Alpha );

									if(lpObj->ID == gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Class)
									{
										pDrawColorText(lpObj->Name, PosX -1, PosY - 11, 66.95, 1, color[h], 9, 3); // Äðàâ èìåíè
										break;
									}
								}
							}
							else
							{

								char Text[100];
								//char HP[20];
								//char MaxHP[20];
								//strcpy(HP, this->GetHPValue((int)lpNewHealthBar->Life));
								//strcpy(MaxHP, this->GetHPValue((int)lpNewHealthBar->MaxLife));

								sprintf(Text, "Lvl: %d HP: %s/%s", lpNewHealthBar->Level, this->ParseReducedValue((int)lpNewHealthBar->Life), this->ParseReducedValue((int)lpNewHealthBar->MaxLife));
								
								pDrawColorText(lpObj->Name, PosX -1, PosY - 21, 67, 1, eWhite, 9, 3); // Äðàâ èìåíè

								for (int h = 0; h < MAX_NAME_COLOR; h++)
								{
									int color[MAX_NAME_COLOR];
									color[h] = Color4f ( gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Red, gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Green, gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Blue, gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Alpha );
									if(lpObj->ID == gCustomMonsterNameColor.m_CustomMonsterColorInfo[h].Class)
									{
										pDrawColorText(lpObj->Name, PosX -1, PosY - 21, 67, 1, color[h], 9, 3); // Äðàâ èìåíè
										break;
									}
								}
								if(gConfig.CustomerName == 1996)
								{
									pDrawColorText(Text, PosX -1, PosY - 11, 67, 1, eWhite, 9, 3); // Äðàâ èíôû
								}
						}
				}
				else
				{
					glColor4f(RGBTOGLFLOAT(HpBarEx->Red), RGBTOGLFLOAT(HpBarEx->Green), RGBTOGLFLOAT(HpBarEx->Blue), HpBarEx->Opacity); // Öâåò ôîíà äëÿ èìåíè

					if (!istarget)
					{
						pDrawBarForm((float)(PosX - 1), (float)(PosY - 22), 66.95, 20, 0.0, 0); // Ôîí äëÿ èìåíè
					}
					else
					{
						pDrawBarForm((float)(PosX - 1), (float)(PosY - 32), 66.95, 30, 0.0, 0); // Ôîí äëÿ èìåíè
					}

					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); // Öâåò ôîíà äëÿ õïáàðà
					pDrawBarForm((float)(PosX - 1), (float)(PosY - 1.5), 66.95, 6, 0.0, 0); // Ôîí õïáàðà

					glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT(ABS(((255.0f/100.0f)*lpNewHealthBar->rate)-255.0f)), RGBTOGLFLOAT(0), 0.8); // Öâåò ÕÏ Áàðà

					pDrawBarForm((float)(PosX), (float)(PosY), BarWidth2, 3, 0.0, 0); // ÕïÁàð

					if (!istarget)
					{
						pDrawColorText(lpObj->Name, PosX -1, PosY - 11, 66.95, 1, eWhite, 9, 3); // Äðàâ èìåíè
						pDrawColorText(HpBarEx->Text, PosX -1, PosY - 21, 66.95, 1, eWhite, 9, 3); // Äðàâ èìåíè
					}
					else
					{
						char Text[100];
						/*char HP[20];
						char MaxHP[20];
						strcpy(HP, GetHPValue((int)lpNewHealthBar->Life));
						strcpy(MaxHP, GetHPValue((int)lpNewHealthBar->MaxLife));*/
						sprintf(Text, "Lvl: %d HP: %s/%s", lpNewHealthBar->Level, this->ParseReducedValue((int)lpNewHealthBar->Life), this->ParseReducedValue((int)lpNewHealthBar->MaxLife));

						pDrawColorText(HpBarEx->Text, PosX -1, PosY - 31, 66.95, 1, eWhite, 9, 3); // Äðàâ ñàáèìåíè
						pDrawColorText(lpObj->Name, PosX -1, PosY - 21, 66.95, 1, eWhite, 9, 3); // Äðàâ èìåíè
						pDrawColorText(Text, PosX -1, PosY - 11, 66.95, 1, eWhite, 9, 3); // Äðàâ èíôû
					}
				}
			}
		}
		pGLSwitch();
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
				if(gHPBar.TitleBar == TRUE)
				{
					gHPBar.DrawRankTitle_1 ( gDanhHieu.m_RankSlot, PosX + 47.0f, PosY - 45.0f );
					gHPBar.DrawRankTitle_2 ( gDanhHieu.m_RankSlot, PosX + 47.0f, PosY - 40.0f );
				}
			}

	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);
}

bool CHPBar::IsPartyMember(int ViewportID)
{
	for( int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++ )
	{
		PartyList PartyMember	= *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);
		//lpViewObj lpPartyObj	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), PartyMember.ViewportID);
		if (ViewportID == PartyMember.ViewportID)
		{
			return true;
		}
	}

	return false;
}


void CHPBar::DrawAllHPBars()
{
	gHPBar.DrawHealthBar();
}
//
char* CHPBar::ParseReducedValue(DWORD Num)
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

char* CHPBar::del_char(char* s, char c)
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
void CHPBar::LoadRankTitle() {
	this->TitleBar				= true;
	this->LifeBar				= true;
	this->PlayerHPBar			= true;
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
void CHPBar::DrawRankTitle_1 ( int lpTitle, int PosX, int PosY ) {
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
void CHPBar::DrawRankTitle_2 ( int Title, int PosX, int PosY ) {
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
