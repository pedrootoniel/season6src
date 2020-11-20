#pragma once

#include "Object.h"
typedef unsigned char byte;
#define PetWhiteTiger	0x1833
#define PetHullWolf		0x1834
#define PetBeast		0x1835

class NewPets
{
public:
	void			Load();
	static int		GetFenrirSkillColor(ObjectPreview * gPreview);
};
extern NewPets gNewPets;