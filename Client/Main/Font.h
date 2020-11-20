#pragma once

class cFont
{
public:
	cFont(TCHAR* Name, int Size, int Weight);
	virtual ~cFont();
	int SetFont();
	int DrawText(int x, int y, BYTE *Color, BYTE * BgColor, int width, LPINT align, LPCSTR Text, ...);
	HFONT MAKE;
	//HFONT Bold;
	//HFONT Arial14;
}; extern cFont *Font[100];

class cColor
{
public:
	cColor();
	virtual ~cColor();
	void LoadResource();
	BYTE ShinyGreen[4];
	BYTE Gold[4];
	BYTE White[4];
	BYTE Orange[4];
	BYTE Red[4];
	BYTE Red50[4];
	BYTE Blue[4];
	BYTE Green[4];
	BYTE Trans[4];
	BYTE Trans25[4];
	BYTE Black[4];
}; extern cColor *Fcolor;

enum FONT_TYPE
{
	ARIAL_12,
	ARIAL_14,
	ARIAL_15,
	ARIAL_16,

	ARIAL_BOLD_12,
	ARIAL_BOLD_14,
	ARIAL_BOLD_15,
	ARIAL_BOLD_16,

	TAHOMA_12,
	TAHOMA_13,
	TAHOMA_14,
	TAHOMA_15,
	TAHOMA_16,

	TAHOMA_BOLD_12,
	TAHOMA_BOLD_13,
	TAHOMA_BOLD_14,
	TAHOMA_BOLD_15,
	TAHOMA_BOLD_16,
	TAHOMA_BOLD_17,
};