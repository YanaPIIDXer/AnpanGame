#ifndef __HTTPCONNECTION_H__
#define __HTTPCONNECTION_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "network/HttpClient.h"
using namespace cocos2d::network;

/**
 * HTTP接続.
 */
class HttpConnection : public Layer
{

private:		// 別名定義.

	typedef std::function<void(HttpResponse *)> CallbackFunc;

public:

	// コンストラクタ
	HttpConnection(const std::string &URL);

	// パラメータ追加.
	void AddParameter(const std::string &Name, const std::string &Value);
	void AddParameter(const std::string &Name, int Value);

	// 送信.
	void Send(const CallbackFunc &InCallback);

	// おまじない展開関数.
	static HttpConnection *create(const std::string &URL);

private:

	// リクエスト
	HttpRequest *pRequest;

	// パラメータ
	std::string Parameter;

	// コールバック
	CallbackFunc Callback;


	// レスポンス受信.
	void OnResponse(HttpClient *pClient, HttpResponse *pResponse);

};

#endif		// #ifndef __HTTPCONNECTION_H__
