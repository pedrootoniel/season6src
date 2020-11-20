#include "stdafx.h"
#include "Pet.h"
#include "Import.h"
#include "User.h"
#include "PetProtocol.h"
#include "TMemory.h"
#include "Fenrir.h"
#include "Protect.h"
// ----------------------------------------------------------------------------------------------

CustomPet gCustomPet;

CustomPet::CustomPet() //OK
{
	this->PetTickCount = 0;
}

CustomPet::~CustomPet()
{

}

char CustomPet::PetHPBar(int a1, int a2)
{
	lpViewObj Object = &*(ObjectPreview*)oUserPreviewStruct;

	char result;
	char PetName[255];
	int PetHP;

	if ((Object->PetSlot < 7827 || Object->PetSlot > 7831)
		&& Object->PetSlot != 7891
		&& Object->PetSlot != 7892
		&& Object->PetSlot != 7894
		&& Object->PetSlot != 7907
		&& Object->PetSlot != 7933
		&& Object->PetSlot != 7950
		&& Object->PetSlot != 7864
		&& (Object->PetSlot < ITEM2(13, 147) || Object->PetSlot > ITEM2(13, 410)))
	{
		result = 0;
	}
	else
	{
		memset(&PetHP, 0, 255);
		PetName[0] = 0;
		switch (Object->PetSlot)
		{
		case 7827:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 353));
			break;
		case 7828:
			wsprintf(PetName, (char *)oUserTextObject + 84 * (*(WORD *)(oUserPreviewStruct + 556) - 1171));
			break;
		case 7829:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 355));
			break;
		case 7830:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 354));
			break;
		case 7831:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 1187));
			break;
		case 7864:
			wsprintf(PetName, pGetTextLine_(pTextLineThis, 1916));
			break;
		case 7891:
			wsprintf(PetName, (char *)(oUserTextObject + 564480));
			break;
		case 7892:
			wsprintf(PetName, (char *)(oUserTextObject + 564564));
			break;
		case 7894:
			wsprintf(PetName, (char *)(oUserTextObject + 564732));
			break;
		case 7907:
			wsprintf(PetName, (char *)(oUserTextObject + 565824));
			break;
		case 7933:
			wsprintf(PetName, (char *)(oUserTextObject + 568008));
			break;
		case 7950:
			wsprintf(PetName, (char *)(oUserTextObject + 569436));
			break;
		default:
			wsprintf(PetName, (char *)oUserTextObject + 84 * (*(WORD *)(oUserPreviewStruct + 556) - 1171));
			break;
		}

		PetHP = *(BYTE*)(oUserObjectStruct_ + 5550);
		sub_7DFA60(1, 50, (int)&PetName, PetHP, 255, 0);
		result = 1;
	}

	return result;
}

bool IsCharacterMove(int a1)
{
	//if ((*(WORD *)(*(DWORD *)(a1 + 472) + 18) >= 15 && *(WORD *)(*(DWORD *)(a1 + 472) + 18) <= 37))
	//{
	//	return true;
	//}
	//return false;

	if ((*(WORD *)(*(DWORD *)(a1 + 472) + 18) >= 15
		&& *(WORD *)(*(DWORD *)(a1 + 472) + 18) <= 37)
		|| *(WORD *)(*(DWORD *)(a1 + 472) + 18) == 74
		|| *(WORD *)(*(DWORD *)(a1 + 472) + 18) == 75
		|| *(WORD *)(*(DWORD *)(a1 + 472) + 18) == 259
		|| *(WORD *)(*(DWORD *)(a1 + 472) + 18) == 260)
	{
		return true;
	}
	return false;
}

