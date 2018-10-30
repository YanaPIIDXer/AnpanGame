#ifndef __APIURLS_H__
#define __APIURLS_H__

#include <string>

/**
 * APIのURL定数.
 */
class APIURLs
{

private:

	// ベース
	static const std::string URLBase;

public:

	// 認証.
	static const std::string Auth;

	// ショップ情報.
	static const std::string ShopData;

	// 開始.
	static const std::string Start;

	// リザルト
	static const std::string Result;

};

#endif		// #ifndef __APIURLS_H__
