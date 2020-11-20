#pragma once

#define MAX_CUSTOM_GLOVES	100

struct CUSTOM_RF_GLOVES
{
	int Index;
	int ItemIndex;
	char ModelName[32];
	int TextureLeftIndex;
	char TextureLeftName[32];
	int TextureRightIndex;
	char TextureRightName[32];
};

class cCustomGloves
{
public:
	cCustomGloves();
	virtual ~cCustomGloves();
	void Init();
	void Load(CUSTOM_RF_GLOVES* info);
	void SetInfo(CUSTOM_RF_GLOVES info);
	CUSTOM_RF_GLOVES* GetInfoByID(int index);
	void AssocGloves(char* This);
	bool CheckGloves(int ItemID);
public:
	CUSTOM_RF_GLOVES m_CustomGlovesInfo[MAX_CUSTOM_GLOVES];
}; extern cCustomGloves gCustomGloves;