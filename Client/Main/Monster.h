#pragma once


class Monster
{
public:
	Monster();
	virtual ~Monster();

	void			Load();
	static void		LoadMonsterBMD(signed int ModelID, char* a2, char* a3, signed int a4);
	static void		LoadMonsterTexture(signed int ModelID, char* a2, int a3, int a4);
	static int		ShowMonster(int MonsterID, int a2, int a3, int a4);
	static void		SetMainAttribute(int ObjectPointer, signed int MonsterID);
	static void		NPCChat(int a1, int a2);
	static int		LoadNpcModel(int a1);

};
extern Monster gMonster;