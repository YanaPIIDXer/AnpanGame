#ifndef __RESULTSCENE_H__
#define __RESULTSCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class TouchGuard;

/**
 * リザルト画面.
 */
class ResultScene : public Scene
{

public:

	// 初期化.
	bool init(int Score, int AfterPoint, int HighScore);

	// おまじない展開関数.
	static ResultScene *create(int Score, int AfterPoint, int HighScore);

private:

	// タッチガード
	TouchGuard *pTouchGuard;

};

#endif		// #ifndef __RESULTSCENE_H__
