#pragma once
#include <string>

class SwcPoint
{
public:
	static bool try_parse(const std::string& s, SwcPoint& out);

	int id;
	int type;
	float x;
	float y;
	float z;
	float raidus;
	int parent;
};
