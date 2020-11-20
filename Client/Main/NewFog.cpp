#include "Stdafx.h"
#include "NewFog.h"
#include "Offset.h"
#include "Defines.h"
#include "Camera.h"
#include "Util.h"
#include "TMemory.h"
#include "Import.h"

cNewFog gNewFog;

void cNewFog::Load()
{
    this->Init();
}

void cNewFog::Init()
{
    this->MainFogAllowed();
    SetOp3(0x004D9969,this->glMainEnable,ASM::CALL);
    SetOp3(0x004D9C7C,this->glMainDisable,ASM::CALL);
}

void cNewFog::MainFogAllowed()
{
    SetRange(0x004D9938,2, ASM::NOP);
    SetRange(0x004D9954,2, ASM::NOP);
	SetByte(0x004D87EC, 0x0E);
}

bool cNewFog::CheckBlackMaps()
{
    switch(pMapNumber)
    {
        case eMapNumber::Dungeon:
        case eMapNumber::LostTower:
		case eMapNumber::DevilSquare:
        case eMapNumber::ChaosCastle1:
        case eMapNumber::ChaosCastle2:
        case eMapNumber::ChaosCastle3:
        case eMapNumber::ChaosCastle4:
        case eMapNumber::ChaosCastle5:
        case eMapNumber::ChaosCastle6:
        case eMapNumber::ChaosCastle7:
        case eMapNumber::BloodCastle1:
        case eMapNumber::BloodCastle2:
        case eMapNumber::BloodCastle3:
        case eMapNumber::BloodCastle4:
        case eMapNumber::BloodCastle5:
        case eMapNumber::BloodCastle6:
        case eMapNumber::BloodCastle7:
        case eMapNumber::BloodCastle8:
        case eMapNumber::DevilSquare6:
        {
            return true;
        }
        break;
        // ----
        default:
        {
            return false;
        }
        break;
    }
    return false;
}


bool cNewFog::CheckEventMaps()
{
    switch(pMapNumber)
    {
        case eMapNumber::Icarus:
        case eMapNumber::DevilSquare:
        case eMapNumber::ChaosCastle1:
        case eMapNumber::ChaosCastle2:
        case eMapNumber::ChaosCastle3:
        case eMapNumber::ChaosCastle4:
        case eMapNumber::ChaosCastle5:
        case eMapNumber::ChaosCastle6:
        case eMapNumber::ChaosCastle7:
        case eMapNumber::BloodCastle1:
        case eMapNumber::BloodCastle2:
        case eMapNumber::BloodCastle3:
        case eMapNumber::BloodCastle4:
        case eMapNumber::BloodCastle5:
        case eMapNumber::BloodCastle6:
        case eMapNumber::BloodCastle7:
        case eMapNumber::BloodCastle8:
        case eMapNumber::DevilSquare6:
        {
            return true;
        }
        break;
        // ----
        default:
        {
            return false;
        }
        break;
    }
    return false;
}


bool cNewFog::glAllowedFog(GLenum cap)
{
    if (cap != GL_TEXTURE_2D || cap != GL_DEPTH_TEST || cap != GL_ALPHA || cap != GL_2D || cap != GL_RGB || cap != GL_ALPHA_SCALE || cap != GL_RGBA)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void cNewFog::glMainEnable(GLenum cap)
{
    if(*(DWORD*)(MAIN_SCREEN_STATE) == GameProcess)
    {
        if (gNewFog.CheckEventMaps() != true)
        {
            if (gNewFog.CheckBlackMaps() == true)
            {
                if (gNewFog.glAllowedFog(cap) == true)
                {
                    GLfloat params[4] = { 0.f,0.f,0.f,0.f };
                    // ----
					GLfloat StartCoords[1] = { (floorf(oCam_RotZ - 45.0f) * 360.0f) + 3000.0f };
                    // ----
                    glEnable(GL_FOG);
                    glFogfv(GL_FOG_COLOR,params);
                    glFogf(GL_FOG_DENSITY,0.001f);
                    glFogf(GL_FOG_MODE,GL_LINEAR);
                    glFogf(GL_FOG_START,2100.0f);
                    glFogfv(GL_FOG_END,StartCoords);
                }
            }
            else
            {
                if (gNewFog.glAllowedFog(cap) == true)
                {
                    GLfloat params[4] = { 1.f,1.f,1.f,0.f };
                    GLfloat StartCoords[1] = { (floorf(oCam_RotZ - 45.0f) * 360.0f) + 3000.0f };
                    // ----
                    glEnable(GL_FOG);
                    glFogfv(GL_FOG_COLOR,params);
                    glFogf(GL_FOG_DENSITY,0.0001f);
                    glFogf(GL_FOG_MODE,GL_LINEAR);
                    glFogf(GL_FOG_START,2100.0f);
                    glFogfv(GL_FOG_END,StartCoords);
                }
            }
        }
        else
        {
            gNewFog.glMainDisable();
        }
    }
}


void cNewFog::glMainDisable()
{
    if(*(DWORD*)(MAIN_SCREEN_STATE) == GameProcess)
    {
        glDisable(GL_FOG);
    }
}