#include "stdafx.h"
#include "Font.h"
#include "Import.h"

cFont *Font[100];
cColor *Fcolor = new cColor;

cFont::cFont(TCHAR* Name, int Size, int Weight)
{
	this->MAKE = CreateFontA(Size, 0, 0, 0, Weight, FALSE, FALSE, FALSE, 0x4E4, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 3, FF_DONTCARE | DEFAULT_PITCH, Name);
	//this->MAKE = CreateFont(Size, 0, 0, 0, Weight, 0, 0, FALSE, 0x4E4, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, 3, FF_DONTCARE | DEFAULT_PITCH, Name);
}
cColor::cColor()
{
	Vector4(0xAC, 0xFF, 0x38, 0xFF, this->ShinyGreen);
	Vector4(0xFF, 0xBD, 0x19, 0xFF, this->Gold);
	Vector4(0xFF, 0xFF, 0xFF, 0xFF, this->White);
	Vector4(0xFF, 0x69, 0x19, 0xFF, this->Orange);
	Vector4(0xFF, 0, 0, 0x80, this->Red50);
	Vector4(0, 0, 0, 0, this->Trans);
	Vector4(0, 0, 0, 0x32, this->Trans25);
	Vector4(0xFF, 0, 0, 0xFF, this->Red);
	Vector4(0, 0xFF, 0, 0xFF, this->Green);
	Vector4(0, 0, 0xFF, 0xFF, this->Blue);
	Vector4(50, 50, 50, 150, this->Black);
}

cFont::~cFont()
{
	return;
}

cColor::~cColor()
{
	return;
}

int cFont::SetFont()
{
	return pSetTextSize(pTextThis(), this->MAKE);
}

int cFont::DrawText(int x, int y, BYTE *Color, BYTE * BgColor, int width, LPINT align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	
	this->SetFont();
	pSetTextColor(pTextThis(), Color[0], Color[1], Color[2], Color[3]);
	pSetTextBGColor(pTextThis(), BgColor[0], BgColor[1], BgColor[2], BgColor[3]);
	return pDrawText(pTextThis(), x, y, Buff, width, 0, (LPINT)align, 0);
}

void cColor::LoadResource() //dllmain - Just loaded because in one cpp.
{
	char Arial[] = "Arial";
	char Tahoma[] = "Tahoma";
	int BaseFontSize = 0;

	Font[ARIAL_12] = new cFont(Arial, BaseFontSize + 12, FW_NORMAL);
	Font[ARIAL_14] = new cFont(Arial, BaseFontSize + 14, FW_NORMAL);
	Font[ARIAL_15] = new cFont(Arial, BaseFontSize + 15, FW_NORMAL);
	Font[ARIAL_16] = new cFont(Arial, BaseFontSize + 16, FW_NORMAL);

	Font[ARIAL_BOLD_12] = new cFont(Arial, BaseFontSize + 12, FW_BOLD);
	Font[ARIAL_BOLD_14] = new cFont(Arial, BaseFontSize + 14, FW_BOLD);
	Font[ARIAL_BOLD_15] = new cFont(Arial, BaseFontSize + 15, FW_BOLD);
	Font[ARIAL_BOLD_16] = new cFont(Arial, BaseFontSize + 16, FW_BOLD);

	Font[TAHOMA_12] = new cFont(Tahoma, BaseFontSize + 12, FW_NORMAL);
	Font[TAHOMA_13] = new cFont(Tahoma, BaseFontSize + 13, FW_NORMAL);
	Font[TAHOMA_14] = new cFont(Tahoma, BaseFontSize + 14, FW_NORMAL);
	Font[TAHOMA_15] = new cFont(Tahoma, BaseFontSize + 15, FW_NORMAL);
	Font[TAHOMA_16] = new cFont(Tahoma, BaseFontSize + 16, FW_NORMAL);

	Font[TAHOMA_BOLD_12] = new cFont(Tahoma, BaseFontSize + 12, FW_BOLD);
	Font[TAHOMA_BOLD_13] = new cFont(Tahoma, BaseFontSize + 13, FW_BOLD);
	Font[TAHOMA_BOLD_14] = new cFont(Tahoma, BaseFontSize + 14, FW_BOLD);
	Font[TAHOMA_BOLD_15] = new cFont(Tahoma, BaseFontSize + 15, FW_BOLD);
	Font[TAHOMA_BOLD_16] = new cFont(Tahoma, BaseFontSize + 16, FW_BOLD);
	Font[TAHOMA_BOLD_17] = new cFont(Tahoma, BaseFontSize + 20, FW_BOLD);
}

