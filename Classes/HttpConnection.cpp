#include "HttpConnection.h"

// �R���X�g���N�^
HttpConnection::HttpConnection(const std::string &URL)
	: Parameter("")
{
	pRequest = new HttpRequest();
	pRequest->setUrl(URL);
	pRequest->setRequestType(HttpRequest::Type::POST);
	pRequest->setResponseCallback(this, httpresponse_selector(HttpConnection::OnResponse));
}

// �p�����[�^�ǉ�.
void HttpConnection::AddParameter(const std::string &Name, const std::string &Value)
{
	if (Parameter != "")
	{
		Parameter += "&";
	}

	Parameter += Name + "=" + Value;
}

// �p�����[�^�ǉ�.
void HttpConnection::AddParameter(const std::string &Name, int Value)
{
	std::stringstream Stream;
	Stream << Value;
	AddParameter(Name, Stream.str());
}

// ���M.
void HttpConnection::Send(const CallbackFunc &InCallback)
{
	Callback = InCallback;

	pRequest->setRequestData(Parameter.c_str(), Parameter.size());
	HttpClient::getInstance()->send(pRequest);
}

// ���܂��Ȃ��W�J�֐�.
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


// ���X�|���X��M.
void HttpConnection::OnResponse(HttpClient *pClient, HttpResponse *pResponse)
{
	Callback(pResponse);

	auto *pParent = getParent();
	if (pParent != nullptr)
	{
		pParent->removeChild(this);
	}
}
