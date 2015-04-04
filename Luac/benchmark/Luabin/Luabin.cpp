/**===File Commentary=======================================*/
/**
 *	@file	Luabin.cpp
 *
 *	@brief	Luaバイナリ化モジュール
 *
 *	@author	KORYUOH
 *
 *	@date	2013/11/18
 */
/**===File Include=========================================*/
#include	<Luabin/Luabin.h>
#include	<cstdio>
/**===Class Implementation=================================*/
const int Luabin::BUF_SIZE = LUA_BIN_BUF_SIZE;
Luabin* Luabin::mInstance = nullptr;
char Luabin::m_buf[BUF_SIZE];
Luabin::Luabin(const std::string& luaPath)
	:mLuaPath(luaPath)
	,mLua(luaL_newstate())
{
	mInstance = this;
	luainit();
}
/*
void make_bin_lua(const char *bin_filename, const char *text_filename) {
	FILE *fin = fopen(lua_filename, "r");
	FILE *fout = fopen(bin_filename, "wb");
	lua_State *ls = luaL_newstate();
	lua_load(ls, (lua_Reader)reader, fin, "", NULL);
	lua_dump(ls, (lua_Writer)writer, fout);
	lua_close(ls);
	fclose(fout);
	fclose(fin);
}
*/
void Luabin::luainit(){
//	m_buf = malloc(sizeof(char)*LUA_BIN_BUF_SIZE);
	printf("LUA2BIN > buf_size: %d\n",sizeof(m_buf));
}
void Luabin::convert(){
	FILE *fin = fopen(mLuaPath.c_str(), "r");
	std::string filename = std::string(mLuaPath,0,mLuaPath.find_first_of('.'));
	FILE *fout = fopen((filename+".lub").c_str(), "wb");
	lua_load(mLua, (lua_Reader)reader, fin, "", NULL);
	lua_dump(mLua, (lua_Writer)writer, fout);
	lua_close(mLua);
	fclose(fout);
	fclose(fin);
}

const char * Luabin::reader(LUA_STATE L,FILE *fp, size_t *size) {
	if (feof(fp)) {
		*size = 0;
		return NULL;
	} else {
		if(mInstance == nullptr){
			return nullptr;
		}
		*size = std::fread(mInstance->m_buf, 1, mInstance->getBufSize(), fp);
		return mInstance->m_buf;
	}
}
int Luabin::writer(LUA_STATE L,const void *data, size_t size, FILE *fp) {
	fwrite(data, size, 1, fp);
	return 0; // no error
}
size_t Luabin::getBufSize()const{
	return sizeof(m_buf);
}
/**===End Of File==========================================*/