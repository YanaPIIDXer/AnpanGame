#ifndef __JSONHELPER_H__
#define __JSONHELPER_H__

struct Json;
#include <vector>
#include <string>

/**
 * spine/Json.hのラッパークラス
 */
class JsonHelper
{

public:

	// コンストラクタ
	JsonHelper(std::vector<char> *pBuffer);
	JsonHelper(Json *pInJson) { pJson = pInJson; }
	
	// Int取得.
	int GetInt(const std::string &Name) const;

	// 文字列取得.
	std::string GetString(const std::string &Name) const;

	// 配列長取得.
	int GetArrayLength() const;

	// 配列参照.
	JsonHelper operator[](int Index) const;

private:

	// Json
	Json *pJson;

};

#endif		// #ifndef __JSONHELPER_H__
