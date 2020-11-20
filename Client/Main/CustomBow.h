#pragma once
#ifdef NOLOAD
#define iBowAddSkillEffect 0x0074A128
#define iCrossAddSkillEffect 0x00749DCC
#define iBowAddInventoryPos 0x005CC8E4
#define iBowAddPlayerDimension 0x00566178
class CCustomBow
{
public:
	CCustomBow();
	virtual ~CCustomBow();
void Load();
};
extern CCustomBow gCustomBow;
#endif