/**===File Commentary=======================================*/
/**
 *	@file	Luac.cpp
 *
 *	@brief	Luaモジュール
 *
 *	@author	KORYUOH
 *
 *	@date	2013/09/15
 */
/**===File Include=========================================*/
#include	<Lua/Luac.h>
#include	<iostream>
#include	<iomanip>
/**===Class Implementation=================================*/
/**
static const struct luaL_Reg myMathLib [] = {
	{"add", l_add},
		{"mul", l_mul},
		{NULL, NULL} //最後は必ずNULLのペア
}
この後で
	luaL_register(L, "myMath", myMathLib);って登録すると
	luaのなかで
	myMath.add(1,2)
	とかで使えるようになる
**/
/**========================================================*/
/**
 *	@brief	コンストラクタ
 *	@param[in]	Luaファイルパス
 */
/**========================================================*/
Luac::Luac(const std::string& luaPath)
	: mLuaPath(luaPath)
	, mLua(luaL_newstate())
	, mInitialized(true)
	, mArgCnt(0)
{
	luainit();
}
/**========================================================*/
/**
*	@brief	コンストラクタ
*	@param[in]	Luaファイルパス
*/
/**========================================================*/
Luac::Luac()
	: mLuaPath("")
	, mLua(nullptr)
	, mInitialized(false)
	, mArgCnt(0)
{
}
/**========================================================*/
/**
*	@brief	初期化
*	@param[in]	Luaファイルパス
*	@note	本来はコンストラクタで呼ばれる
*/
/**========================================================*/
void Luac::Initialize(const std::string& luapath)
{
	if (mInitialized)
	{
		lua_close(mLua);
		mInitialized = false;
	}

	mLuaPath = luapath;
	mLua = luaL_newstate();
	mInitialized = true;
	mArgCnt = 0;

	luainit();

}
/**========================================================*/
/**
 *	@brief	Luaに関数を追加
 *	@param[in]	追加関数名
 *	@param[in]	コールバック関数
 *	@note	追加の関数は既定の型のみ
 */
/**========================================================*/
//*template<typename Ty>
void Luac::setFunction(const std::string& funcName,void* function){
	lua_register(mLua,funcName.c_str(),static_cast<lua_CFunction>(function));
}
/**========================================================*/
/**
*	@brief	Luaに関数を追加
*	@param[in]	追加関数名
*	@param[in]	コールバック関数
*	@note	追加の関数は既定の型のみ
*/
/**========================================================*/
void Luac::addClass(const std::string& className , const static struct luaL_Reg *classdef)
{
	luaL_newlib(mLua, classdef);
	lua_setglobal(mLua, className.c_str());
}
/**========================================================*/
/**
 *	@brief	Luaダンプの生成
 *	@param[in]	Luaステート
 */
/**========================================================*/
void Luac::Dump(LUA_STATE lua){
	int max_stack = lua_gettop(lua);
	std::cout <<"=== Lua Dump ========================================="<<"\n";
	std::cout << "LUA_MAX_STACK : " << max_stack<<"\n";
	for(int i = 0; i < max_stack;i++){
		int stack =	max_stack - i;
		int type = lua_type(lua,stack);
		std::cout <<"Stack["<<std::setw(2)<<stack<< " : "<<std::setw(10)<< lua_typename(lua,type) <<"]\t";
		switch(type){
		case LUA_TNUMBER:
			//number型
			std::cout << lua_tonumber(lua, stack);
			break;
		case LUA_TBOOLEAN:
			//boolean型
			if( lua_toboolean(lua, stack) ) {
				std::cout << "true";
			}else{
				std::cout <<"false";
			}
			break;
		case LUA_TSTRING:
			//string型
			std::cout << lua_tostring(lua,stack);
			break;
		case LUA_TNIL:
			//nil
			break;
		default:
			//その他の型
			std::cout <<lua_typename(lua, stack);
			break;
		}
			std::cout<<"\n";
	}
	std::cout <<"======================================================"<<"\n";
}
void Luac::Dump(){
	Dump(mLua);
}

/**========================================================*/
/**
 *	@brief	デストラクタ
 */
/**========================================================*/
Luac::~Luac(){
	if (mInitialized)
		lua_close(mLua);
}
/**========================================================*/
/**
 *	@brief	Luaの初期化
 */
/**========================================================*/
void Luac::luainit(){
	// Lua標準関数を使う
	luaL_openlibs(mLua);
	if(luaL_loadfile(mLua, mLuaPath.c_str())){
		std::string error = lua_tostring(mLua,-1);
		perror(("init ERROR:"+error).c_str());
	}
}
/**========================================================*/
/**
 *	@brief	Luaファイルの実行
 */
/**========================================================*/
void Luac::run(){

	if (!isInitialized())
	{
		return;
	}
//	luaL_openlibs(mLua);
	if(luaL_loadfile(mLua, mLuaPath.c_str())||lua_pcall(mLua,0,0,0)){
		std::string error = lua_tostring(mLua,-1);
		perror(("Run ERROR:"+error).c_str());
	}
}
/**========================================================*/
/**
 *	@brief	Luaの関数を呼び出す
 */
/**========================================================*/
//template<typename Ty>
void Luac::CallFunc(const std::string& funcName){
	lua_getglobal(mLua, funcName.c_str());
	 if(lua_pcall(mLua, 0, 0, 0)) {
		std::string error = lua_tostring(mLua,-1);
		perror((funcName+" EXEC ERROR:"+error).c_str());
	}
}
/**========================================================*/
/**
*	@brief	Luaの関数を呼び出す準備
*	@param[in] 関数名
*/
/**========================================================*/

void Luac::ReadyFunc(const std::string& funcName)
{
	lua_getglobal(mLua, funcName.c_str());
}

/**========================================================*/
/**
*	@brief	Luaの関数を呼び出す
*	@param[in]	Luaの引数の数
*/
/**========================================================*/
void Luac::CallFunc()
{
	if (lua_pcall(mLua, mArgCnt, 0, 0))
	{
		std::string error = lua_tostring(mLua, -1);
		perror((" EXEC ERROR:" + error).c_str());
	}
	mArgCnt = 0;
}
/**========================================================*/
/**
*	@brief	Luaの関数の引数を設定
*	@param[in]	引数
*/
/**========================================================*/

void Luac::SetInt(int arg)
{
	lua_pushinteger(mLua, arg);
	++mArgCnt;
}

void Luac::SetFloat(float arg)
{
	lua_pushnumber(mLua, arg);
	++mArgCnt;
}

void Luac::SetPtr(void* p)
{
	lua_pushlightuserdata(mLua, p);
	++mArgCnt;
}

void Luac::SetStr(const char* str)
{
	lua_pushstring(mLua, str);
	++mArgCnt;
}

void Luac::SetStr(const std::string& str)
{
	SetStr(str.c_str());
	++mArgCnt;
}

void Luac::SetNil()
{
	lua_pushnil(mLua);
	++mArgCnt;
}


/**===End Of File==========================================*/