void CustomPet::PetFollowCharacter(int a1, float MaxPos)
{
	float v22;
	vec3_t MUFLOAT;
	vec3_t PetPos;
	vec3_t OwnerPos;
	vec3_t CurrentPos;
	int LootPosition = 1000;

	OwnerPos[0] = *(float *)(*(DWORD *)(a1 + 472) + 252);
	OwnerPos[1] = *(float *)(*(DWORD *)(a1 + 472) + 256);
	OwnerPos[2] = *(float *)(*(DWORD *)(a1 + 472) + 260);

	PetPos[0] = OwnerPos[0] - *(float *)(a1 + 252);
	PetPos[1] = OwnerPos[1] - *(float *)(a1 + 256);
	PetPos[2] = OwnerPos[2] - *(float *)(a1 + 260);

	CurrentPos[0] = *(float *)(a1 + 252);
	CurrentPos[1] = *(float *)(a1 + 256);
	CurrentPos[2] = *(float *)(a1 + 260);
	
	float PetMapPos = PetPos[0] * PetPos[0] + PetPos[1] * PetPos[1];

	float diff1 = ((OwnerPos[0] > CurrentPos[0]) ? OwnerPos[0] - CurrentPos[0] : CurrentPos[0] - OwnerPos[0]);
	float diff2 = ((OwnerPos[1] > CurrentPos[1]) ? OwnerPos[1] - CurrentPos[1] : CurrentPos[1] - OwnerPos[1]);

	float angle = atan(diff2 / diff1) * 180 / PI;
	float angle2 = atan2(diff1, diff2) * 180 / PI; //

	if (PetMapPos >= MaxPos * MaxPos )
	{
		float speed;
		if (PetMapPos >= (MaxPos * 2) * (MaxPos * 2))
		{
			speed = 14.0f;
			speed += 1.0f;
			*(float *)(a1 + 120) = 0.89000002f;
		}
		else if (PetMapPos >= (MaxPos + (MaxPos / 2)) * (MaxPos + (MaxPos / 2)))
		{
			speed = 13.0f;
			*(float *)(a1 + 120) = 0.69000002f;
		}
		else
		{
			speed = 10.0f;
			*(float *)(a1 + 120) = 0.40000001f;
		}

		double MoveX = speed *(cos(angle * PI / 180));
		double MoveY = speed *(sin(angle * PI / 180));

		if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 252) += (float)MoveX;
			*(float *)(a1 + 256) += (float)MoveY;
			*(float *)(a1 + 272) = 180;
			*(float *)(a1 + 272) -= angle2;
		}
		else if (CurrentPos[0] < OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 252) += (float)MoveX;
			*(float *)(a1 + 256) -= (float)MoveY;
			*(float *)(a1 + 272) = angle2;
		}
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] > OwnerPos[1])
		{
			*(float *)(a1 + 252) -= (float)MoveX;
			*(float *)(a1 + 256) -= (float)MoveY;
			*(float *)(a1 + 272) = 360;
			*(float *)(a1 + 272) -= angle2;
		}
		else if (CurrentPos[0] > OwnerPos[0] && CurrentPos[1] < OwnerPos[1])
		{
			*(float *)(a1 + 252) -= (float)MoveX;
			*(float *)(a1 + 256) += (float)MoveY;
			*(float *)(a1 + 272) = 180;
			*(float *)(a1 + 272) += angle2;
		}
		//else
		//{
		//	*(float *)(a1 + 252) += abs(MoveX);
		//	*(float *)(a1 + 256) += abs(MoveY);
		//	*(float *)(a1 + 272) = *(float *)(*(DWORD *)(a1 + 472) + 272);
		//}
		*(WORD*)(a1 + 18) = 2;
	}
	else if (PetMapPos < 70 * 70)
	{
		if ((*(WORD *)(*(DWORD *)(a1 + 472) + 18) < 15 || *(WORD *)(*(DWORD *)(a1 + 472) + 18) > 37))
		{
			*(WORD*)(a1 + 18) = 2;
			sub_959CE0(a1 + 264, a1 + 372);
			sub_95A1E0(a1 + 168, a1 + 372, MUFLOAT);
			*(float *)(a1 + 252) = *(float *)(a1 + 252) + MUFLOAT[0];
			*(float *)(a1 + 256) = *(float *)(a1 + 256) + MUFLOAT[1];
			//*(float *)(a1 + 260) = *(float *)(a1 + 260);
		}

	}
	else
	{
		if (GetTickCount() <= gCustomPet.PetTickCount + 800)
		{
			*(WORD*)(a1 + 18) = 1;
		}
		else if (GetTickCount() <= gCustomPet.PetTickCount + 12000)
		{
			*(WORD*)(a1 + 18) = 0;
		}
		else
		{
			gCustomPet.PetTickCount = GetTickCount();
		}
	}

	if (PetMapPos >= LootPosition * LootPosition)
	{
		if (*(float *)(a1 + 252) < *(float *)(*(DWORD *)(a1 + 472) + 252))
			*(float *)(a1 + 252) = *(float *)(a1 + 252) + PetPos[0] + rand() % 360;
		if (*(float *)(a1 + 252) > *(float *)(*(DWORD *)(a1 + 472) + 252))
			*(float *)(a1 + 252) = *(float *)(a1 + 252) + PetPos[0] - rand() % 360;

		if (*(float *)(a1 + 256) < *(float *)(*(DWORD *)(a1 + 472) + 256))
			*(float *)(a1 + 256) = *(float *)(a1 + 256) + PetPos[1] + rand() % 360;
		if (*(float *)(a1 + 256) > *(float *)(*(DWORD *)(a1 + 472) + 256))
			*(float *)(a1 + 256) = *(float *)(a1 + 256) + PetPos[1] - rand() % 360;
	}

	*(float *)(a1 + 260) = *(float *)(*(DWORD *)(a1 + 472) + 260);

	if (!(rand() % 100))
	{
		if (PetMapPos < MaxPos * MaxPos)
		{
			v22 = -(float)(rand() % 64 + 16) * 0.1000000014901161f;
			*(float *)(a1 + 272) = (float)(rand() % 360);
		}
		else
		{
			v22 = -(float)(rand() % 64 + 128) * 0.1000000014901161f;
		}
		*(float *)(a1 + 168) = 0.0f;
		*(float *)(a1 + 172) = v22;
		*(float *)(a1 + 176) = (float)(rand() % 64 - 32) * 0.1000000014901161f;
	}

	if (*(float *)(a1 + 260) < *(float *)(*(DWORD *)(a1 + 472) + 260) + 100.0f)
		*(float *)(a1 + 176) = *(float *)(a1 + 176) + 1.5f;
	if (*(float *)(a1 + 260) > *(float *)(*(DWORD *)(a1 + 472) + 260) + 200.0f)
		*(float *)(a1 + 176) = *(float *)(a1 + 176) - 1.5f;
}

