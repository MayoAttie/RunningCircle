#include "GameEnding.h"

GameEnding::GameEnding()
{

}

GameEnding::~GameEnding()
{
}

bool GameEnding::Ending(int score)
{
	system("mode con cols=100 lines=25 | title 런닝서클");
	bool isKeyInput = false;
	bool isRestartGame = false;

	system("cls");
	for (int i = 0; i < 50; i++)
	{
		printf("□");
	}
	printf("\n");
	for (int i = 0; i < 50; i++)
	{
		printf("□");
	}


	printf("\n\n\n");

	printf("점수 %d \n", score);
	printf("재시작을 원하면 r, 게임 종료를 원하면 q를 입력하세요.\n");

	printf("\n\n\n");

	for (int i = 0; i < 50; i++)
	{
		printf("□");
	}
	printf("\n");
	for (int i = 0; i < 50; i++)
	{
		printf("□");
	}


	while (isKeyInput == false)
	{
		if (_kbhit())
		{
			char ckey = _getch();
			if (ckey == 'r' || ckey == 'R')
			{
				isKeyInput = true;
				isRestartGame = true;
			}
			else if (ckey == 'q' || ckey == 'Q')
			{
				isKeyInput = true;
			}

		}
		else {}
		Sleep(1);
	}
	system("cls");
	Sleep(500);

	return isRestartGame;
}	
