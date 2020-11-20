#include "stdafx.h"
#include "RankingEx.h"
#include "Import.h"
char* CharacterCode (int a)
{
	switch(a)
	{
		case 0:  return pGetTextLine(pTextLineThis,20);
		case 1:  return pGetTextLine(pTextLineThis,25);
		case 2:  return pGetTextLine(pTextLineThis,1669);
		case 3:  return pGetTextLine(pTextLineThis,1669);
		case 16: return pGetTextLine(pTextLineThis,21);
		case 17: return pGetTextLine(pTextLineThis,26);
		case 18: return pGetTextLine(pTextLineThis,1668);
		case 19: return pGetTextLine(pTextLineThis,1668);
		case 32: return pGetTextLine(pTextLineThis,22);
		case 33: return pGetTextLine(pTextLineThis,27);
		case 34: return pGetTextLine(pTextLineThis,1670);
		case 35: return pGetTextLine(pTextLineThis,1670);
		case 48: return pGetTextLine(pTextLineThis,23);
		case 50: return pGetTextLine(pTextLineThis,1671);
		case 66: return pGetTextLine(pTextLineThis,24);
		case 67: return pGetTextLine(pTextLineThis,24);
		case 64: return pGetTextLine(pTextLineThis,24);
		case 65: return pGetTextLine(pTextLineThis,24);
		case 68: return pGetTextLine(pTextLineThis,1672);
		case 80: return pGetTextLine(pTextLineThis,1687);
		case 81: return pGetTextLine(pTextLineThis,1688);
		case 82: return pGetTextLine(pTextLineThis,1689);
		case 83: return pGetTextLine(pTextLineThis,1689);
		case 96: return pGetTextLine(pTextLineThis,3150);
		case 97: return pGetTextLine(pTextLineThis,3151);		
		case 98: return pGetTextLine(pTextLineThis,3151);		
	}
	return "unknown";
}

