#include "GameManager.h"
#include <iostream>
#include <stdlib.h>

GameManager::GameManager()
{
	isGameEnd = false;
	isRight = false;
	isLeft = false;
	life = 3;
	Maps maps;
	//맵1 초기화
	vec_Stage_1 = maps.vec_Map_1;
	vec_Stage_1[HEIGHT - 5][WIDTH / 2] = Character;
	//맵2 초기화
	vec_Stage_2 = maps.vec_Map_2;
	vec_Stage_2[HEIGHT - 5][WIDTH / 2] = Character;

	enemy_X = WIDTH - 1;
	vec_Stage_1[HEIGHT - 5][enemy_X] = Enemy;
	vec_Stage_2[HEIGHT - 5][enemy_X] = Enemy;

	item_X = WIDTH - 15;
	vec_Stage_1[HEIGHT - 6][item_X] = Item;
	vec_Stage_2[HEIGHT - 6][item_X] = Item;

	Cloud_X[0] = WIDTH - 3;
	Cloud_X[1] = WIDTH - 2;
	Cloud_X[2] = WIDTH - 1;
	for (int i = 0; i < 3; i++)
	{
		vec_Stage_1[HEIGHT - 18][Cloud_X[i]] = Cloud;
		vec_Stage_2[HEIGHT - 18][Cloud_X[i]] = Cloud;
	}


	score = 0;
}

GameManager::~GameManager()
{
}

GameManager* GameManager::Instance()
{
	static GameManager instance;
	return &instance;
}

void GameManager::Init()
{
	system("mode con cols=150 lines=25 | title 런닝서클");
	for (int i = 0; i < HEIGHT; i++)
	{
		GoToXY(WIDTH + 2, i);
		printf("│");
	}

	GoToXY(WIDTH + 5, 10);
	printf("점수");
	GoToXY(WIDTH + 10, 10);
	printf("%d", score);

	GoToXY(WIDTH + 5, 15);
	printf("목숨");
	GoToXY(WIDTH + 10, 15);
	printf("%d", life);

	MainGame();


}

void GameManager::MainGame()
{
	while (!isGameEnd)
	{


		DrawGame_1();
		InputKey();
		DrawGame_2();
		ItemComing();
		ItemBack();
		EnemyComing();
		EnemyBack();
		CloudComing();
		CloudBack();
		Sleep(33);
		CheckEnd();
		UpScore();
		
	}
	CallEndFunc();
}

#pragma region 맵드로우

void GameManager::DrawGame_1()
{

	for (int i = 0; i < vec_Stage_1.size(); i++)
	{
		for (int j = 0; j < vec_Stage_1[i].size(); j++)
		{

			GoToXY(j, i);
			if (vec_Stage_1[i][j] == Blink)
				printf("  ");
			else if (vec_Stage_1[i][j] == Tile)
				printf("■");
			else if (vec_Stage_1[i][j] == BackGround && isRight == true)
				printf("□");
			else if (vec_Stage_1[i][j] == Character)
				printf("★");
			else if (vec_Stage_1[i][j] == Enemy)
				printf("◆");
			else if (vec_Stage_1[i][j] == Item)
				printf("☆");
			else if (vec_Stage_1[i][j] == Cloud)
				printf("○");

		}
	}
	

}

void GameManager::DrawGame_2()
{

	for (int i = 0; i < vec_Stage_2.size(); i++)
	{
		for (int j = 0; j < vec_Stage_2[i].size(); j++)
		{
			GoToXY(j, i);
			if (vec_Stage_2[i][j] == Blink)
				printf("  ");
			else if (vec_Stage_2[i][j] == Tile)
				printf("■");
			else if (vec_Stage_2[i][j] == BackGround && isRight == true)
				printf("□");
			else if (vec_Stage_2[i][j] == Character)
				printf("★");
			else if (vec_Stage_2[i][j] == Enemy)
				printf("◆");
			else if (vec_Stage_2[i][j] == Item)
				printf("☆");
			else if (vec_Stage_2[i][j] == Cloud)
				printf("○");
		}

	}
}
#pragma endregion

