#ifndef __JSONHELPER_H__
#define __JSONHELPER_H__

struct Json;
#include <vector>
#include <string>

/**
 * spine/Json.h�̃��b�p�[�N���X
 */
class JsonHelper
{

public:

	// �R���X�g���N�^
	JsonHelper(std::vector<char> *pBuffer);
	JsonHelper(Json *pInJson) { pJson = pInJson; }
	
	// Int�擾.
	int GetInt(const std::string &Name) const;

	// ������擾.
	std::string GetString(const std::string &Name) const;

	// �z�񒷎擾.
	int GetArrayLength() const;

	// �z��Q��.
	JsonHelper operator[](int Index) const;

private:

	// Json
	Json *pJson;

};

#endif		// #ifndef __JSONHELPER_H__
