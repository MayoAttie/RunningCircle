#pragma once
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "Maps.h"
#include "GameEnding.h"	

#define LEFT		75	//왼쪽	 방향키
#define RIGHT		77	//오른쪽	 방향키
#define UP			72	//위쪽	 방향키
#define DOWN		80	//아래쪽	 방향키
#define DROPDOWN	82	//스페이스바

#define Blink		 0
#define Tile		 1
#define Character	 2
#define BackGround	 3
#define Enemy		 4
#define Item		 5
#define Cloud		 6

/*
*	cols=100 lines=25
#	define WIDTH 50
#	define HEIGHT 25
*/

class GameManager
{
public:
	GameManager();
	~GameManager();
	static GameManager* Instance();

	void Init();
	
private:
	void DrawGame_1();
	void DrawGame_2();
	void MainGame();
	void InputKey();
	void EnemyComing();
	void CheckEnd();
	void UpScore();
	void CallEndFunc();
	void ItemComing();
	void ItemEatCheck();
	void CloudComing();
	void EnemyBack();
	void ItemBack();
	void CloudBack();


	void GoToXY(int nX, int nY);

private:
	bool isGameEnd;
	vector<vector<int>> vec_Stage_1;
	vector<vector<int>> vec_Stage_2;
	int score;
	int enemy_X;
	int item_X;
	int Cloud_X[3];
	int life;
	bool isRight;
	bool isLeft;

};

