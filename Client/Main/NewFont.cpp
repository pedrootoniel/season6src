//---------------------------------------------------------------------------
#include "stdafx.h"
#include "NewFont.h"
#include "Defines.h"
#include "Util.h"

FontHook gFont;

char MyFontFaceName[100];
char sValue[99];
//--
int zBold = GetPrivateProfileInt("Font", "Bold", 0, ".\\Settings.ini");
int Height = GetPrivateProfileInt("Font", "Height", 13, ".\\Settings.ini");
int Italic = GetPrivateProfileInt("Font", "Italic", 0, ".\\Settings.ini");
int Unicode = GetPrivateProfileInt("Font", "Unicode", 0, ".\\Settings.ini");
//--
int Width = GetPrivateProfileInt("Font", "Width", 0, ".\\Settings.ini");
int UnderLine = GetPrivateProfileInt("Font", "Underline", 0, ".\\Settings.ini");
int Quality = GetPrivateProfileInt("Font", "Quality", 3, ".\\Settings.ini");
int StrikeOut = GetPrivateProfileInt("Font", "StrikeOut", 0, ".\\Settings.ini");

//---------------------------------------------------------------------------

void FontHook::Load()
{
    GetPrivateProfileStringA("Font", "Name", "Tahoma", MyFontFaceName, 100, ".\\Settings.ini");
    //--

	SetByte((Offset_CreateFontA1 + 5), 0x90);
    SetByte((Offset_CreateFontA2 + 5), 0x90);
    SetByte((Offset_CreateFontA3 + 5), 0x90);
    SetByte((Offset_CreateFontA4 + 5), 0x90);
    SetByte((Offset_CreateFontA5 + 5), 0x90);

    SetCompleteHook(0xE8, Offset_CreateFontA1, &FontHook::LoadNewFontBold);
    SetCompleteHook(0xE8, Offset_CreateFontA2, &FontHook::LoadNewFont);
    SetCompleteHook(0xE8, Offset_CreateFontA3, &FontHook::LoadNewFontBold);
    SetCompleteHook(0xE8, Offset_CreateFontA4, &FontHook::LoadNewFontBold);
    SetCompleteHook(0xE8, Offset_CreateFontA5, &FontHook::LoadNewFont);
	
    //--

}
//---------------------------------------------------------------------------
HFONT FontHook::LoadNewFont()
{
    HFONT MyFont;
    //--
    if (zBold == 0)
    {
        if (Unicode == 1)
        {
            MyFont = CreateFont(Height, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x01, 0, 0, Quality, 0, MyFontFaceName);
        }
        else
        {
            MyFont = CreateFont(Height, Width, 0, 0, 400, Italic, UnderLine, StrikeOut, 0x0, 0, 0, Quality, 0, MyFontFaceName);
        }
    }
    else
    {
        if (Unicode == 1)
        {
            MyFont = CreateFont(Height, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x01, 0, 0, Quality, 0, MyFontFaceName);
        }
        else
        {
            MyFont = CreateFont(Height, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x0, 0, 0, Quality, 0, MyFontFaceName);
        }
    }
    return MyFont;
}
HFONT FontHook::LoadNewFontBold()
{
    HFONT MyFont;
    //--
        if (Unicode == 1)
        {
            MyFont = CreateFont(Height, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x01, 0, 0, Quality, 0, MyFontFaceName);
        }
        else
        {
            MyFont = CreateFont(Height, Width, 0, 0, 700, Italic, UnderLine, StrikeOut, 0x0, 0, 0, Quality, 0, MyFontFaceName);
        }
   
   
  
    return MyFont;
}