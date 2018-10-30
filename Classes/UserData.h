#ifndef __USERDATA_H__
#define __USERDATA_H__

#include <string>

/**
 * ���[�U�f�[�^
 */
class UserData
{

public:

	// �Z�b�g
	static void Set(const std::string &InId, int InPoint, int InHighScore)
	{
		Instance.Id = InId;
		Instance.Point = InPoint;
		Instance.HighScore = InHighScore;
	}

	// ID�擾.
	static const std::string &GetId() { return Instance.Id; }

	// �|�C���g�擾.
	static int GetPoint() { return Instance.Point; }

	// �|�C���g���Z�b�g
	static void SetPoint(int InPoint) { Instance.Point = InPoint; }

	// �n�C�X�R�A�擾.
	static int GetHighScore() { return Instance.HighScore; }

	// �n�C�X�R�A���Z�b�g�B
	static void SetHighScore(int InHighScore) { Instance.HighScore = InHighScore; }

private:

	// ID
	std::string Id;

	// �|�C���g
	int Point;

	// �n�C�X�R�A
	int HighScore;


	UserData() {}
	static UserData Instance;

};

#endif		// #ifndef __USERDATA_H__
