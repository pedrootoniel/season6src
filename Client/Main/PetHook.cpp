#include "stdafx.h"
#include "Protect.h"
#include "PetHook.h"
#include "Util.h"
#include "Defines.h"
#include "Import.h"
#include "TMemory.h"
#include "Pet.h"

ObjCreateBug gObjCreateBug		= (ObjCreateBug)0x00501700;
ObjCreatePet gObjCreatePet		= (ObjCreatePet)0x00835E40;

void gObjCreatePetEx(int ItemId)
{
    int ItemSwitch        = *(WORD*)ItemId;
    int PetPreview        = LODWORD(pPreviewPetThis) + 776;
    // ----
    switch (ItemSwitch)
    {
		if(gProtect.m_MainInfo.CustomItemPack == 0)
		{
		case ITEM(12,189):
		case ITEM(12,194):
		//case ITEM(12,196):
		case ITEM(12,220):
		case ITEM(12,221):
		//case ITEM(12,222):
			pRefreshViewportEffect(oUserPreviewStruct, oUserPreviewStruct + 776, 0);
			break;
		}
        //case ITEM(13,147):
		//	gObjCreateBug(ITEM2(13,147), PetPreview + 252, PetPreview, 0, 0);
		//	break;
        //case ITEM(13,148):
		//	gObjCreateBug(ITEM2(13,148), PetPreview + 252, PetPreview, 0, 0);
		//	break;
        //case ITEM(13,149):
		//	gObjCreateBug(ITEM2(13,149), PetPreview + 252, PetPreview, 0, 0);
		//	break;
        //case ITEM(13,150):
		//	gObjCreateBug(ITEM2(13,150), PetPreview + 252, PetPreview, 0, 0);
		//	break;
        //case ITEM(13,151):
		//	gObjCreateBug(ITEM2(13,151), PetPreview + 252, PetPreview, 0, 0);
		//	break;
        //case ITEM(13,152):
		//	gObjCreateBug(ITEM2(13,152), PetPreview + 252, PetPreview, 0, 0);
		//	break;
        //case ITEM(13,153):
        //    gObjCreateBug(ITEM2(13,153), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,154):
        //    gObjCreateBug(ITEM2(13,154), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,155):
        //    gObjCreateBug(ITEM2(13,155), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,156):
        //    gObjCreateBug(ITEM2(13,156), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,157):
        //    gObjCreateBug(ITEM2(13,157), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,158):
        //    gObjCreateBug(ITEM2(13,158), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,159):
        //    gObjCreateBug(ITEM2(13,159), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,160):
        //    gObjCreateBug(ITEM2(13,160), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,161):
        //    gObjCreateBug(ITEM2(13,161), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 162):
		//	gObjCreateBug(ITEM2(13, 162), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 163):
		//	gObjCreateBug(ITEM2(13, 163), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 164):
		//	gObjCreateBug(ITEM2(13, 164), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 165):
		//	gObjCreateBug(ITEM2(13, 165), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 166):
		//	gObjCreateBug(ITEM2(13, 166), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 167):
		//	gObjCreateBug(ITEM2(13, 167), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 168):
		//	gObjCreateBug(ITEM2(13, 168), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 169):
		//	gObjCreateBug(ITEM2(13, 169), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 170):
		//	gObjCreateBug(ITEM2(13, 170), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 171):
		//	gObjCreateBug(ITEM2(13, 171), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 172):
		//	gObjCreateBug(ITEM2(13, 172), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 173):
		//	gObjCreateBug(ITEM2(13, 173), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 174):
		//	gObjCreateBug(ITEM2(13, 174), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 175):
		//	gObjCreateBug(ITEM2(13, 175), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 176):
		//	gObjCreateBug(ITEM2(13, 176), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 177):
		//	gObjCreateBug(ITEM2(13, 177), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 178):
		//	gObjCreateBug(ITEM2(13, 178), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 179):
		//	gObjCreateBug(ITEM2(13, 179), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 180):
		//	gObjCreateBug(ITEM2(13, 180), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 181):
		//	gObjCreateBug(ITEM2(13, 181), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 182):
		//	gObjCreateBug(ITEM2(13, 182), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 183):
		//	gObjCreateBug(ITEM2(13, 183), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 184):
		//	gObjCreateBug(ITEM2(13, 184), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 185):
		//	gObjCreateBug(ITEM2(13, 185), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 186):
		//	gObjCreateBug(ITEM2(13, 186), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 187):
		//	gObjCreateBug(ITEM2(13, 187), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 188):
		//	gObjCreateBug(ITEM2(13, 188), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 189):
		//	gObjCreateBug(ITEM2(13, 189), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 190):
		//	gObjCreateBug(ITEM2(13, 190), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 191):
		//	gObjCreateBug(ITEM2(13, 191), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 192):
		//	gObjCreateBug(ITEM2(13, 192), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 193):
		//	gObjCreateBug(ITEM2(13, 193), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 194):
		//	gObjCreateBug(ITEM2(13, 194), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 195):
		//	gObjCreateBug(ITEM2(13, 195), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 196):
		//	gObjCreateBug(ITEM2(13, 196), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 197):
		//	gObjCreateBug(ITEM2(13, 197), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 198):
		//	gObjCreateBug(ITEM2(13, 198), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 199):
		//	gObjCreateBug(ITEM2(13, 199), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 200):
		//	gObjCreateBug(ITEM2(13, 200), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 201):
		//	gObjCreateBug(ITEM2(13, 201), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 202):
		//	gObjCreateBug(ITEM2(13, 202), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 203):
		//	gObjCreateBug(ITEM2(13, 203), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 204):
		//	gObjCreateBug(ITEM2(13, 204), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 205):
		//	gObjCreateBug(ITEM2(13, 205), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 206):
		//	gObjCreateBug(ITEM2(13, 206), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 207):
		//	gObjCreateBug(ITEM2(13, 207), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 208):
		//	gObjCreateBug(ITEM2(13, 208), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 209):
		//	gObjCreateBug(ITEM2(13, 209), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 210):
		//	gObjCreateBug(ITEM2(13, 210), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 211):
		//	gObjCreateBug(ITEM2(13, 211), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 212):
		//	gObjCreateBug(ITEM2(13, 212), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 213):
		//	gObjCreateBug(ITEM2(13, 213), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 214):
		//	gObjCreateBug(ITEM2(13, 214), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 215):
		//	gObjCreateBug(ITEM2(13, 215), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 216):
		//	gObjCreateBug(ITEM2(13, 216), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 217):
		//	gObjCreateBug(ITEM2(13, 217), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 218):
		//	gObjCreateBug(ITEM2(13, 218), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 219):
		//	gObjCreateBug(ITEM2(13, 219), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 220):
		//	gObjCreateBug(ITEM2(13, 220), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 221):
		//	gObjCreateBug(ITEM2(13, 221), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 222):
		//	gObjCreateBug(ITEM2(13, 222), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 223):
		//	gObjCreateBug(ITEM2(13, 223), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 224):
		//	gObjCreateBug(ITEM2(13, 224), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 225):
		//	gObjCreateBug(ITEM2(13, 225), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 226):
		//	gObjCreateBug(ITEM2(13, 226), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 227):
		//	gObjCreateBug(ITEM2(13, 227), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 228):
		//	gObjCreateBug(ITEM2(13, 228), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 229):
		//	gObjCreateBug(ITEM2(13, 229), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 230):
		//	gObjCreateBug(ITEM2(13, 230), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 231):
		//	gObjCreateBug(ITEM2(13, 231), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 232):
		//	gObjCreateBug(ITEM2(13, 232), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 233):
		//	gObjCreateBug(ITEM2(13, 233), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 234):
		//	gObjCreateBug(ITEM2(13, 234), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 235):
		//	gObjCreateBug(ITEM2(13, 235), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 236):
		//	gObjCreateBug(ITEM2(13, 236), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 237):
		//	gObjCreateBug(ITEM2(13, 237), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 238):
		//	gObjCreateBug(ITEM2(13, 238), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 239):
		//	gObjCreateBug(ITEM2(13, 239), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 240):
		//	gObjCreateBug(ITEM2(13, 240), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 241):
		//	gObjCreateBug(ITEM2(13, 241), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//
		//case ITEM(13,242):
        //    gObjCreateBug(ITEM2(13,242), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,243):
        //    gObjCreateBug(ITEM2(13,243), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,244):
        //    gObjCreateBug(ITEM2(13,244), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,245):
        //    gObjCreateBug(ITEM2(13,245), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,246):
        //    gObjCreateBug(ITEM2(13,246), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,247):
        //    gObjCreateBug(ITEM2(13,247), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,248):
        //    gObjCreateBug(ITEM2(13,248), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,249):
        //    gObjCreateBug(ITEM2(13,249), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,250):
        //    gObjCreateBug(ITEM2(13,250), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,251):
        //    gObjCreateBug(ITEM2(13,251), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,252):
        //    gObjCreateBug(ITEM2(13,252), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,253):
        //    gObjCreateBug(ITEM2(13,253), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,254):
        //    gObjCreateBug(ITEM2(13,254), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,255):
        //    gObjCreateBug(ITEM2(13,255), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,256):
        //    gObjCreateBug(ITEM2(13,256), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13,257):
        //    gObjCreateBug(ITEM2(13,257), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 320):
		//	gObjCreateBug(ITEM2(13, 320), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 321):
		//	gObjCreateBug(ITEM2(13, 321), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 322):
		//	gObjCreateBug(ITEM2(13, 322), PetPreview + 252, PetPreview, 0, 0);
		//	break;
		//case ITEM(13, 323):
		//	gObjCreateBug(ITEM2(13, 323), PetPreview + 252, PetPreview, 0, 0);
		//	break;
    }
	if (ItemSwitch >= ITEM(13, 147) && ItemSwitch <= ITEM(13, 410))
	{
		gObjCreateBug(ItemSwitch + 1171, PetPreview + 252, PetPreview, 0, 0);
	}
    gObjCreatePet(ItemId);
}
bool ResetPetPreviewEx(int ItemId)
{

    bool Result;
    // ----
    if (ItemId)
        Result = *(WORD*)ItemId == 0x1A00    //Angel
        || *(WORD*)ItemId == 0x1A01        //Satan
        || *(WORD*)ItemId == 0x1A02        //Unicorn
        || *(WORD*)ItemId == 0x1A03        //Dinorant
        || *(WORD*)ItemId == 0x1A04        //Dark Horse
        || *(WORD*)ItemId == 0x1A05        //Dark Raven
        || *(WORD*)ItemId == 0x1A25        //Fenrir     //
        || *(WORD*)ItemId == ITEM(13, 64)
        || *(WORD*)ItemId == ITEM(13, 65)
        || *(WORD*)ItemId == ITEM(13, 67)
        || *(WORD*)ItemId == ITEM(13, 80)
        || *(WORD*)ItemId == ITEM(13, 106)
        || *(WORD*)ItemId == ITEM(13, 123)
        || *(WORD*)ItemId == ITEM(13, 147) //WTF
        || *(WORD*)ItemId == ITEM(13, 148)  
        || *(WORD*)ItemId == ITEM(13, 149)  
        || *(WORD*)ItemId == ITEM(13, 150)  
        || *(WORD*)ItemId == ITEM(13, 151)  
        || *(WORD*)ItemId == ITEM(13, 152)  
        || *(WORD*)ItemId == ITEM(13, 153)  
        || *(WORD*)ItemId == ITEM(13, 154)  
        || *(WORD*)ItemId == ITEM(13, 155)  
        || *(WORD*)ItemId == ITEM(13, 156)  
        || *(WORD*)ItemId == ITEM(13, 157)  
        || *(WORD*)ItemId == ITEM(13, 158)  
        || *(WORD*)ItemId == ITEM(13, 159)  
        || *(WORD*)ItemId == ITEM(13, 160)
		|| *(WORD*)ItemId == ITEM(13, 161)
		|| *(WORD*)ItemId == ITEM(13, 162)
		|| *(WORD*)ItemId == ITEM(13, 163)
		|| *(WORD*)ItemId == ITEM(13, 164)
		|| *(WORD*)ItemId == ITEM(13, 165)
		|| *(WORD*)ItemId == ITEM(13, 166)
		|| *(WORD*)ItemId == ITEM(13, 167)
		|| *(WORD*)ItemId == ITEM(13, 168)
		|| *(WORD*)ItemId == ITEM(13, 169)
		|| *(WORD*)ItemId == ITEM(13, 170)
		|| *(WORD*)ItemId == ITEM(13, 171)
		|| *(WORD*)ItemId == ITEM(13, 172)
		|| *(WORD*)ItemId == ITEM(13, 173)
		|| *(WORD*)ItemId == ITEM(13, 174)
		|| *(WORD*)ItemId == ITEM(13, 175)
		|| *(WORD*)ItemId == ITEM(13, 176)
		|| *(WORD*)ItemId == ITEM(13, 177)
		|| *(WORD*)ItemId == ITEM(13, 178)
		|| *(WORD*)ItemId == ITEM(13, 179)
		|| *(WORD*)ItemId == ITEM(13, 180)
		|| *(WORD*)ItemId == ITEM(13, 181)
		|| *(WORD*)ItemId == ITEM(13, 182)
		|| *(WORD*)ItemId == ITEM(13, 183)
		|| *(WORD*)ItemId == ITEM(13, 184)
		|| *(WORD*)ItemId == ITEM(13, 185)
		|| *(WORD*)ItemId == ITEM(13, 186)
		|| *(WORD*)ItemId == ITEM(13, 187)
		|| *(WORD*)ItemId == ITEM(13, 188)
		|| *(WORD*)ItemId == ITEM(13, 189)
		|| *(WORD*)ItemId == ITEM(13, 190)
		|| *(WORD*)ItemId == ITEM(13, 191)
		|| *(WORD*)ItemId == ITEM(13, 192)
		|| *(WORD*)ItemId == ITEM(13, 193)
		|| *(WORD*)ItemId == ITEM(13, 194)
		|| *(WORD*)ItemId == ITEM(13, 195)
		|| *(WORD*)ItemId == ITEM(13, 196)
		|| *(WORD*)ItemId == ITEM(13, 197)
		|| *(WORD*)ItemId == ITEM(13, 198)
		|| *(WORD*)ItemId == ITEM(13, 199)
		|| *(WORD*)ItemId == ITEM(13, 200)
		|| *(WORD*)ItemId == ITEM(13, 201)
		|| *(WORD*)ItemId == ITEM(13, 202)
		|| *(WORD*)ItemId == ITEM(13, 203)
		|| *(WORD*)ItemId == ITEM(13, 204)
		|| *(WORD*)ItemId == ITEM(13, 205)
		|| *(WORD*)ItemId == ITEM(13, 206)
		|| *(WORD*)ItemId == ITEM(13, 207)
		|| *(WORD*)ItemId == ITEM(13, 208)
		|| *(WORD*)ItemId == ITEM(13, 209)
		|| *(WORD*)ItemId == ITEM(13, 210)
		|| *(WORD*)ItemId == ITEM(13, 211)
		|| *(WORD*)ItemId == ITEM(13, 212)
		|| *(WORD*)ItemId == ITEM(13, 213)
		|| *(WORD*)ItemId == ITEM(13, 214)
		|| *(WORD*)ItemId == ITEM(13, 215)
		|| *(WORD*)ItemId == ITEM(13, 216)
		|| *(WORD*)ItemId == ITEM(13, 217)
		|| *(WORD*)ItemId == ITEM(13, 218)
		|| *(WORD*)ItemId == ITEM(13, 219)
		|| *(WORD*)ItemId == ITEM(13, 220)
		|| *(WORD*)ItemId == ITEM(13, 221)
		|| *(WORD*)ItemId == ITEM(13, 222)
		|| *(WORD*)ItemId == ITEM(13, 223)
		|| *(WORD*)ItemId == ITEM(13, 224)
		|| *(WORD*)ItemId == ITEM(13, 225)
		|| *(WORD*)ItemId == ITEM(13, 226)
		|| *(WORD*)ItemId == ITEM(13, 227)
		|| *(WORD*)ItemId == ITEM(13, 228)
		|| *(WORD*)ItemId == ITEM(13, 229)
		|| *(WORD*)ItemId == ITEM(13, 230)
		|| *(WORD*)ItemId == ITEM(13, 231)
		|| *(WORD*)ItemId == ITEM(13, 232)
		|| *(WORD*)ItemId == ITEM(13, 233)
		|| *(WORD*)ItemId == ITEM(13, 234)
		|| *(WORD*)ItemId == ITEM(13, 235)
		|| *(WORD*)ItemId == ITEM(13, 236)
		|| *(WORD*)ItemId == ITEM(13, 237)
		|| *(WORD*)ItemId == ITEM(13, 238)
		|| *(WORD*)ItemId == ITEM(13, 239)
		|| *(WORD*)ItemId == ITEM(13, 240)
		|| *(WORD*)ItemId == ITEM(13, 241)									   
        || *(WORD*)ItemId == ITEM(13, 242)  
        || *(WORD*)ItemId == ITEM(13, 243)  
        || *(WORD*)ItemId == ITEM(13, 244)  
        || *(WORD*)ItemId == ITEM(13, 245)  
        || *(WORD*)ItemId == ITEM(13, 246)  
        || *(WORD*)ItemId == ITEM(13, 247)  
        || *(WORD*)ItemId == ITEM(13, 248)  
        || *(WORD*)ItemId == ITEM(13, 249)  
        || *(WORD*)ItemId == ITEM(13, 250)  
        || *(WORD*)ItemId == ITEM(13, 251)  
        || *(WORD*)ItemId == ITEM(13, 252)  
        || *(WORD*)ItemId == ITEM(13, 253)
        || *(WORD*)ItemId == ITEM(13, 254)
        || *(WORD*)ItemId == ITEM(13, 255)
		|| *(WORD*)ItemId == ITEM(13, 256)
		|| *(WORD*)ItemId == ITEM(13, 257)
		|| *(WORD*)ItemId == ITEM(13, 258)
		|| *(WORD*)ItemId == ITEM(13, 259)
		|| *(WORD*)ItemId == ITEM(13, 260)
		|| *(WORD*)ItemId == ITEM(13, 261)
		|| *(WORD*)ItemId == ITEM(13, 262)
		|| *(WORD*)ItemId == ITEM(13, 263)
		|| *(WORD*)ItemId == ITEM(13, 264)
		|| *(WORD*)ItemId == ITEM(13, 265)
		|| *(WORD*)ItemId == ITEM(13, 266)
		|| *(WORD*)ItemId == ITEM(13, 267)
		|| *(WORD*)ItemId == ITEM(13, 268)
		|| *(WORD*)ItemId == ITEM(13, 269)
		|| *(WORD*)ItemId == ITEM(13, 270)
		|| *(WORD*)ItemId == ITEM(13, 271)
		|| *(WORD*)ItemId == ITEM(13, 272)
		|| *(WORD*)ItemId == ITEM(13, 273)
		|| *(WORD*)ItemId == ITEM(13, 274)
		|| *(WORD*)ItemId == ITEM(13, 275)
		|| *(WORD*)ItemId == ITEM(13, 276)
		|| *(WORD*)ItemId == ITEM(13, 277)
		|| *(WORD*)ItemId == ITEM(13, 278)
		|| *(WORD*)ItemId == ITEM(13, 279)
		|| *(WORD*)ItemId == ITEM(13, 280)
		|| *(WORD*)ItemId == ITEM(13, 281)
		|| *(WORD*)ItemId == ITEM(13, 282)
		|| *(WORD*)ItemId == ITEM(13, 283)
		|| *(WORD*)ItemId == ITEM(13, 284)
		|| *(WORD*)ItemId == ITEM(13, 285)
		|| *(WORD*)ItemId == ITEM(13, 286)
		|| *(WORD*)ItemId == ITEM(13, 287)
		|| *(WORD*)ItemId == ITEM(13, 288)
		|| *(WORD*)ItemId == ITEM(13, 289)
		|| *(WORD*)ItemId == ITEM(13, 290)
		|| *(WORD*)ItemId == ITEM(13, 291)
		|| *(WORD*)ItemId == ITEM(13, 292)
		|| *(WORD*)ItemId == ITEM(13, 293)
		|| *(WORD*)ItemId == ITEM(13, 294)
		|| *(WORD*)ItemId == ITEM(13, 295)
		|| *(WORD*)ItemId == ITEM(13, 296)
		|| *(WORD*)ItemId == ITEM(13, 297)
		|| *(WORD*)ItemId == ITEM(13, 298)
		|| *(WORD*)ItemId == ITEM(13, 299)
		|| *(WORD*)ItemId == ITEM(13, 300)
		|| *(WORD*)ItemId == ITEM(13, 301)
		|| *(WORD*)ItemId == ITEM(13, 302)
		|| *(WORD*)ItemId == ITEM(13, 303)
		|| *(WORD*)ItemId == ITEM(13, 304)
		|| *(WORD*)ItemId == ITEM(13, 305)
		|| *(WORD*)ItemId == ITEM(13, 306)
		|| *(WORD*)ItemId == ITEM(13, 307)
		|| *(WORD*)ItemId == ITEM(13, 308)
		|| *(WORD*)ItemId == ITEM(13, 309)
		|| *(WORD*)ItemId == ITEM(13, 310)
		|| *(WORD*)ItemId == ITEM(13, 311)
		|| *(WORD*)ItemId == ITEM(13, 312)
		|| *(WORD*)ItemId == ITEM(13, 313)
		|| *(WORD*)ItemId == ITEM(13, 314)
		|| *(WORD*)ItemId == ITEM(13, 315)
		|| *(WORD*)ItemId == ITEM(13, 316)
		|| *(WORD*)ItemId == ITEM(13, 317)
		|| *(WORD*)ItemId == ITEM(13, 318)
		|| *(WORD*)ItemId == ITEM(13, 319)
		|| *(WORD*)ItemId == ITEM(13, 320)
		|| *(WORD*)ItemId == ITEM(13, 321)
		|| *(WORD*)ItemId == ITEM(13, 322)
		|| *(WORD*)ItemId == ITEM(13, 323)
		|| *(WORD*)ItemId == ITEM(13, 324)
		|| *(WORD*)ItemId == ITEM(13, 325)
		|| *(WORD*)ItemId == ITEM(13, 326)
		|| *(WORD*)ItemId == ITEM(13, 327)
		|| *(WORD*)ItemId == ITEM(13, 328)
		|| *(WORD*)ItemId == ITEM(13, 329)
		|| *(WORD*)ItemId == ITEM(13, 330)
		|| *(WORD*)ItemId == ITEM(13, 331)
		|| *(WORD*)ItemId == ITEM(13, 332)
		|| *(WORD*)ItemId == ITEM(13, 333)
		|| *(WORD*)ItemId == ITEM(13, 334)
		|| *(WORD*)ItemId == ITEM(13, 335)
		|| *(WORD*)ItemId == ITEM(13, 336)
		|| *(WORD*)ItemId == ITEM(13, 337)
		|| *(WORD*)ItemId == ITEM(13, 338)
		|| *(WORD*)ItemId == ITEM(13, 339)
		|| *(WORD*)ItemId == ITEM(13, 340)
		|| *(WORD*)ItemId == ITEM(13, 341)
		|| *(WORD*)ItemId == ITEM(13, 342)
		|| *(WORD*)ItemId == ITEM(13, 343)
		|| *(WORD*)ItemId == ITEM(13, 344)
		|| *(WORD*)ItemId == ITEM(13, 345)
		|| *(WORD*)ItemId == ITEM(13, 346)
		|| *(WORD*)ItemId == ITEM(13, 347)
		|| *(WORD*)ItemId == ITEM(13, 348)
		|| *(WORD*)ItemId == ITEM(13, 349)
		|| *(WORD*)ItemId == ITEM(13, 350)
		|| *(WORD*)ItemId == ITEM(13, 351)
		|| *(WORD*)ItemId == ITEM(13, 352)
		|| *(WORD*)ItemId == ITEM(13, 353)
		|| *(WORD*)ItemId == ITEM(13, 354)
		|| *(WORD*)ItemId == ITEM(13, 355)
		|| *(WORD*)ItemId == ITEM(13, 356)
		|| *(WORD*)ItemId == ITEM(13, 357)
		|| *(WORD*)ItemId == ITEM(13, 358)
		|| *(WORD*)ItemId == ITEM(13, 359)
		|| *(WORD*)ItemId == ITEM(13, 360)
		|| *(WORD*)ItemId == ITEM(13, 361)
		|| *(WORD*)ItemId == ITEM(13, 362)
		|| *(WORD*)ItemId == ITEM(13, 363)
		|| *(WORD*)ItemId == ITEM(13, 364)
		|| *(WORD*)ItemId == ITEM(13, 365)
		|| *(WORD*)ItemId == ITEM(13, 366)
		|| *(WORD*)ItemId == ITEM(13, 367)
		|| *(WORD*)ItemId == ITEM(13, 368)
		|| *(WORD*)ItemId == ITEM(13, 369)
		|| *(WORD*)ItemId == ITEM(13, 370)
		|| *(WORD*)ItemId == ITEM(13, 371)
		|| *(WORD*)ItemId == ITEM(13, 372)
		|| *(WORD*)ItemId == ITEM(13, 373)
		|| *(WORD*)ItemId == ITEM(13, 374)
		|| *(WORD*)ItemId == ITEM(13, 375)
		|| *(WORD*)ItemId == ITEM(13, 376)
		|| *(WORD*)ItemId == ITEM(13, 377)
		|| *(WORD*)ItemId == ITEM(13, 378)
		|| *(WORD*)ItemId == ITEM(13, 379)
		|| *(WORD*)ItemId == ITEM(13, 380)
		|| *(WORD*)ItemId == ITEM(13, 381)
		|| *(WORD*)ItemId == ITEM(13, 382)
		|| *(WORD*)ItemId == ITEM(13, 383)
		|| *(WORD*)ItemId == ITEM(13, 384)
		|| *(WORD*)ItemId == ITEM(13, 385)
		|| *(WORD*)ItemId == ITEM(13, 386)
		|| *(WORD*)ItemId == ITEM(13, 387)
		|| *(WORD*)ItemId == ITEM(13, 388)
		|| *(WORD*)ItemId == ITEM(13, 389)
		|| *(WORD*)ItemId == ITEM(13, 390)
		|| *(WORD*)ItemId == ITEM(13, 391)
		|| *(WORD*)ItemId == ITEM(13, 392)
		|| *(WORD*)ItemId == ITEM(13, 393)
		|| *(WORD*)ItemId == ITEM(13, 394)
		|| *(WORD*)ItemId == ITEM(13, 395)
		|| *(WORD*)ItemId == ITEM(13, 396)
		|| *(WORD*)ItemId == ITEM(13, 397)
		|| *(WORD*)ItemId == ITEM(13, 398)
		|| *(WORD*)ItemId == ITEM(13, 399)
		|| *(WORD*)ItemId == ITEM(13, 400)
		|| *(WORD*)ItemId == ITEM(13, 401)
		|| *(WORD*)ItemId == ITEM(13, 402)
		|| *(WORD*)ItemId == ITEM(13, 403)
		|| *(WORD*)ItemId == ITEM(13, 404)
		|| *(WORD*)ItemId == ITEM(13, 405)
		|| *(WORD*)ItemId == ITEM(13, 406)
		|| *(WORD*)ItemId == ITEM(13, 407)
		|| *(WORD*)ItemId == ITEM(13, 408)
		|| *(WORD*)ItemId == ITEM(13, 409)
		|| *(WORD*)ItemId == ITEM(13, 410)
		|| *(WORD*)ItemId == ITEM(12, 189)
		|| *(WORD*)ItemId == ITEM(12, 194)
		|| *(WORD*)ItemId == ITEM(12, 220)
		|| *(WORD*)ItemId == ITEM(12, 221);
	else
        Result = 0;
    return Result;
}
void gObjCreatePetExHook()
{
	SetOp((LPVOID)0x00836481,(LPVOID)ResetPetPreviewEx,ASM::CALL);
	SetOp((LPVOID)0x007DD304,(LPVOID)gObjCreatePetEx,ASM::CALL);
	SetOp((LPVOID)0x00833B08,(LPVOID)gObjCreatePetEx,ASM::CALL);
}
/*
void gObjCreatePetExHook()
{
	SetOp((LPVOID)0x00836331,(LPVOID)ResetPetPreviewEx,ASM::CALL);
	SetOp((LPVOID)0x007DD1B4,(LPVOID)gObjCreatePetEx,ASM::CALL);
	SetOp((LPVOID)0x008339B8,(LPVOID)gObjCreatePetEx,ASM::CALL);
}
*/