#pragma region 키 인풋
void GameManager::InputKey()
{
	if (vec_Stage_2[HEIGHT - 5][WIDTH / 2] == Enemy || vec_Stage_1[HEIGHT - 5][WIDTH / 2] == Enemy)
		return;
	//Right 키
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		isRight = true;
	}
	else
		isRight = false;

	//Left 키
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if(!isRight)
			isLeft = true;
	}
	else
		isLeft = false;


	//Up 키
	static int jumpIndex = 0;
	if (jumpIndex == 1)
	{

			vec_Stage_1[HEIGHT - 7][WIDTH / 2] = Character;
			vec_Stage_1[HEIGHT - 6][WIDTH / 2] = Blink;
			vec_Stage_2[HEIGHT - 7][WIDTH / 2] = Character;
			vec_Stage_2[HEIGHT - 6][WIDTH / 2] = Blink;
			jumpIndex = 2;

	}
	else if (jumpIndex == 2)
	{

			ItemEatCheck();
			vec_Stage_1[HEIGHT - 6][WIDTH / 2] = Character;
			vec_Stage_1[HEIGHT - 7][WIDTH / 2] = Blink;
			vec_Stage_2[HEIGHT - 6][WIDTH / 2] = Character;
			vec_Stage_2[HEIGHT - 7][WIDTH / 2] = Blink;
			jumpIndex = 3;

	}
	else if (jumpIndex == 3)
	{

			vec_Stage_1[HEIGHT - 5][WIDTH / 2] = Character;
			vec_Stage_1[HEIGHT - 6][WIDTH / 2] = Blink;
			vec_Stage_2[HEIGHT - 5][WIDTH / 2] = Character;
			vec_Stage_2[HEIGHT - 6][WIDTH / 2] = Blink;
			jumpIndex = 0;

	}
	else
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{

			if (jumpIndex == 0)
			{
				ItemEatCheck();
				vec_Stage_1[HEIGHT - 5][WIDTH / 2] = Blink;
				vec_Stage_1[HEIGHT - 6][WIDTH / 2] = Character;
				vec_Stage_2[HEIGHT - 5][WIDTH / 2] = Blink;
				vec_Stage_2[HEIGHT - 6][WIDTH / 2] = Character;
				jumpIndex = 1;
			}

		}
	}

}
#pragma endregion


#pragma region  적 이동
void GameManager::EnemyComing()
{
	if (isRight)
	{
		enemy_X--;
		if (enemy_X >= 0)
		{
			vec_Stage_1[HEIGHT - 5][enemy_X] = Enemy;
			vec_Stage_2[HEIGHT - 5][enemy_X] = Enemy;
		}
		else
		{
			vec_Stage_1[HEIGHT - 5][0] = Blink;
			vec_Stage_2[HEIGHT - 5][0] = Blink;
			enemy_X = WIDTH - 1;
		}
		if (enemy_X != WIDTH - 1)
		{
			if (vec_Stage_1[HEIGHT - 5][enemy_X + 1] != Character || vec_Stage_2[HEIGHT - 5][enemy_X + 1] != Character)
			{
				vec_Stage_1[HEIGHT - 5][enemy_X + 1] = Blink;
				vec_Stage_2[HEIGHT - 5][enemy_X + 1] = Blink;
			}
		}
	}

}


void GameManager::EnemyBack()
{
	if (isLeft)
	{
		enemy_X++;
		if (enemy_X <= WIDTH - 1)
		{
			vec_Stage_1[HEIGHT - 5][enemy_X] = Enemy;
			vec_Stage_2[HEIGHT - 5][enemy_X] = Enemy;
		}
		else
		{
			vec_Stage_1[HEIGHT - 5][WIDTH - 1] = Blink;
			vec_Stage_2[HEIGHT - 5][WIDTH - 1] = Blink;
			enemy_X = WIDTH;
		}
		if (enemy_X != WIDTH - 1)
		{

			vec_Stage_1[HEIGHT - 5][enemy_X - 1] = Blink;
			vec_Stage_2[HEIGHT - 5][enemy_X - 1] = Blink;

		}
	}
}
#pragma endregion

