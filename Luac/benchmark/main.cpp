#include <Lua/Luac.h>
#include <Luabin/Luabin.h>
#include <ClockTimer/ClockTimer.h>
#include <iostream>
#include <memory>
#include <cstdlib>
#ifdef _DEBUG
#pragma comment(linker,"/NODEFAULTLIB:libcmt.lib")
#endif
int main(int argc,char* argv[]){
	std::unique_ptr<ClockTimer> timer(new ClockTimer());
	Luabin binary("tarai.lua");
	binary.convert();
	Luac lua("tarai.lua");
	Luac lub("tarai.lub");
	std::cout<< "LUA START \n";
	timer->start();
//*
	lua.run();
/*/
	lua.Dump();
//*/
	timer->stop();

	std::cout <<"LUA >> "<< timer->getTimerSec() << "\n";



	std::cout<<"LUB START\n";
	timer->start();
//*
	lua.run();
/*/
	lua.Dump();
//*/
	timer->stop();
	std::cout <<"LUB >> "<< timer->getTimerSec() << "\n";
	system("pause");
	return 0;
}