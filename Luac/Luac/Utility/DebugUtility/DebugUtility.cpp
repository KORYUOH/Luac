/**===File Commentary=======================================*/
/**
 *	@file	DebugUtility.cpp
 *
 *	@brief	デバッグ用コンソール出力
 *
 *	@attention	デバッグのみ有効
 *
 *	@author	KORYUOH
 *
 *	@date	2012/11/19
 */
/**===File Include=========================================*/
#include	<Utility/DebugUtility/DebugUtility.h>
#ifdef _DEBUG
#include	<sstream>
#include	<Windows.h>
/**===Class Implementation=================================*/
/**========================================================*/
/**
 *	@brief	デバッグ出力
 *	@param[in]	可変長
 *	@note	書式はprintfに準ずる
 *	@author	KORYUOH
 */
/**========================================================*/
void DebugUtility::print(const char* format,...){
	char tmp[1024];
	va_list argptr;
	va_start(argptr,format);
	vsprintf(tmp,format,argptr);
	va_end(argptr);
	OutputDebugString(tmp);
}
void DebugUtility::println(const char* format,...){
	char tmp[1024];
	va_list argptr;
	va_start(argptr,format);
	vsprintf(tmp,format,argptr);
	va_end(argptr);
	OutputDebugString(tmp);
	OutputDebugString("\n");
}
#else //_DEBUG is no defined
/**========================================================*/
/**
 *	@brief	デバッグ出力
 *	@param[in]	可変長
 *	@attention	偽実装
 *	@note	書式はprintfに準ずる
 *	@author	KORYUOH
 */
/**========================================================*/

void DebugUtility::print(const char* format,...){
}
void DebugUtility::println(const char* format,...){
}
#endif//_DEBUG
/**===End Of File==========================================*/