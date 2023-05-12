#include "Maps.h"

Maps::Maps()
{
	StageGenerator();
}

Maps::~Maps()
{
}

void Maps::StageGenerator()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		vec_Map_1.push_back(vector<int>(WIDTH, 0));
		vec_Map_2.push_back(vector<int>(WIDTH, 0));

	}

	for (int i = 0; i < vec_Map_1.size(); i++)
	{
		for (int j = 0; j < vec_Map_1[i].size(); j++)
		{
			//1번맵 배열 초기화
			if (i == HEIGHT -2 || i == HEIGHT -1 || i == HEIGHT - 4)
			{
				vec_Map_1[i][j] = 1;

			}
			if (i == HEIGHT - 3 && j % 2 == 0)
			{
				vec_Map_1[i][j] = 3;
			}

			//2번맵 배열 초기화
			if (i == HEIGHT - 2 || i == HEIGHT - 1 || i == HEIGHT - 4)
			{
				vec_Map_2[i][j] = 1;

			}
			if (i == HEIGHT - 3 && j % 2 != 0)
			{
				vec_Map_2[i][j] = 3;
			}
		}
	}
}