void CustomPet::PetsMovement(int a1, char a2)
{
	//float ColorRandom[3];
	//MU3Float BMD;
	//MU3Float BMD2;
	//MU3Float StaticBone;
	//vec3_t Color;
	//vec3_t ColorRandom;

	//Vector(1.0f, 1.0f, 1.0f, Color);
	//Vector(((float)(rand() % 100) / 100), ((float)(rand() % 100) / 100), ((float)(rand() % 100) / 100), ColorRandom);

	if (*(BYTE *)(a1 + 4))
	{
		lpViewObj lpObj = &*(ObjectPreview*)*(DWORD*)0x07BC4F04;
		//ObjectModelPet * lpPet = &*(ObjectModelPet*)a1;

		if (*(DWORD*)0xE609E8 == 5
			&& (*(DWORD*)0xE61E18 < 65 || *(DWORD*)0xE61E18 > 68)
			&& (!*(BYTE *)(*(DWORD *)(a1 + 472) + 4) || *(BYTE *)(*(DWORD *)(a1 + 472) + 24) != 1))
		{
			*(BYTE *)(a1 + 4) = 0;
			sub_501790(a1, a2);
			return;
		}
		// sub_541460(a1);
		// v3 = *(float *)(a1 + 48);
		// v68 = sub_969C50(sub_4CDA10(a1),LODWORD(v3));
		// if (!v68)
		//	return sub_501790(a1, a2);

		DWORD SkinID = *(DWORD *)(a1 + 48);
		DWORD Model = sub_969C50(sub_4CDA10(), SLODWORD(SkinID));

		if (Model)
		{
			//BMD.X = (float)(rand() % 64 - 32) + *(float *)(a1 + 252);
			//BMD.Y = (float)(rand() % 64 - 32) + *(float *)(a1 + 256);
			//BMD.Z = (float)(rand() % 32 - 16) + *(float *)(a1 + 260);
			//BMD2.X = *(float*)(a1 + 264);
			//BMD2.Y = *(float*)(a1 + 268);
			//BMD2.Z = *(float*)(a1 + 270);
			//StaticBone.X = *(float*)(a1 + 252);
			//StaticBone.Y = *(float*)(a1 + 256);
			//StaticBone.Z = *(float*)(a1 + 260);
			//pCustomEffGet(&Model, (int)&*(DWORD*)0x7BC08A0 + 48 * m, Bone, Bone2, 1);
			//switch (SkinID)
			//{
			//case ITEM2(13, 147): //Nymph
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	sub_74CD30(32260, (int)&BMD, a1 + 264, Color, 11, 0.5f, 0);
			//	*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 50.0f;
			//	break;
			//case ITEM2(13, 148): //Pumpy
			//	CustomPet::PetsMonkeyStyle(a1, 200, 1000);
			//	Vector(1.0f, 0.4f, 0.4f, Color);
			//	sub_74CD30(32291, (int)&BMD, a1 + 264, Color, 0, 0.5f, 0);
			//	break;
			//case ITEM2(13, 149): //Branch
			//	CustomPet::PetsMonkeyStyle(a1, 200, 1000);
			//	break;
			//case ITEM2(13, 150): //Buserker Monkey
			//	CustomPet::PetsMonkeyStyle(a1, 200, 1000);
			//	break;
			//case ITEM2(13, 151): //Canifle
			//	CustomPet::PetsMonkeyStyle(a1, 150, 1000);
			//	Vector(0.6f, 0.2f, 0.7f, Color);
			//	StaticBone.Z = StaticBone.Z + 130.0f;
			//	BMD.Z = BMD.Z + 130.0f;
			//	sub_771310(32002, (int)&StaticBone, 3.0f, Color, a1 + 264, 0, 0);
			//	sub_74CD30(0x7D71, (int)&BMD, a1 + 264, Color, 2, 0.5f, 0);
			//	break;
			//case ITEM2(13, 152): //Choco Cookie
			//	CustomPet::PetsFlyJumpStyle(a1, 150, 1000);
			//	sub_74CD30(0x7D65, (int)&BMD, a1 + 264, Color, 3, 0.3f, 0);
			//	*(WORD*)(a1 + 18) = 2;
			//	break;
			//case ITEM2(13, 153): //Cooling Girl
			//	CustomPet::PetsFlyStyle(a1, 150, 1000);
			//	sub_74CD30(32049, (int)&BMD, a1 + 264, Color, 11, 0.3f, 0);
			//	sub_74CD30(32101, (int)&BMD, a1 + 264, Color, 0, 0.3f, 0);
			//	sub_74CD30(0x7D71, (int)&BMD, a1 + 264, ColorRandom, 4, 0.3f, 0);
			//	*(WORD*)(a1 + 18) = 2;
			//	break;
			//case ITEM2(13, 154): //Dj Monkey
			//	CustomPet::PetsMonkeyStyle(a1, 200, 1000);
			//	//sub_544E60((LPVOID)Model, Bone, a1 + 264, 1, 0);
			//	//sub_771310_(32002, Bone, 3.0f, Color, a1 + 264, 0, 0);
			//	break;
			//case ITEM2(13, 155): //Dragon
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	BMD.Z = BMD.Z + 70.0f;
			//	Vector(0.95f, 0.84f, 0.49f, Color);
			//	if (*(WORD*)(a1 + 18) == 2)
			//		sub_74CD30(32101, (int)&BMD, a1 + 264, Color, 0, 0.3f, 0);
			//	break;
			//case ITEM2(13, 156): //Reyner
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	BMD.Z = BMD.Z + 50.0f;
			//	Vector(0.7f, 0.2f, 1.0f, Color);
			//	sub_74CD30(32049, (int)&BMD, a1 + 264, Color, 11, 0.5f, 0);
			//	BMD.Z = BMD.Z + 70.0f;
			//	sub_74CD30(0x7D71, (int)&BMD, a1 + 264, Color, 5, 1.0f, 0); //Star
			//	*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 70.0f;
			//	break;
			//case ITEM2(13, 157): //Ghost
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	if (rand() % 25 < 1)
			//		sub_74CD30(32279, (int)&BMD, a1 + 264, Color, 3, 0.3f, 0);
			//	sub_74CD30(32101, (int)&BMD, a1 + 264, Color, 0, 0.3f, 0);
			//	*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 100.0f;
			//	*(DWORD *)(a1 + 68) = 1;
			//	break;
			//case ITEM2(13, 158): //Gigantes
			//	CustomPet::PetsMonkeyStyle(a1, 200, 1000);
			//	sub_74CD30(0x7D83, (int)&BMD, a1 + 264, ColorRandom, 3, 0.3f, 0);
			//	break;
			//case ITEM2(13, 159): //Ginkgo
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	sub_74CD30(32049, (int)&BMD, a1 + 264, Color, 11, 0.3f, 0);
			//	sub_74CD30(0x7d71, (int)&BMD, a1 + 264, Color, 4, 0.5f, 0);
			//	//sub_74CD30(0x7D71, (int)&BMD, a1 + 264, ColorRandom, 4, 0.3f, 0);
			//	*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 100.0f;
			//	break;
			//case ITEM2(13, 160): //Satan
			//	//CustomPet::PetsFlyJumpStyle(a1, 200, 1000);
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	sub_74CD30(0x7D71, (int)&BMD, a1 + 264, ColorRandom, 4, 0.3f, 0);
			//	BMD.Z += 30.0f;
			//	sub_74CD30(0x7d7E, (int)&BMD, a1 + 264, Color, 1, 0.5f, 0);
			//	//*(WORD*)(a1 + 18) = 2;
			//	break;
			//case ITEM2(13, 161): //Lucky Rabbit
			//	CustomPet::PetsMonkeyStyle(a1, 200, 1000);
			//	sub_74CD30(0x7D71, (int)&BMD, a1 + 264, ColorRandom, 4, 0.3f, 0);
			//	BMD.Z += 30.0f;
			//	sub_74CD30(0x7d7E, (int)&BMD, a1 + 264, Color, 1, 0.5f, 0);
			//	StaticBone.Z = StaticBone.Z + 70.0f;
			//	pPlayStaticEffect(32002, (DWORD*)&StaticBone, 2.0f, Color, a1 + 264, 0, 0);
			//	break;
			//case ITEM2(13, 242): //Lure
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	//sub_74CD30(0x7E36, (int)&BMD, a1 + 264, ColorRandom, 2, 0.3f, 0);
			//	break;
			//case ITEM2(13, 243): //Rocka
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	sub_74CD30(32396, (int)&BMD, a1 + 264, ColorRandom, 2, 0.3f, 0);
			//	break;
			//case ITEM2(13, 244): //Mapple
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	Vector(1.0f, 0.2f, 0.2f, Color);
			//	sub_74CD30(32049, (int)&BMD, a1 + 264, Color, 11, 0.3f, 0);
			//	sub_74CD30(0x7d71, (int)&BMD, a1 + 264, Color, 4, 0.5f, 0);
			//	*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 100.0f;
			//	break;
			//case ITEM2(13, 245): //Mutantion
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	if (*(WORD*)(a1 + 18) == 2)
			//		sub_74CD30(32283, (int)&BMD, a1 + 264, ColorRandom, 5, *(float *)(a1 + 96), 0);
			//	break;
			//case ITEM2(13, 246): //Pinochino
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	BMD.Z = BMD.Z + 50.0f;
			//	if (rand() % 15 < 2)
			//		pCreateEffect(388, (DWORD*)&BMD, a1 + 264, Color, 1, a1 + 262, -1, 0, 0, 0, 0.0f, -1);
			//	break;
			//case ITEM2(13, 247): //Polar Bear
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	break;
			//case ITEM2(13, 248): //Polaris
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	BMD.Z = BMD.Z + 50.0f;
			//	Vector(1.0f, 0.3f, 0.3f, Color);
			//	sub_74CD30(0x7D71, (int)&BMD, a1 + 264, Color, 4, 0.4f, 0);
			//	break;
			//case ITEM2(13, 249): //Present
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	sub_74CD30(0x7D71, (int)&BMD, a1 + 264, Color, 4, 0.3f, 0);
			//	if (*(WORD*)(a1 + 18) == 2)
			//		sub_74CD30(0x7D83, (int)&BMD, a1 + 264, Color, 3, 0.3f, 0);
			//	break;
			//case ITEM2(13, 250): //Song Rabbit
			//	CustomPet::PetsMonkeyStyle(a1, 200, 1000);
			//	sub_74CD30(0x7D71, (int)&BMD, a1 + 264, ColorRandom, 4, 0.5f, 0);
			//	BMD.Z = BMD.Z + 40.0f;
			//	sub_74CD30(0x7d7E, (int)&BMD, a1 + 264, Color, 1, 0.5f, 0);
			//	Vector(1.0f, 0.3f, 0.3f, Color);
			//	StaticBone.Z = StaticBone.Z + 70.0f;
			//	sub_771310(32002, (int)&StaticBone, 3.0f, Color, (int)&BMD2, 0, 0);
			//	break;
			//case ITEM2(13, 251): //Surfing Girl
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	sub_74CD30(0x7d71, (int)&BMD, a1 + 264, ColorRandom, 1, 0.2f, 0);
			//	if (*(WORD*)(a1 + 18) == 2)
			//		sub_74CD30(32291, (int)&BMD, a1 + 264, Color, 5, 0.4f, 0); //Rain
			//	*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 100.0f;
			//	break;
			//case ITEM2(13, 252): //Behemoth
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	StaticBone.Z = StaticBone.Z + 80.0f;
			//	BMD.Z = BMD.Z + 70.0f;
			//	Vector(1.0f, 0.2f, 0.2f, Color);
			//	if (*(WORD*)(a1 + 18) == 2)
			//		sub_74CD30(32101, (int)&BMD, a1 + 264, Color, 0, 0.3f, 0);
			//
			//	sub_74CD30(0x7d71, (int)&BMD, a1 + 264, Color, 1, 0.3f, 0);
			//	sub_771310(32002, (int)&StaticBone, 1.5, Color, (int)&BMD2, 0, 0);
			//	*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 50.0f;
			//	break;
			//case ITEM2(13, 253): //Witch
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	BMD.Z += 30.0f;
			//	sub_74CD30(0x7d7E, (int)&BMD, a1 + 264, Color, 1, 0.5f, 0);
			//	*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 100.0f;
			//	if (*(WORD*)(a1 + 18) == 2)
			//		sub_74CD30(32101, (int)&BMD, a1 + 264, Color, 0, 0.2f, 0);
			//	break;
			//case ITEM2(13, 254): //Alcamo
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	StaticBone.Z = StaticBone.Z + 80.0f;
			//	BMD.Z = BMD.Z + 70.0f;
			//	Vector(0.3f, 0.3f, 1.0f, Color);
			//	if (*(WORD*)(a1 + 18) == 2)
			//		sub_74CD30(32101, (int)&BMD, a1 + 264, Color, 0, 0.2f, 0);
			//
			//	sub_74CD30(0x7d71, (int)&BMD, a1 + 264, Color, 1, 0.3f, 0);
			//	sub_771310(32002, (int)&StaticBone, 1.5, Color, (int)&BMD2, 0, 0);
			//	break;
			//case ITEM2(13, 255): //Tibetton
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	BMD.Z = BMD.Z + 50.0f;
			//	if (rand() % 15 < 2)
			//		pCreateEffect(388, (DWORD*)&BMD, a1 + 264, Color, 1, a1 + 262, -1, 0, 0, 0, 0.0f, -1);
			//	break;
			//case ITEM2(13, 256): //Splinter
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	Vector(1.0f, 0.3f, 0.3f, Color);
			//	StaticBone.Z = StaticBone.Z + 50.0f;
			//	pPlayStaticEffect(32002, (DWORD*)&StaticBone, 3.0f, Color, a1 + 264, 0, 0);
			//	if (*(WORD*)(a1 + 18) == 2)
			//		sub_74CD30(32283, (int)&BMD, a1 + 264, ColorRandom, 5, *(float *)(a1 + 96), 0);
			//	break;
			//case ITEM2(13, 257): //Xmastree Evo
			//	CustomPet::PetsMonkeyStyle(a1, 180, 1000);
			//	sub_74CD30(0x7D71, (int)&BMD, a1 + 264, ColorRandom, 4, 0.3f, 0);
			//	sub_74CD30(0x7D83, (int)&BMD, a1 + 264, ColorRandom, 3, 0.3f, 0);
			//	break;
			//case 0x1833:
			//case 0x1834:
			//case 0x1835:
			//	if (!lpObj->InSafeZone)
			//	{
			//		Vector(1.0f, 1.0f, 0.2f, Color);
			//		pCreateEffect(388, (DWORD*)&BMD, a1 + 264, Color, 0, a1 + 262, -1, 0, 10.0f, 0, 0.0f, -1);
			//		if (*(WORD*)(a1 + 18) == 1 || *(WORD*)(a1 + 18) == 2)
			//			if (rand() % 15 < 2)
			//				sub_6D9070(32279, (int)&BMD, a1 + 264, Color, 1, 0, -1, 0, 0, 0, 0.0f, -1);
			//		//lpObj->m_Model.Scale = 1.0f;
			//
			//	}
			//	break;
			//}
			if ((SkinID >= ITEM2(13, 147) && SkinID <= ITEM2(13, 410)))
			{
				gCustomPet.PetFollowCharacter(a1, 150);
				switch (SkinID)
				{
				case ITEM2(13, 226): //King
				case ITEM2(13, 281): //Prince
				case ITEM2(13, 388): //Prince =)) lazy
					*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 40.0f;
					break;
				case ITEM2(13, 214): //Hawk
				case ITEM2(13, 215): //Hawk Evo
				case ITEM2(13, 174): //CherryBlossom
				case ITEM2(13, 175): //CherryBlossom Evo
				case ITEM2(13, 178): //Chrysanthemum
				case ITEM2(13, 179): //Chrysanthemum Evo
				case ITEM2(13, 200): //Ghost
					*(float*)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 30.0f;
					break;
				case ITEM2(13, 201): //Ghost Evo
					*(DWORD *)(a1 + 68) = 1;
					*(float *)(a1 + 260) = *(float*)(*(DWORD*)(a1 + 472) + 260) + 30.0f;
					break;
				}
			}
		}
	}

	//sub_501790(a1, a2);
	((void(*)(int, char)) 0x501790)(a1, a2);
}

