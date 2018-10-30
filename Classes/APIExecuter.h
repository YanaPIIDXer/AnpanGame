#ifndef __APIEXECUTER_H__
#define __APIEXECUTER_H__

#include <string>
#include <functional>
#include <vector>

#include "network/HttpClient.h"
using namespace cocos2d::network;

class HttpConnection;

/**
 * WebAPIを叩くクラス
 */
class APIExecuter
{

public:

	// 認証.
	static void Auth(const std::string &Id, const std::function<void(HttpResponse *)> &Callback);

	// ショップ情報.
	static void ShopData(const std::function<void(HttpResponse *)> &Callback);

	// 開始.
	static void Start(const std::vector<int> &ItemIds, const std::function<void(HttpResponse *)> &Callback);

	// リザルト
	static void Result(int Score, const std::function<void(HttpResponse *)> &Callback);

private:

	// HttpConnectionを生成.
	static HttpConnection *CreateConnection(const std::string &URL);

};

#endif		// #ifndef __APIEXECUTER_H__