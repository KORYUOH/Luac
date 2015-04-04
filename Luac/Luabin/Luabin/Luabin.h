/**===File Commentary=======================================*/
/**
 *	@file	Luabin.h
 *
 *	@brief	Luaバイナリ化モジュール
 *
 *	@author	KORYUOH
 *
 *	@date	2013/11/18
 */
/**===Include Guard========================================*/
#ifndef	_LUABIN_H_
#define	_LUABIN_H_
/**===File Include=========================================*/
#include	<string>
#include	<lua.hpp>
#pragma comment(lib, "lua52.lib")
#define LUA_BIN_BUF_SIZE 1024
/**===Class Definition=====================================*/
class Luabin{
public:
	typedef lua_State* LUA_STATE;
	Luabin(const std::string& luaPath);
	virtual ~Luabin(){};
	void convert();
	void setOutDir(const std::string& outdir);
private:
	void luainit();
	static const char * reader(LUA_STATE L,FILE *fp, size_t *size);
	static int writer(LUA_STATE L,const void *data, size_t size, FILE *fp);
	size_t getBufSize()const;
private:
	static Luabin* mInstance;
	const static int BUF_SIZE;
	LUA_STATE mLua;
	std::string	mLuaPath;
	std::string mOutDir;
	std::string mExtention;
	static char m_buf[LUA_BIN_BUF_SIZE];
};
/**===End Class Definition=================================*/
#endif
/**===End Of File==========================================*/