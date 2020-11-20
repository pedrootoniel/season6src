#include "stdafx.h"
#include "LuaExport.h"

LuaExport gLuaExport;

LuaExport::LuaExport()
{

}


LuaExport::~LuaExport()
{

}

void LuaExport::AddTable(lua_State * Lua)
{
	lua_register(Lua, "SetBkColor", this->LuaSetBkColor);
	lua_register(Lua, "SetTextColor", this->LuaSetTextColor);
	lua_register(Lua, "SetFont", this->LuaSetFont);
	/*lua_register(Lua, "ChatTargetSend", this->LuaChatTargetSend);
	lua_register(Lua, "LogAdd", this->LuaLogAdd);
	lua_register(Lua, "gObjTeleport", this->LuagObjTeleport);
	lua_register(Lua, "GCServerMsgStringSend", this->LuaGCServerMsgStringSend);
	lua_register(Lua, "FireCrackerOpen", this->LuaFireCrackerOpen);
	lua_register(Lua, "gObjCalDistance", this->LuagObjCalDistance);
	lua_register(Lua, "GCServerCmd", this->LuaGCServerCmd);
	lua_register(Lua, "gUserFindDevilSquareKeyEyes", this->LuagUserFindDevilSquareKeyEyes);
	lua_register(Lua, "gObjAddBuffEffect", this->LuagObjAddBuffEffect);
	lua_register(Lua, "GCReFillSend", this->LuaGCReFillSend);
	lua_register(Lua, "GCManaSend", this->LuaGCManaSend);
	lua_register(Lua, "gQeustNpcTeleport_TalkRefAdd", this->LuagQeustNpcTeleport_TalkRefAdd);
	lua_register(Lua, "gObjIsConnected", this->LuagObjIsConnected);
	lua_register(Lua, "gParty_GetPKPartyPenalty", this->LuagParty_GetPKPartyPenalty);
	lua_register(Lua, "gObjGuildMasterCapacityTest", this->LuagObjGuildMasterCapacityTest);
	lua_register(Lua, "gObjMonsterTopHitDamageUser", this->LuagObjMonsterTopHitDamageUser);
	lua_register(Lua, "CreateItem", this->LuaItemSerialCreateSend);
	lua_register(Lua, "MakeRandomSetItem", this->LuaMakeRandomSetItem);
	lua_register(Lua, "GetBagItemLevel", this->LuaGetBagItemLevel);
	lua_register(Lua, "AddItemBag", this->LuaAddItemBag);
	lua_register(Lua, "IsItem", this->LuaIsItem);
	lua_register(Lua, "GetExcellentOpt", this->LuaNewOptionRand);
	lua_register(Lua, "GetAncientOpt", this->LuaGetSetItemOption);
	lua_register(Lua, "GetRandomValue", this->LuaGetRandomValue);
	lua_register(Lua, "IsSocketItem", this->LuaIsSocketItem);
	lua_register(Lua, "IsPentagramItem", this->LuaIsPentagramItem);
	lua_register(Lua, "IsElementalItem", this->LuaIsElementalItem);
	lua_register(Lua, "AddToMLSTable", this->LuaAddToMLSValueTable);
	lua_register(Lua, "GetExcellentOptByKind", this->LuaGetExcOptionByConfig);
	lua_register(Lua, "GetLargeRandomValue", this->LuaGetLargeRandomValue);*/

	int arr[10] = { 10,20,30,40,50,60,70,80,90,100 };
	lua_newtable(Lua);
	lua_pushstring(Lua, "arr");

	for (int i = 0; i < 10; i++)
	{
		lua_pushinteger(Lua, arr[i]);
		lua_rawseti(Lua, -3, i + 1);
	}

}

void LuaExport::AddGlobal(lua_State * Lua)
{
	/*lua_pushinteger(Lua, (int)pFontNormal);
	lua_setglobal(Lua, "FontNormal");

	lua_pushinteger(Lua, (int)pFontBold);
	lua_setglobal(Lua, "FontBold");

	lua_pushinteger(Lua, (int)pFontBigBold);
	lua_setglobal(Lua, "FontBigBold");

	lua_pushinteger(Lua, (int)pFontNormal2);
	lua_setglobal(Lua, "FontNormal2");

	lua_pushinteger(Lua, 542);
	lua_setglobal(Lua, "pTestNum");*/

	
	lua_pushlightuserdata(Lua, (LPVOID)&pFontNormal);
	lua_setglobal(Lua, "FontNormal");

	lua_pushlightuserdata(Lua, (LPVOID)&pFontBold);
	lua_setglobal(Lua, "FontBold");

	lua_pushlightuserdata(Lua, (LPVOID)&pFontBigBold);
	lua_setglobal(Lua, "FontBigBold");

	lua_pushlightuserdata(Lua, (LPVOID)&pFontNormal2);
	lua_setglobal(Lua, "FontNormal2");
	 


	/*lua_pushinteger(Lua, gEnableServerDivision);
	lua_setglobal(Lua, "gEnableServerDivision");

	lua_pushinteger(Lua, g_ConfigRead.data.common.GuildCreate);
	lua_setglobal(Lua, "GuildCreate");

	lua_pushinteger(Lua, gEnableEventNPCTalk);
	lua_setglobal(Lua, "gEnableEventNPCTalk");

	lua_pushinteger(Lua, (int)g_DevilSquare.IsEventEnable());
	lua_setglobal(Lua, "DevilSquareEvent");

	lua_pushinteger(Lua, g_ConfigRead.data.common.UserMaxLevel);
	lua_setglobal(Lua, "MaxNormalLevel");

	lua_pushinteger(Lua, g_MaxStatsInfo.GetClass.MLUserMaxLevel);
	lua_setglobal(Lua, "MaxMasterLevel");*/
}