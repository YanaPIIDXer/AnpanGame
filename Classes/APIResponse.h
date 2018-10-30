#ifndef __APIRESPONSE_H__
#define __APIRESPONSE_H__

#include <string>

// AuthAPI�߂�l.
struct AuthResponse
{
	std::string Id;
	int Point;
	int HighScore;
};

// StartAPI�߂�l.
struct StartResponse
{
	int Point;
	std::string Script;
};

#endif		// #ifndef __APIRESPONSE_H__
