#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Lua/Luac.h>

int func(){
	printf("Called ...\n");
	return 0;
}

class Value{
public:
	static int destroy(Luac::LUA_STATE lua){
		printf(" THIS IS DESTROY FUNCTION\n"); 
		return 0;
	};
};

int add(Luac::LUA_STATE lua){
	int a = luaL_checkint(lua,-2);
	int b = luaL_checkint(lua,-1);
	Luac::Dump(lua);
	lua_pushnumber(lua,a+b);
	Luac::Dump(lua);
	return 1;//戻り値はスタックで返す個数
}

int dice(Luac::LUA_STATE lua)
{
	lua_pushnumber(lua, 1 + rand() % 6);
	return 1;
}

int randomize(Luac::LUA_STATE lua)
{
	unsigned int seed = luaL_checkint(lua, -1);
	srand(seed);
	return 0;
}

int randomtime(Luac::LUA_STATE lua)
{
	srand((unsigned int)time(NULL));
	return 0;
}

int nDm(Luac::LUA_STATE lua)
{
	int surface = luaL_checkint(lua, -2);
	int loop = luaL_checkint(lua, -1);

	int sum = 0;

	for (int i = 0; i < loop; ++i)
	{
		int roll = 1 + rand() % surface;
		printf("[%d]", roll);
		sum += roll;
	}

	printf("\n");

	printf("min %d max %d\n",loop , surface* loop);
	printf("/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/\n");
	printf("Result = %d\n",sum);

	lua_pushnumber(lua, sum);
	return 1;
}

static luaL_Reg g_lib_a[] = { 
		{"roll",dice},
		{ "initrand", randomize },
		{ "srand", randomtime },
		{"tdice",nDm},
		{NULL,NULL} 
};

int fizbuz(Luac::LUA_STATE lua)
{
	int max = luaL_checkint(lua, -1);

	for (int i = 1; i <= max; ++i)
	{
		if (i % 15 == 0)
		{
			printf("FizzBuzz\n");
			continue;
		}
		if (i % 5 == 0)
		{
			printf("Buzz\n");
			continue;
		}

		if (i % 3 == 0)
		{
			printf("Fizz\n");
			continue;
		}

		printf("%d\n", i);
	}
	return 0;

}


int rollFB(Luac::LUA_STATE lua)
{
	int max = 1 + rand() % 29;

	printf("Roll[%d]\n",max);

	for (int i = 1; i <= max; ++i)
	{
		if (i % 15 == 0)
		{
			printf("FizzBuzz\n");
			continue;
		}
		if (i % 5 == 0)
		{
			printf("Buzz\n");
			continue;
		}

		if (i % 3 == 0)
		{
			printf("Fizz\n");
			continue;
		}

		printf("%d\n", i);
	}
	return 0;
}

static Luac::LUA_LIBTABLE g_lib_b[] =
{
	{ "FizzBuzz", fizbuz },
	{ "FizzBuzzRoll", rollFB },
	{NULL,NULL}
};

int main(int argc, char* argv[])
{
//*
//	Luac lua("test.lua");
//	lua.setFunction("Shout",&func);
//	lua.setFunction("add",&add);
//	lua.setFunction("Destroyer",&Value::destroy);
//
//	printf("===ADD_CLASS===\n");
//
//	lua.Dump();
//	lua.addClass("Mod",g_lib_a);
//	lua.addClass("FB", g_lib_b);
//	lua.Dump();
//
//	printf("===============\n");
//
//	lua.run();
//	lua.CallFunc("speech");
//	lua.CallFunc("say");
//
	Luac lua("call.lua");
	lua.run();

	lua.Dump();
	lua.ReadyFunc("sum");
	lua.Dump();
	lua.SetInt(2);
	lua.Dump();
	lua.SetInt(5);
	lua.Dump();
	lua.CallFunc();

	lua.Dump();
/*/
		// Luaを開く
	lua_State* L	= luaL_newstate();

		// Lua標準関数を使う
		luaL_openlibs(L);

		// Luaファイルを読み込む
		if(luaL_loadfile(L, "test.lua") || lua_pcall(L, 0, 0, 0)) {
				perror(lua_tostring(L, -1));
		}

		// 関数を読み込む
		lua_getglobal(L, "speech");
		if(lua_pcall(L, 0, 0, 0)) {
				perror(lua_tostring(L, -1));
		}
		// グローバル変数を読む
		lua_getglobal(L, "Name");
		if(lua_isstring(L, -1)) {
				printf("My name is %s.\n", lua_tostring(L, -1));
		}

		// Luaを閉じる
		lua_close(L);
//*/
		getchar();
		return 0;
}