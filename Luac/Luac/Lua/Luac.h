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

#ifdef _WIN32
#pragma once
#endif
/**===File Include=========================================*/
#include	<string>
#include	<lua.hpp>
#pragma comment(lib, "lua52.lib")
/**===Class Definition=====================================*/
class Luac{
public:
	typedef lua_State* LUA_STATE;
	typedef luaL_Reg LUA_LIBTABLE;
	typedef int LUA_TYPES;
	/**
	 *	@brief	コンストラクタ
	 *	@param[in]	luaファイル
	 */
	Luac(const std::string& luaPath);
	/**
	*	@brief	コンストラクタ
	*/
	Luac();
	/**
	 *	@brief 初期化を開始
	 *	@param[in]	Luaファイルパス
	 *	@note 非推奨、コンストラクタを使ってほしい
	 */
	void Initialize(const std::string& luapath);
	/**
	 *	@brief	Luaファイル実行
	 */
	void run();
	/**
	 *	@brief	関数呼び出し
	 */
//	template<typename Ty>
	void CallFunc(const std::string& funcName);
	/**
	 *	@brief	関数呼び出し準備
	 *	@param[in]	関数名
	 *	@note	この後に与える引数をスタックにつむ
	 */
	void ReadyFunc(const std::string& funcName);
	/**
	*	@brief	関数呼び出し
	*/
	void CallFunc();
	/**
	 *	@brief	Luaのダンプコールバック
	 *	@note	テンプレート
	 */
	static void Dump(LUA_STATE lua);
	/**
	 *	@brief	Luaのダンプ
	 */
	void Dump();
	/**
	 *	@brief	関数を設定する
	 *	@param[in]	Luaでの関数名
	 *	@param[in]	追加する関数のポインタ
	 */
	void setFunction(const std::string& funcName,void* func);
	/**
	 *	@brief	Luaにクラス追加
	 *	@note	テンプレート
	 */
	void addClass(const std::string&className, const static struct luaL_Reg *classdef);
	/**
	 *	@brief	初期化されているか？
	 *	@return	初期化状態
	 */
	bool isInitialized()const{ return mInitialized;}


	void SetInt(int arg);
	void SetFloat(float arg);
	void SetPtr(void* p);
	void SetStr(const char* str);
	void SetStr(const std::string& str);
	void SetNil();
	
	/**
	 *	@brief	仮想デストラクタ
	 */
	virtual ~Luac();
private:
	/**
	 *	@brief	Luaの初期化
	 */
	void luainit();
private:
	/**	メンバー変数*/
	std::string	mLuaPath;
	LUA_STATE	mLua;
	bool	mInitialized;
	int mArgCnt;
};
/**===End Class Definition=================================*/
#endif
/**===End Of File==========================================*/