#pragma region 아이템 이동

void GameManager::ItemComing()
{
	if (isRight)
	{
		item_X--;



		if (item_X >= 0)
		{
			vec_Stage_1[HEIGHT - 6][item_X] = Item;
			vec_Stage_2[HEIGHT - 6][item_X] = Item;
		}
		else
		{
			vec_Stage_1[HEIGHT - 6][0] = Blink;
			vec_Stage_2[HEIGHT - 6][0] = Blink;
			item_X = WIDTH - 1;
		}
		if (item_X != WIDTH - 1)
		{
			
			vec_Stage_1[HEIGHT - 6][item_X + 1] = Blink;
			vec_Stage_2[HEIGHT - 6][item_X + 1] = Blink;

		}
	}
	
}

void GameManager::ItemBack()
{
	if (isLeft)
	{
		if (item_X == WIDTH - 1 || item_X == WIDTH || item_X == WIDTH - 2)
		{
			vec_Stage_1[HEIGHT - 6][WIDTH - 1] = Blink;
			vec_Stage_1[HEIGHT - 6][WIDTH - 2] = Blink;
			vec_Stage_2[HEIGHT - 6][WIDTH - 1] = Blink;
			vec_Stage_2[HEIGHT - 6][WIDTH - 2] = Blink;
			item_X = WIDTH - 15;
			vec_Stage_1[HEIGHT - 6][item_X] = Item;
			return;
		}

		item_X++;
		if (item_X <= WIDTH - 1)
		{
			vec_Stage_1[HEIGHT - 6][item_X] = Item;
			vec_Stage_2[HEIGHT - 6][item_X] = Item;
		}
		else
		{
			vec_Stage_1[HEIGHT - 6][WIDTH - 1] = Blink;
			vec_Stage_2[HEIGHT - 6][WIDTH - 1] = Blink;
			item_X = WIDTH - 1;


		}
		if (item_X != WIDTH - 1)
		{

			vec_Stage_1[HEIGHT - 6][item_X - 1] = Blink;
			vec_Stage_2[HEIGHT - 6][item_X - 1] = Blink;

		}
	}
}
#pragma endregion

#pragma region 아이템 먹기
void GameManager::ItemEatCheck()
{
	if (vec_Stage_1[HEIGHT - 6][WIDTH / 2] == Item || vec_Stage_2[HEIGHT - 6][WIDTH / 2] == Item ||
		vec_Stage_1[HEIGHT - 6][WIDTH / 2+1] == Item || vec_Stage_2[HEIGHT - 6][WIDTH / 2+1] == Item ||
		vec_Stage_1[HEIGHT - 6][WIDTH / 2-1] == Item || vec_Stage_2[HEIGHT - 6][WIDTH / 2-1] == Item)
	{
		item_X = WIDTH- 1;
		vec_Stage_1[HEIGHT - 6][WIDTH / 2] = Blink;
		vec_Stage_2[HEIGHT - 6][WIDTH / 2] = Blink;
		vec_Stage_1[HEIGHT - 6][WIDTH / 2+1] = Blink;
		vec_Stage_2[HEIGHT - 6][WIDTH / 2+1] = Blink;
		vec_Stage_1[HEIGHT - 6][WIDTH / 2-1] = Blink;
		vec_Stage_2[HEIGHT - 6][WIDTH / 2-1] = Blink;

		score += 100;

	}



}
#pragma endregion

