#ifndef __APIEXECUTER_H__
#define __APIEXECUTER_H__

#include <string>
#include <functional>
#include <vector>

#include "cocos2d.h"
#include "network/HttpClient.h"
using namespace cocos2d;
using namespace cocos2d::network;

#include "APIResponse.h"

class HttpConnection;
class ShopItem;
class JsonHelper;

/**
 * WebAPIを叩くクラス
 */
class APIExecuter
{

public:

	// 認証.
	static void Auth(Node *pParent, const std::string &Id, const std::function<void(const AuthResponse &)> &Callback);

	// ショップ情報.
	static void ShopData(Node *pParent, const std::function<void(const std::vector<ShopItem *> &)> &Callback);

	// 開始.
	static void Start(Node *pParent, const std::vector<int> &ItemIds, const std::function<void(const StartResponse &)> &Callback);

	// リザルト
	static void Result(Node *pParent, int Score, const std::function<void(int, int)> &Callback);

private:

	// HttpConnectionを生成.
	static void CreateConnection(Node *pParent, const std::string &URL, const std::function<void(HttpConnection *)> &CreatedCallback, const std::function<void(const JsonHelper &)> &JsonCallback);

};

#endif		// #ifndef __APIEXECUTER_H__