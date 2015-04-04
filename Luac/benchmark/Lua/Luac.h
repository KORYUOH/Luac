/**===File Commentary=======================================*/
/**
 *	@file	Luac.h
 *
 *	@brief	Luaモジュール
 *
 *	@author	KORYUOH
 *
 *	@date	2013/09/15
 */
/**===Include Guard========================================*/
#ifndef	_LUAC_H_
#define	_LUAC_H_
/**===File Include=========================================*/
#include	<string>
#include	<lua.hpp>
#pragma comment(lib, "lua52.lib")
/**===Class Definition=====================================*/
class Luac{
public:
	typedef lua_State* LUA_STATE;
	typedef int LUA_TYPES;
	/**
	 *	@brief	コンストラクタ
	 *	@param[in]	luaファイル
	 */
	Luac(const std::string& luaPath);
	/**
	 *	@brief	Luaファイル実行
	 */
	void run();
	/**
	 *	@brief	関数呼び出し
	 *	@note	テンプレート
	 *	@return	指定タイプ
	 */
//	template<typename Ty>
	void CallFunc(const std::string& funcName);
	static void Dump(LUA_STATE lua);
	void Dump();
//	template<typename Ty>
	void setFunction(const std::string& funcName,void* func);
	/**&
	 *	@brief	仮想デストラクタ
	 */
	virtual ~Luac();
private:
	void luainit();
private:
	/**	メンバー変数*/
	const std::string	mLuaPath;
	LUA_STATE	mLua;
};
/**===End Class Definition=================================*/
#endif
/**===End Of File==========================================*/