#pragma region  구름이동
void GameManager::CloudComing()
{
	if (isRight)
	{
		for (int i = 0; i < 3; i++)
		{
			Cloud_X[i]--;
		}
#pragma region  0번
		if (Cloud_X[0] >= 0)
		{
			vec_Stage_1[HEIGHT - 18][Cloud_X[0]] = Cloud;
			vec_Stage_2[HEIGHT - 18][Cloud_X[0]] = Cloud;
		}
		else
		{
			vec_Stage_1[HEIGHT - 18][0] = Blink;
			vec_Stage_2[HEIGHT - 18][0] = Blink;
			Cloud_X[0] = WIDTH - 1;
		}
		if (Cloud_X[0] != WIDTH - 1)
		{

			vec_Stage_1[HEIGHT - 18][Cloud_X[0] + 1] = Blink;
			vec_Stage_2[HEIGHT - 18][Cloud_X[0] + 1] = Blink;
			
		}
#pragma endregion

#pragma region 1번

		if (Cloud_X[1] >= 0)
		{
			vec_Stage_1[HEIGHT - 18][Cloud_X[1]] = Cloud;
			vec_Stage_2[HEIGHT - 18][Cloud_X[1]] = Cloud;
		}
		else
		{
			vec_Stage_1[HEIGHT - 18][0] = Blink;
			vec_Stage_2[HEIGHT - 18][0] = Blink;
			Cloud_X[1] = WIDTH - 1;
		}
		if (Cloud_X[1] != WIDTH - 1)
		{

			vec_Stage_1[HEIGHT - 18][Cloud_X[1] + 1] = Blink;
			vec_Stage_2[HEIGHT - 18][Cloud_X[1] + 1] = Blink;
			
		}
#pragma endregion

#pragma region 2번
		if (Cloud_X[2] >= 0)
		{
			vec_Stage_1[HEIGHT - 18][Cloud_X[2]] = Cloud;
			vec_Stage_2[HEIGHT - 18][Cloud_X[2]] = Cloud;
		}
		else
		{
			vec_Stage_1[HEIGHT - 18][0] = Blink;
			vec_Stage_2[HEIGHT - 18][0] = Blink;
			Cloud_X[2] = WIDTH - 1;
		}
		if (Cloud_X[2] != WIDTH - 1)
		{

			vec_Stage_1[HEIGHT - 18][Cloud_X[2] + 1] = Blink;
			vec_Stage_2[HEIGHT - 18][Cloud_X[2] + 1] = Blink;
			
		}
#pragma endregion

	}
	
}



void GameManager::CloudBack()
{
	if (isLeft)
	{
		for (int i = 0; i < 3; i++)
		{
			Cloud_X[i]++;
		}
		if (Cloud_X[2] >= WIDTH - 1)
		{
			Cloud_X[2] = WIDTH - 1;
			Cloud_X[1] = WIDTH - 2;
			Cloud_X[0] = WIDTH - 3;
			return;
		}

#pragma region  0번
		if (Cloud_X[0] <= WIDTH - 1)
		{
			vec_Stage_1[HEIGHT - 18][Cloud_X[0]] = Cloud;
			vec_Stage_2[HEIGHT - 18][Cloud_X[0]] = Cloud;
		}
		else
		{
			vec_Stage_1[HEIGHT - 18][WIDTH - 1] = Blink;
			vec_Stage_2[HEIGHT - 18][WIDTH - 1] = Blink;
			Cloud_X[0] = WIDTH - 3;
		}
		if (Cloud_X[0] != WIDTH - 3)
		{

			vec_Stage_1[HEIGHT - 18][Cloud_X[0] - 1] = Blink;
			vec_Stage_2[HEIGHT - 18][Cloud_X[0] - 1] = Blink;

		}
#pragma endregion

#pragma region 1번

		if (Cloud_X[1] <= WIDTH - 2)
		{
			vec_Stage_1[HEIGHT - 18][Cloud_X[1]] = Cloud;
			vec_Stage_2[HEIGHT - 18][Cloud_X[1]] = Cloud;
		}
		else
		{
			vec_Stage_1[HEIGHT - 18][WIDTH - 2] = Blink;
			vec_Stage_2[HEIGHT - 18][WIDTH - 2] = Blink;
			Cloud_X[1] = WIDTH - 2;
		}
		if (Cloud_X[1] != WIDTH - 2)
		{
		}
#pragma endregion

#pragma region 2번
		if (Cloud_X[2] <= WIDTH - 3)
		{
			vec_Stage_1[HEIGHT - 18][Cloud_X[2]] = Cloud;
			vec_Stage_2[HEIGHT - 18][Cloud_X[2]] = Cloud;
		}
		else
		{
			vec_Stage_1[HEIGHT - 18][WIDTH - 3] = Blink;
			vec_Stage_2[HEIGHT - 18][WIDTH - 3] = Blink;
			Cloud_X[2] = WIDTH - 1;
		}
		if (Cloud_X[2] != WIDTH - 3)
		{
		}
#pragma endregion
	}
}
#pragma endregion




