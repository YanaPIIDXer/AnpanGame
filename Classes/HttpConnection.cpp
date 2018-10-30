#include "HttpConnection.h"

// コンストラクタ
HttpConnection::HttpConnection(const std::string &URL)
	: Parameter("")
{
	pRequest = new HttpRequest();
	pRequest->setUrl(URL);
	pRequest->setRequestType(HttpRequest::Type::POST);
	pRequest->setResponseCallback(this, httpresponse_selector(HttpConnection::OnResponse));
}

// パラメータ追加.
void HttpConnection::AddParameter(const std::string &Name, const std::string &Value)
{
	if (Parameter != "")
	{
		Parameter += "&";
	}

	Parameter += Name + "=" + Value;
}

// パラメータ追加.
void HttpConnection::AddParameter(const std::string &Name, int Value)
{
	std::stringstream Stream;
	Stream << Value;
	AddParameter(Name, Stream.str());
}

// 送信.
void HttpConnection::Send(const CallbackFunc &InCallback)
{
	Callback = InCallback;

	pRequest->setRequestData(Parameter.c_str(), Parameter.size());
	HttpClient::getInstance()->send(pRequest);
}

// おまじない展開関数.
HttpConnection *HttpConnection::create(const std::string &URL)
{
	HttpConnection *pRet = new HttpConnection(URL);
	if (pRet != nullptr && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		delete pRet;
		pRet = nullptr;
	}

	return pRet;
}


// レスポンス受信.
void HttpConnection::OnResponse(HttpClient *pClient, HttpResponse *pResponse)
{
	Callback(pResponse);

	auto *pParent = getParent();
	if (pParent != nullptr)
	{
		pParent->removeChild(this);
	}
}
