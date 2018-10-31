#include "JsonHelper.h"
#include "spine/Json.h"

// �R���X�g���N�^
JsonHelper::JsonHelper(std::vector<char> *pBuffer)
{
	const char *pData = reinterpret_cast<char *>(&(pBuffer->front()));
	pJson = Json_create(pData);
}

// Int�擾.
int JsonHelper::GetInt(const std::string &Name) const
{
	return Json_getInt(pJson, Name.c_str(), 0);
}

// ������擾.
std::string JsonHelper::GetString(const std::string &Name) const
{
	std::string Value = Json_getString(pJson, Name.c_str(), "");
	return Value;
}

// �I�u�W�F�N�g�擾.
JsonHelper JsonHelper::GetObject(const std::string &Name) const
{
	Json *pObj = Json_getItem(pJson, Name.c_str());
	JsonHelper Obj(pObj);
	return Obj;
}

// �z�񒷎擾.
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

// �z��Q��.
JsonHelper JsonHelper::operator[](int Index) const
{
	Json *pItem = pJson->child;
	for (int i = 0; i < Index; i++)
	{
		pItem = pItem->next;
	}

	return JsonHelper(pItem);
}
