#include	<Luabin/Luabin.h>
#include	<memory>
#include	<iostream>
#include	<string>

int main(int argc, char* argv[]){

	std::unique_ptr<Luabin> lua = nullptr;

	if(argc > 1){
		lua.reset(new Luabin(argv[1]));
	}

	if(lua == nullptr){
		std::string in="";
		std::cout << "Lua File : ";
		std::cin >> in;
		lua.reset(new Luabin(in));
	}

	lua->convert();



	return 0;
}