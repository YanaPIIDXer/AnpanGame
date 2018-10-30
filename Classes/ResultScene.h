#ifndef __RESULTSCENE_H__
#define __RESULTSCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class TouchGuard;

/**
 * ���U���g���.
 */
class ResultScene : public Scene
{

public:

	// ������.
	bool init(int Score, int AfterPoint, int HighScore);

	// ���܂��Ȃ��W�J�֐�.
	static ResultScene *create(int Score, int AfterPoint, int HighScore);

private:

	// �^�b�`�K�[�h
	TouchGuard *pTouchGuard;

};

#endif		// #ifndef __RESULTSCENE_H__
