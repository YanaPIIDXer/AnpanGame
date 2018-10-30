#ifndef __USERDATA_H__
#define __USERDATA_H__

#include <string>

/**
 * ユーザデータ
 */
class UserData
{

public:

	// セット
	static void Set(const std::string &InId, int InPoint, int InHighScore)
	{
		Instance.Id = InId;
		Instance.Point = InPoint;
		Instance.HighScore = InHighScore;
	}

	// ID取得.
	static const std::string &GetId() { return Instance.Id; }

	// ポイント取得.
	static int GetPoint() { return Instance.Point; }

	// ポイントをセット
	static void SetPoint(int InPoint) { Instance.Point = InPoint; }

	// ハイスコア取得.
	static int GetHighScore() { return Instance.HighScore; }

	// ハイスコアをセット。
	static void SetHighScore(int InHighScore) { Instance.HighScore = InHighScore; }

private:

	// ID
	std::string Id;

	// ポイント
	int Point;

	// ハイスコア
	int HighScore;


	UserData() {}
	static UserData Instance;

};

#endif		// #ifndef __USERDATA_H__
