#include "APIExecuter.h"
#include "HttpConnection.h"
#include "APIURLs.h"
#include "UserData.h"
#include "JsonHelper.h"
#include "ShopItem.h"
#include "ErrorDialog.h"

// 認証.
void APIExecuter::Auth(Node *pParent, const std::string &Id, const std::function<void(const AuthResponse &)> &Callback)
{
	CreateConnection(pParent, APIURLs::Auth, [Id](HttpConnection *pConnection)
	{
		pConnection->AddParameter("Id", Id);
	}, [Callback](const JsonHelper &Json)
	{
		AuthResponse Response;
		Response.Id = Json.GetString("Id");
		Response.Point = Json.GetInt("Point");
		Response.HighScore = Json.GetInt("HighScore");
		Callback(Response);
	});
}

// ショップ情報.
void APIExecuter::ShopData(Node *pParent, const std::function<void(const std::vector<ShopItem *> &)> &Callback)
{
	CreateConnection(pParent, APIURLs::ShopData, [](HttpConnection *pConnection){}, [Callback](const JsonHelper &Json)
	{
		std::vector<ShopItem *> ItemList;
		int Length = Json.GetArrayLength();
		for (int i = 0; i < Length; i++)
		{
			JsonHelper Item = Json[i];
			ShopItem *pItem = ShopItem::create(Item);

			ItemList.push_back(pItem);
		}

		Callback(ItemList);
	});
}

// 開始.
void APIExecuter::Start(Node *pParent, const std::vector<int> &ItemIds, const std::function<void(const StartResponse &)> &Callback)
{
	CreateConnection(pParent, APIURLs::Start, [ItemIds](HttpConnection *pConnection)
	{
		pConnection->AddParameter("Id", UserData::GetId());
		for (int i = 0; i < ItemIds.size(); i++)
		{
			pConnection->AddParameter("ItemIds[]", ItemIds[i]);
		}
	}, [Callback](const JsonHelper &Json)
	{
		StartResponse Response;
		Response.Point = Json.GetInt("Point");
		Response.Script = Json.GetString("Script");
		Callback(Response);
	});
}

// リザルト
void APIExecuter::Result(Node *pParent, int Score, const std::function<void(int, int)> &Callback)
{
	CreateConnection(pParent, APIURLs::Result, [Score](HttpConnection *pConnection)
	{
		pConnection->AddParameter("Id", UserData::GetId());
		pConnection->AddParameter("Score", Score);
	}, [Callback](const JsonHelper &Json)
	{
		int AfterPoint = Json.GetInt("Point");
		int HighScore = Json.GetInt("HighScore");

		Callback(AfterPoint, HighScore);
	});
}


// HttpConnectionを生成.
void APIExecuter::CreateConnection(Node *pParent, const std::string &URL, const std::function<void(HttpConnection *)> &CreatedCallback, const std::function<void(const JsonHelper &)> &JsonCallback)
{
	auto *pConnection = HttpConnection::create(URL);
	pParent->addChild(pConnection);
	CreatedCallback(pConnection);
	pConnection->Send([pParent, JsonCallback](HttpResponse *pResponse)
	{
		JsonHelper Json(pResponse->getResponseData());
		if (!Json.IsValid())
		{
			ErrorDialog *pErrorDialog = ErrorDialog::create();
			pParent->addChild(pErrorDialog);
			return;
		}

		JsonCallback(Json);
	});
}
