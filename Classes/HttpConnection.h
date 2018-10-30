#ifndef __HTTPCONNECTION_H__
#define __HTTPCONNECTION_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "network/HttpClient.h"
using namespace cocos2d::network;

/**
 * HTTP�ڑ�.
 */
class HttpConnection : public Layer
{

private:		// �ʖ���`.

	typedef std::function<void(HttpResponse *)> CallbackFunc;

public:

	// �R���X�g���N�^
	HttpConnection(const std::string &URL);

	// �p�����[�^�ǉ�.
	void AddParameter(const std::string &Name, const std::string &Value);
	void AddParameter(const std::string &Name, int Value);

	// ���M.
	void Send(const CallbackFunc &InCallback);

	// ���܂��Ȃ��W�J�֐�.
	static HttpConnection *create(const std::string &URL);

private:

	// ���N�G�X�g
	HttpRequest *pRequest;

	// �p�����[�^
	std::string Parameter;

	// �R�[���o�b�N
	CallbackFunc Callback;


	// ���X�|���X��M.
	void OnResponse(HttpClient *pClient, HttpResponse *pResponse);

};

#endif		// #ifndef __HTTPCONNECTION_H__
