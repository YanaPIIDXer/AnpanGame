#include "APIExecuter.h"
#include "HttpConnection.h"
#include "APIURLs.h"
#include "UserData.h"
#include "JsonHelper.h"
#include "ShopItem.h"

// �F��.
void APIExecuter::Auth(Node *pParent, const std::string &Id, const std::function<void(const std::string &, int, int)> &Callback)
{
	CreateConnection(pParent, APIURLs::Auth, [Id](HttpConnection *pConnection)
	{
		pConnection->AddParameter("Id", Id);
	}, [Callback](const JsonHelper &Json)
	{
		std::string Id = Json.GetString("Id");
		int Point = Json.GetInt("Point");
		int HighScore = Json.GetInt("HighScore");
		Callback(Id, Point, HighScore);
	});
}

// �V���b�v���.
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

// �J�n.
void APIExecuter::Start(Node *pParent, const std::vector<int> &ItemIds, const std::function<void(int, const std::string &)> &Callback)
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
		int Point = Json.GetInt("Point");
		std::string Script = Json.GetString("Script");
		Callback(Point, Script);
	});
}

// ���U���g
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


// HttpConnection�𐶐�.
void APIExecuter::CreateConnection(Node *pParent, const std::string &URL, const std::function<void(HttpConnection *)> &CreatedCallback, const std::function<void(const JsonHelper &)> &JsonCallback)
{
	auto *pConnection = HttpConnection::create(URL);
	pParent->addChild(pConnection);
	CreatedCallback(pConnection);
	pConnection->Send([pParent, JsonCallback](HttpResponse *pResponse)
	{
		JsonHelper Json(pResponse->getResponseData());

		JsonCallback(Json);
	});
}
