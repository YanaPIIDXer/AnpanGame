#include "APIExecuter.h"
#include "HttpConnection.h"
#include "APIURLs.h"
#include "UserData.h"
#include "JsonHelper.h"

// 認証.
void APIExecuter::Auth(Node *pParent, const std::string &Id, const std::function<void(const std::string &, int, int)> &Callback)
{
	auto *pConnection = CreateConnection(pParent, APIURLs::Auth);
	pConnection->AddParameter("Id", Id);
	pConnection->Send([Callback](HttpResponse *pResponse)
	{
		JsonHelper Json(pResponse->getResponseData());
		std::string Id = Json.GetString("Id");
		int Point = Json.GetInt("Point");
		int HighScore = Json.GetInt("HighScore");
		Callback(Id, Point, HighScore);
	});
}

// ショップ情報.
void APIExecuter::ShopData(Node *pParent, const std::function<void(HttpResponse *)> &Callback)
{
	auto *pConnection = CreateConnection(pParent, APIURLs::ShopData);
	pConnection->Send(Callback);
}

// 開始.
void APIExecuter::Start(Node *pParent, const std::vector<int> &ItemIds, const std::function<void(HttpResponse *)> &Callback)
{
	auto *pConnection = CreateConnection(pParent, APIURLs::Start);
	pConnection->AddParameter("Id", UserData::GetId());
	for (int i = 0; i < ItemIds.size(); i++)
	{
		pConnection->AddParameter("ItemIds[]", ItemIds[i]);
	}
	pConnection->Send(Callback);
}

// リザルト
void APIExecuter::Result(Node *pParent, int Score, const std::function<void(HttpResponse *)> &Callback)
{
	auto *pConnection = CreateConnection(pParent, APIURLs::Result);
	pConnection->AddParameter("Id", UserData::GetId());
	pConnection->AddParameter("Score", Score);
	pConnection->Send(Callback);
}


// HttpConnectionを生成.
HttpConnection *APIExecuter::CreateConnection(Node *pParent, const std::string &URL)
{
	auto *pConnection = HttpConnection::create(URL);
	pParent->addChild(pConnection);
	return pConnection;
}