#pragma region  장애물 부딪침 검사

void GameManager::CheckEnd()
{
	if (vec_Stage_1[HEIGHT - 6][WIDTH / 2] == Character || vec_Stage_2[HEIGHT - 6][WIDTH / 2] == Character)
		return;

	if (vec_Stage_2[HEIGHT - 5][WIDTH / 2] == Enemy || vec_Stage_1[HEIGHT - 5][WIDTH / 2] == Enemy)
	{
		life--;
		enemy_X = WIDTH - 1;
		vec_Stage_2[HEIGHT - 5][WIDTH / 2] = Character;
		vec_Stage_1[HEIGHT - 5][WIDTH / 2] = Character;

	}
	if (life <= 0)
		isGameEnd = true;
}
#pragma endregion

#pragma region 점수 증가

void GameManager::UpScore()
{

	GoToXY(WIDTH + 5, 10);
	printf("점수");
	GoToXY(WIDTH + 10, 10);
	printf("%d", score);

	GoToXY(WIDTH + 5, 15);
	printf("목숨");
	GoToXY(WIDTH + 10, 15);
	printf("%d", life);
}
#pragma endregion

#pragma region 엔딩 이후 함수

void GameManager::CallEndFunc()
{
	GameEnding end;
	bool isRestart = end.Ending(score);
	if (isRestart == true)
	{
		isGameEnd = false;
		isRight = false;
		isLeft = false;
		life = 3;
		Maps maps;
		//맵1 초기화
		vec_Stage_1 = maps.vec_Map_1;
		vec_Stage_1[HEIGHT - 5][WIDTH / 2] = Character;
		//맵2 초기화
		vec_Stage_2 = maps.vec_Map_2;
		vec_Stage_2[HEIGHT - 5][WIDTH / 2] = Character;

		enemy_X = WIDTH - 1;
		vec_Stage_1[HEIGHT - 5][enemy_X] = Enemy;
		vec_Stage_2[HEIGHT - 5][enemy_X] = Enemy;

		item_X = WIDTH - 15;
		vec_Stage_1[HEIGHT - 6][item_X] = Item;
		vec_Stage_2[HEIGHT - 6][item_X] = Item;

		Cloud_X[0] = WIDTH - 3;
		Cloud_X[1] = WIDTH - 2;
		Cloud_X[2] = WIDTH - 1;
		for (int i = 0; i < 3; i++)
		{
			vec_Stage_1[HEIGHT - 18][Cloud_X[i]] = Cloud;
			vec_Stage_2[HEIGHT - 18][Cloud_X[i]] = Cloud;
		}


		score = 0;
		Init();
	}
	else
	{

	}
}
#pragma endregion


#pragma region  GoToXY
void GameManager::GoToXY(int nX, int nY)
{
	COORD cursorPosition = { nX,nY };
	HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hHandle, cursorPosition);
}

#pragma endregion



