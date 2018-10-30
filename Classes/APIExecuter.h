#ifndef __APIEXECUTER_H__
#define __APIEXECUTER_H__

#include <string>
#include <functional>
#include <vector>

#include "network/HttpClient.h"
using namespace cocos2d::network;

class HttpConnection;

/**
 * WebAPI��@���N���X
 */
class APIExecuter
{

public:

	// �F��.
	static void Auth(const std::string &Id, const std::function<void(HttpResponse *)> &Callback);

	// �V���b�v���.
	static void ShopData(const std::function<void(HttpResponse *)> &Callback);

	// �J�n.
	static void Start(const std::vector<int> &ItemIds, const std::function<void(HttpResponse *)> &Callback);

	// ���U���g
	static void Result(int Score, const std::function<void(HttpResponse *)> &Callback);

private:

	// HttpConnection�𐶐�.
	static HttpConnection *CreateConnection(const std::string &URL);

};

#endif		// #ifndef __APIEXECUTER_H__