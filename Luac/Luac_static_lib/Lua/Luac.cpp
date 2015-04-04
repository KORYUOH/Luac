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
 *	@param[in]	luaのパス
 */
/**========================================================*/
Luac::Luac(const std::string& luaPath)
	:mLuaPath(luaPath)
	,mLua(luaL_newstate())
{
	luainit();
}
/**========================================================*/
/**
 *	@brief	関数の設定
 *	@param[in]	関数名
 *	@param[in]	関数
 */
/**========================================================*/
//*template<typename Ty>
void Luac::setFunction(const std::string& funcName,void* function){
	lua_register(mLua,funcName.c_str(),(lua_CFunction)function);
}
/**========================================================*/
/**
 *	@brief	ダンプ吐出し
 *	@param[in]	LuaState
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
/**========================================================*/
/**
*	@brief	Luaのダンプ(外部呼出し用)
*/
/**========================================================*/
void Luac::Dump(){
	Dump(mLua);
}

/**========================================================*/
/**
 *	@brief	デストラクタ
 */
/**========================================================*/
Luac::~Luac(){
	lua_close(mLua);
}
/**========================================================*/
/**
*	@brief	Luaの初期化（読み込み）
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
*	@brief	Luaの実行
*/
/**========================================================*/
void Luac::run(){
//	luaL_openlibs(mLua);
	if(luaL_loadfile(mLua, mLuaPath.c_str())||lua_pcall(mLua,0,0,0)){
		std::string error = lua_tostring(mLua,-1);
		perror(("init ERROR:"+error).c_str());
	}
}
/**========================================================*/
/**
 *	@brief	Luaの関数の呼び出し
 *	@param[in]	関数名
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
/**===End Of File==========================================*/