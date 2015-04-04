/**===File Commentary=======================================*/
/**
 *	@file	ClockTimer.h
 *
 *	@brief	タイマー
 *
 *	@author	KORYUOH
 *
 *	@date	2013/01/08
 */
/**===Include Guard========================================*/
#ifndef	_CLOCKTIMER_H_
#define	_CLOCKTIMER_H_
/**===File Include=========================================*/
#include	<ctime>
/**===Class Definition=====================================*/
class ClockTimer{
public:
	/**
	 *	@brief	コンストラクタ
	 */
	ClockTimer();
	/**
	 *	@brief	デストラクタ
	 */
	virtual ~ClockTimer(){}
	/**
	 *	@brief	開始
	 */
	void start();
	/**
	 *	@brief	停止・更新
	 */
	void stop();
	/**
	 *	@brief	経過時間取得
	 *	@return	経過時間
	 */
	float getTimerSec()const;
	/**
	 *	@brief	指定時間経過したか？
	 *	@param[in]	指定時間
	 *	@return	経過しているならば true
	 */
	bool isOverSec(float sec);
	/**
	 *	@brief	指定時間待機
	 *	@param[in]	指定時間
	 */
	void WaitOverSec(float sec);
private:
	/**	メンバー変数*/
	clock_t mOldTime;
	clock_t mNewTime;
};
/**===End Class Definition=================================*/
#endif
/**===End Of File==========================================*/