#include "JsonHelper.h"
#include "spine/Json.h"

// コンストラクタ
JsonHelper::JsonHelper(std::vector<char> *pBuffer)
{
	const char *pData = reinterpret_cast<char *>(&(pBuffer->front()));
	pJson = Json_create(pData);
}

// Int取得.
int JsonHelper::GetInt(const std::string &Name) const
{
	return Json_getInt(pJson, Name.c_str(), 0);
}

// 文字列取得.
std::string JsonHelper::GetString(const std::string &Name) const
{
	std::string Value = Json_getString(pJson, Name.c_str(), "");
	return Value;
}

// 配列長取得.
int JsonHelper::GetArrayLength() const
{
	int Length = 0;
	Json *pItem = pJson->child;
	while (pItem != nullptr)
	{
		Length++;
		pItem = pItem->next;
	}
	return Length;
}

// 配列参照.
JsonHelper JsonHelper::operator[](int Index) const
{
	Json *pItem = pJson->child;
	for (int i = 0; i < Index; i++)
	{
		pItem = pItem->next;
	}

	return JsonHelper(pItem);
}
