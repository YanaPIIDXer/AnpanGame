#include "ScriptObject.h"
#include "tolua_fix.h"
#include "GameConfig.h"

// コンストラクタ
ScriptObject::ScriptObject()
	: Time(GameConfig::GameTime)
	, ScoreRate(1.0f)
{
}

// 時間追加.
void ScriptObject::AddTime(int AddTime)
{
	Time += AddTime;
}

// AddTime呼び出し
static int ToLua_ScriptObject_AddTime(lua_State *pState)
{
	ScriptObject *pObj = (ScriptObject *)tolua_tousertype(pState, 1, nullptr);
	int Arg0 = (int)tolua_tonumber(pState, 2, 0);
	pObj->AddTime(Arg0);
	return 1;
}

// SetScoreRate呼び出し
static int ToLua_ScriptObject_SetScoreRate(lua_State *pState)
{
	ScriptObject *pObj = (ScriptObject *)tolua_tousertype(pState, 1, nullptr);
	float Arg0 = (float)tolua_tonumber(pState, 2, 0);
	pObj->SetScoreRate(Arg0);
	return 1;
}

// 登録.
int ScriptObject::Register(lua_State *pState)
{
	tolua_open(pState);
	tolua_usertype(pState, "ScriptObject");
	tolua_module(pState, nullptr, 0);
	tolua_beginmodule(pState, nullptr);
	{
		tolua_cclass(pState, "ScriptObject", "ScriptObject", "CCObject", nullptr);
		tolua_beginmodule(pState, "ScriptObject");
		{
			tolua_function(pState, "AddTime", ToLua_ScriptObject_AddTime);
			tolua_function(pState, "SetScoreRate", ToLua_ScriptObject_SetScoreRate);
		}
		tolua_endmodule(pState);
	}
	tolua_endmodule(pState);
	return 1;
}
