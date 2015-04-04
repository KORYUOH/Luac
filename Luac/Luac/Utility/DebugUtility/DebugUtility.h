/**===File Commentary=======================================*/
/**
 *	@file	DebugUtility.h
 *
 *	@brief	デバッグ用ユーティリティー
 *
 *	@note	効果はデバッグ時のみ
 *
 *	@author	KORYUOH
 *
 *	@date	2012/11/19
 */
/**===Include Guard========================================*/
#ifndef	_DEBUGUTILITY_H_
#define	_DEBUGUTILITY_H_
/**===File Include=========================================*/

/**===Class Definition=====================================*/
class DebugUtility{
public:
	/**
	 *	@brief	デバッグコンソールに文字出力
	 *	@param[in]	可変長引数
	 *	@note	文法はprintfに準ずる
	 */
	static void print(const char* format,...);
	static void println(const char* format,...);
private:
	/**	メンバー変数*/

};
/**===End Class Definition=================================*/
#endif
/**===End Of File==========================================*/