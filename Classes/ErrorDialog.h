#ifndef __ERRORDIALOG_H__
#define __ERRORDIALOG_H__

#include "cocos2d.h"
using namespace cocos2d;

/**
 * �G���[�_�C�A���O�N���X
 */
class ErrorDialog : public Layer
{

public:

	// ������.
	virtual bool init() override;

	// ���܂��Ȃ�
	CREATE_FUNC(ErrorDialog);

private:

};

#endif		// #ifndef __ERRORDIALOG_H__
