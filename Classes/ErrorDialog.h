#ifndef __ERRORDIALOG_H__
#define __ERRORDIALOG_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * エラーダイアログクラス
 */
class ErrorDialog : public Layer
{

public:

	// 初期化.
	virtual bool init() override;

	// おまじない
	CREATE_FUNC(ErrorDialog);

private:

};

#endif		// #ifndef __ERRORDIALOG_H__
