#include "APIExecuter.h"
#include "HttpConnection.h"
#include "APIURLs.h"
#include "UserData.h"

// 認証.
void APIExecuter::Auth(const std::string &Id, const std::function<void(HttpResponse *)> &Callback)
{
	auto *pConnection = CreateConnection(APIURLs::Auth);
	pConnection->AddParameter("Id", Id);
	pConnection->Send(Callback);
}

// ショップ情報.
void APIExecuter::ShopData(const std::function<void(HttpResponse *)> &Callback)
{
	auto *pConnection = CreateConnection(APIURLs::ShopData);
	pConnection->Send(Callback);
}

// 開始.
void APIExecuter::Start(const std::vector<int> &ItemIds, const std::function<void(HttpResponse *)> &Callback)
{
	auto *pConnection = CreateConnection(APIURLs::Start);
	pConnection->AddParameter("Id", UserData::GetId());
	for (int i = 0; i < ItemIds.size(); i++)
	{
		pConnection->AddParameter("ItemIds[]", ItemIds[i]);
	}
	pConnection->Send(Callback);
}

// リザルト
void APIExecuter::Result(int Score, const std::function<void(HttpResponse *)> &Callback)
{
	auto *pConnection = CreateConnection(APIURLs::Result);
	pConnection->AddParameter("Id", UserData::GetId());
	pConnection->AddParameter("Score", Score);
	pConnection->Send(Callback);
}


// HttpConnectionを生成.
HttpConnection *APIExecuter::CreateConnection(const std::string &URL)
{
	auto *pConnection = HttpConnection::create(URL);
	return pConnection;
}