void CustomPet::PreviewCharSet(int ObjectIndex, BYTE * CharSet, lpViewObj Object, int Mode)
{
	pPreviewCharSet(ObjectIndex, CharSet, Object, Mode);

	lpViewObj lpObj;

	if (Object == 0)
	{
		lpObj = &*(lpViewObj)pGetPreviewStruct(pPreviewThis(), ObjectIndex);
	}
	else
	{
		lpObj = Object;
	}

	//
	////gCustomPet.CharSetView = CustomPets;
	//
	//if (CustomPets > 0 && CustomPets != 16 && CustomPets != 32 && CustomPets != 48 && CustomPets != 64 && CustomPets != 80 && CustomPets != 112)
	//{
	//	if (Mode)
	//	{
	//		*(BYTE *)(Mode + 4) = 0;
	//	}
	//	else
	//	{
	//		sub_5012D0((int)&lpObj->m_Model);
	//		sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
	//	}
	//
	//	lpObj->PetSlot = ITEM2(13, 147) + (CustomPets - 1);
	//
	//	if (Mode)
	//		sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
	//	else
	//		sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
	//}
		PMSG_NEW_CHARACTER_CHARSET_RECV* SelectCharSet = GetNewCharSetSelectCharacter(lpObj->Name);

		if (pPlayerState == 4)
		{
			if (SelectCharSet > 0)
			{
				BYTE sNewCharSet0 = SelectCharSet->PetCharSet[0] >> 1;
				BYTE sNewCharSet1 = SelectCharSet->PetCharSet[1] >> 1;
				BYTE sNewCharSet2 = SelectCharSet->PetCharSet[2] >> 1;
				BYTE sNewCharSet3 = SelectCharSet->PetCharSet[3] >> 1;

				if (sNewCharSet0 > 0 && sNewCharSet0 < 112)
				{
					if (Mode)
					{
						*(BYTE *)(Mode + 4) = 0;
					}
					else
					{
						sub_5012D0((int)&lpObj->m_Model);
						sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
					}

					lpObj->PetSlot = ITEM2(13, 147) + (sNewCharSet0 - 1);

					if (Mode)
						sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
					else
						sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
				}

				if (sNewCharSet1 > 0 && sNewCharSet1 < 94)
				{
					if (Mode)
					{
						*(BYTE *)(Mode + 4) = 0;
					}
					else
					{
						sub_5012D0((int)&lpObj->m_Model);
						sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
					}

					lpObj->PetSlot = ITEM2(13, 258) + (sNewCharSet1 - 1);

					if (Mode)
						sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
					else
						sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
				}

				if (sNewCharSet2 > 0 && sNewCharSet2 < 100)
				{
					if (Mode)
					{
						*(BYTE *)(Mode + 4) = 0;
					}
					else
					{
						sub_5012D0((int)&lpObj->m_Model);
						sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
					}

					lpObj->PetSlot = ITEM2(13, 351) + (sNewCharSet2 - 1);

					if (Mode)
						sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
					else
						sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
				}

				if (sNewCharSet3 > 0 && sNewCharSet3 < 100)
				{
					if (Mode)
					{
						*(BYTE *)(Mode + 4) = 0;
					}
					else
					{
						sub_5012D0((int)&lpObj->m_Model);
						sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
					}

					lpObj->PetSlot = ITEM2(13, 451) + (sNewCharSet3 - 1);

					if (Mode)
						sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
					else
						sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
				}
			}
		}

		NEW_PET_STRUCT* lpCharSet = GetNewPetCharSet(lpObj->aIndex);

		if (lpCharSet > 0)
		{
			BYTE NewCharSet0 = lpCharSet->PetCharSet[0] >> 1;
			BYTE NewCharSet1 = lpCharSet->PetCharSet[1] >> 1;
			BYTE NewCharSet2 = lpCharSet->PetCharSet[2] >> 1;
			BYTE NewCharSet3 = lpCharSet->PetCharSet[3] >> 1;

			if (NewCharSet0 > 0 && NewCharSet0 < 112)
			{
				if (Mode)
				{
					*(BYTE *)(Mode + 4) = 0;
				}
				else
				{
					sub_5012D0((int)&lpObj->m_Model);
					sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
				}

				lpObj->PetSlot = ITEM2(13, 147) + (NewCharSet0 - 1);

				if (Mode)
					sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
				else
					sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			}

			if (NewCharSet1 > 0 && NewCharSet1 < 94)
			{
				if (Mode)
				{
					*(BYTE *)(Mode + 4) = 0;
				}
				else
				{
					sub_5012D0((int)&lpObj->m_Model);
					sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
				}

				lpObj->PetSlot = ITEM2(13, 258) + (NewCharSet1 - 1);

				if (Mode)
					sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
				else
					sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			}

			if (NewCharSet2 > 0 && NewCharSet2 < 100)
			{
				if (Mode)
				{
					*(BYTE *)(Mode + 4) = 0;
				}
				else
				{
					sub_5012D0((int)&lpObj->m_Model);
					sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
				}

				lpObj->PetSlot = ITEM2(13, 351) + (NewCharSet2 - 1);

				if (Mode)
					sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
				else
					sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			}

			if (NewCharSet3 > 0 && NewCharSet3 < 100)
			{
				if (Mode)
				{
					*(BYTE *)(Mode + 4) = 0;
				}
				else
				{
					sub_5012D0((int)&lpObj->m_Model);
					sub_9253D0(sub_4DB230(), (int)&lpObj->m_Model, (int)&lpObj->PetSlot);
				}

				lpObj->PetSlot = ITEM2(13, 451) + (NewCharSet3 - 1);

				if (Mode)
					sub_5013B0(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
				else
					sub_501700(lpObj->PetSlot, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			}
			
		}

	BYTE CustomPets = CharSet[15] >> 1;

	if (CharSet[11] & 1) // == 1 
	{
		lpObj->PetSlot = 7831;
		if (Mode)
			sub_5013B0(226, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
		else
			sub_501700(226, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
	}
	/*
	if ((CharSet[11] & 4) == 4)
	{
		lpObj->PetSlot = 7864;

		if ((CharSet[15] & 3) == 1 && (CharSet[16] & 3) == 0)
		{
			if (Mode)
				pPetCall1(384, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, Mode, 0);
			else
				pPetCall2(384, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, 0, 0);
			lpObj->PetExcellent = 1;
		}
		else if ((CharSet[15] & 3) == 2 && (CharSet[16] & 3) == 0)
		{
			if (Mode)
				pPetCall1(386, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, Mode, 0);
			else
				pPetCall2(386, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, 0, 0);
			lpObj->PetExcellent = 2;
		}
		else if ((CharSet[15] & 3) == 3 && (CharSet[16] & 3) == 0)
		{
			if (Mode)
				pPetCall1(387, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, Mode, 0);
			else
				pPetCall2(387, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, 0, 0);
			lpObj->PetExcellent = 4;
		}
		else if ((CharSet[15] & 3) == 1 && (CharSet[16] & 3) == 1)
		{
			if (Mode)
				pPetCall1(PetWhiteTiger, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, Mode, 0);
			else
				pPetCall2(PetWhiteTiger, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, 0, 0);
			lpObj->PetExcellent = 8;
		}
		else if ((CharSet[15] & 3) == 2 && (CharSet[16] & 3) == 1)
		{
			if (Mode)
				pPetCall1(PetHullWolf, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, Mode, 0);
			else
				pPetCall2(PetHullWolf, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, 0, 0);
			lpObj->PetExcellent = 16;
		}
		else if ((CharSet[15] & 3) == 3 && (CharSet[16] & 3) == 1)
		{
			if (Mode)
				pPetCall1(PetBeast, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, Mode, 0);
			else
				pPetCall2(PetBeast, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, 0, 0);
			lpObj->PetExcellent = 32;
		}
		else
		{
			if (Mode)
				pPetCall1(385, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, Mode, 0);
			else
				pPetCall2(385, ((DWORD)&lpObj->m_Model) + 252, (DWORD)&lpObj->m_Model, 0, 0);
			lpObj->PetExcellent = 0;
		}

	}
	*/
	if ((CharSet[11] & 4) == 4)
	{
		lpObj->PetSlot = 7864;
		BYTE v17 = CharSet[15] & 3;
		if (CharSet[16] & 1)
			v17 = 4;
		if (CustomPets == 122)
			v17 = 8;
		else if (CustomPets == 123)
			v17 = 16;
		else if (CustomPets == 124)
			v17 = 32;

		lpObj->PetExcellent = v17;

		switch (v17)
		{
		case 1:
			if (Mode)
				sub_5013B0(384, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(384, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			break;
		case 2:
			if (Mode)
				sub_5013B0(386, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(386, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			break;
		case 4:
			if (Mode)
				sub_5013B0(387, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(387, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			break;
		case 8:
			if (Mode)
				sub_5013B0(0x1833, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(0x1833, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			break;
		case 16:
			if (Mode)
				sub_5013B0(0x1834, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(0x1834, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			break;
		case 32:
			if (Mode)
				sub_5013B0(0x1835, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(0x1835, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			break;
		default:
			if (Mode)
				sub_5013B0(385, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, Mode, 0);
			else
				sub_501700(385, (int)&lpObj->m_Model + 252, (int)&lpObj->m_Model, 0, 0);
			break;
		}
	}
	
}

void CustomPet::RefreshViewPortItem(int a1)
{
	signed int v1; // ST14_4@1
	int result; // eax@1
	int v6; // [sp+Ch] [bp-14h]@2
	int v7; // [sp+10h] [bp-10h]@1
	int v8; // [sp+14h] [bp-Ch]@2
	BYTE v9; // [sp+1Dh] [bp-3h]@2
	BYTE v10; // [sp+1Eh] [bp-2h]@2
	BYTE v11; // [sp+1Fh] [bp-1h]@2

	v1 = sub_57D9A0(*(BYTE *)(a1 + 4) + (*(BYTE *)(a1 + 3) << 8));
	result = sub_96A4C0(sub_402BC0(), v1);
	v7 = result;
	if (result)
	{
		v6 = result + 776;
		v8 = sub_58AA80(a1 + 5);
		v11 = *(BYTE *)(a1 + 6) & 0xF;
		v10 = *(BYTE *)(a1 + 8) & 0x3F;
		v9 = *(BYTE *)(a1 + 9);
		switch ((signed int)*(BYTE *)(a1 + 6) >> 4)
		{
			if(gProtect.m_MainInfo.CustomItemPack == 0)
			{
		case 7:
			if (v8 == 0x1FFF)
			{
				if (*(WORD*)(v7 + 520) == ITEM2(12,189)
					|| *(WORD*)(v7 + 520) == ITEM2(12,194)
					//|| *(WORD*)(v7 + 520) == ITEM2(12,196)
					|| *(WORD*)(v7 + 520) == ITEM2(12,220)
					|| *(WORD*)(v7 + 520) == ITEM2(12,221)
					//|| *(WORD*)(v7 + 520) == ITEM2(12,222)
					)
				{
					sub_558630(v7, v6, 0);
				}
				*(WORD *)(v7 + 520) = -1;
			}
			else
			{
				*(WORD *)(v7 + 520) = v8 + 1171;
				*(BYTE *)(v7 + 522) = 0;
				if (*(WORD*)(v7 + 520) == ITEM2(12, 189)
					|| *(WORD*)(v7 + 520) == ITEM2(12, 194)
					//|| *(WORD*)(v7 + 520) == ITEM2(12, 196)
					|| *(WORD*)(v7 + 520) == ITEM2(12, 220)
					|| *(WORD*)(v7 + 520) == ITEM2(12, 221)
					//|| *(WORD*)(v7 + 520) == ITEM2(12, 222)
					)
				{
					sub_558630(v7, v6, 0);
				}
			}
			break;
			}
		case 8:
			if (v8 == 0x1FFF)
			{
				*(WORD *)(v7 + 556) = -1;
				sub_5012D0(v6);
				sub_9253D0(sub_4DB230(), v7, -1);
			}
			else
			{
				*(WORD *)(v7 + 556) = v8 + 1171;
				*(BYTE *)(v7 + 558) = 0;
				if (v8 >= ITEM(13, 147) && v8 <= ITEM(13, 410))
				{
					sub_501700(v8 + 1171, v6 + 252, v6, 0, 0);
				}
			}
			break;
		default:
			break;
		}
	}
	((void(*)(int))0x6411A0)(a1);
}

void CustomPet::Load()
{
	SetOp((LPVOID)0x0048E17D, CustomPet::PetsMovement, ASM::CALL);
	SetOp((LPVOID)0x00503756, CustomPet::PetsMovement, ASM::CALL);

	SetOp((LPVOID)0x007DF8BB, CustomPet::PetHPBar, ASM::CALL);
	
	SetOp((LPVOID)0x48FB8C, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x63D2D8, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x641189, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x641F42, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x642598, CustomPet::PreviewCharSet, ASM::CALL);
	SetOp((LPVOID)0x65EA2D, CustomPet::PreviewCharSet, ASM::CALL);
	

	SetOp((LPVOID)0x664267, CustomPet::RefreshViewPortItem, ASM::CALL);
}

