#include "IdManager.h"
#include <fstream>
#include <sstream>
#include "cocos2d.h"

const std::string IdManager::FileName = "Id.dat";
const int IdManager::IdLength = 32;

// �R���X�g���N�^
IdManager::IdManager()
	: IdCache("")
{
}

// ID�擾.
std::string IdManager::GetId()
{
	if (IdCache != "") { return IdCache; }

	std::string Id = "";
	if (!LoadId(Id))
	{
		// ����.
		GenerateId(Id);
	}

	IdCache = Id;
	return Id;
}


// ID�����[�h
bool IdManager::LoadId(std::string &OutId)
{
	std::ifstream FileStream(FileName);
	if (!FileStream) { return false; }

	FileStream >> OutId;
	return true;
}

// ID�𐶐�.
void IdManager::GenerateId(std::string &OutId)
{
	std::stringstream StrStream;
	for (int i = 0; i < IdLength; i++)
	{
		char Ch = (cocos2d::random<int>(1, 100) < 50) ? 'A' : 'a';
		Ch += cocos2d::random<int>(0, 26);
		StrStream << Ch;
	}
	OutId = StrStream.str();

	// �t�@�C���ɕۑ�.
	std::ofstream FileStream(FileName);
	FileStream << OutId;
}
