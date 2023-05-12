#pragma once
#include <Windows.h>
#include <vector>

#define WIDTH 100
#define HEIGHT 25

using namespace std;

class Maps
{
public:
	Maps();
	~Maps();

private:
	void StageGenerator();

public:
	vector<vector<int>> vec_Map_1;
	vector<vector<int>> vec_Map_2;

};

