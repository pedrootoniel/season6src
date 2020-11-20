#pragma once
// ----------------------------------------------------------------------------------------------

struct LoadMap
{
public:
	LoadMap();
	virtual ~LoadMap();
	void Load();
	static int Mapname(signed int a1);

};
extern LoadMap gLoadMap;
// ----------------------------------------------------------------------------------------------