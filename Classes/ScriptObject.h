#ifndef __SCRIPTOBJECT_H__
#define __SCRIPTOBJECT_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * �X�N���v�g���Q�Ƃ���I�u�W�F�N�g
 */
class ScriptObject : public CCObject
{

public:

	// �R���X�g���N�^
	ScriptObject();

	// ���Ԓǉ�.
	void AddTime(int AddTime);

	// �X�R�A�{����ݒ�.
	void SetScoreRate(float InScoreRate) { ScoreRate = InScoreRate; }

	// ���Ԏ擾.
	int GetTime() const { return Time; }

	// �X�R�A�{���擾.
	float GetScoreRate() const { return ScoreRate; }

	// �o�^.
	static int Register(lua_State *pState);

private:

	// ����.
	int Time;

	// �X�R�A�{��
	float ScoreRate;

};


#endif		// #ifndef __SCRIPTOBJECT_H__
