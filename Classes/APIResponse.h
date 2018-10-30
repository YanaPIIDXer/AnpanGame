#ifndef __APIRESPONSE_H__
#define __APIRESPONSE_H__

#include <string>

// AuthAPI–ß‚è’l.
struct AuthResponse
{
	std::string Id;
	int Point;
	int HighScore;
};

// StartAPI–ß‚è’l.
struct StartResponse
{
	int Point;
	std::string Script;
};

// ResultAPI–ß‚è’l.
struct ResultResponse
{
	int Point;
	int HighScore;
};

#endif		// #ifndef __APIRESPONSE_H__
